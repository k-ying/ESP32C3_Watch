/**
 * @file st7789.c
 *
 * Mostly taken from lbthomsen/esp-idf-littlevgl github.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "esp_log.h"

#include "st7789.h"

#include "disp_spi.h"
#include "driver/gpio.h"
#include <math.h>

/*********************
 *      DEFINES
 *********************/
#define TAG "st7789"
/**********************
 *      TYPEDEFS
 **********************/

/*The LCD needs a bunch of command/argument values to be initialized. They are stored in this struct. */
typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes; //No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} lcd_init_cmd_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static uint8_t* shadow_buff;


static void st7789_set_orientation(uint8_t orientation);

static void st7789_send_cmd(uint8_t cmd);
static void st7789_send_data(void *data, uint16_t length);
static void st7789_send_color(void *data, uint16_t length);

void st7789_init_shadow_buff();
static uint16_t st7789_encode_header(uint8_t* buff, lv_area_t * area);
static uint16_t st7789_encode_data(uint8_t* buff, uint8_t* data, uint16_t length);


/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void st7789_init(void)
{
    /*
    lcd_init_cmd_t st7789_init_cmds[] = {
        {0xCF, {0x00, 0x83, 0X30}, 3},
        {0xED, {0x64, 0x03, 0X12, 0X81}, 4},
        {ST7789_PWCTRL2, {0x85, 0x01, 0x79}, 3},
        {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
        {0xF7, {0x20}, 1},
        {0xEA, {0x00, 0x00}, 2},
        {ST7789_LCMCTRL, {0x26}, 1},
        {ST7789_IDSET, {0x11}, 1},
        {ST7789_VCMOFSET, {0x35, 0x3E}, 2},
        {ST7789_CABCCTRL, {0xBE}, 1},
        {ST7789_MADCTL, {0x00}, 1}, // Set to 0x28 if your display is flipped
        {ST7789_COLMOD, {0x55}, 1},
#if ST7789_INVERT_COLORS == 1
		{ST7789_INVON, {0}, 0}, // set inverted mode
#else
 		{ST7789_INVOFF, {0}, 0}, // set non-inverted mode
#endif
        {ST7789_RGBCTRL, {0x00, 0x1B}, 2},
        {0xF2, {0x08}, 1},
        {ST7789_GAMSET, {0x01}, 1},
        {ST7789_PVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x32, 0x44, 0x42, 0x06, 0x0E, 0x12, 0x14, 0x17}, 14},
        {ST7789_NVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x31, 0x54, 0x47, 0x0E, 0x1C, 0x17, 0x1B, 0x1E}, 14},
        {ST7789_CASET, {0x00, 0x00, 0x00, 0xEF}, 4},
        {ST7789_RASET, {0x00, 0x00, 0x01, 0x3f}, 4},
        {ST7789_RAMWR, {0}, 0},
        {ST7789_GCTRL, {0x07}, 1},
        {0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
        {ST7789_SLPOUT, {0}, 0x80},
        {ST7789_DISPON, {0}, 0x80},
        {0, {0}, 0xff},
    };*/


        lcd_init_cmd_t st7789_init_cmds[] = {
        {0x11, {0}, 0x80},
        {0x36, {0}, 1},
        {0x3a, {0x05}, 1},
        {0xb2, {0x0c, 0x0c, 0x00, 0x33, 0x33}, 5},
        {0xb7, {0x35}, 1},
        {0xbb, {0x1f}, 1},
        {0xc0, {0x2c}, 1},
        {0xc2, {0x01}, 1},
        {0xc3, {0x1d}, 1},
        {0xc4, {0x20}, 1},
        {0xc6, {0x0f},1},
        {ST7789_INVON, {0}, 0}, // set inverted mode
        {0xd0, {0xa4, 0xa1},2},
        {0xe4, {0x27, 0x00, 0x10}, 3},
        {0xe0, {0xd0, 0x00, 0x14, 0x15, 0x13, 0x2c, 0x42, 0x43, 0x4e, 0x09, 0x16, 0x14, 0x18, 0x21}, 14},
        {0xe1, {0xd0, 0x00, 0x14, 0x15, 0x13, 0x0b, 0x43, 0x55, 0x53, 0x0c, 0x17, 0x14, 0x23, 0x20}, 14},
        {0x29, {0}, 0},
        {0, {0}, 0xff},
    };

    //Initialize non-SPI GPIOs
    gpio_pad_select_gpio(ST7789_DC);
    gpio_set_direction(ST7789_DC, GPIO_MODE_OUTPUT);

#if !defined(CONFIG_LV_DISP_ST7789_SOFT_RESET)
    gpio_pad_select_gpio(ST7789_RST);
    gpio_set_direction(ST7789_RST, GPIO_MODE_OUTPUT);
#endif

#if ST7789_ENABLE_BACKLIGHT_CONTROL
    gpio_pad_select_gpio(ST7789_BCKL);
    gpio_set_direction(ST7789_BCKL, GPIO_MODE_OUTPUT);
#endif

    //Reset the display
#if !defined(CONFIG_LV_DISP_ST7789_SOFT_RESET)
    gpio_set_level(ST7789_RST, 0);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(ST7789_RST, 1);
    vTaskDelay(100 / portTICK_RATE_MS);
#else
    st7789_send_cmd(ST7789_SWRESET);
#endif

    printf("ST7789 initialization.\n");

    //Send all the commands
    uint16_t cmd = 0;
    while (st7789_init_cmds[cmd].databytes!=0xff) {
        st7789_send_cmd(st7789_init_cmds[cmd].cmd);
        st7789_send_data(st7789_init_cmds[cmd].data, st7789_init_cmds[cmd].databytes&0x1F);
        if (st7789_init_cmds[cmd].databytes & 0x80) {
                vTaskDelay(100 / portTICK_RATE_MS);
        }
        cmd++;
    }

    st7789_enable_backlight(true);

    st7789_init_shadow_buff();

    st7789_set_orientation(CONFIG_LV_DISPLAY_ORIENTATION);
}


void st7789_enable_backlight(bool backlight)
{
#if ST7789_ENABLE_BACKLIGHT_CONTROL
    printf("%s backlight.\n", backlight ? "Enabling" : "Disabling");
    uint32_t tmp = 0;

#if (ST7789_BCKL_ACTIVE_LVL==1)
    tmp = backlight ? 1 : 0;
#else
    tmp = backlight ? 0 : 1;
#endif

    //gpio_set_level(ST7789_BCKL, tmp);
#endif
}

void st7789_rounder_cb(lv_disp_drv_t * disp_drv, lv_area_t * area)
{
  /* Update the areas as needed.
   * For example it makes the area to start only on 8th rows and have Nx8 pixel height.*/
   area->x1 = ((area->x1) & 0xFFFFFFF8);
   area->x2 = ((area->x2 + 1) & 0xFFFFFFF8) + 7;
   uint8_t hor_max = disp_drv->hor_res;
   if(area->x2 > hor_max -1){
       area->x2 = hor_max - 1;
   }
}

/* The ST7789 display controller can drive 320*240 displays, when using a 240*240
 * display there's a gap of 80px, we need to edit the coordinates to take into
 * account that gap, this is not necessary in all orientations. */
void st7789_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map)
{
    uint16_t pos = 0;

    pos = st7789_encode_header(shadow_buff, area);
    uint32_t size = lv_area_get_width(area) * lv_area_get_height(area);
    pos += st7789_encode_data(shadow_buff + pos, (void*) color_map, size * 2);
    st7789_send_color((void*)shadow_buff, pos);
    //printf("flush:(%d,%d), (%d, %d)\n", area->x1, area->y1, area->x2, area->y2);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void st7789_send_cmd(uint8_t cmd)
{
    disp_wait_for_pending_transactions();
   // gpio_set_level(ST7789_DC, 0);
    disp_spi_send_data_dc(&cmd, 1, 0);
    //disp_spi_send_data(&cmd, 1);
}

static void st7789_send_data(void * data, uint16_t length)
{
    disp_wait_for_pending_transactions();
   // gpio_set_level(ST7789_DC, 1);
    for(uint16_t i=0; i<length; i++){
        disp_spi_send_data_dc(&data[i], 1, 1);
        //disp_spi_send_data(&data[i], 1);
    }
    
}

static void st7789_send_color(void * data, uint16_t length)
{
    disp_wait_for_pending_transactions();
    disp_spi_send_colors(data, length);
}

static void st7789_set_orientation(uint8_t orientation)
{
    // ESP_ASSERT(orientation < 4);

    const char *orientation_str[] = {
        "PORTRAIT", "PORTRAIT_INVERTED", "LANDSCAPE", "LANDSCAPE_INVERTED"
    };

    ESP_LOGI(TAG, "Display orientation: %s", orientation_str[orientation]);

    uint8_t data[] =
    {
#if CONFIG_LV_PREDEFINED_DISPLAY_TTGO
	0x60, 0xA0, 0x00, 0xC0
#else
	0xC0, 0x00, 0x60, 0xA0
#endif
    };

    ESP_LOGI(TAG, "0x36 command value: 0x%02X", data[orientation]);

    st7789_send_cmd(ST7789_MADCTL);
    st7789_send_data((void *) &data[orientation], 1);
}


void st7789_init_shadow_buff()
{
    const uint32_t dis_buff_size = DISP_BUF_SIZE * sizeof(lv_color_t);
    uint32_t shadow_buff_size = ceil( dis_buff_size * 1.125f ) + 18; // factor 9/8
    shadow_buff = heap_caps_malloc(shadow_buff_size, MALLOC_CAP_DMA);
    printf("shadow buff: dis_buf_size=%d bytes, shadow_buf_size=%d\n", dis_buff_size, shadow_buff_size);
    assert(shadow_buff != NULL);
}


uint16_t st7789_encode_header(uint8_t* buff, lv_area_t * area){

     uint8_t data[4] = {0};

    uint16_t offsetx1 = area->x1;
    uint16_t offsetx2 = area->x2;
    uint16_t offsety1 = area->y1;
    uint16_t offsety2 = area->y2;

#if (CONFIG_LV_TFT_DISPLAY_OFFSETS)
    offsetx1 += CONFIG_LV_TFT_DISPLAY_X_OFFSET;
    offsetx2 += CONFIG_LV_TFT_DISPLAY_X_OFFSET;
    offsety1 += CONFIG_LV_TFT_DISPLAY_Y_OFFSET;
    offsety2 += CONFIG_LV_TFT_DISPLAY_Y_OFFSET;

#elif (LV_HOR_RES_MAX == 240) && (LV_VER_RES_MAX == 240)
    offsety1 += 40;
    offsety2 += 40;
#if (CONFIG_LV_DISPLAY_ORIENTATION_PORTRAIT)
    offsetx1 += 80;
    offsetx2 += 80;
#elif (CONFIG_LV_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED)
    offsety1 += 80;
    offsety2 += 80;
#endif
#endif


    data[0] = (offsetx1 >> 8) & 0xFF;
    data[1] = offsetx1 & 0xFF;
    data[2] = (offsetx2 >> 8) & 0xFF;
    data[3] = offsetx2 & 0xFF;
    
    buff[0] =  ST7789_CASET >> 1;
    buff[1] = ( ST7789_CASET << 7)| 0x40 | (data[0] >> 2);
    buff[2] = (data[0] << 6) | 0x20 | (data[1] >> 3);
    buff[3] = (data[1] << 5) | 0x10 | (data[2] >> 4);
    buff[4] = (data[2] << 4) | 0x8 | (data[3] >> 5);
    buff[5] = (data[3] << 3) | 0x0  | (ST7789_RASET >> 6);

    data[0] = (offsety1 >> 8) & 0xFF;
    data[1] = offsety1 & 0xFF;
    data[2] = (offsety2 >> 8) & 0xFF;
    data[3] = offsety2 & 0xFF;

    buff[6] = (ST7789_RASET << 2) | 0x2  | (data[0] >> 7);
    buff[7] = (data[0] << 1) | 0x1;
    buff[8] = data[1];
    buff[9] = 0x80 | (data[2] >> 1);
    buff[10] = (data[2] << 7) | 0x40 | (data[3] >> 2);
    buff[11] = (data[3] << 6);
    buff[12] = 0;
    buff[13] = 0;
    buff[14] = 0;
    buff[15] = 0;
    buff[16] = 0;
    buff[17] = ST7789_RAMWR;

    return 18;

}

static void st7789_encode_8b_fully(uint8_t *buff, uint8_t *data) {
    buff[0] = 0x80 | (data[0] >> 1);
    buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
    buff[2] = (data[1] << 6) | 0x20 | (data[2] >> 3);
    buff[3] = (data[2] << 5) | 0x10 | (data[3] >> 4);
    buff[4] = (data[3] << 4) | 0x8 | (data[4] >> 5);
    buff[5] = (data[4] << 3) | 0x4 | (data[5] >> 6);
    buff[6] = (data[5] << 2) | 0x2 | (data[6] >> 7);
    buff[7] = (data[6] << 1) | 0x1;
    buff[8] = data[7];
}

static void st7789_encode_8b_last(uint8_t *buff, uint8_t *data, uint8_t mod) {
    switch (mod) {
        case 7: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
            buff[2] = (data[1] << 6) | 0x20 | (data[2] >> 3);
            buff[3] = (data[2] << 5) | 0x10 | (data[3] >> 4);
            buff[4] = (data[3] << 4) | 0x8 | (data[4] >> 5);
            buff[5] = (data[4] << 3) | 0x4 | (data[5] >> 6);
            buff[6] = (data[5] << 2) | 0x2 | (data[6] >> 7);
            buff[7] = (data[6] << 1);
            buff[8] = 0;
        }
            break;
        case 6: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
            buff[2] = (data[1] << 6) | 0x20 | (data[2] >> 3);
            buff[3] = (data[2] << 5) | 0x10 | (data[3] >> 4);
            buff[4] = (data[3] << 4) | 0x8 | (data[4] >> 5);
            buff[5] = (data[4] << 3) | 0x4 | (data[5] >> 6);
            buff[6] = (data[5] << 2);
            buff[7] = 0;
            buff[8] = 0;
        }
            break;

        case 5: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
            buff[2] = (data[1] << 6) | 0x20 | (data[2] >> 3);
            buff[3] = (data[2] << 5) | 0x10 | (data[3] >> 4);
            buff[4] = (data[3] << 4) | 0x8 | (data[4] >> 5);
            buff[5] = (data[4] << 3);
            buff[6] = 0;
            buff[7] = 0;
            buff[8] = 0;
        }
            break;

        case 4: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
            buff[2] = (data[1] << 6) | 0x20 | (data[2] >> 3);
            buff[3] = (data[2] << 5) | 0x10 | (data[3] >> 4);
            buff[4] = (data[3] << 4);
            buff[5] = 0;
            buff[6] = 0;
            buff[7] = 0;
            buff[8] = 0;
        }
            break;

        case 3: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
            buff[2] = (data[1] << 6) | 0x20 | (data[2] >> 3);
            buff[3] = (data[2] << 5);
            buff[4] = 0;
            buff[5] = 0;
            buff[6] = 0;
            buff[7] = 0;
            buff[8] = 0;
        }
            break;

        case 2: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7) | 0x40 | (data[1] >> 2);
            buff[2] = (data[1] << 6);
            buff[3] = 0;
            buff[4] = 0;
            buff[5] = 0;
            buff[6] = 0;
            buff[7] = 0;
            buff[8] = 0;
        }
            break;
        case 1: {
            buff[0] = 0x80 | (data[0] >> 1);
            buff[1] = (data[0] << 7);
            buff[2] = 0;
            buff[3] = 0;
            buff[4] = 0;
            buff[5] = 0;
            buff[6] = 0;
            buff[7] = 0;
            buff[8] = 0;
        }
            break;
    }
}


static uint16_t st7789_encode_data(uint8_t *buff, uint8_t *data, uint16_t length) {
    uint8_t mod = length & 7;
    uint16_t i = 0, j = 0;
    for (; i < length - mod; i += 8, j += 9) {
        st7789_encode_8b_fully(buff + j, data + i);
    }
    if (mod > 0) {
        st7789_encode_8b_last(buff + j, data + i, mod);
    }
    return ((length >> 3) + (mod > 0 ? 1 : 0)) * 9;
}
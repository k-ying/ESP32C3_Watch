/* LVGL Example project
 *
 * Basic project to test LVGL on ESP32 based projects.
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
//#include "components/lvgl/lvgl.h"
#endif
/* USER Need */
#include "lvgl_helpers.h"
#include "generated/gui_guider.h"
#include "generated/events_init.h"
#include "generated/custom/custom.h"
#include "MAX30205.h"
#include "max30102-registers.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "max30102.h"
#include "userwifi.h"
/****************** VAR *********************/
lv_ui guider_ui;
bool scrloading = false,Fallen=false,people_flag=false,sleep_flag=false;
uint8_t time_sec=0,time_min=0,time_hour=0,time_sync_flag=0;
char time_day[11];
float temp_value = 0,stepDis=0,stepF=0;
unsigned long step_count = 0;
max30102_config_t max30102 = {};
max30102_data_t result = {};
extern lv_chart_series_t * APPtoHR_chart_HeartBeep_0;
int HR_TIM_CNT=8000;
int16_t ax=0,ay=0,az=0;
/****************** VAR *********************/

#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    #if defined CONFIG_LV_USE_DEMO_WIDGETS
        #include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
    #elif defined CONFIG_LV_USE_DEMO_KEYPAD_AND_ENCODER
        #include "lv_examples/src/lv_demo_keypad_encoder/lv_demo_keypad_encoder.h"
    #elif defined CONFIG_LV_USE_DEMO_BENCHMARK
        #include "lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.h"
    #elif defined CONFIG_LV_USE_DEMO_STRESS
        #include "lv_examples/src/lv_demo_stress/lv_demo_stress.h"
    #else
        #error "No demo application selected."
    #endif
#endif

/*********************
 *      DEFINES
 *********************/
#define TAG "demo"
#define LV_TICK_PERIOD_MS 1

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
// static void sec_tick_task(void *arg);
// static void Xms_tick_task(void *arg);
void lv_sec_task(lv_task_t * sec_task);
void lv_xms_task(lv_task_t * xms_task);
static void guiTask(void *pvParameter);
// static void create_demo_application(void);
void memory_print(void);
/**********************
 *   APPLICATION MAIN
 **********************/
void app_main() {
    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
    gpio_pad_select_gpio(ST7789_BCKL);                // BCKL OFF when boot
    gpio_set_direction(ST7789_BCKL, GPIO_MODE_OUTPUT);// 
    gpio_set_level(ST7789_BCKL, 0);                   // 
    xTaskCreatePinnedToCore(guiTask, "gui", 4096*13, NULL, 0, NULL, 0);
}

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

static void guiTask(void *pvParameter) {

    (void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    lv_color_t* buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    /* Use double buffered when not working with monochrome displays */
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    lv_color_t* buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);
#else
    static lv_color_t *buf2 = NULL;
#endif

    static lv_disp_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820         \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A    \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D     \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306

    /* Actual size in pixels, not bytes. */
    size_in_px *= 8;
#endif

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

    /* When using a monochrome display we need to register the callbacks:
     * - rounder_cb
     * - set_px_cb */
#ifdef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
#endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif
    
    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    esp_timer_handle_t periodic_timer;//periodic_sec_timer,periodic_Xms_timer;
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));//定时器单位us，此操作1ms调用一次lv_tick_inc(1)

    /*********************************** Create LVGL application ************************************/
    //create_demo_application();
	setup_ui(&guider_ui);
    // events_init(&guider_ui);
    // custom_init(&guider_ui);
    /*************************************** Sensor Init ********************************************/
    int ret = MAX30205_Init();
    if(ret==ESP_OK){
        printf("MAX30205_Init Successful!\n");
    }else{
        printf("MAX30205_Init Error!\n");
    }
    ret = mpu_dmp_init();
    if(ret==0){
        printf("MPU6050_Init Successful!\n");
    }else{
        printf("MPU6050_Init Error!\n");
    }
    ESP_ERROR_CHECK(max30102_init( &max30102, I2C_NUM_0,
               MAX30102_DEFAULT_OPERATING_MODE,
               MAX30102_DEFAULT_SAMPLING_RATE,
               MAX30102_DEFAULT_LED_PULSE_WIDTH,
               MAX30102_DEFAULT_IR_LED_CURRENT,
               MAX30102_DEFAULT_START_RED_LED_CURRENT,
               MAX30102_DEFAULT_MEAN_FILTER_SIZE,
               MAX30102_DEFAULT_PULSE_BPM_SAMPLE_SIZE,
               MAX30102_DEFAULT_ADC_RANGE, 
               MAX30102_DEFAULT_SAMPLE_AVERAGING,
               MAX30102_DEFAULT_ROLL_OVER,
               MAX30102_DEFAULT_ALMOST_FULL,
               false ));
    gpio_pad_select_gpio(ST7789_BCKL);                // BCKL ON
    gpio_set_direction(ST7789_BCKL, GPIO_MODE_OUTPUT);//
    gpio_set_level(ST7789_BCKL, 1);                   //
    //Shutdowm MAX30102 after boot
    max30102_set_mode(&max30102, MAX30102_SHDN_ON);
    // /*************************************** USER Tick ********************************************/
    // const esp_timer_create_args_t periodic_sec_timer_args = {
    //     .callback = &sec_tick_task,
    //     .name = "sec_tick"
    // };
    // ESP_ERROR_CHECK(esp_timer_create(&periodic_sec_timer_args, &periodic_sec_timer));
    // ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_sec_timer, 1000 * 1000));//定时器单位us，此操作1s调用一次

    // const esp_timer_create_args_t periodic_Xms_timer_args = {
    // .callback = &Xms_tick_task,
    // .name = "Xms_tick"
    // };
    // ESP_ERROR_CHECK(esp_timer_create(&periodic_Xms_timer_args, &periodic_Xms_timer));
    // ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_Xms_timer, 50 * 1000));//定时器单位us，此操作50ms调用一次
    
    lv_task_t * sec_task = lv_task_create(lv_sec_task, 1000, LV_TASK_PRIO_MID,NULL);
    lv_task_t * xms_task = lv_task_create(lv_xms_task, 10, LV_TASK_PRIO_LOW,NULL);
    
    if(ret != 0){
        static const char * notify_btns[] ={"Close", ""};
        guider_ui.notify_msgbox = lv_msgbox_create(lv_scr_act(), NULL);
        lv_msgbox_set_text(guider_ui.notify_msgbox, "Init Error, pls reboot!");
        lv_msgbox_add_btns(guider_ui.notify_msgbox, notify_btns);
        lv_obj_set_width(guider_ui.notify_msgbox, 200);
        lv_obj_align(guider_ui.notify_msgbox, NULL, LV_ALIGN_CENTER, 0, 0);
    }

    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
        /* ------------------- SCR Sleep code ---------------- */
        if ((sleep_flag==0) && (lv_disp_get_inactive_time(NULL) > 30*1000)){
            gpio_pad_select_gpio(ST7789_BCKL);                // BCKL OFF
            gpio_set_direction(ST7789_BCKL, GPIO_MODE_OUTPUT);//
            gpio_set_level(ST7789_BCKL, 0);                   //
            sleep_flag=1;
        }else if (sleep_flag && (lv_disp_get_inactive_time(NULL) <= 30*1000)){
            gpio_pad_select_gpio(ST7789_BCKL);                // BCKL ON
            gpio_set_direction(ST7789_BCKL, GPIO_MODE_OUTPUT);//
            gpio_set_level(ST7789_BCKL, 1);                   //
            sleep_flag=0;
        }
        if (az > 10000){
            lv_disp_trig_activity(NULL); //when screen up, trigger it to avoid inactive_time over
        }
        /* ------------------- SCR Sleep code ---------------- */
    }

    /* A task should NEVER return */
    free(buf1);
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    free(buf2);
#endif
    vTaskDelete(NULL);
}


static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void lv_sec_task(lv_task_t * sec_task){
    if(time_sec<59){
        time_sec++;
    }else{
        time_sec = 0;
        if(time_min<59){
            time_min++;
        }else{
            time_min=0;
            if(time_hour<23){
                time_hour++;
            }else{time_hour=0;}
        }
        if((lv_scr_act() == guider_ui.Timehome) && scrloading==0){
            Timeset_func(&guider_ui,time_hour,time_min,time_day);//display update every min
        }
    }
    if(time_sync_flag && (lv_scr_act() == guider_ui.Timehome) && scrloading==0)//sync time now
    {
        Timeset_func(&guider_ui,time_hour,time_min,time_day);
        time_sync_flag=0;
    }
    if(scrloading==0){
        //tempset
        temp_value = (float)GetTemperature();
        if(temp_value > 30.9)
        {
            people_flag=1;
        }else people_flag=0;  
        Tempset_func(&guider_ui,temp_value);
        //stepset
        // dmp_get_pedometer_step_count(&step_count);
        Stepset_func(&guider_ui,step_count,stepDis);
        //HRset
        HR_func(&guider_ui,result.heart_bpm,result.spO2);
        //memory_print();
    }
    if (time_min%5==0 && time_sec==0){
        max30102_set_mode(&max30102, MAX30102_SHDN_OFF);//start max30102
        HR_TIM_CNT=0;
    }
}

void lv_xms_task(lv_task_t * xms_task){
    static unsigned long beforeStepC=0;
    static int beforeTickC=0;
    // printf("MAX: %f\n", result.ir_cardiogram);
    // if(result.pulse_detected) {
    //     printf("-----\n");
    //     printf("BPM: %f | SpO2: %f%%\n", result.heart_bpm, result.spO2);
    // }
    /*------------------------------------ MAX30102 UPDATE ------------------------------------*/
    if(lv_scr_act() == guider_ui.APPtoHR){ //when HR_APP page now
        if(lv_debug_check_obj_valid(guider_ui.APPtoHR_chart_HeartBeep))
        {
            max30102_update(&max30102, &result);
            lv_chart_set_next(guider_ui.APPtoHR_chart_HeartBeep,APPtoHR_chart_HeartBeep_0,result.ir_cardiogram);
        }
    }else if (people_flag == 1 && HR_TIM_CNT<3000){//if people wearing, keep data updating periodically
        max30102_update(&max30102, &result);
        HR_TIM_CNT++;
        if(HR_TIM_CNT==2999) max30102_set_mode(&max30102, MAX30102_SHDN_ON);/*shutdown max30102*/
    }else{HR_TIM_CNT=8000;}
    /*------------------------------------ STEPS & FALLDETECT TASK ------------------------------------*/
	MPU_Get_Accelerometer(&ax,&ay,&az);
    float svm_v = sqrt((ax/16384.0)*(ax/16384.0) + (ay/16384.0)*(ay/16384.0)  + (az/16384.0)*(az/16384.0));
    dmp_get_pedometer_step_count(&step_count);
    if(step_count != beforeStepC){
        stepF = 1/(((xTaskGetTickCount()-beforeTickC)*portTICK_PERIOD_MS)*0.001);
        printf("stepF=%f\r\n",stepF);
        beforeTickC=xTaskGetTickCount();
        stepDis = stepDis+(0.132*svm_v+0.123*stepF+0.225)*(step_count-beforeStepC);
        beforeStepC=step_count;
    }
    static uint8_t Div2=0;
    if(Div2==9){
        if(SVM_FallenDet(svm_v,az)==1)
        {
            Fallen=true;
            if(!lv_debug_check_obj_valid(guider_ui.notify_msgbox))
            {
                static const char * notify_btns[] ={"Close", ""};
                guider_ui.notify_msgbox = lv_msgbox_create(lv_scr_act(), NULL);
                lv_msgbox_set_text(guider_ui.notify_msgbox, "Fall Detected!");
                lv_msgbox_add_btns(guider_ui.notify_msgbox, notify_btns);
                lv_obj_set_width(guider_ui.notify_msgbox, 200);
                lv_obj_align(guider_ui.notify_msgbox, NULL, LV_ALIGN_CENTER, 0, 0);
            }
        }
        Div2=0;
    }else{Div2++;}
    // printf("FALLEN=%d\n",SVM_FallenDet());
}
void lv_mqtt_task(lv_task_t * task)
{
    {
        char pub_payload_c3data[150];
        sprintf(pub_payload_c3data,"{\"method\":\"thing.event.property.post\",\"params\":{\"Temp\":%2.1f,\"Step\":%d,\"HR\":%2.1f,\"SpO2\":%2.1f,\"Fallen\":%d}}",temp_value,step_count,result.heart_bpm,result.spO2,Fallen);
        esp_mqtt_client_publish(task->user_data, "/sys/a1fpFa35yU2/demo1/thing/event/property/post", pub_payload_c3data, 0, 0, 0);
        //printf("mem================%d\n",esp_get_free_heap_size());
    }
    // static uint8_t time_count =0;
    if(Fallen)
    {
        // time_count++;
        // if(time_count>=6){
        //     time_count=0;
            Fallen=0;
        // }  
    }
}

void memory_print(void)
{
    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
                mon.used_pct,
                mon.frag_pct,
                (int)mon.free_biggest_size);
}

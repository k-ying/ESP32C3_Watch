/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "userwifi.h"

static lv_obj_t * kb;
static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
{
	/* Just call the regular event handler */
	lv_keyboard_def_event_cb(event_kb, event);
	if(event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL){
		if(NULL != kb){
			lv_obj_del(kb);
		}
	}
}
static void text_area_event_cb(lv_obj_t* ta, lv_event_t event)
{

	if(event == LV_EVENT_CLICKED){
		 if( !lv_debug_check_obj_valid(kb) ){
			/* Create a keyboard and make it fill the width of the above text areas */
			kb = lv_keyboard_create(lv_scr_act(), NULL);
			lv_obj_set_event_cb(kb, kb_event_cb);
			lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
		}
		lv_keyboard_set_textarea(kb, ta);
		lv_keyboard_set_cursor_manage(kb, true); 
	}
}

void setup_scr_APPtoConnect(lv_ui *ui){

	esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret =  nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
	// extern char wifi_ssid;
	// extern char wifi_passwd;
	nvs_handle_t wifiget_handle;
    esp_err_t err;
	err = nvs_open("wifisave", NVS_READWRITE, &wifiget_handle);
    if (err != ESP_OK){printf("nvs_open_error:%d\n",err);}
	
	size_t required_size = 0;
    err = nvs_get_str(wifiget_handle, "wifissid",NULL,&required_size);
    // err = nvs_get_i32(my_handle, "str_test", &restart_counter);
    // if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return err;
    // err = nvs_get_blob(my_handle, "run_time", NULL, &required_size);
    if (err == ESP_ERR_NVS_NOT_FOUND)
	{
		printf("nvs_not_found,wifisave set default\n");
		// nvs_handle_t wifisave_handle;
        // nvs_open("wifisave", NVS_READWRITE, &wifisave_handle);
        nvs_set_str(wifiget_handle,"wifissid","kyGTneotest");
		nvs_commit(wifiget_handle);
        nvs_set_str(wifiget_handle,"wifipasswd","kygtneo232");
        nvs_commit(wifiget_handle);
        //nvs_close(wifiget_handle);
	}
    err = nvs_get_str(wifiget_handle, "wifissid", wifi_ssid, &required_size);
	printf("str is: %s , size is %d \n",wifi_ssid,required_size);
	err = nvs_get_str(wifiget_handle, "wifipasswd",NULL,&required_size);
	err = nvs_get_str(wifiget_handle, "wifipasswd", wifi_passwd, &required_size);
	printf("str is: %s , size is %d \n",wifi_passwd,required_size);
    //printf("nvs_get other error:%d\n",err);
    // Close nvs
    nvs_close(wifiget_handle);

	/* -------------------------------------- USER Init wifi(UP) ----------------------------------------- */

	//Write codes APPtoConnect
	ui->APPtoConnect = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for APPtoConnect
	static lv_style_t style_APPtoConnect_main;
	lv_style_reset(&style_APPtoConnect_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_main
	lv_style_set_bg_color(&style_APPtoConnect_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_APPtoConnect_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoConnect, LV_OBJ_PART_MAIN, &style_APPtoConnect_main);

	//Write codes APPtoConnect_input_SSID
	ui->APPtoConnect_input_SSID = lv_textarea_create(ui->APPtoConnect, NULL);

	//Write style LV_PAGE_PART_BG for APPtoConnect_input_SSID
	static lv_style_t style_APPtoConnect_input_SSID_bg;
	lv_style_reset(&style_APPtoConnect_input_SSID_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_input_SSID_bg
	lv_style_set_radius(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_border_color(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_text_color(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_right(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_top(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_bottom(&style_APPtoConnect_input_SSID_bg, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->APPtoConnect_input_SSID, LV_PAGE_PART_BG, &style_APPtoConnect_input_SSID_bg);

	//Write style LV_PAGE_PART_SCROLLABLE for APPtoConnect_input_SSID
	static lv_style_t style_APPtoConnect_input_SSID_scrollable;
	lv_style_reset(&style_APPtoConnect_input_SSID_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_input_SSID_scrollable
	lv_style_set_radius(&style_APPtoConnect_input_SSID_scrollable, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_input_SSID_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_input_SSID_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_input_SSID_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_APPtoConnect_input_SSID_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoConnect_input_SSID, LV_PAGE_PART_SCROLLABLE, &style_APPtoConnect_input_SSID_scrollable);

	//Write style LV_PAGE_PART_EDGE_FLASH for APPtoConnect_input_SSID
	static lv_style_t style_APPtoConnect_input_SSID_edge_flash;
	lv_style_reset(&style_APPtoConnect_input_SSID_edge_flash);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_input_SSID_edge_flash
	lv_style_set_radius(&style_APPtoConnect_input_SSID_edge_flash, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_input_SSID_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_input_SSID_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_input_SSID_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_input_SSID_edge_flash, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoConnect_input_SSID, LV_PAGE_PART_EDGE_FLASH, &style_APPtoConnect_input_SSID_edge_flash);
	lv_obj_set_pos(ui->APPtoConnect_input_SSID, 80, 25);
	lv_obj_set_size(ui->APPtoConnect_input_SSID, 140, 25);
	lv_textarea_set_text(ui->APPtoConnect_input_SSID, wifi_ssid);//--------------------
	lv_obj_set_event_cb(ui->APPtoConnect_input_SSID, text_area_event_cb);
	lv_textarea_set_text_align(ui->APPtoConnect_input_SSID, LV_LABEL_ALIGN_LEFT);

	//Write codes APPtoConnect_label_SSID
	ui->APPtoConnect_label_SSID = lv_label_create(ui->APPtoConnect, NULL);
	lv_label_set_text(ui->APPtoConnect_label_SSID, "SSID");
	lv_label_set_long_mode(ui->APPtoConnect_label_SSID, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoConnect_label_SSID, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoConnect_label_SSID
	static lv_style_t style_APPtoConnect_label_SSID_main;
	lv_style_reset(&style_APPtoConnect_label_SSID_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_label_SSID_main
	lv_style_set_radius(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoConnect_label_SSID_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoConnect_label_SSID, LV_LABEL_PART_MAIN, &style_APPtoConnect_label_SSID_main);
	lv_obj_set_pos(ui->APPtoConnect_label_SSID, 5, 30);
	lv_obj_set_size(ui->APPtoConnect_label_SSID, 70, 0);

	//Write codes APPtoConnect_input_PWD
	ui->APPtoConnect_input_PWD = lv_textarea_create(ui->APPtoConnect, NULL);

	//Write style LV_PAGE_PART_BG for APPtoConnect_input_PWD
	static lv_style_t style_APPtoConnect_input_PWD_bg;
	lv_style_reset(&style_APPtoConnect_input_PWD_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_input_PWD_bg
	lv_style_set_radius(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_border_color(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_text_color(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_right(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_top(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_bottom(&style_APPtoConnect_input_PWD_bg, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->APPtoConnect_input_PWD, LV_PAGE_PART_BG, &style_APPtoConnect_input_PWD_bg);

	//Write style LV_PAGE_PART_SCROLLABLE for APPtoConnect_input_PWD
	static lv_style_t style_APPtoConnect_input_PWD_scrollable;
	lv_style_reset(&style_APPtoConnect_input_PWD_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_input_PWD_scrollable
	lv_style_set_radius(&style_APPtoConnect_input_PWD_scrollable, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_input_PWD_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_input_PWD_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_input_PWD_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_APPtoConnect_input_PWD_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoConnect_input_PWD, LV_PAGE_PART_SCROLLABLE, &style_APPtoConnect_input_PWD_scrollable);

	//Write style LV_PAGE_PART_EDGE_FLASH for APPtoConnect_input_PWD
	static lv_style_t style_APPtoConnect_input_PWD_edge_flash;
	lv_style_reset(&style_APPtoConnect_input_PWD_edge_flash);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_input_PWD_edge_flash
	lv_style_set_radius(&style_APPtoConnect_input_PWD_edge_flash, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_input_PWD_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_input_PWD_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_input_PWD_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_input_PWD_edge_flash, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoConnect_input_PWD, LV_PAGE_PART_EDGE_FLASH, &style_APPtoConnect_input_PWD_edge_flash);
	lv_obj_set_pos(ui->APPtoConnect_input_PWD, 80, 65);
	lv_obj_set_size(ui->APPtoConnect_input_PWD, 140, 25);
	lv_textarea_set_text(ui->APPtoConnect_input_PWD, wifi_passwd);//------------------------
	lv_obj_set_event_cb(ui->APPtoConnect_input_PWD, text_area_event_cb);
	lv_textarea_set_text_align(ui->APPtoConnect_input_PWD, LV_LABEL_ALIGN_LEFT);

	//Write codes APPtoConnect_label_PWD
	ui->APPtoConnect_label_PWD = lv_label_create(ui->APPtoConnect, NULL);
	lv_label_set_text(ui->APPtoConnect_label_PWD, "PWD");
	lv_label_set_long_mode(ui->APPtoConnect_label_PWD, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoConnect_label_PWD, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoConnect_label_PWD
	static lv_style_t style_APPtoConnect_label_PWD_main;
	lv_style_reset(&style_APPtoConnect_label_PWD_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_label_PWD_main
	lv_style_set_radius(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoConnect_label_PWD_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoConnect_label_PWD, LV_LABEL_PART_MAIN, &style_APPtoConnect_label_PWD_main);
	lv_obj_set_pos(ui->APPtoConnect_label_PWD, 5, 70);
	lv_obj_set_size(ui->APPtoConnect_label_PWD, 70, 0);

	//Write codes APPtoConnect_cb_Remember
	ui->APPtoConnect_cb_Remember = lv_checkbox_create(ui->APPtoConnect, NULL);
	lv_checkbox_set_text(ui->APPtoConnect_cb_Remember, "Remember?");

	//Write style LV_CHECKBOX_PART_BG for APPtoConnect_cb_Remember
	static lv_style_t style_APPtoConnect_cb_Remember_bg;
	lv_style_reset(&style_APPtoConnect_cb_Remember_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_cb_Remember_bg
	lv_style_set_radius(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoConnect_cb_Remember_bg, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->APPtoConnect_cb_Remember, LV_CHECKBOX_PART_BG, &style_APPtoConnect_cb_Remember_bg);

	//Write style LV_CHECKBOX_PART_BULLET for APPtoConnect_cb_Remember
	static lv_style_t style_APPtoConnect_cb_Remember_bullet;
	lv_style_reset(&style_APPtoConnect_cb_Remember_bullet);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_cb_Remember_bullet
	lv_style_set_radius(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_cb_Remember_bullet, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->APPtoConnect_cb_Remember, LV_CHECKBOX_PART_BULLET, &style_APPtoConnect_cb_Remember_bullet);
	lv_obj_set_pos(ui->APPtoConnect_cb_Remember, 31, 108);

	//Write codes APPtoConnect_btn_Conn
	ui->APPtoConnect_btn_Conn = lv_btn_create(ui->APPtoConnect, NULL);

	//Write style LV_BTN_PART_MAIN for APPtoConnect_btn_Conn
	static lv_style_t style_APPtoConnect_btn_Conn_main;
	lv_style_reset(&style_APPtoConnect_btn_Conn_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_btn_Conn_main
	lv_style_set_radius(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, 240);
	lv_style_set_border_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, 150);
	lv_style_set_outline_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_APPtoConnect_btn_Conn_main, LV_STATE_DEFAULT, 100);

	//Write style state: LV_STATE_PRESSED for style_APPtoConnect_btn_Conn_main
	lv_style_set_radius(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, 10);
	lv_style_set_bg_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, 200);
	lv_style_set_border_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, 5);
	lv_style_set_border_opa(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, 255);
	lv_style_set_outline_color(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_APPtoConnect_btn_Conn_main, LV_STATE_PRESSED, 100);
	lv_obj_add_style(ui->APPtoConnect_btn_Conn, LV_BTN_PART_MAIN, &style_APPtoConnect_btn_Conn_main);
	lv_obj_set_pos(ui->APPtoConnect_btn_Conn, 59.5, 161);
	lv_obj_set_size(ui->APPtoConnect_btn_Conn, 121, 44);
	ui->APPtoConnect_btn_Conn_label = lv_label_create(ui->APPtoConnect_btn_Conn, NULL);
	lv_label_set_text(ui->APPtoConnect_btn_Conn_label, "Connect");
	lv_obj_set_style_local_text_color(ui->APPtoConnect_btn_Conn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->APPtoConnect_btn_Conn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);

	//Write codes APPtoConnect_msgbox_connOK
	ui->APPtoConnect_msgbox_connOK = lv_msgbox_create(ui->APPtoConnect, NULL);

	//Write style LV_MSGBOX_PART_BG for APPtoConnect_msgbox_connOK
	static lv_style_t style_APPtoConnect_msgbox_connOK_bg;
	lv_style_reset(&style_APPtoConnect_msgbox_connOK_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_msgbox_connOK_bg
	lv_style_set_radius(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, 3);
	lv_style_set_text_color(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, lv_color_make(0x4e, 0x4e, 0x4e));
	lv_style_set_text_font(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_line_space(&style_APPtoConnect_msgbox_connOK_bg, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->APPtoConnect_msgbox_connOK, LV_MSGBOX_PART_BG, &style_APPtoConnect_msgbox_connOK_bg);

	//Write style LV_MSGBOX_PART_BTN_BG for APPtoConnect_msgbox_connOK
	static lv_style_t style_APPtoConnect_msgbox_connOK_btn_bg;
	lv_style_reset(&style_APPtoConnect_msgbox_connOK_btn_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_msgbox_connOK_btn_bg
	lv_style_set_radius(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_msgbox_connOK_btn_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoConnect_msgbox_connOK, LV_MSGBOX_PART_BTN_BG, &style_APPtoConnect_msgbox_connOK_btn_bg);

	//Write style LV_MSGBOX_PART_BTN for APPtoConnect_msgbox_connOK
	static lv_style_t style_APPtoConnect_msgbox_connOK_btn;
	lv_style_reset(&style_APPtoConnect_msgbox_connOK_btn);

	//Write style state: LV_STATE_DEFAULT for style_APPtoConnect_msgbox_connOK_btn
	lv_style_set_radius(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, 20);
	lv_style_set_bg_color(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, lv_color_make(0x4e, 0x4e, 0x4e));
	lv_style_set_text_font(&style_APPtoConnect_msgbox_connOK_btn, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_obj_add_style(ui->APPtoConnect_msgbox_connOK, LV_MSGBOX_PART_BTN, &style_APPtoConnect_msgbox_connOK_btn);
	lv_obj_set_pos(ui->APPtoConnect_msgbox_connOK, 32, 46);
	lv_obj_set_size(ui->APPtoConnect_msgbox_connOK, 180, 0);
	lv_msgbox_set_text(ui->APPtoConnect_msgbox_connOK,"Connect successful");
	static const char * APPtoConnect_msgbox_connOK_btns[] = {"OK",""};
	lv_msgbox_add_btns(ui->APPtoConnect_msgbox_connOK, APPtoConnect_msgbox_connOK_btns);
	lv_obj_set_width(ui->APPtoConnect_msgbox_connOK,180);
	lv_obj_add_style(ui->APPtoConnect_msgbox_connOK, LV_MSGBOX_PART_BTN_BG, &style_APPtoConnect_msgbox_connOK_btn_bg);
	lv_obj_add_style(ui->APPtoConnect_msgbox_connOK, LV_MSGBOX_PART_BTN, &style_APPtoConnect_msgbox_connOK_btn);
	
	lv_obj_set_hidden(ui->APPtoConnect_msgbox_connOK, true);
	/************************** USERCODE *******************************/
	lv_obj_set_event_cb(ui->APPtoConnect, Back_APP_cb);
	lv_obj_set_event_cb(ui->APPtoConnect_btn_Conn, APPtoConnect_btn_click);
	lv_obj_set_event_cb(ui->APPtoConnect_msgbox_connOK, msgbox_connOK_cb);

}
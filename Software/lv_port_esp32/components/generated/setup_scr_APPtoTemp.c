/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_APPtoTemp(lv_ui *ui){

	//Write codes APPtoTemp
	ui->APPtoTemp = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for APPtoTemp
	static lv_style_t style_APPtoTemp_main;
	lv_style_reset(&style_APPtoTemp_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_main
	lv_style_set_bg_color(&style_APPtoTemp_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_APPtoTemp_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoTemp, LV_OBJ_PART_MAIN, &style_APPtoTemp_main);

	//Write codes APPtoTemp_bar_Tempbar
	ui->APPtoTemp_bar_Tempbar = lv_bar_create(ui->APPtoTemp, NULL);

	//Write style LV_BAR_PART_BG for APPtoTemp_bar_Tempbar
	static lv_style_t style_APPtoTemp_bar_Tempbar_bg;
	lv_style_reset(&style_APPtoTemp_bar_Tempbar_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_bar_Tempbar_bg
	lv_style_set_radius(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoTemp_bar_Tempbar_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoTemp_bar_Tempbar, LV_BAR_PART_BG, &style_APPtoTemp_bar_Tempbar_bg);

	//Write style LV_BAR_PART_INDIC for APPtoTemp_bar_Tempbar
	static lv_style_t style_APPtoTemp_bar_Tempbar_indic;
	lv_style_reset(&style_APPtoTemp_bar_Tempbar_indic);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_bar_Tempbar_indic
	lv_style_set_radius(&style_APPtoTemp_bar_Tempbar_indic, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_APPtoTemp_bar_Tempbar_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_APPtoTemp_bar_Tempbar_indic, LV_STATE_DEFAULT, lv_color_make(0x99, 0x05, 0x05));
	lv_style_set_bg_grad_dir(&style_APPtoTemp_bar_Tempbar_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoTemp_bar_Tempbar_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoTemp_bar_Tempbar, LV_BAR_PART_INDIC, &style_APPtoTemp_bar_Tempbar_indic);
	lv_obj_set_pos(ui->APPtoTemp_bar_Tempbar, 32, 50);
	lv_obj_set_size(ui->APPtoTemp_bar_Tempbar, 30, 130);
	lv_bar_set_anim_time(ui->APPtoTemp_bar_Tempbar,1000);
	lv_bar_set_value(ui->APPtoTemp_bar_Tempbar,10,LV_ANIM_ON);
	lv_bar_set_range(ui->APPtoTemp_bar_Tempbar,0,50);

	//Write codes APPtoTemp_line_bottom
	ui->APPtoTemp_line_bottom = lv_line_create(ui->APPtoTemp, NULL);

	//Write style LV_LINE_PART_MAIN for APPtoTemp_line_bottom
	static lv_style_t style_APPtoTemp_line_bottom_main;
	lv_style_reset(&style_APPtoTemp_line_bottom_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_line_bottom_main
	lv_style_set_line_color(&style_APPtoTemp_line_bottom_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_APPtoTemp_line_bottom_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->APPtoTemp_line_bottom, LV_LINE_PART_MAIN, &style_APPtoTemp_line_bottom_main);
	lv_obj_set_pos(ui->APPtoTemp_line_bottom, 31, 154);
	lv_obj_set_size(ui->APPtoTemp_line_bottom, 16, 11);
	static lv_point_t APPtoTemp_line_bottom[] ={{0,0},{15,0}};
	lv_line_set_points(ui->APPtoTemp_line_bottom,APPtoTemp_line_bottom,2);

	//Write codes APPtoTemp_line_middle
	ui->APPtoTemp_line_middle = lv_line_create(ui->APPtoTemp, NULL);

	//Write style LV_LINE_PART_MAIN for APPtoTemp_line_middle
	static lv_style_t style_APPtoTemp_line_middle_main;
	lv_style_reset(&style_APPtoTemp_line_middle_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_line_middle_main
	lv_style_set_line_color(&style_APPtoTemp_line_middle_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_APPtoTemp_line_middle_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->APPtoTemp_line_middle, LV_LINE_PART_MAIN, &style_APPtoTemp_line_middle_main);
	lv_obj_set_pos(ui->APPtoTemp_line_middle, 31, 112);
	lv_obj_set_size(ui->APPtoTemp_line_middle, 16, 11);
	static lv_point_t APPtoTemp_line_middle[] ={{0,0},{15,0}};
	lv_line_set_points(ui->APPtoTemp_line_middle,APPtoTemp_line_middle,2);

	//Write codes APPtoTemp_line_top
	ui->APPtoTemp_line_top = lv_line_create(ui->APPtoTemp, NULL);

	//Write style LV_LINE_PART_MAIN for APPtoTemp_line_top
	static lv_style_t style_APPtoTemp_line_top_main;
	lv_style_reset(&style_APPtoTemp_line_top_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_line_top_main
	lv_style_set_line_color(&style_APPtoTemp_line_top_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_APPtoTemp_line_top_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->APPtoTemp_line_top, LV_LINE_PART_MAIN, &style_APPtoTemp_line_top_main);
	lv_obj_set_pos(ui->APPtoTemp_line_top, 31, 74);
	lv_obj_set_size(ui->APPtoTemp_line_top, 16, 11);
	static lv_point_t APPtoTemp_line_top[] ={{0,0},{15,0}};
	lv_line_set_points(ui->APPtoTemp_line_top,APPtoTemp_line_top,2);

	//Write codes APPtoTemp_label_TempValue
	ui->APPtoTemp_label_TempValue = lv_label_create(ui->APPtoTemp, NULL);
	lv_label_set_text(ui->APPtoTemp_label_TempValue, "00.0");
	lv_label_set_long_mode(ui->APPtoTemp_label_TempValue, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoTemp_label_TempValue, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for APPtoTemp_label_TempValue
	static lv_style_t style_APPtoTemp_label_TempValue_main;
	lv_style_reset(&style_APPtoTemp_label_TempValue_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_label_TempValue_main
	lv_style_set_radius(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, lv_color_make(0xd1, 0x3d, 0x3d));
	lv_style_set_text_font(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_40);
	lv_style_set_text_letter_space(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_APPtoTemp_label_TempValue_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->APPtoTemp_label_TempValue, LV_LABEL_PART_MAIN, &style_APPtoTemp_label_TempValue_main);
	lv_obj_set_pos(ui->APPtoTemp_label_TempValue, 72, 90);
	lv_obj_set_size(ui->APPtoTemp_label_TempValue, 134, 0);

	//Write codes APPtoTemp_label_Celsius
	ui->APPtoTemp_label_Celsius = lv_label_create(ui->APPtoTemp, NULL);
	lv_label_set_text(ui->APPtoTemp_label_Celsius, "C");
	lv_label_set_long_mode(ui->APPtoTemp_label_Celsius, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoTemp_label_Celsius, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for APPtoTemp_label_Celsius
	static lv_style_t style_APPtoTemp_label_Celsius_main;
	lv_style_reset(&style_APPtoTemp_label_Celsius_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_label_Celsius_main
	lv_style_set_radius(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, lv_color_make(0xd1, 0x3d, 0x3d));
	lv_style_set_text_font(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_40);
	lv_style_set_text_letter_space(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_APPtoTemp_label_Celsius_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->APPtoTemp_label_Celsius, LV_LABEL_PART_MAIN, &style_APPtoTemp_label_Celsius_main);
	lv_obj_set_pos(ui->APPtoTemp_label_Celsius, 165, 63);
	lv_obj_set_size(ui->APPtoTemp_label_Celsius, 75, 0);

	// //Write codes APPtoTemp_sw_Sensor2People
	// ui->APPtoTemp_sw_Sensor2People = lv_switch_create(ui->APPtoTemp, NULL);
	// lv_obj_set_pos(ui->APPtoTemp_sw_Sensor2People, 95, 193);
	// lv_obj_set_size(ui->APPtoTemp_sw_Sensor2People, 61, 32);
	// lv_switch_set_anim_time(ui->APPtoTemp_sw_Sensor2People, 100);

	//Write codes APPtoTemp_label_Sensor
	ui->APPtoTemp_label_Sensor = lv_label_create(ui->APPtoTemp, NULL);
	lv_label_set_text(ui->APPtoTemp_label_Sensor, "People: NO");
	lv_label_set_long_mode(ui->APPtoTemp_label_Sensor, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoTemp_label_Sensor, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoTemp_label_Sensor
	static lv_style_t style_APPtoTemp_label_Sensor_main;
	lv_style_reset(&style_APPtoTemp_label_Sensor_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoTemp_label_Sensor_main
	lv_style_set_radius(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_14);
	lv_style_set_text_letter_space(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoTemp_label_Sensor_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoTemp_label_Sensor, LV_LABEL_PART_MAIN, &style_APPtoTemp_label_Sensor_main);
	lv_obj_set_pos(ui->APPtoTemp_label_Sensor, 20, 203);
	lv_obj_set_size(ui->APPtoTemp_label_Sensor, 200, 0);

	// //Write codes APPtoTemp_label_People
	// ui->APPtoTemp_label_People = lv_label_create(ui->APPtoTemp, NULL);
	// lv_label_set_text(ui->APPtoTemp_label_People, "People");
	// lv_label_set_long_mode(ui->APPtoTemp_label_People, LV_LABEL_LONG_BREAK);
	// lv_label_set_align(ui->APPtoTemp_label_People, LV_LABEL_ALIGN_CENTER);

	// //Write style LV_LABEL_PART_MAIN for APPtoTemp_label_People
	// static lv_style_t style_APPtoTemp_label_People_main;
	// lv_style_reset(&style_APPtoTemp_label_People_main);

	// //Write style state: LV_STATE_DEFAULT for style_APPtoTemp_label_People_main
	// lv_style_set_radius(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_bg_color(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	// lv_style_set_bg_opa(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_text_color(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_text_font(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	// lv_style_set_text_letter_space(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 2);
	// lv_style_set_pad_left(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_pad_right(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_pad_top(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_pad_bottom(&style_APPtoTemp_label_People_main, LV_STATE_DEFAULT, 0);
	// lv_obj_add_style(ui->APPtoTemp_label_People, LV_LABEL_PART_MAIN, &style_APPtoTemp_label_People_main);
	// lv_obj_set_pos(ui->APPtoTemp_label_People, 166, 203);
	// lv_obj_set_size(ui->APPtoTemp_label_People, 65, 0);

	/************************** USERCODE *******************************/
	lv_obj_set_event_cb(ui->APPtoTemp,Back_APP_cb);
}
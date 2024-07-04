/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


lv_chart_series_t * APPtoHR_chart_HeartBeep_0;

void setup_scr_APPtoHR(lv_ui *ui){

	//Write codes APPtoHR
	ui->APPtoHR = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for APPtoHR
	static lv_style_t style_APPtoHR_main;
	lv_style_reset(&style_APPtoHR_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_main
	lv_style_set_bg_color(&style_APPtoHR_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_APPtoHR_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoHR, LV_OBJ_PART_MAIN, &style_APPtoHR_main);

	//Write codes APPtoHR_chart_HeartBeep
	ui->APPtoHR_chart_HeartBeep = lv_chart_create(ui->APPtoHR, NULL);

	//Write style LV_CHART_PART_BG for APPtoHR_chart_HeartBeep
	static lv_style_t style_APPtoHR_chart_HeartBeep_bg;
	lv_style_reset(&style_APPtoHR_chart_HeartBeep_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_chart_HeartBeep_bg
	lv_style_set_bg_color(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_APPtoHR_chart_HeartBeep_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->APPtoHR_chart_HeartBeep, LV_CHART_PART_BG, &style_APPtoHR_chart_HeartBeep_bg);

	//Write style LV_CHART_PART_SERIES_BG for APPtoHR_chart_HeartBeep
	static lv_style_t style_APPtoHR_chart_HeartBeep_series_bg;
	lv_style_reset(&style_APPtoHR_chart_HeartBeep_series_bg);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_chart_HeartBeep_series_bg
	lv_style_set_line_color(&style_APPtoHR_chart_HeartBeep_series_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_line_width(&style_APPtoHR_chart_HeartBeep_series_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_APPtoHR_chart_HeartBeep_series_bg, LV_STATE_DEFAULT, 150);
	lv_obj_add_style(ui->APPtoHR_chart_HeartBeep, LV_CHART_PART_SERIES_BG, &style_APPtoHR_chart_HeartBeep_series_bg);
	lv_obj_set_pos(ui->APPtoHR_chart_HeartBeep, 18, 13);
	lv_obj_set_size(ui->APPtoHR_chart_HeartBeep, 205, 155);
	lv_chart_set_type(ui->APPtoHR_chart_HeartBeep,LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->APPtoHR_chart_HeartBeep,-2000,2000);
	lv_chart_set_div_line_count(ui->APPtoHR_chart_HeartBeep, 0, 0);
	lv_chart_set_point_count(ui->APPtoHR_chart_HeartBeep, 50);
	/*lv_chart_series_t * */APPtoHR_chart_HeartBeep_0 = lv_chart_add_series(ui->APPtoHR_chart_HeartBeep, lv_color_make(0xff, 0x00, 0x00));
	lv_chart_set_next(ui->APPtoHR_chart_HeartBeep, APPtoHR_chart_HeartBeep_0,0);

	//Write codes APPtoHR_label_BPM
	ui->APPtoHR_label_BPM = lv_label_create(ui->APPtoHR, NULL);
	lv_label_set_text(ui->APPtoHR_label_BPM, "BPM");
	lv_label_set_long_mode(ui->APPtoHR_label_BPM, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoHR_label_BPM, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoHR_label_BPM
	static lv_style_t style_APPtoHR_label_BPM_main;
	lv_style_reset(&style_APPtoHR_label_BPM_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_label_BPM_main
	lv_style_set_radius(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoHR_label_BPM_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoHR_label_BPM, LV_LABEL_PART_MAIN, &style_APPtoHR_label_BPM_main);
	lv_obj_set_pos(ui->APPtoHR_label_BPM, 30, 175);
	lv_obj_set_size(ui->APPtoHR_label_BPM, 65, 0);

	//Write codes APPtoHR_label_SpO2
	ui->APPtoHR_label_SpO2 = lv_label_create(ui->APPtoHR, NULL);
	lv_label_set_text(ui->APPtoHR_label_SpO2, "SpO2");
	lv_label_set_long_mode(ui->APPtoHR_label_SpO2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoHR_label_SpO2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoHR_label_SpO2
	static lv_style_t style_APPtoHR_label_SpO2_main;
	lv_style_reset(&style_APPtoHR_label_SpO2_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_label_SpO2_main
	lv_style_set_radius(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoHR_label_SpO2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoHR_label_SpO2, LV_LABEL_PART_MAIN, &style_APPtoHR_label_SpO2_main);
	lv_obj_set_pos(ui->APPtoHR_label_SpO2, 143, 175);
	lv_obj_set_size(ui->APPtoHR_label_SpO2, 65, 0);

	//Write codes APPtoHR_label_NumBPM
	ui->APPtoHR_label_NumBPM = lv_label_create(ui->APPtoHR, NULL);
	lv_label_set_text(ui->APPtoHR_label_NumBPM, "00.0");
	lv_label_set_long_mode(ui->APPtoHR_label_NumBPM, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoHR_label_NumBPM, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoHR_label_NumBPM
	static lv_style_t style_APPtoHR_label_NumBPM_main;
	lv_style_reset(&style_APPtoHR_label_NumBPM_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_label_NumBPM_main
	lv_style_set_radius(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, lv_color_make(0xd1, 0x3d, 0x3d));
	lv_style_set_text_font(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_APPtoHR_label_NumBPM_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->APPtoHR_label_NumBPM, LV_LABEL_PART_MAIN, &style_APPtoHR_label_NumBPM_main);
	lv_obj_set_pos(ui->APPtoHR_label_NumBPM, 19, 190);
	lv_obj_set_size(ui->APPtoHR_label_NumBPM, 85, 0);

	//Write codes APPtoHR_label_NumSpO2
	ui->APPtoHR_label_NumSpO2 = lv_label_create(ui->APPtoHR, NULL);
	lv_label_set_text(ui->APPtoHR_label_NumSpO2, "00.0");
	lv_label_set_long_mode(ui->APPtoHR_label_NumSpO2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoHR_label_NumSpO2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoHR_label_NumSpO2
	static lv_style_t style_APPtoHR_label_NumSpO2_main;
	lv_style_reset(&style_APPtoHR_label_NumSpO2_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoHR_label_NumSpO2_main
	lv_style_set_radius(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x85, 0xd1));
	lv_style_set_text_font(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_APPtoHR_label_NumSpO2_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->APPtoHR_label_NumSpO2, LV_LABEL_PART_MAIN, &style_APPtoHR_label_NumSpO2_main);
	lv_obj_set_pos(ui->APPtoHR_label_NumSpO2, 135, 190);
	lv_obj_set_size(ui->APPtoHR_label_NumSpO2, 85, 0);

	/************************** USERCODE *******************************/
	max30102_set_mode(&max30102, MAX30102_SHDN_OFF);
	lv_obj_set_event_cb(ui->APPtoHR,Back_APP_cb);
}
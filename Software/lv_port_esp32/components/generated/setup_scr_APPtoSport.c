/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_APPtoSport(lv_ui *ui){

	//Write codes APPtoSport
	ui->APPtoSport = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for APPtoSport
	static lv_style_t style_APPtoSport_main;
	lv_style_reset(&style_APPtoSport_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoSport_main
	lv_style_set_bg_color(&style_APPtoSport_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_APPtoSport_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APPtoSport, LV_OBJ_PART_MAIN, &style_APPtoSport_main);

	//Write codes APPtoSport_lmeter_steps
	ui->APPtoSport_lmeter_steps = lv_linemeter_create(ui->APPtoSport, NULL);

	//Write style LV_LINEMETER_PART_MAIN for APPtoSport_lmeter_steps
	static lv_style_t style_APPtoSport_lmeter_steps_main;
	lv_style_reset(&style_APPtoSport_lmeter_steps_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoSport_lmeter_steps_main
	lv_style_set_radius(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 200);
	lv_style_set_bg_color(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 5);
	lv_style_set_line_color(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0x4b, 0x06));
	lv_style_set_line_width(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 4);
	lv_style_set_line_opa(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 255);
	lv_style_set_scale_grad_color(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, lv_color_make(0x4d, 0xff, 0x61));
	lv_style_set_scale_end_color(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, lv_color_make(0xa8, 0xa8, 0xa8));
	lv_style_set_scale_width(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 15);
	lv_style_set_scale_end_line_width(&style_APPtoSport_lmeter_steps_main, LV_STATE_DEFAULT, 4);
	lv_obj_add_style(ui->APPtoSport_lmeter_steps, LV_LINEMETER_PART_MAIN, &style_APPtoSport_lmeter_steps_main);
	lv_obj_set_pos(ui->APPtoSport_lmeter_steps, 47, 25);
	lv_obj_set_size(ui->APPtoSport_lmeter_steps, 146, 146);
	lv_linemeter_set_scale(ui->APPtoSport_lmeter_steps, 250, 25);
	lv_linemeter_set_range(ui->APPtoSport_lmeter_steps, 0, 100);
	lv_linemeter_set_value(ui->APPtoSport_lmeter_steps, 50);
	lv_linemeter_set_angle_offset(ui->APPtoSport_lmeter_steps, 0);

	//Write codes APPtoSport_label_Steps
	ui->APPtoSport_label_Steps = lv_label_create(ui->APPtoSport, NULL);
	lv_label_set_text(ui->APPtoSport_label_Steps, "Steps");
	lv_label_set_long_mode(ui->APPtoSport_label_Steps, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoSport_label_Steps, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoSport_label_Steps
	static lv_style_t style_APPtoSport_label_Steps_main;
	lv_style_reset(&style_APPtoSport_label_Steps_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoSport_label_Steps_main
	lv_style_set_radius(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoSport_label_Steps_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoSport_label_Steps, LV_LABEL_PART_MAIN, &style_APPtoSport_label_Steps_main);
	lv_obj_set_pos(ui->APPtoSport_label_Steps, 87.5, 142);
	lv_obj_set_size(ui->APPtoSport_label_Steps, 65, 0);

	//Write codes APPtoSport_label_NumSteps
	ui->APPtoSport_label_NumSteps = lv_label_create(ui->APPtoSport, NULL);
	lv_label_set_text(ui->APPtoSport_label_NumSteps, "00000");
	lv_label_set_long_mode(ui->APPtoSport_label_NumSteps, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoSport_label_NumSteps, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoSport_label_NumSteps
	static lv_style_t style_APPtoSport_label_NumSteps_main;
	lv_style_reset(&style_APPtoSport_label_NumSteps_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoSport_label_NumSteps_main
	lv_style_set_radius(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, lv_color_make(0x02, 0x92, 0x0c));
	lv_style_set_text_font(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_APPtoSport_label_NumSteps_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->APPtoSport_label_NumSteps, LV_LABEL_PART_MAIN, &style_APPtoSport_label_NumSteps_main);
	lv_obj_set_pos(ui->APPtoSport_label_NumSteps, 60, 76);
	lv_obj_set_size(ui->APPtoSport_label_NumSteps, 122, 0);

	// //Write codes APPtoSport_sw_Fall
	// ui->APPtoSport_sw_Fall = lv_switch_create(ui->APPtoSport, NULL);
	// lv_obj_set_pos(ui->APPtoSport_sw_Fall, 17, 173);
	// lv_obj_set_size(ui->APPtoSport_sw_Fall, 52, 24);
	// lv_switch_set_anim_time(ui->APPtoSport_sw_Fall, 100);

	//Write codes APPtoSport_label_Fall
	ui->APPtoSport_label_Fall = lv_label_create(ui->APPtoSport, NULL);
	lv_label_set_text(ui->APPtoSport_label_Fall, "Distance:0.0 m");
	lv_label_set_long_mode(ui->APPtoSport_label_Fall, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APPtoSport_label_Fall, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APPtoSport_label_Fall
	static lv_style_t style_APPtoSport_label_Fall_main;
	lv_style_reset(&style_APPtoSport_label_Fall_main);

	//Write style state: LV_STATE_DEFAULT for style_APPtoSport_label_Fall_main
	lv_style_set_radius(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APPtoSport_label_Fall_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APPtoSport_label_Fall, LV_LABEL_PART_MAIN, &style_APPtoSport_label_Fall_main);
	lv_obj_set_pos(ui->APPtoSport_label_Fall, 10, 206);
	lv_obj_set_size(ui->APPtoSport_label_Fall, 220, 0);

	// //Write codes APPtoSport_label_DetectRes
	// ui->APPtoSport_label_DetectRes = lv_label_create(ui->APPtoSport, NULL);
	// lv_label_set_text(ui->APPtoSport_label_DetectRes, "Normal");
	// lv_label_set_long_mode(ui->APPtoSport_label_DetectRes, LV_LABEL_LONG_BREAK);
	// lv_label_set_align(ui->APPtoSport_label_DetectRes, LV_LABEL_ALIGN_CENTER);

	// //Write style LV_LABEL_PART_MAIN for APPtoSport_label_DetectRes
	// static lv_style_t style_APPtoSport_label_DetectRes_main;
	// lv_style_reset(&style_APPtoSport_label_DetectRes_main);

	// //Write style state: LV_STATE_DEFAULT for style_APPtoSport_label_DetectRes_main
	// lv_style_set_radius(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_bg_color(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	// lv_style_set_bg_opa(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_text_color(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x91, 0xc2));
	// lv_style_set_text_font(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	// lv_style_set_text_letter_space(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 3);
	// lv_style_set_pad_left(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_pad_right(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_pad_top(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_pad_bottom(&style_APPtoSport_label_DetectRes_main, LV_STATE_DEFAULT, 0);
	// lv_obj_add_style(ui->APPtoSport_label_DetectRes, LV_LABEL_PART_MAIN, &style_APPtoSport_label_DetectRes_main);
	// lv_obj_set_pos(ui->APPtoSport_label_DetectRes, 101, 190);
	// lv_obj_set_size(ui->APPtoSport_label_DetectRes, 110, 0);

	/************************** USERCODE *******************************/
	lv_obj_set_event_cb(ui->APPtoSport,Back_APP_cb);
}
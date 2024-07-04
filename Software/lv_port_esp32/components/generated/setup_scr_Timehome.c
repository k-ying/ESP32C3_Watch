/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
extern uint8_t time_sync_flag;

void setup_scr_Timehome(lv_ui *ui){

	//Write codes Timehome
	ui->Timehome = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for Timehome
	static lv_style_t style_Timehome_main;
	lv_style_reset(&style_Timehome_main);

	//Write style state: LV_STATE_DEFAULT for style_Timehome_main
	lv_style_set_bg_color(&style_Timehome_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_Timehome_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Timehome, LV_OBJ_PART_MAIN, &style_Timehome_main);

	//Write codes Timehome_TIme_Hour
	ui->Timehome_TIme_Hour = lv_label_create(ui->Timehome, NULL);
	lv_label_set_text(ui->Timehome_TIme_Hour, "00");
	lv_label_set_long_mode(ui->Timehome_TIme_Hour, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Timehome_TIme_Hour, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Timehome_TIme_Hour
	static lv_style_t style_Timehome_TIme_Hour_main;
	lv_style_reset(&style_Timehome_TIme_Hour_main);

	//Write style state: LV_STATE_DEFAULT for style_Timehome_TIme_Hour_main
	lv_style_set_radius(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, lv_color_make(0xd1, 0x3d, 0x3d));
	lv_style_set_text_font(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_40);
	lv_style_set_text_letter_space(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_Timehome_TIme_Hour_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->Timehome_TIme_Hour, LV_LABEL_PART_MAIN, &style_Timehome_TIme_Hour_main);
	lv_obj_set_pos(ui->Timehome_TIme_Hour, 37, 70);
	lv_obj_set_size(ui->Timehome_TIme_Hour, 83, 0);

	//Write codes Timehome_Time_Min
	ui->Timehome_Time_Min = lv_label_create(ui->Timehome, NULL);
	lv_label_set_text(ui->Timehome_Time_Min, "00");
	lv_label_set_long_mode(ui->Timehome_Time_Min, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Timehome_Time_Min, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Timehome_Time_Min
	static lv_style_t style_Timehome_Time_Min_main;
	lv_style_reset(&style_Timehome_Time_Min_main);

	//Write style state: LV_STATE_DEFAULT for style_Timehome_Time_Min_main
	lv_style_set_radius(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_40);
	lv_style_set_text_letter_space(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_Timehome_Time_Min_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->Timehome_Time_Min, LV_LABEL_PART_MAIN, &style_Timehome_Time_Min_main);
	lv_obj_set_pos(ui->Timehome_Time_Min, 122, 70);
	lv_obj_set_size(ui->Timehome_Time_Min, 83, 0);

	//Write codes Timehome_Time_Dot
	ui->Timehome_Time_Dot = lv_label_create(ui->Timehome, NULL);
	lv_label_set_text(ui->Timehome_Time_Dot, ":");
	lv_label_set_long_mode(ui->Timehome_Time_Dot, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Timehome_Time_Dot, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Timehome_Time_Dot
	static lv_style_t style_Timehome_Time_Dot_main;
	lv_style_reset(&style_Timehome_Time_Dot_main);

	//Write style state: LV_STATE_DEFAULT for style_Timehome_Time_Dot_main
	lv_style_set_radius(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_40);
	lv_style_set_text_letter_space(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_right(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_top(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 10);
	lv_style_set_pad_bottom(&style_Timehome_Time_Dot_main, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->Timehome_Time_Dot, LV_LABEL_PART_MAIN, &style_Timehome_Time_Dot_main);
	lv_obj_set_pos(ui->Timehome_Time_Dot, 80, 68);
	lv_obj_set_size(ui->Timehome_Time_Dot, 83, 0);

	//Write codes Timehome_Time_Year
	ui->Timehome_Time_Year = lv_label_create(ui->Timehome, NULL);
	lv_label_set_text(ui->Timehome_Time_Year, "2022-00-00");
	lv_label_set_long_mode(ui->Timehome_Time_Year, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Timehome_Time_Year, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Timehome_Time_Year
	static lv_style_t style_Timehome_Time_Year_main;
	lv_style_reset(&style_Timehome_Time_Year_main);

	//Write style state: LV_STATE_DEFAULT for style_Timehome_Time_Year_main
	lv_style_set_radius(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 15);
	lv_style_set_pad_right(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_Timehome_Time_Year_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->Timehome_Time_Year, LV_LABEL_PART_MAIN, &style_Timehome_Time_Year_main);
	lv_obj_set_pos(ui->Timehome_Time_Year, 20, 140);
	lv_obj_set_size(ui->Timehome_Time_Year, 200, 0);

	// //Write codes Timehome_Time_Line1
	// ui->Timehome_Time_Line1 = lv_label_create(ui->Timehome, NULL);
	// lv_label_set_text(ui->Timehome_Time_Line1, "/");
	// lv_label_set_long_mode(ui->Timehome_Time_Line1, LV_LABEL_LONG_BREAK);
	// lv_label_set_align(ui->Timehome_Time_Line1, LV_LABEL_ALIGN_CENTER);

	// //Write style LV_LABEL_PART_MAIN for Timehome_Time_Line1
	// static lv_style_t style_Timehome_Time_Line1_main;
	// lv_style_reset(&style_Timehome_Time_Line1_main);

	// //Write style state: LV_STATE_DEFAULT for style_Timehome_Time_Line1_main
	// lv_style_set_radius(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_bg_color(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	// lv_style_set_bg_opa(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_text_color(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_text_font(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	// lv_style_set_text_letter_space(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 3);
	// lv_style_set_pad_left(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 15);
	// lv_style_set_pad_right(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_top(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_bottom(&style_Timehome_Time_Line1_main, LV_STATE_DEFAULT, 5);
	// lv_obj_add_style(ui->Timehome_Time_Line1, LV_LABEL_PART_MAIN, &style_Timehome_Time_Line1_main);
	// lv_obj_set_pos(ui->Timehome_Time_Line1, 81, 158);
	// lv_obj_set_size(ui->Timehome_Time_Line1, 32, 0);

	// //Write codes Timehome_TIme_Mon
	// ui->Timehome_TIme_Mon = lv_label_create(ui->Timehome, NULL);
	// lv_label_set_text(ui->Timehome_TIme_Mon, "00");
	// lv_label_set_long_mode(ui->Timehome_TIme_Mon, LV_LABEL_LONG_BREAK);
	// lv_label_set_align(ui->Timehome_TIme_Mon, LV_LABEL_ALIGN_CENTER);

	// //Write style LV_LABEL_PART_MAIN for Timehome_TIme_Mon
	// static lv_style_t style_Timehome_TIme_Mon_main;
	// lv_style_reset(&style_Timehome_TIme_Mon_main);

	// //Write style state: LV_STATE_DEFAULT for style_Timehome_TIme_Mon_main
	// lv_style_set_radius(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_bg_color(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	// lv_style_set_bg_opa(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_text_color(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_text_font(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	// lv_style_set_text_letter_space(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 3);
	// lv_style_set_pad_left(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 15);
	// lv_style_set_pad_right(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_top(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_bottom(&style_Timehome_TIme_Mon_main, LV_STATE_DEFAULT, 5);
	// lv_obj_add_style(ui->Timehome_TIme_Mon, LV_LABEL_PART_MAIN, &style_Timehome_TIme_Mon_main);
	// lv_obj_set_pos(ui->Timehome_TIme_Mon, 91, 157);
	// lv_obj_set_size(ui->Timehome_TIme_Mon, 66, 0);

	// //Write codes Timehome_Time_Line2
	// ui->Timehome_Time_Line2 = lv_label_create(ui->Timehome, NULL);
	// lv_label_set_text(ui->Timehome_Time_Line2, "/");
	// lv_label_set_long_mode(ui->Timehome_Time_Line2, LV_LABEL_LONG_BREAK);
	// lv_label_set_align(ui->Timehome_Time_Line2, LV_LABEL_ALIGN_CENTER);

	// //Write style LV_LABEL_PART_MAIN for Timehome_Time_Line2
	// static lv_style_t style_Timehome_Time_Line2_main;
	// lv_style_reset(&style_Timehome_Time_Line2_main);

	// //Write style state: LV_STATE_DEFAULT for style_Timehome_Time_Line2_main
	// lv_style_set_radius(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_bg_color(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	// lv_style_set_bg_opa(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_text_color(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_text_font(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	// lv_style_set_text_letter_space(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 3);
	// lv_style_set_pad_left(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 15);
	// lv_style_set_pad_right(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_top(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_bottom(&style_Timehome_Time_Line2_main, LV_STATE_DEFAULT, 5);
	// lv_obj_add_style(ui->Timehome_Time_Line2, LV_LABEL_PART_MAIN, &style_Timehome_Time_Line2_main);
	// lv_obj_set_pos(ui->Timehome_Time_Line2, 136, 158);
	// lv_obj_set_size(ui->Timehome_Time_Line2, 32, 0);

	// //Write codes Timehome_Time_Sec
	// ui->Timehome_Time_Sec = lv_label_create(ui->Timehome, NULL);
	// lv_label_set_text(ui->Timehome_Time_Sec, "00");
	// lv_label_set_long_mode(ui->Timehome_Time_Sec, LV_LABEL_LONG_BREAK);
	// lv_label_set_align(ui->Timehome_Time_Sec, LV_LABEL_ALIGN_CENTER);

	// //Write style LV_LABEL_PART_MAIN for Timehome_Time_Sec
	// static lv_style_t style_Timehome_Time_Sec_main;
	// lv_style_reset(&style_Timehome_Time_Sec_main);

	// //Write style state: LV_STATE_DEFAULT for style_Timehome_Time_Sec_main
	// lv_style_set_radius(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_bg_color(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	// lv_style_set_bg_opa(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 0);
	// lv_style_set_text_color(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_text_font(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	// lv_style_set_text_letter_space(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 3);
	// lv_style_set_pad_left(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 15);
	// lv_style_set_pad_right(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_top(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 5);
	// lv_style_set_pad_bottom(&style_Timehome_Time_Sec_main, LV_STATE_DEFAULT, 5);
	// lv_obj_add_style(ui->Timehome_Time_Sec, LV_LABEL_PART_MAIN, &style_Timehome_Time_Sec_main);
	// lv_obj_set_pos(ui->Timehome_Time_Sec, 148, 157);
	// lv_obj_set_size(ui->Timehome_Time_Sec, 66, 0);

/**************************************** USER CODE ******************************************/
	lv_obj_set_event_cb(ui->Timehome, To_APP_cb);
	time_sync_flag=1;
}
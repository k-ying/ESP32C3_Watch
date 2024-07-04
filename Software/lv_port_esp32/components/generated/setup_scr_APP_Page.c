/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

extern bool scrloading;

void setup_scr_APP_Page(lv_ui *ui){

	//Write codes APP_Page
	ui->APP_Page = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for APP_Page
	static lv_style_t style_APP_Page_main;
	lv_style_reset(&style_APP_Page_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_main
	lv_style_set_bg_color(&style_APP_Page_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_APP_Page_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APP_Page, LV_OBJ_PART_MAIN, &style_APP_Page_main);

	//Write codes APP_Page_APP_Titile
	ui->APP_Page_APP_Titile = lv_label_create(ui->APP_Page, NULL);
	lv_label_set_text(ui->APP_Page_APP_Titile, "C3 Watch APP");
	lv_label_set_long_mode(ui->APP_Page_APP_Titile, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APP_Page_APP_Titile, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APP_Page_APP_Titile
	static lv_style_t style_APP_Page_APP_Titile_main;
	lv_style_reset(&style_APP_Page_APP_Titile_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_APP_Titile_main
	lv_style_set_radius(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_14);
	lv_style_set_text_letter_space(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APP_Page_APP_Titile_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_APP_Titile, LV_LABEL_PART_MAIN, &style_APP_Page_APP_Titile_main);
	lv_obj_set_pos(ui->APP_Page_APP_Titile, 55, 12);
	lv_obj_set_size(ui->APP_Page_APP_Titile, 134, 0);

	//Write codes APP_Page_BTN_BackTime
	ui->APP_Page_BTN_BackTime = lv_btn_create(ui->APP_Page, NULL);

	//Write style LV_BTN_PART_MAIN for APP_Page_BTN_BackTime
	static lv_style_t style_APP_Page_BTN_BackTime_main;
	lv_style_reset(&style_APP_Page_BTN_BackTime_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_BTN_BackTime_main
	lv_style_set_radius(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_outline_opa(&style_APP_Page_BTN_BackTime_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_BTN_BackTime, LV_BTN_PART_MAIN, &style_APP_Page_BTN_BackTime_main);
	lv_obj_set_pos(ui->APP_Page_BTN_BackTime, 0, 0);
	lv_obj_set_size(ui->APP_Page_BTN_BackTime, 240, 30);
	ui->APP_Page_BTN_BackTime_label = lv_label_create(ui->APP_Page_BTN_BackTime, NULL);
	lv_label_set_text(ui->APP_Page_BTN_BackTime_label, "");
	lv_obj_set_style_local_text_color(ui->APP_Page_BTN_BackTime_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));

	//Write codes APP_Page_APP_List
	ui->APP_Page_APP_List = lv_tileview_create(ui->APP_Page, NULL);
	static lv_point_t APP_Page_APP_List_valid_pos[] = {{0, 0},{1, 0},{2, 0},{3, 0},{4, 0},};
	lv_tileview_set_valid_positions(ui->APP_Page_APP_List, APP_Page_APP_List_valid_pos, 5);
	lv_tileview_set_edge_flash(ui->APP_Page_APP_List, true);
	lv_tileview_set_anim_time(ui->APP_Page_APP_List, 500);

	//Write style LV_TILEVIEW_PART_BG for APP_Page_APP_List
	static lv_style_t style_APP_Page_APP_List_bg;
	lv_style_reset(&style_APP_Page_APP_List_bg);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_APP_List_bg
	lv_style_set_radius(&style_APP_Page_APP_List_bg, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_APP_Page_APP_List_bg, LV_STATE_DEFAULT, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_color(&style_APP_Page_APP_List_bg, LV_STATE_DEFAULT, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_APP_Page_APP_List_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_APP_List_bg, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APP_Page_APP_List, LV_TILEVIEW_PART_BG, &style_APP_Page_APP_List_bg);

	//Write style LV_TILEVIEW_PART_EDGE_FLASH for APP_Page_APP_List
	static lv_style_t style_APP_Page_APP_List_edge_flash;
	lv_style_reset(&style_APP_Page_APP_List_edge_flash);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_APP_List_edge_flash
	lv_style_set_radius(&style_APP_Page_APP_List_edge_flash, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_APP_List_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_grad_color(&style_APP_Page_APP_List_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_grad_dir(&style_APP_Page_APP_List_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_APP_List_edge_flash, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APP_Page_APP_List, LV_TILEVIEW_PART_EDGE_FLASH, &style_APP_Page_APP_List_edge_flash);

	//Write style LV_TILEVIEW_PART_SCROLLBAR for APP_Page_APP_List
	static lv_style_t style_APP_Page_APP_List_scrollbar;
	lv_style_reset(&style_APP_Page_APP_List_scrollbar);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_APP_List_scrollbar
	lv_style_set_radius(&style_APP_Page_APP_List_scrollbar, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_APP_List_scrollbar, LV_STATE_DEFAULT, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_grad_color(&style_APP_Page_APP_List_scrollbar, LV_STATE_DEFAULT, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_grad_dir(&style_APP_Page_APP_List_scrollbar, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_APP_List_scrollbar, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APP_Page_APP_List, LV_TILEVIEW_PART_SCROLLBAR, &style_APP_Page_APP_List_scrollbar);
	lv_obj_set_pos(ui->APP_Page_APP_List, 4, 36);
	lv_obj_set_size(ui->APP_Page_APP_List, 233, 200);

	//Write codes APP_Page_APP_List_APP_HeartRate
	ui->APP_Page_APP_List_APP_HeartRate = lv_obj_create(ui->APP_Page_APP_List, NULL);
	lv_obj_set_style_local_bg_opa(ui->APP_Page_APP_List_APP_HeartRate, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(ui->APP_Page_APP_List_APP_HeartRate, LV_OBJ_PART_MAIN, LV_STATE_FOCUSED, 0);
	lv_obj_set_pos(ui->APP_Page_APP_List_APP_HeartRate, 0*233, 0);
	lv_obj_set_size(ui->APP_Page_APP_List_APP_HeartRate, 233, 200);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_APP_List_APP_HeartRate);

	//Write codes APP_Page_img_HeartRate
	ui->APP_Page_img_HeartRate = lv_img_create(ui->APP_Page_APP_List_APP_HeartRate, NULL);
	lv_obj_set_pos(ui->APP_Page_img_HeartRate, 56, 34);
	lv_obj_set_size(ui->APP_Page_img_HeartRate, 120, 120);
	lv_obj_set_click(ui->APP_Page_img_HeartRate, true);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_img_HeartRate);
	lv_img_set_src(ui->APP_Page_img_HeartRate,&_HeartBeat_alpha_120x120);
	lv_img_set_pivot(ui->APP_Page_img_HeartRate, 0,0);
	lv_img_set_angle(ui->APP_Page_img_HeartRate, 0);

	//Write codes APP_Page_btn_HeartRate
	ui->APP_Page_btn_HeartRate = lv_btn_create(ui->APP_Page_APP_List_APP_HeartRate, NULL);

	//Write style LV_BTN_PART_MAIN for APP_Page_btn_HeartRate
	static lv_style_t style_APP_Page_btn_HeartRate_main;
	lv_style_reset(&style_APP_Page_btn_HeartRate_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_btn_HeartRate_main
	lv_style_set_radius(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_outline_opa(&style_APP_Page_btn_HeartRate_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_btn_HeartRate, LV_BTN_PART_MAIN, &style_APP_Page_btn_HeartRate_main);
	lv_obj_set_pos(ui->APP_Page_btn_HeartRate, 56, 34);
	lv_obj_set_size(ui->APP_Page_btn_HeartRate, 120, 120);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_btn_HeartRate);
	ui->APP_Page_btn_HeartRate_label = lv_label_create(ui->APP_Page_btn_HeartRate, NULL);
	lv_label_set_text(ui->APP_Page_btn_HeartRate_label, "");
	lv_obj_set_style_local_text_color(ui->APP_Page_btn_HeartRate_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));

	//Write codes APP_Page_APP_List_APP_Sport
	ui->APP_Page_APP_List_APP_Sport = lv_obj_create(ui->APP_Page_APP_List, NULL);
	lv_obj_set_style_local_bg_opa(ui->APP_Page_APP_List_APP_Sport, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(ui->APP_Page_APP_List_APP_Sport, LV_OBJ_PART_MAIN, LV_STATE_FOCUSED, 0);
	lv_obj_set_pos(ui->APP_Page_APP_List_APP_Sport, 1*233, 0);
	lv_obj_set_size(ui->APP_Page_APP_List_APP_Sport, 233, 200);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_APP_List_APP_Sport);

	//Write codes APP_Page_img_Sport
	ui->APP_Page_img_Sport = lv_img_create(ui->APP_Page_APP_List_APP_Sport, NULL);
	lv_obj_set_pos(ui->APP_Page_img_Sport, 56, 34);
	lv_obj_set_size(ui->APP_Page_img_Sport, 120, 120);
	lv_obj_set_click(ui->APP_Page_img_Sport, true);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_img_Sport);
	lv_img_set_src(ui->APP_Page_img_Sport,&_run_alpha_120x120);
	lv_img_set_pivot(ui->APP_Page_img_Sport, 0,0);
	lv_img_set_angle(ui->APP_Page_img_Sport, 0);

	//Write codes APP_Page_btn_Sport
	ui->APP_Page_btn_Sport = lv_btn_create(ui->APP_Page_APP_List_APP_Sport, NULL);

	//Write style LV_BTN_PART_MAIN for APP_Page_btn_Sport
	static lv_style_t style_APP_Page_btn_Sport_main;
	lv_style_reset(&style_APP_Page_btn_Sport_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_btn_Sport_main
	lv_style_set_radius(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_outline_opa(&style_APP_Page_btn_Sport_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_btn_Sport, LV_BTN_PART_MAIN, &style_APP_Page_btn_Sport_main);
	lv_obj_set_pos(ui->APP_Page_btn_Sport, 56, 34);
	lv_obj_set_size(ui->APP_Page_btn_Sport, 120, 120);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_btn_Sport);
	ui->APP_Page_btn_Sport_label = lv_label_create(ui->APP_Page_btn_Sport, NULL);
	lv_label_set_text(ui->APP_Page_btn_Sport_label, "");
	lv_obj_set_style_local_text_color(ui->APP_Page_btn_Sport_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));

	//Write codes APP_Page_APP_List_APP_Temp
	ui->APP_Page_APP_List_APP_Temp = lv_obj_create(ui->APP_Page_APP_List, NULL);
	lv_obj_set_style_local_bg_opa(ui->APP_Page_APP_List_APP_Temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(ui->APP_Page_APP_List_APP_Temp, LV_OBJ_PART_MAIN, LV_STATE_FOCUSED, 0);
	lv_obj_set_pos(ui->APP_Page_APP_List_APP_Temp, 2*233, 0);
	lv_obj_set_size(ui->APP_Page_APP_List_APP_Temp, 233, 200);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_APP_List_APP_Temp);

	//Write codes APP_Page_img_Temp
	ui->APP_Page_img_Temp = lv_img_create(ui->APP_Page_APP_List_APP_Temp, NULL);
	lv_obj_set_pos(ui->APP_Page_img_Temp, 56, 34);
	lv_obj_set_size(ui->APP_Page_img_Temp, 120, 120);
	lv_obj_set_click(ui->APP_Page_img_Temp, true);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_img_Temp);
	lv_img_set_src(ui->APP_Page_img_Temp,&_temperature_alpha_120x120);
	lv_img_set_pivot(ui->APP_Page_img_Temp, 0,0);
	lv_img_set_angle(ui->APP_Page_img_Temp, 0);

	//Write codes APP_Page_btn_Temp
	ui->APP_Page_btn_Temp = lv_btn_create(ui->APP_Page_APP_List_APP_Temp, NULL);

	//Write style LV_BTN_PART_MAIN for APP_Page_btn_Temp
	static lv_style_t style_APP_Page_btn_Temp_main;
	lv_style_reset(&style_APP_Page_btn_Temp_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_btn_Temp_main
	lv_style_set_radius(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_outline_opa(&style_APP_Page_btn_Temp_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_btn_Temp, LV_BTN_PART_MAIN, &style_APP_Page_btn_Temp_main);
	lv_obj_set_pos(ui->APP_Page_btn_Temp, 56, 34);
	lv_obj_set_size(ui->APP_Page_btn_Temp, 120, 120);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_btn_Temp);
	ui->APP_Page_btn_Temp_label = lv_label_create(ui->APP_Page_btn_Temp, NULL);
	lv_label_set_text(ui->APP_Page_btn_Temp_label, "");
	lv_obj_set_style_local_text_color(ui->APP_Page_btn_Temp_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));

	//Write codes APP_Page_APP_List_APP_Connect
	ui->APP_Page_APP_List_APP_Connect = lv_obj_create(ui->APP_Page_APP_List, NULL);
	lv_obj_set_style_local_bg_opa(ui->APP_Page_APP_List_APP_Connect, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(ui->APP_Page_APP_List_APP_Connect, LV_OBJ_PART_MAIN, LV_STATE_FOCUSED, 0);
	lv_obj_set_pos(ui->APP_Page_APP_List_APP_Connect, 3*233, 0);
	lv_obj_set_size(ui->APP_Page_APP_List_APP_Connect, 233, 200);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_APP_List_APP_Connect);

	//Write codes APP_Page_img_Connect
	ui->APP_Page_img_Connect = lv_img_create(ui->APP_Page_APP_List_APP_Connect, NULL);

	//Write style LV_IMG_PART_MAIN for APP_Page_img_Connect
	static lv_style_t style_APP_Page_img_Connect_main;
	lv_style_reset(&style_APP_Page_img_Connect_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_img_Connect_main
	lv_style_set_image_recolor(&style_APP_Page_img_Connect_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_APP_Page_img_Connect_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_APP_Page_img_Connect_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->APP_Page_img_Connect, LV_IMG_PART_MAIN, &style_APP_Page_img_Connect_main);
	lv_obj_set_pos(ui->APP_Page_img_Connect, 56, 34);
	lv_obj_set_size(ui->APP_Page_img_Connect, 120, 120);
	lv_obj_set_click(ui->APP_Page_img_Connect, true);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_img_Connect);
	lv_img_set_src(ui->APP_Page_img_Connect,&_wifi_alpha_120x120);
	lv_img_set_pivot(ui->APP_Page_img_Connect, 0,0);
	lv_img_set_angle(ui->APP_Page_img_Connect, 0);

	//Write codes APP_Page_btn_Connect
	ui->APP_Page_btn_Connect = lv_btn_create(ui->APP_Page_APP_List_APP_Connect, NULL);

	//Write style LV_BTN_PART_MAIN for APP_Page_btn_Connect
	static lv_style_t style_APP_Page_btn_Connect_main;
	lv_style_reset(&style_APP_Page_btn_Connect_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_btn_Connect_main
	lv_style_set_radius(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_outline_opa(&style_APP_Page_btn_Connect_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_btn_Connect, LV_BTN_PART_MAIN, &style_APP_Page_btn_Connect_main);
	lv_obj_set_pos(ui->APP_Page_btn_Connect, 56, 34);
	lv_obj_set_size(ui->APP_Page_btn_Connect, 120, 120);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_btn_Connect);
	ui->APP_Page_btn_Connect_label = lv_label_create(ui->APP_Page_btn_Connect, NULL);
	lv_label_set_text(ui->APP_Page_btn_Connect_label, "");
	lv_obj_set_style_local_text_color(ui->APP_Page_btn_Connect_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));

	//Write codes APP_Page_APP_List_APP_Info
	ui->APP_Page_APP_List_APP_Info = lv_obj_create(ui->APP_Page_APP_List, NULL);
	lv_obj_set_style_local_bg_opa(ui->APP_Page_APP_List_APP_Info, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(ui->APP_Page_APP_List_APP_Info, LV_OBJ_PART_MAIN, LV_STATE_FOCUSED, 0);
	lv_obj_set_pos(ui->APP_Page_APP_List_APP_Info, 4*233, 0);
	lv_obj_set_size(ui->APP_Page_APP_List_APP_Info, 233, 200);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_APP_List_APP_Info);

	//Write codes APP_Page_label_InfoVer
	ui->APP_Page_label_InfoVer = lv_label_create(ui->APP_Page_APP_List_APP_Info, NULL);
	lv_label_set_text(ui->APP_Page_label_InfoVer, "SysVer : 0.0.1");
	lv_label_set_long_mode(ui->APP_Page_label_InfoVer, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APP_Page_label_InfoVer, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APP_Page_label_InfoVer
	static lv_style_t style_APP_Page_label_InfoVer_main;
	lv_style_reset(&style_APP_Page_label_InfoVer_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_label_InfoVer_main
	lv_style_set_radius(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APP_Page_label_InfoVer_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_label_InfoVer, LV_LABEL_PART_MAIN, &style_APP_Page_label_InfoVer_main);
	lv_obj_set_pos(ui->APP_Page_label_InfoVer, 27, 40);
	lv_obj_set_size(ui->APP_Page_label_InfoVer, 183, 0);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_label_InfoVer);

	//Write codes APP_Page_label_InfoName
	ui->APP_Page_label_InfoName = lv_label_create(ui->APP_Page_APP_List_APP_Info, NULL);
	lv_label_set_text(ui->APP_Page_label_InfoName, "By : k_ying");
	lv_label_set_long_mode(ui->APP_Page_label_InfoName, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->APP_Page_label_InfoName, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for APP_Page_label_InfoName
	static lv_style_t style_APP_Page_label_InfoName_main;
	lv_style_reset(&style_APP_Page_label_InfoName_main);

	//Write style state: LV_STATE_DEFAULT for style_APP_Page_label_InfoName_main
	lv_style_set_radius(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_APP_Page_label_InfoName_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->APP_Page_label_InfoName, LV_LABEL_PART_MAIN, &style_APP_Page_label_InfoName_main);
	lv_obj_set_pos(ui->APP_Page_label_InfoName, 40, 82);
	lv_obj_set_size(ui->APP_Page_label_InfoName, 158, 0);
	lv_tileview_add_element(ui->APP_Page_APP_List, ui->APP_Page_label_InfoName);

	//Init events for screen
	events_init_APP_Page(ui);
	scrloading = false;
	max30102_set_mode(&max30102, MAX30102_SHDN_ON);
}
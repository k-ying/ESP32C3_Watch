/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *Timehome;
	lv_obj_t *Timehome_TIme_Hour;
	lv_obj_t *Timehome_Time_Min;
	lv_obj_t *Timehome_Time_Dot;
	lv_obj_t *Timehome_Time_Year;
	// lv_obj_t *Timehome_Time_Line1;
	// lv_obj_t *Timehome_TIme_Mon;
	// lv_obj_t *Timehome_Time_Line2;
	// lv_obj_t *Timehome_Time_Sec;
	lv_obj_t *APP_Page;
	lv_obj_t *APP_Page_APP_Titile;
	lv_obj_t *APP_Page_BTN_BackTime;
	lv_obj_t *APP_Page_BTN_BackTime_label;
	lv_obj_t *APP_Page_APP_List;
	lv_obj_t *APP_Page_APP_List_APP_HeartRate;
	lv_obj_t *APP_Page_img_HeartRate;
	lv_obj_t *APP_Page_btn_HeartRate;
	lv_obj_t *APP_Page_btn_HeartRate_label;
	lv_obj_t *APP_Page_APP_List_APP_Sport;
	lv_obj_t *APP_Page_img_Sport;
	lv_obj_t *APP_Page_btn_Sport;
	lv_obj_t *APP_Page_btn_Sport_label;
	lv_obj_t *APP_Page_APP_List_APP_Temp;
	lv_obj_t *APP_Page_img_Temp;
	lv_obj_t *APP_Page_btn_Temp;
	lv_obj_t *APP_Page_btn_Temp_label;
	lv_obj_t *APP_Page_APP_List_APP_Connect;
	lv_obj_t *APP_Page_img_Connect;
	lv_obj_t *APP_Page_btn_Connect;
	lv_obj_t *APP_Page_btn_Connect_label;
	lv_obj_t *APP_Page_APP_List_APP_Info;
	lv_obj_t *APP_Page_label_InfoVer;
	lv_obj_t *APP_Page_label_InfoName;
	lv_obj_t *APPtoHR;
	lv_obj_t *APPtoHR_chart_HeartBeep;
	lv_obj_t *APPtoHR_label_BPM;
	lv_obj_t *APPtoHR_label_SpO2;
	lv_obj_t *APPtoHR_label_NumBPM;
	lv_obj_t *APPtoHR_label_NumSpO2;
	lv_obj_t *APPtoSport;
	lv_obj_t *APPtoSport_lmeter_steps;
	lv_obj_t *APPtoSport_label_Steps;
	lv_obj_t *APPtoSport_label_NumSteps;
	lv_obj_t *APPtoSport_sw_Fall;
	lv_obj_t *APPtoSport_label_Fall;
	lv_obj_t *APPtoSport_label_DetectRes;
	lv_obj_t *APPtoTemp;
	lv_obj_t *APPtoTemp_bar_Tempbar;
	lv_obj_t *APPtoTemp_line_bottom;
	lv_obj_t *APPtoTemp_line_middle;
	lv_obj_t *APPtoTemp_line_top;
	lv_obj_t *APPtoTemp_label_TempValue;
	lv_obj_t *APPtoTemp_label_Celsius;
	lv_obj_t *APPtoTemp_sw_Sensor2People;
	lv_obj_t *APPtoTemp_label_Sensor;
	lv_obj_t *APPtoTemp_label_People;
	lv_obj_t *APPtoConnect;
	lv_obj_t *APPtoConnect_input_SSID;
	lv_obj_t *APPtoConnect_label_SSID;
	lv_obj_t *APPtoConnect_input_PWD;
	lv_obj_t *APPtoConnect_label_PWD;
	lv_obj_t *APPtoConnect_cb_Remember;
	lv_obj_t *APPtoConnect_btn_Conn;
	lv_obj_t *APPtoConnect_btn_Conn_label;
	lv_obj_t *APPtoConnect_msgbox_connOK;
	lv_obj_t *notify_msgbox;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_Timehome(lv_ui *ui);
void setup_scr_APP_Page(lv_ui *ui);
void setup_scr_APPtoHR(lv_ui *ui);
void setup_scr_APPtoSport(lv_ui *ui);
void setup_scr_APPtoTemp(lv_ui *ui);
void setup_scr_APPtoConnect(lv_ui *ui);
LV_IMG_DECLARE(_run_alpha_120x120);
LV_IMG_DECLARE(_temperature_alpha_120x120);
LV_IMG_DECLARE(_wifi_alpha_120x120);
LV_IMG_DECLARE(_HeartBeat_alpha_120x120);

#ifdef __cplusplus
}
#endif
#endif
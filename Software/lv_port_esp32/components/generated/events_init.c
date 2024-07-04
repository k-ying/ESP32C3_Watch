/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
extern bool scrloading;

void events_init(lv_ui *ui)
{
}

void lv_toHome_task(lv_task_t * toHome_task){
	setup_scr_Timehome(&guider_ui);
	lv_scr_load_anim(guider_ui.Timehome, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 40, true);
}

static void APP_Page_BTN_BackTimeevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		// if (!lv_debug_check_obj_valid(guider_ui.Timehome))
		// 	{setup_scr_Timehome(&guider_ui);}

		// setup_scr_Timehome(&guider_ui);
		// lv_scr_load_anim(guider_ui.Timehome, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 40, true);
		lv_task_t * toHome_task = lv_task_create(lv_toHome_task, 500, LV_TASK_PRIO_HIGHEST, NULL);
        lv_task_once(toHome_task);
		
		//lv_task_handler();
	}
		break;
	default:
		break;
	}
}

static void APP_Page_btn_Connectevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		// if (!lv_debug_check_obj_valid(guider_ui.APPtoConnect))
		// 	{setup_scr_APPtoConnect(&guider_ui);}
		setup_scr_APPtoConnect(&guider_ui);
		lv_scr_load_anim(guider_ui.APPtoConnect, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 40, true);
		//lv_task_handler();
	}
		break;
	default:
		break;
	}
}

static void APP_Page_btn_Tempevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		// if (!lv_debug_check_obj_valid(guider_ui.APPtoTemp))
		// 	{setup_scr_APPtoTemp(&guider_ui);}
		setup_scr_APPtoTemp(&guider_ui);
		lv_scr_load_anim(guider_ui.APPtoTemp, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 40, true);
		//lv_task_handler();
	}
		break;
	default:
		break;
	}
}

static void APP_Page_btn_Sportevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		// if (!lv_debug_check_obj_valid(guider_ui.APPtoSport))
		// 	{setup_scr_APPtoSport(&guider_ui);}
		setup_scr_APPtoSport(&guider_ui);
		lv_scr_load_anim(guider_ui.APPtoSport, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 40, true);
		//lv_task_handler();
	}
		break;
	default:
		break;
	}
}

static void APP_Page_btn_HeartRateevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		if(lv_debug_check_obj_valid(guider_ui.Timehome) || scrloading == true){break;}
		else
		{
			scrloading = true;
			setup_scr_APPtoHR(&guider_ui);
			lv_scr_load_anim(guider_ui.APPtoHR, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 40, true);
			//lv_task_handler();
			scrloading = false;
		}
	}
		break;
	default:
		break;
	}
}

void events_init_APP_Page(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->APP_Page_BTN_BackTime, APP_Page_BTN_BackTimeevent_handler);
	
	lv_obj_set_event_cb(ui->APP_Page_btn_Connect, APP_Page_btn_Connectevent_handler);
	
	lv_obj_set_event_cb(ui->APP_Page_btn_Temp, APP_Page_btn_Tempevent_handler);
	lv_obj_set_event_cb(ui->APP_Page_btn_Sport, APP_Page_btn_Sportevent_handler);
	lv_obj_set_event_cb(ui->APP_Page_btn_HeartRate, APP_Page_btn_HeartRateevent_handler);
}

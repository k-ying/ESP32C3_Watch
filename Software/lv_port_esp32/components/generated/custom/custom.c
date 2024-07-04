// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "custom.h"
#include "userwifi.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
extern bool scrloading;
extern bool people_flag;
// extern bool Mqtt_start_flag;
/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */

}
void lv_toapp_task(lv_task_t * task){
    lv_scr_load_anim(guider_ui.APP_Page, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 40, true);
    //lv_obj_del_async(guider_ui.Timehome);
}

void To_APP_cb(lv_obj_t * obj, lv_event_t e)
{
    // if(e == LV_EVENT_GESTURE) {
    //     lv_gesture_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    //     //printf("Dir: %d\n", dir);
    //     if(dir == LV_GESTURE_DIR_TOP){
    //         if(!lv_debug_check_obj_valid(guider_ui.APP_Page)){
    //             setup_scr_APP_Page(&guider_ui);
    //         }            
    //         lv_scr_load_anim(guider_ui.APP_Page, LV_SCR_LOAD_ANIM_MOVE_TOP, 500, 10, true);
    //     }
    // }
    switch (e)
	{
	case LV_EVENT_GESTURE:
	{
        //lv_gesture_dir_t dir = ;
        //printf("Dir: %d\n", dir);
        if((lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_GESTURE_DIR_TOP) && (scrloading == false)){
            scrloading = true;
            if(!lv_debug_check_obj_valid(guider_ui.APP_Page)){
                setup_scr_APP_Page(&guider_ui);
            }
            //lv_scr_load_anim(guider_ui.APP_Page, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 40, true);
            /* anim may carsh sec task,should use task loading anim */
            lv_task_t * toapp_task = lv_task_create(lv_toapp_task, 500, LV_TASK_PRIO_HIGHEST, NULL);
            lv_task_once(toapp_task);
        }
	}
		break;
	default:
		break;
	}
}

void Back_APP_cb(lv_obj_t * obj, lv_event_t e)
{
    //   if(e == LV_EVENT_GESTURE) {
    //     lv_gesture_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    //     if(dir == LV_GESTURE_DIR_BOTTOM){
    //         if(!lv_debug_check_obj_valid(guider_ui.APP_Page)){
    //             setup_scr_APP_Page(&guider_ui);
    //         }
    //         lv_scr_load_anim(guider_ui.APP_Page, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 10, true);
    //     }
    // }  
    switch (e)
	{
	case LV_EVENT_GESTURE:
	{
        lv_gesture_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if(dir == LV_GESTURE_DIR_BOTTOM){
            if(!lv_debug_check_obj_valid(guider_ui.APP_Page)){
                setup_scr_APP_Page(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.APP_Page, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 40, true);
            
        }
	}
		break;
	default:
		break;
	}
}

void Timeset_func(lv_ui *ui,uint8_t hour_value,uint8_t min_value,char day_str[11])
{
    /* if page valid */
    if(lv_scr_act() == ui->Timehome){
        if(lv_debug_check_obj_valid(ui->Timehome_Time_Min))
        {

            lv_label_set_text_fmt(ui->Timehome_Time_Min, "%02d", min_value);
            lv_label_set_text_fmt(ui->Timehome_TIme_Hour, "%02d", hour_value);
            if(day_str[0] != NULL){
                lv_label_set_text(ui->Timehome_Time_Year,day_str);
            }
        }
    }
}

void Stepset_func(lv_ui *ui, unsigned long step_value, float stepDis)
{
    /* if page valid */
    if(lv_scr_act() == ui->APPtoSport){
        if(lv_debug_check_obj_valid(ui->APPtoSport_label_NumSteps))
        {
            lv_label_set_text_fmt(ui->APPtoSport_label_NumSteps, "%05d", step_value);
            lv_linemeter_set_value(ui->APPtoSport_lmeter_steps, (int32_t)(step_value*100/5000));//if steps 5000 is daily target
            lv_label_set_text_fmt(ui->APPtoSport_label_Fall,"Distance:%.2f m",stepDis);
        }
    }
    /* long time stay Detect  */
    static int timecount=0;
    static unsigned long step_vBefore=0;
    if( timecount > ( 1 * 60 -1) )
    {
        if(step_vBefore == step_value)
        {   // notify user
            if(!lv_debug_check_obj_valid(guider_ui.notify_msgbox))
            {
                static const char * notify_btns[] ={"OK", ""};
                guider_ui.notify_msgbox = lv_msgbox_create(lv_scr_act(), NULL);
                lv_msgbox_set_text(guider_ui.notify_msgbox, "Stay long time!");
                lv_msgbox_add_btns(guider_ui.notify_msgbox, notify_btns);
                lv_obj_set_width(guider_ui.notify_msgbox, 200);
                lv_obj_align(guider_ui.notify_msgbox, NULL, LV_ALIGN_CENTER, 0, 0);
            }
        }else{step_vBefore=step_value;}
        timecount=0;
    }else{timecount++;}
}


void Tempset_func(lv_ui *ui,float temp_value)
{
    /* if page valid */
    if(lv_scr_act() == ui->APPtoTemp){
        if(lv_debug_check_obj_valid(ui->APPtoTemp_label_TempValue))
        {
            lv_label_set_text_fmt(ui->APPtoTemp_label_TempValue, "%2.1f", temp_value);
            lv_bar_set_value(ui->APPtoTemp_bar_Tempbar,temp_value,LV_ANIM_ON);
            if (people_flag)
            {
                lv_label_set_text(ui->APPtoTemp_label_Sensor,"People: YES");
            }else lv_label_set_text(ui->APPtoTemp_label_Sensor,"People: NO");
        }
    }
}

void HR_func(lv_ui *ui,float HR_value,float SPO2_value)
{
    /* if page valid */
    if(lv_scr_act() == ui->APPtoHR){
        if(lv_debug_check_obj_valid(ui->APPtoHR_label_NumBPM))
        {
            lv_label_set_text_fmt(ui->APPtoHR_label_NumBPM, "%2.1f", HR_value);
            lv_label_set_text_fmt(ui->APPtoHR_label_NumSpO2, "%2.1f", SPO2_value);
        }
    }
}
void lv_stmq_task(lv_task_t * stmq_task){
/* ------------------------------------ Start mqtt ------------------------------ */    
    mqtt_app_start();
    lv_msgbox_set_text(guider_ui.APPtoConnect_msgbox_connOK,"SNTP & mqtt OK!");
    lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, false);
    lv_task_handler();
}

void lv_sntp_task(lv_task_t * sntp_task)
{   
    // SNTP in Callback may cause deadlock?
    if(SNTP_GetTime()==1){
        // lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, true);
        //vTaskDelay(100/portTICK_RATE_MS);
        lv_msgbox_set_text(guider_ui.APPtoConnect_msgbox_connOK,"SNTP Error,Retrying... ");
        lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, false);
        lv_task_handler();
        lv_task_t * sntp_task = lv_task_create(lv_sntp_task, 1000, LV_TASK_PRIO_HIGHEST,NULL);
        lv_task_once(sntp_task);
    }else{
        lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, true);
        lv_task_handler();
        //vTaskDelay(100/portTICK_RATE_MS);
        lv_msgbox_set_text(guider_ui.APPtoConnect_msgbox_connOK,"SNTP OK! mqtt... ");
        lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, false);
        lv_task_handler();

        char strf_day[11],strf_hour[3],strf_min[3],strf_sec[3];
        extern uint8_t time_sec,time_min,time_hour,time_sync_flag;
        extern char time_day[11];
        //update sec
        strftime(strf_sec, sizeof(strf_sec), "%S", &timeinfo);//SS
        time_sec=atoi(strf_sec);

        strftime(strf_min, sizeof(strf_min), "%M", &timeinfo);//MM
        time_min=atoi(strf_min);

        strftime(strf_hour, sizeof(strf_hour), "%H", &timeinfo);//HH
        time_hour=atoi(strf_hour);

        strftime(strf_day, sizeof(strf_day), "%F", &timeinfo);//YYYY-MM-DD
        strcpy(time_day,strf_day);
        time_sync_flag=1;

        lv_task_t * stmq_task = lv_task_create(lv_stmq_task, 3000, LV_TASK_PRIO_HIGHEST,NULL);
        lv_task_once(stmq_task);
    }

}

void APPtoConnect_btn_click(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
        lv_btn_set_state(guider_ui.APPtoConnect_btn_Conn,LV_BTN_STATE_DISABLED);
        // lv_task_t * wificonn_task = lv_task_create(lv_wificonn_task, 500, LV_TASK_PRIO_HIGH,NULL);
        // lv_task_once(wificonn_task);
        strcpy(wifi_ssid,lv_textarea_get_text(guider_ui.APPtoConnect_input_SSID));
        //printf("SSID is:%s\n",wifi_ssid);
        strcpy(wifi_passwd,lv_textarea_get_text(guider_ui.APPtoConnect_input_PWD));

        if(lv_checkbox_is_checked(guider_ui.APPtoConnect_cb_Remember) == true)
        {
            nvs_handle_t wifisave_handle;
            nvs_open("wifisave", NVS_READWRITE, &wifisave_handle);
            nvs_set_str(wifisave_handle,"wifissid",wifi_ssid);
            nvs_commit(wifisave_handle);
            nvs_set_str(wifisave_handle,"wifipasswd",wifi_passwd);
            nvs_commit(wifisave_handle);
            nvs_close(wifisave_handle);
        }
        wifi_user_init();
        /* ------------------------------SNTP+RTC sync time task-------------------------- */
        if(Conn_Flag)
        {
            lv_msgbox_set_text(guider_ui.APPtoConnect_msgbox_connOK,"WiFi OK! SNTP...");
            lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, false);
            lv_task_handler();

            lv_task_t * sntp_task = lv_task_create(lv_sntp_task, 1000, LV_TASK_PRIO_HIGHEST,NULL);
            lv_task_once(sntp_task);

            // SNTP_GetTime();// SNTP in Callback may cause deadlock?
            // //disable btn & display msgbox
            // lv_msgbox_set_text(guider_ui.APPtoConnect_msgbox_connOK,"WiFi OK!");
            // lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, false);
            
            // char strf_day[11],strf_hour[3],strf_min[3],strf_sec[3];
            // extern uint8_t time_sec,time_min,time_hour,time_sync_flag;
            // extern char time_day[11];
            // //update sec
            // strftime(strf_sec, sizeof(strf_sec), "%S", &timeinfo);//SS
            // time_sec=atoi(strf_sec);
            // //printf("time_sec=%d",time_sec);
            // strftime(strf_min, sizeof(strf_min), "%M", &timeinfo);//MM
            // time_min=atoi(strf_min);
            // //lv_label_set_text(guider_ui.Timehome_Time_Min, strf_min);
            // strftime(strf_hour, sizeof(strf_hour), "%H", &timeinfo);//HH
            // time_hour=atoi(strf_hour);
            // //lv_label_set_text(guider_ui.Timehome_TIme_Hour, strf_hour);
            // strftime(strf_day, sizeof(strf_day), "%F", &timeinfo);//YYYY-MM-DD
            // strcpy(time_day,strf_day);
            // time_sync_flag=1;
            
            // //lv_label_set_text(guider_ui.Timehome_Time_Year, strf_day);

        }else{
            //disable btn & display msgbox
            lv_msgbox_set_text(guider_ui.APPtoConnect_msgbox_connOK,"Connect Error!");
            lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, false);
        }

	}
		break;
	default:
		break;
	}
}

void msgbox_connOK_cb(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_set_hidden(guider_ui.APPtoConnect_msgbox_connOK, true);
    }
}
// void lv_wificonn_task(lv_task_t * wificonn_task){
//     ();
// }



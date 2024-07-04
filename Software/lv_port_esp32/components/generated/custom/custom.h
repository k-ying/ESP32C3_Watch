// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_

#include "gui_guider.h"

#include "MAX30205.h"
#include "max30102-registers.h"
extern max30102_config_t max30102;

void custom_init(lv_ui *ui);

void To_APP_cb(lv_obj_t * obj, lv_event_t e);
void Back_APP_cb(lv_obj_t * obj, lv_event_t e);

void Timeset_func(lv_ui *ui,uint8_t hour_value,uint8_t min_value,char day_str[11]);
void Stepset_func(lv_ui *ui, unsigned long step_value, float stepDis);
void Tempset_func(lv_ui *ui,float temp_value);
void HR_func(lv_ui *ui,float HR_value,float SPO2_value);
void APPtoConnect_btn_click(lv_obj_t * obj, lv_event_t event);
void msgbox_connOK_cb(lv_obj_t * obj, lv_event_t event);

// void lv_wificonn_task(lv_task_t * wificonn_task);

#endif /* EVENT_CB_H_ */

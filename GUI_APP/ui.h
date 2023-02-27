// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#define WINDOW_NUM			5	//TimePage TimeSetPage, EnvPage, DirectionPage, HR, Logo
#define TIME_WINDOW 		1 
#define	ENV_WINDOW			2
#define DIR_WINDOW			3
#define HR_WINDOW				4
#define LOGO_WINDOW			5

#define TIMESET_NULL		0
#define TIMESET_HOURE		1
#define TIMESET_MINUTE	2
#define TIMESET_MONTH  	3
#define TIMESET_DATE    4
#define TIMESET_DAY			5


extern lv_obj_t * ui_TimePage;
extern lv_obj_t * ui_backgrand1;
extern lv_obj_t * ui_LabelDateMonth;
extern lv_obj_t * ui_LabelDay;
extern lv_obj_t * ui_LabelTimeMin;
extern lv_obj_t * ui_Label11;
extern lv_obj_t * ui_LabelTimeHour;
extern lv_obj_t * ui_Label13;
extern lv_obj_t * ui_LabelDateDate;
extern lv_obj_t * ui_ArcBat;
extern lv_obj_t * ui_bat;
extern lv_obj_t * ui_label_flash;
extern lv_obj_t * ui_label_top_battery_TP;
extern lv_obj_t * ui_label_top_charge_TP;
extern lv_obj_t * ui_label_top_wifi_TP;

extern lv_obj_t * ui_EnvPage;
extern lv_obj_t * ui_backgrand4;
extern lv_obj_t * ui_ArcTemp;
extern lv_obj_t * ui_label_temperature;
extern lv_obj_t * ui_picture_temperature;
extern lv_obj_t * ui_label_Altitude;
extern lv_obj_t * ui_picture_attitude;
extern lv_obj_t * ui_label_top_battery_EP;
extern lv_obj_t * ui_label_top_charge_EP;
extern lv_obj_t * ui_label_top_wifi_EP;

extern lv_obj_t * ui_DirectionPage;
extern lv_obj_t * ui_backgrand2;
extern lv_obj_t * ui_meter_compass;
extern lv_meter_scale_t * ui_scale_compass;
extern lv_meter_indicator_t * ui_needle_compass;
extern lv_obj_t * ui_Label_N;
extern lv_obj_t * ui_Label_S;
extern lv_obj_t * ui_Label_W;
extern lv_obj_t * ui_Label_E;
extern lv_obj_t * ui_Label_Direction;
extern lv_obj_t * ui_label_top_battery_DP;
extern lv_obj_t * ui_label_top_charge_DP;
extern lv_obj_t * ui_label_top_wifi_DP;
extern lv_obj_t * ui_label_top_GPS_DP;

extern lv_obj_t * ui_HrPage;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Spinner2;
extern lv_obj_t * ui_LabelHr;
extern lv_obj_t * ui_label_heart;
extern lv_obj_t * ui_label_top_battery_HP;
extern lv_obj_t * ui_label_top_charge_HP;
extern lv_obj_t * ui_label_top_wifi_HP;

extern lv_obj_t * ui_LogoPage;
extern lv_obj_t * ui_backgrand3;


LV_IMG_DECLARE(ui_img_background1_png);    // assets\backbroun1.png
LV_IMG_DECLARE(ui_img_ow3_png);    // assets\ow3.png
LV_IMG_DECLARE(ui_compass_needle_png);

///////////////////// FONT ////////////////////
LV_FONT_DECLARE(HeartBeatFont);

#define HeartBeatFont1 "\xEE\x98\x91"
#define HeartBeatFont2 "\xEE\x9C\xBA"
#define HeartBeatFont3 "\xEE\x9D\xA2"

LV_FONT_DECLARE(EnvFont_45);

#define TemperatureFont "\xEE\x99\x99"
#define AttitudeFont    "\xEE\x9A\x9B"


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

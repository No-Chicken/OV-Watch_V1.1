// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "rtc.h"
#include "SPL06_001.h"
#include "power.h"
///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_TimePage;
lv_obj_t * ui_backgrand1;
lv_obj_t * ui_LabelDateMonth;
lv_obj_t * ui_LabelDay;
lv_obj_t * ui_LabelTimeMin;
lv_obj_t * ui_Label11;
lv_obj_t * ui_LabelTimeHour;
lv_obj_t * ui_Label13;
lv_obj_t * ui_LabelDateDate;
lv_obj_t * ui_ArcBat;
lv_obj_t * ui_bat;
lv_obj_t * ui_label_flash;
lv_obj_t * ui_label_top_battery_TP;
lv_obj_t * ui_label_top_charge_TP;
lv_obj_t * ui_label_top_wifi_TP;

lv_obj_t * ui_EnvPage;
lv_obj_t * ui_backgrand4;
lv_obj_t * ui_ArcTemp;
lv_obj_t * ui_label_temperature;
lv_obj_t * ui_picture_temperature;
lv_obj_t * ui_label_Altitude;
lv_obj_t * ui_picture_attitude;
lv_obj_t * ui_label_top_battery_EP;
lv_obj_t * ui_label_top_charge_EP;
lv_obj_t * ui_label_top_wifi_EP;

lv_obj_t * ui_DirectionPage;
lv_obj_t * ui_backgrand2;
lv_obj_t * ui_meter_compass;
lv_meter_scale_t * ui_scale_compass;
lv_meter_indicator_t * ui_needle_compass;
lv_obj_t * ui_Label_N;
lv_obj_t * ui_Label_S;
lv_obj_t * ui_Label_W;
lv_obj_t * ui_Label_E;
lv_obj_t * ui_Label_Direction;
lv_obj_t * ui_label_top_battery_DP;
lv_obj_t * ui_label_top_charge_DP;
lv_obj_t * ui_label_top_wifi_DP;
lv_obj_t * ui_label_top_GPS_DP;

lv_obj_t * ui_HrPage;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Spinner2;
lv_obj_t * ui_LabelHr;
lv_obj_t * ui_label_heart;
lv_obj_t * ui_label_top_battery_HP;
lv_obj_t * ui_label_top_charge_HP;
lv_obj_t * ui_label_top_wifi_HP;

lv_obj_t * ui_LogoPage;
lv_obj_t * ui_backgrand3;

uint8_t ui_window 		 = TIME_WINDOW;
uint8_t ui_timeset_pos = 0;

uint8_t num;
extern int16_t direction;
extern int16_t attitude;
extern uint8_t HeartRate;
extern int8_t temperature;
uint8_t strtemp[20];
///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// TIMEDATAInit ////////////////////
void TimeDateRenewInit(void)
{
		uint8_t strbuff[10];
		RTC_DateTypeDef nowdate;
		RTC_TimeTypeDef nowtime;
		HAL_RTC_GetTime(&hrtc,&nowtime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&nowdate,RTC_FORMAT_BIN);
		if((ui_window == TIME_WINDOW) && (ui_timeset_pos == TIMESET_NULL))
		{
			sprintf(strbuff,"%02d", nowtime.Hours);
			lv_label_set_text(ui_LabelTimeHour, strbuff);
			sprintf(strbuff,"%02d", nowtime.Minutes);
			lv_label_set_text(ui_LabelTimeMin, strbuff);
			sprintf(strbuff,"%02d", nowdate.Month/12+nowdate.Month%12);//BCD
			lv_label_set_text(ui_LabelDateMonth, strbuff);
			sprintf(strbuff,"%02d", nowdate.Date);
			lv_label_set_text(ui_LabelDateDate, strbuff);
			switch(nowdate.WeekDay)
			{
				case 1:
					sprintf(strbuff,"Monday");
					break;
				case 2:
					sprintf(strbuff,"Tuesday");
					break;
				case 3:
					sprintf(strbuff,"Wednesday");
					break;
				case 4:
					sprintf(strbuff,"Thursday");
					break;
				case 5:
					sprintf(strbuff,"Friday");
					break;
				case 6:
					sprintf(strbuff,"Saturday");
					break;
				case 7:
					sprintf(strbuff,"Sunday");
					break;
			}
			lv_label_set_text(ui_LabelDay, strbuff);
		}
}

void EnvDataInit()
{
	sprintf(strtemp,"%.1f",Temperature_Calculate());
	lv_label_set_text(ui_label_temperature, strtemp);
	sprintf(strtemp,"%.1fm",Altitude_Calculate());
	lv_label_set_text(ui_label_Altitude, strtemp);
	
}
///////////////////// SCREENS ////////////////////
void ui_TimePage_screen_init(void)
{

    // ui_TimePage

    ui_TimePage = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_TimePage, LV_OBJ_FLAG_SCROLLABLE);

    // ui_backgrand1

    ui_backgrand1 = lv_img_create(ui_TimePage);
    lv_img_set_src(ui_backgrand1, &ui_img_background1_png);

    lv_obj_set_width(ui_backgrand1, 135);
    lv_obj_set_height(ui_backgrand1, 240);

    lv_obj_set_x(ui_backgrand1, 0);
    lv_obj_set_y(ui_backgrand1, 0);

    lv_obj_set_align(ui_backgrand1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_backgrand1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_backgrand1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LabelDateMonth

    ui_LabelDateMonth = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_LabelDateMonth, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDateMonth, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelDateMonth, -18);
    lv_obj_set_y(ui_LabelDateMonth, -12);

    lv_obj_set_align(ui_LabelDateMonth, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelDateMonth, "07");

    lv_obj_set_style_text_font(ui_LabelDateMonth, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LabelDateMonth, lv_color_hex(0x3884F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LabelDateMonth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelDay

    ui_LabelDay = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_LabelDay, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDay, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelDay, 0);
    lv_obj_set_y(ui_LabelDay, 15);

    lv_obj_set_align(ui_LabelDay, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelDay, "Monday");

    lv_obj_set_style_text_font(ui_LabelDay, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LabelDay, lv_color_hex(0x3884F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LabelDay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelTimeMin

    ui_LabelTimeMin = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_LabelTimeMin, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelTimeMin, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelTimeMin, 35);
    lv_obj_set_y(ui_LabelTimeMin, -60);

    lv_obj_set_align(ui_LabelTimeMin, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelTimeMin, "59");

    lv_obj_set_style_text_font(ui_LabelTimeMin, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LabelTimeMin, lv_color_hex(0x3884F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LabelTimeMin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label11

    ui_Label11 = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label11, 0);
    lv_obj_set_y(ui_Label11, -62);

    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label11, ":");

    lv_obj_set_style_text_font(ui_Label11, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelTimeHour

    ui_LabelTimeHour = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_LabelTimeHour, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelTimeHour, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelTimeHour, -35);
    lv_obj_set_y(ui_LabelTimeHour, -60);

    lv_obj_set_align(ui_LabelTimeHour, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelTimeHour, "11");

    lv_obj_set_style_text_font(ui_LabelTimeHour, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LabelTimeHour, lv_color_hex(0x3884F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LabelTimeHour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    // ui_Label13

    ui_Label13 = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label13, 0);
    lv_obj_set_y(ui_Label13, -12);

    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label13, "-");

    lv_obj_set_style_text_font(ui_Label13, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelDateDate

    ui_LabelDateDate = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_LabelDateDate, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDateDate, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelDateDate, 18);
    lv_obj_set_y(ui_LabelDateDate, -12);

    lv_obj_set_align(ui_LabelDateDate, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelDateDate, "07");

    lv_obj_set_style_text_font(ui_LabelDateDate, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LabelDateDate, lv_color_hex(0x3884F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LabelDateDate, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_ArcBat

    ui_ArcBat = lv_arc_create(ui_TimePage);

    lv_obj_set_width(ui_ArcBat, 50);
    lv_obj_set_height(ui_ArcBat, 50);

    lv_obj_set_x(ui_ArcBat, 0);
    lv_obj_set_y(ui_ArcBat, 80);

    lv_obj_set_align(ui_ArcBat, LV_ALIGN_CENTER);

    lv_arc_set_range(ui_ArcBat, 0, 100);
    lv_arc_set_value(ui_ArcBat, 45);
    lv_arc_set_bg_angles(ui_ArcBat, 130, 50);

    lv_obj_set_style_arc_width(ui_ArcBat, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_ArcBat, lv_color_hex(0x12D414), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcBat, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcBat, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcBat, lv_color_hex(0x12D414), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcBat, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ArcBat, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ArcBat, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ArcBat, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ArcBat, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // ui_bat

    ui_bat = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_bat, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_bat, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_bat, 0);
    lv_obj_set_y(ui_bat, 80);

    lv_obj_set_align(ui_bat, LV_ALIGN_CENTER);

    lv_label_set_text(ui_bat, "45%");

    //ui_label_flash

    ui_label_flash = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_label_flash, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_flash, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_flash, 0);
    lv_obj_set_y(ui_label_flash, 100);

    lv_obj_set_align(ui_label_flash, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_flash, LV_SYMBOL_CHARGE);

    lv_obj_set_style_text_color(ui_label_flash, lv_color_hex(0x12D414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_flash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_battery_TP

    ui_label_top_battery_TP = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_label_top_battery_TP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_battery_TP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_battery_TP, 55);
    lv_obj_set_y(ui_label_top_battery_TP, -110);

    lv_obj_set_align(ui_label_top_battery_TP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_battery_TP, LV_SYMBOL_BATTERY_2);
    lv_obj_set_style_text_font(ui_label_top_battery_TP, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_charge_TP

    ui_label_top_charge_TP = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_label_top_charge_TP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_charge_TP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_charge_TP, 35);
    lv_obj_set_y(ui_label_top_charge_TP, -110);

    lv_obj_set_align(ui_label_top_charge_TP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_top_charge_TP, LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_font(ui_label_top_charge_TP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_wifi_TP
    ui_label_top_wifi_TP = lv_label_create(ui_TimePage);

    lv_obj_set_width(ui_label_top_wifi_TP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_wifi_TP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_wifi_TP, 18);
    lv_obj_set_y(ui_label_top_wifi_TP, -110);

    lv_obj_set_align(ui_label_top_wifi_TP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_wifi_TP, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(ui_label_top_wifi_TP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
		//TimeDateInit
		TimeDateRenewInit();
		//power
		sprintf(strtemp,"%d%%",PowerCalculate());
		lv_label_set_text(ui_bat, strtemp);
		lv_arc_set_value(ui_ArcBat, PowerCalculate());
		
}

void ui_EnvPage_screen_init(void)
{
    // ui_EnvPage

    ui_EnvPage = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_EnvPage, LV_OBJ_FLAG_SCROLLABLE);

    // ui_backgrand4

    ui_backgrand4 = lv_img_create(ui_EnvPage);
    lv_img_set_src(ui_backgrand4, &ui_img_background1_png);

    lv_obj_set_width(ui_backgrand4, 135);
    lv_obj_set_height(ui_backgrand4, 240);

    lv_obj_set_x(ui_backgrand4, 0);
    lv_obj_set_y(ui_backgrand4, 0);

    lv_obj_set_align(ui_backgrand4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_backgrand4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_backgrand4, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ArcTemp

    ui_ArcTemp = lv_arc_create(ui_EnvPage);

    lv_obj_set_width(ui_ArcTemp, 90);
    lv_obj_set_height(ui_ArcTemp, 90);

    lv_obj_set_x(ui_ArcTemp, 0);
    lv_obj_set_y(ui_ArcTemp, -50);

    lv_obj_set_align(ui_ArcTemp, LV_ALIGN_CENTER);

    lv_arc_set_range(ui_ArcTemp, -10, 80);
    lv_arc_set_value(ui_ArcTemp, temperature);
    lv_arc_set_bg_angles(ui_ArcTemp, 120, 60);

    lv_obj_set_style_arc_width(ui_ArcTemp, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_ArcTemp, lv_color_hex(0xCD0A20), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcTemp, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcTemp, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcTemp, lv_color_hex(0xCD0A20), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcTemp, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ArcTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ArcTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ArcTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ArcTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    //ui_label_temperature

    ui_label_temperature = lv_label_create(ui_EnvPage);
    lv_obj_set_width(ui_label_temperature, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_temperature, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_temperature, 0);
    lv_obj_set_y(ui_label_temperature, -50);

    lv_obj_set_align(ui_label_temperature, LV_ALIGN_CENTER);
    
    lv_label_set_text(ui_label_temperature, "25.0");

    lv_obj_set_style_text_color(ui_label_temperature, lv_color_hex(0xF60B2A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_temperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		
    lv_obj_set_style_text_font(ui_label_temperature, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_picture_temperature

    ui_picture_temperature = lv_label_create(ui_EnvPage);
    lv_obj_set_width(ui_picture_temperature, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_picture_temperature, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_picture_temperature, 0);
    lv_obj_set_y(ui_picture_temperature, -15);

    lv_obj_set_align(ui_picture_temperature, LV_ALIGN_CENTER);

    lv_label_set_text(ui_picture_temperature, TemperatureFont);

    lv_obj_set_style_text_font(ui_picture_temperature, &EnvFont_45, 0);
    lv_obj_set_style_text_color(ui_picture_temperature, lv_color_make(0xF6, 0x0B, 0x2A), 0);

    // ui_label_Altitude

    ui_label_Altitude = lv_label_create(ui_EnvPage);

    lv_obj_set_width(ui_label_Altitude, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_Altitude, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_Altitude, 0);
    lv_obj_set_y(ui_label_Altitude, 38);

    lv_obj_set_align(ui_label_Altitude, LV_ALIGN_CENTER);
		
    lv_label_set_text(ui_label_Altitude, "60.0m");

    lv_obj_set_style_text_color(ui_label_Altitude, lv_color_hex(0x0BF6F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_Altitude, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_Altitude, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_picture_attitude

    ui_picture_attitude = lv_label_create(ui_EnvPage);
    lv_obj_set_width(ui_picture_attitude, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_picture_attitude, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_picture_attitude, 0);
    lv_obj_set_y(ui_picture_attitude, 70);

    lv_obj_set_align(ui_picture_attitude, LV_ALIGN_CENTER);

    lv_label_set_text(ui_picture_attitude, AttitudeFont);

    lv_obj_set_style_text_font(ui_picture_attitude, &EnvFont_45, 0);
    lv_obj_set_style_text_color(ui_picture_attitude, lv_color_make(0x0B, 0xF6, 0xF4), 0);


    //ui_label_top_battery_EP

    ui_label_top_battery_EP = lv_label_create(ui_EnvPage);

    lv_obj_set_width(ui_label_top_battery_EP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_battery_EP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_battery_EP, 55);
    lv_obj_set_y(ui_label_top_battery_EP, -110);

    lv_obj_set_align(ui_label_top_battery_EP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_battery_EP, LV_SYMBOL_BATTERY_2);
    lv_obj_set_style_text_font(ui_label_top_battery_EP, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_charge_EP

    ui_label_top_charge_EP = lv_label_create(ui_EnvPage);

    lv_obj_set_width(ui_label_top_charge_EP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_charge_EP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_charge_EP, 35);
    lv_obj_set_y(ui_label_top_charge_EP, -110);

    lv_obj_set_align(ui_label_top_charge_EP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_top_charge_EP, LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_font(ui_label_top_charge_EP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_wifi_EP
    ui_label_top_wifi_EP = lv_label_create(ui_EnvPage);

    lv_obj_set_width(ui_label_top_wifi_EP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_wifi_EP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_wifi_EP, 18);
    lv_obj_set_y(ui_label_top_wifi_EP, -110);

    lv_obj_set_align(ui_label_top_wifi_EP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_wifi_EP, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(ui_label_top_wifi_EP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
		
		//EnvDataInit
		EnvDataInit();
    
}

void ui_DirectionPage_screen_init(void)
{
    // ui_DirectionPage

    ui_DirectionPage = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_DirectionPage, LV_OBJ_FLAG_SCROLLABLE);

    // ui_backgrand2

    ui_backgrand2 = lv_img_create(ui_DirectionPage);
    lv_img_set_src(ui_backgrand2, &ui_img_background1_png);

    lv_obj_set_width(ui_backgrand2, 135);
    lv_obj_set_height(ui_backgrand2, 240);

    lv_obj_set_x(ui_backgrand2, 0);
    lv_obj_set_y(ui_backgrand2, 0);

    lv_obj_set_align(ui_backgrand2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_backgrand2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_backgrand2, LV_OBJ_FLAG_SCROLLABLE);

    //ui_meter_compass
    ui_meter_compass = lv_meter_create(ui_DirectionPage);

    lv_obj_set_size(ui_meter_compass, 135, 135);
    lv_obj_center(ui_meter_compass);

    ui_scale_compass = lv_meter_add_scale(ui_meter_compass);
    lv_meter_set_scale_ticks(ui_meter_compass, ui_scale_compass, 61, 0, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(ui_meter_compass,ui_scale_compass,5,2,8,lv_palette_main(LV_PALETTE_GREY),-100);
    lv_meter_set_scale_range(ui_meter_compass, ui_scale_compass,0, 360, 360, 270);
		//needle
		ui_needle_compass = lv_meter_add_needle_img(ui_meter_compass, ui_scale_compass, &ui_compass_needle_png, 7, 50);
    lv_meter_set_indicator_value(ui_meter_compass,ui_needle_compass,100);
		
    // ui_Label_N

    ui_Label_N = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_Label_N, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label_N, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label_N, 0);
    lv_obj_set_y(ui_Label_N, -40);

    lv_obj_set_align(ui_Label_N, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label_N, "N");
		lv_obj_set_style_text_font(ui_Label_N, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Label_N, lv_color_hex(0xF60B2A), LV_PART_MAIN | LV_STATE_DEFAULT);
    // ui_Label_S

    ui_Label_S = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_Label_S, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label_S, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label_S, 0);
    lv_obj_set_y(ui_Label_S, 40);

    lv_obj_set_align(ui_Label_S, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label_S, "S");
		lv_obj_set_style_text_font(ui_Label_S, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Label_S, lv_color_hex(0X1E90FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // ui_Label_W

    ui_Label_W = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_Label_W, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label_W, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label_W, -40);
    lv_obj_set_y(ui_Label_W, 0);

    lv_obj_set_align(ui_Label_W, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label_W, "W");
		
		lv_obj_set_style_text_font(ui_Label_W, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // ui_Label_E

    ui_Label_E = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_Label_E, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label_E, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label_E, 40);
    lv_obj_set_y(ui_Label_E, 0);

    lv_obj_set_align(ui_Label_E, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label_E, "E");
		
		lv_obj_set_style_text_font(ui_Label_E, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
		
    // ui_Label_Direction

    ui_Label_Direction = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_Label_Direction, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label_Direction, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label_Direction, 0);
    lv_obj_set_y(ui_Label_Direction, 90);

    lv_obj_set_align(ui_Label_Direction, LV_ALIGN_CENTER);
    sprintf(strtemp,"%3d '", direction);
    lv_label_set_text(ui_Label_Direction, strtemp);
		lv_obj_set_style_text_font(ui_Label_Direction, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    //ui_label_top_battery_DP

    ui_label_top_battery_DP = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_label_top_battery_DP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_battery_DP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_battery_DP, 55);
    lv_obj_set_y(ui_label_top_battery_DP, -110);

    lv_obj_set_align(ui_label_top_battery_DP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_battery_DP, LV_SYMBOL_BATTERY_2);
    lv_obj_set_style_text_font(ui_label_top_battery_DP, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_charge_DP

    ui_label_top_charge_DP = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_label_top_charge_DP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_charge_DP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_charge_DP, 35);
    lv_obj_set_y(ui_label_top_charge_DP, -110);

    lv_obj_set_align(ui_label_top_charge_DP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_top_charge_DP, LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_font(ui_label_top_charge_DP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_wifi_DP
    ui_label_top_wifi_DP = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_label_top_wifi_DP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_wifi_DP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_wifi_DP, 18);
    lv_obj_set_y(ui_label_top_wifi_DP, -110);

    lv_obj_set_align(ui_label_top_wifi_DP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_wifi_DP, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(ui_label_top_wifi_DP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_GPS_DP
    ui_label_top_GPS_DP = lv_label_create(ui_DirectionPage);

    lv_obj_set_width(ui_label_top_GPS_DP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_GPS_DP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_GPS_DP, 2);
    lv_obj_set_y(ui_label_top_GPS_DP, -110);

    lv_obj_set_align(ui_label_top_GPS_DP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_GPS_DP, LV_SYMBOL_GPS);
    lv_obj_set_style_text_font(ui_label_top_GPS_DP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_HrPage_screen_init(void)
{

    // ui_HrPage

    ui_HrPage = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_HrPage, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image1

    ui_Image1 = lv_img_create(ui_HrPage);
    lv_img_set_src(ui_Image1, &ui_img_background1_png);

    lv_obj_set_width(ui_Image1, 135);
    lv_obj_set_height(ui_Image1, 240);

    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_y(ui_Image1, 0);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Spinner2

    ui_Spinner2 = lv_spinner_create(ui_HrPage, 1000, 90);

    lv_obj_set_width(ui_Spinner2, 80);
    lv_obj_set_height(ui_Spinner2, 80);

    lv_obj_set_x(ui_Spinner2, 0);
    lv_obj_set_y(ui_Spinner2, -30);

    lv_obj_set_align(ui_Spinner2, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_Spinner2, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_style_arc_width(ui_Spinner2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Spinner2, lv_color_hex(0xF50F16), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Spinner2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Spinner2, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //ui_label_heart

    ui_label_heart = lv_label_create(ui_HrPage);
    lv_obj_set_width(ui_label_heart, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_heart, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_heart, 0);
    lv_obj_set_y(ui_label_heart, -30);

    lv_obj_set_align(ui_label_heart, LV_ALIGN_CENTER);

    //heartbeat
    lv_label_set_text(ui_label_heart, HeartBeatFont3);

    lv_obj_set_style_text_font(ui_label_heart, &HeartBeatFont, 0);
    lv_obj_set_style_text_color(ui_label_heart, lv_color_make(0xff, 0x00, 0x00), 0);

    // ui_LabelHr

    ui_LabelHr = lv_label_create(ui_HrPage);

    lv_obj_set_width(ui_LabelHr, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelHr, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelHr, 1);
    lv_obj_set_y(ui_LabelHr, 34);

    lv_obj_set_align(ui_LabelHr, LV_ALIGN_CENTER);
    sprintf(strtemp, "HR: %d", HeartRate);
    lv_label_set_text(ui_LabelHr, strtemp);

    //ui_label_top_battery_HP

    ui_label_top_battery_HP = lv_label_create(ui_HrPage);

    lv_obj_set_width(ui_label_top_battery_HP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_battery_HP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_battery_HP, 55);
    lv_obj_set_y(ui_label_top_battery_HP, -110);

    lv_obj_set_align(ui_label_top_battery_HP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_battery_HP, LV_SYMBOL_BATTERY_2);
    lv_obj_set_style_text_font(ui_label_top_battery_HP, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_charge_HP

    ui_label_top_charge_HP = lv_label_create(ui_HrPage);

    lv_obj_set_width(ui_label_top_charge_HP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_charge_HP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_charge_HP, 35);
    lv_obj_set_y(ui_label_top_charge_HP, -110);

    lv_obj_set_align(ui_label_top_charge_HP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_top_charge_HP, LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_font(ui_label_top_charge_HP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    //ui_label_top_wifi_HP
    ui_label_top_wifi_HP = lv_label_create(ui_HrPage);

    lv_obj_set_width(ui_label_top_wifi_HP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_top_wifi_HP, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_label_top_wifi_HP, 18);
    lv_obj_set_y(ui_label_top_wifi_HP, -110);

    lv_obj_set_align(ui_label_top_wifi_HP, LV_ALIGN_CENTER);

    lv_label_set_text(ui_label_top_wifi_HP, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(ui_label_top_wifi_HP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



}
void ui_LogoPage_screen_init(void)
{

    // ui_LogoPage

    ui_LogoPage = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_LogoPage, LV_OBJ_FLAG_SCROLLABLE);

    // ui_backgrand3

    ui_backgrand3 = lv_img_create(ui_LogoPage);
    lv_img_set_src(ui_backgrand3, &ui_img_ow3_png);

    lv_obj_set_width(ui_backgrand3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_backgrand3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_backgrand3, 0);
    lv_obj_set_y(ui_backgrand3, 0);

    lv_obj_set_align(ui_backgrand3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_backgrand3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_backgrand3, LV_OBJ_FLAG_SCROLLABLE);

}

void ui_init(void)
{

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_TimePage_screen_init();
    ui_DirectionPage_screen_init();
    ui_HrPage_screen_init();
    ui_LogoPage_screen_init();
		ui_EnvPage_screen_init();
		lv_disp_load_scr(ui_TimePage);
}


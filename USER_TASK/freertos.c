#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "lvgl.h"
#include "ui.h"
#include "KEY.h"
#include "lcd.h"
#include "rtc.h"
#include "power.h"
#include "SPL06_001.h"
#include "LSM303.h"
#include "em70x8.h"
#include "HrAlgorythm.h"
#include "mpu6050.h"

#define GESTURE_EN 1

osThreadId_t LVGL_Timer_Handle;
const osThreadAttr_t LVGL_Timer_attributes = {
  .name = "lvgl_timer_task",
  .stack_size = 128 * 20,
  .priority = (osPriority_t) osPriorityLow,
};

osThreadId_t KEY_Handle;
const osThreadAttr_t KEY_attributes = {
  .name = "key_task",
  .stack_size = 128 * 1,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t Gesture_Handle;
const osThreadAttr_t Gesture_attributes = {
  .name = "Gesture_task",
  .stack_size = 128 * 2,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t Screen_Renew_Handle;
const osThreadAttr_t	Screen_Renew_attributes = {
  .name = "ScreenRenew_task",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityLow2,
};

osThreadId_t TopLabel_Renew_Handle;
const osThreadAttr_t	TopLabel_Renew_attributes = {
  .name = "TopLabelRenew_task",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityLow2,
};

osThreadId_t Time_Renew_Handle;
const osThreadAttr_t	Time_Renew_attributes = {
  .name = "TimeRenew_task",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityLow2,
};

osThreadId_t Env_Renew_Handle;
const osThreadAttr_t	Env_Renew_attributes = {
  .name = "EnvRenew_task",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityLow2,
};

osThreadId_t Dir_Renew_Handle;
const osThreadAttr_t	Dir_Renew_attributes = {
  .name = "DirRenew_task",
  .stack_size = 128 * 20,
  .priority = (osPriority_t) osPriorityLow2,
};

osThreadId_t HR_Renew_Handle;
const osThreadAttr_t	HR_Renew_attributes = {
  .name = "HRRenew_task",
  .stack_size = 128 * 20,
  .priority = (osPriority_t) osPriorityLow2,
};

osThreadId_t Sleep_Handle;
const osThreadAttr_t	Sleep_attributes = {
  .name = "Sleeptask",
  .stack_size = 128 * 1,
  .priority = (osPriority_t) osPriorityLow3,
};


osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 2,
  .priority = (osPriority_t) osPriorityNormal,
};

extern uint8_t ui_window;
extern uint8_t ui_timeset_pos;

uint8_t window_renew_flag = 0;
uint8_t timesetpos_renew_flag = 0;
uint8_t timeset_renew_flag = 0;

//datas
RTC_DateTypeDef previousdate;
RTC_TimeTypeDef previoustime;
RTC_DateTypeDef nowdate;
RTC_TimeTypeDef nowtime;
RTC_DateTypeDef setdate;
RTC_TimeTypeDef settime;


int8_t temperature;
int16_t attitude;
int16_t direction;
uint8_t HeartRate;
extern uint32_t time_count;


void tasks_init();
void LVGL_Timer_task( void * pvParameters );
void Gesture_Renew_task( void * pvParameters );
void KEY_task( void * pvParameters );
void Screen_Renew_task( void * pvParameters );
void TopLabel_Renew_task( void * pvParameters );
void Time_Renew_task( void * pvParameters );
void Env_Renew_task( void * pvParameters );
void Dir_Renew_task( void * pvParameters );
void HR_Renew_task( void * pvParameters );
void Sleep_task( void * pvParameters );
void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); 

void MX_FREERTOS_Init(void) 
{
	tasks_init();
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
}

void StartDefaultTask(void *argument)
{
  for(;;)
  {
    osDelay(1);
  }
}

//////////////////////functions//////////////////////


////////////////////////tasks////////////////////////

void vApplicationTickHook()
{
	lv_tick_inc(1);
}

void tasks_init()
{
	LVGL_Timer_Handle 		= osThreadNew(LVGL_Timer_task, NULL, &LVGL_Timer_attributes);
	Gesture_Handle				= osThreadNew(Gesture_Renew_task, NULL, &Gesture_attributes);
	KEY_Handle 						= osThreadNew(KEY_task, NULL, &KEY_attributes);
	Screen_Renew_Handle 	= osThreadNew(Screen_Renew_task, NULL, &Screen_Renew_attributes);
	TopLabel_Renew_Handle = osThreadNew(TopLabel_Renew_task, NULL, &TopLabel_Renew_attributes);
	Time_Renew_Handle 		= osThreadNew(Time_Renew_task, NULL, &Time_Renew_attributes);
	Env_Renew_Handle 			= osThreadNew(Env_Renew_task, NULL, &Env_Renew_attributes);
	Dir_Renew_Handle			= osThreadNew(Dir_Renew_task, NULL, &Dir_Renew_attributes);
	HR_Renew_Handle				=	osThreadNew(HR_Renew_task, NULL, &HR_Renew_attributes);
	Sleep_Handle					= osThreadNew(Sleep_task, NULL, &Sleep_attributes);
}

//LVGL_timer_task
void LVGL_Timer_task( void * pvParameters )
{
	while(1)
	{
		lv_timer_handler();
		osDelay(1);
	}
}

//Gesture_Renew_task
void Gesture_Renew_task( void * pvParameters )
{
	static uint8_t window_cut_flag;
	float pitch,roll;
	while(1)
	{
		if(GESTURE_EN)
		{
			Get_Angles(&roll,&pitch);
			if((pitch<-0.6) && (!window_cut_flag))
			{
				window_cut_flag=1;
				if(ui_timeset_pos == TIMESET_NULL)//not in TIMESET
				{
					ui_window+=1;
					if(ui_window > WINDOW_NUM)
					{ui_window = TIME_WINDOW;}
					window_renew_flag = 1;
					if(ui_window == HR_WINDOW)
					{EM7028_hrs_Enable();}
					else
					{EM7028_hrs_DisEnable();}
				}
			}
			else if((pitch>-0.1) && window_cut_flag)
			{window_cut_flag = 0;}
		}
		osDelay(10);
	}
}

//KEY_task
void KEY_task( void * pvParameters )
{
	while(1)
	{
		switch(KeyScan(0))
		{
			//KEY1
			case 1:
				if(ui_window == TIME_WINDOW)
				{
					ui_timeset_pos+=1;
					if(ui_timeset_pos>TIMESET_DAY)
					{ui_timeset_pos = TIMESET_HOURE;}
					timesetpos_renew_flag = 1;
				}
				break;
			//KEY2
			case 3:
				if(ui_timeset_pos == TIMESET_NULL)//not in TIMESET
				{
					ui_window += 1;
					if(ui_window > WINDOW_NUM)
					{ui_window = TIME_WINDOW;}
					window_renew_flag = 1;
					if(ui_window == HR_WINDOW)
					{EM7028_hrs_Enable();}
					else
					{EM7028_hrs_DisEnable();}
				}
				else//timeset
				{
					switch(ui_timeset_pos)
					{
						case TIMESET_HOURE:
							settime.Hours-=1;
							if(settime.Hours > 23)
							{settime.Hours = 23;}
							break;
						case TIMESET_MINUTE:
							settime.Minutes-=1;
							if(settime.Minutes > 59)
							{settime.Minutes = 59;}
							break;
						case TIMESET_MONTH:
							setdate.Month -= 1;
							if(setdate.Month == 0)
							{setdate.Month = 12;}
							break;
						case TIMESET_DATE:
							setdate.Date -= 1;
							if(setdate.Month == 2)
							{
								if(setdate.Date == 0)
									setdate.Date = 28;
							}
							else if((setdate.Month == 1) || (setdate.Month == 3) ||(setdate.Month == 5) ||(setdate.Month == 7) ||(setdate.Month == 8) ||(setdate.Month == 10) ||(setdate.Month == 12))
							{
								if(setdate.Date == 0)
									setdate.Date = 31;
							}
							else
							{
								if(setdate.Date == 0)
									setdate.Date = 30;
							}
							break;
						case TIMESET_DAY:
							setdate.WeekDay -= 1;
							if(setdate.WeekDay == 0)
							{setdate.WeekDay = 7;}
							break;
					}
					timeset_renew_flag=1;
				}
				break;
			//KEY3	
			case 2:
				if(ui_timeset_pos == TIMESET_NULL)//not in TIMESET
				{
					ui_window -= 1;
					if((ui_window == 0)||(ui_window > WINDOW_NUM))
					{ui_window = LOGO_WINDOW;}
					window_renew_flag = 1;
					if(ui_window == HR_WINDOW)
					{EM7028_hrs_Enable();}
					else
					{EM7028_hrs_DisEnable();}
				}
				else//timeset
				{
					switch(ui_timeset_pos)
					{
						case TIMESET_HOURE:
							settime.Hours += 1;
							if(settime.Hours > 23)
							{settime.Hours = 0;}
							break;
						case TIMESET_MINUTE:
							settime.Minutes += 1;
							if(settime.Minutes > 59)
							{settime.Minutes = 0;}
							break;
						case TIMESET_MONTH:
							setdate.Month += 1;
							if(setdate.Month > 12)
							{setdate.Month = 1;}
							break;
						case TIMESET_DATE:
							setdate.Date += 1;
							if(setdate.Month == 2)
							{
								if(setdate.Date > 28)
									setdate.Date = 0;
							}
							else if((setdate.Month == 1) || (setdate.Month == 3) ||(setdate.Month == 5) ||(setdate.Month == 7) ||(setdate.Month == 8) ||(setdate.Month == 10) ||(setdate.Month == 12))
							{
								if(setdate.Date > 31)
									setdate.Date = 0;
							}
							else
							{
								if(setdate.Date > 30)
									setdate.Date = 0;
							}
							break;
						case TIMESET_DAY:
							setdate.WeekDay += 1;
							if(setdate.WeekDay > 7)
							{setdate.WeekDay = 1;}
							break;
					}
					if(setdate.Date == 0)
					{setdate.Date = 1;}
					timeset_renew_flag=1;
				}
				break;
			//KEY_WAKE	
			case 4:
				if((ui_window == TIME_WINDOW) && (ui_timeset_pos != TIMESET_NULL))
				{
					ui_timeset_pos = TIMESET_NULL;
					timesetpos_renew_flag = 1;
					HAL_RTC_SetTime(&hrtc, &settime, RTC_FORMAT_BIN);
					HAL_RTC_SetDate(&hrtc, &setdate, RTC_FORMAT_BIN);
				}
				else
				{
					Power_DisEnable();
				}
				break;
		}
		osDelay(1);
	}
}

//Screen_Renew_task
void Screen_Renew_task( void * pvParameters )
{
	while(1)
	{
		if(window_renew_flag)
		{
			window_renew_flag = 0;
			switch(ui_window)
			{
				case TIME_WINDOW:
					lv_scr_load_anim(ui_TimePage, LV_SCR_LOAD_ANIM_MOVE_TOP, 0, 0, false);
					//LCD_Fill(0,0,50,50,YELLOW);
					break;
				case ENV_WINDOW:
					lv_scr_load_anim(ui_EnvPage, LV_SCR_LOAD_ANIM_MOVE_TOP, 0, 0, false);
					//LCD_Fill(0,0,50,50,BLUE);
					break;
				case DIR_WINDOW:
					lv_scr_load_anim(ui_DirectionPage, LV_SCR_LOAD_ANIM_MOVE_TOP, 0, 0, false);
					//LCD_Fill(0,0,50,50,WHITE);
					break;
				case HR_WINDOW:
					lv_scr_load_anim(ui_HrPage, LV_SCR_LOAD_ANIM_MOVE_TOP, 0, 0, false);
					break;
				case LOGO_WINDOW:
					lv_scr_load_anim(ui_LogoPage, LV_SCR_LOAD_ANIM_MOVE_TOP, 0, 0, false);
					//LCD_Fill(0,0,50,50,RED);
					break;
			}
		}
		if(timesetpos_renew_flag)
		{
			timesetpos_renew_flag = 0;
			switch(ui_timeset_pos)
			{
				case TIMESET_NULL:
					lv_obj_set_style_bg_opa(ui_LabelDay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelTimeHour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelTimeMin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelDateMonth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelDateDate, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					//LCD_Fill(0,0,135,240,BLACK);
					//LCD_Fill(0,0,50,50,YELLOW);
					break;
				case TIMESET_HOURE:
					lv_obj_set_style_bg_opa(ui_LabelDay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelTimeHour, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
					//LCD_Fill(0,50,50,100,YELLOW);
					//LCD_Fill(50,150,100,200,BLACK);
					break;
				case TIMESET_MINUTE:
					lv_obj_set_style_bg_opa(ui_LabelTimeHour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelTimeMin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
					//LCD_Fill(50,0,100,50,YELLOW);
					//LCD_Fill(0,50,50,100,BLACK);
					break;
				case TIMESET_MONTH:
					lv_obj_set_style_bg_opa(ui_LabelTimeMin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelDateMonth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
					//LCD_Fill(50,50,100,100,YELLOW);
					//LCD_Fill(50,0,100,50,BLACK);
					break;
				case TIMESET_DATE:
					lv_obj_set_style_bg_opa(ui_LabelDateMonth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelDateDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT); 
					//LCD_Fill(0,150,50,200,YELLOW);
					//LCD_Fill(50,50,100,100,BLACK);
					break;
				case TIMESET_DAY:
					lv_obj_set_style_bg_opa(ui_LabelDateDate, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
					lv_obj_set_style_bg_opa(ui_LabelDay, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
					//LCD_Fill(50,150,100,200,YELLOW);
					//LCD_Fill(0,150,50,200,BLACK);
					break;
			}
		}
		osDelay(100);
	}
}

//TopLabel_Renew_task
void TopLabel_Renew_task( void * pvParameters )
{
	uint8_t strbuff[5];
	uint8_t power;
	while(1)
	{
		power = PowerCalculate();
		sprintf(strbuff,"%d%%",power);
		if(ui_window == TIME_WINDOW)
		{
			lv_label_set_text(ui_bat, strbuff);
			lv_arc_set_value(ui_ArcBat, power);
		}
		
		if(power>=90)
		{
			lv_label_set_text(ui_label_top_battery_TP, LV_SYMBOL_BATTERY_FULL);
			//lv_obj_set_style_text_font(ui_label_top_battery_TP, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
			lv_label_set_text(ui_label_top_battery_EP, LV_SYMBOL_BATTERY_FULL);
			lv_label_set_text(ui_label_top_battery_DP, LV_SYMBOL_BATTERY_FULL);
			lv_label_set_text(ui_label_top_battery_HP, LV_SYMBOL_BATTERY_FULL);
		}
		else if(power>=70)
		{
			lv_label_set_text(ui_label_top_battery_TP, LV_SYMBOL_BATTERY_3);
			lv_label_set_text(ui_label_top_battery_EP, LV_SYMBOL_BATTERY_3);
			lv_label_set_text(ui_label_top_battery_DP, LV_SYMBOL_BATTERY_3);
			lv_label_set_text(ui_label_top_battery_HP, LV_SYMBOL_BATTERY_3);
		}
		else if(power>=50)
		{
			lv_label_set_text(ui_label_top_battery_TP, LV_SYMBOL_BATTERY_2);
			lv_label_set_text(ui_label_top_battery_EP, LV_SYMBOL_BATTERY_2);
			lv_label_set_text(ui_label_top_battery_DP, LV_SYMBOL_BATTERY_2);
			lv_label_set_text(ui_label_top_battery_HP, LV_SYMBOL_BATTERY_2);
		}
		else if(power>=30)
		{
			lv_label_set_text(ui_label_top_battery_TP, LV_SYMBOL_BATTERY_1);
			lv_label_set_text(ui_label_top_battery_EP, LV_SYMBOL_BATTERY_1);
			lv_label_set_text(ui_label_top_battery_DP, LV_SYMBOL_BATTERY_1);
			lv_label_set_text(ui_label_top_battery_HP, LV_SYMBOL_BATTERY_1);
		}
		else
		{
			lv_label_set_text(ui_label_top_battery_TP, LV_SYMBOL_BATTERY_EMPTY);
			lv_label_set_text(ui_label_top_battery_EP, LV_SYMBOL_BATTERY_EMPTY);
			lv_label_set_text(ui_label_top_battery_DP, LV_SYMBOL_BATTERY_EMPTY);
			lv_label_set_text(ui_label_top_battery_HP, LV_SYMBOL_BATTERY_EMPTY);
		}
	
		//charging
		if(ChargeCheck())
		{
			lv_obj_move_foreground(ui_label_top_charge_TP);
			lv_obj_move_foreground(ui_label_top_charge_EP);
			lv_obj_move_foreground(ui_label_top_charge_DP);
			lv_obj_move_foreground(ui_label_top_charge_HP);
		}
		else
		{
			lv_obj_move_background(ui_label_top_charge_TP);
			lv_obj_move_background(ui_label_top_charge_EP);
			lv_obj_move_background(ui_label_top_charge_DP);
			lv_obj_move_background(ui_label_top_charge_HP);
		}
		osDelay(1000);
	}
}

//TimeDataRenew
void Time_Renew_task( void * pvParameters )
{
	uint8_t strbuff[10];
	//static uint8_t flash_flag = 1;
	while(1)
	{
		HAL_RTC_GetTime(&hrtc,&nowtime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&nowdate,RTC_FORMAT_BIN);
		if((ui_window == TIME_WINDOW) && (ui_timeset_pos == TIMESET_NULL))
		{
			if(previoustime.Hours != nowtime.Hours)
			{
				sprintf(strbuff,"%02d", nowtime.Hours);
				lv_label_set_text(ui_LabelTimeHour, strbuff);
			}
			if(previoustime.Minutes != nowtime.Minutes)
			{
				sprintf(strbuff,"%02d", nowtime.Minutes);
				lv_label_set_text(ui_LabelTimeMin, strbuff);
			}
			if(previousdate.Month != nowdate.Month)
			{
				sprintf(strbuff,"%02d", nowdate.Month);//BCD
				lv_label_set_text(ui_LabelDateMonth, strbuff);
			}
			if(previousdate.Date != nowdate.Date)
			{
				sprintf(strbuff,"%02d", nowdate.Date);
				lv_label_set_text(ui_LabelDateDate, strbuff);
			}
			if(previousdate.WeekDay != nowdate.WeekDay)
			{
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
//			if(flash_flag)
//			{
//				flash_flag = 0;
//				lv_obj_set_style_text_opa(ui_Label11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//			}
//			else
//			{
//				flash_flag = 1;
//				lv_obj_set_style_text_opa(ui_Label11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//			}
			HAL_RTC_GetTime(&hrtc,&settime,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,&setdate,RTC_FORMAT_BIN);
		}
		else if((ui_window == TIME_WINDOW) && (ui_timeset_pos != TIMESET_NULL))//renew the time setting
		{
			if(timeset_renew_flag)
			{
				timeset_renew_flag = 0;
				switch(ui_timeset_pos)
				{
					case TIMESET_HOURE:
						sprintf(strbuff,"%02d",settime.Hours);
						lv_label_set_text(ui_LabelTimeHour,strbuff);
						break;
					case TIMESET_MINUTE:
						sprintf(strbuff,"%02d",settime.Minutes);
						lv_label_set_text(ui_LabelTimeMin,strbuff);
						break;
					case TIMESET_MONTH:
						sprintf(strbuff,"%02d",setdate.Month);
						lv_label_set_text(ui_LabelDateMonth,strbuff);
						break;
					case TIMESET_DATE:
						sprintf(strbuff,"%02d",setdate.Date);
						lv_label_set_text(ui_LabelDateDate,strbuff);
						break;
					case TIMESET_DAY:
						switch(setdate.WeekDay)
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
						break;
				}
			}
		}
		HAL_RTC_GetTime(&hrtc,&previoustime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&previousdate,RTC_FORMAT_BIN);
		osDelay(100);
	}
}

void Env_Renew_task( void * pvParameters )
{
	uint8_t strbuff[5];
	while(1)
	{
		if(ui_window == ENV_WINDOW)
		{
			sprintf(strbuff,"%.1f",Temperature_Calculate());
			lv_label_set_text(ui_label_temperature, strbuff);
			sprintf(strbuff,"%.1fm",Altitude_Calculate());
			lv_label_set_text(ui_label_Altitude, strbuff);
		}
		osDelay(1000);
	}
}

void Dir_Renew_task( void * pvParameters )
{
	uint8_t strbuff[5];
	int16_t Xa,Ya,Za,Xm,Ym,Zm;
	float Azimuth;
	while(1)
	{
		if(ui_window == DIR_WINDOW)
		{
				LSM303_ReadAcceleration(&Xa, &Ya, &Za);
				LSM303_ReadMagnetic(&Xm, &Ym, &Zm);
				Azimuth=360-Azimuth_Calculate(Xa, Ya, Za, Xm, Ym, Zm)+10;//30 compensation
				if(Azimuth<0)
				{Azimuth+=360;}
				else if(Azimuth>=360)
				{Azimuth-=360;}
				sprintf(strbuff,"%.0f ",Azimuth);
				lv_label_set_text(ui_Label_Direction, strbuff);
				Azimuth+=90;
				Azimuth = 180-Azimuth;
				if(Azimuth<0)
				{Azimuth+=360;}
				else if(Azimuth>=360)
				{Azimuth-=360;}
				lv_meter_set_indicator_value(ui_meter_compass,ui_needle_compass,(int16_t)Azimuth);
				
		}
		osDelay(100);
	}
}

//HR
void HR_Renew_task( void * pvParameters )
{
	uint8_t strbuff[5];
	uint8_t temp;
	uint16_t dat;
	static uint8_t HR_List[5];
	while(1)
	{
		if(ui_window == HR_WINDOW)
		{
			dat = EM7028_ReadOneReg(HRS1_DATA0_H);
			dat <<= 8;
			dat |= EM7028_ReadOneReg(HRS1_DATA0_L);
			HeartRate = HR_Calculate(dat,time_count);
			sprintf(strbuff, "HR: %d", HeartRate);
			lv_label_set_text(ui_LabelHr, strbuff);
		}
		osDelay(10);
	}
}

//Sleep_task
void Sleep_task( void * pvParameters )
{
	uint16_t sleep_timecount=0;
	while(1)
	{
		if(!window_renew_flag && !timesetpos_renew_flag && !timeset_renew_flag && (ui_window != HR_WINDOW))
		{sleep_timecount+=1;}
		else
		{sleep_timecount = 0;}
		if(sleep_timecount>=15000)//15s turn off(no any action)
		{sleep_timecount = 0;Power_DisEnable();}
		osDelay(1);
	}
}

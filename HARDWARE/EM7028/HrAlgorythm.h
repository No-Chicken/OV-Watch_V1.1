#ifndef __HRALGORYTHM_H__
#define __HRALGORYTHM_H__

#include "main.h"
//algorythm1
#define HR_MAX				110
#define HR_MIN				50
#define HR_THRE_VALUE 19000
#define WAIT_TIMES		2

//algorythm2
#define HR_COUNTING_TIME 	5000
#define RISE 							1
#define FALL 							0

typedef struct
{
	uint16_t HR_Data;
	uint16_t HR_Time;
}HR_Data_t;


void enque(uint32_t dat, uint16_t *List, uint8_t lenth);
uint8_t Hr_Filter(uint8_t *HrList, uint8_t lenth);
uint16_t HR_Calculate(uint16_t present_dat,uint32_t present_time);
uint8_t Hr_Peak_time(uint16_t Data_present, uint16_t Data_last, uint8_t * count_flag, uint16_t * count);
uint8_t HR_Peaks_Count(uint16_t Data_present, uint16_t Data_previous, uint8_t * counting_flag);
#endif
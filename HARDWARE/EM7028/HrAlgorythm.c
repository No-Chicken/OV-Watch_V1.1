#include "HrAlgorythm.h"
#include "string.h"
//get in List
void enque(uint32_t dat, uint16_t *List, uint8_t lenth)
{
	uint8_t i;
	for(i=0;i<lenth-1;i++)
	{List[lenth-1-i] = List[lenth-2-i];}
	List[0] = dat;
}


//limit the div
//average
uint8_t Hr_Filter(uint8_t *HrList, uint8_t lenth)
{
	uint32_t temp;
	uint8_t i;
	for(i = 0;i<lenth;i++)
	{
		temp += HrList[i];
	}
	temp /= lenth;
	
	for(i = 0;i<lenth;i++)
	{
		if(HrList[i]>temp)
		{
			if((HrList[i] - temp) > 4)
			{
				HrList[i] = temp;
				temp = Hr_Filter(HrList,lenth);
			}
		}
		else
		{
			if((temp - HrList[i]) > 4)
			{	
				HrList[i] = temp;
				temp = Hr_Filter(HrList,lenth);
			}
		}
	}
	return temp;
}

uint8_t Hr_Ave_Filter(uint16_t *HrList, uint8_t lenth)
{
	uint32_t ave;
	uint8_t i;
	for(i = 0;i<lenth;i++)
	{
		ave += HrList[i];
	}
	ave /= lenth;
}

/**************************************************************************
*paraments	: present_dat,present_time
*return     :	HeartRate
*detail     :	
**************************************************************************/
uint16_t HR_Calculate(uint16_t present_dat,uint32_t present_time)
{
	static uint16_t datas[7];
	static uint16_t times[7];
	static uint16_t peaks_time[]={0,0};
	static uint16_t HR_List[9];
	static uint8_t HR=0;
	uint8_t i;
	
	enque(present_dat,datas,sizeof(datas)/sizeof(uint16_t));
	enque(present_time,times,sizeof(times)/sizeof(uint16_t));
	if((datas[3]>=datas[2]) && (datas[3]>=datas[1]) && (datas[3]>datas[0]) && (datas[3]>=datas[4]) && (datas[3]>=datas[5]) && (datas[3]>datas[6]))
	{
			if((times[3]-peaks_time[0])>425)
			{
					peaks_time[1] = peaks_time[0];
					peaks_time[0] = times[3];
					enque(60000/(peaks_time[0]-peaks_time[1]),HR_List,sizeof(HR_List)/sizeof(uint16_t));
					if(HR_List[5]!=0)
					{HR = Hr_Ave_Filter(HR_List,sizeof(HR_List)/sizeof(uint16_t));}
			}
	}
	return HR;
}


/**************************************************************************
*paraments	: 
*return     :	HeartRate
*detail     :	
							find the point that is after the peak
							it is finding the trend of fall, not rise
							it use the time between 2 peaks to culculate the Heart period
							this Algorythm is RAM saving 
							this Algorythm has significant HR error(+-5~10/min)
							Hr = 60000ms / period
**************************************************************************/
uint8_t Hr_Peak_time(uint16_t Data_present, uint16_t Data_Previous, uint8_t * count_flag, uint16_t * time_count)
{
	
	static uint8_t down_wait = WAIT_TIMES;//
	static uint8_t rise_flag;
	static uint8_t fall_flag;
	static uint8_t start_flag = 1;
	static uint16_t period;
	uint8_t Hr;

	if(Data_present > HR_THRE_VALUE)
	{
		if(Data_present > Data_Previous)
		{    
			down_wait = WAIT_TIMES;
			rise_flag = 1;
			fall_flag = 0;
		}
		else if(Data_present < Data_Previous)
		{
			down_wait -= 1;
			if((down_wait == 0)&&(rise_flag == 1))
			{
				if(start_flag)
				{
					*count_flag = 1;
					start_flag = 0;
				}
				else
				{
					*count_flag = 0;
					start_flag = 1;
					period = *time_count;
					*time_count = 0;
				}
				down_wait = WAIT_TIMES;
				rise_flag = 0;
				fall_flag = 1;
			}
		}
		Hr = 60000/period;
		//Hr = period;
		return Hr;	
	}
	
	/*
	static uint8_t trend_present = FALL;
	static uint8_t trend_previous = RISE;
	static uint8_t Hr;
	uint16_t period;
	trend_previous = trend_present;
	if(Data_present > Data_Previous)
	{
		trend_present = RISE; 
	}
	else if(Data_present < Data_Previous)
	{
		trend_present = FALL;
	}
	if((trend_present == FALL) && (trend_previous == RISE))
	{
		if(*count_flag==0)
		{
			*count_flag = 1;
		}
		else
		{
			*count_flag = 0;
			period = *time_count;
			*time_count = 0;
			Hr = period;
		}
	}
	return Hr;
	*/
}

/*******************************************************************
*paraments	: 
*return     :	HeartRate
*detail     :	during a period, count peaks number, 
							then calculate how much would 1 min has
							long time cost, 
							and 1 peak count error can cause significant HR error
*******************************************************************/
uint8_t HR_Peaks_Count(uint16_t Data_present, uint16_t Data_previous, uint8_t * counting_flag)
{
	static uint8_t peak_count;
	static uint8_t trend_present = FALL;
	static uint8_t trend_previous = RISE;
	static uint8_t Hr;
	trend_previous = trend_present;
	if(Data_present > Data_previous)
	{
		trend_present = RISE; 
	}
	else if(Data_present < Data_previous)
	{
		trend_present = FALL;
	}
	if(*counting_flag)
	{
		if((trend_present == FALL) && (trend_previous == RISE))
		{peak_count += 1;}
	}
	else
	{
		Hr = peak_count * (60000/HR_COUNTING_TIME);
		peak_count = 0;
		*counting_flag = 1;
	}
	return Hr;
}

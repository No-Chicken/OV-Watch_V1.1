#include "delay.h"
#include "sys.h"
 
//cu
void delay_us(u32 nus)
{		
	u32 i;
	for(i=0;i<nus*20;i++);
}

//��ʱnms
//nms:Ҫ��ʱ��ms��
void delay_ms(u16 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}

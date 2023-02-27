#include "KEY.h"
#include "cmsis_os.h"

/******************************************************************
*key scan, mode 1 enable Continuous press while mode 0 disable it
*******************************************************************/
void KEY_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

unsigned char KeyScan( unsigned char mode )
{
	static uint8_t key_up = 1;
	unsigned char keyvalue;
	if(mode) key_up = 1;
	if( key_up && ( (!KEY1) || (!KEY2) || (!KEY3) || (KEY4) ) )
	{
		osDelay(3);//ensure the key is down
		if(!KEY1) keyvalue = 1;
		else if(!KEY2) keyvalue = 2;
		else if(!KEY3) keyvalue = 3;
		else if(KEY4) keyvalue = 4;
		if(keyvalue) key_up = 0;
	}
	else
	{
		osDelay(3);//ensure the key is up
		if( KEY1 && KEY2 && KEY3 && !KEY4)
			key_up = 1;
	}
	return keyvalue;
}
#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f4xx_hal.h"

#define KEY1 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)
#define KEY4 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)//key_wake
#define KEY3 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)
#define KEY2 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)

#define WAKE_PORT				GPIOA
#define WAKE_PIN				GPIO_PIN_4

void KEY_Init();
unsigned char KeyScan( unsigned char mode );

#endif
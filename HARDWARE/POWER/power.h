#ifndef _POWER_H_
#define _POWER_H_

#include "stm32f4xx_hal.h"
#include "rtc.h"

#define BAT_CHECK_PORT	GPIOA
#define BAT_CHECK_PIN		GPIO_PIN_1

#define CHARGE_PORT			GPIOA
#define CHARGE_PIN			GPIO_PIN_2

#define POWER_PORT			GPIOA
#define POWER_PIN				GPIO_PIN_3

void Power_Pins_Init();
void Power_Enable();
void Power_DisEnable();
float BatCheck();
uint8_t ChargeCheck();
uint8_t PowerCalculate();

#endif
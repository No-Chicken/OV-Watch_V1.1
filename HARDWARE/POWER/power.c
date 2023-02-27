#include "power.h"
#include "adc.h"

#define INTERNAL_RES 0.128
#define CHARGING_CUR 1

void Power_Pins_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(POWER_PORT, POWER_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = POWER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(POWER_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : PA2 */
  GPIO_InitStruct.Pin = CHARGE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CHARGE_PORT, &GPIO_InitStruct);
	
}

void Power_Enable()
{
	HAL_GPIO_WritePin(POWER_PORT,POWER_PIN,GPIO_PIN_SET);
}

void Power_DisEnable()
{
	HAL_GPIO_WritePin(POWER_PORT,POWER_PIN,GPIO_PIN_RESET);
}

uint8_t ChargeCheck()//1:charging
{
	return HAL_GPIO_ReadPin(CHARGE_PORT,CHARGE_PIN);
}

float BatCheck()
{
	uint16_t dat;
	float BatVoltage;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,5);
	dat = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	BatVoltage = dat *2 *3.3 /4096;
	return BatVoltage;
}

uint8_t PowerCalculate()
{
	uint8_t power;
	float voltage;
	voltage = BatCheck();
	
	if(ChargeCheck())
	{voltage -= INTERNAL_RES * CHARGING_CUR;}
	
	/*
	if(Voltage >= 4.2)
	{power = 100;}
	else if(Voltage >= 3.68)
	{power = -294.87*Voltage*Voltage + 2504.5*Voltage - 5217.1;}
	else if(Voltage < 3.68 && Voltage >3.5)
	{power = 10;}
	else if(Voltage > 3.5 && Voltage <3.2)
	{power = 5;}
	*/
	
	/*
	if((voltage >= 4.15))
	{power = 100;}
	else if(voltage >= 4.12 && voltage <4.15)
	{power = 95;}
	else if(voltage >= 4.08 && voltage <4.12)
	{power = 90;}
	else if(voltage >= 4.03 && voltage <4.08)
	{power = 85;}
	else if(voltage >= 3.97 && voltage <4.03)
	{power = 80;}
	else if(voltage >= 3.93 && voltage <3.97)
	{power = 75;}
	else if(voltage >= 3.90 && voltage <3.93)
	{power = 70;}
	else if(voltage >= 3.87 && voltage <3.90)
	{power = 65;}
	else if(voltage >= 3.84 && voltage <3.87)
	{power = 60;}
	else if(voltage >= 3.81 && voltage <3.84)
	{power = 55;}
	else if(voltage >= 3.79 && voltage <3.81)
	{power = 50;}
	else if(voltage >= 3.77 && voltage <3.79)
	{power = 45;}
	else if(voltage >= 3.76 && voltage <3.77)
	{power = 40;}
	else if(voltage >= 3.74 && voltage <3.76)
	{power = 35;}
	else if(voltage >= 3.73 && voltage <3.74)
	{power = 30;}
	else if(voltage >= 3.72 && voltage <3.73)
	{power = 25;}
	else if(voltage >= 3.71 && voltage <3.72)
	{power = 20;}
	else if(voltage >= 3.69 && voltage <3.71)
	{power = 15;}
	else if(voltage >= 3.65 && voltage <3.69)
	{power = 10;}
	else if(voltage >= 3.63 && voltage <3.65)
	{power = 5;}
	*/
	
	if((voltage >= 4.2))
	{power = 100;}
	else if(voltage >= 4.06 && voltage <4.2)
	{power = 90;}
	else if(voltage >= 3.98 && voltage <4.06)
	{power = 80;}
	else if(voltage >= 3.92 && voltage <3.98)
	{power = 70;}
	else if(voltage >= 3.87 && voltage <3.92)
	{power = 60;}
	else if(voltage >= 3.82 && voltage <3.87)
	{power = 50;}
	else if(voltage >= 3.79 && voltage <3.82)
	{power = 40;}
	else if(voltage >= 3.77 && voltage <3.79)
	{power = 30;}
	else if(voltage >= 3.74 && voltage <3.77)
	{power = 20;}
	else if(voltage >= 3.68 && voltage <3.74)
	{power = 10;}
	else if(voltage >= 3.45 && voltage <3.68)
	{power = 5;}
	return power;
}




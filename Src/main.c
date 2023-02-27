#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "rtc.h"
#include "gpio.h"
#include "tim.h"
#include "sys.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "ui.h"
#include "lcd.h"
#include "lcd_init.h"
#include "KEY.h"
#include "power.h"
#include "SPL06_001.h"
#include "LSM303.h"
#include "em70x8.h"
#include "mpu6050.h"

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

uint32_t time_count;

int main(void)
{
  
	uint8_t num=5;
	uint8_t strbuff[10];
	float pitch,roll,yaw; 		
	
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_ADC1_Init();
	MX_TIM2_Init();
	HAL_TIM_Base_Start_IT(&htim2);
	Power_Pins_Init();
	Power_Enable();//power on
	KEY_Init();
	LCD_Init();
	while(SPL_init()&&num)
	{
		num--;
		HAL_Delay(100);
	}
	num = 5;
	while(LSM303DLH_Init()&&num)
	{
		num--;
		HAL_Delay(100);
	}
	num = 5;
	while(EM7028_hrs_init()&&num)
	{
		num--;
		HAL_Delay(100);
	}
	num = 5;
	while(MPU_Init()&&num)
	{
		num--;
		HAL_Delay(100);
	}
//	num = 5;
//	while(mpu_dmp_init()&&num)
//	{
//		num--;
//		HAL_Delay(100);
//	}
	//LCD_Fill(0,0,135,240,BLACK);
	lv_init();
	lv_port_disp_init();
	ui_init();
  osKernelInitialize();
  MX_FREERTOS_Init();
  osKernelStart();
  while (1)
  {
		
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  
	if(htim->Instance == TIM2)
	{
		time_count+=1;
	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


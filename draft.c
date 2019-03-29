#include "main.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "stm32l476g_discovery_audio.h"


void SystemClock_Config(void);

volatile int count = 0;
volatile int running = 0;
volatile uint16_t time = 0;
volatile int split_idx;

volatile uint16_t *output_buffer;

const uint16_t idle_msg[7] = {'0','0','0','0','0','0','0'};

typedef enum {IDLE=JOY_UP, RECORD=JOY_DOWN, PLAYBACK=JOY_RIGHT} state_t;

volatile uint16_t audio_buffer[1024];
const uint32_t buffer_size = 1024;

void output_handler(void) {}

void input_handler(JOYState_TypeDef next_state) {
    switch (next_state) {
    case IDLE:
			BSP_AUDIO_IN_Stop();
		  BSP_LED_Off(LED_RED);
      BSP_LED_Off(LED_GREEN);
      break;
    case RECORD:
			BSP_AUDIO_IN_Record(audio_buffer, buffer_size);
			BSP_LED_On(LED_RED);
      break;
    case PLAYBACK:
			BSP_LED_On(LED_GREEN);
    default:
      break;
  }
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
  
  
  HAL_Init();
  SystemClock_Config();
  
  BSP_LED_Init(LED_RED);
  BSP_LED_Init(LED_GREEN);
  BSP_JOY_Init(JOY_MODE_EXTI);
  BSP_LCD_GLASS_Init();
  
	BSP_AUDIO_IN_Init(SAI_AUDIO_FREQUENCY_16K, DEFAULT_AUDIO_IN_BIT_RESOLUTION, DEFAULT_AUDIO_IN_CHANNEL_NBR);
	
//  SystemCoreClockUpdate(); 
//  SysTick_Config(SystemCoreClock / 100);
  
  
  while (1) {
    output_handler();
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int seg_array[20][7]={{A_Pin,B_Pin,C_Pin, D_Pin, E_Pin, F_Pin,G_Pin},
		{B_Pin, C_Pin,A_Pin,D_Pin, E_Pin, F_Pin,G_Pin},
		{A_Pin, B_Pin, G_Pin, E_Pin, D_Pin,C_Pin,F_Pin},
		{A_Pin,B_Pin,C_Pin, D_Pin,G_Pin,E_Pin, F_Pin},
		{B_Pin,C_Pin, F_Pin,G_Pin,A_Pin,D_Pin,E_Pin},
		{A_Pin,C_Pin, D_Pin, F_Pin,G_Pin,B_Pin,E_Pin},
		{A_Pin,C_Pin, D_Pin, E_Pin, F_Pin,G_Pin,B_Pin},
		{A_Pin,B_Pin,C_Pin,D_Pin, E_Pin, F_Pin,G_Pin},
		{A_Pin,B_Pin,C_Pin, D_Pin, E_Pin, F_Pin,G_Pin},
		{A_Pin,B_Pin,C_Pin, D_Pin, F_Pin,G_Pin, E_Pin},
		{a_Pin,b_Pin,c_Pin, d_Pin, e_Pin, f_Pin,g_Pin},
		{b_Pin, c_Pin,a_Pin,d_Pin, e_Pin, f_Pin,g_Pin},
		{a_Pin, b_Pin, g_Pin, e_Pin, d_Pin,c_Pin,f_Pin},
		{a_Pin,b_Pin,c_Pin, d_Pin,g_Pin,e_Pin, f_Pin},
		{b_Pin,c_Pin, f_Pin,g_Pin,a_Pin,d_Pin,e_Pin},
		{a_Pin,c_Pin, d_Pin, f_Pin,g_Pin,b_Pin,e_Pin},
		{a_Pin,c_Pin, d_Pin, e_Pin, f_Pin,g_Pin,b_Pin},
		{a_Pin,b_Pin,c_Pin,d_Pin, e_Pin, f_Pin,g_Pin},
		{a_Pin,b_Pin,c_Pin, d_Pin, e_Pin, f_Pin,g_Pin},
		{a_Pin,b_Pin,c_Pin, d_Pin, f_Pin,g_Pin, e_Pin}};




void turnonLED(int arr,int num, int count)
{
	if(count<0) return;
	if(count>num) HAL_GPIO_WritePin(GPIOA, seg_array[arr][count],1);
	if(count<=num) HAL_GPIO_WritePin(GPIOA, seg_array[arr][count],0);
	turnonLED(arr,num,--count);
}
void display7SEG(int flag,int num)
{
	if (flag==1)
	{
		num+=10;
		switch(num)
		{
		case 10:
			turnonLED(num,5,6);
			break;
		case 11:
				turnonLED(num,1,6);
				break;
		case 12:
				turnonLED(num,4,6);
				break;
		case 13:
				turnonLED(num,4,6);
				break;
		case 14:
				turnonLED(num,3,6);
				break;
		case 15:
				turnonLED(num,4,6);
				break;
		case 16:
				turnonLED(num,5,6);
				break;
		case 17:
				turnonLED(num,2,6);
				break;
		case 18:
				turnonLED(num,6,6);
				break;
		case 19:
				turnonLED(num,5,6);
				break;
		}
	}
	if(flag==2)
	{
		switch(num)
		{
		case 0:
			turnonLED(num,5,6);
			break;
		case 1:
				turnonLED(num,1,6);
				break;
		case 2:
				turnonLED(num,4,6);
				break;
		case 3:
				turnonLED(num,4,6);
				break;
		case 4:
				turnonLED(num,3,6);
				break;
		case 5:
				turnonLED(num,4,6);
				break;
		case 6:
				turnonLED(num,5,6);
				break;
		case 7:
				turnonLED(num,2,6);
				break;
		case 8:
				turnonLED(num,6,6);
				break;
		case 9:
				turnonLED(num,5,6);
				break;
		}
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
int count=10;
setTimer(100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(timerflag==1)
	  {
		  if(count>7)
		  {
			  HAL_GPIO_WritePin(GPIOB, red_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, yellow_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, green_Pin, 0);
			  display7SEG(1,count-7-1);
		  }
		  if(count<=7 && count>5)
		  {
			  HAL_GPIO_WritePin(GPIOB, red_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, yellow_Pin, 0);
			  HAL_GPIO_WritePin(GPIOB, green_Pin, 1);
			  display7SEG(1,count-6);
		  }
		  if (count<=5 && count>0)
		  {
			  HAL_GPIO_WritePin(GPIOB, red_Pin, 0);
			  HAL_GPIO_WritePin(GPIOB, yellow_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, green_Pin, 1);
			  display7SEG(1,count-1);
		  }
		  if(count>5)
		  {
			  HAL_GPIO_WritePin(GPIOB, RED_Pin, 0);
			  HAL_GPIO_WritePin(GPIOB, YELLOW_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, GREEN_Pin, 1);
			  display7SEG(2,count-5-1);
		  }
		  if(count<=5 && count>2)
		  {
			  HAL_GPIO_WritePin(GPIOB, RED_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, YELLOW_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, GREEN_Pin, 0);
			  display7SEG(2,count-3);
		  }
		  if(count<=2 && count>0)
		  {
			  HAL_GPIO_WritePin(GPIOB, RED_Pin, 1);
			  HAL_GPIO_WritePin(GPIOB, YELLOW_Pin, 0);
			  HAL_GPIO_WritePin(GPIOB, GREEN_Pin, 1);
			  display7SEG(2,count-1);
		  }
		  if(count==0) count=10;
		  else count--;
		  setTimer(100);
	  }
	  timerRun();
	  HAL_Delay(10) ;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A_Pin|B_Pin|C_Pin|D_Pin
                          |E_Pin|F_Pin|G_Pin|a_Pin
                          |b_Pin|c_Pin|d_Pin|e_Pin
                          |f_Pin|g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RED_Pin|YELLOW_Pin|GREEN_Pin|red_Pin
                          |yellow_Pin|green_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin D_Pin
                           E_Pin F_Pin G_Pin a_Pin
                           b_Pin c_Pin d_Pin e_Pin
                           f_Pin g_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|D_Pin
                          |E_Pin|F_Pin|G_Pin|a_Pin
                          |b_Pin|c_Pin|d_Pin|e_Pin
                          |f_Pin|g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_Pin YELLOW_Pin GREEN_Pin red_Pin
                           yellow_Pin green_Pin */
  GPIO_InitStruct.Pin = RED_Pin|YELLOW_Pin|GREEN_Pin|red_Pin
                          |yellow_Pin|green_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

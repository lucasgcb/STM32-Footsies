/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "ARM_inits.h"
#include "NOKIA5110_fb.h"
#include "Botao1FSM.h"
#include "Interpreter1FSM.h"
#include "MenuFSM.h"
#include "P1_FSM.h"
#include "P1_ViewFSM.h"
#include "P2_FSM.h"
#include "P2_ViewFSM.h"
#include "Bot.h"
#include "Detector.h"
//// A fazer
//// Arena
//// Ver P2 -> ativar ADC2. Vai apagar tudo
//// Rounds Arena
//// Frame counter -> danese
//// Colisoes -> 16 x 16 dos brother mesmo

osThreadId defaultTaskHandle;
osThreadId InterpreterTaskHandle;
osThreadId botaoTaskHandle;
osThreadId MenuTaskHandle;
osThreadId P1TaskHandle;
osThreadId P1ViewHandle;
osThreadId P2TaskHandle;
osThreadId P2ViewHandle;
osThreadId Bot1Handle;
void StartDefaultTask(void const * argument);
void InputInterpreter(void const * argument);
void Menu(void const * argument);
void P1(void const *argument);
void P1View(void const *argument);
void P2(void const *argument);
void Bot1(void const *argument);
void P2View(void const *argument);
// Function Pointer for State Machines


int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();

  HAL_ADC_Start (&hadc1);
  MX_RTC_Init();
  osThreadDef(InterpreterTask, InputInterpreter, osPriorityNormal, 0, 32);
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 64);
  osThreadDef(botaoTask, ObservaBotao, osPriorityNormal, 0, 32);
  osThreadDef(MenuTask, Menu, osPriorityNormal, 0, 128);
  osThreadDef(P1Task, P1, osPriorityNormal, 0, 64);
  osThreadDef(P1ViewTask, P1View, osPriorityNormal, 0, 64);
  osThreadDef(P2Task, P2, osPriorityNormal, 0, 64);
  osThreadDef(P2ViewTask, P2View, osPriorityNormal, 0, 64);
  osThreadDef(Bot1Task, Bot1, osPriorityNormal, 0, 64);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  InterpreterTaskHandle = osThreadCreate(osThread(InterpreterTask), NULL);
  botaoTaskHandle = osThreadCreate(osThread(botaoTask), NULL);
  MenuTaskHandle = osThreadCreate(osThread(MenuTask), NULL);
  P1TaskHandle = osThreadCreate(osThread(P1Task), NULL);
  P1ViewHandle = osThreadCreate(osThread(P1ViewTask), NULL);
  P2TaskHandle = osThreadCreate(osThread(P2Task), NULL);
  P2ViewHandle = osThreadCreate(osThread(P2ViewTask), NULL);
  Bot1Handle = osThreadCreate(osThread(Bot1Task), NULL);
  osKernelStart();
  
  while (1)
  {
  }
}

void Bot1(void const * argument)
{
	input2 = xSemaphoreCreateBinary();
	xSemaphoreGive(input2);
	for(;;)
	{
		osDelay(1);
		Rodar_Maquina_Bot1();
	}
}



void P2(void const * argument)
{
	for(;;)
	{
		osDelay(1);
		Rodar_Maquina_P2();
	}
}

void P2View(void const *argument)
{
	while(1)
	{
		Rodar_Maquina_P2View();
	}
}

void P1(void const * argument)
{
	for(;;)
	{
		osDelay(1);
		Rodar_Maquina_P1();
	}
}

void P1View(void const *argument)
{
	while(1)
	{
		Rodar_Maquina_P1View();
	}
}
void Menu(void const * argument)
{
	for(;;)
	{
		Rodar_Maquina_Menu();
	}
}

void InputInterpreter(void const * argument)
{
	input1 = xSemaphoreCreateBinary();
	xSemaphoreGive(input1);
	for(;;)
	{
		Rodar_Maquina_Interpretador();
	}
}
void StartDefaultTask(void const * argument)
{
	 tela = xSemaphoreCreateBinary();
	  inic_LCD();
	  limpa_LCD();
	  xSemaphoreGive(tela);
	  	// --------------------------------------------------------------------------------------
	  	// inicializa tela


  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(41);
	  detectarColisao();
	  imprime_LCD();
  }
  /* USER CODE END 5 */
}
void ObservaBotao(void const *argument)
{
	while(1)
	{
		Rodar_Maquina_Botao1();
	}
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

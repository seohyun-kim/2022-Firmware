typedef volatile unsigned int  V_UINT32;
#define RATE 3600000

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_
#endif

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_
#include "def.h"
#include "stm32f7xx_hal.h"
static void SystemClock_Config(void);
#endif



void hwInit(void);
void MyApp();




// ========================================


//=========================================
static void SystemClock_Config(void)
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    //Error_Handler();
  }

  /* activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    //Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    //Error_Handler();

  }

}


int main(void)
{
   hwInit();
   MyApp();
}

void hwInit(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
  HAL_Init();
  SystemClock_Config();


}

int CheckClockStatus(unsigned int GPIOPort){
	return (( *( (V_UINT32*)(0x40023830U) ) & (0x00000001U << GPIOPort) ) > 0);
}

void ClockEnable(unsigned int GPIOPort){
	// Clock Enable
	*((V_UINT32*)(0x40023830U)) |= ( 0x00000001U << GPIOPort );
}


void MyDelay(unsigned int n){ // 10??? ???????????? 1?????? ?????????

	V_UINT32 delay;
	for ( delay = 0; delay <= n*RATE; delay++); //
}

void SetOneLED(unsigned char No){
	switch(No){
		case 1:
			// SET LED 1
			*((V_UINT32*)(0x40021800U)) |= 0x01000000U; //[offser: 0x00] MODER12??? output ??????(01)??? ??????
			*((V_UINT32*)(0x40021808U)) |= 0x03000000U; //[offset: 0x08] OSPEEDR??? veryhigh(11)??? ??????
			*((V_UINT32*)(0x4002180cU)) |= 0x01000000U; //[offser: 0xoc] PUPDR??? pull up(01)??? ??????
			break;
		case 2:
			// SET LED2
			*((V_UINT32*)(0x40021000U)) |= 0x00000400U; //[offset: 0x00] MODER5??? output ??????(01)??? ?????? (10~11??? ??????)
			*((V_UINT32*)(0x40021008U)) |= 0x00000C00U; //[offset: 0x08] OSPEEDR??? veryhigh(11)??? ?????? (10~11??? ??????)
			*((V_UINT32*)(0x4002100cU)) |= 0x01000400U; //[offset: 0xoc] PUPDR??? pull up(01)??? ?????? (10~11??? ??????)
			break;
		case 3:
			//SET LED3
			*((V_UINT32*)(0x40021000U)) |= 0x00000100U; //[offset: 0x00] MODER4 (E) output ??????(01)??? ?????? (8~9??? ??????)
			*((V_UINT32*)(0x40021008U)) |= 0x00000300U; //[offset: 0x08] OSPEEDR 4??? veryhigh(11)??? ?????? (8~9??? ??????)
			*((V_UINT32*)(0x4002100cU)) |= 0x00000100U; //[offset: 0xoc] PUPDR??? pull up(01)??? ??????(8~9??? ??????)
			break;
		case 4:
			//SET LED4
			*((V_UINT32*)(0x40021800U)) |= 0x00100000U; //[offset: 0x00] MODER10 (G) output ??????(01)??? ?????? (20~21??? ??????)
			*((V_UINT32*)(0x40021808U)) |= 0x00300000U; //[offset: 0x08] OSPEEDR 10??? veryhigh(11)??? ?????? (20~21??? ??????)
			*((V_UINT32*)(0x4002180cU)) |= 0x00100000U; //[offset: 0xoc] PUPDR??? pull up(01)??? ?????? (20~21??? ??????)
			break;
	}
}

void TurnOnOneLED(unsigned char No){ // NO ??? 1~4 ????????? ??????

	switch(No){
		case 1: //PG 12
			SetOneLED(1);
			*((V_UINT32*)(0x40021818U)) |= 0x10000000U; //[offser: 0x18] BSRR??? reset
			break;
		case 2: //PE5
			SetOneLED(2);
			*((V_UINT32*)(0x40021018U)) |= 0x00200000U; //[offset: 0x18] BSRR??? reset (5??? ??????)
			break;
		case 3: //PE 4
			SetOneLED(3);
			*((V_UINT32*)(0x40021018U)) |= 0x00100000U; //[offset: 0x18] BSRR??? reset (20??? ??????)
			break;
		case 4:
			SetOneLED(4);
			*((V_UINT32*)(0x40021818U)) |= 0x04000000U; //[offset: 0x18] BSRR??? reset (26??? ??????)
			break;
	}

}

void TurnOffOneLED(unsigned char No){ // NO ??? 1~4 ????????? ??????

	switch(No){
		case 1: //PG 12
			SetOneLED(1);
			*((V_UINT32*)(0x40021818U)) |= 0x00001000U; //[offser: 0x18] BSRR??? set
			break;
		case 2: //PE5
			SetOneLED(2);
			*((V_UINT32*)(0x40021018U)) |= 0x00000020U; //[offset: 0x18] BSRR??? set (5??? ??????)
			break;
		case 3: //PE 4
			SetOneLED(3);
			*((V_UINT32*)(0x40021018U)) |= 0x00000010U; //[offset: 0x18] BSRR??? set (4??? ??????)
			break;
		case 4:
			SetOneLED(4);
			*((V_UINT32*)(0x40021818U)) |= 0x00000400U; //[offset: 0x18] BSRR??? set (10??? ??????)
			break;
	}

}


void MyApp()
{

	//Clock Enable
	if(!CheckClockStatus(4))	ClockEnable(4);
	if(!CheckClockStatus(6))	ClockEnable(6);


	TurnOnOneLED(1);
	MyDelay(5);
	TurnOnOneLED(2);
	MyDelay(5);
	TurnOffOneLED(1);
	MyDelay(5);
	TurnOffOneLED(2);
	MyDelay(5);
	TurnOnOneLED(3);



}

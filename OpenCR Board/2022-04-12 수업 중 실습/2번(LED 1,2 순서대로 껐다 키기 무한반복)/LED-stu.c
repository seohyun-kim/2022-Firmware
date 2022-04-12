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

void MyDelay(unsigned int n){

	V_UINT32 delay;

	for ( delay = 0; delay <= n*RATE; delay++); //
}

void MyApp()
{
 // My Code

	*((V_UINT32*)(0x40023830U)) |= 0x00000050U; // [Offset : 0x30] Clock Enable(01)로 설정 (4,6번비트)

	*((V_UINT32*)(0x40021800U)) |= 0x01000000U; //[offser: 0x00] MODER12를 output 모드(01)을 설정
	*((V_UINT32*)(0x40021808U)) |= 0x03000000U; //[offset: 0x08] OSPEEDR를 veryhigh(11)로 설정
	*((V_UINT32*)(0x4002180cU)) |= 0x01000000U; //[offser: 0xoc] PUPDR를 pull up(01)을 설정

	// SYS_USER_LED2 : PE5 (GPIOE 5번 port)
	*((V_UINT32*)(0x40021000U)) |= 0x00000400U; //[offset: 0x00] MODER5를 output 모드(01)을 설정 (10~11번 비트)
	*((V_UINT32*)(0x40021008U)) |= 0x00000C00U; //[offset: 0x08] OSPEEDR를 veryhigh(11)로 설정 (10~11번 비트)
	*((V_UINT32*)(0x4002100cU)) |= 0x01000400U; //[offset: 0xoc] PUPDR를 pull up(01)을 설정 (10~11번 비트)

	//둘다 꺼지도록 초기화
	*((V_UINT32*)(0x40021818U)) |= 0x00001000U; //[offser: 0x18] BSRR을 set 	// 1번 LED OFF
	*((V_UINT32*)(0x40021018U)) |= 0x00000020U; //[offset: 0x18] BSRR을 set (5번 비트) 	// 2번 LED OFF


	while(1){
		// 1번 LED ON
		*((V_UINT32*)(0x40021818U)) |= 0x10000000U; //[offser: 0x18] BSRR을 reset

		MyDelay(5);

		// 2번 LED ON
		*((V_UINT32*)(0x40021018U)) |= 0x00200000U; //[offset: 0x18] BSRR을 reset (21번 비트)

		MyDelay(5);

		// 1번 LED OFF
		*((V_UINT32*)(0x40021818U)) |= 0x00001000U; //[offser: 0x18] BSRR을 set


		MyDelay(5);

		// 2번 LED OFF
		*((V_UINT32*)(0x40021018U)) |= 0x00000020U; //[offset: 0x18] BSRR을 set (5번 비트)

		MyDelay(5);
	}


}

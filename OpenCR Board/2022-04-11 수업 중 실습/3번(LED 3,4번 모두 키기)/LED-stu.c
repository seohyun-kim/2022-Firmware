typedef volatile unsigned int  V_UINT32;

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

void MyApp()
{
 // My Code

	// user 3,4 LED 키기
	// SYS_USER_LED3 : PE4 (GPIOE 4번 port)- GPIOE : 0x4002 1000
	// SYS_USER_LED4 : PG10 (GPIOG 10번 port) - GPIOG : 0x4002 1800

	*((V_UINT32*)(0x40023830U)) |= 0x00000050U; // [Offset : 0x30] GPIOE와 GPIOG Clock Enable(01)로 설정 (E:4번비트, G:6번 비트)-0101

	*((V_UINT32*)(0x40021000U)) |= 0x00000100U; //[offset: 0x00] MODER4 (E) output 모드(01)을 설정 (8~9번 비트)
	*((V_UINT32*)(0x40021800U)) |= 0x00100000U; //[offset: 0x00] MODER10 (G) output 모드(01)을 설정 (20~21번 비트)

	*((V_UINT32*)(0x40021008U)) |= 0x00000300U; //[offset: 0x08] OSPEEDR 4를 veryhigh(11)로 설정 (8~9번 비트)
	*((V_UINT32*)(0x40021808U)) |= 0x00300000U; //[offset: 0x08] OSPEEDR 10를 veryhigh(11)로 설정 (20~21번 비트)

	*((V_UINT32*)(0x4002100cU)) |= 0x00000100U; //[offset: 0xoc] PUPDR를 pull up(01)을 설정(8~9번 비트)
	*((V_UINT32*)(0x4002180cU)) |= 0x00100000U; //[offset: 0xoc] PUPDR를 pull up(01)을 설정 (20~21번 비트)


	*((V_UINT32*)(0x40021018U)) |= 0x00100000U; //[offset: 0x18] BSRR을 reset (20번 비트)
	*((V_UINT32*)(0x40021818U)) |= 0x04000000U; //[offset: 0x18] BSRR을 reset (26번 비트)



}

typedef volatile unsigned int  V_UINT32;
typedef unsigned int UINT32;
#define RATE 3600000
#define HALFBYTE 4
#define BYTE 8
#define NumofLEDs 4

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

int  CheckClockStatus(unsigned int GPIOPort);
void ClockEnable(unsigned int GPIOPort);
void MyDelay(unsigned int n);

void LEDOnOff(UINT32 No);
void LEDOnDuration(UINT32 DurationArr[]);

void TurnOnOneLED(unsigned char No);
void TurnOffOneLED(unsigned char No);
void SetOneLED(unsigned char No);




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

	//Clock Enable
	if(!CheckClockStatus(4))	ClockEnable(4);
	if(!CheckClockStatus(6))	ClockEnable(6);

	LEDOnOff(0xF0F0F1FF); // 모든 LED ON
	MyDelay(5); // 0.5초 딜레이

	LEDOnOff(0x0000010F); // 모든 LED OFF
	MyDelay(5); // 0.5초 딜레이

	LEDOnOff(0x15FF2A01); // LED 2번은 계속 ON, LED4는 계속 OFF 상태에서 LED 1과 3을 동시에 각 5회, 10회씩 깜빡임(1초딜레이)
	MyDelay(5); // 0.5초 딜레이

	LEDOnOff(0x0F0F0F0F); // 모든 LED OFF
	MyDelay(5); // 0.5초 딜레이

	LEDOnOff(0xA3138323); // 모든 LED 동시에 3회씩 깜빡임(1초 딜레이)
	MyDelay(5); // 0.5초 딜레이

}


int CheckClockStatus(unsigned int GPIOPort){
	return (( *( (V_UINT32*)(0x40023830U) ) & (0x00000001U << GPIOPort) ) > 0);
}

void ClockEnable(unsigned int GPIOPort){
	// Clock Enable
	*((V_UINT32*)(0x40023830U)) |= ( 0x00000001U << GPIOPort );
}

void MyDelay(unsigned int n){ // 10이 들어오면 1초가 되도록
	V_UINT32 delay;
	for ( delay = 0; delay <= n*RATE; delay++); //
}

void LEDOnOff(UINT32 No){
	// [LED 1] [LED 2] [ LED 3] [LED 4]
	UINT32 LEDOptionMask = 0x000000F0U;
	UINT32 DurationMask  = 0x0000000FU;

	UINT32 DurationArr[4]= {0,0,0,0};

	for(int i = 0 ; i < NumofLEDs ; i++){
		UINT32 LEDOption = (LEDOptionMask & No) >> ((i*2 +1)* HALFBYTE); // 현재 LED 속성 값 4bit
		UINT32 Duration  = (DurationMask  & No) >> (i* 2 * HALFBYTE); // 현재 LED Duration 4bit

		switch(LEDOption){
			case 0x00: // 해당 LED 끄기
				TurnOffOneLED(4-i);
				break;
			case 0x0F: // 해당 LED 켜기
				TurnOnOneLED(4-i);
				break;
			default: // 0 또는 F가 아닌 경우는 듀레이션 주기
				DurationArr[3-i] = Duration;
				break;
		}
		// mask 값 8비트(1바이트)씩 왼쪽 시프트 연산
		LEDOptionMask <<= BYTE;
		DurationMask  <<= BYTE;
	}
  LEDOnDuration(DurationArr);
}


void LEDOnDuration(UINT32 DurationArr[]){
	int MaxDuration = 0;
  for (int i = 0; i < NumofLEDs; i++) {
      if (DurationArr[i] > MaxDuration) MaxDuration = DurationArr[i];
  }
	while(MaxDuration > 0){
		for(int i = 0 ; i < NumofLEDs ; i++){
			if(DurationArr[i] > 0) {
				TurnOnOneLED(i+1);
			}
		}
		MyDelay(10);
		for(int i = 0 ; i < NumofLEDs ; i++){
			if(DurationArr[i] > 0){
				TurnOffOneLED(i+1);
				DurationArr[i]--;
			}
		}
		MyDelay(10);
		MaxDuration--;
	}
}

void TurnOnOneLED(unsigned char No){ // NO 는 1~4 사이의 정수
	switch(No){
		case 1: //PG 12
			SetOneLED(1);
			*((V_UINT32*)(0x40021818U)) |= 0x10000000U; //[offser: 0x18] BSRR을 reset
			break;
		case 2: //PE5
			SetOneLED(2);
			*((V_UINT32*)(0x40021018U)) |= 0x00200000U; //[offset: 0x18] BSRR을 reset (5번 비트)
			break;
		case 3: //PE 4
			SetOneLED(3);
			*((V_UINT32*)(0x40021018U)) |= 0x00100000U; //[offset: 0x18] BSRR을 reset (20번 비트)
			break;
		case 4:
			SetOneLED(4);
			*((V_UINT32*)(0x40021818U)) |= 0x04000000U; //[offset: 0x18] BSRR을 reset (26번 비트)
			break;
	}
}

void TurnOffOneLED(unsigned char No){ // NO 는 1~4 사이의 정수
	switch(No){
		case 1: //PG 12
			SetOneLED(1);
			*((V_UINT32*)(0x40021818U)) |= 0x00001000U; //[offser: 0x18] BSRR을 set
			break;
		case 2: //PE5
			SetOneLED(2);
			*((V_UINT32*)(0x40021018U)) |= 0x00000020U; //[offset: 0x18] BSRR을 set (5번 비트)
			break;
		case 3: //PE 4
			SetOneLED(3);
			*((V_UINT32*)(0x40021018U)) |= 0x00000010U; //[offset: 0x18] BSRR을 set (4번 비트)
			break;
		case 4:
			SetOneLED(4);
			*((V_UINT32*)(0x40021818U)) |= 0x00000400U; //[offset: 0x18] BSRR을 set (10번 비트)
			break;
	}
}

void SetOneLED(unsigned char No){
	switch(No){
		case 1:
			// SET LED 1
			*((V_UINT32*)(0x40021800U)) |= 0x01000000U; //[offser: 0x00] MODER12를 output 모드(01)을 설정
			*((V_UINT32*)(0x40021808U)) |= 0x03000000U; //[offset: 0x08] OSPEEDR를 veryhigh(11)로 설정
			*((V_UINT32*)(0x4002180cU)) |= 0x01000000U; //[offser: 0xoc] PUPDR를 pull up(01)을 설정
			break;
		case 2:
			// SET LED2
			*((V_UINT32*)(0x40021000U)) |= 0x00000400U; //[offset: 0x00] MODER5를 output 모드(01)을 설정 (10~11번 비트)
			*((V_UINT32*)(0x40021008U)) |= 0x00000C00U; //[offset: 0x08] OSPEEDR를 veryhigh(11)로 설정 (10~11번 비트)
			*((V_UINT32*)(0x4002100cU)) |= 0x01000400U; //[offset: 0xoc] PUPDR를 pull up(01)을 설정 (10~11번 비트)
			break;
		case 3:
			//SET LED3
			*((V_UINT32*)(0x40021000U)) |= 0x00000100U; //[offset: 0x00] MODER4 (E) output 모드(01)을 설정 (8~9번 비트)
			*((V_UINT32*)(0x40021008U)) |= 0x00000300U; //[offset: 0x08] OSPEEDR 4를 veryhigh(11)로 설정 (8~9번 비트)
			*((V_UINT32*)(0x4002100cU)) |= 0x00000100U; //[offset: 0xoc] PUPDR를 pull up(01)을 설정(8~9번 비트)
			break;
		case 4:
			//SET LED4
			*((V_UINT32*)(0x40021800U)) |= 0x00100000U; //[offset: 0x00] MODER10 (G) output 모드(01)을 설정 (20~21번 비트)
			*((V_UINT32*)(0x40021808U)) |= 0x00300000U; //[offset: 0x08] OSPEEDR 10를 veryhigh(11)로 설정 (20~21번 비트)
			*((V_UINT32*)(0x4002180cU)) |= 0x00100000U; //[offset: 0xoc] PUPDR를 pull up(01)을 설정 (20~21번 비트)
			break;
	}
}




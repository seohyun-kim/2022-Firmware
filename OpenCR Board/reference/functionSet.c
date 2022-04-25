//============== m y d e f =================
// typedef
typedef volatile unsigned int  V_UINT32;
typedef unsigned int UINT32;

// base address
#define GPIOC_BASEADDRESS 0x40020800U
#define GPIOG_BASEADDRESS 0x40021800U
#define GPIOE_BASEADDRESS 0x40021000U
#define RCC_BASEADDRESS   0x40023800U

//offset
#define MODEROFFSET  0x00000000U
#define OSPEEDOFFSET 0x00000008U
#define PUPDROFFSET  0x0000000CU
#define BSRROFFSET   0x00000018U
#define RCCOFFSET    0x00000030U
#define IDROFFSET    0x00000010U

// masking
#define AndMaskforTwoBit 0x00000003U

// 1. MODER OPTION
#define INPUTMODE   0x00000000U   // reset state
#define OUTPUTMODE  0x00000001U   // general purpose output mode
#define ALTFUNCMODE 0x00000002U   // Alternate function mode
#define ANALOGMODE  0x00000003U   // analog mode

// 2. OSPEEDR OPTION
#define LOWSPEED      0x00000000U
#define MEDIUMSPEED   0x00000001U
#define HIGHSPEED     0x00000002U
#define VERYHIGHSPEED 0x00000003U

// 3. PUPDR OPTION
#define NOPUPD   0x00000000U
#define PULLUP   0x00000001U
#define PULLDOWN 0x00000002U
//#define RESERVED 0x00000003U

// 3. BSRR OPTION
#define SETRESET 0x00000001U

// GPIO Port bit
#define GPIOE_BIT 4
#define GPIOG_BIT 6
#define GPIOC_BIT 2
/* |  10bit  |  9bit  |  8bit  |  7bit  |  6bit  |  5bit  |  4bit  |  3bit  |  2bit  |  1bit  |  0bit  |
	 | GPIO K  | GPIO J | GPIO I | GPIO H | GPIO G | GPIO F | GPIO E | GPIO D | GPIO C | GPIO B | GPIO A | */

// etc
#define RATE 3600000
#define HALFBYTE 4
#define BYTE 8
#define NumofLEDs 4

/*
	[SYS_USER_LED 1]  |  PG 12  |
	[SYS_USER_LED 2]  |  PE  5  |
	[SYS_USER_LED 3]  |  PE  4  |
	[SYS_USER_LED 4]  |  PG 10  |

	< Base address >   ------ p.70
	GPIO G : 0x4002 1800  | AHB 1
	GPIO E : 0x4002 1000  | AHB 1

	< Offset >  ------------ p.208-210
	MODER   : 0x00   |  {00:input}       {01: GP Output} {10: Alternate Function}  {11: Analog}
	OSPEEDR : 0x08   |  {00: Low Speed}  {01: Medium}    {10: High}                {11: Very high}
	PUPDR   : 0x0C   |  {00: No}         {01: Pull-up}   {10: Pull-down}           {11: Reserved}
	BSRR    : 0X18   |  {Bits 31:16 RESET}   {Bits 15:0 SET}
*/

//============== m y d e f =================


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


// ============== my functions ===================
int  CheckClockStatus(UINT32 GPIOPort);
	// 해당 GPIO의 Clock이 켜져있는지 체크하는 함수 ( 0:OFF, 1:ON)

void ClockEnable(UINT32 GPIOPort);
	// 해당 port bit에 clock을 Enable 시킴

void MyDelay(UINT32 n);
	// n* 100ms 동안 dalay를 줌 (n=5 : 0.5sec)

void LEDOnOff(UINT32 No);
	/* LED 4개를 1byte 씩 사용하여 제어하는 함수
			-
	*/

void RunLEDOnDuration(int DurationArr[]);

void TurnOnOneLED(UINT32 No);
	/* 1~4 사이의 숫자 No가 입력되고, 해당 LED를 켠다.
			- SetOneLED() 함수가 내부에서 호출 됨*/

void TurnOffOneLED(UINT32 No);
	// 1~4 사이의 숫자 No가 입력되고, 해당 LED를 끈다.

void SetOneLED(UINT32 No);
	/* 1~4 사이의 숫자 No가 입력되고, 해당 LED를 Setting
			- MODER    output 모드(01)
			- OSPEEDR  very high(11)
			- PUPDR    pull up(01)   */

UINT32 GetIDRforButton(UINT32 ButtonNo);
	// Button Switch에 대한 IDR값을 가져옴

UINT32 getBaseAddrforLED(UINT32 LEDNo);
	// LED 1~4의 BaseAddress를 리턴

UINT32 getPortforLED(UINT32 LEDNo);
	// LED 1~4의 GPIO port 번호를 리턴

UINT32 getBaseAddrforButton(UINT32 ButtonNo);
	// ButtonSwitch 1~2의 BaseAddress를 리턴

UINT32 getPortforButton(UINT32 ButtonNo);
	// ButtonSwitch 1~2의 GPIO port 번호를 리턴


void TurnOnOneLEDWhenButtonPushed(UINT32 ButtonNo, UINT32 LEDNo);
void SetOneButton(UINT32 No);

// ============== my functions ===================


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

	//Clock Status Check & Enable
	if(!CheckClockStatus(GPIOE_BIT))	ClockEnable(GPIOE_BIT);
	if(!CheckClockStatus(GPIOG_BIT))	ClockEnable(GPIOG_BIT);
	if(!CheckClockStatus(GPIOC_BIT))	ClockEnable(GPIOC_BIT);


	SetOneButton(1);
	TurnOnOneLEDWhenButtonPushed(2,3);

		//LEDOnOff(0xF0F0F1FF); // 모든 LED ON
//	MyDelay(5); // 0.5초 딜레이
//
//	LEDOnOff(0x0000010F); // 모든 LED OFF
//	MyDelay(5); // 0.5초 딜레이
//
//	LEDOnOff(0x15FF2A01); // LED 2번은 계속 ON, LED4는 계속 OFF 상태에서 LED 1과 3을 동시에 각 5회, 10회씩 깜빡임(1초딜레이)
//	MyDelay(5); // 0.5초 딜레이
//
//	LEDOnOff(0x0F0F0F0F); // 모든 LED OFF
//	MyDelay(5); // 0.5초 딜레이
//
//	LEDOnOff(0xA3138323); // 모든 LED 동시에 3회씩 깜빡임(1초 딜레이)
//	MyDelay(5); // 0.5초 딜레이

}


int CheckClockStatus(UINT32 GPIOPort){
	return (( *( (V_UINT32*)(RCC_BASEADDRESS + RCCOFFSET) ) & (0x00000001U << GPIOPort) ) > 0);
}

void ClockEnable(UINT32 GPIOPort){
	// Clock Enable
	*((V_UINT32*)((RCC_BASEADDRESS + RCCOFFSET))) |= ( 0x00000001U << GPIOPort );
}

void MyDelay(UINT32 n){ // 10이 들어오면 1초가 되도록
	V_UINT32 delay;
	for ( delay = 0; delay <= n*RATE; delay++); //
}

void LEDOnOff(UINT32 No){
	// [LED 1] [LED 2] [ LED 3] [LED 4]
	UINT32 LEDOptionMask = 0x000000F0U; // 4~7번 비트만 1로 줌 (LED옵션을 볼 상위 4비트)
	UINT32 DurationMask  = 0x0000000FU; // 0~3번 비트만 1로 줌 (Duration을 볼 하위 4비트)

	int DurationArr[4]= {0,0,0,0}; // LED 4개의 Duration을 저장할 배열 (0으로 초기화)

	for(int i = 0 ; i < NumofLEDs ; i++){
		UINT32 LEDOption = (LEDOptionMask & No) >> ((i*2 +1)* HALFBYTE); // 해당 LED 속성 값 4bit를 뽑아(LEDOptionMask와 &연산) 가장 끝으로 shift(0~3번 bit에 위치하도록)
		UINT32 Duration  = (DurationMask  & No) >> (i* 2 * HALFBYTE); // 해당 LED의 Duration 값 4bit를 뽑아(DurationMask와 &연산) 가장 끝으로 shift(0~3번 bit에 위치하도록)

		// LED Option값에 따라 분기해 DurationArr배열에 값 넣어줌
		switch(LEDOption){
			case 0x00: // 해당 LED 끄기
				DurationArr[3-i] = -2; // 항상 OFF 를 -2으로 표시
				break;
			case 0x0F: // 해당 LED 켜기
				DurationArr[3-i] = -1; // 항상 ON 를 -1으로 표시
				break;
			default: // 0 또는 F가 아닌 경우는 듀레이션 주기
				DurationArr[3-i] = Duration;
				break;
		}

		// mask 값 8비트(1바이트)씩 왼쪽 시프트 연산
		LEDOptionMask <<= BYTE;
		DurationMask  <<= BYTE;
	}
  RunLEDOnDuration(DurationArr); // LED
}


void RunLEDOnDuration(int DurationArr[]){

	// Duration 배열에서 가장 큰 값 찾기
	int MaxDuration = 0;
  for (int i = 0; i < NumofLEDs; i++) {
      if (DurationArr[i] > MaxDuration) MaxDuration = DurationArr[i];
  }

	do{ // 항상 켜지고 꺼지는 것도 한 번은 실행시키기 위해 do-while문 작성
		for(int i = 0 ; i < NumofLEDs ; i++){
			if(DurationArr[i] > 0) TurnOnOneLED(i+1); // Duration이 있는 경우
			else if(DurationArr[i] == -1) TurnOnOneLED(i+1); // 항상 ON 인 경우
			else if(DurationArr[i] == -2) TurnOffOneLED(i+1); // 항상 OFF인 경우
		}
		MyDelay(5);
		for(int i = 0 ; i < NumofLEDs ; i++){
			if(DurationArr[i] > 0){
				TurnOffOneLED(i+1);
				DurationArr[i]--;
			}
		}
		MyDelay(5);
		MaxDuration--;
	}while(MaxDuration > 0);

}


void TurnOnOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
	SetOneLED(No);
	// BSRR reset
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforLED(No)+16));
}

void TurnOffOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
	// BSRR set
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << getPortforLED(No));
}

void TurnOnOneLEDWhenButtonPushed(UINT32 ButtonNo, UINT32 LEDNo){
	SetOneButton(ButtonNo);	//Button Setup
	while(1){
		if(GetIDRforButton(ButtonNo) > 0){ // 버튼 클릭 시
			TurnOnOneLED(LEDNo);
		}else{
			TurnOffOneLED(LEDNo);
		}
	}
}

UINT32 GetIDRforButton(UINT32 ButtonNo){
	return (*((V_UINT32*)(getBaseAddrforButton(ButtonNo)+IDROFFSET))) & (0x00000001U << getPortforButton(ButtonNo));
}

void SetOneLED(UINT32 No){
	//MODER OUTPUTMODE
	*((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  |=  (OUTPUTMODE       << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀

	//OSPEED VERY HIGH
	*((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀
}

void SetOneButton(UINT32 No){
	//MODER INPUTMODE
	*((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  |=  (INPUTMODE        << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀

	//OSPEED VERY HIGH
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET))	&= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀
}


UINT32 getBaseAddrforLED(UINT32 LEDNo){ // LED 1~4
	switch(LEDNo){
		case 1:
		case 4:
			return GPIOG_BASEADDRESS;
		case 2:
		case 3:
			return GPIOE_BASEADDRESS;
	}
}

UINT32 getPortforLED(UINT32 LEDNo){ // LED 1~4
		switch(LEDNo){
			case 1:
				return 12;
			case 2:
				return 5;
			case 3:
				return 4;
			case 4:
				return 10;
		}
}

UINT32 getBaseAddrforButton(UINT32 ButtonNo){ // LED 1~4
	switch(ButtonNo){
		case 1:
			return GPIOC_BASEADDRESS;
		case 2:
			return GPIOG_BASEADDRESS;
	}
}

UINT32 getPortforButton(UINT32 ButtonNo){ // LED 1~4
		switch(ButtonNo){
			case 1:
				return 12; // PC12
			case 2:
				return 3; // PG3
		}
}





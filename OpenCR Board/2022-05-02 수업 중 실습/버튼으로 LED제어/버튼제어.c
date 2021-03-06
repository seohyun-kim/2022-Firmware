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
#define AndMaskforTwoBit  0x00000003U
#define AndMaskforOneoBit 0x00000001U

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

// etc
#define RATE 3600000
#define HALFBYTE 4
#define BYTE 8
#define NumofLEDs 4

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
	// 해당 GPIO의 Clock이 켜져있는지 체크하는 함수 (0:OFF, 1:ON)

void ClockEnable(UINT32 GPIOPort);
	// 해당 port bit에 clock을 Enable 시킴

void MyDelay(UINT32 n);
	// n* 100ms 동안 dalay를 줌 (n=5 : 0.5sec)

void InitGPIO();
	// LED제어에 필요한 Clock을 모두 Enable 시키고, LED 1~4를 OFF 시킴


void TurnOnOneLED(UINT32 No);
	/* 1~4 사이의 숫자 No가 입력되고, 해당 LED를 켠다.
			- SetOneLED() 함수가 내부에서 호출 됨*/

void TurnOffOneLED(UINT32 No);
	// 1~5 사이의 숫자 No가 입력되고, 해당 LED를 끈다.

void SetOneLED(UINT32 No);
	/* 1~5 사이의 숫자 No가 입력되고, 해당 LED를 Setting
			- MODER    output 모드(01)
			- OSPEEDR  very high(11)
			- PUPDR    pull up(01)   */


void SetOneButton(UINT32 No);
	/* 1~2 사이의 숫자 No가 입력되고, 해당 Button을 Setting
		- MODER    input 모드(00)
		- OSPEEDR  low(00)
		- PUPDR    no pull(00)   */

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
   while(1){};
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

	InitGPIO(); // LED 4개 관련 클럭 모두 Enable, 모두 OFF로 초기화

	SetOneButton(1); // 버튼 세팅
	SetOneLED(1); // LED 1번 세팅

	while(1){
		if((GetIDRforButton(1) >> getPortforButton(1)) == 1){ // 버튼 클릭 시
			TurnOnOneLED(1);
		}else{
			TurnOffOneLED(1);
		}
	}
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


void InitGPIO(){

	//Clock Status Check & Enable
	if(!CheckClockStatus(GPIOE_BIT))	ClockEnable(GPIOE_BIT);
	if(!CheckClockStatus(GPIOG_BIT))	ClockEnable(GPIOG_BIT);
	if(!CheckClockStatus(GPIOC_BIT))	ClockEnable(GPIOC_BIT);

	// Turn 4 LEDs OFF
	for(int i = 1; i <= 4; i++ ){
		TurnOffOneLED(i);
	}
}


void TurnOnOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
	SetOneLED(No);
	// BSRR reset
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforLED(No)+16));
}

void TurnOffOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
	// BSRR set
	SetOneLED(No);
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << getPortforLED(No));
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
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET)) |=  (LOWSPEED         << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  |=  (NOPUPD           << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀
}


UINT32 getBaseAddrforLED(UINT32 LEDNo){ // LED 1~5 (5는 status)
	switch(LEDNo){
		case 1:
		case 4:
		case 5:
			return GPIOG_BASEADDRESS;
		case 2:
		case 3:
			return GPIOE_BASEADDRESS;
	}
}

UINT32 getPortforLED(UINT32 LEDNo){ // LED 1~4
		switch(LEDNo){
			case 1: return 12;
			case 2: return  5;
			case 3: return  4;
			case 4: return 10;
			case 5: return  9; // SYS_STS_LED
		}
}

UINT32 getBaseAddrforButton(UINT32 ButtonNo){ // BTN 1~2
	switch(ButtonNo){
		case 1: return GPIOC_BASEADDRESS;
		case 2: return GPIOG_BASEADDRESS;
	}
}

UINT32 getPortforButton(UINT32 ButtonNo){ // BTN 1~2
		switch(ButtonNo){
			case 1: return 12; // PC 12
			case 2: return 3;  // PG  3
		}
}





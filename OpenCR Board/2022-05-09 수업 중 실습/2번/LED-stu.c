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
/* |  10bit  |  9bit  |  8bit  |  7bit  |  6bit  |  5bit  |  4bit  |  3bit  |  2bit  |  1bit  |  0bit  |
	 | GPIO K  | GPIO J | GPIO I | GPIO H | GPIO G | GPIO F | GPIO E | GPIO D | GPIO C | GPIO B | GPIO A | */

// etc
#define RATE 3600000
#define HALFBYTE 4
#define BYTE 8
#define NumofLEDs 4
#define MILLOIN 1000000
/*
	[SYS_USER_LED 1]  |  PG 12  |
	[SYS_USER_LED 2]  |  PE  5  |
	[SYS_USER_LED 3]  |  PE  4  |
	[SYS_USER_LED 4]  |  PG 10  |
	[SYS_STS_LED]     |  PG  9  |

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
	// ?????? GPIO??? Clock??? ??????????????? ???????????? ?????? (0:OFF, 1:ON)

void ClockEnable(UINT32 GPIOPort);
	// ?????? port bit??? clock??? Enable ??????

void MyDelay(UINT32 n);
	// n* 100ms ?????? dalay??? ??? (n=5 : 0.5sec)

void InitGPIO();
	// LED????????? ????????? Clock??? ?????? Enable ?????????, LED 1~4??? OFF ??????

//int MoveLED(int Dir, int Start, int Count);
//	// LED??? Dir ???????????? Start??? ????????? LED?????? Count?????? ???????????? ????????????

void LEDOnOff(UINT32 No);
	/* LED 4?????? 1byte ??? ???????????? ???????????? ??????
			- 1Byte ??? [LED 1][LED 2][LED 3][LED 4]
	*/

void RunLEDOnDuration(int DurationArr[]);
	// LED Duration ?????? Blink?????? ?????? ??????

void TurnOnOneLED(UINT32 No);
	/* 1~4 ????????? ?????? No??? ????????????, ?????? LED??? ??????.
			- SetOneLED() ????????? ???????????? ?????? ???*/

void TurnOffOneLED(UINT32 No);
	// 1~5 ????????? ?????? No??? ????????????, ?????? LED??? ??????.

void SetOneLED(UINT32 No);
	/* 1~5 ????????? ?????? No??? ????????????, ?????? LED??? Setting
			- MODER    output ??????(01)
			- OSPEEDR  very high(11)
			- PUPDR    pull up(01)   */

void TurnOnOneLEDWhenButtonPushed(UINT32 ButtonNo, UINT32 LEDNo);
	// ?????? ????????? ???????????? ?????? LED??? ?????? ??????

void SetOneButton(UINT32 No);
	/* 1~2 ????????? ?????? No??? ????????????, ?????? Button??? Setting
		- MODER    input ??????(00)
		- OSPEEDR  low(00)
		- PUPDR    no pull(00)   */

UINT32 GetIDRforButton(UINT32 ButtonNo);
	// Button Switch??? ?????? IDR?????? ?????????

UINT32 getBaseAddrforLED(UINT32 LEDNo);
	// LED 1~4??? BaseAddress??? ??????

UINT32 getPortforLED(UINT32 LEDNo);
	// LED 1~4??? GPIO port ????????? ??????

UINT32 getBaseAddrforButton(UINT32 ButtonNo);
	// ButtonSwitch 1~2??? BaseAddress??? ??????

UINT32 getPortforButton(UINT32 ButtonNo);
	// ButtonSwitch 1~2??? GPIO port ????????? ??????

//void TurnOnLEDUsedforFourBit(UINT32 n);

int isInputValid(UINT32 ButtonNo);

//int DelaywithBTNCheck(int waitingTime);

void TurnOnAllLED(void );

void TurnOffAllLED(void );


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

	InitGPIO(); // LED 4??? ?????? ?????? ?????? Enable, ?????? OFF??? ?????????

	SetOneButton(1); // ?????? ??????
	SetOneButton(2); // ?????? ??????


	while(1){
		int waitingTime = 5;

		if(isInputValid(1)){ // 1??? ?????? ??????

			while(waitingTime --){
				for(int i = 1 ; i <= 4 ; i++){
								TurnOnOneLED(i);
							}
							MyDelay(5);
							TurnOffOneLED(2);
							TurnOffOneLED(3);
							TurnOffOneLED(4);
							MyDelay(5);
			}

		}
		else if(isInputValid(2)){ // 2??? ?????? ??????
			while(waitingTime --){
				for(int i = 1 ; i <= 4 ; i++){
					TurnOnOneLED(i);
				}
				MyDelay(5);
				TurnOffOneLED(1);
				TurnOffOneLED(3);
				TurnOffOneLED(4);
				MyDelay(5);
			}
		}
		else {
			TurnOnAllLED();
			MyDelay(5);
			TurnOffAllLED();
			MyDelay(5);
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

void MyDelay(UINT32 n){ // 10??? ???????????? 1?????? ?????????
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


//int BTNCheck(){
//
//	int BTN1check = isInputValid(1);
//	int BTN2check = isInputValid(2);
//
//	if(BTN1check && BTN1check){ // ?????? ON ??????
//		return 3;
//	}else if (BTN1check){ // 1 ??? ?????? ??????
//		return 1;
//	}else if (BTN2check){ // 2 ??? ?????? ??????
//		return 2;
//	}else return 0; // ?????? OFF ?????? ??? ?????? 0??? ??????
//}


void TurnOnAllLED(){
	for(int i =1 ; i <= 4; i++){
		TurnOnOneLED(i);
	}
	return;
}

void TurnOffAllLED(){
	for(int i =1 ; i <= 4; i++){
		TurnOffOneLED(i);
	}
	return;
}


//int DelaywithBTNCheck(int waitingTime){
//	waitingTime = waitingTime * MILLOIN;
//
//	int BTN1check = isInputValid(1);
//	int BTN2check = isInputValid(2);
//
//	while(waitingTime --){
//		if(BTN1check && BTN1check){ // ?????? ON ??????
//			return 3;
//		}else if (BTN1check){ // 1 ??? ?????? ??????
//			return 1;
//		}else if (BTN2check){ // 2 ??? ?????? ??????
//			return 2;
//		} // ?????? OFF ?????? ??? ????????? while?????? ????????????
//	}
//
//	return 0; // ????????? ?????? wait time ??? ????????? 0??? ??????
//}


void LEDOnOff(UINT32 No){
	// [LED 1] [LED 2] [ LED 3] [LED 4]
	UINT32 LEDOptionMask = 0x000000F0U; // 4~7??? ????????? 1??? ??? (LED????????? ??? ?????? 4??????)
	UINT32 DurationMask  = 0x0000000FU; // 0~3??? ????????? 1??? ??? (Duration??? ??? ?????? 4??????)

	int DurationArr[4]= {0,0,0,0}; // LED 4?????? Duration??? ????????? ?????? (0?????? ?????????)

	for(int i = 0 ; i < NumofLEDs ; i++){
		UINT32 LEDOption = (LEDOptionMask & No) >> ((i*2 +1)* HALFBYTE); // ?????? LED ?????? ??? 4bit??? ??????(LEDOptionMask??? &??????) ?????? ????????? shift(0~3??? bit??? ???????????????)
		UINT32 Duration  = (DurationMask  & No) >> (  i* 2 *  HALFBYTE); // ?????? LED??? Duration ??? 4bit??? ??????(DurationMask??? &??????) ?????? ????????? shift(0~3??? bit??? ???????????????)

		// LED Option?????? ?????? ????????? DurationArr????????? ??? ?????????
		switch(LEDOption){
			case 0x00: // ?????? LED ??????
				DurationArr[3-i] = -2; // ?????? OFF ??? -2?????? ??????
				break;
			case 0x0F: // ?????? LED ??????
				DurationArr[3-i] = -1; // ?????? ON ??? -1?????? ??????
				break;
			default: // 0 ?????? F??? ?????? ????????? ???????????? ??????
				DurationArr[3-i] = Duration;
				break;
		}

		// mask ??? 8??????(1?????????)??? ?????? ????????? ??????
		LEDOptionMask <<= BYTE;
		DurationMask  <<= BYTE;
	}
  RunLEDOnDuration(DurationArr); // LED
}


void RunLEDOnDuration(int DurationArr[]){

	// Duration ???????????? ?????? ??? ??? ??????
	int MaxDuration = 0;
  for (int i = 0; i < NumofLEDs; i++) {
      if (DurationArr[i] > MaxDuration) MaxDuration = DurationArr[i];
  }

	do{ // ?????? ????????? ????????? ?????? ??? ?????? ??????????????? ?????? do-while??? ??????
		for(int i = 0 ; i < NumofLEDs ; i++){
			if(DurationArr[i] > 0) TurnOnOneLED(i+1); // Duration??? ?????? ??????
			else if(DurationArr[i] == -1) TurnOnOneLED(i+1); // ?????? ON ??? ??????
			else if(DurationArr[i] == -2) TurnOffOneLED(i+1); // ?????? OFF??? ??????
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


void TurnOnOneLED(UINT32 No){ // NO ??? 1~4 ????????? ??????
	SetOneLED(No);
	// BSRR reset
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforLED(No)+16));
}

void TurnOffOneLED(UINT32 No){ // NO ??? 1~4 ????????? ??????
	// BSRR set
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << getPortforLED(No));
}

void TurnOnOneLEDWhenButtonPushed(UINT32 ButtonNo, UINT32 LEDNo){
	SetOneButton(ButtonNo);	//Button Setup
	while(1){
		if(GetIDRforButton(ButtonNo) > 0){ // ?????? ?????? ???
			TurnOnOneLED(LEDNo);
		}else{
			TurnOffOneLED(LEDNo);
		}
	}
}

int isInputValid(UINT32 ButtonNo){
	return ((GetIDRforButton(ButtonNo) >> getPortforButton(ButtonNo)) == 1);
}


UINT32 GetIDRforButton(UINT32 ButtonNo){
	return (*((V_UINT32*)(getBaseAddrforButton(ButtonNo)+IDROFFSET))) & (0x00000001U << getPortforButton(ButtonNo));
}

void SetOneLED(UINT32 No){
	//MODER OUTPUTMODE
	*((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // ?????? 2bit??? 00?????? ?????????
	*((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  |=  (OUTPUTMODE       << (getPortforLED(No)*2)); // ????????? ?????? ?????? ???

	//OSPEED VERY HIGH
	*((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // ?????? 2bit??? 00?????? ?????????
	*((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforLED(No)*2)); // ????????? ?????? ?????? ???

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // ?????? 2bit??? 00?????? ?????????
	*((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforLED(No)*2)); // ????????? ?????? ?????? ???
}

void SetOneButton(UINT32 No){
	//MODER INPUTMODE
	*((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // ?????? 2bit??? 00?????? ?????????
	*((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  |=  (INPUTMODE        << (getPortforButton(No)*2)); // ????????? ?????? ?????? ???

	//OSPEED VERY HIGH
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET))	&= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // ?????? 2bit??? 00?????? ?????????
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET)) |=  (LOWSPEED         << (getPortforButton(No)*2)); // ????????? ?????? ?????? ???

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // ?????? 2bit??? 00?????? ?????????
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  |=  (NOPUPD           << (getPortforButton(No)*2)); // ????????? ?????? ?????? ???
}


UINT32 getBaseAddrforLED(UINT32 LEDNo){ // LED 1~5 (5??? status)
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






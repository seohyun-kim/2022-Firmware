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
#define HUNDREDms 360000
#define THOUSANDms 3600000

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


   < 외부 LED 4개 사용 >
   LED 1 : ARD_D2 - PG 6
   LED 2 : ARD_D4 - PG 7
   LED 3 : ARD_D7 - PC 1
   LED 4 : ARD_D8 - PC 2
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
   // 해당 GPIO의 Clock이 켜져있는지 체크하는 함수 (0:OFF, 1:ON)

void ClockEnable(UINT32 GPIOPort);
   // 해당 port bit에 clock을 Enable 시킴

void MyDelay(UINT32 n);
   // n* 100ms 동안 dalay를 줌 (n=5 : 0.5sec)

void InitGPIO();
   // LED제어에 필요한 Clock을 모두 Enable 시키고, LED 1~4를 OFF 시킴

void TurnOnOneLEDb(UINT32 No, char InOut, UINT32 Duration);
	// 내 외부 해당 LED를 Duration 만큼 1개 키는 함수

void TurnOnAllLED(void ); // 내부 LED 4개 모두 ON

void TurnOffAllInOutLED(void ); // 내부 외부 4개씩 LED 모두 OFF


void TurnOnOneLED(UINT32 No);
   /* 1~4 사이의 숫자 No가 입력되고, 해당 LED를 켠다.
         - SetOneLED() 함수가 내부에서 호출 됨*/

void TurnOnOneOutLED(UINT32 No);
		/* 1~4 사이의 숫자 No가 입력되고, 해당 "외부" LED를 켠다.
					- SetOneLED() 함수가 내부에서 호출 됨*/

void TurnOffOneLED(UINT32 No);
   // 1~5 사이의 숫자 No가 입력되고, 해당 LED를 끈다.

void TurnOffOneOutLED(UINT32 No);
	// 1~5 사이의 숫자 No가 입력되고, 해당 LED를 끈다.

void SetOneLED(UINT32 No);
   /* 1~5 사이의 숫자 No가 입력되고, 해당 LED를 Setting
         - MODER    output 모드(01)
         - OSPEEDR  very high(11)
         - PUPDR    pull up(01)   */

void TurnOnOneLEDWhenButtonPushed(UINT32 ButtonNo, UINT32 LEDNo);
   // 해당 버튼이 클릭되면 해당 LED를 키는 함수

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


int isInputValid(UINT32 ButtonNo);





void SetOneOutLED(UINT32 No);
UINT32 getBaseAddrforOutLED(UINT32 LEDNo);
UINT32 getPortforOutLED(UINT32 LEDNo);


void SetOneGPIO(char GPIO, UINT32 Port);
UINT32 getBaseAddrfromGPIO(char GPIO);

int CheckIfButtonPushed(UINT32 ButtonNo);
void TurnOnOneInsideLED(UINT32 InsideNo, UINT32 Duration);

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

	InitGPIO(); //G, E, C Enable
	while(1){
		TurnOnOneInsideLED(1, 1);
		TurnOnOneInsideLED(2, 1);
		TurnOnOneInsideLED(3, 1);
		TurnOnOneInsideLED(4, 1);
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
   if(!CheckClockStatus(GPIOE_BIT))   ClockEnable(GPIOE_BIT);
   if(!CheckClockStatus(GPIOG_BIT))   ClockEnable(GPIOG_BIT);
   if(!CheckClockStatus(GPIOC_BIT))   ClockEnable(GPIOC_BIT);
}

void TurnOnOneInsideLED(UINT32 InsideNo, UINT32 Duration){
	// PG 6 - Input A
	// PG 7 - Input B
	// PC 1 - Input C

	/*  A   B   C   | L ED1  LED2  LED3  LED4  |  InsideNo
	 *  0   0   0   |  O     O      O     X   |     4
	 *  0   1   1   |  O     O      X     O   |     3
	 *  1   0   1   |  O     X      O     O   |     2
	 *  1   1   1   |  X     O      O     O   |     1
	 * */
	TurnOffAllInOutLED(); // 내부 LED 4개, 외부 LED 4개 모두 Off 한 상태로 시작
	TurnOnOneLED(InsideNo);

	switch(InsideNo){
		case 4:
			for(int i = 1 ; i <= 3 ; i ++) TurnOffOneOutLED(i);
			break;
		case 3:
			TurnOffOneOutLED(1); // GPIO G6 Off
			TurnOnOneOutLED(2);
			TurnOnOneOutLED(3);
			break;
		case 2:
			TurnOnOneOutLED(1);
			TurnOffOneOutLED(2);
			TurnOnOneOutLED(3);
			break;
		case 1:
			for(int i = 1 ; i <= 3 ; i ++) TurnOnOneOutLED(i);
			break;
	}
	MyDelay(Duration*10);

}


void TurnOnOneLEDb(UINT32 No, char InOut, UINT32 Duration){
	// No = LED번호 (내 외부의 1~4번)
	// InOut = 내부 LED인지(I), 외부 LED인지(O)를 구분
	// Duration = 켜져있는 시간 (100ms단위, 10이면 1초)
	// 지정된 LED이외에는 나머지 모든 LED를 끄도록 함
	//

	UINT32 waitingTime = Duration * THOUSANDms;
	TurnOffAllInOutLED(); // 내부 LED 4개, 외부 LED 4개 모두 Off한 상태로 시작


	switch(InOut){
		case 'I': // 내부 LED
			while(waitingTime --){
				 if(CheckIfButtonPushedandBack(2) == 1){ // SW1
					 waitingTime *= 0.9;
				 }else if(CheckIfButtonPushedandBack(1) == 1){ // SW2
					 waitingTime *= 1.1;
				 }
				 TurnOnOneLED(No);
			}
			break;

		case 'O': // 외부 LED
			while(waitingTime --){
				 if(CheckIfButtonPushedandBack(2) == 1){ // SW1
					 waitingTime *= 0.9;
				 }else if(CheckIfButtonPushedandBack(1) == 1){ // SW2
					 waitingTime *= 1.1;
				 }
			TurnOnOneOutLED(No);
			}
			break;
	}

}


void TurnOnOneLEDbyPattern(UINT32 Pattern, UINT32 Duration){
	// Pattern | 7 6 5 4 3 2 1 0 |
	// 4~7 bit 는 각각 외부 LED 1~4
	// 0~3 bit 는 각각 내부 LED 1~4

	UINT32 waitingTime = Duration * THOUSANDms;
	UINT32 No = 0;

	while((Pattern >> No) != 1){
		No++;
	}

	if(Pattern < 16 ){ // 내부 LED 일때
		while(waitingTime --){
			 if(CheckIfButtonPushedandBack(2) == 1){ // SW1
				 waitingTime *= 0.9;
			 }else if(CheckIfButtonPushedandBack(1) == 1){ // SW2
				 waitingTime *= 1.1;
			 }

			 TurnOnOneLED(No);
		}
	}


}



int CheckIfButtonPushedandBack(UINT32 ButtonNo){
   //SetOneButton(ButtonNo);   //Button Setup
	int flag = 0;
	while(GetIDRforButton(ButtonNo) > 0 ){ // 버튼 눌러진 상태일 때 block
		flag = 1; // 한 번이라도 눌러진 상태일 때
	}	// 뗐을 때 while문 탈출
	return flag;

}

void TurnOnAllLED(){
   for(int i =1 ; i <= 4; i++){
      TurnOnOneLED(i);
   }
   return;
}

void TurnOffAllInOutLED(){
   for(int i =1 ; i <= 4; i++){
      TurnOffOneLED(i);
      TurnOffOneOutLED(i);
   }
   return;
}


// 내부 LED 4개 제어
void TurnOnOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
   SetOneLED(No);
   // BSRR reset
   *((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforLED(No)+16));
}

// 외부 LED 4개 제어
void TurnOnOneOutLED(UINT32 No){
	SetOneOutLED(No);
	// BSRR set
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+BSRROFFSET))  |= (SETRESET << getPortforOutLED(No)); // ON
}

void TurnOffOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
   // BSRR set
   *((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << getPortforLED(No));
}

// 외부 LED 4개 제어
void TurnOffOneOutLED(UINT32 No){
	//SetOneOutLED(No);
	// BSRR reset
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforOutLED(No)+16)); //OFF
}

void TurnOnOneLEDWhenButtonPushed(UINT32 ButtonNo, UINT32 LEDNo){
   SetOneButton(ButtonNo);   //Button Setup
   while(1){
      if(GetIDRforButton(ButtonNo) > 0){ // 버튼 클릭 시
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
   *((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  |=  (OUTPUTMODE       << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀

   //OSPEED VERY HIGH
   *((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀

   //PUPDR PULL UP
   *((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀
}

void SetOneOutLED(UINT32 No){ // 외부 LED 4개 세팅
	   //MODER OUTPUTMODE
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforOutLED(No)*2)); // 해당 2bit를 00으로 초기화
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+MODEROFFSET))  |=  (OUTPUTMODE       << (getPortforOutLED(No)*2)); // 원하는 값을 덮어 씀

	   //OSPEED VERY HIGH
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (getPortforOutLED(No)*2)); // 해당 2bit를 00으로 초기화
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforOutLED(No)*2)); // 원하는 값을 덮어 씀

	   //PUPDR PULL UP
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforOutLED(No)*2)); // 해당 2bit를 00으로 초기화
	   *((V_UINT32*)(getBaseAddrforOutLED(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforOutLED(No)*2)); // 원하는 값을 덮어 씀
}

void SetOneGPIO(char GPIO, UINT32 Port){ // 외부 LED 4개 세팅
	   //MODER OUTPUTMODE
	   *((V_UINT32*)(getBaseAddrfromGPIO(GPIO)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (Port*2)); // 해당 2bit를 00으로 초기화
	   *((V_UINT32*)(getBaseAddrfromGPIO(GPIO)+MODEROFFSET))  |=  (OUTPUTMODE       << (Port*2)); // 원하는 값을 덮어 씀

	   //OSPEED VERY HIGH
	   *((V_UINT32*)(getBaseAddrfromGPIO(GPIO)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (Port*2)); // 해당 2bit를 00으로 초기화
	   *((V_UINT32*)(getBaseAddrfromGPIO(GPIO)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (Port*2)); // 원하는 값을 덮어 씀

	   //PUPDR PULL UP
	   *((V_UINT32*)(getBaseAddrfromGPIO(GPIO)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (Port*2)); // 해당 2bit를 00으로 초기화
	   *((V_UINT32*)(getBaseAddrfromGPIO(GPIO)+PUPDROFFSET))  |=  (PULLUP           << (Port*2)); // 원하는 값을 덮어 씀
}



void SetOneButton(UINT32 No){
   //MODER INPUTMODE
   *((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  |=  (INPUTMODE        << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀

   //OSPEED VERY HIGH
   *((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET))   &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
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

UINT32 getBaseAddrforOutLED(UINT32 LEDNo){ // LED 1~4(외부)
   switch(LEDNo){
      case 1:
      case 2:
         return GPIOG_BASEADDRESS;
      case 3:
      case 4:
         return GPIOC_BASEADDRESS;
   }
}


UINT32 getBaseAddrfromGPIO(char GPIO){ // LED 1~4(외부)
   switch(GPIO){
      case 'G':
         return GPIOG_BASEADDRESS;
      case 'C':
         return GPIOC_BASEADDRESS;
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

UINT32 getPortforOutLED(UINT32 LEDNo){ // LED 1~4 외부 LED
      switch(LEDNo){
         case 1: return 6;  // PG 6 - LED 1
         case 2: return 7;  // PG 7 - LED 2
         case 3: return 1;  // PC 1 - LED 3
         case 4: return 2;  // PC 2 - LED 4

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





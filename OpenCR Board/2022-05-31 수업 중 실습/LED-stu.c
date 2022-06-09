//============== m y d e f =================
// typedef
typedef volatile unsigned int  V_UINT32;
typedef unsigned int UINT32;

// base address
#define GPIOC_BASEADDRESS 0x40020800U
#define GPIOG_BASEADDRESS 0x40021800U
#define GPIOE_BASEADDRESS 0x40021000U
#define GPIOF_BASEADDRESS 0x40021400U
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
#define AndMaskforOneBit 0x00000001U

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
#define GPIOF_BIT 5
/* |  10bit  |  9bit  |  8bit  |  7bit  |  6bit  |  5bit  |  4bit  |  3bit  |  2bit  |  1bit  |  0bit  |
    | GPIO K  | GPIO J | GPIO I | GPIO H | GPIO G | GPIO F | GPIO E | GPIO D | GPIO C | GPIO B | GPIO A | */

// etc
#define RATE 3600000
#define HALFBYTE 4
#define BYTE 8
#define NumofLEDs 4
#define MILLOIN 1000000
#define HUNDREDTHOUSAND 100000
#define HUNDREDms 360000
#define THOUSANDms 3600000
#define THOUSAND 1000

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
   GPIO 1 : ARD_D2 - PG  6
   GPIO 2 : ARD_D4 - PG  7
   GPIO 3 : ARD_D7 - PC  1
   GPIO 4 : ARD_D8 - PC  2

   GPIO 5 : ARD_A1 - PF 10
   GPIO 6 : ARD_A2 - PF  9
   GPIO 7 : ARD_A3 - PF  8
   GPIO 8 : ARD_A4 - PF  7

   GPIO 9 : ARD_D0 - PC  7

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

void InitGPIO();
   // LED제어에 필요한 Clock을 모두 Enable 시키고, LED 1~4를 OFF 시킴

void TurnOnAllLED(void ); // 내부 LED 4개 모두 ON
void TurnOffAllLED();  // 내부 LED 4개 모두 OFF
void TurnOffAllInOutLED(void ); // 내부 외부 4개씩 LED 모두 OFF

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

void SetOneOutLED(UINT32 No);


UINT32 getBaseAddrforOutGPIO(UINT32 LEDNo);
UINT32 getPortforOutGPIO(UINT32 LEDNo);

void SetOneGPIO(char GPIO, UINT32 Port);
UINT32 getBaseAddrfromGPIO(char GPIO);

int CheckIfButtonPushedandBack(UINT32 ButtonNo);

void TurnOnOneGPIO(UINT32 No);
   // 외부 GPIO ON

void TurnOffOneGPIO(UINT32 No);
   // 외부 GPIO OFF

void ShowBinaryCount(UINT32 count);
   // 사거리 신호등 1SET마다 count 한 것을 이진 형태로 내부 LED 4개를 통해 점등

int RunTrafficLight(UINT32 No, UINT32 Duration);
   // 사거리 신호등 구현 함수

void Show7Segment(UINT32 displayNum);
   // 7 segment 점등 함수

void TurnOffAllOutGPIO();
   // 모든 외부 GPIO OFF
void MyDelay(UINT32 n);

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

   InitGPIO(); //G, E, C, F Enable

   while(1){
      TurnOffOneGPIO(1);
      TurnOffOneGPIO(2);
      MyDelay(1);

      TurnOffOneGPIO(1);
      TurnOnOneGPIO(2);
      MyDelay(1);

      TurnOnOneGPIO(1);
      TurnOffOneGPIO(2);
      MyDelay(1);

      TurnOnOneGPIO(1);
      TurnOnOneGPIO(2);
      MyDelay(1);


   }



//   TurnOffAllInOutLED(); // 내부 LED 4개, 외부 LED 4개 모두 Off한 상태로 시작
//
//
//   int count = 0;   // count(0~15)
//
//   while(1){
//      ShowBinaryCount(count); // 바이너리 카운트 표기
//      count = (count + 1) % 16; // 횟수 증가 및 보정
//
//      for(int i = 0 ; i < 8 ; i++){
//         // 짝수(0) - 7초, 홀수(1) - 2초
//         if(RunTrafficLight(  i, -5*(i%2)+7) == 1){
//               count = 0; // 회로 내부 버튼이 눌린 경우
//         }
//      }
//   }
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




// GPIO 의 Clock 상태를 체크하고 Enable 시킴
void InitGPIO(){

   //Clock Status Check & Enable
   if(!CheckClockStatus(GPIOE_BIT))   ClockEnable(GPIOE_BIT);
   if(!CheckClockStatus(GPIOG_BIT))   ClockEnable(GPIOG_BIT);
   if(!CheckClockStatus(GPIOC_BIT))   ClockEnable(GPIOC_BIT);
   if(!CheckClockStatus(GPIOF_BIT))   ClockEnable(GPIOF_BIT);
}

// 사거리 신호등 제어 함수
int RunTrafficLight(UINT32 No, UINT32 Duration){
   // No는 0~7까지의 숫자
   // Duration 만큼 반복함 (1은 1초)
   TurnOffAllOutGPIO();   // 외부 GPIO 4개 모두 Off한 상태로 시작

   UINT32 remainTime = 9;
   UINT32 pastRemainTime = remainTime;
   UINT32 pastTick = HAL_GetTick();

   while(HAL_GetTick() - pastTick < Duration * THOUSAND ){

      // Reset 버튼이 눌렀다 떼 졌는지 체크
      if(CheckIfButtonPushedandBack(2) == 1){ // SW1 눌렀다 뗐을 때
         return 1;      // reset
      }
      // 외부 SKIP 버튼이 눌렀다 떼 졌는지 체크
      if(CheckIfButtonPushedandBack(3) == 1){ // SW2 눌렀다 뗐을 때
         return 0;      // skip (그냥 바로 리턴)
      }


      // bit check (000~111)
      for(int i = 0; i < 3 ;i++){
         if((No >> i) & AndMaskforOneBit) TurnOnOneGPIO(i+1); // 해당 GPIO ON(1)
         else TurnOffOneGPIO(i+1); // 해당 GPIO OFF(0)
      }

      switch(No){ // state number 에 따라 분기
         case 4: // 보행자 초록불
            remainTime = 9 -((HAL_GetTick() - pastTick) / THOUSAND); // 새로 계속 갱신
            if(pastRemainTime != remainTime){
               pastRemainTime = remainTime; // 갱신
               Show7Segment(remainTime);
            }
            break;

         case 5: // 노란 불 2초
            // trigger pedestrian signal (0이면 초록불 ON, 1이면 초록불 OFF)
            // No == 5일 때 2초 남아서 blink

            remainTime = 2 -((HAL_GetTick() - pastTick) / THOUSAND); // 새로 계속 갱신
            Show7Segment(remainTime);
            if(pastRemainTime != remainTime){
               pastRemainTime = remainTime; // 갱신
               Show7Segment(remainTime);
            }

            if( ((HAL_GetTick() - pastTick) / 200) % 2 == 0){
               TurnOnOneGPIO(4);
            }else TurnOffOneGPIO(4);
            break;
      }

   }
   return 0; // 정상 종료
}

// 7 segment를 점등시킴
void Show7Segment(UINT32 displayNum){
   // bit check (000~111)
   for(int i = 0; i < 4 ;i++){
      if((displayNum >> i) & AndMaskforOneBit) TurnOnOneGPIO(i+5); // 해당 GPIO ON(1)
      else TurnOffOneGPIO(i+5); // 해당 GPIO OFF(0)
   }
}

// 내부 LED의 카운트를 바이너리 형태로 점등시킴
void ShowBinaryCount(UINT32 count){
   TurnOffAllLED(); // 초기화
   // bit check (000~111)
   for(int i = 0; i < 4 ;i++){
      if((count >> i) & AndMaskforOneBit ) TurnOnOneLED(i+1); // 해당 내부LED ON(1)
      else TurnOffOneLED(i+1); // 해당 내부 LED OFF(0)
   }
}

// 버튼이 눌렀다 떼 졌는지 체크 (누르는 동안 Blocking)
int CheckIfButtonPushedandBack(UINT32 ButtonNo){
   SetOneButton(ButtonNo);   //Button Setup
   int flag = 0;
   while( GetIDRforButton(ButtonNo)> 0 ){ // 버튼 눌러진 상태일 때 block
      flag = 1; // 한 번이라도 눌러진 상태일 때
   }   // 뗐을 때 while문 탈출
   return flag;
}



// 모든 내부 LED 4개 ON
void TurnOnAllLED(){
   for(int i =1 ; i <= 4; i++){
      TurnOnOneLED(i);
   }
   return;
}

// 모든 내부 LED 4개 OFF
void TurnOffAllLED(){
   for(int i =1 ; i <= 4; i++){
      TurnOffOneLED(i);
   }
   return;
}

// 모든 외부 GPIO 1~8 OFF (초기화)
void TurnOffAllOutGPIO(){
  for(int i =1 ; i <= 8; i++){
     TurnOffOneGPIO(i);
  }
   return;
}

// 모든 내부, 외부 GPIO OFF
void TurnOffAllInOutLED(){
   for(int i =1 ; i <= 4; i++){
      TurnOffOneLED(i);
   }
   for(int i =1 ; i <= 8; i++){
      TurnOffOneGPIO(i);
   }
   return;
}


// 내부 LED 4개 제어
void TurnOnOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
   SetOneLED(No);
   // BSRR reset
   *((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforLED(No)+16));
}


// 외부 GPIO 9 개 제어
void TurnOnOneGPIO(UINT32 No){
   SetOneOutLED(No);
   // BSRR set
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+BSRROFFSET))  |= (SETRESET << getPortforOutGPIO(No)); // ON
}

// 외부 GPIO 9 개 제어
void TurnOffOneGPIO(UINT32 No){
   // BSRR reset
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+BSRROFFSET))  |= (SETRESET << (getPortforOutGPIO(No)+16)); //OFF
}

// 내부 LED 1개 OFF
void TurnOffOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
   // BSRR set
   *((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << getPortforLED(No));
}

// IDR 값 가져옴
UINT32 GetIDRforButton(UINT32 ButtonNo){
   return (*((V_UINT32*)(getBaseAddrforButton(ButtonNo)+IDROFFSET))) & (AndMaskforOneBit << getPortforButton(ButtonNo));
}

// 내부 LED 1개 세팅
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

// 외부 GPIO 1개 세팅
void SetOneOutLED(UINT32 No){
      //MODER OUTPUTMODE
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforOutGPIO(No)*2)); // 해당 2bit를 00으로 초기화
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+MODEROFFSET))  |=  (OUTPUTMODE       << (getPortforOutGPIO(No)*2)); // 원하는 값을 덮어 씀

      //OSPEED VERY HIGH
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (getPortforOutGPIO(No)*2)); // 해당 2bit를 00으로 초기화
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforOutGPIO(No)*2)); // 원하는 값을 덮어 씀

      //PUPDR PULL UP
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforOutGPIO(No)*2)); // 해당 2bit를 00으로 초기화
      *((V_UINT32*)(getBaseAddrforOutGPIO(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforOutGPIO(No)*2)); // 원하는 값을 덮어 씀
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


// 버튼 1개 세팅
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

UINT32 getBaseAddrforOutGPIO(UINT32 LEDNo){ // LED 1~4(외부)
   switch(LEDNo){
      case 1:
      case 2:
         return GPIOG_BASEADDRESS;
      case 3:
      case 4:
      case 9:
         return GPIOC_BASEADDRESS;
      case 5:
      case 6:
      case 7:
      case 8:
         return GPIOF_BASEADDRESS;

   }
}


UINT32 getBaseAddrfromGPIO(char GPIO){ // LED 1~4(외부)
   switch(GPIO){
      case 'G':
         return GPIOG_BASEADDRESS;
      case 'C':
         return GPIOC_BASEADDRESS;
      case 'F':
         return GPIOF_BASEADDRESS;
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

UINT32 getPortforOutGPIO(UINT32 LEDNo){ // 외부 GPIO 1~7
      switch(LEDNo){
         case 1: return 6;  // PG  6 - GPIO 1 (input A - Traffic light)
         case 2: return 7;  // PG  7 - GPIO 2 (input B - Traffic light)
         case 3: return 1;  // PC  1 - GPIO 3 (input C - Traffic light)
         case 4: return 2;  // PC  2 - GPIO 4 (input D - Light Trigger)
         case 5: return 10; // PF 10 - GPIO 5 (7 segment)
         case 6: return 9;  // PF  9 - GPIO 6 (7 segment)
         case 7: return 8;  // PF  8 - GPIO 7 (7 segment)
         case 8: return 7;  // PF  7 - GPIO 8 (7 segment)
         case 9: return 7;  // PC  7 - GPIO 9 (Push Switch control)
      }
}

UINT32 getBaseAddrforButton(UINT32 ButtonNo){ // BTN 1~2 내부 , 3은 외부
   switch(ButtonNo){
      case 1: return GPIOC_BASEADDRESS;
      case 2: return GPIOG_BASEADDRESS;
      case 3: return GPIOC_BASEADDRESS; // 외부 스위치 버튼으로 함!
   }
}

UINT32 getPortforButton(UINT32 ButtonNo){ // BTN 1~2내부, 3은 외부
      switch(ButtonNo){
         case 1: return 12; // PC 12
         case 2: return 3;  // PG  3
         case 3: return 7;  // PC 7 (외부)
      }
}



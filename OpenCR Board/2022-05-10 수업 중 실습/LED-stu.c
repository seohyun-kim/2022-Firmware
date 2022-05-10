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
   // 해당 GPIO의 Clock이 켜져있는지 체크하는 함수 (0:OFF, 1:ON)

void ClockEnable(UINT32 GPIOPort);
   // 해당 port bit에 clock을 Enable 시킴

void MyDelay(UINT32 n);
   // n* 100ms 동안 dalay를 줌 (n=5 : 0.5sec)



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

   if(!CheckClockStatus(GPIOG_BIT))   ClockEnable(GPIOG_BIT);

   //MODER OUTPUTMODE
   *((V_UINT32*)(GPIOG_BASEADDRESS + MODEROFFSET))  &= ~(AndMaskforTwoBit << (7*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(GPIOG_BASEADDRESS + MODEROFFSET))  |=  (OUTPUTMODE       << (7*2)); // 원하는 값을 덮어 씀

   //OSPEED VERY HIGH
   *((V_UINT32*)(GPIOG_BASEADDRESS + OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (7*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(GPIOG_BASEADDRESS + OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (7*2)); // 원하는 값을 덮어 씀

   //PUPDR PULL UP
   *((V_UINT32*)(GPIOG_BASEADDRESS + PUPDROFFSET))  &= ~(AndMaskforTwoBit << (7*2)); // 해당 2bit를 00으로 초기화
   *((V_UINT32*)(GPIOG_BASEADDRESS + PUPDROFFSET))  |=  (PULLUP           << (7*2)); // 원하는 값을 덮어 씀


   *((V_UINT32*)(GPIOG_BASEADDRESS + BSRROFFSET))  |= (SETRESET << (7)); //ON

//   // BSRR set
//   while(1){
//      *((V_UINT32*)(GPIOG_BASEADDRESS + BSRROFFSET))  |= (SETRESET << (7));  //ON
//      MyDelay(5);
//      *((V_UINT32*)(GPIOG_BASEADDRESS + BSRROFFSET))  |= (SETRESET << (7+16)); //OFF
//      MyDelay(5);
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





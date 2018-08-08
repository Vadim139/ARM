///**
// *****************************************************************************
// **
// **  File        : main.c
// **
// **  Abstract    : main function.
// **
// **  Functions   : main
// **
// **  Environment : Atollic TrueSTUDIO(R)
// **
// **  Distribution: The file is distributed ï¿½as is,ï¿½ without any warranty
// **                of any kind.
// **
// **  (c)Copyright Atollic AB.
// **  You may use this file as-is or modify it according to the needs of your
// **  project. Distribution of this file (unmodified or modified) is not
// **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
// **  rights to distribute the assembled, compiled & linked contents of this
// **  file as part of an application binary file, provided that it is built
// **  using the Atollic TrueSTUDIO(R) toolchain.
// **
// *****************************************************************************
// */
//
///* Includes */
//#include "stm32f30x.h"
//#include "stm32f3_discovery.h"
//#include "common.h"
//
///* Private typedef */
//
///* Private define  */
//#define DELAY	(1000)
//
///* Private macro */
//
///* Private variables */
//float a, b, c, d;
//
///* Private function prototypes */
//
///* Private functions */
//
///* Global variables */
//
//
//
//
///**
// **===========================================================================
// **
// **  Abstract: main program
// **
// **===========================================================================
// */
//int main(void)
//{
//	uint32_t ii;
//
//	/* Example use SysTick timer and read System core clock */
//	SysTick_Config(72);  /* 1 us if clock frequency 72 MHz */
//
//	SystemCoreClockUpdate();
//	ii = SystemCoreClock;   /* This is a way to read the System core clock */
//
//	/* Initialize LEDs and User Button available on STM32F3-Discovery board */
//	STM_EVAL_LEDInit(LED3);
//	STM_EVAL_LEDInit(LED4);
//	STM_EVAL_LEDInit(LED5);
//	STM_EVAL_LEDInit(LED6);
//	STM_EVAL_LEDInit(LED7);
//	STM_EVAL_LEDInit(LED8);
//	STM_EVAL_LEDInit(LED9);
//	STM_EVAL_LEDInit(LED10);
//
//	//STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
//
//	while (1)
//	{
//		/* Waiting User Button is pressed */
//		//while (UserButtonPressed == 0x00)
//		{
//			/* Toggle LD3 */
//			STM_EVAL_LEDToggle(LED3);
//			_delay_ms(DELAY);
//
//			/* Toggle LD5 */
//			STM_EVAL_LEDToggle(LED5);
//			_delay_ms(DELAY);
//
//			/* Toggle LD7 */
//			STM_EVAL_LEDToggle(LED7);
//			_delay_ms(DELAY);
//
//			/* Toggle LD9 */
//			STM_EVAL_LEDToggle(LED9);
//			_delay_ms(DELAY);
//
//			/* Toggle LD10 */
//			STM_EVAL_LEDToggle(LED10);
//			_delay_ms(DELAY);
//
//			/* Toggle LD8 */
//			STM_EVAL_LEDToggle(LED8);
//			_delay_ms(DELAY);
//
//			/* Toggle LD6 */
//			STM_EVAL_LEDToggle(LED6);
//			_delay_ms(DELAY);
//
//			/* Toggle LD4 */
//			STM_EVAL_LEDToggle(LED4);
//			_delay_ms(DELAY);
//		}
//	}
//
//	/* Program will never run to this line */
//	return 0;
//}

#include "stdlib.h"
#include "stdio.h"
#include "common.h"
#include "stm32f30x.h"
#include "stm32f30x_conf.h"
#include "stm32f3_discovery.h"
#include "STM32F3_my.h"
#include "lcd_drv.h"
#include "sbit.h"
//#include "SPI.h"
//#include "lcd.h"
#include "lcdlib.h"
#include "board.h"
//#include "HC-SR04.h"

#define Led_Port GPIOB
#define Led1 GPIO_Pin_0
#define Led2 GPIO_Pin_1
#define Led3 GPIO_Pin_2

#define SW_Port GPIOA
#define SW1 GPIO_Pin_1
#define SW2 GPIO_Pin_2
#define SW3 GPIO_Pin_3
#define SW4 GPIO_Pin_4

//void SPI_Configuration(void)
//{
//  	SPI_InitTypeDef  SPI_InitStructure;
//  	GPIO_InitTypeDef GPIO_InitStructure;
//
//  	// Enable SPI1 and GPIO clocks
//  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
//  	RCC_AHBPeriphClockCmd((uint32_t)RCC_AHBPeriph_GPIOB, ENABLE);
//
//  	// Configure SPI2 pins: SCK, MISO and MOSI
//  	GPIO_InitStructure.GPIO_Pin = DATA | CLK;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);
//	GPIO_PinAFConfig(PORT_ctrl, GPIO_PinSource15, GPIO_AF_5);
//	GPIO_PinAFConfig(PORT_ctrl, GPIO_PinSource13, GPIO_AF_5);
//
//
//  	// Configure I/O for Flash Chip select
//  	GPIO_InitStructure.GPIO_Pin = CS | RES;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);
//  	SPI_CS_Enable();
//
//  	// SPI1 configuration
//  	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
//  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//  	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
//  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
//  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//  	SPI_InitStructure.SPI_CRCPolynomial = 7;
//  	SPI_Init(SPI2, &SPI_InitStructure);
//
//  	// Enable SPI1
//  	SPI_Cmd(SPI2, ENABLE);
//}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// LCD lines configuration
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ctrl, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = DATA | CLK | CS | RES ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);

//	// Joystick lines configuration
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_JOY, ENABLE);
//  	GPIO_InitStructure.GPIO_Pin = JOY_UP | JOY_DOWN;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(JOY_PORT, &GPIO_InitStructure);
}
//extern unsigned char bitmap[];
//extern unsigned char bmp[];
extern unsigned char bmp1[];
extern unsigned char bmp2[];
extern unsigned char bmp4[];
extern volatile signed int contrast;
volatile uint8_t ext_flag = 0;
volatile uint8_t active_mot = 0;
volatile uint8_t mot_comp = 0;

//char* intToStr(int n)
//{
//     int i = 0;
//     char tmp[12];
//     static char ret[12];
//     if(n < 0) {
//      *ret = '-';
//      i++;
//      n = -n;
//     }
//     do {
//      *tmp = n % 10 + 48;
//      n -= n % 10;
//      if(n > 9) tmp++;
//     }
//     while(n /= 10);
//     while(ret[i++] = tmp--);
//     return ret;
//}

//char * itoa (int value, char *result, int base)
//{
//    // check that the base if valid
//    if (base < 2 || base > 36) { *result = '\0'; return result; }
//
//    char* ptr = result, *ptr1 = result, tmp_char;
//    int tmp_value;
//
//    do {
//        tmp_value = value;
//        value /= base;
//        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
//    } while ( value );
//
//    // Apply negative sign
//    if (tmp_value < 0) *ptr++ = '-';
//    *ptr-- = '\0';
//    while (ptr1 < ptr) {
//        tmp_char = *ptr;
//        *ptr--= *ptr1;
//        *ptr1++ = tmp_char;
//    }
//    return result;
//}
//char *str;
int main(void)
   {
	int ii;

//	signed char x, y, z, xo = 0, yo = 0, zo = 0;		// x, y, z - MEMS orientation,
															// xo, yo, zo - previous MEMS orientation
				 											// 				used to check whether MEMS
															//				position changed
								// contrast value
		unsigned int k, l;

	/* Example use SysTick timer and read System core clock */
	SysTick_Config(72);  /* 1 us if clock frequency 72 MHz */

//	SystemCoreClockUpdate();
	ii = SystemCoreClock;   /* This is a way to read the System core clock */

//	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

//	LED_init();


	GPIO_PinOut(Led_Port, Led1);
	GPIO_PinOut(Led_Port, Led2);
	GPIO_PinOut(Led_Port, Led3);
//	GPIO_PinOut(GPIOE, GPIO_Pin_All);

//	GPIO_PinIn(SW_Port, SW1);
//  GPIO_PinIn(SW_Port, SW2);
//	GPIO_PinIn(SW_Port, SW3);
//	GPIO_PinIn(SW_Port, SW4);

	EXTI_Config(SW_Port, SW1, EXTI_Trigger_Falling);
	EXTI_Config(SW_Port, SW2, EXTI_Trigger_Falling);
	EXTI_Config(SW_Port, SW3, EXTI_Trigger_Falling);
	EXTI_Config(SW_Port, SW4, EXTI_Trigger_Falling);

//	TIM_Config(TIM3, 6000, 3000);
//	TIM_Config(TIM2, 6000, 6000);
//	TIM_Config(TIM7, 6000, 3000);
//	TIM1_PWM_Config(4, 71, 50);
//	TIM8_PWM_Config(4, 71, 50);
	TIM4_PWM_Config(4, 71, 50);
	TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
	TIM_SetCompare2(TIM4, 0);
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 0);


//	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

//	lcd_init();
//	lcd_number(165);
//	lcd_putchar(' ');
//	lcd_puts("Dzia³a !!");

//	InitSPI();
//	InitLcd();
//	GPIOB -> BSRR = GPIO_Pin_0;
//	GPIOB -> BSRR = GPIO_Pin_1;
//	GPIOB -> BSRR = GPIO_Pin_2;

	HC_init();
	GPIO_Configuration();
//	SPI_Configuration();
//	SPI_CS_Enable();

	// Initialize LCD
		InitLcdNokia();

		// Set contrast
		SetContrast(contrast);
		 _delay_ms(3000);
		 SetContrast(contrast);



		// *****************************************************************
		// Uncomment this code to find best contrast value. Contrast is
		// adjusted with joystick (up-down).
		// *****************************************************************

		// Draw three rectangles (red, green and blue)

		for (k=0; k<44; k++)
			for (l=0; l<132; l++)
				LCDSetPixel(k,l, RED);
		for (k=44; k<88; k++)
			for (l=0; l<132; l++)
				LCDSetPixel(k,l, GREEN);
		for (k=88; k<132; k++)
			for (l=0; l<132; l++)
				LCDSetPixel(k,l, BLUE);

		int j = 42;
//		LCDPutInt(56,2,5,MEDIUM,WIB,WHITE,BLACK);
//		LCDPutInt(j,45,5,LARGE,WOB,WHITE,BLACK);
//		LCDPutInt(6794,70,5,MEDIUM,WIB,PINK,BLACK);
//		LCDPutInt(239,90,5,MEDIUM,WIB,WHITE,BLACK);
		LCDPutInt(3567,2,5,MEDIUM,WIB,WHITE,BLACK);
		LCDPutInt(-875,45,5,LARGE,WOB,WHITE,BLACK);
		LCDPutInt(23.567,70,5,MEDIUM,WIB,PINK,BLACK);
		LCDPutInt(TIM_GetCounter(TIM7),90,5,MEDIUM,WIB,WHITE,BLACK);

//		char str[10];
////		str = intToStr(j);
////		sprintf(str, "%d", j);
//		itoa(j, str, 10);
////		char *string = atoa(1234567890);
////		printf("%s\n", string);
//		LCDPutStr(str, 40, 10, LARGE,WIB, WHITE, BLACK);

//	SetContrast(20);
	_delay_ms(3000);
//	LCDClearScreen(0xFF);
//	LCDWriteKamamiBmp();
//	SetContrast(25);
//	_delay_ms(3000);
//	SetContrast(30);
//	_delay_ms(3000);
//	SetContrast(35);
//	_delay_ms(3000);
//	SetContrast(40);
//	_delay_ms(3000);
//	SetContrast(45);
//	_delay_ms(3000);
//	SetContrast(50);
//	_delay_ms(3000);
//
//	WriteSpiCommand(PASET);
//		WriteSpiData(0);
//		WriteSpiData(131);
//
//		// Set column address range
//		WriteSpiCommand(CASET);
//		WriteSpiData(0);
//		WriteSpiData(131);
//	GPIOE -> BSRR = GPIO_Pin_All;
//LCDSetXY(0,0);
//WriteSpiCommand(PASET);
//WriteSpiData(0);
//WriteSpiData(131);
//
//// Set column address range
//WriteSpiCommand(CASET);
//WriteSpiData(0);
//WriteSpiData(131);
//	Test-Picture
	int i;
		  //red bar
//		  for (i=0;i<132*33;i++) {
			  lcd_set(RED);
//		  }

		  //green bar
//		  for (i=0;i<132*33;i++) {
//			  lcd_set(BLUE);
//		  }

		  //blue bar
//		  for (i=0;i<132*33;i++) {
//			  lcd_set(GREEN);
//		  }

		  //white bar
//		  for (i=0;i<132*33;i++) {
//			  lcd_set(YELLOW);		  }
//		  _delay_ms(1000);


//
//		  LCDSetPixel(120, 120, WHITE);
//		  LCDSetPixel(120, 121, WHITE);
//		  _delay_ms(1000);
//		 	LCDPutChar('A',2,2,SMALL,WIB,WHITE,BLACK);
//		 	  _delay_ms(1000);
//		 	LCDPutChar('B',2,17,MEDIUM,WIB,YELLOW,GREEN);
//		 	  _delay_ms(1000);
//		 	LCDPutChar('C',2,32,LARGE,WIB,BLUE,RED);
//		  _delay_ms(1000);
//		LCDPutChar('A',20,20,LARGE,WOB,WHITE,BLACK);
//		  _delay_ms(1000);
//		LCDPutChar('B',20,30,LARGE,WOB,YELLOW,GREEN);
//		  _delay_ms(1000);
//		LCDPutChar('C',20,40,LARGE,WOB,BLUE,RED);
//		_delay_ms(1000);
//		LCDPutChar('D',20,50,LARGE,WOB,WHITE,BLACK);
//		_delay_ms(1000);
//		LCDPutChar('E',20,60,LARGE,WOB,YELLOW,GREEN);
//		_delay_ms(1000);
//		LCDPutChar('I',20,70,LARGE,WOB,BLUE,RED);
//		_delay_ms(1000);


//		int o = 98;
//		char str[8];
//		dtostrf(o, 1, 1, str); //zamienia ASCI na stringa
//		LCDPutStr(str, 50, 10, LARGE,WIB, WHITE, BLACK);
//			_delay_ms(1000);
		LCDPutStr("Hello World!", 50, 10, LARGE,WIB, WHITE, BLACK);
		LCDPutStr("Witamy w swiecie",80,2,MEDIUM,WOB, RED,WHITE);
		LCDPutStr("     pixeli!    ",71,2,MEDIUM,WIB, BLUE,WHITE);
		LCDPutStr("A to jest maly tekst.",110,2,SMALL,WIB, YELLOW,BROWN);
//		 SetContrast(contrast);

		_delay_ms(2000);
		LCDClearScreen(ORANGE);
		LCDSetRect(12,12,60,60,0,BLUE);
//		 SetContrast(contrast);

//		_delay_ms(2000);
//		LCDSetRect(0,0,33,132,1,RED);
//		LCDSetRect(34,0,66,132,1,BLUE);
//		LCDSetRect(67,0,99,132,1,GREEN);
//		LCDSetRect(100,0,132,132,1,YELLOW);
////		LCDWrite130x130bmp();
//		_delay_ms(2000);
////		n6100_lcd_drawbitmap(1,1,130,130,bitmap);
////		_delay_s(3);
////		n6100_lcd_drawbitmap(1,1,130,130,bmp2);
////		 SetContrast(contrast);
////		_delay_s(5);
//		n6100_lcd_drawbitmap(1,1,130,130,bmp1);
//		 _delay_ms(3000);
//		SetContrast(contrast);

		LCDClearScreen(YELLOW);
		LCDPutInt(HC_get(),70,5,LARGE,WIB,PINK,BLACK);

		TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
		TIM_SetCompare2(TIM4, 0);
		TIM_SetCompare3(TIM4, 0);
		TIM_SetCompare4(TIM4, 0);


//			 _delay_ms(3000);
//			 WriteSpiCommand(SWRESET);
//			 _delay_ms(3000);
//			 WriteSpiCommand(BSTROFF);
//			 _delay_ms(3000);
//			 WriteSpiCommand(BSTRON);
//			 _delay_ms(3000);
//			 WriteSpiCommand(SLEEPIN);
//			 _delay_ms(3000);
//			 WriteSpiCommand(SLEEPOUT);
//			 _delay_ms(3000);
//			 WriteSpiCommand(DALO);
//			 _delay_ms(3000);
//			 WriteSpiCommand(DAL);
//			 _delay_ms(3000);
//			 WriteSpiCommand(DISPOFF);
//			 _delay_ms(3000);
//			 WriteSpiCommand(DISPON);
//			 _delay_ms(3000);
//			 WriteSpiCommand(IDMON);
//			 _delay_ms(3000);
//			 WriteSpiCommand(IDMOFF);
//			 _delay_ms(3000);
//			 WriteSpiCommand(DAL);
						// 12bit per pixel
//		LCDPutStr("A to jest maly tekst.",110,2,SMALL,WOB, YELLOW,BROWN);
//		LCDPutStr("Hello World!", 20, 10, SMALL,WOB, WHITE, BLACK);
//		LCDPutStr("Hello World!", 40, 10, MEDIUM,WOB, WHITE, BLACK);
//		LCDPutStr("Hello World!", 60, 10, LARGE,WOB, WHITE, BLACK);
//		_delay_ms(2000);
		  //Set Constrast
//		  WriteSpiCommand(0x25);
//		  WriteSpiData(46);
//		  _delay_ms(3000);
//		  //Set Constrast
//		  WriteSpiCommand(0x25);
//		  WriteSpiData(31);
//		  _delay_ms(3000);
//		  //Set Constrast
//		  WriteSpiCommand(0x25);
//		  WriteSpiData(15);
//		  _delay_ms(3000);
//		  //Set Constrast
//		  WriteSpiCommand(0x25);
//		  WriteSpiData(0);
//		  _delay_ms(3000);
//		  //Set Constrast
//		  WriteSpiCommand(0x25);
//		  WriteSpiData(-15);
//			_delay_ms(3000);
//			  //Set Constrast
//			  WriteSpiCommand(0x25);
//			  WriteSpiData(-31);
//			  _delay_ms(3000);
//			  //Set Constrast
//			  WriteSpiCommand(0x25);
//			  WriteSpiData(-46);
//			  _delay_ms(3000);
//			  //Set Constrast
//			  WriteSpiCommand(0x25);
//			  WriteSpiData(-63);
//			  _delay_ms(3000);
//			  //Set Constrast
//			  WriteSpiCommand(0x25);
//			  WriteSpiData(63);
//			  _delay_ms(3000);

//TIM_SetCompare1(TIM1,0);
	while (1)
	{
		if(ext_flag)
		{
			LCDPutInt(HC_get(),70,5,LARGE,WIB,PINK,BLACK);
			ext_flag = 0;
		}

		LCDPutInt(active_mot,2,5,MEDIUM,WIB,WHITE,BLACK);
		LCDPutInt(mot_comp,2,30,MEDIUM,WIB,WHITE,BLACK);

		switch (active_mot) {
			case 1:
				TIM_SetCompare1(TIM4, mot_comp);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, 0);
				TIM_SetCompare3(TIM4, 0);
				TIM_SetCompare4(TIM4, 0);
				break;
			case 2:
				TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, mot_comp);
				TIM_SetCompare3(TIM4, 0);
				TIM_SetCompare4(TIM4, 0);
				break;
			case 3:
				TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, 0);
				TIM_SetCompare3(TIM4, mot_comp);
				TIM_SetCompare4(TIM4, 0);
				break;
			case 4:
				TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, 0);
				TIM_SetCompare3(TIM4, 0);
				TIM_SetCompare4(TIM4, mot_comp);
				break;
			default:
				break;
		}
		//				TIM_SetCompare1(TIM1, 13);
//				TIM_SetCompare2(TIM1, 13);
//				TIM_SetCompare3(TIM1, 13);
//				TIM_SetCompare4(TIM1, 13);
//				TIM_SetCompare5(TIM1, 13);
//				TIM_SetCompare6(TIM1, 13);
//				_delay_ms(5000);

//				TIM_SetCompare1(TIM1, 25);
//				TIM_SetCompare2(TIM1, 25);//(25us / 50us = 0.5)
//				TIM_SetCompare3(TIM1, 25);
//				TIM_SetCompare4(TIM1, 25);
//				TIM_SetCompare5(TIM1, 25);
//				TIM_SetCompare6(TIM1, 25);
//				_delay_ms(5000);

//				TIM_SetCompare1(TIM1, 38);
//				TIM_SetCompare2(TIM1, 38);//(38us / 50us = 0.76)
//				TIM_SetCompare3(TIM1, 38);
//				TIM_SetCompare4(TIM1, 38);
//				TIM_SetCompare5(TIM1, 38);
//				TIM_SetCompare6(TIM1, 38);
//				_delay_ms(5000);

//				TIM_SetCompare1(TIM1, 50);
//				TIM_SetCompare2(TIM1, 50);//(50us / 50us = 1.0)
//				TIM_SetCompare3(TIM1, 50);
//				TIM_SetCompare4(TIM1, 50);
//				TIM_SetCompare5(TIM1, 50);
//				TIM_SetCompare6(TIM1, 50);
//				_delay_ms(5000);

//				TIM_SetCompare1(TIM1, 0);//(0us / 50us = 0.0)
//				TIM_SetCompare2(TIM1, 0);
//				TIM_SetCompare3(TIM1, 0);
//				TIM_SetCompare4(TIM1, 0);
//				TIM_SetCompare5(TIM1, 0);
//				TIM_SetCompare6(TIM1, 0);
//				_delay_ms(5000);

//		if(!GPIO_GetState(SW_Port, SW1))
//		{
//			Led_Port -> ODR ^= Led1;
//		_delay_ms(500);
//		}

//		LED3_T;
//		_delay_s(1);
//		LED4_T;
//		_delay_s(1);
//		LED6_T;
//		_delay_s(1);
//		LED8_T;
//		_delay_s(1);
//		LED10_T;
//		_delay_s(1);
//		LED9_T;
//		_delay_s(1);
//		LED7_T;
//		_delay_s(1);
//		LED5_T;
//		_delay_s(1);

	}

	return 0;
}



void EXTI1_IRQHandler(void)
{
//	Led_Port -> ODR ^= Led1;
//	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line1);
//	if(contrast < 63)
//	{
//	contrast++;
//	SetContrast(contrast);
//	}
//		DrawCube(12, 12, 12, 0xFFF);
	if(mot_comp < 50)
		mot_comp++;

}

void EXTI2_TS_IRQHandler(void)
{
//	Led_Port -> ODR ^= Led2;
//	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line2);
//	if(contrast > -63)
//	{
//		contrast--;
//		SetContrast(contrast);
//	}
//		LCDClearScreen(ORANGE);
	if(mot_comp > 0)
		mot_comp--;


}

void EXTI3_IRQHandler(void)
{
	Led_Port -> ODR ^= Led3;
//	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line3);
	ext_flag = 1;
	if(active_mot < 4)
		active_mot++;
//	switch (active_mot) {
//		case 1:
//			TIM_SetCompare1(TIM4, mot_comp);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, 0);
//			TIM_SetCompare3(TIM4, 0);
//			TIM_SetCompare4(TIM4, 0);
//			break;
//		case 2:
//			TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, mot_comp);
//			TIM_SetCompare3(TIM4, 0);
//			TIM_SetCompare4(TIM4, 0);
//			break;
//		case 3:
//			TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, 0);
//			TIM_SetCompare3(TIM4, mot_comp);
//			TIM_SetCompare4(TIM4, 0);
//			break;
//		case 4:
//			TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, 0);
//			TIM_SetCompare3(TIM4, 0);
//			TIM_SetCompare4(TIM4, mot_comp);
//			break;
//		default:
//			break;
//	}

}

void EXTI4_IRQHandler(void)
{
	Led_Port -> ODR ^= Led1;
	Led_Port -> ODR ^= Led2;
	Led_Port -> ODR ^= Led3;
//	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line4);
	if(active_mot > 1)
		active_mot--;
//	switch (active_mot) {
//		case 1:
//			TIM_SetCompare1(TIM4, mot_comp);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, 0);
//			TIM_SetCompare3(TIM4, 0);
//			TIM_SetCompare4(TIM4, 0);
//			break;
//		case 2:
//			TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, mot_comp);
//			TIM_SetCompare3(TIM4, 0);
//			TIM_SetCompare4(TIM4, 0);
//			break;
//		case 3:
//			TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, 0);
//			TIM_SetCompare3(TIM4, mot_comp);
//			TIM_SetCompare4(TIM4, 0);
//			break;
//		case 4:
//			TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//			TIM_SetCompare2(TIM4, 0);
//			TIM_SetCompare3(TIM4, 0);
//			TIM_SetCompare4(TIM4, mot_comp);
//			break;
//		default:
//			break;
//	}

}
//void TIM1_CC_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
//	    {
//	//    	Led_Port -> ODR ^= Led1;
//	        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	        Led_Port -> ODR ^= Led2;
//
//	    }
//}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
    	Led_Port -> ODR ^= Led1;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        Led_Port -> ODR ^= Led3;

    }
}

//void TIM3_IRQHandler()
//{
//    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//    {
////    	Led_Port -> ODR ^= Led1;
//        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//        Led_Port -> ODR ^= Led2;
//
//    }
//}

//void TIM7_IRQHandler()
//{
//    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
//    {
////    	Led_Port -> ODR ^= Led1;
//        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//        Led_Port -> ODR ^= Led2;
//
//    }
//}

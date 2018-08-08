#include "stm32f4xx.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdio.h"
#include "common.h"
#include "STM32F3_my.h"
#include "sbit.h"
#include "lcdlib.h"
#include "board.h"
#include "PCF8583.h"
#include "tm_stm32f4_i2c.h"
#include "tm_stm32f4_spi.h"
#include "OV7670_I2C.h"
#include "lcd_drv.h"

#include "enc424j600.h"
#include "uip_arp.h"
#include "network.h"
#include "avrlibtypes.h"
#include "timer.h"
#include "clock-arch.h"
#include "simple-httpd.h"

#define Led_Port GPIOC
#define Led1 GPIO_Pin_0
#define Led2 GPIO_Pin_1
#define Led3 GPIO_Pin_2

#define SW_Port GPIOD
#define SW1 GPIO_Pin_0
#define SW2 GPIO_Pin_1
#define SW3 GPIO_Pin_2
#define SW4 GPIO_Pin_3

#define M_Port GPIOE
#define M1 GPIO_Pin_2
#define M2 GPIO_Pin_4
#define M3 GPIO_Pin_5
#define M4 GPIO_Pin_6

//#define datal GPIOC
//#define RS GPIO_Pin_7
//#define WR GPIO_Pin_8
//#define RD GPIO_Pin_9
//#define CS GPIO_Pin_10
//#define REST GPIO_Pin_11
//#define LED GPIO_Pin_12

//#define VSYNC 	GPIO_Pin_1
//#define OE 		GPIO_Pin_11
//#define WRST 	GPIO_Pin_12
//#define RRST 	GPIO_Pin_13
//#define WE 		GPIO_Pin_14
//#define RCLK 		GPIO_Pin_8


//#define WRST_H()  GPIOB->BSRRL = WRST
//#define WRST_L()  GPIOB->BSRRH  = WRST
//
//#define RRST_H()  GPIOB->BSRRL = RRST
//#define RRST_L()  GPIOB->BSRRH  = RRST
//
//#define OE_H()    GPIOB->BSRRL = OE
//#define OE_L()    GPIOB->BSRRH  = OE
//
//#define WE_H()    GPIOB->BSRRL = WE
//#define WE_L()    GPIOB->BSRRH  = WE
//
//#define RCLK_H()    GPIOA->BSRRL = RCLK
//#define RCLK_L()    GPIOA->BSRRH  = RCLK


//extern volatile signed int contrast;
///* Adjust them for your own board. */
//
//#if defined(BOARD_OLIMEX_STM32_E407)
//
///* STM32-E407 definitions (the GREEN LED) */
//
//#define BLINK_PORT      GPIOC
//#define BLINK_PIN       13
//#define BLINK_RCC_BIT   RCC_AHB1Periph_GPIOC
//
//#else
//
///* STM32F4DISCOVERY definitions (the GREEN LED) */
//
//#define BLINK_PORT      GPIOD
//#define BLINK_PIN       12
//#define BLINK_RCC_BIT   RCC_AHB1Periph_GPIOD
//
//#endif
//
//#define BLINK_TICKS     SYSTICK_FREQUENCY_HZ/2

// ----------------------------------------------------------------------------
volatile uint32_t iii = 0;
int out = 0;
unsigned int  bn=3;
void UARTSend1(const unsigned char * pucBuffer, unsigned long ulCount);

//extern u8_t uip_buf[UIP_BUFSIZE + 2];
//#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
//void GPIO_Configuration(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	// LCD lines configuration
//  	RCC_AHB1PeriphClockCmd(RCC_AHBPeriph_ctrl, ENABLE);
//  	GPIO_InitStructure.GPIO_Pin = DATA | CLK | CS | RES ;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);
//
////	// Joystick lines configuration
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_JOY, ENABLE);
////  	GPIO_InitStructure.GPIO_Pin = JOY_UP | JOY_DOWN;
////  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////  	GPIO_Init(JOY_PORT, &GPIO_InitStructure);
//}
//volatile u32 a = 0;
//volatile u8 frame[25344];
//volatile u8 c = 0;
//volatile u8 p = 0;

//void simple_httpd_init(void) {
//    uip_listen(HTONS(80));
//
//}
//volatile int gg = 1;


//uint16_t read_port(GPIO_TypeDef* Port)
//{
//	uint16_t l = 0;
//	int i = 0;
//
//	for(;i<16;i++)
//	{
//		if(GPIO_ReadInputDataBit(Port,i))
//			l |= (1<<i);
//		else
//			l &= ~(1<<i);
//
////		l |= (GPIO_ReadInputDataBit(Port,i)<<i);
////		l = l | lGPIO_ReadInputDataBit(Port,i);
//	}
//return l;
////	GPIO_ReadInputDataBit(Port,Pin);
//}
int pos = 0;
volatile uint16_t slave_pos = 1;
int temp = 0;
void Mot_res()
{
	printf("connected\r\nLBStarted Blocking mode\r\n");

	GPIO_PinSet(M_Port,M1);
	GPIO_PinRes(M_Port,M2);
	GPIO_PinRes(M_Port,M3);
	GPIO_PinRes(M_Port,M4);

	_delay_ms(500);

	GPIO_PinRes(M_Port,M1);
	GPIO_PinSet(M_Port,M2);
	GPIO_PinRes(M_Port,M3);
	GPIO_PinRes(M_Port,M4);

	_delay_ms(500);

	GPIO_PinRes(M_Port,M1);
	GPIO_PinRes(M_Port,M2);
	GPIO_PinSet(M_Port,M3);
	GPIO_PinRes(M_Port,M4);

	_delay_ms(500);

	GPIO_PinRes(M_Port,M1);
	GPIO_PinRes(M_Port,M2);
	GPIO_PinRes(M_Port,M3);
	GPIO_PinSet(M_Port,M4);

	_delay_ms(500);

	GPIO_PinSet(M_Port,M1);
	GPIO_PinRes(M_Port,M2);
	GPIO_PinRes(M_Port,M3);
	GPIO_PinRes(M_Port,M4);

	_delay_ms(500);

	pos = 1;

//	temp =
	if(!TM_GPIO_GetInputPinValue(SW_Port,SW4))
		while(slave_pos != 0)
			Step_l(1);
}

//void Step_r(int i)
//{
//	while(i--){
//	if(pos == 1){
//		GPIO_PinRes(M_Port,M1);
//		GPIO_PinSet(M_Port,M2);
//		GPIO_PinRes(M_Port,M3);
//		GPIO_PinRes(M_Port,M4);
//		pos = 2;
//	}
//	else if(pos == 2){
//		GPIO_PinRes(M_Port,M1);
//		GPIO_PinRes(M_Port,M2);
//		GPIO_PinSet(M_Port,M3);
//		GPIO_PinRes(M_Port,M4);
//		pos = 3;
//	}
//	else if(pos == 3){
//		GPIO_PinRes(M_Port,M1);
//		GPIO_PinRes(M_Port,M2);
//		GPIO_PinRes(M_Port,M3);
//		GPIO_PinSet(M_Port,M4);
//		pos = 4;
//	}
//	else if(pos == 4){
//		GPIO_PinSet(M_Port,M1);
//		GPIO_PinRes(M_Port,M2);
//		GPIO_PinRes(M_Port,M3);
//		GPIO_PinRes(M_Port,M4);
//		pos = 1;
//	}
//	_delay_ms(50);
////	_delay_us(500);
//	}
//}
// && slave_pos != 0
//void Step_l(int i)
//{
//	while(i-- && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
//	if(pos == 1 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
//		GPIO_PinRes(M_Port,M1);
//		GPIO_PinRes(M_Port,M2);
//		GPIO_PinRes(M_Port,M3);
//		GPIO_PinSet(M_Port,M4);
//		pos = 4;
//	}
//	else if(pos == 2 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
//		GPIO_PinSet(M_Port,M1);
//		GPIO_PinRes(M_Port,M2);
//		GPIO_PinRes(M_Port,M3);
//		GPIO_PinRes(M_Port,M4);
//		pos = 1;
//	}
//	else if(pos == 3 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
//		GPIO_PinRes(M_Port,M1);
//		GPIO_PinSet(M_Port,M2);
//		GPIO_PinRes(M_Port,M3);
//		GPIO_PinRes(M_Port,M4);
//		pos = 2;
//	}
//	else if(pos == 4 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
//		GPIO_PinRes(M_Port,M1);
//		GPIO_PinRes(M_Port,M2);
//		GPIO_PinSet(M_Port,M3);
//		GPIO_PinRes(M_Port,M4);
//		pos = 3;
//	}
//	_delay_ms(4);
//	}
//}

void Step_r(int i)
{
	while(i--){
	if(pos == 1){
		GPIO_PinSet(M_Port,M1);
		GPIO_PinSet(M_Port,M2);
		GPIO_PinRes(M_Port,M3);
		GPIO_PinRes(M_Port,M4);
		pos = 2;
	}
	else if(pos == 2){
		GPIO_PinSet(M_Port,M1);
		GPIO_PinRes(M_Port,M2);
		GPIO_PinRes(M_Port,M3);
		GPIO_PinSet(M_Port,M4);
		pos = 3;
	}
	else if(pos == 3){
		GPIO_PinRes(M_Port,M1);
		GPIO_PinRes(M_Port,M2);
		GPIO_PinSet(M_Port,M3);
		GPIO_PinSet(M_Port,M4);
		pos = 4;
	}
	else if(pos == 4){
		GPIO_PinRes(M_Port,M1);
		GPIO_PinSet(M_Port,M2);
		GPIO_PinSet(M_Port,M3);
		GPIO_PinRes(M_Port,M4);
		pos = 1;
	}
	_delay_ms(6);
//	_delay_us(500);
	}
}
//// && slave_pos != 0
void Step_l(int i)
{
	while(i-- && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
	if(pos == 1 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
		GPIO_PinSet(M_Port,M1);
		GPIO_PinRes(M_Port,M2);
		GPIO_PinRes(M_Port,M3);
		GPIO_PinSet(M_Port,M4);
		pos = 4;
	}
	else if(pos == 2 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
		GPIO_PinSet(M_Port,M1);
		GPIO_PinSet(M_Port,M2);
		GPIO_PinRes(M_Port,M3);
		GPIO_PinRes(M_Port,M4);
		pos = 1;
	}
	else if(pos == 3 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
		GPIO_PinRes(M_Port,M1);
		GPIO_PinSet(M_Port,M2);
		GPIO_PinSet(M_Port,M3);
		GPIO_PinRes(M_Port,M4);
		pos = 2;
	}
	else if(pos == 4 && slave_pos != 0 && !TM_GPIO_GetInputPinValue(SW_Port,SW4)){
		GPIO_PinRes(M_Port,M1);
		GPIO_PinRes(M_Port,M2);
		GPIO_PinSet(M_Port,M3);
		GPIO_PinSet(M_Port,M4);
		pos = 3;
	}
	_delay_ms(4);
	}
}


char str[17];
int buff[2];

void init_USART1(uint32_t baudrate){

  /* This is a concept that has to do with the libraries provided by ST
  * to make development easier the have made up something similar to
  * classes, called TypeDefs, which actually just define the common
  * parameters that every peripheral needs to work correctly
  *
  * They make our life easier because we don't have to mess around with
  * the low level stuff of setting bits in the correct registers
  */
  GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
  USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
  NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

  /* enable APB2 peripheral clock for USART1
  * note that only USART1 and USART6 are connected to APB2
  * the other USARTs are connected to APB1
  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* enable the peripheral clock for the pins used by
  * USART1, PB6 for TX and PB7 for RX
  */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* This sequence sets up the TX and RX pins
  * so they work correctly with the USART1 peripheral
  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Pins 6 (TX) and 7 (RX) are used
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 			// the pins are configured as alternate function so the USART peripheral has access to them
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		// this defines the IO speed and has nothing to do with the baudrate!
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			// this defines the output type as push pull mode (as opposed to open drain)
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			// this activates the pullup resistors on the IO pins

  GPIO_Init(GPIOB, &GPIO_InitStruct);					// now all the values are passed to the GPIO_Init() function which sets the GPIO registers

  /* The RX and TX pins are now connected to their AF
  * so that the USART1 can take over control of the
  * pins
  */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); //
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

  /* Now the USART_InitStruct is used to define the
  * properties of USART1
  */
  USART_InitStruct.USART_BaudRate = baudrate;				// the baudrate is set to the value we passed into this init function
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
  USART_InitStruct.USART_StopBits = USART_StopBits_1;		// we want 1 stop bit (standard)
  USART_InitStruct.USART_Parity = USART_Parity_No;		// we don't want a parity bit (standard)
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver
  USART_Init(USART1, &USART_InitStruct);					// again all the properties are passed to the USART_Init function which takes care of all the bit setting


  /* Here the USART1 receive interrupt is enabled
  * and the interrupt controller is configured
  * to jump to the USART1_IRQHandler() function
  * if the USART1 receive interrupt occurs
  */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		 // we want to configure the USART1 interrupts
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
  NVIC_Init(&NVIC_InitStructure);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff

  // finally this enables the complete USART1 peripheral
  USART_Cmd(USART1, ENABLE);
}

/*- Interruption handler -----------------------------------------------------*/
volatile char buf;
volatile int state = 0;
volatile int res,left,right = 0;
// this is the interrupt request handler (IRQ) for ALL USART1 interrupts
void USART1_IRQHandler(void){

  // check if the USART1 receive interrupt flag was set
  if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
	  if(state == 0){
		  buf = USART1->DR;
		  buff[0] = 0;
	  	  state = 1;
	  }else if(state == 1){
		  buff[1] = USART1->DR;
		  buff[0] += buff[1];
		  if(buff[1] == 0){
			  itoa(buff[0],str,10);
			  UARTSend1(str,4);
			  if(buf == 'l'){
				  strcpy(str,(" krokow w lewo\n"));
				  UARTSend1(str,15);
//				  Step_l(buff[0]);
				  slave_pos -= buff[0];
				  left = 1;
//				  slave_pos -= buff[0];
			  }else if(buf == 'r'){
				  strcpy(str," krokow w prawo\n");
				  UARTSend1(str,15);
				  slave_pos += buff[0];
				  right = 1;
//				  Step_r(buff[0]);
//				  slave_pos += buff[0];
			  }
			  state = 0;

		  }else
			  ;


	  }
  }
}

void UARTSend1(const unsigned char *pucBuffer, unsigned long ulCount)
{
  //
  // Loop while there are more characters to send.
  //
  while(ulCount--)
  {
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }
    USART_SendData(USART1, (uint8_t) *pucBuffer++);
    /* Loop until the end of transmission */

  }
}
volatile int tim_c = 0;
int main(void)

{
	SysTick_Config(168);  /* 1 us if clock frequency 168 MHz */

	printf("Hej, tu STM ;)");

	EXTI_Config(SW_Port, SW1,EXTI_Trigger_Rising);
	EXTI_Config(SW_Port, SW2,EXTI_Trigger_Rising);
	EXTI_Config(SW_Port, SW3,EXTI_Trigger_Rising);
	EXTI_Config(SW_Port, SW4,EXTI_Trigger_Rising);

	TIM4_PWM_Config(4, 83, 50);

//	TIM1_PWM_Config(1, 168, 50);
TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
TIM_SetCompare2(TIM4, 0);
TIM_SetCompare3(TIM4, 0);
TIM_SetCompare4(TIM4, 0);

TIM_Config(TIM3,42000,500);

	GPIO_PinOut(M_Port, M1);
	GPIO_PinOut(M_Port, M2);
	GPIO_PinOut(M_Port, M3);
	GPIO_PinOut(M_Port, M4);

	init_USART1(9600);
//	GPIO_PinRes(M_Port,M1);
//	GPIO_PinRes(M_Port,M2);
//	GPIO_PinRes(M_Port,M3);
//	GPIO_PinRes(M_Port,M4);

	Mot_res();
	slave_pos = 1;
	slave_pos = 0;
	  strcpy(str,"ready\n");
	  buff[0] = USART1->DR;
	  UARTSend1(str,5);

	while(1)
	{
		if(res == 1){
			Mot_res();
			res = 0;
		}
		if(right == 1){
			Step_r(buff[0]);
			right = 0;
			buff[0] = 0;
		}
		if(left == 1){
			Step_l(buff[0]);
			left = 0;
			buff[0] = 0;
		}
		delay(500);
	}










////iii = 4;
//unsigned int k, l;
//int ret = 0;
//u8 data = 0;
//	int ii;
//
////u8 frame[25344];
//for(uint16_t o = 0;o<25344;o++)
//{
//	frame[o] = 10;
//}
//
//		/* Example use SysTick timer and read System core clock */
//		SysTick_Config(168);  /* 1 us if clock frequency 168 MHz */
//
//	//	SystemCoreClockUpdate();
//		ii = SystemCoreClock;   /* This is a way to read the System core clock */
//		EXTI_Config(GPIOA, GPIO_Pin_2,EXTI_Trigger_Falling);
//		EXTI_Config(GPIOA, GPIO_Pin_3,EXTI_Trigger_Falling);
//  LED_init();
//  LEDs_on();
//
////  	GPIO_PinOut(Led_Port, Led2);
////  	GPIO_PinOut(GPIOA, GPIO_Pin_2);
//  lcd_init();
//  lcd_blank();
////  while(gg);
//  lcd_puts("Wyszlem");
//
//////	data = OV7670_read1(0x0A);
//////	ret = OV7670_read(0x0A, &data);
////////////////////////////////////////////////////////////////////
////		GPIO_PinInit(GPIOE, GPIO_Pin_0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);// DATA 0-7
////		GPIO_PinInit(GPIOE, GPIO_Pin_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////		GPIO_PinInit(GPIOE, GPIO_Pin_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////		GPIO_PinInit(GPIOE, GPIO_Pin_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////		GPIO_PinInit(GPIOE, GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////		GPIO_PinInit(GPIOE, GPIO_Pin_5, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////		GPIO_PinInit(GPIOE, GPIO_Pin_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////		GPIO_PinInit(GPIOE, GPIO_Pin_7, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////
////		GPIO_PinInit(GPIOB, GPIO_Pin_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //VSYNC
//////
////		GPIO_PinInit(GPIOB, GPIO_Pin_11, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); // OE
////		GPIO_PinInit(GPIOB, GPIO_Pin_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); // WRST
////		GPIO_PinInit(GPIOB, GPIO_Pin_13, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); // RRST
////		GPIO_PinInit(GPIOB, GPIO_Pin_14, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); // WE
//////
////		GPIO_PinInit(GPIOA, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); // RCLK
////
////		STM_EVAL_PBInit(GPIO_Pin_0,1);
////////////////////////////////////////////////////////////////////
////		I2C_Config(SCCB_Camera,I2C_Ack_Enable);
//
////		USART_init();
//
////  		GPIO_PinInit(GPIOC, GPIO_Pin_0, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_3, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_5, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_6, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_7, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_9, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_10, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_11, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_13, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_14, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_15, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
//
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_0);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_1);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_2);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_3);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_4);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_5);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_6);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_7);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_8);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_9);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_10);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_11);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_12);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_13);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_14);
//	TM_GPIO_SetPinAsOutput(datal,GPIO_Pin_15);
//
//  		GPIO_PinRes(GPIOC,GPIO_Pin_0);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_1);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_2);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_3);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_4);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_5);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_6);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_7);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_8);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_9);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_10);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_11);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_12);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_13);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_14);
//  		GPIO_PinRes(GPIOC,GPIO_Pin_15);
//
//  		GPIO_PinInit(GPIOE, GPIO_Pin_7, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //RS
//  		GPIO_PinInit(GPIOE, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //WR
//  		GPIO_PinInit(GPIOE, GPIO_Pin_9, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //RD
//  		GPIO_PinInit(GPIOE, GPIO_Pin_10, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //CS
//  		GPIO_PinInit(GPIOE, GPIO_Pin_11, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //REST
//  		GPIO_PinInit(GPIOE, GPIO_Pin_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); //LED
//
//
//  		GPIO_PinSet(GPIOE,RS);
//  		GPIO_PinSet(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,RD);
//  		GPIO_PinSet(GPIOE,CS);
//  		GPIO_PinSet(GPIOE,REST);
//  		GPIO_PinRes(GPIOE,LED);
//
//  		GPIO_PinRes(GPIOE,REST);
//  		_delay_ms(100);
//  		GPIO_PinSet(GPIOE,REST);
//  		_delay_ms(100);
//  		GPIO_PinRes(GPIOE,CS);
//  		GPIO_PinRes(GPIOE,RS);
//
////  		TM_GPIO_SetPortValue(datal, 0);
//  		datal -> BSRRH = 0xFFFF;
//
//  		GPIO_PinRes(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,RS);
//
////  		TM_GPIO_SetPortValue(datal, 1);
//  		datal -> BSRRL = 1;
//
//  		GPIO_PinRes(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,CS);
//
//  		GPIO_PinRes(GPIOE,CS);
//  		GPIO_PinRes(GPIOE,RS);
//
////  		TM_GPIO_SetPortValue(datal, 0);
//  		datal -> BSRRH = 0xFFFF;
//
//  		GPIO_PinRes(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,WR);
//  		GPIO_PinSet(GPIOE,RS);
//
////  		GPIO_PinInit(GPIOC, GPIO_Pin_0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_5, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_7, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_8, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_9, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_10, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_13, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_14, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
////  		GPIO_PinInit(GPIOC, GPIO_Pin_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
//
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_0);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_1);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_2);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_3);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_4);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_5);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_6);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_7);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_8);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_9);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_10);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_11);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_12);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_13);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_14);
//  		TM_GPIO_SetPinAsInput(datal,GPIO_Pin_15);
//  		GPIO_PinRes(GPIOE,RD);
////  		lcd_number(read_port(datal));
//  		lcd_number(TM_GPIO_GetPortInputValue(datal));
////  		zmienna = dane;   //zmienna zawsze przyjmuje 0x8988
//  		GPIO_PinSet(GPIOE,RD);
//  		GPIO_PinSet(GPIOE,CS);
//
//  		_delay_ms(5000);
////  		while(1){
////  			lcd_blank();
////  			lcd_number(read_port(datal));
//////  			int p = 0;
//////  			for(;p<16;p++)
//////  			{
//////  				if(GPIO_ReadInputDataBit(datal,p))
//////  					lcd_number(p);
//////  			}
//////  			lcd_number(gg);
////  			_delay_ms(500);
////  		}
//
////		TM_SPI_Init(SPI3, TM_SPI_PinsPack_2);
////		GPIO_PinInit(GPIOB, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz); // CS
//
//	    //Init network
////	    network_init();
////	    LEDs_off();
////
//	    lcd_blank();
//	    lcd_puts("To dziala!  ");
//
////	    write_reg(EUDAND, 1234);
////	    lcd_lnumber(read_reg(EUDAND));
////	    lcd_lnumber(1000);
//	    //Basic static variables
//	    int i;
////	    uip_ipaddr_t ipaddr; //IP Address
////	    struct uip_eth_addr mac_addr; //MAC Address
////	    struct timer periodic_timer, arp_timer;
//
//	    //Read MAC from ethernet chip
////	    network_get_MAC((u8_t *) & mac_addr);
//
////	    //UIP initialization
////	    uip_init();
////	    //Set MAC address in UIP (not to network card, this is only for arp)
////	    uip_setethaddr(mac_addr);
////
////	    simple_httpd_init();
////
////	    uip_ipaddr(ipaddr, 192,168,1,60);
////	    uip_sethostaddr(ipaddr);
////	    uip_ipaddr(ipaddr, 192,168,1,254);
////	    uip_setdraddr(ipaddr);
////	    uip_ipaddr(ipaddr, 255, 255, 255, 0);
////	    uip_setnetmask(ipaddr);
//
//
//
//
//
////			TIM1_PWM_Config(1, 1, 1680);
////			TIM_SetCompare1(TIM1, 840);//(0us / 50us = 0.0)
//
////			TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
//
////			NVIC_InitTypeDef nvicStructure;
////			nvicStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
////			nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
////			nvicStructure.NVIC_IRQChannelSubPriority = 1;
////			nvicStructure.NVIC_IRQChannelCmd = ENABLE;
////			NVIC_Init(&nvicStructure);
//
////		  TIM_Config(TIM1,42000,2000);
////		  TIM_Config(TIM2,42000,2000);
////		  TIM_Config(TIM3,42000,1000);
////		  TIM_Config(TIM8,42000,4000);
//			///////////////////////////////////////////////////////////////////////////
//
//		/* Configuration for QCIF format */
//
////		// COM3 register: Enable format scaling
////		ret = OV7670_read(0x0C, &data);
////		data = data | 0b00001000;
////		OV7670_write(0x0C, &data);
////
////		// COM7 register: Select QCIF format
////		ret = OV7670_read(0x0C, &data);
////		data = (data & 0b11000111) | 0b00001000;
////		OV7670_write(0x12, &data);
////		///////////////////////////////////////////////////////////////////////////
////
////		OE_H();
////		WE_H();
//////		RCLK_H();
////
////		WRST_H();
////		RRST_H();
////
////		WRST_L();
////		RRST_L();
////		_delay_ms(1);
////		WRST_H();
////		RRST_H();
////		_delay_ms(1);
////		EXTI_Config(GPIOB, VSYNC, EXTI_Trigger_Rising);
////		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
////		out = 1;
////		_delay_ms(100);
////		while(1)
////		{
////			while(bn == 0)
////			{
////				c=1;
////				a = 0;
//////		out = 1;
////
//////		_delay_ms(100);
////
////		OE_L();
////		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
////		_delay_ms(1500);
//////		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
//////		u8 p = 1;
//////		u8 in = 0;
//////		u32 g = 0;
//////		for (uint32_t a = 0; a < 144; a++) {// * 176 * 2
//////
//////			RCLK_H();
//////			_delay_us(1);
//////			frame[a] = GPIOE->IDR & 0x00FF; //读高位
//////			RCLK_L();
//////
////////			if(p % 2 == 0)
////////			{
////////				frame[g] = in;
////////				g++;
////////				p = 1;
////////			}else
////////				p++;
//////
//////			// LCD_WriteRAM(c_data);//写RGB数据到TFT GRAM
////////		               USART_SendData(USART2, frame[a]);
////////		               _delay_us(40);
//////
//////		}
////
////		u32 b = 0;
////		for (int j = 0; j < 1; j++) {
////			for (int i = 0; i < a; i++) {
////				USART_SendData(USART2, frame[b]);
////				b++;
////				delay_qs(200);
////			}
////bn = 3;
////		}
////		}
//// }
//////		GPIO_PinSet(GPIOB,GPIO_Pin_11);
//		///////////////////////////////////////////////////////////////////////////
////		  OE_L();
////		  WE_H();
//////		  _delay_ms(1);
////		  bn = 3;
////		RRST_L();
////		RCLK_L();
////		RCLK_H();
////		RCLK_L();
////		RRST_H();
////		RCLK_H();
////		  for(uint32_t a=0;a<144*176;a++)
////		   {
////			  RCLK_L(); ;
////			  RCLK_H();
////			  RCLK_L();
////			  RCLK_H();
////		  }
//////		  GPIO_PinSet(GPIOB,GPIO_Pin_11);
////	////////////////////////////////////////
////	while (1) {
//		if (bn == 2) {
////
////			RRST_L();
////			RCLK_L();
////			RCLK_H();
////			RCLK_L();
////			RRST_H();
////			RCLK_H();
////			u8 p = 1;
////			u8 in = 0;
////			u32 g = 0;
//////			OE_H();
////			for (uint32_t a = 0; a < 144 * 176 * 2; a++) {
////
////				RCLK_L();
////				in = GPIOE->IDR & 0x00FF; //读高位
////				RCLK_H();
////
////				if(p % 2 == 0)
////				{
////					frame[g] = in;
////					g++;
////					p = 1;
////				}else
////					p++;
////
////				// LCD_WriteRAM(c_data);//写RGB数据到TFT GRAM
//////		               USART_SendData(USART2, frame[a]);
//////		               _delay_us(40);
////
////			}
////			u32 b = 0;
////			for (int j = 0; j < 176; j++) {
////				for (int i = 0; i < 144; i++) {
////					USART_SendData(USART2, frame[b]);
////					b++;
////					delay_qs(50);
////				}
////
////			}
//////		          	for (int j = 0; j < 176; j++)
//////		          	{
//////		          		for (int i = 0; i < 144; i++)
//////		          		{
//////		          			USART_SendData(USART2, data);
//////		          			data++;
//////		          			if (data > 15)
//////		          				data = 0;
//////		          			delay_qs(50);
//////		          		}
//////
//////		          	}
////		           bn=3;
////		         }
////		       }
//  //////////////////////////////////////////////////////////////////////////////////////////
//
////	GPIO_PinOut(Led_Port, Led1);
////	GPIO_PinOut(Led_Port, Led2);
////	GPIO_PinOut(Led_Port, Led3);
////	GPIO_PinOut(GPIOE, GPIO_Pin_All);
//
////	GPIO_PinIn(SW_Port, SW1);
////  GPIO_PinIn(SW_Port, SW2);
////	GPIO_PinIn(SW_Port, SW3);
////	GPIO_PinIn(SW_Port, SW4);
////	/* Set variables used */
////	    GPIO_InitTypeDef GPIO_InitStruct;
////	    EXTI_InitTypeDef EXTI_InitStruct;
////	    NVIC_InitTypeDef NVIC_InitStruct;
////
////	    /* Enable clock for GPIOD */
////	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
////	    /* Enable clock for SYSCFG */
////	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
////
////	    /* Set pin as input */
////	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
////	    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
////	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
////	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
////	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
////	    GPIO_Init(GPIOE, &GPIO_InitStruct);
////
////	    /* Tell system that you will use PD0 for EXTI_Line0 */
////	    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);
////
////	    /* PD0 is connected to EXTI_Line0 */
////	    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
////	    /* Enable interrupt */
////	    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
////	    /* Interrupt mode */
////	    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
////	    /* Triggers on rising and falling edge */
////	    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
////	    /* Add to EXTI */
////	    EXTI_Init(&EXTI_InitStruct);
////
////	    /* Add IRQ vector to NVIC */
////	    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
////	    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
////	    /* Set priority */
////	    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
////	    /* Set sub priority */
////	    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
////	    /* Enable interrupt */
////	    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
////	    /* Add to NVIC */
////	    NVIC_Init(&NVIC_InitStruct);
////
////	    /* Enable clock for GPIOD */
////	    	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
////	    	    /* Enable clock for SYSCFG */
////	    	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
////
////	    	    /* Set pin as input */
////	    	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
////	    	    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
////	    	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
////	    	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
////	    	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
////	    	    GPIO_Init(GPIOE, &GPIO_InitStruct);
////
////	    	    /* Tell system that you will use PD0 for EXTI_Line0 */
////	    	    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
////
////	    	    /* PD0 is connected to EXTI_Line0 */
////	    	    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
////	    	    /* Enable interrupt */
////	    	    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
////	    	    /* Interrupt mode */
////	    	    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
////	    	    /* Triggers on rising and falling edge */
////	    	    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
////	    	    /* Add to EXTI */
////	    	    EXTI_Init(&EXTI_InitStruct);
////
////	    	    /* Add IRQ vector to NVIC */
////	    	    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
////	    	    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
////	    	    /* Set priority */
////	    	    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
////	    	    /* Set sub priority */
////	    	    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
////	    	    /* Enable interrupt */
////	    	    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
////	    	    /* Add to NVIC */
////	    	    NVIC_Init(&NVIC_InitStruct);
//
////  	GPIO_PinIn(GPIOA, GPIO_Pin_0);
////  	GPIO_PinInit(GPIOA,GPIO_Pin_0,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
////  	EXTI_Config(GPIOA, GPIO_Pin_0,EXTI_Trigger_Rising);
//
//
////	EXTI_Config(SW_Port, SW1, EXTI_Trigger_Falling);
////	EXTI_Config(SW_Port, SW2, EXTI_Trigger_Falling);
////	EXTI_Config(SW_Port, SW3, EXTI_Trigger_Falling);
////	EXTI_Config(SW_Port, SW4, EXTI_Trigger_Falling);
//
////	Led_Port -> ODR ^= Led1;
////	Led_Port -> ODR ^= Led2;
////	Led_Port -> ODR ^= Led3;
//
////	TIM_Config(TIM3, 6000, 3000);
////	TIM_Config(TIM2, 6000, 6000);
////	TIM_Config(TIM7, 6000, 3000);
////	TIM1_PWM_Config(4, 71, 50);
////	TIM8_PWM_Config(4, 71, 50);
////	TIM4_PWM_Config(4, 83, 50);
////	TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
////	TIM_SetCompare2(TIM4, 0);
////	TIM_SetCompare3(TIM4, 0);
////	TIM_SetCompare4(TIM4, 0);
//
////  TIM1_PWM_Config(4,16800,10000);
//
////  TIM_Config(TIM1,42000,2000);
////  TIM_Config(TIM2,42000,2000);
////  TIM_Config(TIM3,42000,1000);
////  TIM_Config(TIM8,42000,4000);
//
//  int seconds = 0;
//
//	// Initialize LCD
////    GPIO_Configuration();
////	InitLcdNokia();
//
////	MCO1_Init();
////	Hardware_InitI2C();
////	 ret = camera_read_reg(0x0A,&data);
//	// PCF init
//
//
////	PCF8583_init();
////	LCDPutInt(reg,20,20,MEDIUM,WIB,WHITE,BLACK);
//
////	PCF8583_set_date(27,1,2015);
////	PCF8583_set_time(21,51,0,0);
//	iii = 1;
//
////	lcd_set(PINK);
//
//	// Set contrast
////	SetContrast(contrast);
////	_delay_ms(3000);
////	SetContrast(contrast);
//
//	// *****************************************************************
//	// Uncomment this code to find best contrast value. Contrast is
//	// adjusted with joystick (up-down).
//	// *****************************************************************
//
//	// Draw three rectangles (red, green and blue)
//
////	for (k = 0; k < 44; k++)
////		for (l = 0; l < 132; l++)
////			LCDSetPixel(k, l, RED);
////	for (k = 44; k < 88; k++)
////		for (l = 0; l < 132; l++)
////			LCDSetPixel(k, l, GREEN);
////	for (k = 88; k < 132; k++)
////		for (l = 0; l < 132; l++)
////			LCDSetPixel(k, l, BLUE);
//
////	LCDPutInt(ret,20,20,MEDIUM,WIB,WHITE,BLACK);
////	LCDPutInt(data,40,20,MEDIUM,WIB,WHITE,BLACK);
////    puttime(20,20,3,MEDIUM,WIB,WHITE,BLACK);
////    putdate(40,20,3,MEDIUM,WIB,WHITE,BLACK);
////  TIM_TimeBaseInitTypeDef    TIM_InitStruct;
////
////  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
////
////  TIM_InitStruct.TIM_Prescaler = 42000 - 1;                // This will configure the clock to 2 kHz
////  TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;     // Count-up timer mode
////  TIM_InitStruct.TIM_Period = 2000 - 1;                    // 2 kHz down to 1 Hz = 1 second
////  TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        // Divide clock by 1
////  TIM_InitStruct.TIM_RepetitionCounter = 0;                // Set to 0, not used
////  TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
////  /* TIM2 enable counter */
////  TIM_Cmd(TIM2, ENABLE);
//
//  /* Infinite loop */
//  while (1)
//    {
////	  while (1) {
////	 	        uip_len = network_read();
////
////	 	        if (uip_len > 0) {
////	 	            if (BUF->type == htons(UIP_ETHTYPE_IP)) {
////	 	                uip_arp_ipin();
////	 	                uip_input();
////	 	                if (uip_len > 0) {
////	 	                    uip_arp_out();
////	 	                    network_send();
////	 	                }
////	 	            } else if (BUF->type == htons(UIP_ETHTYPE_ARP)) {
////	 	                uip_arp_arpin();
////	 	                if (uip_len > 0) {
////	 	                    network_send();
////	 	                }
////	 	            }
////
////	 	        } else if (timer_expired(&periodic_timer)) {
////	 	            timer_reset(&periodic_timer);
////
////	 	            for (i = 0; i < UIP_CONNS; i++) {
////	 	                uip_periodic(i);
////	 	                if (uip_len > 0) {
////	 	                    uip_arp_out();
////	 	                    network_send();
////	 	                }
////	 	            }
////
////	 	            if (timer_expired(&arp_timer)) {
////	 	                timer_reset(&arp_timer);
////	 	                uip_arp_timer();
////	 	            }
////	 	        }
//
//
////	 	    }
////	 	    return 0;
////	 	}
//
////	  USART_SendData(USART2, 123);
////	  if(GPIO_GetState(GPIOA,GPIO_Pin_0))
////	  {
////		  USART_SendData(USART2, 159);
////	  }
////	  _delay_ms(2000);
//
////	  if (TIM_GetFlagStatus(TIM8, TIM_FLAG_Update) != RESET)
////	  {
////	  TIM_ClearFlag(TIM8, TIM_IT_Update);
////	  GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
////	  }
//
//      /* Assume the LED is active low */
//
//      /* Turn on led by setting the pin low */
////      GPIO_ResetBits(BLINK_PORT, (1 << BLINK_PIN));
//
////      _delay_s(1);
////      Delay(BLINK_TICKS);
//
//      /* Turn off led by setting the pin high */
////      GPIO_SetBits(BLINK_PORT, (1 << BLINK_PIN));
////
////      _delay_s(1);
////      Delay(BLINK_TICKS);
//
////      ++seconds;
//
//    }
////EXTI4_IRQ
////  EXTI
}

//void TIM2_IRQHandler(void)
//{
////    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
////    {
////    	LED4_T;
////    	iii++;
////    }
//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//    {
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//        LED4_T;
//        iii++;
//    }
////	LED4_T;
//}

//void USART2_IRQHandler(void) {
//	uint16_t data = 0;
//	data = USART_ReceiveData(USART2);
////	USART_SendData(USART2, data + 5);
//
////	for (int j = 0; j < 176; j++)
////	{
////		for (int i = 0; i < 144; i++)
////		{
////			USART_SendData(USART2, data);
////			data++;
////			if (data > 15)
////				data = 0;
////			delay_qs(50);
////		}
////
////	}
////	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, DISABLE);
////	OV7670_read(0x0A, &data);
////	USART_SendData(USART2, data);
////	USART_SendData(USART2, data);
//	bn=0;
////	delay_ms(2000);
//}
//
//void TIM1_UP_TIM10_IRQHandler()
//{
//    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
//    {
////		delay_qs(1);
////		frame[a] = GPIOE->IDR & 0x00FF;
////		USART_SendData(USART2, 20);
//		if (c==1)
//		{
//			delay_qs(1);
////			delay(4);
////			frame[a] = GPIOE->IDR & 0x00FF;
//			if(p % 2 == 0)
//			{
//				frame[a] = GPIOE->IDR & 0x00FF;
//				a++;
//				p = 1;
//			}else
//			{
////				GPIOE->IDR & 0x00FF;
//				p++;
//			}
//		}
////			a++;
////		delay_qs(50);
//		if(a == (144*176))
//			TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
////        if (iii)  frame[a]
////        {
//////        	PCF8583_set_time(21,55,0,0);
//////        puttime(20,20,3,MEDIUM,WIB,WHITE,BLACK);
//////        putdate(40,20,3,MEDIUM,WIB,WHITE,BLACK);
////        }
//        LED3_T;
//        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//    }
//}
//
//void TIM2_IRQHandler()
//{
//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//    {
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//        LED4_T;
//    }
//}
//
//void TIM8_UP_TIM13_IRQHandler()
//{
//    if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)
//    {
//        TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
//        LED5_T;    }
//
//}
//
volatile bool start_f = false;
void TIM3_IRQHandler()
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        if(start_f){
        if(tim_c<50)
        	tim_c++;
        else;
//        	tim_c = 0;

        TIM_SetCompare4(TIM4, tim_c);
        }
    }
}


void EXTI0_IRQHandler(void)
{

//	GPIO_PinSet(M_Port,M1);
//	GPIO_PinRes(M_Port,M2);
//	GPIO_PinRes(M_Port,M3);
//	GPIO_PinRes(M_Port,M4);
//	Step_r(1);
//	Mot_res();
//	res = 1;

	start_f = false;
//	if(tim_c>0)
//		tim_c--;
//	else
//		;

//	TIM_SetCompare4(TIM4, tim_c);
//		  USART_SendData(USART2, 147);
//	LED4_T;
//	gg = 0;
//	LEDs_off();
		  delay_ms(500);

		  EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
//	GPIO_PinRes(M_Port,M1);
//	GPIO_PinSet(M_Port,M2);
//	GPIO_PinRes(M_Port,M3);
//	GPIO_PinRes(M_Port,M4);

//	Step_l(1);

	tim_c = 0;

	TIM_SetCompare4(TIM4, tim_c);

//    if(bn==0)
//    {
//     WRST_L();
//     WE_H();
//
//
//     bn=1;
//     WE_H();
//     WRST_H();
//    }
//    else if(bn==1)
//    {
//       WE_L();
//       bn=2;
//    }
//
//if(out == 1)
//{
//	WE_H();
//	out = 2;
//}else if(out == 2)
//{
////	WE_L();
//}
delay_ms(500);
//	Led_Port -> ODR ^= Led1;
//	TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
//	TIM_SetCompare2(TIM4, 0);
//	TIM_SetCompare3(TIM4, 0);
//	TIM_SetCompare4(TIM4, 0);
//	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line1);

}
//volatile int kkkk = 0;
void EXTI2_IRQHandler(void)
{

//	GPIO_PinRes(M_Port,M1);
//	GPIO_PinRes(M_Port,M2);
//	GPIO_PinSet(M_Port,M3);
//	GPIO_PinRes(M_Port,M4);
//if(tim_c<50)
//	tim_c++;
//else
//	;
//
//TIM_SetCompare4(TIM4, tim_c);

	start_f = true;
	tim_c = 0;
delay_ms(500);
//	Step_r(1);

//	gg &= ~(1<<kkkk);
//	kkkk--;
//	Led_Port -> ODR ^= Led2;
//	gg = 0;
//	LEDs_off();
//
////	lcd_xy(1,10);
////	lcd_lnumber(read_reg(EUDAST));
//	delay_ms(1000);
//	Led_Port -> ODR ^= Led2;
//	TIM_SetCompare1(TIM4, 15);//(0us / 50us = 0.0)
//	TIM_SetCompare2(TIM4, 15);
//	TIM_SetCompare3(TIM4, 15);
//	TIM_SetCompare4(TIM4, 15);
////	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line2);

}

void EXTI3_IRQHandler(void)
{

//	GPIO_PinRes(M_Port,M1);
//	GPIO_PinRes(M_Port,M2);
//	GPIO_PinRes(M_Port,M3);
//	GPIO_PinSet(M_Port,M4);

//	Step_l(10);
	delay_ms(500);
	if(TM_GPIO_GetInputPinValue(SW_Port,SW4))
		slave_pos = 0;

//	Led_Port -> ODR ^= Led2;
//	GPIOB -> ODR ^= GPIO_Pin_8;
//	GPIOA -> ODR ^= GPIO_Pin_2;
//	delay_ms(1000);
//		Led_Port -> ODR ^= Led2;
//	kkkk++;
//	gg |= (1<<kkkk);

//	Led_Port -> ODR ^= Led3;
//	TIM_SetCompare1(TIM4, 30);//(0us / 50us = 0.0)
//	TIM_SetCompare2(TIM4, 30);
//	TIM_SetCompare3(TIM4, 30);
//	TIM_SetCompare4(TIM4, 30);
//	_delay_ms(500);
	EXTI_ClearITPendingBit(EXTI_Line3);

}

//void EXTI9_5_IRQHandler(void)
//{
//	Led_Port -> ODR ^= Led1;
//	Led_Port -> ODR ^= Led2;
//	Led_Port -> ODR ^= Led3;
//	TIM_SetCompare1(TIM4, 50);//(0us / 50us = 0.0)
//	TIM_SetCompare2(TIM4, 50);
//	TIM_SetCompare3(TIM4, 50);
//	TIM_SetCompare4(TIM4, 50);
////	_delay_ms(500);
//	EXTI_ClearITPendingBit(EXTI_Line5);
//
//}
//void TIM8_CC_IRQHandler(void)
//{
//	if (TIM_GetFlagStatus(TIM8, TIM_FLAG_Update) != RESET)
//    {
//    	TIM_ClearFlag(TIM8, TIM_IT_Update);
//    	LED4_T;
//    	iii++;
//    }
//}
// ----------------------------------------------------------------------------


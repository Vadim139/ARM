#ifndef _main_h_
#define _main_h_

//#include "my_defs.h"
#include "common.h"

//#define XTAL	16e6
//#define F_CPU   XTAL

//
//// klawiatura
//#define	ROW_1		SBIT( PORTC, 4 )
//#define	ROW_R_1		SBIT( PINC, 4 )
//#define	ROW_DDR_1	SBIT( DDRC, 4 )
//
//#define	ROW_2		SBIT( PORTC, 5 )
//#define	ROW_R_2		SBIT( PINC, 5 )
//#define	ROW_DDR_2	SBIT( DDRC, 5 )
//
//#define	ROW_3		SBIT( PORTC, 6 )
//#define	ROW_R_3		SBIT( PINC, 6 )
//#define	ROW_DDR_3	SBIT( DDRC, 6 )
//
//#define	ROW_4		SBIT( PORTC, 7 )
//#define	ROW_R_4		SBIT( PINC, 7 )
//#define	ROW_DDR_4	SBIT( DDRC, 7 )
//
//#define	COL_1		SBIT( PORTC, 4 )
//#define	COL_R_1		SBIT( PINC, 4 )
//#define	COL_DDR_1	SBIT( DDRC, 4 )
//
//#define	COL_2		SBIT( PORTC, 5 )
//#define	COL_R_2		SBIT( PINC, 5 )
//#define	COL_DDR_2	SBIT( DDRC, 5 )
//
//#define	COL_3		SBIT( PORTC, 6 )
//#define	COL_R_3		SBIT( PINC, 6 )
//#define	COL_DDR_3	SBIT( DDRC, 6 )
//
//#define	COL_4		SBIT( PORTC, 7 )
//#define	COL_R_4		SBIT( PINC, 7 )
//#define	COL_DDR_4	SBIT( DDRC, 7 )
//
//#define	KEYINT		SBIT( PORTD, 2 )
//#define	KEYINT_R	SBIT( PIND, 2 )
//#define	KEYINT_DDR 	SBIT( DDRD, 2 )
//
//// ledy
//#define	LED_1		SBIT( PORTD, 0 )
//#define	LED_DDR_1	SBIT( DDRD, 0 )
//
//#define	LED_2		SBIT( PORTD, 1 )
//#define	LED_DDR_2	SBIT( DDRD, 1 )
//
//#define	LED_3		SBIT( PORTD, 2 )
//#define	LED_DDR_3	SBIT( DDRD, 2 )
//
//#define	LED_4		SBIT( PORTD, 3 )
//#define	LED_DDR_4	SBIT( DDRD, 3 )
//
//#define	LED_5		SBIT( PORTD, 4 )
//#define	LED_DDR_5	SBIT( DDRD, 4 )
//
//#define	LED_6		SBIT( PORTD, 5 )
//#define	LED_DDR_6	SBIT( DDRD, 5 )
//
//#define	LED_7		SBIT( PORTD, 6 )
//#define	LED_DDR_7	SBIT( DDRD, 6 )
//
//#define	LED_8		SBIT( PORTD, 7 )
//#define	LED_DDR_8	SBIT( DDRD, 7 )
//
// lcd
#define	LCD_D4		GPIO_Pin_0
#define	LCD_D5		GPIO_Pin_1
#define	LCD_D6		GPIO_Pin_2
#define	LCD_D7		GPIO_Pin_3
#define	LCD_RS		GPIO_Pin_6
#define	LCD_E0		GPIO_Pin_7

#define	LCD_Port		GPIOD
//#define	LCD_DDR_E0	SBIT( DDRA, 1 )
//
//// uart
//#define	UART_RxD		SBIT( PORTD, 1 )
//#define	UART_RxD_R		SBIT( PIND, 1 )
//#define	UART_RxD_DDR	SBIT( DDRD, 1 )
//
//#define	UART_TxD		SBIT( PORTD, 0 )
//#define	UART_TxD_R		SBIT( PIND, 0 )
//#define	UART_TxD_DDR	SBIT( DDRD, 0 )
//
////// twi
////#define	TWI_SDA			SBIT( PORTC, 4 )
////#define	TWI_SDA_R		SBIT( PINC, 4 )
////#define	TWI_SDA_DDR		SBIT( DDRC, 4 )
////
////#define	TWI_SCK			SBIT( PORTC, 5 )
////#define	TWI_SCK_R		SBIT( PINC, 5 )
////#define	TWI_SCK_DDR		SBIT( DDRC, 5 )
//
//// adc
//#define	ADC6		SBIT( PORTA, 6 )
//#define	ADC6_R		SBIT( PINA, 6 )
//#define	ADC6_DDR	SBIT( DDRA, 6 )
//
#endif



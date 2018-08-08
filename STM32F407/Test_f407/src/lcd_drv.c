#include "sbit.h"
#include "lcd_drv.h"

uint8_t x, y = 0;
uint8_t lcd_pos = LCD_LINE1;


static void lcd_nibble( uint8_t d )
{
	GPIO_PinRes(LCD_Port, LCD_D7); if( d & 1<<7 ) GPIO_PinSet(LCD_Port, LCD_D7);
	GPIO_PinRes(LCD_Port, LCD_D6); if( d & 1<<6 ) GPIO_PinSet(LCD_Port, LCD_D6);
	GPIO_PinRes(LCD_Port, LCD_D5); if( d & 1<<5 ) GPIO_PinSet(LCD_Port, LCD_D5);
	GPIO_PinRes(LCD_Port, LCD_D4); if( d & 1<<4 ) GPIO_PinSet(LCD_Port, LCD_D4);
	GPIO_PinSet(LCD_Port, LCD_E0);
  _delay_us( LCD_TIME_ENA );
  GPIO_PinRes(LCD_Port, LCD_E0);
}


static void lcd_byte( uint8_t d )
{
  lcd_nibble( d );
  lcd_nibble( d<<4 );
  _delay_us( LCD_TIME_DAT );
}


void lcd_command( uint8_t d )
{
	GPIO_PinRes(LCD_Port, LCD_RS);
//  LCD_RS = 0;
  lcd_byte( d );
  if( d <= 3 )
    _delay_ms( 2 );                     // wait 2ms
}

void lcd_putchar( uint8_t d )
{
	GPIO_PinSet(LCD_Port, LCD_RS);
//	  LCD_RS = 1;
	  lcd_byte( d );
	  switch (++lcd_pos) {
	case LCD_LINE1 + LCD_COLUMN:
		d = LCD_LINE2;
		break;
	case LCD_LINE2 + LCD_COLUMN:
		d = LCD_LINE1;
		break;
	default:
		return;
	}
	//lcd_command(d);
}

void lcd_puts( void *s )                        // display string from SRAM
{
  for( uint8_t *s1 = s; *s1; s1++ )             // until zero byte
    lcd_putchar( *s1 );
}


void lcd_blank(/* uint8_t len */)                   // blank n digits
{
//  while( len-- )
//    lcd_putchar( ' ' );
	lcd_xy(0,0);
	lcd_puts("                ");
	lcd_xy(0,1);
	lcd_puts("                ");
	lcd_xy(0,0);
}


void lcd_init( void )
{

	  GPIO_InitTypeDef  GPIO_InitStructure;

	  /* Enable the GPIO_LED Clock */
	  switch ((uint32_t)LCD_Port) {
		case GPIOA_BASE :
			RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOA, ENABLE);
			break;
		case GPIOB_BASE :
			RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOB, ENABLE);
			break;
		case GPIOC_BASE :
			RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOC, ENABLE);
			break;
		case GPIOD_BASE :
			RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOD, ENABLE);
			break;
		case GPIOE_BASE :
			RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOE, ENABLE);
			break;
		case GPIOF_BASE :
			RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOF, ENABLE);
			break;
		default:
			break;
	}


	  /* Configure the GPIO pin */
	  GPIO_InitStructure.GPIO_Pin = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7 | LCD_RS | LCD_E0;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(LCD_Port, &GPIO_InitStructure);

	  GPIO_PinRes(LCD_Port, LCD_E0);
	  GPIO_PinRes(LCD_Port, LCD_RS);

//	  LCD_DDR_D4 = 1;                               // enable output pins
//  LCD_DDR_D5 = 1;
//  LCD_DDR_D6 = 1;
//  LCD_DDR_D7 = 1;
//  LCD_DDR_RS = 1;
//  LCD_DDR_E0 = 1;
//  LCD_E0 = 0;
//  LCD_RS = 0;                                   // send commands

  _delay_ms( 30 );
  lcd_nibble( 0x38 );
  _delay_ms( 4.1 );
  lcd_nibble( 0x38 );
  _delay_us( 100 );
  lcd_nibble( 0x38 );
  _delay_us( LCD_TIME_DAT );
  lcd_nibble( 0x20 );                           // 4 bit mode
  _delay_us( LCD_TIME_DAT );
  lcd_command( 0x28 );                          // 2 lines 5*8
  lcd_command( 0x08 );                          // display off
  lcd_command( 0x01 );                          // display clear
  lcd_command( 0x06 );                          // cursor increment
  lcd_command( 0x0E );                          // on, cursor, no blink

//  _delay_ms( 30 );
//  lcd_nibble( 0x30 );
//  _delay_ms( 4.1 );
//  lcd_nibble( 0x30 );
//  _delay_us( 100 );
//  lcd_nibble( 0x30 );
//  _delay_us( LCD_TIME_DAT );
//  lcd_nibble( 0x20 );                           // 4 bit mode
//  _delay_us( LCD_TIME_DAT );
//  lcd_command( 0x28 );                          // 2 lines 5*7
//  lcd_command( 0x08 );                          // display off
//  lcd_command( 0x01 );                          // display clear
//  lcd_command( 0x06 );                          // cursor increment
//  lcd_command( 0x0C );                          // on, no cursor, no blink
}


void lcd_number(uint8_t number)
{
	uint8_t cyf1, cyf2, cyf3 = 0;

	if (number >= 0 && number <= 9)
	lcd_cyfra(number);

	if (number >= 10 && number <= 99)
	{
		cyf1 = number % 10;
		cyf2 = number / 10;

		lcd_cyfra(cyf2);
		lcd_cyfra(cyf1);
	}
	if (number >= 100 && number <= 255)
		{
			cyf1 = number % 10;
			cyf2 = (number / 10) % 10;
			cyf3 = number /100;

			lcd_cyfra(cyf3);
			lcd_cyfra(cyf2);
			lcd_cyfra(cyf1);
		}
}

void lcd_lnumber(int number)
{
	uint8_t cyf1, cyf2, cyf3, cyf4, cyf5, cyf6, cyf7, cyf8, cyf9, cyf10 = 0;

	if (number >= 0 && number <= 9)
	lcd_cyfra(number);

	if (number >= 10 && number <= 99)
	{
		cyf1 = number % 10;
		cyf2 = number / 10;

		lcd_cyfra(cyf2);
		lcd_cyfra(cyf1);
	}
	if (number >= 100 && number <= 999)
		{
			cyf1 = number % 10;
			cyf2 = (number / 10) % 10;
			cyf3 = number /100;

			lcd_cyfra(cyf3);
			lcd_cyfra(cyf2);
			lcd_cyfra(cyf1);
		} else
	if (number >= 1000 && number <= 9999)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = number /1000;

				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			} else
	if (number >= 10000 && number <= 99999)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = (number /1000) % 10;
				cyf5 = number /10000;

				lcd_cyfra(cyf5);
				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			} else
	if (number >= 100000 && number <= 999999)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = (number /1000) % 10;
				cyf5 = (number /10000) % 10;
				cyf6 = number /100000;

				lcd_cyfra(cyf6);
				lcd_cyfra(cyf5);
				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			} else
	if (number >= 1000000 && number <= 9999999)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = (number /1000) % 10;
				cyf5 = (number /10000) % 10;
				cyf6 = (number /100000) % 10;
				cyf7 = number /1000000;

				lcd_cyfra(cyf7);
				lcd_cyfra(cyf6);
				lcd_cyfra(cyf5);
				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			} else
	if (number >= 10000000 && number <= 99999999)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = (number /1000) % 10;
				cyf5 = (number /10000) % 10;
				cyf6 = (number /100000) % 10;
				cyf7 = (number /1000000) % 10;
				cyf8 = number /10000000;

				lcd_cyfra(cyf8);
				lcd_cyfra(cyf7);
				lcd_cyfra(cyf6);
				lcd_cyfra(cyf5);
				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			} else
	if (number >= 100000000 && number <= 999999999)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = (number /1000) % 10;
				cyf5 = (number /10000) % 10;
				cyf6 = (number /100000) % 10;
				cyf7 = (number /1000000) % 10;
				cyf8 = (number /10000000) % 10;
				cyf9 = number /100000000;

				lcd_cyfra(cyf9);
				lcd_cyfra(cyf8);
				lcd_cyfra(cyf7);
				lcd_cyfra(cyf6);
				lcd_cyfra(cyf5);
				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			} else
	if (number >= 1000000000 && number <= 2147483647)
			{
				cyf1 = number % 10;
				cyf2 = (number / 10) % 10;
				cyf3 = (number /100) % 10;
				cyf4 = (number /1000) % 10;
				cyf5 = (number /10000) % 10;
				cyf6 = (number /100000) % 10;
				cyf7 = (number /1000000) % 10;
				cyf8 = (number /10000000) % 10;
				cyf9 = (number /100000000) % 10;
				cyf10 = number /1000000000;

				lcd_cyfra(cyf10);
				lcd_cyfra(cyf9);
				lcd_cyfra(cyf8);
				lcd_cyfra(cyf7);
				lcd_cyfra(cyf6);
				lcd_cyfra(cyf5);
				lcd_cyfra(cyf4);
				lcd_cyfra(cyf3);
				lcd_cyfra(cyf2);
				lcd_cyfra(cyf1);
			}
}
void lcd_cyfra(uint8_t cyf)
{
	switch (cyf) {
	case 0:
		lcd_putchar(48);
		break;
	case 1:
			lcd_putchar(49);
			break;
	case 2:
			lcd_putchar(50);
			break;
	case 3:
			lcd_putchar(51);
			break;
	case 4:
			lcd_putchar(52);
			break;
	case 5:
			lcd_putchar(53);
			break;
	case 6:
			lcd_putchar(54);
			break;
	case 7:
			lcd_putchar(55);
			break;
	case 8:
			lcd_putchar(56);
			break;
	case 9:
			lcd_putchar(57);
			break;
	default:
			break;

	}
}

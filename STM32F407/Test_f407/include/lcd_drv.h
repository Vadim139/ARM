#include "common.h"
#include "STM32F3_my.h"

#ifndef _lcd_drv_h_
#define _lcd_drv_h_


#define LCD_COLUMN      16
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)

#define	LCD_TIME_ENA    1.0             // 1µs
#define LCD_TIME_DAT    50.0            // 50µs
#define LCD_TIME_CLR    2000.0          // 2ms


void lcd_putchar( uint8_t d );
void lcd_init( void );
void lcd_puts( void *s );
void lcd_blank( /*uint8_t len*/ );          // blank n digits
void lcd_command( uint8_t d );
void lcd_number(uint8_t number);
void lcd_lnumber(int number);
void lcd_cyfra(uint8_t cyf);
#define lcd_xy(x, y)    lcd_command((x) + ((y) ? LCD_LINE2 : LCD_LINE1 ))


#endif

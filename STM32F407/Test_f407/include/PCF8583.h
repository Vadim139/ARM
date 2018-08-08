/**
    Biblioteka obs³ugi zegara czasu rzeczywistego z magistral¹ I2C typu PCF8583.
*/
#include "stm32f4xx_i2c.h"

#ifndef __PCF8583_H__
#define __PCF8583_H__

#define PCF8583_A0  1

#define I2C_RTC I2C1
#define PCF8583_address (PCF8583_A0 << 1) | 0xa0

/* u¿yte biblioteki */
//#include "i2c.h"//sprzêtowa obs³uga magistrali TWI (I2C)

#ifndef PCF8583_A0
#error " Nie zdefiniowa³eœ stanu lini A0 uk³adu. u¿yj #define PCF8583_A0  0(1)"
#endif
/**
 Bajt statusu uk³adu
*/

volatile uint8_t PCF8583_status;
volatile uint8_t PCF8583_alarm;
uint8_t bcd2bin(uint8_t bcd);
uint8_t bin2bcd(uint8_t bin);
uint8_t PCF8583_read(uint8_t reg);
void PCF8583_write(uint8_t reg,uint8_t data);
uint8_t PCF8583_read_bcd(uint8_t address);
void PCF8583_write_bcd(uint8_t address,uint8_t data);
uint8_t PCF8583_get_status(void);
void PCF8583_init(void);
void PCF8583_stop(void);
void PCF8583_start(void);
void PCF8583_hold_off(void);
void PCF8583_hold_on(void);
void PCF8583_alarm_off(void);
void PCF8583_alarm_on(void);
void PCF8583_write_word(uint8_t address,uint16_t data);
void PCF8583_write_date(uint8_t address,uint8_t day,uint16_t year);
void PCF8583_get_time(uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *hsec);
void PCF8583_get_time_bcd(uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *hsec);
void PCF8583_set_time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t hsec);
void PCF8583_get_date(uint8_t *day,uint8_t *month,uint16_t *year);
void PCF8583_set_date(uint8_t day,uint8_t month,uint16_t year);
void PCF8583_get_alarm_time(uint8_t *hour, uint8_t *min, uint8_t *sec, uint8_t *hsec);
void PCF8583_set_alarm_time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t hsec);
void PCF8583_get_alarm_date(uint8_t *day, uint8_t *month);
void PCF8583_set_alarm_date (uint8_t day, uint8_t month );

#endif // __PCF8583_H__

/*
 * PCF8583.c
 *
 *  Created on: 27 sty 2015
 *      Author: Dawid
 */

/**
    Biblioteka obs³ugi zegara czasu rzeczywistego z magistral¹ I2C typu PCF8583.
*/
#include "stm32f4xx_i2c.h"
#include "PCF8583.h"
#include "tm_stm32f4_i2c.h"

/* u¿yte biblioteki */
//#include "i2c.h"//sprzêtowa obs³uga magistrali TWI (I2C)

/**
 Bajt statusu uk³adu
*/
 volatile uint8_t PCF8583_status;

/**
 Bajt alarmu uk³adu
*/
 volatile uint8_t PCF8583_alarm;


/**-------------------------------------------------------------------------------------------------

  Name         :  uint8_t bcd2bin(uint8_t bcd)

  Description  :  Zamiana kodu BCD na binarny, bity BCD: 7654 - dziesiatki, 3210 -jednosci

  Argument(s)  :  bcd - wartoœæ w kodzie BCD

  Return value :  kod binarny z kodu BCD

--------------------------------------------------------------------------------------------------*/
uint8_t bcd2bin(uint8_t bcd)
{
    return (10*(bcd>>4) + (bcd&0x0f));
}
/**-------------------------------------------------------------------------------------------------

  Name         :  uint8_t bcd2bin(uint8_t bcd);

  Description  :  Zamiana kodu binarnego na BCD

  Argument(s)  :  bin - wartoœæ binarna z zakresu 0-99

  Return value :  kod BCD, bity: 7654 - dziesiatki, 3210 -jednosci

--------------------------------------------------------------------------------------------------*/
uint8_t bin2bcd(uint8_t bin)
{
    return ( ( ( bin / 10 ) << 4) | ( bin % 10 ) );
}

/**
 Czyta bajt z uk³adu
 \param address adres komórki w uk³adzie
 \return odczytany bajt
*/
uint8_t PCF8583_read(uint8_t reg)
{
    uint8_t b;
////    a = 0xA2;
//    a = (PCF8583_A0 << 1) | 0xa0;

    b = TM_I2C_Read(I2C_RTC,PCF8583_address,reg);

//    I2C_GenerateSTART(I2C,ENABLE);
////    I2C_SendData(I2C,a);
//    I2C_Send7bitAddress(I2C,a,I2C_Direction_Transmitter);
//    I2C_SendData(I2C,reg);
//    I2C_GenerateSTOP(I2C,ENABLE);
//    I2C_GenerateSTART(I2C,ENABLE);
//    I2C_Send7bitAddress(I2C,a,I2C_Direction_Receiver);
//	I2C_AcknowledgeConfig(I2C, DISABLE);
//	I2C_GenerateSTOP(I2C, ENABLE);
////    I2C_SendData(I2C,a | 1);
//    a = I2C_ReceiveData(I2C);


    //    I2C_GenerateSTOP(I2C,ENABLE);
//    i2cStart();
//    i2cWrite(a);
//    i2cWrite(address);
//    i2cStart();
//    i2cWrite(a | 1);
//    a = i2cRead(NOACK);
//    i2cStop();
    return b;
}


/**
 Zapisuje bajt do uk³adu
 \param address adres komórki w uk³adzie
 \param data bajt do wpisania
*/
void PCF8583_write(uint8_t reg,uint8_t data)
{
	TM_I2C_Write(I2C_RTC,PCF8583_address,reg,data);

//    I2C_GenerateSTART(I2C,ENABLE);
//    I2C_Send7bitAddress(I2C,a,I2C_Direction_Transmitter);
////    I2C_SendData(I2C,(PCF8583_A0 << 1) | 0xa0);
//    I2C_SendData(I2C,reg);
//    I2C_SendData(I2C,data);
//    I2C_GenerateSTOP(I2C,ENABLE);



//    i2cStart();
//    i2cWrite((PCF8583_A0 << 1) | 0xa0);
//    i2cWrite(address);
//    i2cWrite(data);
//    i2cStop();
}


/**
 Czyta bajt z uk³adu w formacie BCD
 \param address adres komórki w uk³adzie
 \return odczytany bajt
*/
uint8_t PCF8583_read_bcd(uint8_t address)
{
    return bcd2bin(PCF8583_read(address));
}

/**
 Zapisuje bajt do uk³adu w formacie BCD
 \param address adres komórki w uk³adzie
 \param data bajt do wpisania
*/
void PCF8583_write_bcd(uint8_t address,uint8_t data)
{
    PCF8583_write(address,bin2bcd(data));
}

/**
 Czyta status uk³adu
 \return status uk³adu
*/
uint8_t PCF8583_get_status(void)
{
    PCF8583_status = PCF8583_read(0);
    PCF8583_alarm = (PCF8583_status & 2);
    return PCF8583_status;
}


/**
 Inicjalizuje uk³adu
*/
void PCF8583_init(void)
{
    PCF8583_status=0;
    PCF8583_alarm=0;
    PCF8583_write(0, 0);
    PCF8583_write(4, PCF8583_read(4) & 0x3f);
    PCF8583_write(8, 0x90);
}

/**
 Zatrzymuje uk³adu
*/
void PCF8583_stop(void)
{
    PCF8583_get_status();
    PCF8583_status |= 0x80;
    PCF8583_write(0, PCF8583_status);
}

/**
 Startuje uk³adu
*/
void PCF8583_start(void)
{
    PCF8583_get_status();
    PCF8583_status &= 0x7f;
    PCF8583_write(0, PCF8583_status);
}

/**
 Odwiesza uk³adu
*/
void PCF8583_hold_off(void)
{
  PCF8583_get_status();
  PCF8583_status &= 0xbf;
  PCF8583_write(0, PCF8583_status);
}

/**
 Zawiesza uk³adu
*/
void PCF8583_hold_on(void)
{
  PCF8583_get_status();
  PCF8583_status |= 0x40;
  PCF8583_write(0, PCF8583_status);
}


/**
 Wy³¹cza alarm
*/
void PCF8583_alarm_off(void)
{
    PCF8583_get_status();
    PCF8583_status &= 0xfb;
    PCF8583_write(0, PCF8583_status);
}

/**
 Za³¹cza alarm
*/
void PCF8583_alarm_on(void)
{
  PCF8583_get_status();
  PCF8583_status |= 0x04;
  PCF8583_write(0, PCF8583_status);
}


/**
 Zapisuje s³owo do uk³adu
 \param address adres komórki w uk³adzie
 \param data s³owo do wpisania
*/
void PCF8583_write_word(uint8_t address,uint16_t data)
{
  PCF8583_write(address, (uint8_t)(data & 0xff));
  PCF8583_write(++address, (uint8_t)(data >> 8));
}


/**
 Ustawia datê w uk³adzie
 \param address adres komórki w uk³adzie
 \param day dzieñ
 \param year rok
*/
void PCF8583_write_date(uint8_t address,uint8_t day,uint16_t year)
{
    PCF8583_write(address, bin2bcd(day) | ( ( (uint8_t)year & 0x03) << 6 ) );
}

/**
 Czyta czas z uk³adu
 \param hour godzina
 \param min minuta
 \param sec sekunda
 \param hsec setne czêœci sekundy
*/
void PCF8583_get_time(uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *hsec)
{
    PCF8583_hold_on();
    *hsec=PCF8583_read_bcd(1);
    *sec=PCF8583_read_bcd(2);
    *min=PCF8583_read_bcd(3);
    *hour=PCF8583_read_bcd(4);
    PCF8583_hold_off();
}

/**
 Czyta czas z uk³adu
 \param hour godzina w formanie BCD
 \param min minuta w formanie BCD
 \param sec sekunda w formanie BCD
 \param hsec setne czêœci sekundy w formanie BCD
*/
void PCF8583_get_time_bcd(uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *hsec)
{
    PCF8583_hold_on();
    *hsec=PCF8583_read(1);
    *sec=PCF8583_read(2);
    *min=PCF8583_read(3);
    *hour=PCF8583_read(4) & 0b00111111;
    PCF8583_hold_off();
}
/**
 Ustawia czas w uk³adzie
 \param hour godzina
 \param min minuta
 \param sec sekunda
 \param hsec setne czêœci sekundy
*/
void PCF8583_set_time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t hsec)
{
    PCF8583_stop();
    PCF8583_write_bcd(1,hsec);
    PCF8583_write_bcd(2,sec);
    PCF8583_write_bcd(3,min);
    PCF8583_write_bcd(4,hour);
    PCF8583_start();
}
/**
 Czyta datê z uk³adu
 \param day dzieñ
 \param month miesi¹c
 \param year rok
*/
void PCF8583_get_date(uint8_t *day,uint8_t *month,uint16_t *year)
{
    uint8_t dy;
    uint16_t y1;
    PCF8583_hold_on();
    dy = PCF8583_read(5);
    *month = bcd2bin(PCF8583_read(6) & 0x1f);
    PCF8583_hold_off();
    *day = bcd2bin(dy & 0x3f);
    dy >>= 6;
    y1 = PCF8583_read(16) | ( (uint16_t)PCF8583_read(17) << 8);
    if ( ( (uint8_t) y1 & 3 ) != dy )
            PCF8583_write_word(16, ++y1);
    *year = y1;
}

/**
 Ustawia datê w uk³adzie
 \param day dzieñ
 \param month miesi¹c
 \param year rok
*/
void PCF8583_set_date(uint8_t day,uint8_t month,uint16_t year)
{
    PCF8583_write_word(16, year);
    PCF8583_stop();
    PCF8583_write_date(5, day, year);
    PCF8583_write_bcd(6, month);
    PCF8583_start();
}

/**
 Czyta czas alarmu z uk³adu
 \param hour godzina
 \param min minuta
 \param sec sekunda
 \param hsec setne czêœci sekundy
*/
void PCF8583_get_alarm_time(uint8_t *hour, uint8_t *min, uint8_t *sec, uint8_t *hsec)
{
  *hsec=PCF8583_read_bcd(0x9);
  *sec=PCF8583_read_bcd(0xa);
  *min=PCF8583_read_bcd(0xb);
  *hour=PCF8583_read_bcd(0xc);
}

/**
 Ustawia czas alarmu w uk³adzie
 \param hour godzina
 \param min minuta
 \param sec sekunda
 \param hsec setne czêœci sekundy
*/
void PCF8583_set_alarm_time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t hsec)
{
  PCF8583_write_bcd(0x9, hsec);
  PCF8583_write_bcd(0xa, sec);
  PCF8583_write_bcd(0xb, min);
  PCF8583_write_bcd(0xc, hour);
}

/**
 Czyta dat&#234; alarmu z uk³adu
 \param day dzieñ
 \param month miesi¹c
*/
void PCF8583_get_alarm_date(uint8_t *day, uint8_t *month)
{
  *day = bcd2bin( PCF8583_read(0xd) & 0x3f );
  *month = bcd2bin( PCF8583_read(0xe) & 0x1f );
}

/**
 Ustawia datê alarmu w uk³adzie
 \param day dzieñ
 \param month miesi¹c
*/
void PCF8583_set_alarm_date (uint8_t day, uint8_t month )
{
  PCF8583_write_date( 0xd, day, 0 );
  PCF8583_write_bcd( 0xe, month );
}

/*@}*/






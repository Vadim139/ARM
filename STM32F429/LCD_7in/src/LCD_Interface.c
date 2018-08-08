#include "LCD_Interface.h"

#include "stm32f4xx.h"
#include "delay.h"

void LCD_CmdWrite(uint8_t cmd)
{	
  #ifdef  USE_FSMC
   Chk_Busy();
   LCD_COMM_ADD = cmd;
  #endif
  #ifdef  USE_SPI   
   Clr_Cs();
   SPI_Write(0x80); 
   SPI_Write(cmd);
   Set_Cs();
  #endif 
}

/*************************LCD数据写入*********************************/
void LCD_DataWrite(uint8_t data)
{
  #ifdef  USE_FSMC
   LCD_DATA_ADD = data;
  #endif 
  #ifdef  USE_SPI 
   Clr_Cs();
   SPI_Write(0x00); 
   SPI_Write(data);
   Set_Cs();
  #endif 
}

/*********************SPI 数据读取*********************************/
uint8_t LCD_DataRead(void)
{
 #ifdef  USE_FSMC
   return (LCD_DATA_ADD);
 #endif
 #ifdef  USE_SPI
   uint8_t Data;
   Clr_Cs();
   SPI_Write(0x40);
   Data = SPI_Read(); 
   Set_Cs();
   return Data;
 #endif  
}  

uint8_t LCD_StatusRead(void)
{
  #ifdef  USE_FSMC
    return (LCD_COMM_ADD);
  #endif      
  #ifdef USE_SPI
    uint8_t Data;
    Clr_Cs();
    SPI_Write(0xc0);
    Data = SPI_Read(); 
    Set_Cs();
    return Data;
  #endif  
}

uint8_t LCD_CmdRead(uint8_t Addr)
{
  #ifdef  USE_FSMC
   return (LCD_COMM_ADD);
  #endif
  #ifdef USE_SPI
   uint8_t temp;
   LCD_CmdWrite(Addr);
   temp=LCD_DataRead();
   return temp;
  #endif 
}

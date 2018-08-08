#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#include "stm32f4xx.h"
#include "RA8875_Driver.h"
#include "LCD_Config.h"
#ifdef __cplusplus
extern "C"{
#endif


#define  USE_FSMC
//#define  USE_SPI




//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID（ATK-7' TFTLCD不支持id读）
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16 sysreg;			//PREF寄存器，设置当前操作页，显示页和背光等（ATK-7' TFTLCD暂不支持横竖屏设置，统一为横屏）。	
	u8	wramcmd;		//开始写gram指令
	u8  setxcmd;		//设置x坐标指令
	u8  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	  



//-----------------------------------------------------------------------------------------------
#define LCD_COMM_ADD		 (*((volatile unsigned short *) 0x60020000)) /* RS = 0 */	 	 	          //命令或状态地址
#define LCD_DATA_ADD		 (*((volatile unsigned short *) 0x60000000)) /* RS = 1 */

void LCD_CmdWrite(uint8_t cmd);
void LCD_DataWrite(uint8_t data);
void LCD_DataWrite(uint8_t data);
uint8_t LCD_DataRead(void);
uint8_t LCD_StatusRead(void);
uint8_t LCD_CmdRead(uint8_t Addr);



#ifdef __cplusplus
}
#endif

#endif /*_LCD_INTERFACE_H*/




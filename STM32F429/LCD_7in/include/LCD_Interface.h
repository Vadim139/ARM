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




//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID��ATK-7' TFTLCD��֧��id����
	u8  dir;			//���������������ƣ�0��������1��������	
	u16 sysreg;			//PREF�Ĵ��������õ�ǰ����ҳ����ʾҳ�ͱ���ȣ�ATK-7' TFTLCD�ݲ�֧�ֺ��������ã�ͳһΪ��������	
	u8	wramcmd;		//��ʼдgramָ��
	u8  setxcmd;		//����x����ָ��
	u8  setycmd;		//����y����ָ��	 
}_lcd_dev; 	  



//-----------------------------------------------------------------------------------------------
#define LCD_COMM_ADD		 (*((volatile unsigned short *) 0x60020000)) /* RS = 0 */	 	 	          //�����״̬��ַ
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




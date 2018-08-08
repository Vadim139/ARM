#ifndef __CT_I2C_H_
#define __CT_I2C_H_

#include "stm32f4xx.h"
#include "GPIO_Config.h"
#ifdef __cplusplus
extern "C"{
#endif

//IIC���в�������
void CT_I2C_Init(void);		 
void CT_I2C_Start(void);				//����IIC��ʼ�ź�
void CT_I2C_Stop(void);	  				//����IICֹͣ�ź�
void CT_I2C_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CT_I2C_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CT_I2C_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CT_I2C_Ack(void);					//IIC����ACK�ź�
void CT_I2C_NAck(void);					//IIC������ACK�ź�	  


#ifdef __cplusplus
}
#endif
#endif /*__CAP_I2C_H_*/



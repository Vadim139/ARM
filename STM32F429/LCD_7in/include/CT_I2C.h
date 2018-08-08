#ifndef __CT_I2C_H_
#define __CT_I2C_H_

#include "stm32f4xx.h"
#include "GPIO_Config.h"
#ifdef __cplusplus
extern "C"{
#endif

//IIC所有操作函数
void CT_I2C_Init(void);		 
void CT_I2C_Start(void);				//发送IIC开始信号
void CT_I2C_Stop(void);	  				//发送IIC停止信号
void CT_I2C_Send_Byte(u8 txd);			//IIC发送一个字节
u8 CT_I2C_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 CT_I2C_Wait_Ack(void); 				//IIC等待ACK信号
void CT_I2C_Ack(void);					//IIC发送ACK信号
void CT_I2C_NAck(void);					//IIC不发送ACK信号	  


#ifdef __cplusplus
}
#endif
#endif /*__CAP_I2C_H_*/



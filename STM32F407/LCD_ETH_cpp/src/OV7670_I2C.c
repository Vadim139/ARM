/*
 * OV7670_I2C.c
 *
 *  Created on: 27 sty 2015
 *      Author: Dawid
 */

#include "OV7670_I2C.h"
#include "tm_stm32f4_i2c.h"
#include "sccb.h"

//uint8_t OV7670_read1(uint8_t reg)
//{
//    uint8_t b;
//
//    b = TM_I2C_Read(I2C2,OV7670_address,reg);
//
//    return b;
//}
//
//void OV7670_write(uint8_t reg,uint8_t data)
//{
//	TM_I2C_Write(I2C_Camera,OV7670_address,reg,data);
//}
//

#include "stm32f4xx.h"
#define ONE_BYTE_REG_ADDR 0x01
#define TWO_BYTE_REG_ADDR 0x02

//void MCO1_Init(void)
//{
// GPIO_InitTypeDef GPIO_InitStructure;
//
// RCC_ClockSecuritySystemCmd(ENABLE);
//
// /* Enable GPIOs clocks */
// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//
// GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
//
// /* Configure MCO (PA8) */
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
// GPIO_Init(GPIOA, &GPIO_InitStructure);
//
// RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_4);
//}

int SCCB_send_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len)
{
  int timeout = 0x7FFFFF;
  int ret = 0;
         /* send i2c*/
  I2C_GenerateSTART(I2C2, ENABLE);
  while( !I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
  {
   if ((timeout--) == 0)
   {
    ret = 1;
    goto exit;
   }
  }
  I2C_Send7bitAddress(I2C2, slave_addr, I2C_Direction_Transmitter);
  while(!(I2C2->SR1 & (1 << 1))); // check ADDR bit
  {
   if ((timeout--) == 0)
   {
    ret = 2;
    goto exit;
   }
  }
  while(!(I2C2->SR2 & (1 << 2)));   // check TRA bit
  {
   if ((timeout--) == 0)
   {
    ret = 3;
    goto exit;
   }
  }

  /* 2 byte reg address */
  if(addr_len == TWO_BYTE_REG_ADDR)
  {
   // MSB
   I2C_SendData(I2C2, (0xFF & (reg_addr >> 8)) );
   while(!(I2C2->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 4;
    goto exit;
   }
   }

   // LSB
   I2C_SendData(I2C2, (0xFF & reg_addr));
   while(!(I2C2->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 5;
    goto exit;
   }
   }

  }
  /* 1 byte reg address */
  else
  {
   I2C_SendData(I2C2, (0xFF & reg_addr));
   while(!(I2C2->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 6;
    goto exit;
   }
   }
  }

  I2C_SendData(I2C2, *data);
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  {
//   if ((timeout--) == 0)
   {
    ret = 7;
    goto exit;
   }
  }

                exit:
  I2C_GenerateSTOP(I2C2, ENABLE);
  return ret;
}

int SCCB_receive_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len)
{
  int timeout = 0x7FFFFF;
  int ret = 0;
   /* send i2c*/
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2C2, ENABLE);
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
  {
   if ((timeout--) == 0)
   {
    ret = 1;
    goto exit;
   }
  }

  I2C_Send7bitAddress(I2C2, slave_addr, I2C_Direction_Transmitter);
  while(!(I2C2->SR1 & (1 << 1))); // check ADDR bit
  {
   if ((timeout--) == 0)
   {
    ret = 2;
    goto exit;
   }
  }

  while(!(I2C2->SR2 & (1 << 2)));   // check TRA bit
  {
   if ((timeout--) == 0)
   {
    ret = 3;
    goto exit;
   }
  }

  /* 2 byte reg address */
  if(addr_len == TWO_BYTE_REG_ADDR)
  {
   // MSB
   I2C_SendData(I2C2, (0xFF & (reg_addr >> 8)) );
   while(!(I2C2->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 4;
    goto exit;
   }
  }

   // LSB
   I2C_SendData(I2C2, (0xFF & reg_addr));
   while(!(I2C2->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 5;
    goto exit;
   }
  }
  }

  /* 1 byte reg address */
  else
  {
   I2C_SendData(I2C2, (0xFF & reg_addr));
   while(!(I2C2->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 6;
    goto exit;
   }
  }
  }

  I2C_GenerateSTOP(I2C2, ENABLE);
  I2C_GenerateSTART(I2C2, ENABLE);
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
  {
   if ((timeout--) == 0)
   {
    ret = 7;
    goto exit;
   }
  }
  I2C_Send7bitAddress(I2C2, slave_addr, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // check ADDR bit
  {
   if ((timeout--) == 0)
   {
    ret = 8;
    goto exit;
   }
  }


  I2C_AcknowledgeConfig(I2C2, DISABLE);
                /* Send STOP Condition */
                I2C_GenerateSTOP(I2C2, ENABLE);

  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
  {
   if ((timeout--) == 0)
   {
    ret = 10;
    goto exit;
   }
  }

  *data = I2C_ReceiveData(I2C2);
  I2C_AcknowledgeConfig(I2C2, ENABLE);
  return ret;

exit:
  I2C_GenerateSTOP(I2C2, ENABLE);
  return ret;
}

unsigned char wrOV7670Reg(unsigned char regID, unsigned char regDat)
{
		startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
  	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
  	if(0==SCCBwriteByte(regDat))
	{
		stopSCCB();
		return(0);
	}
  	stopSCCB();

  	return(1);
}

unsigned char rdOV7670Reg(unsigned char regID, unsigned char *regDat)
{

	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
  	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	stopSCCB();

	_delay_us(100);


	startSCCB();
	if(0==SCCBwriteByte(0x43))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
  	*regDat=SCCBreadByte();
  	noAck();
  	stopSCCB();
  	return(1);
}


int OV7670_read(u8 reg, u8* data)
{
 return SCCB_receive_data(0x42, (u16) reg, data, ONE_BYTE_REG_ADDR);
//	return rdOV7670Reg(reg, data);
}
/*******************************************************************************/
int OV7670_write(u8 reg, u8* data)
{
 return SCCB_send_data(0x43, (u16) reg, data, ONE_BYTE_REG_ADDR);
//	wrOV7670Reg(reg, *data);
//	return 0;
}

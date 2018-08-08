#ifndef __GPIO_CONFIG_H_
#define __GPIO_CONFIG_H_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"


///////////////////////////////////////////////////////////////
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入



#define	USART1_OPEN
//#define	USART2_OPEN
//#define	USART3_OPEN
/**
 * @brief Definition for COM port1, connected to USART3
 */ 
#ifdef	USART1_OPEN  
	#define Open_USART                        USART1
	#define Open_USART_CLK                    RCC_APB2Periph_USART1
	
	#define Open_USART_TX_PIN                 GPIO_Pin_9
	#define Open_USART_TX_GPIO_PORT           GPIOA
	#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open_USART_TX_SOURCE              GPIO_PinSource9
	#define Open_USART_TX_AF                  GPIO_AF_USART1
	
	
	#define Open_USART_RX_PIN                 GPIO_Pin_10
	#define Open_USART_RX_GPIO_PORT           GPIOA
	#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open_USART_RX_SOURCE              GPIO_PinSource10
	#define Open_USART_RX_AF                  GPIO_AF_USART1
	
	#define Open_USART_IRQn                   USART1_IRQn
	#define USARTx_IRQHANDLER  				  USART1_IRQHandler

#elif	defined	USART2_OPEN
	#define Open_USART                        USART2
	#define Open_USART_CLK                    RCC_APB1Periph_USART2
	
	#define Open_USART_TX_PIN                 GPIO_Pin_2
	#define Open_USART_TX_GPIO_PORT           GPIOA
	#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open_USART_TX_SOURCE              GPIO_PinSource2
	#define Open_USART_TX_AF                  GPIO_AF_USART2
	
	
	#define Open_USART_RX_PIN                 GPIO_Pin_3
	#define Open_USART_RX_GPIO_PORT           GPIOA
	#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open_USART_RX_SOURCE              GPIO_PinSource3
	#define Open_USART_RX_AF                  GPIO_AF_USART2
	
	#define Open_USART_IRQn                   USART2_IRQn
	#define USARTx_IRQHANDLER  				  USART2_IRQHandler

#elif	defined	USART3_OPEN
	#define Open_USART                        USART3
	#define Open_USART_CLK                    RCC_APB1Periph_USART3
	
	#define Open_USART_TX_PIN                 GPIO_Pin_10
	#define Open_USART_TX_GPIO_PORT           GPIOC
	#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOC
	#define Open_USART_TX_SOURCE              GPIO_PinSource10
	#define Open_USART_TX_AF                  GPIO_AF_USART3
	
	
	#define Open_USART_RX_PIN                 GPIO_Pin_11
	#define Open_USART_RX_GPIO_PORT           GPIOC
	#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOC
	#define Open_USART_RX_SOURCE              GPIO_PinSource11
	#define Open_USART_RX_AF                  GPIO_AF_USART3
	
	#define Open_USART_IRQn                   USART3_IRQn
	#define USARTx_IRQHANDLER  				  USART3_IRQHandler
#else
	#error "Please select The COM to be used (in usart.h)"
#endif 	


//IO操作函数	   
#define SET_SDA()     GPIO_SetBits(CT_SDA_GPIO_PORT,CT_SDA_GPIO_PIN)    
#define CLR_SDA()     GPIO_ResetBits(CT_SDA_GPIO_PORT,CT_SDA_GPIO_PIN)  

#define SET_CLK()     GPIO_SetBits(CT_SCL_GPIO_PORT,CT_SCL_GPIO_PIN)    
#define CLR_CLK()     GPIO_ResetBits(CT_SCL_GPIO_PORT,CT_SCL_GPIO_PIN)

#define CT_READ_SDA   GPIO_ReadInputDataBit(CT_SDA_GPIO_PORT,CT_SDA_GPIO_PIN)
#define CT_IIC_SDA     

#define CT_SDA_CLK    	   RCC_AHB1Periph_GPIOB
#define CT_SDA_GPIO_PORT   GPIOB
#define CT_SDA_GPIO_PIN    GPIO_Pin_9

#define CT_SCL_CLK    	   RCC_AHB1Periph_GPIOB
#define CT_SCL_GPIO_PORT   GPIOB
#define CT_SCL_GPIO_PIN    GPIO_Pin_8


#define CT_INT_CLK    	    RCC_AHB1Periph_GPIOB
#define CT_INT_GPIO_PORT   	GPIOB
#define CT_INT_GPIO_PIN   	GPIO_Pin_12
#define CT_INT_EXTI_LINE    EXTI_Line12

//IO操作函数	 
//#define CT_RST    		PCout(13)	//GT811复位引脚




#endif /*__GPIO_CONFIG_H_*/

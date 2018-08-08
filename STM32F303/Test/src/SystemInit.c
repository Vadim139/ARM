//-----------------------------------------------------------------------------
//
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    BTC KORPORACJA SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//
//                     http://www kamami.com
//-----------------------------------------------------------------------------


#include "common.h"
#include "STM32F3_my.h"

#include "board.h"

//void SPI_Configuration(void);
//void RCC_Configuration(void);
//void GPIO_Configuration(void);
//void NVIC_Configuration(void);

//void SPI_Configuration(void)
//{
//  	SPI_InitTypeDef  SPI_InitStructure;
//  	GPIO_InitTypeDef GPIO_InitStructure;
//
//  	// Enable SPI1 and GPIO clocks
//  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
//  	RCC_AHBPeriphClockCmd((uint32_t)RCC_AHBPeriph_GPIOB, ENABLE);
//
//  	// Configure SPI2 pins: SCK, MISO and MOSI
//  	GPIO_InitStructure.GPIO_Pin = DATA | CLK;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);
//	GPIO_PinAFConfig(PORT_ctrl, DATA, GPIO_AF_6);
//	GPIO_PinAFConfig(PORT_ctrl, CLK, GPIO_AF_6);
//
//
//  	// Configure I/O for Flash Chip select
//  	GPIO_InitStructure.GPIO_Pin = CS | RES;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);
//
//  	// SPI1 configuration
//  	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
//  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_9b;
//  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
//  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//  	SPI_InitStructure.SPI_CRCPolynomial = 7;
//  	SPI_Init(SPI2, &SPI_InitStructure);
//
//  	// Enable SPI1
//  	SPI_Cmd(SPI2, ENABLE);
//}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void RCC_Configuration(void)
//{
//	ErrorStatus HSEStartUpStatus;
//
//  	/* RCC system reset(for debug purpose) */
//  	RCC_DeInit();
//
//  	/* Enable HSE */
//  	RCC_HSEConfig(RCC_HSE_ON);
//
//  	/* Wait till HSE is ready */
//  	HSEStartUpStatus = RCC_WaitForHSEStartUp();
//
//  	if(HSEStartUpStatus == SUCCESS)
//  	{
//    	/* Enable Prefetch Buffer */
//    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//
//    	/* Flash 2 wait state */
//    	FLASH_SetLatency(FLASH_Latency_2);
//
//    	/* HCLK = SYSCLK */
//    	RCC_HCLKConfig(RCC_SYSCLK_Div1);
//
//    	/* PCLK2 = HCLK / 2 */
//    	RCC_PCLK2Config(RCC_HCLK_Div2);
//
//    	/* PCLK1 = HCLK/2 */
//    	RCC_PCLK1Config(RCC_HCLK_Div2);
//
//    	/* PLLCLK = 25MHz * 9 = 72 MHz */
//    	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
//
//    	/* Enable PLL */
//    	RCC_PLLCmd(ENABLE);
//
//    	/* Wait till PLL is ready */
//    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
//	    {
//    	}
//
//	    /* Select PLL as system clock source */
//    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//
//	    /* Wait till PLL is used as system clock source */
//    	while(RCC_GetSYSCLKSource() != 0x08)
//    	{
//		}
// 	}
//}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void NVIC_Configuration(void)
//{
//
//  	//Set the Vector Table base location at 0x08000000
//  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
//}

//void GPIO_Configuration(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	// LCD lines configuration
//  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ctrl, ENABLE);
//  	GPIO_InitStructure.GPIO_Pin = DATA | CLK | CS | RES ;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(PORT_ctrl, &GPIO_InitStructure);
//
////	// Joystick lines configuration
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_JOY, ENABLE);
////  	GPIO_InitStructure.GPIO_Pin = JOY_UP | JOY_DOWN;
////  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////  	GPIO_Init(JOY_PORT, &GPIO_InitStructure);
//}

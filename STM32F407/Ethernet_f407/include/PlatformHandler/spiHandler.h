#ifndef __SSP_H__
#define __SSP_H__

#define GPIO_SPI0_PORT		GPIOA
#define GPIO_CS_PORT		GPIOA
#define GPIO_W5500_RST_PORT	GPIOA

#define GPIO_SPI0_CS0		4
#define GPIO_SPI0_CLK		5
#define GPIO_SPI0_MISO		6
#define GPIO_SPI0_MOSI		7
#define GPIO_W5500_RST		3

//#define GPIO_CS1_PORT		1
//#define GPIO_SPI0_CS1		19

void SPI_Init_Eth();

#endif

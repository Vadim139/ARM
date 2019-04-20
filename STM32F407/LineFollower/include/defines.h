/**
 *  Defines for your entire project at one place
 * 
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/* Put your global defines for all libraries here used in your project */

//Ethernet - Wiz550io
//PA5 - SCK
//PA6 - MISO
//PA7 - MOSI
//
//PC0 - CS
//PC1 - RST
//PC2 - RDY
#define ETH_SPI			SPI3
//#define ETH_SCK       	GPIO_Pin_10
//#define ETH_MISO 		GPIO_Pin_11
//#define ETH_MOSI 		GPIO_Pin_12
#define ETH_PINSPACK 	TM_SPI_PinsPack_2

#define ETH_CS 			GPIO_Pin_4
#define ETH_RST 		GPIO_Pin_1
#define ETH_RDY 		GPIO_Pin_2
#define ETH_PORT 		GPIOC



#endif




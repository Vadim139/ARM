//#include "board.h"
#include "PlatformHandler\spiHandler.h"
#include "tm_stm32f4_spi.h"
#include "STM32F3_my.h"

/* Set pin mux for SSP operation */
static void Init_SSP_PinMux(void)
{
	/* Configure SPI Pin */

//	TM_SPI_InitFull(SPI3,TM_SPI_PinsPack_1,SPI_BaudRatePrescaler_256,TM_SPI_Mode_3,)
//	Chip_IOCON_PinMuxSet(LPC_IOCON, GPIO_SPI0_PORT, GPIO_SPI0_CLK, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));	// SCK
//	Chip_IOCON_PinMuxSet(LPC_IOCON, GPIO_SPI0_PORT, GPIO_SPI0_MISO, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));	// MISO
//	Chip_IOCON_PinMuxSet(LPC_IOCON, GPIO_SPI0_PORT, GPIO_SPI0_MOSI, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));	// MOSI
//	Chip_IOCON_PinMuxSet(LPC_IOCON, GPIO_SPI0_PORT, GPIO_SPI0_CS0, (IOCON_FUNC0 | IOCON_MODE_PULLUP));
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO, GPIO_SPI0_PORT, GPIO_SPI0_CS0);	// SSEL(CS) as GPIO output
//	//Chip_GPIO_SetPinState(LPC_GPIO, GPIO_SPI0_PORT, GPIO_SPI0_CS0, true);

	/* Configure W5500 RESET Pin */
	GPIO_PinOut(GPIO_W5500_RST_PORT,GPIO_W5500_RST);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO, GPIO_W5500_RST_PORT, GPIO_W5500_RST);	// N_RESET as GPIO output
	//Chip_GPIO_SetPinState(LPC_GPIO, GPIO_W5500_RST_PORT, GPIO_W5500_RST, true);	// N_RESET
}

void SPI_Init_Eth()
{
	/* SSP initialization */

	Init_SSP_PinMux();
	TM_SPI_Init(SPI3,TM_SPI_PinsPack_1);
//	TM_SPIx_Init(SPI3, TM_SPI_PinsPack_1, TM_SPI3_MODE, TM_SPI3_PRESCALER, TM_SPI3_MASTERSLAVE, TM_SPI3_FIRSTBIT);
//	Chip_SSP_Init(LPC_SSP0);
//
//	Chip_SSP_SetFormat(LPC_SSP0, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_MODE3);
//	Chip_SSP_SetMaster(LPC_SSP0, true);
//	Chip_SSP_SetBitRate(LPC_SSP0, 20000000);			// 20MHz
//	Chip_SSP_Enable(LPC_SSP0);
}

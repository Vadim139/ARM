/**
 *
 */
/* Includes *******************************************************************/
#include "main.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "STM32F3_my.h"
#include "tm_stm32f4_adc.h"
#include "Ethernet/wizchip_conf.h"
#include "Ethernet/socket.h"
#include "STM32F4_my.h"
#include "OV7670_I2C.h"
#include "img/img03.h"
#include "sccb.h"
#include "tm_stm32f4_mco_output.h"



// Image buffer
//volatile uint8_t frame_buffer[IMG_ROWS*IMG_COLUMNS*2];

uint32_t srcbuf[10] = {1,2,3,4,5,6,7,8,9,10};
//uint16_t bufor[25100];//50689 50112
#define buf_size 76802//50200;
uint8_t bufor[buf_size];//50689 50112//50200 153600 614400
#define send_size 770//15362

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO TestStatus  TransferStatus = FAILED;

//#define DCMI_DR_ADDRESS   0x50050028
#define DCMI_DR_ADDRESS   0x28
#define FSMC_LCD_ADDRESS  LCD_BASE

#define TRUE true
#define FALSE false

uint8_t frame = 0;
volatile uint8_t frame_flag = 0;

GPIO_IO Cam_Rst(Cam_Port1,Cam_RST,0);
GPIO_IO Cam_Pwr(Cam_Port1,Cam_PWR,0);

uint8_t	  dcmi_flag_frameri_bak, dcmi_flag_lineri_bak, dcmi_flag_errri_bak,
dcmi_flag_ovfri_bak, dcmi_flag_vsyncri_bak;

int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t size);
//int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t size);


#define DATA_BUF_SIZE   2048
uint8_t gDATABUF[DATA_BUF_SIZE];
wiz_NetInfo gWIZNETINFO;

uint8_t listen2(){
	uint8_t tmp;
	uint8_t str[5] = {'1','2','3',' ','6'};
	uint8_t tmpstr[6] = {0,};
	int32_t ret = 0;

	while(1){
	uint8_t sn = 2;
	     if((ret = socket(sn,Sn_MR_TCP,3000,SF_TCP_NODELAY)) != sn)
	     {
	        printf("%d:socket() error:%ld\r\n", sn,ret);
	        close(sn);
	        continue;
	     }
	     printf("%d:socket() ok.\r\n",sn);


	     if((ret = listen(sn)) != SOCK_OK)
	     {
	        printf("%d:listen() error:%ld",sn,ret);
	        close(sn);
	        return ret;
	     }
	     printf("%d:listen() ok.\r\n",sn);


	     if(((ret = socket(sn+1, Sn_MR_UDP, 3000, 0)) != sn+1))
	     {
	        printf("%d:socket() error:%ld\r\n", sn+1,ret);
	        continue;
	     }
	     do
	     {
	        getsockopt(sn,SO_STATUS, &tmp);
	     }while(tmp != SOCK_CLOSED && tmp != SOCK_ESTABLISHED);
	     if(tmp == SOCK_CLOSED) continue;
	     //Accept for client
	     printf("%d:connected\r\nLBStarted Blocking mode\r\n",sn);

//	     for(int i = 0;i<10;i++){
//	    	 uint16tostr((char*)str, bufor[i], 10);
//	     	 send(sn,bufor,buf_size);//sizeof(bufor)
//	     	 _delay_s(5);
//	     }

//	     send(sn,str,5);
	     while(1)
	     {
	        if((ret = loopback_tcps(sn, gDATABUF, DATA_BUF_SIZE)) < 0)
	        {
	           printf("%d:loopback_tcps error:%ld\r\n",sn,ret);
	           break;
	        }
	/*
	        if((ret=loopback_udps(sn+1,gDATABUF,10)) < 0)
	        {
	           printf("%d:loopback_udps error:%ld\r\n",sn+1,ret);
	           break;
	        }
	*/}
	     }
}

void LCD_puts(int x, int y, u8 data)
{
	char buf[10];
	data = 200;
		  Draw_Full_Rect(43, 295 ,61 ,25 , LCD_BLACK);
		  uint16tostr(buf, data, 10);
		  Display_String(43, 295, buf, LCD_WHITE);
//	Draw_Full_Rect(x, y+252 ,x+18 ,y , LCD_BLACK);
//	uint16tostr(buf, data, 10);
//	Display_String(x, y+252, "Buf", LCD_WHITE);
}

uint8_t ov7670_init(void)
{
	uint8_t data;
	OV7670_read(REG_PID, &data);

//    if (data != 0x76) {
//        return 0;
//    }
//    data = 0x80;
//    OV7670_write(REG_COM7, &data); /* reset to default values */
//    _delay_ms(50);
//    data = 0x80;
//    OV7670_write(REG_CLKRC, &data);
//    _delay_ms(50);
//    data = 0x0A;
//    OV7670_write(REG_COM11, &data);
//    _delay_ms(50);
//    data = 0x04;
//    OV7670_write(REG_TSLB, &data);
//    _delay_ms(50);
//    data = 0x04;
//    OV7670_write(REG_TSLB, &data);
//    _delay_ms(50);
//    data = 0x04;
//    OV7670_write(REG_COM7, &data); /* output format: rgb */
//    _delay_ms(50);
//    data = 0x00;
//    OV7670_write(REG_RGB444, &data); /* disable RGB444 */
//    _delay_ms(50);
//    data = 0xD0;
//    OV7670_write(REG_COM15, &data); /* set RGB565 */
//
//    _delay_ms(50);
//    /* not even sure what all these do, gonna check the oscilloscope and go
//     * from there... */
//    data = 0x16;
//    OV7670_write(REG_HSTART, &data);
//    _delay_ms(50);
//    data = 0x04;
//    OV7670_write(REG_HSTOP, &data);
//    _delay_ms(50);
//    data = 0x24;
//    OV7670_write(REG_HREF, &data);
//    _delay_ms(50);
//    data = 0x02;
//    OV7670_write(REG_VSTART, &data);
//    _delay_ms(50);
//    data = 0x7a;
//    OV7670_write(REG_VSTOP, &data);
//    _delay_ms(50);
//    data = 0x0a;
//    OV7670_write(REG_VREF, &data);
//    _delay_ms(50);
//    data = 0x02;
//    OV7670_write(REG_COM10, &data);
//    _delay_ms(50);
//    data = 0x04;
//    OV7670_write(REG_COM3, &data);
//    _delay_ms(50);
//    data = 0x3f;
//    OV7670_write(REG_MVFP, &data);

//    _delay_ms(50);
//    /* 160x120, i think */
//    data = 0x1a;
//    OV7670_write(REG_COM14, &data); // divide by 4
//    _delay_ms(50);
//    data = 0x22;
//    OV7670_write(0x72, &data); // downsample by 4
//    _delay_ms(50);
//    data =0xf2 ;
//    OV7670_write(0x73, &data); // divide by 4


//    /* 320x240: */
//    data = 0x19;
//    OV7670_write(REG_COM14, &data);
//    data = 0x11;
//    OV7670_write(0x72, &data);
//    data = 0xf1;
//    OV7670_write(0x73, &data);

//    // test pattern
////    data = 0xf0;
////    OV7670_write(0x70, &data);
////    data = 0xf0;
////    OV7670_write(0x71, &data);
////    _delay_ms(50);
////     COLOR SETTING
//    data = 0x80;
//    OV7670_write(0x4f, &data);
////    _delay_ms(50);
//    data = 0x80;
//    OV7670_write(0x50, &data);
////    _delay_ms(50);
//    data = 0x00;
//    OV7670_write(0x51, &data);
////    _delay_ms(50);
//    data = 0x22;
//    OV7670_write(0x52, &data);
////    _delay_ms(50);
//    data = 0x5e;
//    OV7670_write(0x53, &data);
////    _delay_ms(50);
//    data = 0x80;
//    OV7670_write(0x54, &data);
////    _delay_ms(50);
//    data = 0x40;
//    OV7670_write(0x56, &data);
////    _delay_ms(50);
//    data = 0x9e;
//    OV7670_write(0x58, &data);
////    _delay_ms(50);
//    data = 0x88;
//    OV7670_write(0x59, &data);
////    _delay_ms(50);
//    data = 0x88;
//    OV7670_write(0x5a, &data);
////    _delay_ms(50);
//    data = 0x44;
//    OV7670_write(0x5b, &data);
////    _delay_ms(50);
//    data = 0x67;
//    OV7670_write(0x5c, &data);
////    _delay_ms(50);
//    data = 0x49;
//    OV7670_write(0x5d, &data);
////    _delay_ms(50);
//    data = 0x0e;
//    OV7670_write(0x5e, &data);
////    _delay_ms(50);
//    data = 0x00;
//    OV7670_write(0x69, &data);
////    _delay_ms(50);
//    data = 0x40;
//    OV7670_write(0x6a, &data);
////    _delay_ms(50);
//    data = 0x0a;
//    OV7670_write(0x6b, &data);
////    _delay_ms(50);
//    data = 0x0a;
//    OV7670_write(0x6c, &data);
////    _delay_ms(50);
//    data = 0x55;
//    OV7670_write(0x6d, &data);
////    _delay_ms(50);
//    data = 0x11;
//    OV7670_write(0x6e, &data);
////    _delay_ms(50);
//    data = 0x9f;
//    OV7670_write(0x6f, &data);
////    _delay_ms(50);
//    data = 0x84;
//    OV7670_write(0xb0, &data);
////    _delay_ms(50);

    return 1;
}

void Cam_init(){
	u8 data = 0;
	char str[] = {0,0,0,0,0};

	Cam_Pwr.Init();
	Cam_Rst.Init();

//	RCC_HSEConfig(RCC_HSE_ON);
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO1Div_1);//hsi


	Cam_Pwr.Set_low();
	Cam_Rst.Set_high();
//	_delay_ms(100);
//	Cam_Rst.Set_low();
	_delay_ms(100);
//	SCCB_GPIO_Config();
	I2C_Config(SCCB_Camera,I2C_Ack_Enable);

	/* Configuration for 30 FPS */

//	data=0x80;
//	while(0!=wrOV7670Reg(0x12, data)); //Reset SCCB
//
//	_delay_ms(50);
//
//data = 0;
//// CLKRC register: Prescaler = 2
//rdOV7670Reg(0x11, &data);
//data = (data & 0b10000000) | 0b00000001;
//wrOV7670Reg(0x11, data);
//
//// DBLV register: PLL = 6
//rdOV7670Reg(0x6B, &data);
//data = (data & 0b00111111) | 0b10000000;
//wrOV7670Reg(0x6B, data);
//
///* Configuration for QCIF format */
//
//// COM3 register: Enable format scaling
//rdOV7670Reg(0x0C, &data);
//uint16tostr(str, data, 10);
//printf("%d",data);
//puts(" ");
//data = data | 0b00001000;
//wrOV7670Reg(0x0C, data);
//data = 0;
//rdOV7670Reg(0x0C, &data);
//uint16tostr(str, data, 10);
//printf("%d",data);
//puts(" ");
//
//// COM7 register: Select QCIF format
//rdOV7670Reg(0x12, &data);
//uint16tostr(str, data, 10);
//printf("%d",data);
//puts(" ");
//data = (data & 0b11000111) | 0b00010000;
//wrOV7670Reg(0x12, data);
//data = 0;
//rdOV7670Reg(0x12, &data);
//uint16tostr(str, data, 10);
//printf("%d",data);
//puts(" ");
	//TODO:
	for (int i = 0; i < OV7670_REG_NUM2; i++) {
		_delay_ms(10);
			data = OV7670_QVGA[i][1];
			OV7670_write(OV7670_QVGA[i][0], &data);
	}
	for (int i = 0; i < OV7670_REG_NUM; i++) {
		_delay_ms(10);
			data = OV7670_reg[i][1];
			OV7670_write(OV7670_reg[i][0], &data);
	}
	for (int i = 0; i < 30; i++) {
		_delay_ms(10);
			data = OV[i][1];
			OV7670_write(OV[i][0], &data);
	}
	while(ov7670_init() != 1){

	}


	// CLKRC register: Prescaler = 2
	OV7670_read(0x11, &data);
	data = (data & 0b10000000) | 0b00000001;
	OV7670_write(0x11, &data);

//	// DBLV register: PLL = 6
//	OV7670_read(0x6B, &data);
//	data = (data & 0b00111111) | 0b10000000;
//	OV7670_write(0x6B, &data);

	/* Configuration for QCIF format */

//	// COM3 register: Enable format scaling
//	OV7670_read(0x0C, &data);
//	uint16tostr(str, data, 10);
//	printf("%d",data);
//	puts(" ");
//	data = data | 0b00001000;
//	OV7670_write(0x0C, &data);
//	data = 0;
//
////		OV7670_read(0x0C, &data);
////		data = (data & 0b10111111) | 0b00000000;
////		OV7670_write(0x0C, &data);
//
//	OV7670_read(0x0C, &data);
//	uint16tostr(str, data, 10);
//	printf("%d",data);
//	puts(" ");
//
//	// COM7 register: Select QCIF format
//	OV7670_read(0x12, &data);
//	uint16tostr(str, data, 10);
//	printf("%d",data);
//	puts(" ");
//	data = (data & 0b11000111) | 0b00001000;//0b00001100
//	OV7670_write(0x12, &data);
//	data = 0;
//	OV7670_read(0x12, &data);
//	uint16tostr(str, data, 10);
//	printf("%d",data);
//	puts(" ");
	/* Configuration for QCIF format */

//	// COM3 register: Enable format scaling
//	tmp = readOV7670(0x0C);
//	writeOV7670(0x0C, tmp | 0b00001000);
//
//	// COM7 register: Select QCIF format
//	tmp = readOV7670(0x12);
//	writeOV7670(0x12, (tmp & 0b11000111) | 0b00001000);

	// RGB565
	OV7670_read(0x40, &data);
	uint16tostr(str, data, 10);
	printf("%d",data);
	puts(" ");
	data = (data & 0b11001111) | 0b00010000;
	OV7670_write(0x40, &data);
	data = 0;
	OV7670_read(0x40, &data);
	uint16tostr(str, data, 10);
	printf("%d",data);
	puts(" ");
//
//	// gain
//	OV7670_read(0x14, &data);
//	uint16tostr(str, data, 10);
//	printf("%d",data);
//	puts(" ");
//	data = (data & 0b00000000) | 0b00110000;
//	OV7670_write(0x14, &data);
//	data = 0;
//	OV7670_read(0x14, &data);
//	uint16tostr(str, data, 10);
//	printf("%d",data);
//	puts(" ");

//	GPIO_PinOut(GPIOA,GPIO_Pin_8);
//	GPIO_PinOut(GPIOA,GPIO_Pin_15);
//
//	GPIO_PinRes(GPIOA,GPIO_Pin_8);
//	GPIO_PinRes(GPIOA,GPIO_Pin_15);

//		RRST_Pin.Init();
//		WRST_Pin.Init();
//		WE_Pin.Init();
//		OE_Pin.Init();
//
//		WE_Pin.Set_high();
//		OE_Pin.Set_high();
//
//		WRST_Pin.Set_high();
//		RRST_Pin.Set_high();
//
//		WRST_Pin.Set_low();
//		RRST_Pin.Set_low();
//		_delay_ms(1);
//		WRST_Pin.Set_high();
//		RRST_Pin.Set_high();
//		_delay_ms(1);

	  EXTI_InitTypeDef   EXTI_InitStructure;

	  NVIC_InitTypeDef   NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
	RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*** Connect DCMI pins to AF13 ***/
	/* HSYNC(PA4), PIXCLK(PA6) */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);
	/* D5(PB6), VSYNC(PB7) */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
	/* D0..1(PC6/7)  PA9 - D0*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);
//	/* D2..4,6..7(PE0/1/4/5/6) */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);

//	GPIO_InitTypeDef   GPIO_InitStructure;
	/*** DCMI GPIOs configuration ***/
	/* HSYNC(PA4), PIXCLK(PA6) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* D5(PB6), VSYNC(PB7) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* D0..1(PC6/7) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;// | GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* D2..4,6..7(PE0/1/4/5/6) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);



//	void DCMI_Config(){
	  DCMI_InitTypeDef DCMI_InitStructure;
	  DMA_InitTypeDef  DMA_InitStructure;

	  /*** Configures the DCMI to receive data from MT9D111 ***/
	  DCMI_DeInit();

	  /* DCMI configuration */
	  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
	  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
	  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
	  DCMI_InitStructure.DCMI_VSPolarity  = DCMI_VSPolarity_High;
	  DCMI_InitStructure.DCMI_HSPolarity  = DCMI_HSPolarity_Low;
	  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
	  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
	  DCMI_Init(&DCMI_InitStructure);
//	  DCMI_JPEGCmd  ( DISABLE );
	  /* Enable interrupts from DCMI interface */
	  /* OPCJONALNIE */
	  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
	  DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
	  DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
	  DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
	  DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
	  /* OPCJONALNIE */


	  /*** Configures the DMA2 to transfer data from DCMI DR to LCD RAM ***/

	  /* DMA2 Stream1 DeInit */
	  DMA_DeInit(DMA2_Stream1);
	  while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
		//TODO:
	  /* DMA2 Stream1 configuration */
	  DMA_InitStructure.DMA_Channel = DMA_Channel_1;
	  DMA_InitStructure.DMA_PeripheralBaseAddr = 0x50050028;//(uint32_t)(DCMI_BASE + 0x28);//DCMI_DR_ADDRESS;//(uint32_t)srcbuf; // Rejestr 32-bitowy
	  DMA_InitStructure.DMA_Memory0BaseAddr = 0x60020000;//(uint32_t)bufor+2;//0x60020000;//(uint32_t)frame_buffer;//(uint32_t)bufor;//LCD->Data;//FSMC_LCD_ADDRESS;   // Rejestr 16-bitowy
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	  DMA_InitStructure.DMA_BufferSize = 1;//buf_size/4;//1;//153600*2;//sizeof(frame_buffer);//50680;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 32-bit
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // 16-bit
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  DMA_Init(DMA2_Stream1, &DMA_InitStructure);

	  /* Enable DMA2 Stream 1 */
//	  DMA_Cmd(DMA2_Stream1, ENABLE);
//	  while (DMA_GetCmdStatus(DMA2_Stream1) != ENABLE);
//	}



//	DCMI_Cmd(ENABLE);
//	DCMI_CaptureCmd(DISABLE);

//	WE_Pin.Set_low();
//	OE_Pin.Set_low();
//	  Delay_ms(3000);

}
int start = 0;
int count = 0;
//void DCMI_IRQHandler(void)
//{
//
//if (DCMI_GetFlagStatus(DCMI_FLAG_VSYNCRI) ==SET)
//{
//	if(start == 0)
//		start = 1;
//	else
//		start = 0;
//	 while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) == RESET);
//			    Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
//			    Write_GDDRAM_Prepare();   // Prepare to write GRAM
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_LINERI) ==SET)
//{
////	DCMI_CaptureCmd ( DISABLE );
////	DCMI_Cmd ( DISABLE );
////	if(start == 1)
////	{
////		count++;
////	}else {
////		if(count != 0)
////		{
////			printf("Lini: %d", count);
////			puts(" ");
////		}
////		count = 0;
////	}
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_LINEMI) ==SET)
//{
////	puts("LINEMI interrupt");
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_FRAMERI) ==SET)
//{
////	puts("frame interrupt");
//
////	DMA_Cmd(DMA2_Stream1, DISABLE);
////		DCMI_CaptureCmd ( DISABLE );
////		DCMI_Cmd ( DISABLE );
////		frame = 1;
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_ERRRI) ==SET)
//{
//	puts("err interrupt");
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_OVFRI) ==SET)
//{
//	puts("OVF interrupt");
//}
//DCMI_ClearFlag(DCMI_FLAG_VSYNCRI);
//DCMI_ClearFlag(DCMI_FLAG_LINERI);
//DCMI_ClearFlag(DCMI_FLAG_LINEMI);
//DCMI_ClearFlag(DCMI_FLAG_FRAMERI);
//DCMI_ClearFlag(DCMI_FLAG_ERRRI);
//DCMI_ClearFlag(DCMI_FLAG_OVFRI);
//}
volatile int send_flag = -1;
int line_l = 0;
void DCMI_IRQHandler(void){
	  // Przerwanie generowane po odebraniu pelnej ramki
	  if(DCMI_GetITStatus(DCMI_IT_FRAME) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
	  }

	  // Przerwanie generowane przy zmianie stanu sygnalu VSYNC
	  // z aktywnego na nieaktywny (VPOL = Low)
	  if(DCMI_GetITStatus(DCMI_IT_VSYNC) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);

//	    if((send_flag == 0 && frame_flag == 0) || (frame_flag == 1 && line_l == 120)){
//	    DMA_Cmd(DMA2_Stream1, ENABLE);
//	    send_flag++;
//	    }
	    // Czekaj, az DMA zakonczy transfer do pamieci RAM wyswietlacza
	    while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) == RESET);
	    Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
	    Write_GDDRAM_Prepare();   // Prepare to write GRAM
	  }

	  // Przerwanie generowane przy zmianie stanu sygnalu HSYNC
	  // z aktywnego na nieaktywny (HPOL = Low)
	  if(DCMI_GetITStatus(DCMI_IT_LINE) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_LINE);
//	    if(send_flag>0 || frame_flag == 1)
//	    	{
//	    	line_l++;
//	    	}
//	    if((frame_flag == 1 && line_l == 120))
//	    {
//		    DMA_Cmd(DMA2_Stream1, ENABLE);
//		    send_flag++;
//	    }
//	    if(((line_l >= 120 && frame_flag == 0) || (line_l >= 240 && frame_flag == 1)) && send_flag != -2)
//	    {
////	    	DMA_Cmd(DMA2_Stream1, DISABLE);
//	    	send_flag = -2;
//	    	DMA_Cmd(DMA2_Stream1, DISABLE);
////	        DCMI_Cmd(DISABLE);
////	        DCMI_CaptureCmd(DISABLE);
//
//	    }
	  }

	  // Przerwanie generowane gdy stare dane (32-bitowe) w rejestrze DCMI_DR
	  // nie zostaly calkowicie przeslane przed nadejsciem nowych danych
	  if(DCMI_GetITStatus(DCMI_IT_OVF) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_OVF);
	  }
	}


//void Capture_to_RAM(void)
//{
//
//DCMI_ClearITPendingBit(DCMI_IT_FRAME | DCMI_IT_OVF | DCMI_IT_ERR | DCMI_IT_VSYNC | 						DCMI_IT_LINE);
//DCMI_ClearFlag (DCMI_FLAG_FRAMERI | DCMI_FLAG_OVFRI | DCMI_FLAG_ERRRI | DCMI_FLAG_VSYNCRI | 					DCMI_FLAG_LINERI);
//dcmi_flag_frameri_bak =FALSE;
//dcmi_flag_errri_bak =FALSE;
//dcmi_flag_ovfri_bak =FALSE;
//DCMI_CaptureCmd(ENABLE);
//
//while ( dcmi_flag_frameri_bak ==FALSE )
//{
//if (dcmi_flag_errri_bak ==TRUE || dcmi_flag_ovfri_bak ==TRUE)
//{
//break;
//}
//}
//
//DCMI_CaptureCmd ( DISABLE );
//DCMI_Cmd ( DISABLE );
//}
//
//TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
//{
//  while(BufferLength--)
//  {
//    if(*pBuffer != *pBuffer1)
//    {
//      return FAILED;
//    }
//
//    pBuffer++;
//    pBuffer1++;
//  }
//
//  return PASSED;
//}

const uint8_t OV7670_Reg[OV7670_REG_NUM3][2]=
{
     /*ÒÔÏÂÎªOV7670 QVGA RGB565²ÎÊý  */
//  	{0x3a, 0x04},//
//	{0x40, 0x10},
//	{0x12, 0x14},
//	{0x32, 0x80},
//	{0x17, 0x16},

//	{0x18, 0x04},
//	{0x19, 0x02},
//	{0x1a, 0x7b},
//	{0x03, 0x06},
//	{0x0c, 0x0c},
//    {0x15, 0x02},
//	{0x3e, 0x00},
//	{0x70, 0x00},
//	{0x71, 0x01},
//	{0x72, 0x11},
//	{0x73, 0x09},

	{0xa2, 0x02},
	{0x11, 0x00},
	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},

	{0x7d, 0x3c},
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},

	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},

	{0x87, 0xc4},
	{0x88, 0xd7},
	{0x89, 0xe8},
	{0x13, 0xe0},
	{0x00, 0x00}, /* AGC */

	{0x10, 0x00},
	{0x0d, 0x00},
	{0x14, 0x20},
	{0xa5, 0x05},
	{0xab, 0x07},

	{0x24, 0x75},
	{0x25, 0x63},
	{0x26, 0xA5},
	{0x9f, 0x78},
	{0xa0, 0x68},

	{0xa1, 0x03},
	{0xa6, 0xdf},
	{0xa7, 0xdf},
	{0xa8, 0xf0},
	{0xa9, 0x90},

	{0xaa, 0x94},
	{0x13, 0xe5},
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},

	{0x1e, 0x37},
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},

	{0x35, 0x0b},
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},
	{0x3c, 0x78},

	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x5d},
	{0x6b, 0x40},
	{0x74, 0x19},
	{0x8d, 0x4f},

	{0x8e, 0x00},
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},

	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},

	{0xb3, 0x82},
	{0xb8, 0x0a},
	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},

	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},

	{0x5b, 0x44},
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},

	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},

	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},

	{0x6e, 0x11},
	{0x6f, 0x9f},
    {0x55, 0x00}, /* ÁÁ¶È */
    {0x56, 0x40}, /* ¶Ô±È¶È */
    {0x57, 0x80}, /* change according to Jim's request */
};

#define ADDR_OV7670   0x42

int Sensor_Init(void)
{
  uint16_t i=0;
  u8 data = 0;

  uint8_t Sensor_IDCode = 0;

////  delay_init();
//
////  GPIO_Configuration();
//
////  I2C_Configuration();
//
//	Cam_Pwr.Init();
//	Cam_Rst.Init();
//
////	RCC_HSEConfig(RCC_HSE_ON);
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO1Div_1);//hsi
//
//
//	Cam_Pwr.Set_low();
//	Cam_Rst.Set_high();
////	_delay_ms(100);
////	Cam_Rst.Set_low();
//	_delay_ms(100);
////	SCCB_GPIO_Config();
//	I2C_Config(SCCB_Camera,I2C_Ack_Enable);
//	_delay_ms(10);

//	OV7670_read(0x11, &data);
//	OV7670_write(0x40, &data);

	data = 0x80;
	OV7670_write(0x12, &data);
//  if( 0 == OV7670_write(0x12, &data) ) /* Reset SCCB */
//  {
//     return 0 ;
//  }
data = 0;
  delay_ms(50);

  OV7670_read(0x0b, &Sensor_IDCode);
//  if( 0 == OV7670_read(0x0b, &Sensor_IDCode) )	 /* read ID */
//  {
//	 return 0;	                              /* error*/
//  }
  if(Sensor_IDCode == OV7670)				  /* ID = OV7670 */
  {
  	 for( i=0 ; i < OV7670_REG_NUM3 ; i++ )
  	 {
  		 data = OV7670_Reg[i][1];
  		OV7670_write(OV7670_Reg[i][0], &data);
//	 	if( 0 == OV7670_write(OV7670_Reg[i][0], &data) )
//	    {
//			return 0;
//	 	}
	 }
  }
  else										  /* NO ID */
  {
      return 0;
  }

  return 1;
}

int main (void)
 {
	uint8_t tmp;
	uint8_t tmpstr[6] = {0,};
	int32_t ret = 0;
	uint8_t memsize[2][8] = { {2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};
  /* Initialization */

	RCC_HSEConfig(RCC_HSE_ON);
	while(!RCC_WaitForHSEStartUp())
	{
	}

//  Init_SysTick();
  SysTick_Config(180);

  	for(int o = 0; o<buf_size ;o++)
  	{
  		bufor[o] = 0;//o%10 + 48;
  	}
    TM_ADC_Init(ADC1,TM_ADC_Channel_12);
    Eth_init();
    Init_GPIO();
    Init_FSMC();
    Init_LCD();
    pwm_init();
    touch_init();

    Clear_Screen(LCD_WHITE);
    Set_Font(&Font16x24);

    Cam_init();
    ov7670_init();
//    while( 1 != Sensor_Init() );

    DMA_Cmd(DMA2_Stream1, ENABLE);
    DCMI_Cmd(ENABLE);
    DCMI_CaptureCmd(ENABLE);
    send_flag = 0;
//    for(int y = 0; y<50200;y++)
//    	bufor[y] = 5;
//    while(!frame);
//    C# Code to convert the YUYV pair (y1/u/y2/v) in a RGB pair:
//    r1 = (int)((float)y1 – 1.4075 * (float)(v – 128));
//    g1 = (int)((float)y1 – 0.3455 * (float)(u – 128) + 0.7169 * (float)(v – 128));
//    b1 = (int)((float)y1 + 1.7790 * (float)(u – 128));
//    r2 = (int)((float)y2 – 1.4075 * (float)(v – 128));
//    g2 = (int)((float)y2 – 0.3455 * (float)(u – 128) + 0.7169 * (float)(v – 128));
//    b2 = (int)((float)y2 + 1.7790 * (float)(u – 128));
//int r,g,b,o = 0;
//uint16_t pix;
//        Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
//        Write_GDDRAM_Prepare();   // Prepare to write GRAM
//    for(int j = 0;j < 144;j++)
//    	for(int k = 0;k < 176;k++){
//
////    		r = bufor[o];
////    		g = bufor[o];
////    		b = bufor[o];
//
//    		    r = (int)(((float)bufor[o]) – 1.4075 * ((float)(bufor[o+3]) – 128));
//    		    g = (int)((float)bufor[o] – 0.3455 * (float)(bufor[o+1] – 128) + 0.7169 * (float)(bufor[o+3] – 128));
//    		    b = (int)((float)bufor[o] + 1.7790 * (float)(bufor[o+1] – 128));
//    	  		pix = 0;
//    	    		pix = ((r << 11) | (g << 5) | b);
//    	    		Draw_Pixel(j,k,pix);
//    		    r = (int)((float)bufor[o+2] – 1.4075 * (float)(bufor[o+3] – 128));
//    		    g = (int)((float)bufor[o+2] – 0.3455 * (float)(bufor[o+1] – 128) + 0.7169 * (float)(bufor[o+3] – 128));
//    		    b = (int)((float)bufor[o+2] + 1.7790 * (float)(bufor[o+1] – 128));
//    	  		pix = 0;
//    	    		pix = ((r << 11) | (g << 5) | b);
//    	    		Draw_Pixel(j,k+1,pix);
//    		o += 2;
//    		Draw_Pixel(j,k,pix);
//    	}
//    while(DCMI->CR & 0x1);
//    while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);



	    Draw_Image(0, 319, 240, 320, img03);


	    // register the chip select/ deselect fucntion
	    reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);

	    // register the chip read/ write fucntion
	    reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);

	    /* wizchip initialize*/
	    if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1) {
	        printf("WIZCHIP Initialized fail.\r\n");
	        while(1);
	    }

//	    do
//	    {
//	        if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1)
//	            printf("Unknown PHY Link stauts.\r\n");
//	    }while(tmp == PHY_LINK_OFF);

	    /* wizchip netconf */
	    ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);

	    gWIZNETINFO.ip[0] = 192;
	    gWIZNETINFO.ip[1] = 168;
	    gWIZNETINFO.ip[2] = 1;
	    gWIZNETINFO.ip[3] = 125;

//	    gWIZNETINFO.sn[0] = 255;
//	    gWIZNETINFO.sn[1] = 255;
//	    gWIZNETINFO.sn[2] = 255;
//	    gWIZNETINFO.sn[3] = 0;

	    printf("=== %s NET CONF ===\r\n",(char*)tmpstr);
	    printf("MAC:%02X.%02X.%02X.%02X.%02X.%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
	                                                      gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	    printf("GAR:%d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	    printf("SUB:%d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	    printf("SIP:%d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);

	    // set network configuration
	    ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);

	    // get network configuration
	    ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);

	    // Display network configuration
	    ctlwizchip(CW_GET_ID,(void*)tmpstr);
	    printf("=== %s NET CONF ===\r\n",(char*)tmpstr);
	    printf("MAC:%02X.%02X.%02X.%02X.%02X.%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
	                                                      gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	    printf("GAR:%d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	    printf("SUB:%d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	    printf("SIP:%d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);

//	    uint16_t i = 0, j = 0,l = 0;
//
//	   	        for(i = 0; i < 240; i++)
//	   	        {
//	   	          if((i*320)%16000 == 0) l++;
//	   	          Set_Cursor((0+i), 319);
//	   	          Write_GDDRAM_Prepare();
//
//	   	          for(j = 0; j < 320; j++)
//	   	          {
//	   	            Write_Data(bufor[((i*320)+j)-(16000*l)]);
//	   	          }
//	   	        }
//	    Draw_Image(0, 319, 120, 320, (uint16_t*)bufor+1);


//puts("ha");
  while(1)
  {

	  listen2();


  }

}


void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {
//	  printf("Dotyk: ");
	  u16 X = 0, Y = 0;
	  ret_pos(&X,&Y);

	  printf("Dotyk: %d  %d",X,Y);
	  puts("hi");

	    Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
	    Write_GDDRAM_Prepare();   // Prepare to write GRAM
	    DMA_Cmd(DMA2_Stream1, ENABLE);
	    DCMI_Cmd(ENABLE);
	    DCMI_CaptureCmd(ENABLE);
	  //
//	  if(X>160 && which<5)
//		  which++;
//	  else if(X>160)
//		  which = 1;
//	  else if(X<160 && which>1)
//		  which--;
//	  else
//		  which = 5;
//
//	  switch (which) {
//		case 1:
//			Draw_Image(0, 319, 240, 320, img03);(GPIOD, GPIO_Pin_13);
//			break;
//		case 2:
//			Draw_Image(0, 319, 240, 320, img04);(GPIOD, GPIO_Pin_13);
//			break;
//		case 3:
//			Draw_Image(0, 319, 240, 320, img05);(GPIOD, GPIO_Pin_13);
//			break;
//		case 4:
//			Draw_Image(0, 319, 240, 320, img06);(GPIOD, GPIO_Pin_13);
//			break;
//		default:
//			break;
//	}
	  delay_ms(500);



    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
}


/*
 * The width of the CRC calculation and result.
 * Modify the typedef for a 16 or 32-bit CRC standard.
 */
//typedef uint8_t crc;
//
//#define WIDTH  (8 * sizeof(crc))
//#define TOPBIT (1 << (WIDTH - 1))
//#define POLYNOMIAL 0xD8

//crc
//crcSlow(uint8_t const message[], int nBytes)
//{
//    crc  remainder = 0;
//
//
//    /*
//     * Perform modulo-2 division, a byte at a time.
//     */
//    for (int byte = 0; byte < nBytes; ++byte)
//    {
//        /*
//         * Bring the next byte into the remainder.
//         */
//        remainder ^= (message[byte] << (WIDTH - 8));
//
//        /*
//         * Perform modulo-2 division, a bit at a time.
//         */
//        for (uint8_t bit = 8; bit > 0; --bit)
//        {
//            /*
//             * Try to divide the current data bit.
//             */
//            if (remainder & TOPBIT)
//            {
//                remainder = (remainder << 1) ^ POLYNOMIAL;
//            }
//            else
//            {
//                remainder = (remainder << 1);
//            }
//        }
//    }
//
//    /*
//     * The final remainder is the CRC result.
//     */
//    return (remainder);
//
//}   /* crcSlow() */

static u_long crc_table[256] = {
        0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
        0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
        0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
        0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
        0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
        0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
        0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
        0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
        0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
        0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
        0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
        0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
        0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
        0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
        0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
        0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
        0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
        0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
        0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
        0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
        0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
        0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
        0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
        0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
        0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
        0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
        0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
        0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
        0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
        0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
        0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
        0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
        0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
        0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
        0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
        0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
        0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
        0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
        0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
        0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
        0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
        0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
        0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4};

u_long crc32 (char *data, int len)
{
        register int i;
        u_long crc = 0xffffffff;

        for (i=0; i<len; i++);
                crc = (crc << 8) ^ crc_table[((crc >> 24) ^ *data++) & 0xff];

        return crc;
}

u_long cc;

int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t size)
{
   int32_t ret = 0;
   ret = recv(sn,buf,1);
   if(ret != size)
   {
      if(ret < 0)
      {
         printf("%d:recv() error:%ld\r\n",sn,ret);
         close(sn);
         return ret;
      }
   }

//   for(int i = 0; i<ret;i++)
//	   printf("%c",buf[0]);

//   puts(" ");

//   if(buf[0] == 's')
//	   send_flag = 0;
   int s = 1;
   bufor[0] = 1;
while(1){
// 	for(int o = 0; o<buf_size ;o++)
// 	{
// 		bufor[o] = 0;//o%250;
// 	}
   while(send_flag != -2);



//   send(sn,bufor,146);
if(frame_flag == 1)
	for(int y = 0;y<5;y++)
   Draw_Image(0, 319, 120, 320, (uint16_t*)bufor+1);
else if(frame_flag == 0)
	for(int y = 0;y<5;y++)
	Draw_Image(119, 319, 120, 320, (uint16_t*)bufor+1);
//   cc = crc32((char*)bufor+2,buf_size-2);
//   cc = crc32((char*)img03,153600);

//   bufor[0] = 1;

//   _delay_s(2);
if(frame_flag == 0)
   for(; s<=100; s++)
   {
	   if(s == 1)
		   send(sn,&bufor[(s-1)*send_size],send_size);
	   else
		   send(sn,&bufor[(s-1)*(send_size-2)],send_size);
//	   _delay_ms(1);
	   _delay_us(50);
//	   do{
//		   ret = recv(sn,buf,1);
//	   }while(ret != 1);

//	   if(buf[0] == 'c'){
		   bufor[((s-1)*(send_size-2)) + send_size-2] = s + 1;
		   bufor[((s-1)*(send_size-2)) + send_size-1] = 0;
//	   }
//	   else if(buf[0] == 'b')
//		   break;
   }
else if(frame_flag == 1)
	   for(int ss = 1; ss<=100; ss++)
	   {
		   if(ss == 1)
			   send(sn,&bufor[(ss-1)*send_size],send_size);
		   else
			   send(sn,&bufor[(ss-1)*(send_size-2)],send_size);
	//	   _delay_ms(1);
		   _delay_us(50);
//		   do{
//			   ret = recv(sn,buf,1);
//		   }while(ret != 1);
//
//		   if(buf[0] == 'c'){
			   bufor[((ss-1)*(send_size-2)) + send_size-2] = s + 1;
			   bufor[((ss-1)*(send_size-2)) + send_size-1] = 0;
	//	   }
	//	   else if(buf[0] == 'b')
	//		   break;
			   s++;
	   }
 if(s == 101)
 {
	 	for(int o = 0; o<buf_size ;o++)
	 	{
	 		bufor[o] = 0;//o%250;
	 	}
		   do{
			   ret = recv(sn,buf,1);
		   }while(ret != 1);

		   if(buf[0] == 'n'){
	 frame_flag = 1;
	 send_flag = 0;
	 line_l = 0;
//     DCMI_Cmd(ENABLE);
//     DCMI_CaptureCmd(ENABLE);
      bufor[0] = 101;
		   }
 }
 else if(s == 201)
 {
	 frame_flag = 5;
	 send_flag = -1;
	 line_l = 0;
//     DCMI_Cmd(ENABLE);
//     DCMI_CaptureCmd(ENABLE);
     bufor[0] = 1;
 }
//   size = ret;
}
//   ret = send(sn,buf,size);
//
//   if(ret != size)
//   {
//      if(ret < 0)
//      {
//         printf("%d:send() error:%ld\r\n",sn,ret);
//         close(sn);
//      }
//   }
   return ret;
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}
#endif


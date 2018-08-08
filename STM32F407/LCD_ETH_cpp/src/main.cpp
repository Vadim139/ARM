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
uint8_t bufor[50200];//50689 50112

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO TestStatus  TransferStatus = FAILED;

//#define DCMI_DR_ADDRESS   DCMI_DR_ADDRESS//0x50050028//0x28
//#define FSMC_LCD_ADDRESS  bufor
//#define DCMI_DR_ADDRESS   0x50050028
#define DCMI_DR_ADDRESS   0x28
#define FSMC_LCD_ADDRESS  LCD_BASE

#define TRUE true
#define FALSE false

uint8_t frame = 0;

GPIO_IO Cam_Rst(Cam_Port1,Cam_RST,0);
GPIO_IO Cam_Pwr(Cam_Port1,Cam_PWR,0);

uint8_t	  dcmi_flag_frameri_bak, dcmi_flag_lineri_bak, dcmi_flag_errri_bak,
dcmi_flag_ovfri_bak, dcmi_flag_vsyncri_bak;

//#define RST_P GPIOE
//#define WRST GPIO_Pin_2
//#define RRST GPIO_Pin_3
//
//#define OWE_P GPIOB
//#define OE GPIO_Pin_4
//#define WE GPIO_Pin_5
//
//GPIO_IO WE_Pin(OWE_P,WE,0);
//GPIO_IO OE_Pin(OWE_P,OE,0);
//GPIO_IO WRST_Pin(RST_P,WRST,0);
//GPIO_IO RRST_Pin(RST_P,RRST,0);

int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t size);
int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t size);


#define DATA_BUF_SIZE   2048
uint8_t gDATABUF[DATA_BUF_SIZE];
wiz_NetInfo gWIZNETINFO;

uint8_t listen2(){
	uint8_t tmp;
	uint8_t str[5];
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
	     	 send(sn,bufor,sizeof(bufor));
//	     	 _delay_s(5);
//	     }
////	     str = {'1','2','3',' ','6'};
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

//	for(int i = 0;i<100;i++)//50688
//		bufor[i] = 0;

//	TM_MCOOUTPUT_InitMCO1();
//	TM_MCOOUTPUT_SetOutput1(TM_MCOOUTPUT1_Source_HSI,TM_MCOOUTPUT_Prescaler_1);

//		TIM1_PWM_Config(1, 5, 2);
//		TIM_SetCompare1(TIM1, 1);//(0us / 50us = 0.0)

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
	  DMA_InitStructure.DMA_Memory0BaseAddr = 0x60020000;//(uint32_t)frame_buffer;//(uint32_t)bufor;//LCD->Data;//FSMC_LCD_ADDRESS;   // Rejestr 16-bitowy
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	  DMA_InitStructure.DMA_BufferSize = 1;//153600*2;//sizeof(frame_buffer);//50680;
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

void DCMI_IRQHandler(void){
	  // Przerwanie generowane po odebraniu pelnej ramki
	  if(DCMI_GetITStatus(DCMI_IT_FRAME) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
	  }

	  // Przerwanie generowane przy zmianie stanu sygnalu VSYNC
	  // z aktywnego na nieaktywny (VPOL = Low)
	  if(DCMI_GetITStatus(DCMI_IT_VSYNC) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);

	    // Czekaj, az DMA zakonczy transfer do pamieci RAM wyswietlacza
	    while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) == RESET);
	    Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
	    Write_GDDRAM_Prepare();   // Prepare to write GRAM
	  }

	  // Przerwanie generowane przy zmianie stanu sygnalu HSYNC
	  // z aktywnego na nieaktywny (HPOL = Low)
	  if(DCMI_GetITStatus(DCMI_IT_LINE) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_LINE);
	  }

	  // Przerwanie generowane gdy stare dane (32-bitowe) w rejestrze DCMI_DR
	  // nie zostaly calkowicie przeslane przed nadejsciem nowych danych
	  if(DCMI_GetITStatus(DCMI_IT_OVF) == SET){
	    DCMI_ClearITPendingBit(DCMI_IT_OVF);
	  }
	}
//void DCMI_IRQHandler(void)
//{
//
//if (DCMI_GetFlagStatus(DCMI_FLAG_VSYNCRI) ==SET)
//{
//dcmi_flag_vsyncri_bak =TRUE;
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_LINERI) ==SET)
//{
//dcmi_flag_lineri_bak =TRUE;
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_LINEMI) ==SET)
//{
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_FRAMERI) ==SET)
//{
//dcmi_flag_frameri_bak =TRUE;
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_ERRRI) ==SET)
//{
//dcmi_flag_errri_bak =TRUE;
//}
//if (DCMI_GetFlagStatus(DCMI_FLAG_OVFRI) ==SET)
//{
//dcmi_flag_ovfri_bak =TRUE;
//}
//DCMI_ClearFlag(DCMI_FLAG_VSYNCRI);
//DCMI_ClearFlag(DCMI_FLAG_LINERI);
//DCMI_ClearFlag(DCMI_FLAG_LINEMI);
//DCMI_ClearFlag(DCMI_FLAG_FRAMERI);
//DCMI_ClearFlag(DCMI_FLAG_ERRRI);
//DCMI_ClearFlag(DCMI_FLAG_OVFRI);
//}

void Capture_to_RAM(void)
{

DCMI_ClearITPendingBit(DCMI_IT_FRAME | DCMI_IT_OVF | DCMI_IT_ERR | DCMI_IT_VSYNC | 						DCMI_IT_LINE);
DCMI_ClearFlag (DCMI_FLAG_FRAMERI | DCMI_FLAG_OVFRI | DCMI_FLAG_ERRRI | DCMI_FLAG_VSYNCRI | 					DCMI_FLAG_LINERI);
dcmi_flag_frameri_bak =FALSE;
dcmi_flag_errri_bak =FALSE;
dcmi_flag_ovfri_bak =FALSE;
DCMI_CaptureCmd(ENABLE);

while ( dcmi_flag_frameri_bak ==FALSE )
{
if (dcmi_flag_errri_bak ==TRUE || dcmi_flag_ovfri_bak ==TRUE)
{
break;
}
}

DCMI_CaptureCmd ( DISABLE );
DCMI_Cmd ( DISABLE );
}

TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer != *pBuffer1)
    {
      return FAILED;
    }

    pBuffer++;
    pBuffer1++;
  }

  return PASSED;
}

int main (void)
{
	uint8_t tmp;
	uint8_t tmpstr[6] = {0,};
	int32_t ret = 0;
	uint8_t memsize[2][8] = { {0,0,16,0,0,0,0,0},{2,2,2,2,2,2,2,2}};
  /* Initialization */

	RCC_HSEConfig(RCC_HSE_ON);
	while(!RCC_WaitForHSEStartUp())
	{
	}

//  Init_SysTick();
  SysTick_Config(168);

    TM_ADC_Init(ADC1,TM_ADC_Channel_12);
    Eth_init();
    Init_GPIO();
    Init_FSMC();
    Init_LCD();
    pwm_init();
    touch_init();
    Clear_Screen(LCD_WHITE);
//    Draw_Image(0, 319, 240, 320, img03);(GPIOD, GPIO_Pin_13);
    Set_Font(&Font16x24);
    Cam_init();
    ov7670_init();
//    Capture_to_RAM();
//    Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
//    Write_GDDRAM_Prepare();   // Prepare to write GRAM
    DMA_Cmd(DMA2_Stream1, ENABLE);
    DCMI_Cmd(ENABLE);
    DCMI_CaptureCmd(ENABLE);

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

//    TransferStatus = Buffercmp(srcbuf, bufor, 10);

//	char StrNumber1[10] = {'H','E','L','L','O'};
////	char StrNumber2[10];
//	u16 data = 213;
////	uint32_t Number;
//
	    Draw_Image(0, 319, 240, 320, img03);
////		Draw_Full_Rect(43, 295 ,61 ,25 , LCD_BLACK);
////		uint16tostr(StrNumber1, data, 10);
//		Display_String(43, 295, StrNumber1, LCD_BLACK);
//while(1)
//{
//
//}
//	  Delay_ms(3000);

//
//	    // register the chip select/ deselect fucntion
//	    reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
//
//	    // register the chip read/ write fucntion
//	    reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
//
//	    /* wizchip initialize*/
//	    if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1) {
//	        printf("WIZCHIP Initialized fail.\r\n");
//	        while(1);
//	    }
//
////	    do
////	    {
////	        if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1)
////	            printf("Unknown PHY Link stauts.\r\n");
////	    }while(tmp == PHY_LINK_OFF);
//
//	    /* wizchip netconf */
//	    ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
//
//	    gWIZNETINFO.ip[0] = 192;
//	    gWIZNETINFO.ip[1] = 168;
//	    gWIZNETINFO.ip[2] = 1;
//	    gWIZNETINFO.ip[3] = 125;
//
////	    gWIZNETINFO.sn[0] = 255;
////	    gWIZNETINFO.sn[1] = 255;
////	    gWIZNETINFO.sn[2] = 255;
////	    gWIZNETINFO.sn[3] = 0;
//
//	    printf("=== %s NET CONF ===\r\n",(char*)tmpstr);
//	    printf("MAC:%02X.%02X.%02X.%02X.%02X.%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
//	                                                      gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
//	    printf("GAR:%d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
//	    printf("SUB:%d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
//	    printf("SIP:%d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
//
//	    // set network configuration
//	    ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);
//
//	    // get network configuration
//	    ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
//
//	    // Display network configuration
//	    ctlwizchip(CW_GET_ID,(void*)tmpstr);
//	    printf("=== %s NET CONF ===\r\n",(char*)tmpstr);
//	    printf("MAC:%02X.%02X.%02X.%02X.%02X.%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
//	                                                      gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
//	    printf("GAR:%d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
//	    printf("SUB:%d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
//	    printf("SIP:%d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);

//puts("ha");
  while(1)
  {
//  Delay_ms(5000);
//  printf("%d",bufor[0]);
//  puts(" ");
//	  listen2();
//    printf("Error");
//    Delay_ms(5);
//    while(1);

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



int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t size)
{
   int32_t ret = 0;
   ret = recv(sn,buf,size);
   if(ret != size)
   {
      if(ret < 0)
      {
         printf("%d:recv() error:%ld\r\n",sn,ret);
         close(sn);
         return ret;
      }
   }
   for(int i = 0; i<ret;i++)
	   printf("%c",buf[i]);
   puts(" ");
   size = ret;
   ret = send(sn,buf,size);
   if(ret != size)
   {
      if(ret < 0)
      {
         printf("%d:send() error:%ld\r\n",sn,ret);
         close(sn);
      }
   }
   return ret;
}

int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t size)
{
   int32_t  ret = 0;
   static uint8_t  addr[4] = {0,};
   static uint16_t port = 0;
   uint8_t  packinfo;

   if((ret = recvfrom(sn,buf,size, addr,&port,&packinfo)) < 0)
   {
      printf("%d:recvfrom error:%ld\r\n",sn,ret);
      return ret;
   }
   if(packinfo & 0x80)
   {
      printf("%d:recvfrom %d.%d.%d.%d(%d), size=%ld.\r\n",sn,addr[0],addr[1],addr[2],addr[3],port, ret);
   }
   if(packinfo & 0x01)
   {
      printf("%d:recvfrom remained packet.\r\n",sn);
   }
   else
   {
      printf("%d:recvfrom completed.\r\n",sn);
   }
   if( (ret = sendto(sn, buf, ret, addr, port)) < 0)
   {
      printf("%d:sendto error:%ld\r\n",sn,ret);
      return ret;
   }
   printf("%d:sendto %d.%d.%d.%d(%d), size=%ld\r\n",sn,addr[0],addr[1],addr[2],addr[3],port, ret);
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

/**
  * @}
  */

/**
  * @}
  */

///******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
//
///**
// *
// */
///* Includes *******************************************************************/
//#include "main.h"
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
////#include "img/img00.h"
//#include "img/img01.h"
////#include "img/img02.h"
//#include "img/img03.h"
//#include "img/img04.h"
//#include "img/img05.h"
//#include "img/img06.h"
//#include "OV7670_I2C.h"
//#include "STM32F3_my.h"
//#include "tm_stm32f4_adc.h"
//#include "Ethernet/wizchip_conf.h"
//#include "Ethernet/socket.h"
//#include "STM32F4_my.h";
////#include "Ethernet/socket.h"
////extern unsigned char bmp1[];
//
////void  wizchip_select(void);
////void  wizchip_deselect(void);
////uint8_t wizchip_read();
////void  wizchip_write(uint8_t wb);
//int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t size);
//int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t size);
//
//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//TIM_OCInitTypeDef  TIM_OCInitStructure;
//uint16_t CCR1_Val = 300;
//uint16_t CCR2_Val = 100;
//
//volatile int which = 5;
//#define DCMI_DR_ADDRESS   0x28
//#define FSMC_LCD_ADDRESS  LCD_BASE
//
//#define DATA_BUF_SIZE   2048
//uint8_t gDATABUF[DATA_BUF_SIZE];
//wiz_NetInfo gWIZNETINFO;
//
//uint8_t listen2(){
//	uint8_t tmp;
//	uint8_t tmpstr[6] = {0,};
//	int32_t ret = 0;
//
//	while(1){
//	uint8_t sn = 2;
//	     if((ret = socket(sn,Sn_MR_TCP,3000,SF_TCP_NODELAY)) != sn)
//	     {
//	        printf("%d:socket() error:%ld\r\n", sn,ret);
//	        close(sn);
//	        continue;
//	     }
//	     printf("%d:socket() ok.\r\n",sn);
//
//
//	     if((ret = listen(sn)) != SOCK_OK)
//	     {
//	        printf("%d:listen() error:%ld",sn,ret);
//	        close(sn);
//	        return ret;
//	     }
//	     printf("%d:listen() ok.\r\n",sn);
//
//
//	     if(((ret = socket(sn+1, Sn_MR_UDP, 3000, 0)) != sn+1))
//	     {
//	        printf("%d:socket() error:%ld\r\n", sn+1,ret);
//	        continue;
//	     }
//	     do
//	     {
//	        getsockopt(sn,SO_STATUS, &tmp);
//	     }while(tmp != SOCK_CLOSED && tmp != SOCK_ESTABLISHED);
//	     if(tmp == SOCK_CLOSED) continue;
//	     //Accept for client
//	     printf("%d:connected\r\nLBStarted Blocking mode\r\n",sn);
//
//	     while(1)
//	     {
//	        if((ret = loopback_tcps(sn, gDATABUF, DATA_BUF_SIZE)) < 0)
//	        {
//	           printf("%d:loopback_tcps error:%ld\r\n",sn,ret);
//	           break;
//	        }
//	/*
//	        if((ret=loopback_udps(sn+1,gDATABUF,10)) < 0)
//	        {
//	           printf("%d:loopback_udps error:%ld\r\n",sn+1,ret);
//	           break;
//	        }
//	*/}
//	     }
//}
//int main (void)
//{
//	uint8_t tmp;
//	uint8_t tmpstr[6] = {0,};
//	int32_t ret = 0;
//	uint8_t memsize[2][8] = { {2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};
//  /* Initialization */
//
//	RCC_HSEConfig(RCC_HSE_ON);
//	while(!RCC_WaitForHSEStartUp())
//	{
//	}
//
////  Init_SysTick();
//  SysTick_Config(168);
//  Init_GPIO();
//  Init_FSMC();
//  Init_LCD();
//  pwm_init();
////  touch_init();
//  TM_ADC_Init(ADC1,TM_ADC_Channel_1);
//  TM_ADC_Init(ADC1,TM_ADC_Channel_2);
////  Delay_ms(3000);
////  _delay_us(500);
////  _delay_ms(5);
////  _delay_s(1);
////  /////////////////////////////////////////////////////////////////
////  GPIO_InitTypeDef   GPIO_InitStructure;
////  SPI_InitTypeDef  SPI_InitStructure;
////
////  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
////  RCC_APB1PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
////
////  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOB |
////		  RCC_AHB1Periph_GPIOA, ENABLE);
////
////  /*!< SPI pins configuration *************************************************/
////
////  /*!< Connect SPI pins to AF5 */
////  GPIO_PinAFConfig(GPIOA,  GPIO_Pin_5,GPIO_AF_SPI1);
////  GPIO_PinAFConfig(GPIOB, GPIO_Pin_4, GPIO_AF_SPI1);
////  GPIO_PinAFConfig(GPIOB, GPIO_Pin_5, GPIO_AF_SPI1);
////
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
////  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
////
////  /*!< SPI SCK pin configuration */
////  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
////  GPIO_Init(GPIOA, &GPIO_InitStructure);
////
////  /*!< SPI MOSI pin configuration */
////  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
////  GPIO_Init(GPIOB, &GPIO_InitStructure);
////
////  /*!< SPI MISO pin configuration */
////  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
////  GPIO_Init(GPIOB, &GPIO_InitStructure);
////
////  /*!< SPI configuration */
////  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
////  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
////  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
////  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//High
////  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//2Edge
////  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
////  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
////  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
////  SPI_InitStructure.SPI_CRCPolynomial = 7;
////  SPI_Init(SPI1, &SPI_InitStructure);
////
////  /*!< Enable the sFLASH_SPI  */
////  SPI_Cmd(SPI1, ENABLE);
//  ///////////////////////////////////////////////////////////////////
//  Eth_init();
//
//
//  /*!< At this stage the microcontroller clock setting is already configured,
//         this is done through SystemInit() function which is called from startup
//         file (startup_stm32f4xx.s) before to branch to application main.
//         To reconfigure the default setting of SystemInit() function, refer to
//         system_stm32f4xx.c file
//       */
//
//  /* Demo */
//  TIM4->CCR1 = CCR1_Val;
//  //TIM4->CCR2 = CCR2_Val;
//
//  Clear_Screen(0x0000);
////	Demo_MMIA();
//	u16 X, Y;
//	char StrNumber1[10];
//	char StrNumber2[10];
//	u16 data = 0;
//	uint32_t Number;
//
//	I2C_Config(SCCB_Camera,I2C_Ack_Enable);
////	/* Configuration for QCIF format */
////
//////		// COM3 register: Enable format scaling
//////		OV7670_read(0x0C, &data);
//////		data = data | 0b00001000;
//////		OV7670_write(0x0C, &data);
//////
//////		// COM7 register: Select QCIF format
//////		OV7670_read(0x0C, &data);
//////		data = (data & 0b11000111) | 0b00001000;
//////	  uint16tostr(StrNumber1, data, 10);
//////	  Display_String(43, 100, StrNumber1, LCD_WHITE);
//////		OV7670_write(0x12, &data);
//////	  data = 0;
//////	  uint16tostr(StrNumber1, data, 10);
//////	  Display_String(43, 150, StrNumber1, LCD_WHITE);
//////		OV7670_read(0x0C, &data);
//////	  	uint16tostr(StrNumber1, data, 10);
//////	  Display_String(43, 200, StrNumber1, LCD_WHITE);
////
////	GPIO_PinOut(GPIOA,GPIO_Pin_8);
////	GPIO_PinOut(GPIOA,GPIO_Pin_15);
////
////	GPIO_PinRes(GPIOA,GPIO_Pin_8);
////	GPIO_PinRes(GPIOA,GPIO_Pin_15);
////
////	  EXTI_InitTypeDef   EXTI_InitStructure;
////
////	  NVIC_InitTypeDef   NVIC_InitStructure;
////
////	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
////	RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);
////	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
////	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
////
////	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);
////
////	/*** Connect DCMI pins to AF13 ***/
////	/* HSYNC(PA4), PIXCLK(PA6) */
////	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);
////	/* D5(PB6), VSYNC(PB7) */
////	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
////	/* D0..1(PC6/7)  PA9 - D0*/
////	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);
////	/* D2..4,6..7(PE0/1/4/5/6) */
////	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
////	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);
////
////	GPIO_InitTypeDef   GPIO_InitStructure;
////	/*** DCMI GPIOs configuration ***/
////	/* HSYNC(PA4), PIXCLK(PA6) */
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_9;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
////	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
////	GPIO_Init(GPIOA, &GPIO_InitStructure);
////	/* D5(PB6), VSYNC(PB7) */
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
////	/* D0..1(PC6/7) */
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
////	GPIO_Init(GPIOC, &GPIO_InitStructure);
////	/* D2..4,6..7(PE0/1/4/5/6) */
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
////	GPIO_Init(GPIOE, &GPIO_InitStructure);
////
////
////
////	void DCMI_Config(){
////	  DCMI_InitTypeDef DCMI_InitStructure;
////	  DMA_InitTypeDef  DMA_InitStructure;
////
////	  /*** Configures the DCMI to receive data from MT9D111 ***/
////	  DCMI_DeInit();
////
////	  /* DCMI configuration */
////	  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
////	  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
////	  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
////	  DCMI_InitStructure.DCMI_VSPolarity  = DCMI_VSPolarity_Low;
////	  DCMI_InitStructure.DCMI_HSPolarity  = DCMI_HSPolarity_Low;
////	  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
////	  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
////	  DCMI_Init(&DCMI_InitStructure);
////
////	  /* Enable interrupts from DCMI interface */
////	  /* OPCJONALNIE */
////	  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
////	  DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
////	  DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
////	  DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
////	  DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
////	  /* OPCJONALNIE */
////
////
////	  /*** Configures the DMA2 to transfer data from DCMI DR to LCD RAM ***/
////
////	  /* DMA2 Stream1 DeInit */
////	  DMA_DeInit(DMA2_Stream1);
////	  while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
////
////	  /* DMA2 Stream1 configuration */
////	  DMA_InitStructure.DMA_Channel = DMA_Channel_1;
////	  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS; // Rejestr 32-bitowy
////	  DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;   // Rejestr 16-bitowy
////	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
////	  DMA_InitStructure.DMA_BufferSize = 1;
////	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
////	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
////	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 32-bit
////	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // 16-bit
////	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
////	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
////	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
////	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
////	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
////	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
////	  DMA_Init(DMA2_Stream1, &DMA_InitStructure);
////
////	  /* Enable DMA2 Stream 1 */
////	  DMA_Cmd(DMA2_Stream1, ENABLE);
////	  while (DMA_GetCmdStatus(DMA2_Stream1) != ENABLE);
////	}
////
////
////
////	void DCMI_IRQHandler(void){
////	  // Przerwanie generowane po odebraniu pelnej ramki
////	  if(DCMI_GetITStatus(DCMI_IT_FRAME) == SET){
////	    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
////	  }
////
////	  // Przerwanie generowane przy zmianie stanu sygnalu VSYNC
////	  // z aktywnego na nieaktywny (VPOL = Low)
////	  if(DCMI_GetITStatus(DCMI_IT_VSYNC) == SET){
////	    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);
////
////	    // Czekaj, az DMA zakonczy transfer do pamieci RAM wyswietlacza
////	    while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) == RESET);
////	    LCD_SetCursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
////	    LCD_WriteRAM_Prepare();   // Prepare to write GRAM
////	  }
////
////	  // Przerwanie generowane przy zmianie stanu sygnalu HSYNC
////	  // z aktywnego na nieaktywny (HPOL = Low)
////	  if(DCMI_GetITStatus(DCMI_IT_LINE) == SET){
////	    DCMI_ClearITPendingBit(DCMI_IT_LINE);
////	  }
////
////	  // Przerwanie generowane gdy stare dane (32-bitowe) w rejestrze DCMI_DR
////	  // nie zostaly calkowicie przeslane przed nadejsciem nowych danych
////	  if(DCMI_GetITStatus(DCMI_IT_OVF) == SET){
////	    DCMI_ClearITPendingBit(DCMI_IT_OVF);
////	  }
////	}
////
////	DCMI_Cmd(ENABLE);
////	DCMI_CaptureCmd(ENABLE);
//	  Delay_ms(3000);
//
//	  uint16_t ADC_1 = 0;
//	  uint16_t ADC_2 = 0;
//	  char ADCs1[5] = {0,0,0,0,0};
//	  char ADCs2[5] = {0,0,0,0,0};
//	  Set_Font(&Font16x24);
//
//
//	    // register the chip select/ deselect fucntion
//	    reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
//
//	    // register the chip read/ write fucntion
//	    reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
//
//	    /* wizchip initialize*/
//	    if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1) {
//	        printf("WIZCHIP Initialized fail.\r\n");
//	        while(1);
//	    }
//
//	    do
//	    {
//	        if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1)
//	            printf("Unknown PHY Link stauts.\r\n");
//	    }while(tmp == PHY_LINK_OFF);
//
//	    /* wizchip netconf */
//	    ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
//
//	    gWIZNETINFO.ip[0] = 192;
//	    gWIZNETINFO.ip[1] = 168;
//	    gWIZNETINFO.ip[2] = 1;
//	    gWIZNETINFO.ip[3] = 125;
//
//	    gWIZNETINFO.sn[0] = 255;
//	    gWIZNETINFO.sn[1] = 255;
//	    gWIZNETINFO.sn[2] = 255;
//	    gWIZNETINFO.sn[3] = 0;
//
//	    printf("=== %s NET CONF ===\r\n",(char*)tmpstr);
//	    printf("MAC:%02X.%02X.%02X.%02X.%02X.%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
//	                                                      gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
//	    printf("GAR:%d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
//	    printf("SUB:%d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
//	    printf("SIP:%d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
//
//	    // set network configuration
//	    ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);
//
//	    // get network configuration
//	    ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
//
//	    // Display network configuration
//	    ctlwizchip(CW_GET_ID,(void*)tmpstr);
//	    printf("=== %s NET CONF ===\r\n",(char*)tmpstr);
//	    printf("MAC:%02X.%02X.%02X.%02X.%02X.%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
//	                                                      gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
//	    printf("GAR:%d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
//	    printf("SUB:%d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
//	    printf("SIP:%d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
//
//
//  while(1)
//  {
//  Delay_ms(100);
////  Convert_Pos();
//if(which == 5){
//	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_1);
//	ADC_2 = TM_ADC_Read(ADC1,TM_ADC_Channel_2);
//    Draw_Image(0, 319, 240, 320, img03);
//	Draw_Full_Rect(43, 295 ,61 ,25 , LCD_BLACK);
//	uint16tostr(ADCs1, ADC_1, 10);
//	Display_String(43, 295, ADCs1, LCD_WHITE);
//	Draw_Full_Rect(65, 295 ,85 ,25 , LCD_BLACK);
//	uint16tostr(ADCs2, ADC_2, 10);
//	Display_String(65, 295, ADCs2, LCD_WHITE);
//
//
//	//    ret_pos(&X,&Y);
////    Set_Font(&Font16x24);
////  	uint16tostr(StrNumber1, X, 10);
////  	uint16tostr(StrNumber2, Y, 10);
////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
//#ifdef DEBUG
//	puts(ADCs2);
//#endif
////	puts("\n");
////	fprintf(stderr, ADCs2);
////	fprintf(stderr, "/n");
////	cout << ADCs2;
//    Delay_ms(1000);
////
//
////    Draw_Image(0, 319, 240, 320, img04);
//////    ret_pos(&X,&Y);
//////    Set_Font(&Font16x24);
//////  	uint16tostr(StrNumber1, X, 10);
//////  	uint16tostr(StrNumber2, Y, 10);
//////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
//////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
////    Delay_ms(3000);
//////
////    Draw_Image(0, 319, 240, 320, img05);
//////    ret_pos(&X,&Y);
//////    Set_Font(&Font16x24);
//////  	uint16tostr(StrNumber1, X, 10);
//////  	uint16tostr(StrNumber2, Y, 10);
//////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
//////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
////    Delay_ms(3000);
//////
////    Draw_Image(0, 319, 240, 320, img06);
//////    ret_pos(&X,&Y);
//////    Set_Font(&Font16x24);
//////  	uint16tostr(StrNumber1, X, 10);
//////  	uint16tostr(StrNumber2, Y, 10);
//////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
//////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
////    Delay_ms(3000);
//
////    listen2();
//    printf("Error");
//    Delay_ms(5);
//    while(1);
//  }
//  }
//  //return 0;
//}
//
///*
// * Demonstration project designed for MMIA.
// */
//
//void Demo_MMIA(void)
//{
//  uint16_t Number=0;
//  //int CharCount;
//  char StrNumber[10];
//
//  Clear_Screen(0x0000);
//
//  // Delay_ms(3000);
//
//  Set_Font(&Font16x24);
//  Display_String(14, 295, "Digital Devices", LCD_WHITE);
//  uint16tostr(StrNumber, Number, 10);
//  Display_String(43, 295, StrNumber, LCD_WHITE);
//
//  //CharCount = sprintf(StrNumber,"%d", Number);
//  //Display_String(43, 295, StrNumber, LCD_WHITE);
//
//  Display_String(72, 287, "(c)2013", LCD_WHITE);
//  Set_Font(&Font12x12);
//  Display_String(97, 285, "STM32F4-Discovery", LCD_WHITE);
//
//  Draw_Image(120, 195, 70, 70, img00);
//
//  Set_Font(&Font8x8);
//  Display_String(220, 259, "Compiled by jopl", LCD_WHITE);
//  Display_String(230, 259, "SSD1289 + XPT2046", LCD_WHITE);
//
//  Number = 70;
//  Set_Font(&Font16x24);
//  while (Number != 0)
//  {
//	  Draw_Full_Rect(43, 295 ,61 ,25 , LCD_BLACK);
//	  uint16tostr(StrNumber, Number, 10);
//	  Display_String(43, 295, StrNumber, LCD_WHITE);
//	  //CharCount = sprintf(StrNumber,"%d", Number);
//	  //Display_String(43, 295, StrNumber, LCD_WHITE);
//	    //TIM_OCInitStructure.TIM_Pulse = Number;
//	    //TIM_OC2Init(TIM3, &TIM_OCInitStructure);
//	    //TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//	  Delay_ms(20);
//	  Number--;
//  }
//
//  GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
//
//	Clear_Screen(0x0000);
//	Draw_Image(0, 319, 240, 320, img02);
//	Delay_ms(3000);
//
//  Clear_Screen(0x0000);
//  Set_Font(&Font16x24);
//  Display_String(107, 255, "Random Lines", LCD_WHITE);
//
//  Delay_ms(2000);
//  Clear_Screen(0x0000);
//  Random_Lines();
//  Delay_ms(500);
//
//  Clear_Screen(0x0000);
//  Set_Font(&Font16x24);
//  Display_String(107, 295, "Random Rectangles", LCD_WHITE);
//
//  Delay_ms(2000);
//  Clear_Screen(0x0000);
//  Random_Rect();
//  Delay_ms(500);
//
//  Clear_Screen(0x0000);
//  Set_Font(&Font16x24);
//  Display_String(107, 271, "Random Circles", LCD_WHITE);
//
//  Delay_ms(2000);
//  Clear_Screen(0x0000);
//  Random_Circle();
//  Delay_ms(500);
//
///*  Clear_Screen(0x0000);
//  Set_Font(&Font16x24);
//  Display_String(107, 199, "Images", LCD_WHITE);
//
//  Delay_ms(2000);
//  Draw_Image(0, 319, 240, 320, img02);
//*/
//}
//
///*
// * Draw random lines.
// */
//
//void Random_Lines(void)
//{
//  uint16_t x1,y1,x2,y2;
//  uint32_t i;
//  uint16_t cr;
//
//  for(i=0;i<100;i++)
//  {
//    x1=rand() % 240;  /*TODO: in Eclipse yields rand() error (no reference to _sbrk) */
//    y1=rand() % 320;
//    x2=rand() % 240;
//    y2=rand() % 320;
//
//    cr=rand();
//
//    Draw_Line(x1, y1 ,x2 ,y2 , cr << 3);
//    Delay_ms(100);
//  }
//}
//
///*
// * Draw random rectangles.
// */
//
//void Random_Rect(void)
//{
//  uint16_t x1,y1,x2,y2,z;
//  uint32_t i;
//  uint16_t cr;
//
//  for(i=0;i<25;i++)
//  {
//    x1=rand() % 240;  /*TODO: in Eclipse yields rand() error (no reference to _sbrk) */
//    y1=rand() % 320;
//    x2=rand() % 240;
//    y2=rand() % 320;
//
//    cr=rand();
//
//    z=rand() % 10;
//
//    if (z >= 5) Draw_Rect(x1, y1 ,x2 ,y2 , cr << 3);
//    else Draw_Full_Rect(x1, y1 ,x2 ,y2 , cr << 3);
//    Delay_ms(100);
//  }
//}
//
///*
// * Draw random circles.
// */
//
//void Random_Circle(void)
//{
//  uint16_t x, y, r, z;
//  uint32_t i;
//  uint16_t cr;
//
//  for(i=0;i<25;i++)
//  {
//    x=rand() % 140;  /*TODO: in Eclipse yields rand() error (no reference to _sbrk) */
//    y=rand() % 220;
//    r=(rand() % 50) + 1;
//
//    cr=rand() << 3;
//
//    z=rand() % 10;
//
//    if (z >= 5) Draw_Circle(x+50, y+50, r, cr);
//    else Draw_Full_Circle(x+50, y+50, r, cr);
//    Delay_ms(100);
//  }
//}
//
//
//void EXTI15_10_IRQHandler(void)
//{
//  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
//  {
////	  u16 X, Y;
////	  ret_pos(&X,&Y);
////
////	  if(X>160 && which<5)
////		  which++;
////	  else if(X>160)
////		  which = 1;
////	  else if(X<160 && which>1)
////		  which--;
////	  else
////		  which = 5;
////
////	  switch (which) {
////		case 1:
////			Draw_Image(0, 319, 240, 320, img03);(GPIOD, GPIO_Pin_13);
////			break;
////		case 2:
////			Draw_Image(0, 319, 240, 320, img04);(GPIOD, GPIO_Pin_13);
////			break;
////		case 3:
////			Draw_Image(0, 319, 240, 320, img05);(GPIOD, GPIO_Pin_13);
////			break;
////		case 4:
////			Draw_Image(0, 319, 240, 320, img06);(GPIOD, GPIO_Pin_13);
////			break;
////		default:
////			break;
////	}
////	  delay_ms(500);
//
//
//
//    /* Clear the EXTI line 0 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line12);
//  }
//}
//
//
////void  wizchip_select(void)
////{
////    Eth_cs->Set_low();
////}
////
////void  wizchip_deselect(void)
////{
////	Eth_cs->Set_high();
////}
////
////uint8_t wizchip_read()
////{
////    return spi.write(0x00);
////}
////
////void  wizchip_write(uint8_t wb)
////{
////    spi.write(wb);
////}
//
//int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t size)
//{
//   int32_t ret = 0;
//   ret = recv(sn,buf,size);
//   if(ret != size)
//   {
//      if(ret < 0)
//      {
//         printf("%d:recv() error:%ld\r\n",sn,ret);
//         close(sn);
//         return ret;
//      }
//   }
//   size = ret;
//   ret = send(sn,buf,size);
//   if(ret != size)
//   {
//      if(ret < 0)
//      {
//         printf("%d:send() error:%ld\r\n",sn,ret);
//         close(sn);
//      }
//   }
//   return ret;
//}
//
//int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t size)
//{
//   int32_t  ret = 0;
//   static uint8_t  addr[4] = {0,};
//   static uint16_t port = 0;
//   uint8_t  packinfo;
//
//   if((ret = recvfrom(sn,buf,size, addr,&port,&packinfo)) < 0)
//   {
//      printf("%d:recvfrom error:%ld\r\n",sn,ret);
//      return ret;
//   }
//   if(packinfo & 0x80)
//   {
//      printf("%d:recvfrom %d.%d.%d.%d(%d), size=%ld.\r\n",sn,addr[0],addr[1],addr[2],addr[3],port, ret);
//   }
//   if(packinfo & 0x01)
//   {
//      printf("%d:recvfrom remained packet.\r\n",sn);
//   }
//   else
//   {
//      printf("%d:recvfrom completed.\r\n",sn);
//   }
//   if( (ret = sendto(sn, buf, ret, addr, port)) < 0)
//   {
//      printf("%d:sendto error:%ld\r\n",sn,ret);
//      return ret;
//   }
//   printf("%d:sendto %d.%d.%d.%d(%d), size=%ld\r\n",sn,addr[0],addr[1],addr[2],addr[3],port, ret);
//   return ret;
//}
//
//
//#ifdef  USE_FULL_ASSERT
//
///**
//  * @brief  Reports the name of the source file and the source line number
//  *         where the assert_param error has occurred.
//  * @param  file: pointer to the source file name
//  * @param  line: assert_param error line source number
//  * @retval None
//  */
//void assert_failed(uint8_t* file, uint32_t line)
//{
//  /* User can add his own implementation to report the file name and line number,
//     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//
//  while (1)
//  {}
//}
//#endif
//
///**
//  * @}
//  */
//
///**
//  * @}
//  */
//
///******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

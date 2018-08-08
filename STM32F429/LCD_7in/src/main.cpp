/*********************************************************************************************************
*
* File                : main.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#include <stdio.h>
//#include <string>
#include "GT811.h"
#include "common.h"
#include "STM32F3_my.h"
#include "RA8875_Driver.h"
#include "STM32F4_Class.h"
#include "img/imgg.h"
#include "img/img256.h"
#include "dcmi_ov2640.h"
//#include "camera_api.h"
//#include "img/img03.h"
//String d;

	GPIO_IO LCD_PS(LCD_PS_Po,LCD_PS_Pi,0);
	GPIO_IO LCD_RES(LCD_RES_Po,LCD_RES_Pi,0);

#define Cam_Port1 GPIOC
#define Cam_RST GPIO_Pin_5
#define Cam_PWR GPIO_Pin_4

	GPIO_IO Cam_Rst(Cam_Port1,Cam_RST,0);
	GPIO_IO Cam_Pwr(Cam_Port1,Cam_PWR,0);

	OV2640_IDTypeDef OV2640_Camera_ID;
	__IO uint16_t ADCVal = 0;
	uint8_t buffer[40];
	extern Camera_TypeDef Camera;
	extern ImageFormat_TypeDef ImageFormat;
	extern __IO uint8_t ValueMax;
	extern const uint8_t *ImageForematArray[];

	volatile uint32_t frame = 0;
	volatile uint32_t sec = 0;
	volatile uint32_t tick = 0;
	volatile uint32_t ticks[20];

	void DCMI_IRQHandler(void){
		  // Przerwanie generowane po odebraniu pelnej ramki
		  if(DCMI_GetITStatus(DCMI_IT_FRAME) == SET){
		    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
		  }

		  // Przerwanie generowane przy zmianie stanu sygnalu VSYNC
		  // z aktywnego na nieaktywny (VPOL = Low)
		  if(DCMI_GetITStatus(DCMI_IT_VSYNC) == SET){
		    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);
		    frame++;
//		    printf("Frame: %l\n", frame);
	//	    if((send_flag == 0 && frame_flag == 0) || (frame_flag == 1 && line_l == 120)){
	//	    DMA_Cmd(DMA2_Stream1, ENABLE);
	//	    send_flag++;
	//	    }
		    // Czekaj, az DMA zakonczy transfer do pamieci RAM wyswietlacza
//		    while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) == RESET);
//		      XY_Coordinate(0, 0);
//		      LCD_CmdWrite(LCD_MRWC);
//		    Set_Cursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
//		    Write_GDDRAM_Prepare();   // Prepare to write GRAM
//		  }

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
	}
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{

	RCC_HSEConfig(RCC_HSE_ON);
		while(!RCC_WaitForHSEStartUp())
		{
		}

	//  Init_SysTick();
	  SysTick_Config(180);
	  int key = 0;
	delay_init();
//	USART_Configuration();
	_delay_ms(20);
//	printf("7inch Capacitive Touch LCD TEST\r\n");

	//////////////////////////////////
	LCD_PS.Init();
	LCD_RES.Init();

	LCD_RES.Set_low();
	LCD_PS.Set_low();
	_delay_ms(100);
	LCD_RES.Set_high();
	_delay_ms(200);
	LCD_Initializtion();
	LCD_PrepareDMA();

	Cam_Pwr.Init();
	Cam_Rst.Init();
/////////////////////////////
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
//	TIM1_PWM_Config(1,1,11);
//	  TIM1_PWM_Config(1, 83, 50);
//	  TIM_SetCompare1(TIM1, 5);//(0us / 50us = 0.0)
//	  _delay_s(2);
//	  TIM_SetCompare1(TIM1, 25);
	//	TIM1_PWM_Config(1, 168, 50);

	/*
	 * timer tick freq = tim default/(presc+1) -  90000000/(0+1) = 90Mhz
	 * PWM freq = tim freq/ (period+1) - 90000000/(8 + 1) = 10Mhz
	 */
//	TIM_SetCompare1(TIM1, 1);


	Cam_Pwr.Set_low();
	Cam_Rst.Set_high();

	_delay_ms(100);

	ImageFormat =BMP_QVGA;

	OV2640_HW_Init();
//	TIM1_PWM_Config(1,0,11);
	OV2640_ReadID(&OV2640_Camera_ID);

	if(OV2640_Camera_ID.PIDH  == 0x26)
	  {
		Camera = OV2640_CAMERA;
		sprintf((char*)buffer, "OV2640 Camera ID 0x%x", OV2640_Camera_ID.PIDH);
		ValueMax = 2;
	  }

	 Camera_Config();

	 OV2640_VGAConfig();
//	 int p ;
//	 p =  OV2640_ReadReg(0x48);
//	if(p == 25)
//		sprintf((char*)buffer, "OV2640 Camera ID 0x%x", OV2640_Camera_ID.PIDH);




		/* Write selected arrays to the camera to initialize it and set the
		 * desired output format. */
//		ov2640_write_array(ov2640_init_regs);

//		ov2640_write_array(ov2640_size_change_preamble_regs);
//		ov2640_write_array(ov2640_vga_regs);
//
//		ov2640_write_array(ov2640_format_change_preamble_regs);
//	ov2640_write_array(ov2640_rgb565_be_regs);


	  /* Enable DMA2 stream 1 and DCMI interface then start image capture */


	  /* Insert 100ms delay: wait 100ms */






	  DCMI_Cmd(ENABLE);
	  _delay_ms(100);
	  DCMI_CaptureCmd(ENABLE);
	  DMA_Cmd(DMA2_Stream1, ENABLE);
	  if(ImageFormat == BMP_QQVGA)
	    {
	      /* LCD Display window */
	      Active_Window(0, 159, 0, 119);
	      XY_Coordinate(0, 0);
	      LCD_CmdWrite(LCD_MRWC);
//	      LCD_WriteReg(LCD_REG_3, 0x1038);
//	      LCD_WriteRAM_Prepare();
	    }
	    else if(ImageFormat == BMP_QVGA)
	    {
	      /* LCD Display window */
//	      Active_Window(0, 319, 0, 239);
	      Active_Window(0, 639, 0, 479);
	      XY_Coordinate(0, 0);
	      LCD_CmdWrite(LCD_MRWC);
	    }

	  TIM_Config(TIM2_BASE,9000,10000);
	  EXTI_Config(GPIOE,GPIO_Pin_2,EXTI_Trigger_Falling);

//	  TIM1_PWM_Config(1, 83, 50);
//	  TIM_SetCompare1(TIM1, 50);//(0us / 50us = 0.0)
//	  _delay_s(2);
//	  TIM_SetCompare1(TIM1, 25);
//	  _delay_s(2);
//	  TIM_SetCompare1(TIM1, 1);


//	  _delay_s(5);
//	  printf("0x00\r\n");
//	  OV2640_BrightnessConfig(0x00);
//
//	  _delay_s(5);
//	  printf("0x10\r\n");
//	  OV2640_BrightnessConfig(0x10);
//
//	  _delay_s(5);
//	  printf("0x20\r\n");
//	  OV2640_BrightnessConfig(0x20);
//
//	  _delay_s(5);
//	  printf("0x30\r\n");
//	  OV2640_BrightnessConfig(0x30);
//
//	  _delay_s(5);
//	  printf("Brightness: max\r\n");
//	  OV2640_BrightnessConfig(0x40);

//	  _delay_s(5);
//	  printf("0x00\r\n");
//	  OV2640_BandWConfig(0x00);
//
//	  _delay_s(5);
//	  printf("0x58\r\n");
//	  OV2640_BandWConfig(0x58);
//
//	  _delay_s(5);
//	  printf("0x40\r\n");
//	  OV2640_BandWConfig(0x40);
//
//	  _delay_s(5);
//	  printf("0x18\r\n");
//	  OV2640_BandWConfig(0x18);

//	  _delay_s(5);
//	  printf("0x40,0xa6\r\n");
//	  OV2640_ColorEffectsConfig(0x40,0xa6);
//
//	  _delay_s(5);
//	  printf("0xa0,0x40\r\n");
//	  OV2640_ColorEffectsConfig(0xa0,0x40);
//
//	  _delay_s(5);
//	  printf("0x40,0x40\r\n");
//	  OV2640_ColorEffectsConfig(0x40,0x40);
//
//	  _delay_s(5);
//	  printf("0x40,0xc0\r\n");
//	  OV2640_ColorEffectsConfig(0x40,0xc0);

//	  _delay_s(5);
//	  printf("0x18,0x34\r\n");
//	  OV2640_ContrastConfig(0x18,0x34);
//
//	  _delay_s(5);
//	  printf("0x1c,0x2a\r\n");
//	  OV2640_ContrastConfig(0x1c,0x2a);
//
//	  _delay_s(5);
//	  printf("0x20,0x20\r\n");
//	  OV2640_ContrastConfig(0x20,0x20);
//
//	  _delay_s(5);
//	  printf("0x24,0x16\r\n");
//	  OV2640_ContrastConfig(0x24,0x16);
//
//	  _delay_s(5);
//	  printf("0x28,0x0c\r\n");
	  ///////////////////////////////////////////////////////////
	  OV2640_ContrastConfig(0x28,0x0c);
///////////////////////////////////////////////////////
//	  	  _delay_s(5);
//	  	  for(int k =0;k<255;k++){
////	  	  printf("0x40,0xa6\r\n");
//	  	  OV2640_ColorEffectsConfig(k,0x00);
//	  	_delay_ms(15);
//	  	  }
//	  	_delay_s(5);
//	  	for(int k =0;k<255;k++){
//	  		for(int l =0;l<255;l++){
//	  	//	  	  printf("0x40,0xa6\r\n");
//	  		  	  OV2640_ColorEffectsConfig(k,l);
//	  		  	_delay_ms(100);
//	  		}
//	  	}
//	  	_delay_s(5);
//	  	for(int k =0;k<255;k++){
//	  	//	  	  printf("0x40,0xa6\r\n");
//	  		  	  OV2640_ColorEffectsConfig(k,k);
//	  		  	_delay_ms(15);
//	  		  		  	  }
	  	//	  	  _delay_s(5);
//	  	  printf("0xa0,0x40\r\n");
//	  	  OV2640_ColorEffectsConfig(0x10,0x10);
//
//	  	  _delay_s(5);
//	  	  printf("0x40,0x40\r\n");
//	  	  OV2640_ColorEffectsConfig(0x20,0x20);
//
//	  	  _delay_s(5);
//	  	  printf("0x40,0xc0\r\n");
//	  	  OV2640_ColorEffectsConfig(0x30,0x30);

//	LCD_DrawSquare(0,0,10,479,Blue,1);
//	LCD_DrawSquare(0,469,899,479,Blue,1);
//	LCD_DrawSquare(0,469,8,30,Blue,1);
//	LCD_DrawSquare(789,0,899,479,Blue,1);
//
//	LCD_DrawSquare(0,0,210,30,Blue,1);
//	LCD_DrawSquare(210,0,250,30,Blue,1);
//	LCD_DrawSquare(648,0,799,30,Blue,1);
//	_delay_s(1);
//	LCD_drawVU((uint16_t*) image16);
//	LCD_draw1();
//	LCD_draw2();
//	LCD_draw3();
	printf("Image\r\n");
//	_delay_s(5);
//	Display_OFF();
//	_delay_s(2);
//	Display_ON();
//	_delay_s(2);
//	PWM1_duty_cycle(250);
//	_delay_s(2);
//	PWM1_duty_cycle(150);
//	_delay_s(2);
//	PWM1_duty_cycle(50);
//	_delay_s(2);
//	PWM1_duty_cycle(0);
//	LcdPrint16bitBmp(img03,0,0,320,240);
//	LcdClear(Yellow);
	
//	Two_Layers();
//	Lighten_Overlay_Mode();

//	_delay_s(5);
//	printf("65k , 8bit MPU\r\n");
//	Color_65K();
//	MPU_8bit_Interface();
//	LCD_drawVU();

//	_delay_s(5);
//	printf("65k , 16bit MPU\r\n");
//	Color_65K();
//	MPU_16bit_Interface();
//	LCD_drawVU((uint16_t*) image16);

//	_delay_s(5);
//	printf("256 , 8bit MPU\r\n");
//	Color_256();
//	MPU_8bit_Interface();
//	LCD_drawVU();
////////////////////////////////////////////////////////////////
//	_delay_s(5);

//	BackgroundColor_TransparentMode(0xFF,0xFF,0xFF);
//	Two_Layers();
//	Write_To_Bank1();
//	LcdClear(White);
//	Write_To_Bank2();
//	LcdClear(White);
//
//
//	printf("256 , 16bit MPU\r\n");
//	Color_256();
//	MPU_16bit_Interface();
//	LCD_drawVU((uint16_t*) img256);
//
//	Write_To_Bank1();
//	LCD_Internal_Font_ROM(100,30,Yellow,Blue,1,1,4,0);
//	ISO8859_2();
////	LCD_External_Font_ROM(200,200,Red,Blue,0,0,1,0);
//	char a[] = "Witcher 3: ¹êæó¿Ÿ³œñ";
////	a[11] -= 8;
////	a[15] += 29;
////	a[17] += 26;
//	Show_String(a,1);
//	Graphic_Mode();
////	_delay_s(3);
//
//
//	 Layer1_Visible();
//	 _delay_s(2);
//	 Layer2_Visible();
//	 _delay_s(2);
//	 Transparent_Mode();
//	 _delay_s(2);
//
//
//		Scroll_Window(0,799,0,479);
//		Layer1_scroll();
//		while(1)
//		for(int i = 799;i>=0;i--){
//			Scroll_Offset(i,0);
//			_delay_ms(5);
//		}
//		Scroll_Offset(0,0);
//
////	 Scroll_Window(0,799,0,479);
////	 Buffer_scroll();
////	while(1)
////		for(int i = 1599;i>=0;i--){
//// 			Scroll_Offset(i,0);
//// 			_delay_ms(2);
//// 		}
////		Scroll_Offset(0,0);

	 ///////////////////////////////////////////////////////////////
//	while(1){
//		switch (key) {
//			case 1:
//				LCD_drawVU();
//				key = 0;
//				break;
//			case 2:
//				_delay_s(5);
//				printf("65k , 8bit MPU\r\n");
//				Color_65K();
//				MPU_8bit_Interface();
//				LCD_drawVU();
//				key = 0;
//				break;
//			case 3:
//				_delay_s(5);
//				printf("65k , 16bit MPU\r\n");
//				Color_65K();
//				MPU_16bit_Interface();
//				LCD_drawVU();
//				key = 0;
//				break;
//			case 4:
//				_delay_s(5);
//				printf("256 , 8bit MPU\r\n");
//				Color_256();
//				MPU_8bit_Interface();
//				LCD_drawVU();
//				key = 0;
//				break;
//			case 5:
//				_delay_s(5);
//				printf("256 , 16bit MPU\r\n");
//				Color_256();
//				MPU_16bit_Interface();
//				LCD_drawVU();
//				key = 0;
//				break;
//			default:
//				break;
//		}
//	}

//	Scroll_Window(0,799,0,479);
//	Layer1_scroll();
//	for(int i = 799;i>=0;i--){
//		Scroll_Offset(i,0);
//		_delay_ms(15);
//	}
//	Scroll_Offset(0,0);
//	for(int i = 479;i>=0;i--){
//		Scroll_Offset(0,i);
//		_delay_ms(15);
//	}
//	Scroll_Offset(0,0);
//	for(int i = 479;i>=0;i--){
//		Scroll_Offset(i,i);
//		_delay_ms(15);
//	}
//	Scroll_Offset(0,0);



//	printf("Font_code_UNIJIS\r\n");
//	LCD_drawVU((uint16_t*) img256);
//	Font_code_UNIJIS();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);
//
//	printf("Font_code_JIS0208\r\n");
//	LCD_drawVU((uint16_t*) img256);
//	Font_code_JIS0208();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);
//
//	printf("Font_code_LATIN\r\n");
//	LCD_drawVU((uint16_t*) img256);
//	Font_code_LATIN();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);
//
//	printf("Font_Standard\r\n");
//	LCD_drawVU((uint16_t*) img256);
//	Font_Standard();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);
//
//	printf("Font_Arial\r\n");
//	LCD_drawVU((uint16_t*) img256);
//	Font_Arial();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);
//
//	printf("Font_Roman\r\n");
//	LCD_drawVU((uint16_t*) img256);
//	Font_Roman();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);


//	printf("Font_Bold\r\n");
//	LCD_drawVU((uint16_t*) img256);
////	CGRAM_Font();
//	Font_code_ASCII();
//	Font_Bold();
////	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);
//
//	printf("Font_Bold\r\n");
//	LCD_drawVU((uint16_t*) img256);
////	CGRAM_Font();
//	Font_code_ASCII();
//	Font_Bold();
//	LCD_Internal_Font_ROM(200,200,Red,Blue,1,1,4,0);
//	Show_String("Witcher 3: ¹êó¿Ÿ³œñ",1);
//	Graphic_Mode();
//	_delay_s(3);

	////////////////////

	//	printf("Capacitive touch screen test\r\n");

//	CT_TEST();
	while (1);
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//        sec++;
//        printf("Fps: %lu\n", frame);
//        frame = 0;
//        printf("Clock: %lu\n", tick);
//        if(sec<20)
//        ticks[sec] = tick;
//        else
//        	tick--;
//        tick = 0;
    }
}

void EXTI2_IRQHandler()
{
	  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	  {

//		  if(tick>2700000)
//			  tick--;
//		  tick++;

//		  delay_ms(500);



	    /* Clear the EXTI line 0 pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line2);
	  }

}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


/**
 *
 */
/* Includes *******************************************************************/
#include "main.h"
//#include "img/img00.h"
#include "img/img01.h"
//#include "img/img02.h"
#include "img/img03.h"
#include "img/img04.h"
#include "img/img05.h"
#include "img/img06.h"
#include "OV7670_I2C.h"
#include "STM32F3_my.h"
#include "tm_stm32f4_adc.h"
#include "Ethernet/socket.h"
//extern unsigned char bmp1[];

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 300;
uint16_t CCR2_Val = 100;

volatile int which = 5;
#define DCMI_DR_ADDRESS   0x28
#define FSMC_LCD_ADDRESS  LCD_BASE
int main (void)
{
  /* Initialization */

  Init_SysTick();
  Init_GPIO();
  Init_FSMC();
  Init_LCD();
  pwm_init();
  touch_init();
  TM_ADC_Init(ADC1,TM_ADC_Channel_1);
  TM_ADC_Init(ADC1,TM_ADC_Channel_2);

  /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_stm32f4xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_stm32f4xx.c file
       */

  /* Demo */
  TIM4->CCR1 = CCR1_Val;
  //TIM4->CCR2 = CCR2_Val;

  Clear_Screen(0x0000);
//	Demo_MMIA();
	u16 X, Y;
	char StrNumber1[10];
	char StrNumber2[10];
	u16 data = 0;
	uint32_t Number;

	I2C_Config(SCCB_Camera,I2C_Ack_Enable);
//	/* Configuration for QCIF format */
//
////		// COM3 register: Enable format scaling
////		OV7670_read(0x0C, &data);
////		data = data | 0b00001000;
////		OV7670_write(0x0C, &data);
////
////		// COM7 register: Select QCIF format
////		OV7670_read(0x0C, &data);
////		data = (data & 0b11000111) | 0b00001000;
////	  uint16tostr(StrNumber1, data, 10);
////	  Display_String(43, 100, StrNumber1, LCD_WHITE);
////		OV7670_write(0x12, &data);
////	  data = 0;
////	  uint16tostr(StrNumber1, data, 10);
////	  Display_String(43, 150, StrNumber1, LCD_WHITE);
////		OV7670_read(0x0C, &data);
////	  	uint16tostr(StrNumber1, data, 10);
////	  Display_String(43, 200, StrNumber1, LCD_WHITE);
//
//	GPIO_PinOut(GPIOA,GPIO_Pin_8);
//	GPIO_PinOut(GPIOA,GPIO_Pin_15);
//
//	GPIO_PinRes(GPIOA,GPIO_Pin_8);
//	GPIO_PinRes(GPIOA,GPIO_Pin_15);
//
//	  EXTI_InitTypeDef   EXTI_InitStructure;
//
//	  NVIC_InitTypeDef   NVIC_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
//	RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
//
//	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	/*** Connect DCMI pins to AF13 ***/
//	/* HSYNC(PA4), PIXCLK(PA6) */
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);
//	/* D5(PB6), VSYNC(PB7) */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
//	/* D0..1(PC6/7)  PA9 - D0*/
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);
//	/* D2..4,6..7(PE0/1/4/5/6) */
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);
//
//	GPIO_InitTypeDef   GPIO_InitStructure;
//	/*** DCMI GPIOs configuration ***/
//	/* HSYNC(PA4), PIXCLK(PA6) */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	/* D5(PB6), VSYNC(PB7) */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	/* D0..1(PC6/7) */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	/* D2..4,6..7(PE0/1/4/5/6) */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//
//
//
//	void DCMI_Config(){
//	  DCMI_InitTypeDef DCMI_InitStructure;
//	  DMA_InitTypeDef  DMA_InitStructure;
//
//	  /*** Configures the DCMI to receive data from MT9D111 ***/
//	  DCMI_DeInit();
//
//	  /* DCMI configuration */
//	  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
//	  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
//	  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
//	  DCMI_InitStructure.DCMI_VSPolarity  = DCMI_VSPolarity_Low;
//	  DCMI_InitStructure.DCMI_HSPolarity  = DCMI_HSPolarity_Low;
//	  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
//	  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
//	  DCMI_Init(&DCMI_InitStructure);
//
//	  /* Enable interrupts from DCMI interface */
//	  /* OPCJONALNIE */
//	  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
//	  DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
//	  DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
//	  DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
//	  DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
//	  /* OPCJONALNIE */
//
//
//	  /*** Configures the DMA2 to transfer data from DCMI DR to LCD RAM ***/
//
//	  /* DMA2 Stream1 DeInit */
//	  DMA_DeInit(DMA2_Stream1);
//	  while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
//
//	  /* DMA2 Stream1 configuration */
//	  DMA_InitStructure.DMA_Channel = DMA_Channel_1;
//	  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS; // Rejestr 32-bitowy
//	  DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;   // Rejestr 16-bitowy
//	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
//	  DMA_InitStructure.DMA_BufferSize = 1;
//	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
//	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 32-bit
//	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // 16-bit
//	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
//	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//	  DMA_Init(DMA2_Stream1, &DMA_InitStructure);
//
//	  /* Enable DMA2 Stream 1 */
//	  DMA_Cmd(DMA2_Stream1, ENABLE);
//	  while (DMA_GetCmdStatus(DMA2_Stream1) != ENABLE);
//	}
//
//
//
//	void DCMI_IRQHandler(void){
//	  // Przerwanie generowane po odebraniu pelnej ramki
//	  if(DCMI_GetITStatus(DCMI_IT_FRAME) == SET){
//	    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
//	  }
//
//	  // Przerwanie generowane przy zmianie stanu sygnalu VSYNC
//	  // z aktywnego na nieaktywny (VPOL = Low)
//	  if(DCMI_GetITStatus(DCMI_IT_VSYNC) == SET){
//	    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);
//
//	    // Czekaj, az DMA zakonczy transfer do pamieci RAM wyswietlacza
//	    while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) == RESET);
//	    LCD_SetCursor(0, 319);    // Ustaw w pozycji lewego gornego rogu
//	    LCD_WriteRAM_Prepare();   // Prepare to write GRAM
//	  }
//
//	  // Przerwanie generowane przy zmianie stanu sygnalu HSYNC
//	  // z aktywnego na nieaktywny (HPOL = Low)
//	  if(DCMI_GetITStatus(DCMI_IT_LINE) == SET){
//	    DCMI_ClearITPendingBit(DCMI_IT_LINE);
//	  }
//
//	  // Przerwanie generowane gdy stare dane (32-bitowe) w rejestrze DCMI_DR
//	  // nie zostaly calkowicie przeslane przed nadejsciem nowych danych
//	  if(DCMI_GetITStatus(DCMI_IT_OVF) == SET){
//	    DCMI_ClearITPendingBit(DCMI_IT_OVF);
//	  }
//	}
//
//	DCMI_Cmd(ENABLE);
//	DCMI_CaptureCmd(ENABLE);
	  Delay_ms(3000);

	  uint16_t ADC_1 = 0;
	  uint16_t ADC_2 = 0;
	  char ADCs1[5] = {0,0,0,0,0};
	  char ADCs2[5] = {0,0,0,0,0};
	  Set_Font(&Font16x24);
  while(1)
  {
  Delay_ms(100);
//  Convert_Pos();
if(which == 5){
	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_1);
	ADC_2 = TM_ADC_Read(ADC1,TM_ADC_Channel_2);
    Draw_Image(0, 319, 240, 320, img03);
	Draw_Full_Rect(43, 295 ,61 ,25 , LCD_BLACK);
	uint16tostr(ADCs1, ADC_1, 10);
	Display_String(43, 295, ADCs1, LCD_WHITE);
	Draw_Full_Rect(65, 295 ,85 ,25 , LCD_BLACK);
	uint16tostr(ADCs2, ADC_2, 10);
	Display_String(65, 295, ADCs2, LCD_WHITE);
	//    ret_pos(&X,&Y);
//    Set_Font(&Font16x24);
//  	uint16tostr(StrNumber1, X, 10);
//  	uint16tostr(StrNumber2, Y, 10);
//  	Display_String(43, 200, StrNumber1, LCD_WHITE);
//  	Display_String(90, 250, StrNumber2, LCD_WHITE);
    Delay_ms(1000);
//

//    Draw_Image(0, 319, 240, 320, img04);
////    ret_pos(&X,&Y);
////    Set_Font(&Font16x24);
////  	uint16tostr(StrNumber1, X, 10);
////  	uint16tostr(StrNumber2, Y, 10);
////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
//    Delay_ms(3000);
////
//    Draw_Image(0, 319, 240, 320, img05);
////    ret_pos(&X,&Y);
////    Set_Font(&Font16x24);
////  	uint16tostr(StrNumber1, X, 10);
////  	uint16tostr(StrNumber2, Y, 10);
////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
//    Delay_ms(3000);
////
//    Draw_Image(0, 319, 240, 320, img06);
////    ret_pos(&X,&Y);
////    Set_Font(&Font16x24);
////  	uint16tostr(StrNumber1, X, 10);
////  	uint16tostr(StrNumber2, Y, 10);
////  	Display_String(43, 200, StrNumber1, LCD_WHITE);
////  	Display_String(90, 250, StrNumber2, LCD_WHITE);
//    Delay_ms(3000);
}
  }

  //return 0;
}

/*
 * Demonstration project designed for MMIA.
 */

void Demo_MMIA(void)
{
  uint16_t Number=0;
  //int CharCount;
  char StrNumber[10];

  Clear_Screen(0x0000);

  // Delay_ms(3000);

  Set_Font(&Font16x24);
  Display_String(14, 295, "Digital Devices", LCD_WHITE);
  uint16tostr(StrNumber, Number, 10);
  Display_String(43, 295, StrNumber, LCD_WHITE);

  //CharCount = sprintf(StrNumber,"%d", Number);
  //Display_String(43, 295, StrNumber, LCD_WHITE);

  Display_String(72, 287, "(c)2013", LCD_WHITE);
  Set_Font(&Font12x12);
  Display_String(97, 285, "STM32F4-Discovery", LCD_WHITE);

  Draw_Image(120, 195, 70, 70, img00);

  Set_Font(&Font8x8);
  Display_String(220, 259, "Compiled by jopl", LCD_WHITE);
  Display_String(230, 259, "SSD1289 + XPT2046", LCD_WHITE);

  Number = 70;
  Set_Font(&Font16x24);
  while (Number != 0)
  {
	  Draw_Full_Rect(43, 295 ,61 ,25 , LCD_BLACK);
	  uint16tostr(StrNumber, Number, 10);
	  Display_String(43, 295, StrNumber, LCD_WHITE);
	  //CharCount = sprintf(StrNumber,"%d", Number);
	  //Display_String(43, 295, StrNumber, LCD_WHITE);
	    //TIM_OCInitStructure.TIM_Pulse = Number;
	    //TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	    //TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	  Delay_ms(20);
	  Number--;
  }

  GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	
	Clear_Screen(0x0000);
	Draw_Image(0, 319, 240, 320, img02);
	Delay_ms(3000);

  Clear_Screen(0x0000);
  Set_Font(&Font16x24);
  Display_String(107, 255, "Random Lines", LCD_WHITE);

  Delay_ms(2000);
  Clear_Screen(0x0000);
  Random_Lines();
  Delay_ms(500);

  Clear_Screen(0x0000);
  Set_Font(&Font16x24);
  Display_String(107, 295, "Random Rectangles", LCD_WHITE);

  Delay_ms(2000);
  Clear_Screen(0x0000);
  Random_Rect();
  Delay_ms(500);

  Clear_Screen(0x0000);
  Set_Font(&Font16x24);
  Display_String(107, 271, "Random Circles", LCD_WHITE);

  Delay_ms(2000);
  Clear_Screen(0x0000);
  Random_Circle();
  Delay_ms(500);

/*  Clear_Screen(0x0000);
  Set_Font(&Font16x24);
  Display_String(107, 199, "Images", LCD_WHITE);

  Delay_ms(2000);
  Draw_Image(0, 319, 240, 320, img02);
*/
}

/*
 * Draw random lines.
 */

void Random_Lines(void)
{
  uint16_t x1,y1,x2,y2;
  uint32_t i;
  uint16_t cr;

  for(i=0;i<100;i++)
  {
    x1=rand() % 240;  /*TODO: in Eclipse yields rand() error (no reference to _sbrk) */
    y1=rand() % 320;
    x2=rand() % 240;
    y2=rand() % 320;

    cr=rand();

    Draw_Line(x1, y1 ,x2 ,y2 , cr << 3);
    Delay_ms(100);
  }
}

/*
 * Draw random rectangles.
 */

void Random_Rect(void)
{
  uint16_t x1,y1,x2,y2,z;
  uint32_t i;
  uint16_t cr;

  for(i=0;i<25;i++)
  {
    x1=rand() % 240;  /*TODO: in Eclipse yields rand() error (no reference to _sbrk) */
    y1=rand() % 320;
    x2=rand() % 240;
    y2=rand() % 320;

    cr=rand();

    z=rand() % 10;

    if (z >= 5) Draw_Rect(x1, y1 ,x2 ,y2 , cr << 3);
    else Draw_Full_Rect(x1, y1 ,x2 ,y2 , cr << 3);
    Delay_ms(100);
  }
}

/*
 * Draw random circles.
 */

void Random_Circle(void)
{
  uint16_t x, y, r, z;
  uint32_t i;
  uint16_t cr;

  for(i=0;i<25;i++)
  {
    x=rand() % 140;  /*TODO: in Eclipse yields rand() error (no reference to _sbrk) */
    y=rand() % 220;
    r=(rand() % 50) + 1;

    cr=rand() << 3;

    z=rand() % 10;

    if (z >= 5) Draw_Circle(x+50, y+50, r, cr);
    else Draw_Full_Circle(x+50, y+50, r, cr);
    Delay_ms(100);
  }
}


void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {
	  u16 X, Y;
	  ret_pos(&X,&Y);

	  if(X>160 && which<5)
		  which++;
	  else if(X>160)
		  which = 1;
	  else if(X<160 && which>1)
		  which--;
	  else
		  which = 5;

	  switch (which) {
		case 1:
			Draw_Image(0, 319, 240, 320, img03);(GPIOD, GPIO_Pin_13);
			break;
		case 2:
			Draw_Image(0, 319, 240, 320, img04);(GPIOD, GPIO_Pin_13);
			break;
		case 3:
			Draw_Image(0, 319, 240, 320, img05);(GPIOD, GPIO_Pin_13);
			break;
		case 4:
			Draw_Image(0, 319, 240, 320, img06);(GPIOD, GPIO_Pin_13);
			break;
		default:
			break;
	}
	  delay_ms(500);



    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

#ifndef _RA8875_DERIVER_H
#define _RA8875_DERIVER_H

#include "stm32f4xx.h"
#include "delay.h"
#include "LCD_Interface.h"
#include "STM32F4_Class.h"
#include "vu.h"
#include "lcd_ra8875_registers.h"
//#include "img/img00.h"
//#include "img/img01.h"
//#include "img/img06.h"
//#include "img/img03.h"
//#include "img/imgg.h"
//#include "img/img256.h"

#ifdef __cplusplus
extern "C"{
#endif

#define LCD_PS_Pi GPIO_Pin_3
#define LCD_PS_Po GPIOD

#define LCD_RES_Pi GPIO_Pin_13
#define LCD_RES_Po GPIOC



//#define Color256
#define Color65k

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define   CYAN   GREEN|BLUE
#define   PURPLE RED|BLUE


#define color_black   0x0000
#define color_white   0xffff
#define color_red     0xf800
#define color_green   0x07e0
#define color_blue    0x001f
#define color_yellow  color_red|color_green
#define color_cyan    color_green|color_blue
#define color_purple  color_red|color_blue

#define color_grayscale1    2113
#define color_grayscale2    2113*2
#define color_grayscale3    2113*3
#define color_grayscale4    2113*4
#define color_grayscale5    2113*5
#define color_grayscale6    2113*6
#define color_grayscale7    2113*7
#define color_grayscale8    2113*8
#define color_grayscale9    2113*9
#define color_grayscale10   2113*10
#define color_grayscale11   2113*11
#define color_grayscale12   2113*12
#define color_grayscale13   2113*13
#define color_grayscale14   2113*14
#define color_grayscale15   2113*15
#define color_grayscale16   2113*16
#define color_grayscale17   2113*17
#define color_grayscale18   2113*18
#define color_grayscale19   2113*19
#define color_grayscale20   2113*20
#define color_grayscale21   2113*21
#define color_grayscale22   2113*22
#define color_grayscale23   2113*23
#define color_grayscale24   2113*24
#define color_grayscale25   2113*25
#define color_grayscale26   2113*26
#define color_grayscale27   2113*27
#define color_grayscale28   2113*28
#define color_grayscale29   2113*29
#define color_grayscale30   2113*30
	
#define	cSetD0		 0x01
#define	cSetD1		 0x02
#define	cSetD2		 0x04
#define	cSetD3		 0x08
#define	cSetD4		 0x10
#define	cSetD5		 0x20
#define	cSetD6		 0x40
#define	cSetD7		 0x80
	                         
#define	cClrD0		 0xfe
#define	cClrD1		 0xfd
#define	cClrD2		 0xfb
#define	cClrD3		 0xf7
#define	cClrD4		 0xef
#define	cClrD5		 0xdf
#define	cClrD6		 0xbf
#define	cClrD7		 0x7f
	
#define cClrD1D0         0xfc
#define cClrD1SetD0	 0x01
#define cSetD1ClrD0	 0x02
#define cSetD1D0	 0x03
#define cClrD3D2         0xf3
#define cClrD3SetD2      0x04
#define cSetD3ClrD2      0x08
#define cSetD3D2	 0x0c
	
#define cClrD2D1D0	 0xf8
#define cClrD2D1SetD0	 0x01
#define cClrD2SetD1ClrD0 0x02
#define cClrD2SetD1D0	 0x03
#define cSetD2ClrD1D0	 0x04
#define cSetD2ClrD1SetD0 0x05
	
#define cClrD6D5D4	 0x8f
#define cClrD6D5SetD4    0x10
#define cClrD6SetD5ClrD4 0x20
#define cClrD6SetD5D4	 0x30
#define cSetD6ClrD5D4	 0x40
#define cSetD6ClrD5SetD4 0x50
#define cSetD6D5ClrD4	 0x60
#define cSetD6D5D4	 0x70


// DMA configuracion

#define DMA_STREAM               DMA2_Stream7
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2
#define DMA_STREAM_IRQ           DMA2_Stream7_IRQn
#define DMA_STREAM_STATUS_BIT	DMA_IT_TCIF7

#define LCD_RAM       (*((volatile unsigned short *) 0x60000000))
#define LCD_REG (*((volatile unsigned short *) 0x60020000))

/***********************************************************************/
//STATUS 
void Chk_Busy(void);
void Chk_Busy_BTE(void);
void Chk_Busy_DIR_Access(void);

//REG[BFh]
void Chk_DMA_Busy(void);

//REG[01h]
void Display_ON(void);
void Display_OFF(void);
void Normal_Mode_exitSleep(void);
void Sleep_Mode(void);
void Software_Reset(void);

//REG[04h]
void PCLK_inversion(void);
void PCLK_non_inversion(void);
void PCLK_width(uint8_t setx);

//REG[05h] 
void Serial_ROM_select0(void);//bit7
void Serial_ROM_select1(void);//bit7

void Serial_ROM_Address_set_24bit(void);//bit6
void Serial_ROM_Address_set_32bit(void);//bit6

void Select_Serial_Waveform_mode0(void);//bit5
void Select_Serial_Waveform_mode3(void);//bit5

void SERIAL_ROM_Read_Cycle_4bus(void); //bit4~3
void SERIAL_ROM_Read_Cycle_5bus(void); //bit4~3
void SERIAL_ROM_Read_Cycle_6bus(void); //bit4~3

void SERIAL_ROM_Font_mode(void); //bit2
void SERIAL_ROM_DMA_mode(void);  //bit2

void SERIAL_ROM_Signal_mode(void); //bit1~0
void SERIAL_ROM_Dual_mode0(void);  //bit1~0
void SERIAL_ROM_Dual_mode1(void);  //bit1~0

  
void SROM_CLK_DIV(uint8_t CLK_DIV);

//REG[10h]
void Color_256(void);
void Color_65K(void);
void MPU_8bit_Interface(void);
void MPU_16bit_Interface(void);


//REG[12h] 
uint8_t GPI_data(void);
//REG[13h] 
void GPO_data(uint8_t setx);

//REG[20h]
void One_Layer(void);
void Two_Layers(void);
void HDIR_SEG0_SEGn(void);
void HDIR_SEGn_SEG0(void);
void VDIR_COM0_COMn(void);
void VDIR_COMn_COM0(void);

//REG[21h] 
void CGROM_Font(void);
void CGRAM_Font(void);
void Internal_CGROM(void);
void External_CGROM(void);
void ISO8859_1(void);
void ISO8859_2(void);
void ISO8859_3(void);
void ISO8859_4(void);

//REG[22h]
void No_FullAlignment(void);
void FullAlignment(void);
void Font_with_BackgroundColor(void);
void Font_with_BackgroundTransparency(void);

void Horizontal_FontEnlarge_x1(void);
void Horizontal_FontEnlarge_x2(void);
void Horizontal_FontEnlarge_x3(void);
void Horizontal_FontEnlarge_x4(void);
void Vertical_FontEnlarge_x1(void);
void Vertical_FontEnlarge_x2(void);
void Vertical_FontEnlarge_x3(void);
void Vertical_FontEnlarge_x4(void);

//REG[23h]	
void CGRAM_Select_Number(uint8_t number);

//REG[24h]REG[25h]REG[26h]REG[27h]	
void Scroll_Offset(uint16_t X,uint16_t Y);

//REG[29h]
void Line_distance(uint8_t setx);

//REG[2Ah]~REG[2Dh]
void Font_Coordinate(uint16_t X,uint16_t Y);

//REG[2Eh]
void Font_size_16x16_8x16(void);
void Font_size_24x24_12x24(void);
void Font_size_32x32_16x32(void);
void Font_spacing_set(uint8_t setx); //uint8_t[5:0]

//REG[2Fh]
void GT_serial_ROM_select_GT21L16T1W(void);
void GT_serial_ROM_select_GT23L16U2W(void);
void GT_serial_ROM_select_GT23L24T3Y(void);
void GT_serial_ROM_select_GT23L24M1Z(void);
void GT_serial_ROM_select_GT23L32S4W(void);
void Font_code_GB2312(void);
void Font_code_GB12345(void);
void Font_code_BIG5(void);
void Font_code_UNICODE(void);
void Font_code_ASCII(void);
void Font_code_UNIJIS(void);
void Font_code_JIS0208(void);
void Font_code_LATIN(void);
void Font_Standard(void);
void Font_Arial(void);
void Font_Roman(void);
void Font_Bold(void); //for ASCII

//REG[30h]~REG[37h]
void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB);

//REG[38h]~REG[3Fh]
void Scroll_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB);
//REG[40h]
void Graphic_Mode(void);
void Text_Mode(void);
void Text_Cursor_Disable(void);
void Text_Cursor_Enable(void);
void Text_Cursor_Blink_Disable(void);
void Text_Cursor_Blink_Enable(void);
void Memory_Write_LeftRight_TopDown(void);
void Memory_Write_RightLeft_TopDown(void);
void Memory_Write_DownTop_LeftRight(void);
void Memory_Write_TopDown_LeftRight(void);
void MemoryWrite_Cursor_autoIncrease(void);
void MemoryWrite_Cursor_NoautoIncrease(void);
void MemoryRead_Cursor_autoIncrease(void);
void MemoryRead_Cursor_NoautoIncrease(void);

//REG[41h]
void No_Graphic_Cursor(void);
void Graphic_Cursor(void);
void Graphic_Cursor_Set1(void);
void Graphic_Cursor_Set2(void);
void Graphic_Cursor_Set3(void);
void Graphic_Cursor_Set4(void);
void Graphic_Cursor_Set5(void);
void Graphic_Cursor_Set6(void);
void Graphic_Cursor_Set7(void);
void Graphic_Cursor_Set8(void);
void Write_To_Bank1and2(void);
void Write_To_CGRAM(void);
void Write_To_GraphicCursor(void);
void Write_To_Pattern(void);
void Write_To_Bank1(void);
void Write_To_Bank2(void);


//REG[44h]
void Text_Blink_Time(uint8_t setx);

//REG[45h]  
void Memory_read_LeftRight_TopDown(void);
void Memory_read_RightLeft_TopDown(void);
void Memory_read_TopDown_LeftRight(void);
void Memory_read_DownTop_LeftRight(void);

//REG[46h]~REG[49h]
void XY_Coordinate(uint16_t X,uint16_t Y);


//REG[4Ah]~REG[4Dh]
void Memory_read_Coordinate(uint16_t X,uint16_t Y);

//REG[4Eh]
void Text_Cursor_Horizontal_Size(uint8_t setx);//uint8_t[3:0]

//REG[4Fh] 
void Text_Cursor_Vertical_Size(uint8_t setx);//uint8_t[3:0]

//REG[50h] 
void no_BTE_write(void);
void BTE_enable(void);
void BTE_contiguous_Data(void);
void BTE_rectangular_Data(void);

//REG[51h] 
void BTE_ROP_Code(uint8_t setx);

//REG[52h] 
void Layer1_Visible(void);
void Layer2_Visible(void);
void Transparent_Mode(void);
void Lighten_Overlay_Mode(void);
void Boolean_OR(void);
void Boolean_AND(void);
void Floating_window_mode(void);
void Floating_Window_transparent_with_BGTR_enable(void);
void Floating_Window_transparent_with_BGTR_disable(void);

void Layer1_2_scroll(void);
void Layer1_scroll(void);
void Layer2_scroll(void);
void Buffer_scroll(void);



//REG[53h] 
void layer2_1_transparency(uint8_t setx);

//REG[54h]~ [5Fh]
void BTE_Source_Destination	(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB);
void Source_Layer1(void);
void Source_Layer2(void);
void Destination_Layer1(void);
void Destination_Layer2(void);
void BTE_Size_setting(uint16_t X,uint16_t Y);


//REG[60h]~REG[67h]
void Text_color(uint16_t color);
void Background_color(uint16_t color);

void Text_Background_Color(uint8_t setR,uint8_t setG,uint8_t setB);//new 20100810
void Text_Foreground_Color(uint8_t setR,uint8_t setG,uint8_t setB);//new 20100810

void BTE_Background_color(uint8_t setR,uint8_t setG,uint8_t setB);
void BTE_Foreground_color(uint8_t setR,uint8_t setG,uint8_t setB);

void BTE_Background_red(uint8_t setx);
void BTE_Background_green(uint8_t setx);
void BTE_Background_blue(uint8_t setx);
void BTE_Foreground_red(uint8_t setx);
void BTE_Foreground_green(uint8_t setx);
void BTE_Foreground_blue(uint8_t setx);
void Pattern_Set_number(uint8_t setx);

void Pattern_Set_8x8(void);
void Pattern_Set_16x16(void);
void Pattern_Set_number(uint8_t setx);
void BackgroundColor_TransparentMode(uint8_t setR,uint8_t setG,uint8_t setB);


//********TP controller*******
//REG[70h]~REG[74h]
void Enable_TP(void);
void Disable_TP(void);
void Enable_Touch_WakeUp(void);
void Disable_Touch_WakeUp(void);
void TP_manual_mode(void);
void TP_auto_mode(void);
void TP_IDLE_mode(void);
void TP_event_mode(void);
void TP_latch_X(void);
void TP_latch_Y(void);
uint8_t ADC_X(void);
uint8_t ADC_Y(void);
uint8_t ADC_XY(void);


//REG[80h]~REG[85h]
void Graphic_Cursor_Coordinate(uint16_t X,uint16_t Y);
void Graphic_Cursor_Color_0(uint8_t setx);
void Graphic_Cursor_Color_1(uint8_t setx);


//REG[8Ah]
void PWM1_enable(void);
void PWM1_disable(void);
void PWM1_disable_level_low(void);
void PWM1_disable_level_high(void);
void PWM1_fnuction_sel(void);
void PWM1_system_clk_out(void);
void PWM1_clock_ratio(uint8_t setx); //bit0~3 
//REG[8Bh]
void PWM1_duty_cycle(uint8_t setx); //bit0~7

//REG[8Ch]
void PWM2_enable(void);
void PWM2_disable(void);
void PWM2_disable_level_low(void);
void PWM2_disable_level_high(void);
void PWM2_fnuction_sel(void);
void PWM2_system_clk_out(void);
void PWM2_clock_ratio(uint8_t setx); //bit0~3 
//REG[8Dh]
void PWM2_duty_cycle(uint8_t setx); //bit0~7

//REG[8Eh]
void Stop_Memory_Clear(void);
void Memory_Clear(void);
void Clear_Full_Window(void);
void Clear_Active_Window(void);


//REG[90h] 					
void Draw_line(void);
void Draw_square(void);
void Draw_square_fill(void);
void Draw_circle(void);
void Draw_circle_fill(void);
void Draw_Triangle(void);
void Draw_Triangle_fill(void);


//REG[90h]~REG[9Dh]  
void Geometric_Coordinate(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB);
void Circle_Coordinate_Radius(uint16_t X,uint16_t Y,uint16_t R);


//REG[A0h]~REG[ACh] 
void Draw_Ellipse(void);
void Draw_Ellipse_Curve(void);
void Draw_Ellipse_Curve_Fill(void);
void Draw_Ellipse_fill(void);

void Draw_Circle_Square(void);
void Draw_Circle_Square_fill(void);
void Draw_Ellipse_Curve_part(uint8_t setx);

void Ellipse_Coordinate_setting(uint16_t X,uint16_t Y,uint16_t ELL_A,uint16_t ELL_B);
void Circle_Square_Coordinate_setting(uint16_t XL,uint16_t XR ,uint16_t YT ,
                                      uint16_t YB ,uint16_t ELL_A,uint16_t ELL_B);
void Draw_Triangle_3point_Coordinate(uint16_t P1_X,uint16_t P1_Y,uint16_t P2_X,
                                     uint16_t P2_Y,uint16_t P3_X,uint16_t P3_Y);


//REG[B0]~REG[B3]
void DMA_Start_address_setting(uint32_t set_address);
//REG[B4]~REG[B8]
void DMA_Continuous_mode_size_setting(uint32_t set_size);
void DMA_block_mode_size_setting(uint16_t BWR,uint16_t BHR,uint16_t SPWR);

//REG[BFh]
void DMA_Continuous_mode(void);
void DMA_Block_mode(void);
void DMA_Start_enable(void);


//REG[C0h]
void Key_Scan_Enable(void);
void Long_Key_Scan_enable(void);
void Key_Scan_setting(uint8_t setx);//uint8_t[5:0]
void Key_Scan_Wakeup_Function_Enable(void);
void Long_Key_Timing_Adjustment(uint8_t setx);

//REG[D0]
void Floating_window_start_point(uint16_t X,uint16_t Y);
void Floating_window_size(uint16_t width_X,uint16_t high_Y);
void Floating_window_display_point(uint16_t X,uint16_t Y);


 //REG[E0]
void Serial_ROM_direct_access_mode_enable(void);
void Serial_ROM_direct_access_mode_disable(void);
void Direct_access_mode_Address_32bits(uint32_t set_address);
void Direct_access_mode_Address_24bits(uint32_t set_address);
uint8_t Direct_access_mode_Read_Data_buffer(void);

//REG[F0h] 
void KEYSCAN_Interrupt_Enable(void);
void KEYSCAN_Interrupt_Disable(void);
void DMA_Interrupt_Enable(void);
void DMA_Interrupt_Disable(void);
void Touch_Panel_Interrupt_Enable(void);
void Touch_Panel_Interrupt_Disable(void);
void BTE_Interrupt_Enable(void);
void BTE_Interrupt_Disable(void);
void Font_BTE_read_write_Interrupt_Enable(void);
void Font_BTE_read_write_Interrupt_Disable(void);


//REG[F1h] 
void Clear_keyscan_interrupt(void);
uint8_t Keyscan_Status(void);

void Clear_DMA_interrupt(void);
uint8_t DMA_Status(void);

void clear_TP_interrupt(void);
uint8_t Touch_Status(void);

void Clear_BTE_interrupt(void);
uint8_t BTE_Status(void);

void Clear_Font_BTE_read_write_Interrupt(void);
uint8_t Font_BTE_read_write_Status(void);


void Chk_Wait(void);
void Show_String(const char *str,uint8_t n);
//void LCD_Print_J_Str(uchar *ptr, int char_num);

void LCD_Reset(void);
uint8_t LCD_StatusRead(void);
void Show_word(u16 WOD);
void Show_WD(char *str,u8 n);
//void RA8875_WAITSTATUS(void);
//u16 Get_X_ADC_Value_10bit(void);
//u16 Get_Y_ADC_Value_10bit(void);
void delaysometime(void);
void LcdPrintHz(u16 code,u16 x,u16 y,u16 color,u16 bcolor);
void LcdPrintStr(char *str,u16 x,u16 y,u16 color,u16 bcolor,u8 mode);
void LcdPrintWord(u16 *str,u16 x,u16 y,u16 color,u16 bcolor,u8 mode);
void LcdPrintf(u16 x,u16 y,u16 color,u16 bcolor,char *fmt,...);
void LcdPrint16bitBmp(u16* image,u16 x,u16 y,u16 widht,u16 height);
void LcdPrint8bitBmp(const u8* image,u16 x,u16 y,u16 widht,u16 height);
void LCD_Init_RA8875(void);
void RA8875_PLL_ini(void);


void LCD_Initializtion(void);
void LcdClear(u16 color);
void Lcd_DrawPoint(u16 x, u16 y, u16 color);
void LCD_DrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color );
void LCD_DrawTriangle( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t x3, uint16_t y3 ,uint16_t color, uint16_t fill );
void LCD_DrawCircle( uint16_t x, uint16_t y, uint16_t r , uint16_t color , uint16_t fill );
void LCD_DrawEllipse( uint16_t x, uint16_t y, uint16_t Long_axis , uint16_t Short_axis,uint16_t color , uint16_t fill );
void LCD_DrawCurve( uint16_t x, uint16_t y, uint16_t Long_axis , uint16_t Short_axis,uint16_t color ,uint16_t part, uint16_t fill );
void LCD_DrawSquare( uint16_t x, uint16_t y, uint16_t x1 , uint16_t y1,uint16_t color , uint16_t fill );
void LCD_DrawCircleSquare( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 ,uint16_t Long_axis , uint16_t Short_axis,uint16_t color, uint16_t fill );

void LCD_Internal_Font_ROM(uint16_t x0, uint16_t y0,uint16_t Foreground_color,uint16_t Background_color,uint16_t Alignment,uint16_t Transparency, uint16_t zoom,uint16_t turning);
void LCD_External_Font_ROM(uint16_t x0, uint16_t y0,uint16_t Foreground_color,uint16_t Background_color,uint16_t Alignment,uint16_t Transparency, uint16_t zoom,uint16_t turning);

void LCD_drawVU(uint16_t* img);
void LCD_draw1(uint16_t* img);
void LCD_draw2(uint16_t* img);
void LCD_draw3(uint16_t* img);


void LCD_PrepareDMA(void);
void LCD_TransferDataDMA(void *buffer, uint32_t count);

void LCD_OpenBulkWrite(u16 x, u16 width, u16 y, u16 height);
void LCD_BulkWrite(uint16_t* pixel, uint32_t len);
void LCD_CloseBulkWrite(void);
#ifdef __cplusplus
}
#endif
#endif /*_RA8875_DERIVER_H*/


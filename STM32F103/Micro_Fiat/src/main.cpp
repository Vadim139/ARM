
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "diag/Trace.h"
#include <string.h>
#include "Timer.h"
#include "BlinkLed.h"
#include "main.h"
#include "BT_HC.h"
#include "STM32F4_Class.h"


#define __CAN1_USED__
/* #define __CAN2_USED__*/   /* Please check that you device is
                                Connectivity line when using CAN2 */

#ifdef  __CAN1_USED__
  #define CANx CAN1
#else /*__CAN2_USED__*/
  #define CANx CAN2
#endif  /* __CAN1_USED__ */

/* Private variables ---------------------------------------------------------*/
uint16_t CAN_ID;
uint8_t CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7;
uint8_t CAN_SDATA0,CAN_SDATA1,CAN_SDATA2,CAN_SDATA3,CAN_SDATA4,CAN_SDATA5,CAN_SDATA6,CAN_SDATA7;
uint8_t CanFlag,Display;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void CAN_Configuration(void);
void CanWriteData(uint16_t ID,uint8_t dlc = 8);

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t ret = 0; /* for return of the interrupt handling */
volatile TestStatus TestRx;

Timer timer;
BT_HC BT;

GPIO_IO L1(GPIOA,GPIO_Pin_11,1);
GPIO_IO L2(GPIOA,GPIO_Pin_12,1);
GPIO_IO W(GPIOA,GPIO_Pin_8,1);

using namespace std;
namespace {
// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wwrite-strings"

volatile bool flag = false;
volatile bool catching = false;
volatile bool filtering = false;
volatile bool show = false;
vector<uint16_t> IDs;

int main(int argc, char* argv[]) {
	// Send a greeting to the trace device (skipped on Release).
	trace_puts("Hello ARM World!");
	trace_printf("System clock: %u Hz\n", SystemCoreClock);
	bool exist = 0;
	char str[50];
	timer.start();

	BlinkLed blinkLed;

	L1.Init();
	L2.Init();

	W.Init();
	W.Set_low();

	L1.Set_low();
	L2.Set_high();

	BT.Init();

	  CAN_Configuration();
//	  CanWriteData(0x7de);

	  trace_puts("\r\n****************************************************************\r\n");

	  trace_puts("Bluetooth bautrate 115200\n");
	  trace_puts("CAN-Bus Speed 50kHz\n");

//	  int stany[3000];
//
//	  for(int &s : stany)
//		  s = 0;
//
//	  int state = W.read_state();
//	  while(state == W.read_state());
//	  int l = 0;
	while (1) {

//		stany[l] = W.read_state();
//		l++;
//		if(l >= 2999)
//			l = 0;
//		timer.sleep(1);
		  if( CanFlag == ENABLE )
		  {
	      CanFlag = DISABLE;
	      if(catching){
	    	  exist = false;
	    	  for(auto ID : IDs){
	    		  if(ID == CAN_ID)
	    		  {
	    			  exist = true;
	    			  break;
	    		  }
	    	  }
    		  if(!exist)
    			  IDs.push_back(CAN_ID);
	      }
	      else if(!filtering && show){
	    	  sprintf(str,"CAN ID %x ",CAN_ID);
	    	  BT.BT_sendcom(str);
//	    	  trace_printf("CAN ID %x ",CAN_ID);
	    	  sprintf(str,"%x %x %x %x %x %x %x %x \r",CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7);
	    	  BT.BT_sendcom(str);
	      }
	      else if(filtering){
	    	  exist = false;
	    	  for(auto ID : IDs){
	    		  if(ID == CAN_ID)
	    		  {
	    			  exist = true;
	    			  break;
	    		  }

	    	  }
    		  if(!exist){
//	    	    	  trace_printf("CAN ID %x ",CAN_ID);
//	    	    	  trace_printf("%x %x %x %x %x %x %x %x \n",CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7);
    	    	  sprintf(str,"CAN ID %x ",CAN_ID);
    	    	  BT.BT_sendcom(str);
    	    	  sprintf(str,"%x %x %x %x %x %x %x %x \r",CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7);
    	    	  BT.BT_sendcom(str);
    		  }
	      }
	      }
		  timer.sleep(10);
////		  CanWriteData(0x101);


		if(flag){
			if(BT.BT_find("catch\r"))
			{
				catching = true;
				show = false;
			}
			if(BT.BT_find("st_catch\r"))
			{
				catching = false;
				show = false;
//				for(auto ID : IDs){
//	    	    	  sprintf(str,"%x \r",ID);
//	    	    	  BT.BT_sendcom(str);
//				}
				sort (IDs.begin(), IDs.end());
				for(auto ID : IDs){
	    	    	  sprintf(str,"%x \r",ID);
	    	    	  BT.BT_sendcom(str);
				}
			}
			if(BT.BT_find("start\r"))
			{
				filtering = true;
				show = false;
			}
			if(BT.BT_find("stop\r"))
			{
				filtering = false;
				show = false;
			}
			if(BT.BT_find("show\r"))
			{
				show = true;
			}
			if(BT.BT_find("send1\r"))
			{
				//				Line 1
				CAN_SDATA0 = 0x04;
				CAN_SDATA1 = 0x04;
				CAN_SDATA2 = 0x30;
				CAN_SDATA3 = 0x2e;
				CAN_SDATA4 = 0x07;
				CAN_SDATA5 = 0xff;
				CAN_SDATA6 = 0x00;
				CAN_SDATA7 = 0x00;
				CanWriteData(0x7B0,6);
//				timer.sleep(200);
				//				Line 2
				CAN_SDATA0 = 0x04;
				CAN_SDATA1 = 0x04;
				CAN_SDATA2 = 0x30;
				CAN_SDATA3 = 0x2e;
				CAN_SDATA4 = 0x07;
				CAN_SDATA5 = 0x00;
				CAN_SDATA6 = 0x00;
				CAN_SDATA7 = 0x00;
				CanWriteData(0x7B0,6);
////				Line 1
//				CAN_SDATA0 = 0x50;
//				CAN_SDATA1 = 0x02;
//				CAN_SDATA2 = 0x52;
//				CAN_SDATA3 = 0x86;
//				CAN_SDATA4 = 0x28;
//				CAN_SDATA5 = 0x56;
//				CAN_SDATA6 = 0x07;
//				CAN_SDATA7 = 0x9f;
//				CanWriteData(0x5E7);
//
////				Line 2
//				CAN_SDATA0 = 0x51;
//				CAN_SDATA1 = 0x02;
//				CAN_SDATA2 = 0xa0;
//				CAN_SDATA3 = 0xca;
//				CAN_SDATA4 = 0x1e;
//				CAN_SDATA5 = 0x50;
//				CAN_SDATA6 = 0xf4;
//				CAN_SDATA7 = 0xe8;
//				CanWriteData(0x5E7);
//
////				Line 3
//				CAN_SDATA0 = 0x52;
//				CAN_SDATA1 = 0x02;
//				CAN_SDATA2 = 0x51;
//				CAN_SDATA3 = 0x9a;
//				CAN_SDATA4 = 0x14;
//				CAN_SDATA5 = 0x75;
//				CAN_SDATA6 = 0x05;
//				CAN_SDATA7 = 0xcc;
//				CanWriteData(0x5E7);
//
////				Line 4
//				CAN_SDATA0 = 0x53;
//				CAN_SDATA1 = 0x02;
//				CAN_SDATA2 = 0x64;
//				CAN_SDATA3 = 0xff;
//				CAN_SDATA4 = 0xdf;
//				CAN_SDATA5 = 0x4d;
//				CAN_SDATA6 = 0x0a;
//				CAN_SDATA7 = 0x1e;
//				CanWriteData(0x5E7);
//
////				Line 5
//				CAN_SDATA0 = 0x54;
//				CAN_SDATA1 = 0x02;
//				CAN_SDATA2 = 0x50;
//				CAN_SDATA3 = 0xf4;
//				CAN_SDATA4 = 0xff;
//				CAN_SDATA5 = 0xa3;
//				CAN_SDATA6 = 0xf0;
//				CAN_SDATA7 = 0x41;
//				CanWriteData(0x5E7);
//
////				Line 6
//				CAN_SDATA0 = 0x55;
//				CAN_SDATA1 = 0x02;
//				CAN_SDATA2 = 0xe8;
//				CAN_SDATA3 = 0x10;
//				CAN_SDATA4 = 0x80;
//				CAN_SDATA5 = 0x0;
//				CAN_SDATA6 = 0x0;
//				CAN_SDATA7 = 0x0;
//				CanWriteData(0x5E7);
//
//				timer.sleep(2000);
//				CAN_SDATA0 = 0x00;
//				CAN_SDATA1 = 0x00;
//				CAN_SDATA2 = 0x00;
//				CAN_SDATA3 = 0xda;
//				CAN_SDATA4 = 0x00;
//				CAN_SDATA5 = 0x00;
//				CAN_SDATA6 = 0x00;
//				CAN_SDATA7 = 0x00;
//				CanWriteData(0x5E7);
			}
			if (BT.BT_find("send2\r")) {
//				for(l=0;l<255;l++)
					for(int k=0;k<255;k=k+4){
				//				Line 1
				CAN_SDATA0 = 0x50;
				CAN_SDATA1 = 0x02;
				CAN_SDATA2 = k;//0x50;
				CAN_SDATA3 = 0x86;
				CAN_SDATA4 = 0x28;
				CAN_SDATA5 = 0x56;
				CAN_SDATA6 = 0x07;
				CAN_SDATA7 = 0x9f;
				CanWriteData(0x5E7);

				//				Line 2
				CAN_SDATA0 = 0x51;
				CAN_SDATA1 = 0x02;
				CAN_SDATA2 = 0xa0;
				CAN_SDATA3 = 0xca;
				CAN_SDATA4 = 0x1e;
				CAN_SDATA5 = 0x50;
				CAN_SDATA6 = 0xf4;
				CAN_SDATA7 = 0xe8;
				CanWriteData(0x5E7);

				//				Line 3
				CAN_SDATA0 = 0x52;
				CAN_SDATA1 = 0x02;
				CAN_SDATA2 = 0x51;
				CAN_SDATA3 = 0x9a;
				CAN_SDATA4 = 0x14;
				CAN_SDATA5 = 0x75;
				CAN_SDATA6 = 0x05;
				CAN_SDATA7 = 0xcc;
				CanWriteData(0x5E7);

				//				Line 4
				CAN_SDATA0 = 0x53;
				CAN_SDATA1 = 0x02;
				CAN_SDATA2 = 0x64;
				CAN_SDATA3 = 0xff;
				CAN_SDATA4 = 0xdf;
				CAN_SDATA5 = 0x4d;
				CAN_SDATA6 = 0x0a;
				CAN_SDATA7 = 0x1e;
				CanWriteData(0x5E7);

				//				Line 5
				CAN_SDATA0 = 0x54;
				CAN_SDATA1 = 0x02;
				CAN_SDATA2 = 0x50;
				CAN_SDATA3 = 0xf4;
				CAN_SDATA4 = 0xff;
				CAN_SDATA5 = 0xa3;
				CAN_SDATA6 = 0xf0;
				CAN_SDATA7 = 0x41;
				CanWriteData(0x5E7);

				//				Line 6
				CAN_SDATA0 = 0x55;
				CAN_SDATA1 = 0x02;
				CAN_SDATA2 = 0xe8;
				CAN_SDATA3 = 0x10;
				CAN_SDATA4 = 0x80;
				CAN_SDATA5 = 0x0;
				CAN_SDATA6 = 0x0;
				CAN_SDATA7 = 0x0;
				CanWriteData(0x5E7);

				timer.sleep(1000);
				CAN_SDATA0 = 0x00;
				CAN_SDATA1 = 0x00;
				CAN_SDATA2 = 0x00;
				CAN_SDATA3 = 0xda;
				CAN_SDATA4 = 0x00;
				CAN_SDATA5 = 0x00;
				CAN_SDATA6 = 0x00;
				CAN_SDATA7 = 0x00;
				CanWriteData(0x5E7);
				}
			}
			if(BT.BT_find("close\r"))
			{
				L1.Set_low();
				L2.Set_high();
				timer.sleep(200);
				L1.Set_low();
				L2.Set_low();
			}
			if(BT.BT_find("open\r"))
			{
				L1.Set_high();
				L2.Set_low();
				timer.sleep(200);
				L1.Set_low();
				L2.Set_low();
			}
			if(BT.BT_find("win_open\r"))
			{
				W.Set_high();
				timer.sleep(135);
				W.Set_low();
				timer.sleep(90);
				W.Set_high();
				timer.sleep(90);
				W.Set_low();
				timer.sleep(4000);
				W.Set_high();
				timer.sleep(60);
				W.Set_low();
			}
			if(BT.BT_find("win_close\r"))
			{
				W.Set_high();
				timer.sleep(135);
				W.Set_low();
				timer.sleep(4000);
				W.Set_high();
				timer.sleep(60);
				W.Set_low();
			}
			BT.ShowBuf();
			BT.FlushBuf();
			flag = false;
		}

	}
	// Infinite loop, never return.
}


void USART3_IRQHandler(void) {
	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {

		uint8_t ch;

		ch = USART_ReceiveData(USART3);

		BT.BT_recdata(&ch);
		if(ch == '\r')
			flag = true;


	}
}



void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* CAN Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable CAN1 RX0 interrupt IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : CAN_Configuration
* Description    : Configures the CAN
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void CAN_Configuration(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;

  NVIC_Configuration();
  GPIO_Configuration();
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = ENABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_15tq; // 80%   50kbs
  CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
  CAN_InitStructure.CAN_Prescaler = 36;

  if (CAN_Init(CAN1,&CAN_InitStructure) == CANINITFAILED)
  {
  }

  CAN_FilterInitStructure.CAN_FilterNumber=0;
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
  CAN_FilterInit(&CAN_FilterInitStructure);
}

/*******************************************************************************
* Function Name  : CanWriteData
* Description    : Can Write Date to CAN-BUS
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void CanWriteData(uint16_t ID,uint8_t dlc)
{
  CanTxMsg TxMessage;

//  CAN_DATA0=0x01;//rand()%0xff;
//  CAN_DATA1=0x02;//rand()%0xff;
//  CAN_DATA2=0x03;//rand()%0xff;
//  CAN_DATA3=0x04;//rand()%0xff;
//  CAN_DATA4=0x05;//rand()%0xff;
//  CAN_DATA5=0x07;//rand()%0xff;
//  CAN_DATA6=0x08;//rand()%0xff;
//  CAN_DATA7=0x09;//rand()%0xff;

  /* transmit */
  TxMessage.StdId = ID;
//TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = dlc;
  TxMessage.Data[0] = CAN_SDATA0;
  TxMessage.Data[1] = CAN_SDATA1;
  TxMessage.Data[2] = CAN_SDATA2;
  TxMessage.Data[3] = CAN_SDATA3;
  TxMessage.Data[4] = CAN_SDATA4;
  TxMessage.Data[5] = CAN_SDATA5;
  TxMessage.Data[6] = CAN_SDATA6;
  TxMessage.Data[7] = CAN_SDATA7;
  while(!((CANx->TSR&CAN_TSR_TME0) == CAN_TSR_TME0) && !((CANx->TSR&CAN_TSR_TME1) == CAN_TSR_TME1) && !((CANx->TSR&CAN_TSR_TME2) == CAN_TSR_TME2))
	  TxMessage.StdId = ID;
  if(CAN_Transmit(CAN1,&TxMessage) == CAN_TxStatus_NoMailBox)
	  TxMessage.StdId = ID;
}

/*******************************************************************************
* Function Name  : USB_LP_CAN1_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
volatile int none = 0;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;
  CAN_Receive(CAN1,CAN_FIFO0, &RxMessage);
  none = 0;
  for(int i = 0;i<8;i++){
	  if(RxMessage.Data[i] == 0)
		  none++;
  }
  if(none != 8)
  {
	  CAN_ID=RxMessage.StdId;
//	  if(CAN_ID == 0x180)
//		  CAN_ID=RxMessage.StdId;
	  CAN_DATA0=RxMessage.Data[0];
	  CAN_DATA1=RxMessage.Data[1];
	  CAN_DATA2=RxMessage.Data[2];
	  CAN_DATA3=RxMessage.Data[3];
	  CAN_DATA4=RxMessage.Data[4];
	  CAN_DATA5=RxMessage.Data[5];
	  CAN_DATA6=RxMessage.Data[6];
	  CAN_DATA7=RxMessage.Data[7];
	  //  CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	     CanFlag = ENABLE;
  }

}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

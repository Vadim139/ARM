//-----------------------------------------------------------------------------
//
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    BTC KORPORACJA SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//
//                     http://www kamami.com
//-----------------------------------------------------------------------------

//
//// MEMS CS line
//#define GPIO_Pin_CS GPIO_Pin_4
//#define GPIO_CS GPIOA


// LCD connection
#define PORT_ctrl          		GPIOB
#define RCC_AHBPeriph_ctrl    	RCC_AHB1Periph_GPIOB
#define DATA 					GPIO_Pin_15
#define CLK 					GPIO_Pin_13
#define CS 						GPIO_Pin_12
#define RES 					GPIO_Pin_14
//
//
//// Joystick
//#define JOY_PORT				GPIOE
//#define JOY_UP					GPIO_Pin_10
//#define JOY_DOWN				GPIO_Pin_9
//#define RCC_APB2Periph_JOY		RCC_APB2Periph_GPIOE

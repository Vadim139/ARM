#ifndef __GT811_H_
#define __GT811_H_

#include "stm32f4xx.h"
#include "GPIO_Config.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif
#define CT_CMD_WR		0XBA	//写数据命令
#define CT_CMD_RD   	0XBB	//读数据命令
#define CT_EXCHG_XY		1		//调转XY坐标

#define CT_MAX_TOUCH    5		//电容触摸屏最大支持的点数
#define CT_READ_XY_REG 	0x721  	//读取坐标寄存器 
#define CT_CONFIG_REG   0x6A2	//配置参数起始寄存器

//电容触摸屏控制器
typedef struct
{
	u8   (*init)(void);			//初始化触摸屏控制器
	void (*scan)(void);			//扫描触摸屏 	 
	u16 x[CT_MAX_TOUCH];		//触摸X坐标
	u16 y[CT_MAX_TOUCH];		//触摸Y坐标
 	u8	ppr[CT_MAX_TOUCH];		//触摸点的压力	 
	u8 tpsta;					//触摸屏状态
								//[0]:0,触摸点0无效;1,触摸点0有效
								//[1]:0,触摸点1无效;1,触摸点1有效
								//[2]:0,触摸点2无效;1,触摸点2有效
								//[3]:0,触摸点3无效;1,触摸点3有效
								//[4]:0,触摸点4无效;1,触摸点4有效
								//[5:6]:保留
								//[7]:0,没有有效触摸;1,有有效触摸,可以读出数据
				   	    	  
}_m_ctp_dev;


extern _m_ctp_dev ctp_dev;

u8 GT811_WR_Reg(u16 reg,u8 *buf,u8 len);//向GT811写入一次数据						    
u8 GT811_WR_Reg(u16 reg,u8 *buf,u8 len);//从GT811读出一次数据
u8 GT811_Send_Cfg(u8 * buf,u16 cfg_len);//向GT811发送配置参数
void GT811_Wakeup_Sleep(void);			//唤醒GT811
u8 GT811_Init(void);	    			//初始化GT811						 
void GT811_Scan(void);					//扫描GT811	  
void CT_TEST(void);
 
#ifdef __cplusplus
}
#endif
#endif /*__GT811_H_*/

#include "sccb.h"
//#include "delay.h"
#include "common.h"

void SCCB_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIOC  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SIC_BIT|SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}
void SCCB_SID_GPIO_OUTPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIOC  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void SCCB_SID_GPIO_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIOC  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void startSCCB(void)
{
    SCCB_SID_H();     //�����߸ߵ�ƽ
    _delay_us(500);

    SCCB_SIC_H();	   //��ʱ���߸ߵ�ʱ���������ɸ�����
    _delay_us(500);

    SCCB_SID_L();
    _delay_us(500);

    SCCB_SIC_L();	 //�����߻ָ��͵�ƽ��������������Ҫ
    _delay_us(500);


}
/*
-----------------------------------------------
   ����: stop����,SCCB��ֹͣ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void stopSCCB(void)
{
    SCCB_SID_L();
    _delay_us(500);

    SCCB_SIC_H();
    _delay_us(500);


    SCCB_SID_H();
    _delay_us(500);

}

/*
-----------------------------------------------
   ����: noAck,����������ȡ�е����һ����������
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void noAck(void)
{

	SCCB_SID_H();
	_delay_us(500);

	SCCB_SIC_H();
	_delay_us(500);

	SCCB_SIC_L();
	_delay_us(500);

	SCCB_SID_L();
	_delay_us(500);

}

/*
-----------------------------------------------
   ����: д��һ���ֽڵ����ݵ�SCCB
   ����: д������
 ����ֵ: ���ͳɹ�����1������ʧ�ܷ���0
-----------------------------------------------
*/
unsigned char SCCBwriteByte(unsigned char m_data)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if((m_data<<j)&0x80)
		{
			SCCB_SID_H();
		}
		else
		{
			SCCB_SID_L();
		}
		_delay_us(500);
		SCCB_SIC_H();
		_delay_us(500);
		SCCB_SIC_L();
		_delay_us(500);

	}
	_delay_us(100);
	SCCB_SID_IN;/*����SDAΪ����*/
	_delay_us(500);
	SCCB_SIC_H();
	_delay_us(100);
	if(SCCB_SID_STATE){tem=0;}   //SDA=1����ʧ�ܣ�����0}
	else {tem=1;}   //SDA=0���ͳɹ�������1
	SCCB_SIC_L();
	_delay_us(500);
        SCCB_SID_OUT;/*����SDAΪ���*/

	return (tem);
}

/*
-----------------------------------------------
   ����: һ���ֽ����ݶ�ȡ���ҷ���
   ����: ��
 ����ֵ: ��ȡ��������
-----------------------------------------------
*/
unsigned char SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;

	SCCB_SID_IN;/*����SDAΪ����*/
	_delay_us(500);
	for(j=8;j>0;j--) //ѭ��8�ν�������
	{
		_delay_us(500);
		SCCB_SIC_H();
		_delay_us(500);
		read=read<<1;
		if(SCCB_SID_STATE)
		{
			read=read+1;
		}
		SCCB_SIC_L();
		_delay_us(500);
	}
	return(read);
}

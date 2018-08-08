
#ifndef _sccb_H
#define _sccb_H
#ifdef __cplusplus
 extern "C" {
#endif
#define SCCB_SIC_BIT     GPIO_Pin_10
#define SCCB_SID_BIT     GPIO_Pin_11

#define SCCB_SIC_H()     GPIOB->BSRRL = SCCB_SIC_BIT;
#define SCCB_SIC_L()     GPIOB->BSRRH =  SCCB_SIC_BIT;

#define SCCB_SID_H()     GPIOB->BSRRL = SCCB_SID_BIT;
#define SCCB_SID_L()     GPIOB->BSRRH =  SCCB_SID_BIT;
/**/
#define SCCB_SID_IN      SCCB_SID_GPIO_INPUT();
#define SCCB_SID_OUT     SCCB_SID_GPIO_OUTPUT();


#define SCCB_SID_STATE	 GPIOB->IDR&0x0040

///////////////////////////////////////////
void SCCB_GPIO_Config(void);
void SCCB_SID_GPIO_OUTPUT(void);
void SCCB_SID_GPIO_INPUT(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);

#ifdef __cplusplus
 }
#endif
#endif /* _IIC_H */




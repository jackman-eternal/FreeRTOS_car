#ifndef __MONIIIC_H__
#define __MONIIIC_H__

#include "stm32f10x.h"
#include "delay.h"
//#include "system.h"


#define  IIC_SCL    PAout(7)   
#define  IIC_SDA    PAout(6)
#define  READ_SDA   PAin(6)

//IO��������  PA6
#define SDA_IN()  {GPIOA->CRL &= 0XF0FFFFFF;GPIOA->CRL |= 0X08000000;}//����
#define SDA_OUT() {GPIOA->CRL &= 0XF0FFFFFF;GPIOA->CRL |= 0X03000000;}//���

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	

#endif


#include "1602_iic_sw.h"

const u8 Ainit[42] = {
	0x30, 0x34, 0x30,
	0x30, 0x34, 0x30,
	0x30, 0x34, 0x30,
	0x20, 0x24, 0x20,
	0x20, 0x24, 0x20,
	0x80, 0x84, 0x80,
	0x00, 0x04, 0x00,
	0xc0, 0xc4, 0xc0,
	0x00, 0x04, 0x00,
	0x10, 0x14, 0x10,
	0x00, 0x04, 0x00,
	0x60, 0x64, 0x60,
	0x00, 0x04, 0x00,
	0x20, 0x24, 0x20,
};

//set default status of backlight to ON
static u8 backLight = BACKLIGHT_ON;
long int soc(int n);
/***
	initial 1602 pins and mode
***/
void init_1602(void)
{
	u8 i = 0;
	IIC_Init();     //配置GPIO
	i2cAction(0);   //全部清零
	delay_ms(500);

	for(i = 0; i < 42; ++i)
	{
		i2cAction(Ainit[i]);
		
		if((i == 2) || (i == 5))delay_ms(5);
		else if((i == 29) || (i == 41))delay_ms(2);
		else if(i == 8)delay_us(230); 
		else delay_us(20);
	}
}
//打印整数
void lcdPrint_int(int m)     
{
   int i,a,n=m,q[100];
    for(i=0;m!=0;i++)
	{
     m=m/10;	
	}
	a=i;
	for(i=0;i<a;i++)
	{
	  q[i]=n/soc(a-1-i);
		q[i]=q[i]%10;
		writeOneChar(DATA ,q[i]+48);
	}
}

//打印浮点数
void lcdPrint_float(float m) 
{
   /*整数部分*/
   int i,j,a,n,x,q[100];
	float h=m, y;
	  x=(int)m;	        //强制类型转换
	     n=x;
    for(i=0;x!=0;i++)
	{
     x=x/10;	
	}
	a=i;
	for(i=0;i<a;i++)
	{
	  q[i]=n/soc(a-1-i);
		q[i]=q[i]%10;
		writeOneChar(DATA ,q[i]+48);
	}
	/*打印小数部分*/
	y=h-(int)h;
	if(y==0)
	{
	 return;
	}
   writeOneChar(DATA ,'.');
	y=y*soc(jingdu+1);
	n=(int)y;
		for(j=0;j<jingdu;j++)
	{
	  q[i]=n/soc(jingdu-j);
		q[i]=q[i]%10;
		writeOneChar(DATA ,q[i]+48);
	     i++;
	}
}
/***
	Output charactors on 1602
***/
void lcdPrint_char(const char* charactor)  //打印一个数组
{
	u8 c = 0;
	for(c = 0; c < (u8)strlen(charactor); ++c)
	writeOneChar(DATA ,*(charactor + c));
}

void disOneChar(unsigned char X, unsigned char Y, char DData)
{
	Y &= 0x1;
	X &= 0xF;   //限制 X 不能大于 15，Y 不能大于 1
	if (Y) X |= 0x40;   //当要显示第二行时地址码+0x40;
	X |= 0x80;       //算出指令码
	writeOneChar(CMD, X);    //这里不检测忙信号，发送地址码
	writeOneChar(DATA, DData);
}
//
//打印一个字节
void writeOneChar(const u8 cmdOrData, const u8 Data)        //厉害！！！！！！！
{
	u8 LCM_Data = 0;
	LCM_Data = ((Data & 0xF0) | (cmdOrData) | (backLight));
	i2cAction(LCM_Data);

	i2cAction(LCM_Data | 0x04);
	delay_us(20);

	LCM_Data = (((Data & 0x0F)<<4) | (cmdOrData) | (backLight));
	i2cAction(LCM_Data);

	i2cAction(LCM_Data | 0x04);
	delay_us(20);
	i2cAction(LCM_Data);
}

/***
	set position of cursor
***/
void setCursor(u8 colmn, u8 line)
{
	line &= 0x1;
	colmn &= 0xF;   //限制 X 不能大于 15，line 不能大于 1
	if (line) colmn |= 0x40;   //当要显示第二行时地址码+0x40;
	colmn |= 0x80;       //算出指令码
	writeOneChar(CMD, colmn);    //这里不检测忙信号，发送地址码
}

/***
	send one frame by iic
***/
void i2cAction(u8 status)
{
	IIC_Start();
	IIC_Send_Byte(ADDRWRITE);
	IIC_Wait_Ack();
	IIC_Send_Byte(status);
	IIC_Wait_Ack();
	IIC_Stop();
}
//10的 n次方
long int soc(int n)
	{
	   int i,c=1;
		for(i=0;i<n;i++)
	   c=c*10;
		return c;
	}


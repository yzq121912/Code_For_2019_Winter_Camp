#include<iom16v.h>

a[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//数码管0~9数字
b[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//数码管1~8
int i,j,time[8]={0},*p=time,control[2]={0,1};//time[8]为3位ms,2位s,2位min,1位h

void init()//初始化
{
    DDRA = 0xff;
	DDRC = 0xff;
	PORTA = 0xc0;
	PORTC = 0xff;
	PORTB = 0xff;
}

void timeinit()//计时器初始化
{
    TCCR0 = 0x02;
	TCNT0 = 0;
}

void forward(int *p,int x)//进位函数
{
    if(*p == x)
	{
	    *p = 0;
	    *(p+1) = *(p+1) + 1;
	}
}

void delay(unsigned int x)//延时函数
{
    while(1)
	{
	    if(TCNT0 == x)
	    {
		    TCNT0 = 0;
			break;
		}
	}
}

void delay_ms()//基于程序修改后的ms延时函数
{
    for(i=0;i<10;i++)
	{
	    while(1)
	    {
	        if(TCNT0 == 45)
		    {
		        TCNT0 = 0;
		        break;
			}
		}
	}
}

void display()//显示函数
{
    for(i=0;i<8;i++)
    {
		if(i == 7 || i == 5 || i == 3)
	    {
		    PORTC = b[i];
		    PORTA = a[time[i]] - 0x80;
			delay(35);
	    }
		else
		{
		    PORTC = b[i];
		    PORTA = a[time[i]];
			delay(35);
	    }
	}
}

void main()
{
    init();
	timeinit();
	while(1)
	{
	    if(control[0] == 1 && control[1] == 1)//按钮判断
	    {
		    delay_ms();
		    time[0] = time[0] + 1;
		    for(i=0;i<7;i++)//进位循环
		    {
		        if(i == 4 || i == 6)
			        forward(p + i,6);
			    else
		            forward(p + i,10);
		    }
		    display();
			if(PINB == 0xfd)//STOP
			    control[1] = 0;
		}
		else
		{
		    if(PINB == 0xfe)//START
			    control[0] = 1;
			if(PINB == 0xfb)//CONTINUE
			    control[1] = 1;
			display();
		}
    }
}
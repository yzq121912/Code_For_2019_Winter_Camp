#include "iom16v.h"
#define uchar unsigned char
#define uint unsigned int 

void timer0_init(); 
void counter();
void disp(uint hour,uint minute,uint second,uint ms);
void delay(uint n);
uchar key();

uchar const table[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uint hour = 0,minute = 0,second = 0,ms = 0;
uchar Key_Value = 0X00;

void main()
{
   uchar i;
   timer0_init();  //定时器、计数器初始化
   Key_Value = key();  //检测START按钮是否被按下
   while(1)
   {   
       if(Key_Value == 0X06) //STAR 控制
       { 
           while(1) 
           {
	            while(1)  //计时器、计数器
		        {
		            TCNT0 = 0X59;  
				    break;    
			    }     
	   		    ms++;
	   		    if(ms==100)  //时、分、秒计算
	   		    {
	       	        counter();
	   		    } 
                
                Key_Value = PIND&0X07;  
                delay(1);   //消抖
                  		    
			    if(Key_Value == 0X07)  //START按钮是否被打开
			    {
			        hour = 0;minute = 0;second = 0;ms = 0;
			        break;
			    }
			    if(Key_Value == 0X04)  //RESET按钮是否被按下
			    {
			        hour = 0;minute = 0;second = 0;ms = 0;
			    }               
                if(Key_Value == 0X02) //STOP/CONTINUE按钮是否被按下
                {
                    break;                               
                }
                if(Key_Value == 0X00)  //START/RESET/STOP/CONTINUE按钮同时按下初始化位0
                {
                     hour = 0;minute = 0;second = 0;ms = 0;
                }             
                disp(hour,minute,second,ms);  //显示时、分、秒
   		    }
        }
        Key_Value = key(); //继续检测START按钮是否被按下
               
        if(Key_Value == 0X02) //STOP/CONTINUE按钮是否被按下后执行的动作
        {
            while(1)
            {             
                 disp(hour,minute,second,ms);       
                 Key_Value = PIND&0X07;
                 delay(1);
                 if(Key_Value == 0X00)   //START/RESET/STOP/CONTINUE按钮同时按下初始化位0
                 {
                     hour = 0;minute = 0;second = 0;ms = 0;
                 }
                 if(Key_Value == 0X06);
                 {                           
                      break;
                 }
             }
        }   
    }  
}

void timer0_init()
{
    TCCR0 = 0X00;
	TCNT0 = 0X59;  //初始化寄存器
	TCCR0 = 0X05; //选择1024分频
}

void counter() //时、分、秒计算
{
	ms = 0;
	second++;
	if(second == 60)
	{
		second = 0;
		minute++;
		if(minute == 60)
		{
		    minute = 0;
			hour++;
			if(hour == 60)
			{
			    hour = 0;
		    }
		}
	}	
}

void delay(uint n)  //延时 n ms  
{
    uint m; 
    for(n;n>0;n--)
    {
        for(m = 1141;m>0;m--);
    }
}

void disp(uint hour,uint minute,uint second,uint ms)//显示函数
{
    uchar i;
	uchar num[8] = {0};
    num[0] = hour/10;
	num[1] = hour%10;
	num[2] = minute/10;
	num[3] = minute%10;
	num[4] = second/10;
	num[5] = second%10;
	num[6] = ms/10;
	num[7] = ms%10;
	
	DDRA = 0XFF;
	DDRB = 0XFF;
	while(1)
	{
	    PORTA = 0XFF;
		PORTB = 0X00;
		for(i = 0;i<8;i++)
		{
		    if(((i+1)%2)==0)  //设置小数点
			{
			    PORTA = (1<<i);
		        PORTB = table[num[i]]&0X7F;
				delay(1);
				PORTA = 0X00;
				PORTB = 0X00;	    
		    }
			else
			{
			    PORTA = (1<<i);
		        PORTB = table[num[i]];
				delay(1);
				PORTA = 0X00;
				PORTB = 0X00;
			}
		}
		break;
	}
}

uchar key() //检测START按键是否被按下
{
    DDRD = 0X00;
	PORTD = 0X07;
	while(1)
	{
        delay(1); //消抖
        Key_Value = PIND&0X07;
	    if(Key_Value == 0X07)  
	    {
	        return (0);
	    }
        if(Key_Value == 0X06)  
	    {
	        return (Key_Value);
	    }
        else
        {
            Key_Value == 0X02;
            return (Key_Value);
        }
	}
} 

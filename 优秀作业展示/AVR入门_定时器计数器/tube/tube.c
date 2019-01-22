#include <iom16v.h>
#define bit(n) (1<<n)
#pragma interrupt_handler enter_one:9
unsigned char data[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0};
unsigned char  ms = 0;s = 0,m = 0,h = 0; 
void enter_one ()
{ 
  if (ms == 10)
  {
   ms = 0;
   s++;
  	 if (s == 60)
	 {
	     s = 0;
	     m++;
	        if (m == 60)
	       {
	  	      m = 0;
		      h++;
		      if(h == 24) 
			  {
			      h = 0;
			  }
	        }
	  }
	}
	 ms++;
	 TCNT1H = 0XF3;
	 TCNT1L = 0XCA;
}
void delay(int ms)
{
 	int i,j;
 	for(i = 0; i<ms ;i++)
	{
	 	  for (j = 0; j<1148; j++);
	}
}
void show_time(int i, int j)//低电平输出位数。
{
  if (j ==2 || j == 4 || j == 6)
  {
    PORTA = ~bit(j); 
	PORTB = data[i]|0x80;
  }
  else 
  {
  PORTA = ~bit(j); 
  PORTB = data[i];
  }
  delay(1);
}

int key_press()
{
 	unsigned char j;
	
 	DDRD  = 0X0f;
	PORTD = 0X0f;
	
	DDRD  &= ~0X0F; 
	j = PIND;
	j = j&0x0f;
	if(j == 0x0f)
	return 0;
	else 
	return 1;
}
int key_scan()
{ 
  unsigned char key;
  delay(10);
  if (key_press())
  {
   	 key = PIND;
	 key&= 0x0f;
	switch(key)
	{
	   case 0x0e:key = 1; break;           //start 按下
	   case 0x0d:key = 2; break;		  //reset 按下
	   case 0x0b:key = 3; break;		 //continue 按下
	   case 0x07:key = 4; break;	    //stop 按下
	}
	 while (key_press());     //判断是否按钮松开，避免重复以上循环！
	 return key;
  }
  else 
  return key =10;
}


void main ()
{	
    int i;
    DDRA = 0xff;
	DDRB = 0xff;
	
	TCCR1B = 0X00;
start:	TCNT1H = 0XF3;
	    TCNT1L = 0XCA;
	    TIMSK |= bit(2);
	    SREG  |= bit(7);
	while (1)
	{
	if (key_press())
	 {
	   	 switch (key_scan())
	 {
	   case 1:  TCCR1B = 0X04;goto start;
	   case 2: ms = 0 ;s =0 ; m =0 ;h =0 ;TCCR1B = 0X00;goto start ;
	   case 3:TCCR1B = 0X04;goto start;
	   case 4:TCCR1B = 0X00;goto start;
	   }
	  }
	
	             show_time(0,0);
	             show_time(ms,1);
	             show_time(s%10,2);
	             show_time(s/10,3);
	             show_time(m%10,4);
	             show_time(m/10,5);
	             show_time(h%10,6);
	             show_time(h/10,7);
				 
	}
}

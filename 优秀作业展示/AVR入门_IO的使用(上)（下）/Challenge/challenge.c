#include <iom16v.h>

void delay(unsigned int ms)//ms����ʱ����
{
   int i;
   for(i=0;i<ms*1148;i++);
}

void main()
{
    int i,j;
    DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	while(1)
	{
		PORTC = ~0x01;
    	PORTD = 0xFF;
    	for(i=0;i<8;i++)//A--C
   		{
        	PORTA = 0x01;
        	for(j=0;j<7;j++)
        	{
	    		delay(300);
	        	PORTA = (PORTA << 1);
	    	}
	    	delay(300);
	    	PORTA = 0x00;
	    	PORTC = (PORTC << 1) + 1;
		}
		PORTC = 0xFF;
		PORTD = ~0x01;
		for(i=0;i<8;i++)//A--D
		{
	    	PORTA = 0x01;
	    	for(j=0;j<7;j++)
	    	{
	        	delay(300);
	        	PORTA = (PORTA << 1);
	    	}
	    	delay(300);
	    	PORTA = 0x00;
	    	PORTD = (PORTD << 1) + 1;
    	}
		PORTC = ~0x01;
    	PORTD = 0xFF;
    	for(i=0;i<8;i++)//B--C
    	{
        	PORTB = 0x01;
        	for(j=0;j<7;j++)
        	{
	        	delay(300);
	        	PORTB = (PORTB << 1);
	    	}
	    	delay(300);
	    	PORTB = 0x00;
	    	PORTC = (PORTC << 1) + 1;
    	}
    	PORTC = 0xFF;
    	PORTD = ~0x01;
    	for(i=0;i<8;i++)//B--D
    	{
        	PORTB = 0x01;
        	for(j=0;j<7;j++)
        	{
    	    	delay(300);
    	    	PORTB = (PORTB << 1);
	    	}
    		delay(300);
    		PORTB = 0x00;
	    	PORTD = (PORTD << 1) + 1;
		}
    }
}
#include<avr/io.h>
#include<util/delay.h>
#include"lcd.h"
#include"string.h"
#include<stdlib.h>
#include <avr/interrupt.h>

void delay(uint16_t count)
{
	uint16_t i;
	for(i=0;i<count;i++)
	_delay_ms(1);
}
void main()
{
	uint16_t adc_val;
	uint8_t FSR1;
	DDRB=0xFF;
	InitLCD(0);
	USARTInit(51);
	InitADC();
	LCDClear();
	LCDWriteString("Temperature");
	LCDWriteStringXY(0,1,"Monitoring Node");
	char arr[10];
	delay(20);

	LCDClear();
	LCDWriteString("Temperature 0C");
	 sei();
	while(1)
	{
	 	char adc_val=ReadADC(0);
		FSR1=adc_val/2;
     	        delay(100);
		write("FSR1:");
		itoa(FSR1,arr,10);
		write(arr);
		USARTWriteChar('\n');
		LCDWriteIntXY(0,1,FSR1,3);
	 	delay(100);
 

       }
 }

 ISR(USART_RXC_vect)
	{
       char data= USARTReadChar();
	if(data=='X')
	   {
	    LCDClear();
	 	PORTB=0b00000001;
		LCDWriteStringXY(0,1,"FORWARD");
	   }
	else if(data=='Y')
	   {
		LCDClear();
	 	PORTB=0b00000010;
		LCDWriteStringXY(0,1,"REVERSE");
		}
    }
	
ISR(USART_TXC_vect)
		{
		cli();
		}

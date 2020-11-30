#include<avr/io.h>

void InitADC()
{
ADMUX=(1<<REFS0);// For Aref=AVcc;
ADCSRA=(1<<ADEN)|(7<<ADPS0);
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ADMUX&=0xf8;
	ch=ch&0b00000111;
	ADMUX|=ch;
	
	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);
	return(ADC);
}

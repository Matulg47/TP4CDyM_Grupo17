#include "adc.h"
static volatile uint16_t data = 0;
uint8_t flag_adc = 0;

void ADC_Init(void){
	DDRC &=~(1<<DDC3);			                                // Configuro como entrada el pin PC3.
	DIDR0 |= (1 << ADC3D);                                      // Configuro como entrada analógica el pin PC3.
	ADCSRB = 0x00;                                              // Free running mode
	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);        // Escribiendo este bit a uno se habilita el ADC y Prescaler de 8
	ADMUX = (1<< REFS0) | (1 << MUX0) | (1 << MUX1); // Vref=AVCC, ADLAR = 1 => Bits convertidos en la parte alta, selecciono ADC3 como canal analogico
}

void ADC_Lectura(void){
	ADCSRA |= (1<<ADSC);              //Iniciamos conversion.
	while((ADCSRA&(1<<ADIF))==0);     //Esperamos hasta que termine la conversion.
	ADCSRA |= (1<<ADIF);              //Borramos el flag.
	data = ADC;                       //Guardo la parte alta de ACD en la variable data
	flag_adc = 1;	                  //Este flag esta para informar al programa principal que ya termino la conversion
	_delay_ms(50);
}

void set_flag_adc(uint8_t valor) {
	flag_adc = valor;
}

uint8_t get_flag_adc(void) {
	return flag_adc;
}

uint16_t get_adc_data(void) {
	return data;
}
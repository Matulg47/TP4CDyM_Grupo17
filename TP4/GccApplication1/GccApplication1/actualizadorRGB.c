#include "SerialPort.h"
#include "ADC.h"
#include <stdio.h>
#include "actualizadorRGB.h"

volatile uint8_t car;
volatile uint8_t Flag_RX = 0;
uint8_t valor;

void ledrgb_Init(void){
	DDRB |= (1<<DDB1); //PIN PB1 como salida
	DDRB |= (1<<DDB2); //PIN PB2 como salida
	DDRB |= (1<<DDB3); //PIN PB3 como salida   Dado que este valor se copia abajo.
	DDRB |= (1<<DDB5); //PIN PB5 como salida
}

void Task(uint8_t *red, uint8_t *green, uint8_t *blue)
{
	ADC_Lectura();	                                       //Se lee el valor del potenciometro y se guarda.
	if(get_flag_adc())                                     //Se confirma si se leyo el valor del potenciometro correctamente
	{
	
	    valor = get_adc_data();                    //Leo el valor del potenciometro
		uint8_t porcentaje = (valor*100) / 1023.0;                     //Convierto valor en porcentaje

		set_flag_adc(0);
		
		uint8_t nuevoColor = (uint8_t)((porcentaje / 100.0) * 255);
		
		switch (car) {
			case 'R':
				*red = nuevoColor;
				Ingreso_R(*red);
				break;
			case 'r':
				*red = nuevoColor;
				Ingreso_R(*red);
				break;
			case 'G':
				*green = nuevoColor;
				Ingreso_G(*green);
				break;
			case 'g':
				*green = nuevoColor;
				Ingreso_G(*green);
				break;
			case 'B':
				*blue = nuevoColor;
				Ingreso_B(*blue);
				break;
			case 'b':
				*blue = nuevoColor;
				Ingreso_B(*blue);
				break;
		}
	}
}

uint8_t getFlag()
{
	return Flag_RX;
}

void setFlag(uint8_t flag)
{
	Flag_RX = flag;
}
	
ISR(USART_RX_vect)
{
	static volatile uint8_t RX_Buffer = 0;
	RX_Buffer = UDR0; // lee datos ingresados
	Flag_RX = 1;
	car = RX_Buffer;
}
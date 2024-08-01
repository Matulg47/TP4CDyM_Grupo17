#include <avr/io.h>
#include "actualizadorRGB.h"
#include "ADC.h"
#include "timers.h"
#include "serialPort.h"
#include <avr/interrupt.h>

#define F_CPU 16000000UL

uint8_t red;
uint8_t green;
uint8_t blue;

int main(void)
{
    SerialPort_Init(0x67); // Configurar UART a 9600bps, 8 bits de datos, 1 bit de parada @ F_CPU = 16MHz.
    SerialPort_RX_Enable(); // Habilitar receptor USART.
    SerialPort_RX_Interrupt_Enable(); // Habilitar interrupción de receptor USART.
	SerialPort_TX_Enable();
	
	PWM_timer1_init();
	PWM_timer2_init();
	
	ADC_Init();
	
	ledrgb_Init();
	
	red = 255;
	green = 0;
	blue = 0;
	
	Ingreso_R(red);
	Ingreso_G(green);
	Ingreso_B(blue);
	
	sei();
	
	SerialPort_Send_String("Ingrese R, G o B dependiendo del color que desee cambiar \n");
		
    while (1) 
    {
		if (getFlag())
		{
			Task(&red, &green, &blue);
			SerialPort_Send_String("Ingrese R, G o B dependiendo del color que desee cambiar \n");
			setFlag(0);
		}
    }
}


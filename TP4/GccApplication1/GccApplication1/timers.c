#include "timers.h"

/*Inicializacion de PWM para PB1 y PB2 */

void PWM_timer1_init(void){
	TCNT1 = 0;                                     // Reiniciar el contador inicial
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);  // Modo 5, Fast PWM 8-bit (el TOP de esta PWM es 0xFF)
	TCCR1B |= (1<<WGM12)|(1<<CS11);	               // Prescaler 8
}

/*Inicializacion de PWM para PB3, con interrupcion para PB5*/

void PWM_timer2_init(void){
	TCNT2 = 0;                                                 // Reiniciar el contador inicial 
	TCCR2A |= (1<<COM2A1)|(1<<WGM21)|(1<<WGM20);               // Modo 3, Fast PWM (el TOP de esta PWM es 0xFF)
	TCCR2B |= (1<<CS21);                                       // Prescaler 8
	TIMSK2 |= (1<<OCIE2A)|(1<<TOIE2);				    	   // Activar la interrupción en modo CTC Match A y Overflow en Timer2
}

/*Para definir los componentes RGB*/
void Ingreso_R(uint8_t r){
	OCR2A = 255 - r;
}

void Ingreso_G(uint8_t g){
	OCR1B = 255 - g;
}

void Ingreso_B(uint8_t b){
	OCR1A = 255 - b;
}

/*Las siguientes interrupciones sirven para copiar el la señal pwm de OC2A en PB5 debido a como esta conectado el LED en el kit*/

ISR(TIMER2_COMPA_vect)
{
	PORTB &=~(1<<5);
}

ISR(TIMER2_OVF_vect){
	PORTB |= (1<<5);
}
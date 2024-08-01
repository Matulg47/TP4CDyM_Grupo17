#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

void ADC_Init(void);
void ADC_Lectura(void);

void set_flag_adc(uint8_t valor);
uint8_t get_flag_adc(void);
uint16_t get_adc_data(void);

#endif /* ADC_H_ */
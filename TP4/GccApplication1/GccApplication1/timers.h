#ifndef PWM_H_
#define PWM_H_

#include <avr/interrupt.h>

void PWM_timer1_init(void);
void PWM_timer2_init(void);
void Ingreso_R(uint8_t r);
void Ingreso_G(uint8_t g);
void Ingreso_B(uint8_t b);

#endif /* PWM_H_ */
#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint8_t car;
extern volatile uint8_t Flag_RX;

void ledrgb_Init(void);
void Task(uint8_t *, uint8_t *, uint8_t *);
void setFlag(uint8_t);
uint8_t getFlag(void);

#endif /* INCFILE1_H_ */
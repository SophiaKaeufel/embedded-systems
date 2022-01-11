/*
 * timer.h
 *
 * Created: 03.01.2022 19:58:47
 *  Author: Miche
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "events.h"

#define NUMOFTIMER 5
#define TIMER1 1
#define TIMER2 2
struct timer{
	uint32_t duration;
	uint32_t timerCounter;
	uint32_t run;
	uint8_t declare;
	void (*callback)();
};
	
volatile struct timer timer_t[NUMOFTIMER];


ISR(TIMER0_OVF_vect){
	TCNT0 = 6;
	for(uint8_t i = 0; i< NUMOFTIMER; i++){
		if(timer_t[i].run == 1){
			timer_t[i].timerCounter++;
			if(timer_t[i].timerCounter >= timer_t[i].duration){
				timer_t[i].timerCounter = 0;
				sei();
				timer_t[i].callback();
			}
		}
	}
	
}


void initTimer(){
	for(uint8_t i = 0; i < NUMOFTIMER; ++i){
		timer_t[i].duration = 0;
		timer_t[i].run = 0;
		timer_t[i].declare = 0;
		timer_t[i].timerCounter = 0;
		timer_t[i].callback = NULL;
	}
}

void declareTimer(uint8_t t, uint32_t time, void (*fun)()) {
	timer_t[t].duration = time;
	timer_t[t].declare = 1;
	timer_t[t].callback = fun;
}

void startTimer(uint8_t t){
	timer_t[t].run = 1;
	timer_t[t].timerCounter = 0;
}

void clearTimer(uint8_t t){
	unsigned char sreg_old = SREG;
	cli();
	timer_t[t].run = 0;
	SREG = sreg_old;
}

#endif /* TIMER_H_ */
/*
 * functions.h
 *
 * Created: 06.01.2022 18:16:00
 *  Author: Mekon
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "init.h"
#include "uart.h"

void high();
	
void taster(){
	if((PIND & (1<<PIND7)) && button == 0){
		button = 1;
	}
	
	if(button == 1){
		button = 0;
		cli();
		
		HS_GRUEN_AUS;
		HS_GELB_AN;
		NS_GELB_AN;
		
		_delay_ms(2000);
		HS_GELB_AUS;
		HS_ROT_AN;
		
		NS_ROT_GELB_AUS;
		NS_GRUEN_AN;
		_delay_ms(3000);
		
		NS_GRUEN_AUS;
		NS_GELB_AN;
		_delay_ms(2000);
		NS_GELB_AUS;
		NS_ROT_AN;
		_delay_ms(4000);
		HS_GELB_AN;
		_delay_ms(2000);
		HS_ROT_GELB_AUS;
		HS_GRUEN_AN;
		
		sei();
	}
}

void high(){
		HS_GRUEN_AN;
		NS_ROT_AN;
		_delay_ms(6000);		//1:10 (60s) freie HS
		HS_GRUEN_AUS;
		HS_GELB_AN;
		NS_ROT_GELB_AN;
		_delay_ms(2000);		//HS: 2s leuchtet gelb
		HS_GELB_AUS;
		HS_ROT_AN;
		_delay_ms(3000);		//NS: 3s leuchtet rot & gelb
		NS_ROT_GELB_AUS;
		NS_GRUEN_AN;
		_delay_ms(3000);		//1:10 (30s) freie NS
		HS_ROT_GELB_AN;
		NS_GRUEN_AUS;
		NS_GELB_AN;
		_delay_ms(2000);		//NS: Gelb 2sek.
		NS_GELB_AUS;
		NS_ROT_AN;
		_delay_ms(3000);		//HS: 3s leuchtet rot & gelb
		HS_ROT_GELB_AUS;
}

void low(){
	HS_AUS;
	NS_GRUEN_AUS;
	NS_ROT_AUS;
	NS_GELB_AUS;
	_delay_ms(3000);
	NS_GELB_AN;
	_delay_ms(1000);
}

void remote(){
	HS_AUS;
	NS_AUS;
	HS_GRUEN_AN;
}

void degraded(){
	//bla
}



#endif /* FUNCTIONS_H_ */
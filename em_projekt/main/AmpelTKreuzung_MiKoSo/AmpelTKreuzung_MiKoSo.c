/*
 * AmpelTKreuzung_MiKoSo.c
 *
 * Created: 04.01.2022 12:13:38
 * Author : Miche
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "timer.h"
#include "init.h"
#include "interrupt.h"
#include "functions.h"
#include "uart.h"
#include "menu.h"


int main(void){
    init();
	USART_Init();
		
	declareTimer(TIMER500MS, 500, taster);
	startTimer(TIMER500MS);
		
	//interrupt enable
	sei();
	
	// Testtage und -stunden
	day = sunday;
	hour = 13;
	
	//printMenu(mainMenu_message_menu);
	//char c;
	//uint8_t selection;

    while (1) {
		/*
		c = USART_Receive();

		if(c){
			USART_Transmit(c);
			USART_Transmit(0x0d);
		}
		selection = c - 48;	//Notwendig da wir einen char als Eingabe haben und dieser im ASCII-Code zu einem Integer runtergerechnet werden muss
*/
		mainmenu_func();
		
		if (hour == 0){
			if (day == sunday){
				day = monday;
			}
			else
				day++;
		}

		switch (day){
			case monday:
			case tuesday:
			case wednesday:
			case thursday:
			case friday:
			//start - end Zeiten fuer Werktagzustaende
			if((hour >= werktag_starttime_remote) && (hour < werktag_endtime_remote)){
				status = remotefreq;
				remote();
			}
			else if((hour >= werktag_starttime_high) && (hour < werktag_endtime_high)){
				status = highfreq;
				high();
			}
			else if ((hour >= werktag_starttime_low) && (hour <= werktag_endtime_low)){
				status = lowfreq;
				low();
			}
			break;
			case saturday:
			//Start und Endzeiten fuer Samstagszustaende
			if((hour >= saturday_starttime_remote) && (hour < saturday_endtime_remote)){
				status = remotefreq;
				remote();
			}
			else if(((hour >= saturday_starttime_low1) && (hour < saturday_endtime_low1)) || ((saturday_starttime_low2 >= 22 && hour <= saturday_endtime_low2))){
				status = lowfreq;
				low();
			}
			else if ((hour >= saturday_starttime_high) && (hour < saturday_endtime_high)){
				status = highfreq;
				high();
			}
			break;
			case sunday:
			//Start und Endzeiten fuer Sonntagszustaende
			if((hour >= sunday_starttime_remote) && (hour < sunday_endtime_remote)){
				status = remotefreq;
				remote();
			}
			else if(((hour >= sunday_starttime_low1) && (hour < sunday_endtime_low1)) || ((hour >= sunday_starttime_low2) && (hour <= sunday_endtime_low2))){
				status = lowfreq;
				low();
			}
			else if ((hour >= sunday_starttime_high) && (hour < sunday_endtime_high)){
				status = highfreq;	
				high();
			}
			break;
			default:
				status = degradedfreq;
				//Fehlermeldung
			break;
		}		
    }
}


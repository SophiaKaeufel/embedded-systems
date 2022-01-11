/*
 * defines.h
 *
 * Created: 06.01.2022 14:33:10
 *  Author: Mekon
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

volatile enum week {monday = 1, tuesday = 2, wednesday = 3, thursday = 4, friday = 5, saturday = 6, sunday = 7} day;
volatile uint8_t hour = 0; // 24 stunden pro Tag
volatile uint8_t button = 0;

volatile enum freqstate{highfreq = 0, lowfreq, remotefreq, degradedfreq}status;

//Frequency_Zeiten weekday
volatile uint8_t werktag_starttime_high = 5; // 5 bis >20 Uhr ist high
volatile uint8_t werktag_endtime_high = 19;	// 5 bis >20 Uhr ist high
volatile uint8_t werktag_starttime_low = 20; // 20 bis >=23
volatile uint8_t werktag_endtime_low = 23; // 20 bis >=23
volatile uint8_t werktag_starttime_remote = 0; //0 bis >5
volatile uint8_t werktag_endtime_remote = 4; //0 bis >5

//Frequency_Zeiten Saturday
volatile uint8_t saturday_starttime_high = 9; // 9 bis >22
volatile uint8_t saturday_endtime_high = 21; // 9 bis >22
volatile uint8_t saturday_starttime_low1 = 5; //5 bis >9
volatile uint8_t saturday_endtime_low1 = 8; //5 bis >9
volatile uint8_t saturday_starttime_low2 = 22; // 22 bis >=23
volatile uint8_t saturday_endtime_low2 = 23; // 22 bis >=23
volatile uint8_t saturday_starttime_remote = 0; //0 bis >5
volatile uint8_t saturday_endtime_remote = 4; //0 bis >5

//Frequency_Zeiten sunday
volatile uint8_t sunday_starttime_high = 13; // 13 bis >20
volatile uint8_t sunday_endtime_high = 19;	// 13 bis >20
volatile uint8_t sunday_starttime_low1 = 9; // 9 bis >13
volatile uint8_t sunday_endtime_low1 = 12;	// 9 bis >13
volatile uint8_t sunday_starttime_low2 = 20; // 20 bis >=23
volatile uint8_t sunday_endtime_low2 = 23;	// 20 bis >=23
volatile uint8_t sunday_starttime_remote = 0; //0 bis >9
volatile uint8_t sunday_endtime_remote = 8; //0 bis >9


//Hauptstraﬂenampeln
#define HS_GRUEN_AN			PORTB |= (1<<PORTB2)
#define HS_GRUEN_AUS		PORTB &= ~(1<<PORTB2)
#define HS_GELB_AN			PORTB |= (1<<PORTB1)
#define HS_GELB_AUS			PORTB &= ~(1<<PORTB1)
#define HS_ROT_AN			PORTB |= (1<<PORTB0)
#define HS_ROT_AUS			PORTB &= ~(1<<PORTB0)
#define HS_ROT_GELB_AN		PORTB |= (1<<PORTB1)
#define HS_ROT_GELB_AUS		PORTB &= ~((1<<PORTB0)|(1<<PORTB1))
#define HS_AUS				PORTB &= ~((1<<PORTB2)|(1<<PORTB1)|(1<<PORTB0))

//Nebenstraﬂe + Fuﬂg‰ngerampel
#define NS_GRUEN_AN			PORTC |= (1<<PORTC2)
#define NS_GRUEN_AUS		PORTC &= ~(1<<PORTC2)
#define NS_GELB_AN			PORTC |= (1<<PORTC1)
#define NS_GELB_AUS			PORTC &= ~(1<<PORTC1)
#define NS_ROT_AN			PORTC |= (1<<PORTC0)
#define NS_ROT_AUS			PORTC &= ~(1<<PORTC0)
#define NS_ROT_GELB_AN		PORTC |= (1<<PORTC1)
#define NS_ROT_GELB_AUS		PORTC &= ~((1<<PORTC0)|(1<<PORTC1))
#define NS_AUS				PORTC &= ~((1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0))
	
//Taster
#define TIMER500MS		1

//Betriebszustand
#define HIGH_FREQ_OP	0
#define LOW_FREQ_OP		1
#define REMOTE_FREQ_OP	2
#define DEGRADED_OP		3
	
//Timer
#define TIMER_24H	0

void init(){
	//Ampeln auf Hauptstraﬂe
	DDRB |= (1<<DDB0);	//rot
	DDRB |= (1<<DDB1);	//gelb	
	DDRB |= (1<<DDB2);	//gruen
	//Ampeln auf Nebenstraﬂe und Fussgaenger
	DDRC |= (1<<DDC0);	//rot
	DDRC |= (1<<DDC1);	//gelb
	DDRC |= (1<<DDC2);	//gruen
	//Taster Fussgaengerampel
	//DDRD |= (1<<DDD7);
	//Taster f¸r Magnetsensoratrappe
	DDRD |= (1<<DDD6);
	
	//Ampeln auf Hauptstraﬂe
	PORTB &= (1<<PORTB0);	//rot
	PORTB &= (1<<PORTB1);	//gelb
	PORTB &= (1<<PORTB2);	//gruen
	//Ampeln auf Nebenstraﬂe und Fussgaenger
	PORTC &= (1<<PORTC0);	//rot
	PORTC &= (1<<PORTC1);	//gelb
	PORTC &= (1<<PORTC2);	//gruen
	//Taster Fussgaengerampel
	PORTD &= (1<<PORTD7);
	//Taster fuer Magnetsensoratrappe
	PORTD &= (1<<PORTD6);
	
	//timer einstellen
	TCNT0 = 6;
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	TCCR0B |= ((1<<CS01) | (1<<CS00)); //prescaler 64
	TIMSK0 |= (1<<TOIE0);
		
	//timer einstellen
	TCNT1 = 9286;
	TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
	TCCR1B |= ((1<<CS12) | (1<<CS10)); //prescaler 1024
	TIMSK1 |= (1<<TOIE1);
}
#endif /* DEFINES_H_ */
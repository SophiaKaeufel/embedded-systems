/*
 * uart.h
 *
 * Created: 02.12.2021 13:52:55
 *  Author: kem45324
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL

#define BAUDRATE 9600
#define BAUD_CONST (((F_CPU/(BAUDRATE*16UL)))-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "functions.h"
	
void USART_Transmit(unsigned char data);	
	
void printMenu(const char string[]){
	char s = '0';
	for(uint8_t i = 0; s != '\0'; ++i){
		s = pgm_read_byte(string + i);
		USART_Transmit(s);
	}
}

void printUI(uint32_t val){
	uint8_t i;
	char c, arr[12] = "";
	
	//convert unsigned long data type to string data type; char *ultoa(long N, char *str, int base);
	ultoa(val, arr, 10);
	
	//Print val
	for(i = 0; i < 12; i++){
		c = arr[i];
		USART_Transmit(c);
	}
	//USART_Transmit(0x0d);
}

//Init
void USART_Init(){
	UBRR0H = (BAUD_CONST >> 8);
	UBRR0L = BAUD_CONST;
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}


void USART_Transmit(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))) ;
	UDR0 = data;
}

unsigned char USART_Receive(){
	while(!(UCSR0A & (1<<RXC0))) ;
	return UDR0;
}

#endif /* UART_H_ */
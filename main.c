/*
 * maestro_entregable.c
 *
 * Created: 7/31/2024 11:03:49 AM
 * Author : sarax
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "spi.h"

void USART_Init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char USART_Receive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void displayOnLEDs(uint8_t value) {
	PORTC = (value & 0x3F); // Output to the first 6 bits (C0 to C5)
	if (value & 0x40) {
		PORTD |= (1 << PD2); // Set D2 if needed
		} else {
		PORTD &= ~(1 << PD2); // Clear D2 if needed
	}
	if (value & 0x80) {
		PORTD |= (1 << PD3); // Set D3 if needed
		} else {
		PORTD &= ~(1 << PD3); // Clear D3 if needed
	}
}

int main(void) {
	USART_Init(103); // 9600 baud rate
	SPI_MasterInit();
	DDRC = 0x3F; // Set PORTC0 to PORTC5 as output
	DDRD = (1 << PD2) | (1 << PD3); // Set PORTD2 and PORTD3 as output
	
	while (1) {
		PORTB &= ~(1 << PORTB2); // Pull SS low

		uint8_t pot1 = SPI_MasterTransmit(0xFF); // Send dummy byte to receive pot1
		_delay_ms(10);
		uint8_t pot2 = SPI_MasterTransmit(0xFF); // Send dummy byte to receive pot2

		PORTB |= (1 << PORTB2); // Pull SS high

		USART_Transmit(pot1); // Send pot1 to computer
		USART_Transmit(pot2); // Send pot2 to computer

		uint8_t counter = USART_Receive(); // Receive counter from computer
		displayOnLEDs(counter); // Display counter on LEDs

		_delay_ms(100);
	}
}

/*
 * ADC.c
 *
 * Created: 7/31/2024 11:02:27 AM
 *  Author: sarax
 */ 

#include "adc.h"

void ADC_Init(void) {
	ADMUX = (1 << REFS0); // AVcc with external capacitor at AREF pin
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}

uint16_t ADC_Read(uint8_t channel) {
	channel &= 0x07; // Select ADC channel between 0-7
	ADMUX = (ADMUX & 0xF8) | channel;
	ADCSRA |= (1 << ADSC); // Start conversion
	while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
	return ADCW;
}

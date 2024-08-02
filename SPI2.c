/*
 * SPI.c
 *
 * Created: 8/2/2024 11:06:16 AM
 *  Author: sarax
 */ 

#include "spi.h"

void SPI_MasterInit(void) {
	// Set MOSI, SCK, and SS as output, MISO as input
	DDRB = (1 << DDB3) | (1 << DDB5) | (1 << DDB2);
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t SPI_MasterTransmit(uint8_t cData) {
	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	// Return received data
	return SPDR;
}

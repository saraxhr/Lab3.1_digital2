/*
 * SPI.c
 *
 * Created: 7/31/2024 11:02:51 AM
 *  Author: sarax
 */ 

#include "spi.h"

void SPI_MasterInit(void) {
	DDRB = (1 << DDB3) | (1 << DDB5) | (1 << DDB2); // Set MOSI, SCK, SS as output
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);  // Enable SPI, Master, set clock rate fck/16
}

uint8_t SPI_MasterTransmit(uint8_t data) {
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

void SPI_SlaveInit(void) {
	DDRB = (1 << DDB4); // Set MISO as output
	SPCR = (1 << SPE);  // Enable SPI
}

uint8_t SPI_SlaveReceive(void) {
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

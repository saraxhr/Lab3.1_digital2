/*
 * SPI.h
 *
 * Created: 8/2/2024 11:06:38 AM
 *  Author: sarax
 */ 


#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

// Initializes the SPI as Master
void SPI_MasterInit(void);

// Transmits a byte through SPI and receives a byte
uint8_t SPI_MasterTransmit(uint8_t cData);

#endif // SPI_H

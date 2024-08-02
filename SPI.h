/*
 * SPI.h
 *
 * Created: 7/31/2024 11:03:10 AM
 *  Author: sarax
 */ 


#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void SPI_MasterInit(void);
uint8_t SPI_MasterTransmit(uint8_t data);
void SPI_SlaveInit(void);
uint8_t SPI_SlaveReceive(void);

#endif

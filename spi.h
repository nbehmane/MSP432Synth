/*
 * spi.h
 *
 *  Created on: May 8, 2021
 *      Author: Nima Behmanesh
 */

#ifndef SPI_H_
#define SPI_H_
#include "msp.h"
#include "my_gpio.h"


#define CLK BIT5 // Port 1.5 CLK bit
#define DATAOUT BIT6 // Port 1.6 Data
#define FUNCSEL1 (~(BIT5|BIT6))
#define FUNCSEL0 (BIT5|BIT6)
#define CONFIG_BITS 0x30
#define MASK_MSB 0x00FF



void setupSPI(void);
void transmit(uint16_t data);


#endif /* SPI_H_ */

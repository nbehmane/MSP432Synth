/*
 * my_gpio.h
 *
 *  Created on: Apr 7, 2021
 *      Author: Nima Behmanesh
 */

#ifndef MY_GPIO_H_
#define MY_GPIO_H_
#include "msp.h"

void createOutputEven(DIO_PORT_Even_Interruptable_Type* PORT,
                      uint16_t BIT);

void createOutputOdd(DIO_PORT_Odd_Interruptable_Type* PORT,
                     uint16_t BIT);

void createInputEven(DIO_PORT_Even_Interruptable_Type* PORT,
                     uint16_t BIT, uint8_t res);

void createInputOdd(DIO_PORT_Odd_Interruptable_Type* PORT,
                    uint16_t BIT, uint8_t res);

void setOutEven(DIO_PORT_Even_Interruptable_Type* PORT, uint16_t BIT,
                uint8_t out);

void setOutOdd(DIO_PORT_Odd_Interruptable_Type* PORT, uint16_t BIT,
               uint8_t out);


#endif /* MY_GPIO_H_ */

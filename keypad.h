/*
 * keypad.h
 *
 *  Created on: Apr 12, 2021
 *      Author: Nima Behmanesh
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "msp.h"
#include "my_gpio.h"

#define DEBOUNCE 100000

#define COL0 1
#define COL1 2
#define COL2 4
#define COL3 8

#define ROW0 1
#define ROW1 2
#define ROW2 4
#define ROW3 8

void setupKeypadPorts(void);
uint8_t detectKeyPress(void);
void keyPress(uint8_t *r, uint8_t *c);
uint8_t getChar(uint8_t row, uint8_t col);
void debounce(void);



#endif /* KEYPAD_H_ */

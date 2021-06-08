/*
 * wave.h
 *
 *  Created on: May 30, 2021
 *      Author: Nima Behmanesh
 */

#ifndef WAVE_H_
#define WAVE_H_
#include "msp.h"
#include "keypad.h"
#include "lcd.h"


uint16_t get_next_value(uint8_t wave_select);
void change_wave(uint8_t *wave_select);



#endif /* WAVE_H_ */

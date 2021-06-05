/*
 * flag.h
 *
 *  Created on: May 18, 2021
 *      Author: Nima Behmanesh
 */

#ifndef FLAG_H_
#define FLAG_H_
#include "msp.h"

void set_flag(uint8_t bit);
void clear_flag(uint8_t bit);
uint8_t check_flag(uint8_t bit);
void toggle_flag(uint8_t bit);

#endif /* FLAG_H_ */


/*
 * flag.c
 *
 *  Created on: May 18, 2021
 *      Author: Nima Behmanesh
 */
#include "flag.h"
static uint8_t flag = 0;

void set_flag(uint8_t bit)
{
    flag |= bit;
}

void clear_flag(uint8_t bit)
{
    flag &= ~bit;
}

uint8_t check_flag(uint8_t bit)
{
    if (flag & bit)
        return 1;
    return 0;
}

void toggle_flag(uint8_t bit)
{
    flag ^= bit;
}

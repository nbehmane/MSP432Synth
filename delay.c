/*
 * delay.c
 *
 *  Created on: Apr 5, 2021
 *      Author: Nima Behmanesh
 */
#include "delay.h"

void setup_DCO(uint32_t freq, uint8_t div)
{
    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = freq;
    CS->CTL1 |= CS_CTL1_SELM__DCOCLK | CS_CTL1_DIVM__1;

    if (div)
        CS->CTL1 |= CS_CTL1_SELS__DCOCLK | CS_CTL1_DIVS__2;
    else
        CS->CTL1 |= CS_CTL1_SELS__DCOCLK | CS_CTL1_DIVS__1;

    CS->KEY = 0;
}

void delay_us(uint32_t delay)
{
    uint32_t i = 0;
    switch(CS->CTL0)
    {

        case FREQ_1_5MHZ:
            for (; i < delay / 8; i++)
                __delay_cycles(1);
            break;
        case FREQ_3MHZ:
            for (; i < delay / 6; i++)
                __delay_cycles(0);
            break;
        case FREQ_6MHZ:
            for (; i < (delay / 2); i++)
                __delay_cycles(1);
            break;
        case FREQ_12MHZ:
            for (; i < delay; i++)
                __delay_cycles(1);
            break;
        case FREQ_24MHZ:
            for (; i < delay; i++)
                __delay_cycles(14);
            break;

        default:
            for (; i < delay; i++)
                __delay_cycles(13);
            break;
    }
}

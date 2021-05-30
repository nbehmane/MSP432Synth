/*
 * my_gpio.c
 * Contains functions to create input and output pins.
 * Contains functions to set output pins high or low.
 *
 *
 *  Created on: Apr 7, 2021
 *      Author: Nima Behmanesh
 */
#include "my_gpio.h"


/* createOutputEven
 * Input: Even port number on the MPS432P401R and a BIT#(s)
 * Output: Sets the pin at the specified port as an output
 */
void createOutputEven(DIO_PORT_Even_Interruptable_Type* PORT,
                      uint16_t BIT)
{
    PORT->SEL0 &= ~(BIT); // Setting up for outputs
    PORT->SEL1 &= ~(BIT);
    PORT->DIR |= BIT;
}

/* createOutputOdd
 * Input: Odd port number on the MPS432P401R and a BIT#(s)
 * Output: Sets the pin at the specified port as an output
 */
void createOutputOdd(DIO_PORT_Odd_Interruptable_Type* PORT,
                     uint16_t BIT)
{
    PORT->SEL0 &= ~(BIT); // Setting up for outputs
    PORT->SEL1 &= ~(BIT);
    PORT->DIR |= BIT;
}


/* createInputEven
 * Input: Even port number on the MPS432P401R, BIT#(s), and resistor pull mode
 *      (res | 0 = Pull-down resistor, 1 = Pull-up resistor)
 * Output: Sets the pin at the specified port as an input with a pull resistor
 */
void createInputEven(DIO_PORT_Even_Interruptable_Type* PORT,
                     uint16_t BIT, uint8_t res)
{
    PORT->SEL1 &= ~BIT;
    PORT->SEL0 &= ~BIT;
    PORT->DIR &= ~BIT;
    PORT->REN |= BIT; // Enables Resistor
    if (res == 0)
        PORT->OUT &= ~BIT;  // Enables pulldown resistor
    else
        PORT->OUT |= BIT; // Enables pullup resistor
}

/* createInputOdd
 * Input: Odd port number on the MPS432P401R, BIT#(s), and resistor pull mode
 *      (res | 0 = Pull-down resistor, 1 = Pull-up resistor)
 * Output: Sets the pin at the specified port as an input with a pull resistor
 */
void createInputOdd(DIO_PORT_Odd_Interruptable_Type* PORT, uint16_t BIT,
                    uint8_t res)
{
    PORT->SEL1 &= ~BIT;
    PORT->SEL0 &= ~BIT;
    PORT->DIR &= ~BIT; // Sets DIRection to output
    PORT->REN |= BIT; // Enables Resistor
    if (res == 0)
        PORT->OUT &= ~BIT;  // Enables pull-down resistor
    else
        PORT->OUT |= BIT; // Enables pull-up resistor
}

/* setOutEven
 * Input: Even port number on the MPS432P401R, BIT#(s), and out value
 * (0 = output set low, 1 = output set high)
 * Output: Sets the pin at the specified port high or low
 */
void setOutEven(DIO_PORT_Even_Interruptable_Type* PORT, uint16_t BIT,
                uint8_t out)
{
    if (out == 1)
        PORT->OUT |= BIT;
    else
        PORT->OUT &= ~BIT;
}

/* setOutOdd
 * Input: Odd port number on the MPS432P401R, BIT#(s), and out value
 * (out | 0 = output set low, 1 = output set high)
 * Output: Sets the pin at the specified port high or low
 */
void setOutOdd(DIO_PORT_Odd_Interruptable_Type* PORT, uint16_t BIT,
               uint8_t out)
{
    if (out == 1)
        PORT->OUT |= BIT;
    else
        PORT->OUT &= ~BIT;
}

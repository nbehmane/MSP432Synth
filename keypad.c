/*
 * keypad.c
 * Contains functions to detect keypad inputs.
 * Contains functoins to parse keypad inputs.
 *
 *  Created on: Apr 12, 2021
 *      Author: Nima Behmanesh
 */
#include "keypad.h"
#include "delay.h"

/*
 * debounce
 * Input: void
 * Output: debounces keypad input to avoid repeating keyboard inputs
 */
void debounce(void)
{
    delay_us(DEBOUNCE);
    delay_us(DEBOUNCE);
    delay_us(DEBOUNCE);
}

/* SUBJECT TO CHANGE -> See note below
 * setupKeypadPorts
 * Input: void
 * Output: Sets all input and output pins necessary for keypad functionality
 *
 * Note: Currently this function takes no inputs.
 * This function will be rewritten to allow any ports to be used for the keypad.
 * This will be implemented to allow more general support and dynamic design.
 *
 */
void setupKeypadPorts(void)
{
    createOutputEven(P4, (BIT0|BIT1|BIT2|BIT3)); // rows
    createInputEven(P6, (BIT4|BIT5|BIT6|BIT7), 0); // columns
}

/*
 * detectKeyPress
 * Input: void
 * Output: Will return 1 if a key press is detected, 0 otherwise.
 */
// Notice: P6 is shifted to right 4 bits, this is because we are using bits 4-7 for 6.
uint8_t detectKeyPress(void)
{
    setOutEven(P4, (BIT0|BIT1|BIT2|BIT3), 1);

    // Notice: P6 is shifted to right 4 bits, this is because we are using bits 4-7 for 6.
    if ((P6->IN >> 4) > 0)
        return 1;
    else
        return 0;
}


/*
 * keyPress
 * Input: Row and Column pointers. These values will be updated with
 * the row and column numbers that results in the key press and key value
 * Output: This function returns nothing, however, updates the Row and Column
 * pointers with the key value
 */
void keyPress(uint8_t *r, uint8_t *c)
{
    uint8_t i = 0;
    setOutEven(P4, (BIT0|BIT1|BIT2|BIT3), 0); // Turn all the outputs off
    for (i = 0; i < 4; i++)
    {
        // Notice: P6 is shifted to right 4 bits, this is because we are using bits 4-7 for 6.
        // Notice: P4 is &'d with 0xF since the upper bits of P4 are being used.
        // Take this out if P4 is only used for the keypad.

        // set the pin at i in P4 high
        setOutEven(P4, 1 << i, 1);

        // Check if there is a row that goes high
        if ((P6->IN >> 4) > 0)
        {
            *c= P6->IN >> 4; // column is set
            *r = P4->OUT & 0xF; // row is set.
            setOutEven(P4, 1 << i, 0);
            break;
        }
        setOutEven(P4, 1 << i, 0);
    }
}

/*
 * getChar
 * Input: Row and Column value pretaining to a specific key
 * Output: The ascii character value that coincides with a Row and Column value
 */
char getChar(uint8_t row, uint8_t col)
{
    switch(row)
    {
    case ROW0:
        if (col == COL0)
            return '1';
        if (col == COL1)
            return '2';
        if (col == COL2)
            return '3';
        if (col == COL3)
            return 'A';
        break;
    case ROW1:
        if (col == COL0)
            return '4';
        if (col == COL1)
            return '5';
        if (col == COL2)
            return '6';
        if (col == COL3)
            return 'B';
    case ROW2:
        if (col == COL0)
            return '7';
        if (col == COL1)
            return '8';
        if (col == COL2)
            return '9';
        if (col == COL3)
            return 'C';
    case ROW3:
        if (col == COL0)
            return '*';
        if (col == COL1)
            return '0';
        if (col == COL2)
            return '#';
        if (col == COL3)
            return 'D';
    }
    return '\0';
}


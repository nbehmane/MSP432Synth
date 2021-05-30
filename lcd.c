/*
 * lcd.c
 * Contains functions to properly setup and initialize LCD
 * Contains functions to write data, commands, to the LCD
 *
 *  Created on: Apr 10, 2021
 *      Author: Nima Behmanesh
 */
#include "lcd.h"

/* SUBJECT TO CHANGE -> see note below
 * setupPorts
 * Input: void
 * Output: Sets output data pins for LCD
 *
 * Note: Currently this function takes in void, which means that
 * the data pins are hardcoded. Soon, this function will take in
 * general BIT#'s allowing a more general setup method and dynamic design.
 *
 */
void setupPorts(void)
{
    // Creates outputs for our data bits to the LCD
    createOutputEven(P4, (BIT4|BIT5|BIT6|BIT7));
    //creates RS RW and E respectively
    createOutputOdd(P3, (BIT5|BIT6|BIT7));
}

/*
 * writeCmd
 * Input: A command according to the HITACHI data sheet, cmd, and
 * binary value sendTwice, that will send a command once or twice according
 * to the function set.
 * Output: Void
 *
 * If sendTwice is 1, this will send a function in two 4 bit parts,
 * starting with the MSB of cmd. If sendTwice is 0 then only the 4 MSB of
 * cmd is sent to the LCD.
 */
void writeCmd(uint8_t cmd, uint8_t sendTwice)
{
    P4->OUT = cmd; // send the first nibble of the command (4 MSB)
    P3->OUT &= ~RS;
    P3->OUT &= ~RW;
    delay_us(DELAY);
    P3->OUT |= E;
    delay_us(DELAY);
    P3->OUT &= ~E;
    delay_us(DELAY);
    P3->OUT |= RS;
    P3->OUT |= RW;

    if (sendTwice == 1)
    {
        P4->OUT = cmd << 4; // send the second nibble of the command
        P3->OUT &= ~RS;
        P3->OUT &= ~RW;
        delay_us(DELAY);
        P3->OUT |= E;
        delay_us(DELAY);
        P3->OUT &= ~E;
        delay_us(DELAY);
        P3->OUT |= RS;
        P3->OUT |= RW;
    }
}

/*
 * writeData
 * Input: 8-bit data to be sent, data
 * Output: Void
 */
void writeData(uint8_t data)
{
    P4->OUT = data; // send the first nibble of data (upper bits of P4)
    P3->OUT |= RS;
    P3->OUT &= ~RW;
    delay_us(DELAY);
    P3->OUT |= E;
    delay_us(DELAY);
    P3->OUT &= ~E;
    delay_us(DELAY);
    P3->OUT |= RS;
    P3->OUT |= RW;

    P4->OUT = data << 4; // send the lower nibble of data
    P3->OUT |= RS;
    P3->OUT &= ~RW;
    delay_us(DELAY);
    P3->OUT |= E;
    delay_us(DELAY);
    P3->OUT &= ~E;
    delay_us(DELAY);
    P3->OUT |= RS;
    P3->OUT |= RW;
}

/*
 * initLCD
 * Input: void
 * Output: void
 * Function to initialize the LCD
 */
void initLCD(void)
{
    setupPorts();

    delay_us(15000);
    writeCmd(DEFAULTFUNCSET, 0);
    delay_us(42000);
    writeCmd(DEFAULTFUNCSET, 0);
    delay_us(1000);
    writeCmd(DEFAULTFUNCSET, 0);

    writeCmd(0x20, 0);

    writeCmd(FUNCSET, 1); // Function set
    writeCmd(DISPOFF, 1); // Display off
    writeCmd(CLEARLCD, 1); // display clear
    writeCmd(ENTRY, 1); // entry mode
    writeCmd(CURSOR, 1); // cursor settings

}

/*
 * writeChar
 * Input: An ascii value, c
 * Output: void
 * Writes the character to the LCD at the current DDRAM address
 */
void writeChar(char c)
{
    writeData(c);
}

/*
 * writeString
 * Input: A string of ascii values, and the length of the string
 * Output: void
 * Sends a string to the LCD to be displayed.
 */
void writeString(char string[], uint8_t len)
{

    uint8_t i = 0;
    for (; i < len; i++)
        writeData(string[i]);
}

/*writeCharOffset
 *Input: A character c, and an offset amount to set the DDRAM
 *Output: Void
 * Sets a character at the specified location "offset"
 */
void writeCharOffset(char c, uint8_t offset)
{
    moveCursor(offset);
    writeData(c);
}

/* writeStringOffset
 * Input: A string of characters, string, the length of the string, len, and
 * the offset amount to set DDRAM address, offset.
 * Output: Void
 * Writes a string of a certain length at the address specified by the offset.
 *
 */
void writeStringOffset(char string[], uint8_t len, uint8_t offset)
{
    moveCursor(offset);
    uint8_t i = 0;
    for (; i < len; i++)
        writeData(string[i]);
}

/* clearLCD
 * Input: void
 * Output: void
 * Clears the LCD
 *
 */
void clearLCD(void)
{
    writeCmd(CLEARLCD, 1);
}

/* homeLCD
 * Input: void
 * Output: void
 * Sets the DDRAM cursor back to 0x0
 *
 */
void homeLCD(void)
{
    writeCmd(HOMELCD, 1);
}

/* moveCursor
 * Input: an address to set in DDRAM, addr
 * Output: void
 * sets the DDRAM address to the address specified by addr
 */
void moveCursor(uint8_t addr)
{
    writeCmd(MOVECURSOR(addr), 1);
}
























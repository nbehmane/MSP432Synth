/*
 * lcd.h
 *
 *  Created on: Apr 10, 2021
 *      Author: Nima Behmanesh
 */

#ifndef LCD_H_
#define LCD_H_
#include "msp.h"
#include "delay.h"
#include "my_gpio.h"
#define SECONDLINE 0x40
#define FIRSTLINE 0x0
#define CLEARLCD 0x01
#define DISPOFF  0x08
#define ENTRY    0x06
#define FUNCSET  0x28
#define CURSOR   0x0D
#define HOMELCD  0x02
#define MOVECURSOR(x) (0x80 | (x))
#define RS BIT5
#define RW BIT6
#define E  BIT7
#define DEFAULTFUNCSET 0x30

void initLCD(void);
void setupPorts(void);

void writeCmd(uint8_t cmd, uint8_t sendTwice);
void writeData(uint8_t data);

void homeLCD(void);
void clearLCD(void);
void moveCursor(uint8_t addr);

void writeChar(char c);
void writeString(char string[], uint8_t len);
void writeCharOffset(char c, uint8_t offset);
void writeStringOffset(char string[], uint8_t len, uint8_t offset);

#endif /* LCD_H_ */

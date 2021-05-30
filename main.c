#include "msp.h"
#include "lcd.h"

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	setupPorts();
	initLCD();

	writeChar('A');
	while(1)
	{
	    ;
	}
}

#include "msp.h"
#include "lcd.h"
#include "spi.h"
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	setupPorts();
	initLCD();
	setupSPI();
	int i = 0;


	writeChar('A');
	while(1)
	{
	    transmit(4000);
	    for (i = 0; i < 20000; i++);
	    transmit(0);
	    for (i = 0; i < 20000; i++);
	}
}

#include "msp.h"
#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "wave.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	setup_DCO(FREQ_12MHZ, NO_CLK_DIVISION);
	setupPorts();
	initLCD();
	setupSPI();


	writeString("FREQ", 5);
	while(1)
	{
	    transmit(get_next());
	}
}

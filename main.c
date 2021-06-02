#include "msp.h"
#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "wave.h"
#include "keypad.h"
#include "stdio.h"

/**
 * main.c
 */

void TA0_0_IRQHandler(void){
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; //no interrupt pending
    transmit(get_next());
}

void TA0_N_IRQHandler(void){
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG; //no interrupt pending
    printf("HIT\n");
}


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	setup_DCO(FREQ_12MHZ, NO_CLK_DIVISION);
	setupPorts();
 	initLCD();
	setupSPI();
	setupKeypadPorts();

	writeString("FREQ", 5);

	//Set up TIMER_A0 interrupts
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; //TACCR0 interrupt enabled
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;
//    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; //Enable sleep on exit from ISR

    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE; //TACCR1 interrupt enabled
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;

    TIMER_A0->CCR[0] = 271;
    TIMER_A0->CCR[1] = 271;

    //Enable interrupts
    __enable_irq();
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
    NVIC->ISER[0] |= 1 << ((TA0_N_IRQn) & 31);

    while (1)
    {
        if (detectKeyPress())
        {
            ;
        }
    }

//    while(1)
//	{
//        //PSEUDOCODE
//        switch(buttonPressed){
//            case "C4":
//                TIMER_A0->CCR[0] = 455;
//            case "C#4":
//                TIMER_A0->CCR[0] = 430;
//            case "D4":
//                TIMER_A0->CCR[0] = 405;
//            case "D#4":
//                TIMER_A0->CCR[0] = 383;
//            case "E4":
//                TIMER_A0->CCR[0] = 361;
//            case "F4":
//                TIMER_A0->CCR[0] = 341;
//            case "F#4":
//                TIMER_A0->CCR[0] = 322;
//            case "G4":
//                TIMER_A0->CCR[0] = 304;
//            case "G#4":
//                TIMER_A0->CCR[0] = 287;
//            case "A4":
//                TIMER_A0->CCR[0] = 271;
//            case "A#4":
//                TIMER_A0->CCR[0] = 255;
//            case "B4":
//                TIMER_A0->CCR[0] = 240;
//        }
//
//	}
}



/*
 * spi.c
 *
 *  Created on: May 8, 2021
 *      Author: Nima Behmanesh
 */
#include "spi.h"

void setup_SPI()
{
    createOutputOdd(P5, BIT1); // CS bit

    P1->SEL0 |= FUNCSEL0;
    P1->SEL1 &= FUNCSEL1;

    EUSCI_B0_SPI->CTLW0 |= EUSCI_B_CTLW0_SWRST;

    EUSCI_B0_SPI->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK | // Set the SMCLK as the source clk
                           EUSCI_B_CTLW0_MODE_0 | // 3-pin SPI mode (One parent, one child)
                           EUSCI_B_CTLW0_MST | // Select the MSP to be the master device.
                           EUSCI_B_CTLW0_STEM | // Set the child enable pin to be set by the master device
                           EUSCI_B_CTLW0_MSB | // Set the MSB to go in first
                           EUSCI_B_CTLW0_CKPL | // Set the clock polarity to 1
                           EUSCI_B_CTLW0_SYNC; // Set to synchronous

    EUSCI_B0_SPI->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;
    P5->OUT |= BIT1;

}

void transmit(uint16_t data)
{
    // Drop CS
    P5->OUT &= ~BIT1;

    EUSCI_B0_SPI->TXBUF = CONFIG_BITS | (data >> 8);
    while(!(EUSCI_B0_SPI->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0_SPI->TXBUF = (data & MASK_MSB);
    while(!(EUSCI_B0_SPI->IFG & EUSCI_B_IFG_TXIFG));

    P5->OUT |= BIT1;
}

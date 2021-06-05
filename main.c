#include "msp.h"
#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "wave.h"
#include "keypad.h"
#include "flag.h"
#include "my_gpio.h"
#include "note.h"
#include "stdio.h"
#include "stdlib.h"
#define RECORDING (P3->IN & BIT0)
#define NOTE_LEN 100

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	createInputOdd(P3, BIT0, 0);
    setup_DCO(FREQ_24MHZ, NO_CLK_DIVISION);

    uint8_t r = 0;
    uint8_t c = 0;
    uint8_t period = 0;
    uint8_t still_pressed = 0;
    Note * notes = init_notes(NOTE_LEN);
    uint8_t note_index = 0;
    uint8_t playback_index = 0;
    uint32_t playback_duration = 0;

	setupKeypadPorts();
	setupPorts();
 	initLCD();
	setupSPI();
	// Initialize a single note in Notes.

	writeString("FREQ", 4);


    while (1)
    {
        if ((still_pressed = detectKeyPress()))
        {
            keyPress(&r, &c);
            period = getChar(r, c);

            if (period == '*')
            {

                for (playback_index = 0; playback_index < NOTE_LEN; playback_index++)
                {
                    for (playback_duration = 0;
                         playback_duration < notes[playback_index].duration;
                         playback_duration++)
                    {
                        delay_us(notes[playback_index].period);
                        transmit(get_next_sin_value());
                    }
                    delay_us(50);
                    transmit(0);
                }
                free(notes);
                notes = init_notes(NOTE_LEN);
                note_index = 0;
                period = 0;

            }
            delay_us(period);
            transmit(get_next_sin_value());

            if (RECORDING & period != '*')
            {
                notes[note_index].period = period;
                notes[note_index].duration += 2;
            }
            clear_flag(BIT0);

        }
        else if (still_pressed == 0 & !(check_flag(BIT0)))
        {
            if (note_index > 100 & period != '*')
                note_index = 0;
            else if (period != '*')
                note_index += 1;
            set_flag(BIT0);
        }

    }
}



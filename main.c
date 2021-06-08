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
#include "recording.h"
#define SWITCH_WAVE ('#')

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	createInputOdd(P3, BIT0, 0);
    setup_DCO(FREQ_24MHZ, NO_CLK_DIVISION);

    // row and column values for the keypad
    // TODO: Make these static variables in the keypad.c
    uint8_t row = 0;
    uint8_t col = 0;

    // Variable to hold the button value that was pressed for the keypad.
    // Also holds the period for the software delay to transmit the wave
    //      for a given note.
    uint8_t user_cmd = 0;

    // A variable to store whether or not a key was pressed and detected.
    uint8_t still_pressed = 0;

    // Initializes an array of type Note
    // Holds all the note values for a recording.
    Note * notes = init_notes(NOTE_LEN);

    // Indexes into the notes array for a particular note.
    uint8_t note_index = 0;

    // Variable to keep track of what wave is currently selected.
    uint8_t wave_select = 0;

	setupKeypadPorts(); // Set up all the pins for the keypad
	setupPorts(); // Sets up ports for the LCD
 	initLCD(); // Initializes the LCD for operation
	setupSPI(); // Set up the SPI to transit values to the DAC

	writeString("WELCOME TO SYNTH", 17);
	delay_us(1000);


    while (1)
    {
        // We store still_pressed to ensure that when a user continuously
        // presses a key that a frequency is outputted and if not, to stop
        // outputting.
        if ((still_pressed = detectKeyPress()))
        {
            /// update the row and col values to grab the right period/cmd value
            keyPress(&row, &col);

            // get the period/cmd value that the row and col values map to
            user_cmd = getChar(row, col);

            // Check to see if we're recording after a user has pressed a key.
            // This happens only after the key is released to minimize the time
            // it takes to transmit a value. Otherwise the frequency of the
            // notes will be incorrect.
            if (!check_flag(BIT1))
            {
                if (RECORDING)
                    writeStringOffset("RECORDING        ", 17, SECONDLINE);
                else
                    writeStringOffset("NOT RECORDING    ", 17, SECONDLINE);
            }

            // If the playback button is pressed then play it back the
            // current recording.
            if (user_cmd == PLAYBACK_BTN)
            {
                playback(notes, wave_select);

                // Make sure to free the memory after playback, so that we can
                // initialize more. This is to ensure that we don't have
                // memory leaks.
                free_recording(notes, &note_index, &user_cmd);
            }
            else if (user_cmd == SWITCH_WAVE)
                change_wave(&wave_select);

            // Delay this loop the proper amount of time for a given note.
            // NOTE: user_cmd holds commands a period values
            delay_us(user_cmd);

            // Transmit the hardcoded wave values to the DAC
            transmit(get_next_value(wave_select));

            // Set BIT1 such that we don't continuously write to the LCD.
            // If this wasn't here then our entire program would slow down
            // and cause low frequency outputs that may not be heard.
            set_flag(BIT1);

            // If the record switch is switched, then store the note
            // and increment the note_index for the next note.
            recording(user_cmd, notes, note_index);


        }
        // If a key isn't being pressed, and BIT0 isn't set
        // then increment the note
        else if (still_pressed == NO & !(check_flag(BIT0)))
        {
            if (note_index > NOTE_LEN & user_cmd != PLAYBACK_BTN)
                note_index = 0;
            else if (user_cmd != PLAYBACK_BTN)
                note_index += 1;

            // By setting BIT0 we are saying that a new note must be
            // recorded before calling this else if block will be run.
            set_flag(BIT0);

            // Let the display update upon the next keypress.
            clear_flag(BIT1);
        }

    }
}



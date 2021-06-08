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

    uint8_t row = 0;
    uint8_t col = 0;
    uint8_t user_cmd = 0;
    uint8_t still_pressed = 0;
    Note * notes = init_notes(NOTE_LEN);
    uint8_t note_index = 0;
    uint8_t wave_select = 0;

	setupKeypadPorts();
	setupPorts();
 	initLCD();
	setupSPI();

	writeString("WELCOME TO SYNTH", 17);
	delay_us(1000);


    while (1)
    {
        if ((still_pressed = detectKeyPress()))
        {
            keyPress(&row, &col);
            user_cmd = getChar(row, col);
            if (!check_flag(BIT1))
            {
                if (RECORDING)
                    writeStringOffset("RECORDING        ", 17, SECONDLINE);
                else
                    writeStringOffset("NOT RECORDING    ", 17, SECONDLINE);
            }

            if (user_cmd == RECORD_BTN)
            {
                playback(notes, wave_select);
                free_recording(notes, &note_index, &user_cmd);
            }
            else if (user_cmd == SWITCH_WAVE)
                change_wave(&wave_select);

            delay_us(user_cmd);
            transmit(get_next_value(wave_select));
            set_flag(BIT1);
            recording(user_cmd, notes, note_index);


        }
        else if (still_pressed == NO & !(check_flag(BIT0)))
        {
            if (note_index > NOTE_LEN & user_cmd != RECORD_BTN)
                note_index = 0;
            else if (user_cmd != RECORD_BTN)
                note_index += 1;
            set_flag(BIT0);
            clear_flag(BIT1);
        }

    }
}



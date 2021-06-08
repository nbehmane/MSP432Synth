/*
 * recording.c
 *
 *  Created on: Jun 7, 2021
 *      Author: Nima Behmanesh
 */
#include "recording.h"

void recording(uint8_t period, Note *notes, uint8_t note_index)
{
    if (RECORDING & period != '*')
    {
        notes[note_index].period = period;
        notes[note_index].duration += 2;
    }
    clear_flag(BIT0);
}

void playback(Note *notes)
{
    uint8_t playback_index = 0;
    uint32_t playback_duration = 0;

    for (playback_index = 0; playback_index < NOTE_LEN; playback_index++)
    {
        for (playback_duration = 0;
             playback_duration < notes[playback_index].duration;
             playback_duration++)
        {
            delay_us(notes[playback_index].period);
            transmit(get_next_sin_value());
        }
        delay_us(BREAK_NOTE);
        transmit(0);
    }

}

void free_recording(Note *notes, uint8_t *note_index, uint8_t *period)
{
    free(notes);
    notes = init_notes(NOTE_LEN);
    *note_index = 0;
    *period = 0;
}


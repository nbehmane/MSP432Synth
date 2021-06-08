/*
 * recording.c
 *
 *  Created on: Jun 7, 2021
 *      Author: Nima Behmanesh
 */
#include "recording.h"

/*
 * INPUT| uint8_t period    : a note value or a user command
 *        Note *notes       : an array to store notes
 *        uint8_t note_index: an index in notes to store a note
 *
 * OUTPUT| void
 *
 * Description: stores a note in notes to be played back.
 *  Stores a rough estimate of the total time a user pressed that note.
 *  Clears BIT0 to indicate that a note has been recorded.
 */
void recording(uint8_t period, Note *notes, uint8_t note_index)
{
    if (RECORDING & period != PLAYBACK_BTN)
    {
        notes[note_index].period = period;
        notes[note_index].duration += 2;
    }
    clear_flag(BIT0);
}

/*
 * INPUT| Note *notes        : An array of recorded notes.
 *        uint8_t wave_select: a value to represent the wave that
 *          should be used for playback.
 * OUTPUT| void.
 *
 * Description: Plays back through the notes.
 */
void playback(Note *notes, uint8_t wave_select)
{
    uint16_t playback_index = 0;
    uint32_t playback_duration = 0;

    // Indicate that playback is happening on the LCD
    delay_us(1000);
    writeStringOffset("PLAYING BACK", 12, SECONDLINE);

    // Playback loop
    for (playback_index = 0; playback_index < NOTE_LEN; playback_index++)
    {
        for (playback_duration = 0;
             playback_duration < notes[playback_index].duration;
             playback_duration++)
        {
            delay_us(notes[playback_index].period);
            transmit(get_next_value(wave_select));ss
        }
        // delay a break between the notes.
        delay_us(BREAK_NOTE);

        // transmit nothing after taking the break.
        transmit(0);
    }

    // Indicate that the playback is finished.
    writeStringOffset("DONE            ", 17, SECONDLINE);
}


// Free the old recording, and initialize new memory for a new recording.
void free_recording(Note *notes, uint8_t *note_index, uint8_t *period)
{
    free(notes);
    notes = init_notes(NOTE_LEN);
    *note_index = 0;
    *period = 0;
}


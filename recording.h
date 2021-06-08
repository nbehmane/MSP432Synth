/*
 * recording.h
 *
 *  Created on: Jun 7, 2021
 *      Author: Nima Behmanesh
 */

#ifndef RECORDING_H_
#define RECORDING_H_
#include "msp.h"
#include "flag.h"
#include "delay.h"
#include "note.h"
#include "wave.h"
#include "stdlib.h"
#include "spi.h"
#include "lcd.h"

#define RECORDING (P3->IN & BIT0)
#define NOTE_LEN 100
#define BREAK_NOTE 1000
#define PLAYBACK_BTN ('*')
#define YES 1
#define NO 0

void recording(uint8_t period, Note *notes, uint8_t note_index);
void playback(Note *notes, uint8_t wave_select);
void free_recording(Note *notes, uint8_t *note_index, uint8_t *period);


#endif /* RECORDING_H_ */

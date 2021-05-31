/*
 * note.c
 *
 *  Created on: May 31, 2021
 *      Author: Gary Huarng
 */
#include "msp.h"
#include "note.h"
#include "string.h"

typedef struct Note {
    char[4] name; //Ex. {'C', '#', '4', '\0'}
    uint16_t freq;
    uint16_t duration;
} Note;

Note  C4 = {name =  "C4",  freq = 262, duration = 0};
Note Cs4 = {name = "C#4",  freq = 277, duration = 0};
Note  D4 = {name =  "D4",  freq = 294, duration = 0};
Note Ds4 = {name = "D#4",  freq = 311, duration = 0};
Note  E4 = {name =  "E4",  freq = 330, duration = 0};
Note  F4 = {name =  "F4",  freq = 349, duration = 0};
Note Fs4 = {name = "F#4",  freq = 370, duration = 0};
Note  G4 = {name =  "G4",  freq = 392, duration = 0};
Note Gs4 = {name = "G#4",  freq = 415, duration = 0};
Note  A4 = {name =  "A4",  freq = 440, duration = 0};
Note As4 = {name = "A#4",  freq = 466, duration = 0};
Note  B4 = {name =  "B4",  freq = 494, duration = 0};


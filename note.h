/*
 * note.h
 *
 *  Created on: May 31, 2021
 *      Author: Gary
 */

#ifndef NOTE_H_
#define NOTE_H_

typedef struct Note {
    char[4] name; //Ex. {'C', '#', '4', '\0'}
    uint16_t freq;
    uint16_t duration;
} Note;

extern Note C4;
extern Note Cs4;
extern Note D4;
extern Note Ds4;
extern Note E4;
extern Note F4;
extern Note Fs4;
extern Note G4;
extern Note Gs4;
extern Note A4;
extern Note As4;
extern Note B4;

#endif /* NOTE_H_ */

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

#endif /* NOTE_H_ */

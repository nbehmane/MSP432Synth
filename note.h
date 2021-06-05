/*
 * note.h
 *
 *  Created on: May 31, 2021
 *      Author: Gary
 */

#ifndef NOTE_H_
#define NOTE_H_

typedef struct Note{
    uint16_t period;
    uint32_t duration;
} Note;

Note * init_notes(uint16_t len);
#endif /* NOTE_H_ */

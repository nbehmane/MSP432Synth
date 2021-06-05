/*
 * note.c
 *
 *  Created on: May 31, 2021
 *      Author: Gary Huarng
 */
#include "msp.h"
#include "note.h"
#include "stdlib.h"
Note * init_notes(uint16_t len)
{
    uint16_t i = 0;
    Note * notes = malloc(len * sizeof(Note));
    for (; i < len; i++)
    {
        notes[i].period = 0;
        notes[i].duration = 0;
    }
    return notes;
}

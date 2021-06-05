/*
 * wave.c
 *
 *  Created on: May 30, 2021
 *      Author: Nima Behmanesh
 */
#include "wave.h"

static uint8_t index = 0;

static uint16_t sin_list[100] =
{    1861,1979,2096,2213,2328,2441,2552,2660,2765,2867,
     2964,3057,3145,3228,3305,3376,3442,3501,3553,3599,
     3638,3669,3693,3710,3719,3721,3716,3703,3682,3654,
     3619,3577,3528,3472,3410,3341,3267,3187,3101,3011,
     2916,2816,2713,2607,2497,2385,2270,2155,2037,1920,
     1801,1684,1566,1451,1336,1224,1114,1008,905,805,
     710,620,534,454,380,311,249,193,144,102,67,39,18,
     5,0,2,11,28,52,83,122,168,220,279,345,416,493,576,
     664,757,854,956,1061,1169,1280,1393,1508,1625,1742,
     1861
};


uint16_t get_next_sin_value(void)
{
    uint16_t output = 0;
    if (index > 99) index = 0;
    output = sin_list[index];
    index += 1;
    return output;
}

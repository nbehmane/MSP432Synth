/*
 * dac.h
 *
 *  Created on: May 10, 2021
 *      Author: Nima Behmanesh
 */

#ifndef DAC_H_
#define DAC_H_
#include "msp.h"
#include "keypad.h"

#define FREQ_500Hz 243
#define FREQ_400Hz 303
#define FREQ_300Hz 404
#define FREQ_200Hz 605
#define FREQ_100Hz 1210

#define NO_SQUARE_FLAG 0
#define SQUARE_FLAG 1
#define WAVE_LENGTH 99
#define SQUARE_WAVE_LENGTH 2

#define SQUARE_100Hz 60000
#define SQUARE_100Hz_MIN 12000
#define SQUARE_100Hz_MAX 108000

#define SQUARE_200Hz 30000
#define SQUARE_200Hz_MIN 6000
#define SQUARE_200Hz_MAX 54000

#define SQUARE_300Hz 20000
#define SQUARE_300Hz_MIN 4000
#define SQUARE_300Hz_MAX 36000

#define SQUARE_400Hz 15000
#define SQUARE_400Hz_MIN 3000
#define SQUARE_400Hz_MAX 27000

#define SQUARE_500Hz 12050
#define SQUARE_500Hz_MIN 2410
#define SQUARE_500Hz_MAX 21690

#define AMP_UP 0
#define AMP_DOWN 1

struct Wave
{

    uint8_t squareFlag;
    uint32_t squareFreq;
    uint32_t squarePeriod;
    uint32_t squarePeriod2;
    uint32_t squareMax;
    uint32_t squareMin;
    uint32_t squareStep;

    uint8_t square100Hz;
    uint32_t square100HzCount;
    uint16_t lastFreq;


    uint16_t period;
    uint16_t period2;
    uint16_t *currWave;

    uint16_t count;
    uint8_t amp;
};

void waveInit(struct Wave *wave, uint16_t waveList[]);

void changeSquareWave(struct Wave *wave, uint32_t freq,
                      uint32_t squareMin, uint32_t squareMax,
                      uint16_t waveFreq);

void setWave(uint16_t count, uint8_t squareFlag,
             uint16_t *waveList, struct Wave *wave);

void checkSquareFlag(struct Wave *wave);

void increaseDutyCycle(struct Wave *wave);

void decreaseDutyCycle(struct Wave *wave);

void changeWavePeriod(struct Wave *wave, uint16_t period, uint8_t square);

void interruptDAC(struct Wave *wave, uint16_t *count);

void dacWaveChanger(uint8_t r, uint8_t c, uint16_t *squareList,
                    uint16_t *sinList, uint16_t *sawList,
                    struct Wave *wave);

void changeAmp(struct Wave *wave, uint8_t up);

#endif /* DAC_H_ */

/*
 * dac.c
 *
 *  Created on: May 10, 2021
 *      Author: Nima Behmanesh
 */
#include "dac.h"

/*
 * Initializes the Wave struct. This is only called on startup
 * to display the 100Hz squareWave.
 */
void waveInit(struct Wave *wave, uint16_t waveList[])
{
    wave->currWave = waveList; // The current wave
    wave->count = 2; // The number of points in a wave.

    /*
     * squarePeriod and squarePeriod2 are used to
     * set variable duty cycles.
     */
    wave->squarePeriod = SQUARE_100Hz;
    wave->squarePeriod2 = SQUARE_100Hz;

    /*
     * These are important for duty cycle functionality.
     * the square flag tells main that a squareWave is currently
     * being used.
     *
     * squareMax and squareMin are the min and max times for
     * duty cycles of a specific frequency
     * squareStep is how much to increment the duty cycle (10% each time)
     *
     */
    wave->squareFreq = SQUARE_100Hz;
    wave->squareFlag = SQUARE_FLAG;
    wave->squareMax = SQUARE_100Hz_MAX;
    wave->squareMin = SQUARE_100Hz_MIN;
    wave->squareStep = SQUARE_100Hz_MIN;


    /*
     * period and period2 are used to trigger interrupts.
     * for all waves.
     */
    wave->period = wave->squarePeriod;
    wave->period2 = wave->squarePeriod2;

    /*
     * The square wave at 100Hz is a special case,
     * so it has it's own flag.
     *
     * square100HzCount is used to keep a software timer.
     * Once this reaches the actual timer value, a value is triggered.
     */
    wave->square100Hz = 1;
    wave->square100HzCount = 0;

    /*
     * This is the last frequency set, so that when you switch
     * to another wave, the frequency is held.
     */
    wave->lastFreq = FREQ_100Hz;

    /*
     * This is the shift amount used to change the amplitude of a wave.
     */
    wave->amp = 0;
}


/*
 * changes the squareWave to a different frequency.
 */
void changeSquareWave(struct Wave *wave, uint32_t freq,
                      uint32_t squareMin, uint32_t squareMax,
                      uint16_t waveFreq)
{
    wave->squarePeriod = freq;
    wave->squarePeriod2 = freq;
    wave->squareFreq = freq;

    wave->squareMax = squareMax;
    wave->squareMin = squareMin;
    wave->squareStep = squareMin;
    wave->lastFreq = waveFreq;


    if (freq == SQUARE_100Hz)
        wave->square100Hz = 1;
    else
        wave->square100Hz = 0;
}

/*
 * sets the next wave to be displayed. if the square flag is given,
 * then it lets main know to take the square wave flow.
 */
void setWave(uint16_t count, uint8_t squareFlag,
             uint16_t *waveList, struct Wave *wave)
{
    wave->currWave = waveList;
    wave->count = count;
    wave->squareFlag = squareFlag;

    if (wave->squareFlag)
    {
        wave->period = wave->squarePeriod;
        wave->period2 = wave->squarePeriod2;
    }
}

/*
 * A function that changes the period if a squareFlag has been set.
 * This is due to the fact that the squareWave does not behave the
 * same way as the other waves.
 */
void checkSquareFlag(struct Wave *wave)
{
    if (wave->squareFlag)
    {
        wave->period = wave->squarePeriod;
        wave->period2 = wave->squarePeriod2;
    }
    else
    {
        wave->period = wave->lastFreq;
        wave->period2 = wave->lastFreq;
    }

}

void increaseDutyCycle(struct Wave *wave)
{
    if (!(wave->squarePeriod == wave->squareMin))
    {
        wave->squarePeriod -= wave->squareStep;
        wave->squarePeriod2 += wave->squareStep;
    }
    debounce();
}

void decreaseDutyCycle(struct Wave *wave)
{
    if (!(wave->squarePeriod == wave->squareMax))
    {
        wave->squarePeriod += wave->squareStep;
        wave->squarePeriod2 -= wave->squareStep;
    }
    debounce();
}


/*
 * This will change the period of a wave to a different one.
 * if the squareFlag is set then the squarePeriods are updated
 */
void changeWavePeriod(struct Wave *wave, uint16_t period, uint8_t square)
{
    if (!square)
    {
        wave->period = period;
        wave->period2 = period;
    }
    else
    {
        wave->squarePeriod = wave->squareFreq;
        wave->squarePeriod2 = wave->squareFreq;
    }

}


/*
 * Interrupt sequence for a wave and a squareWave.
 */
void interruptDAC(struct Wave *wave, uint16_t *count)
{
    if (wave->square100Hz & wave->squareFlag)
    {
        if (wave->square100HzCount == 120000)
        {
            wave->square100HzCount = 0;
            *count = 0;
        }
        else if (wave->square100HzCount <= wave->squarePeriod2)
        {
            wave->square100HzCount += 300;
            *count = 0;
        }
        else if (wave->square100HzCount - wave->squarePeriod2 < wave->squarePeriod)
        {
            wave->square100HzCount += 300;
            *count = 1;
        }
        TIMER_A0->CCR[0] = 300;
    }
    else if (*count % 2)
        TIMER_A0->CCR[0] = wave->period;
    else
        TIMER_A0->CCR[0] = wave->period2;
}

/*
 * changes the frequency and wave displayed when a button is pressed on the
 * keypad.
 */
void dacWaveChanger(uint8_t r, uint8_t c, uint16_t *squareList,
                    uint16_t *sinList, uint16_t *sawList,
                    struct Wave *wave)
{
    switch(getChar(r, c))
    {
    case '9':
        setWave(WAVE_LENGTH, NO_SQUARE_FLAG, sawList, wave);
        break;
    case '8':
        setWave(WAVE_LENGTH, NO_SQUARE_FLAG, sinList, wave);
        break;
    case '7':
        setWave(SQUARE_WAVE_LENGTH, SQUARE_FLAG, squareList, wave);
        break;
    case '0':
        changeWavePeriod(wave, 0, SQUARE_FLAG);
        break;
    case '1':
        changeSquareWave(wave, SQUARE_100Hz, SQUARE_100Hz_MIN,
                         SQUARE_100Hz_MAX, FREQ_100Hz);
        changeWavePeriod(wave, FREQ_100Hz, NO_SQUARE_FLAG);
        break;
    case '2':
        changeSquareWave(wave, SQUARE_200Hz, SQUARE_200Hz_MIN,
                         SQUARE_200Hz_MAX, FREQ_200Hz);
        changeWavePeriod(wave, FREQ_200Hz, NO_SQUARE_FLAG);
        break;
    case '3':
        changeSquareWave(wave, SQUARE_300Hz, SQUARE_300Hz_MIN,
                         SQUARE_300Hz_MAX, FREQ_300Hz);
        changeWavePeriod(wave, FREQ_300Hz, NO_SQUARE_FLAG);
        break;
    case '4':
        changeSquareWave(wave, SQUARE_400Hz, SQUARE_400Hz_MIN,
                         SQUARE_400Hz_MAX, FREQ_400Hz);
        changeWavePeriod(wave, FREQ_400Hz, NO_SQUARE_FLAG);
        break;
    case '5':
        changeSquareWave(wave, SQUARE_500Hz, SQUARE_500Hz_MIN,
                         SQUARE_500Hz_MAX, FREQ_500Hz);
        changeWavePeriod(wave, FREQ_500Hz, NO_SQUARE_FLAG);
        break;
    case '*':
        decreaseDutyCycle(wave);
        break;
    case '#':
        increaseDutyCycle(wave);
        break;
    case 'A':
        changeAmp(wave, AMP_UP);
        break;
    case 'B':
        changeAmp(wave, AMP_DOWN);
        break;

    default: break;
    }
}

void changeAmp(struct Wave *wave, uint8_t up)
{
    if (up & wave->amp <= 4)
        wave->amp += 1;
    else if (!up & wave->amp > 0)
        wave->amp -= 1;
    debounce();
}









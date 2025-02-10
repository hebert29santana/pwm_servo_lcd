#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
// #include "ws2818b.pio.h"

#define LED_PIN 7
#define LED_COUNT 25

typedef struct pixel_t {
    uint8_t G, R, B;
} pixel_t;

//extern pixel_t leds[LED_COUNT];
//extern PIO np_pio;
//extern uint sm;

extern const uint8_t MATRIZ_LEDS[5][5];
extern const uint8_t NUMBER_PATTERNS[10][5][5];

void npInit(uint pin);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b, uint8_t intensity);
void npWrite();
void npClear();
void displayNumber(int number);

#endif // MATRIX_H

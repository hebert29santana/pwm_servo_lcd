#ifndef SERVO_DISPLAY_H
#define SERVO_DISPLAY_H

#include "displayLCD.h"

// Função para desenhar o servo motor no display
void draw_servo(ssd1306_t *ssd, uint8_t angle);

// Função para sincronizar o LED RGB com o ângulo do servo
void update_rgb_led(uint8_t angle);

// Declaração da função set_led_color
void set_led_color(uint8_t vermelho, uint8_t verde, uint8_t azul);

#endif // SERVO_DISPLAY_H
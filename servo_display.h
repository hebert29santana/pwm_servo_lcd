#ifndef SERVO_DISPLAY_H
#define SERVO_DISPLAY_H

#include "ssd1306.h"
#include <stdbool.h>

// Definições do I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Tamanho do display
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// Declarações das funções
void init_display(ssd1306_t *ssd);
void display_message(ssd1306_t *ssd, const char *line1, const char *line2);

// Função para desenhar o servo motor no display
void draw_servo(ssd1306_t *ssd, uint8_t angle);

// Função para sincronizar o LED RGB com o ângulo do servo
void update_rgb_led(uint8_t angle);

// Declaração da função set_led_color
void set_led_color(uint8_t vermelho, uint8_t verde, uint8_t azul);

#endif // SERVO_DISPLAY_H
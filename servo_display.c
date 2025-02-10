#include "servo_display.h"
#include "pico/stdlib.h"
#include <math.h> // Para usar sinf e cosf
#include <stdio.h>

// Função para exibir o ângulo no display
void display_angle(ssd1306_t *ssd, uint8_t angle) {
    char buffer[16]; // Buffer para armazenar a string formatada
    sprintf(buffer, "Angulo: %d", angle); // Formata a string com o ângulo
    ssd1306_draw_string(ssd, buffer, 0, 50); // Exibe a string no display (posição x=0, y=50)
}

// Função para converter graus em radianos
float to_radians(uint8_t degrees) 
{
    return degrees * M_PI / 180.0f;
}

// Função para interpolar linearmente entre duas cores
uint8_t interpolate_color(uint8_t start, uint8_t end, float t) 
{
    return (uint8_t)(start + (end - start) * t);
}

// Função para desenhar o servo motor no display
void draw_servo(ssd1306_t *ssd, uint8_t angle) 
{
    // Limpa o display
    ssd1306_fill(ssd, false);

    // Desenha o corpo do servo (retângulo)
    ssd1306_rect(ssd, 20, 30, 40, 20, true, false); // Corpo do servo

    // Desenha o braço do servo (linha)
    uint8_t arm_x = 50; // Posição X do braço
    uint8_t arm_y = 30; // Posição Y do braço
    uint8_t arm_length = 35; // Comprimento do braço

    // Calcula a posição final do braço com base no ângulo
    float radians = to_radians(angle);
    uint8_t end_x = arm_x + (arm_length * cosf(radians));
    uint8_t end_y = arm_y - (arm_length * sinf(radians));

    // Desenha o braço
    ssd1306_line(ssd, arm_x, arm_y, end_x, end_y, true);

    // Exibe o ângulo no display
    display_angle(ssd, angle);

    // Atualiza o display
    ssd1306_send_data(ssd);
}

// Função para sincronizar o LED RGB com o ângulo do servo
void update_rgb_led(uint8_t angle) 
{
    uint8_t red, green, blue;

       if (angle <= 60) {
            // Transição de Azul (0, 0, 255) para Verde (0, 255, 0)
            float t = angle / 60.0f; // Fator de interpolação (0 a 1)
            red = 0;
            green = interpolate_color(0, 255, t);
            blue = interpolate_color(255, 0, t);
        } else if (angle <= 120) {
            if (angle == 90) {
                red = 0;
                green = 255;
                blue = 0;
            } else {
                    // Transição de Verde (0, 255, 0) para Amarelo (255, 255, 0)
                    float t = (angle - 90) / 30.0f; // Fator de interpolação (0 a 1)
                    red = interpolate_color(0, 255, t);
                    green = 255;
                    blue = 0;
                }
            } else if (angle <= 180) {
                    // Transição de Amarelo (255, 255, 0) para Vermelho (255, 0, 0)
                    float t = (angle - 120) / 60.0f; // Fator de interpolação (0 a 1)
                    red = 255;
                    green = interpolate_color(255, 0, t);
                    blue = 0;
                } else {
                    // Vermelho (255, 0, 0)
                    red = 255;
                    green = 0;
                    blue = 0;
                }           

        // Define a cor do LED RGB
        set_led_color(red, green, blue);
}
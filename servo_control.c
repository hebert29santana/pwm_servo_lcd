#include "servo_control.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22 // GPIO 22 para o servo

void set_servo_pulse_width(uint16_t pulse_width_us) {
    // Configura o PWM para gerar um pulso de largura específica em microssegundos
    uint16_t wrap = 39062; // Período de 20ms (50Hz) com clock de 125MHz e divisor de 64
    uint16_t level = (pulse_width_us * wrap) / 20000; // Converte microssegundos para nível PWM

    pwm_set_gpio_level(SERVO_PIN, level);
}
/*
    Hebert Costa Vaz Santana
    TIC370101235
    Grupo 7
*/

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo_display.h"
#include "servo_control.h" // Inclua o arquivo de controle do servo
#include "matrix.h"

#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define LED_VERMELHO_PIN 13

#define SERVO_PIN 22

// Função para controlar o LED RGB
void set_led_color(uint8_t vermelho, uint8_t verde, uint8_t azul) {
    pwm_set_gpio_level(LED_VERMELHO_PIN, vermelho);
    pwm_set_gpio_level(LED_VERDE_PIN, verde);
    pwm_set_gpio_level(LED_AZUL_PIN, azul);
}

// Função para contagem regressiva na matriz de LEDs
void countdown() {
    for (int i = 5; i > 0; i--) {
        displayNumber(i); // Exibe o número na matriz de LEDs
        sleep_ms(1000);  // Espera 1 segundo
    }
    npClear(); // Limpa a matriz de LEDs após a contagem
}

int main() {
    npInit(LED_PIN);

    // Incializa o Pino para o Servo Motor
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num_servo = pwm_gpio_to_slice_num(SERVO_PIN);

    // Configura o PWM do Servo
    pwm_config config_servo = pwm_get_default_config();
    pwm_config_set_clkdiv(&config_servo, 64.f); // Divisor de clock para 50Hz
    pwm_config_set_wrap(&config_servo, 39062);  // Período de 20ms
    pwm_init(slice_num_servo, &config_servo, true);

    // Configura os pinos do LED RGB como saída PWM
    gpio_set_function(LED_VERDE_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_AZUL_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_VERMELHO_PIN, GPIO_FUNC_PWM);

    // Configura o PWM para os LEDs
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f); // Divisor de clock para maior resolução
    pwm_config_set_wrap(&config, 255); // Período de 8 bits (0-255)
    pwm_init(pwm_gpio_to_slice_num(LED_VERDE_PIN), &config, true);
    pwm_init(pwm_gpio_to_slice_num(LED_AZUL_PIN), &config, true);
    pwm_init(pwm_gpio_to_slice_num(LED_VERMELHO_PIN), &config, true);
    
    // Inicializa o display
    ssd1306_t ssd;
    init_display(&ssd);

    // 1. Configura a frequência do PWM para 50Hz (período de 20ms)
    // Isso já é feito na função set_servo_pulse_width.

    // 2. Posiciona o servo em 180° (2400µs)
    set_servo_pulse_width(2400);
    draw_servo(&ssd, 180);
    update_rgb_led(180);
    //sleep_ms(5000);
    countdown();

    // 3. Posiciona o servo em 90° (1470µs)
    set_servo_pulse_width(1470);
    draw_servo(&ssd, 90);
    update_rgb_led(90);
    //sleep_ms(5000);
    countdown();

    // 4. Posiciona o servo em 0° (500µs)
    set_servo_pulse_width(500);
    draw_servo(&ssd, 0);
    update_rgb_led(0);
    //sleep_ms(5000);
    countdown();

    // 5. Movimentação periódica suave entre 0° e 180°

    // Loop principal
     while (true) {
        for (uint8_t angle = 0; angle <= 180; angle += 1) {
            uint16_t pulse_width = 500 + (angle * 10); // Calcula o pulso PWM
            set_servo_pulse_width(pulse_width); // Move o servo
            draw_servo(&ssd, angle); // Desenha o servo no display
            update_rgb_led(angle); // Atualiza o LED RGB
            sleep_ms(10); // Atraso de 10ms
        }

        for (uint8_t angle = 180; angle > 0; angle -= 1) {
            uint16_t pulse_width = 500 + (angle * 10); // Calcula o pulso PWM
            set_servo_pulse_width(pulse_width); // Move o servo
            draw_servo(&ssd, angle); // Desenha o servo no display
            update_rgb_led(angle); // Atualiza o LED RGB
            sleep_ms(10); // Atraso de 10ms
        }
    }
}
// PWM.c
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "lib/pwm.h"
#include <stdio.h>
#include <stdint.h>
#include "temp/default.h"
//variables para slinces.
uint slice_left_int1;
uint slice_left_int2;

uint slice_right_int1;
uint slice_right_int2;


void motores_init(void){
    ///Configurar pines de PWM para ambos motores
    ///Motor izquierdo
    gpio_set_function(MOTOR_LEFT_PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_LEFT_DIR_PIN, GPIO_FUNC_PWM);

    //Motor derecho
    gpio_set_function(MOTOR_RIGHT_PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_RIGHT_DIR_PIN, GPIO_FUNC_PWM);

    //Slices para ambos motores
    slice_left_int1 = pwm_gpio_to_slice_num(MOTOR_LEFT_PWM_PIN);
    slice_left_int2 = pwm_gpio_to_slice_num(MOTOR_LEFT_DIR_PIN);

    slice_right_int1 = pwm_gpio_to_slice_num(MOTOR_RIGHT_PWM_PIN);
    slice_right_int2 = pwm_gpio_to_slice_num(MOTOR_RIGHT_DIR_PIN);

    //Configurar wrap para ambos motores
    pwm_set_wrap(slice_left_int1, PWM_MAX_DUTY_CYCLE);
    pwm_set_wrap(slice_left_int2, PWM_MAX_DUTY_CYCLE);

    pwm_set_wrap(slice_right_int1, PWM_MAX_DUTY_CYCLE);
    pwm_set_wrap(slice_right_int2, PWM_MAX_DUTY_CYCLE);

    //Habilitar PWM para ambos motores
    pwm_set_enabled(slice_left_int1, true);
    pwm_set_enabled(slice_left_int2, true);

    pwm_set_enabled(slice_right_int1, true);
    pwm_set_enabled(slice_right_int2, true);

    //Divisores para ambos motores
    pwm_set_clkdiv(slice_left_int1, 125.0f); // Divisor para motor izquierdo
    pwm_set_clkdiv(slice_left_int2, 125.0f); // Divisor para motor izquierdo

    pwm_set_clkdiv(slice_right_int1, 125.0f); // Divisor para motor derecho
    pwm_set_clkdiv(slice_right_int2, 125.0f); // Divisor para motor derecho

    ///inicia
    pwm_set_gpio_level(MOTOR_LEFT_PWM_PIN, 0);
    pwm_set_gpio_level(MOTOR_LEFT_DIR_PIN, 0);

    pwm_set_gpio_level(MOTOR_RIGHT_PWM_PIN, 0);
    pwm_set_gpio_level(MOTOR_RIGHT_DIR_PIN, 0);
}

void motor_set_speed(uint motor, float speed){
    bool reverse = (speed < 0);
    if (reverse)
    speed = -speed; // Asegurar que speed sea positivo para el cálculo del duty cycle

    if (speed > VELOCIDAD_MAX)
        speed = VELOCIDAD_MAX; // Limitar la velocidad al máximo permitido
    
    uint level = (uint)(speed * PWM_MAX_DUTY_CYCLE / VELOCIDAD_MAX); // Calcular el duty cycle proporcional a la velocidad

    /// Colfiguracion del motor izquierdo.
    if(motor == 1){
        if (!reverse) {
            
            // Adelante
            pwm_set_chan_level(
                slice_left_int1,
                pwm_gpio_to_channel(MOTOR_LEFT_PWM_PIN),
                level
            );

            pwm_set_chan_level(
                slice_left_int2,
                pwm_gpio_to_channel(MOTOR_LEFT_DIR_PIN),
                0
            );
        }else{
            // Atrás
            pwm_set_chan_level(
                slice_left_int1,
                pwm_gpio_to_channel(MOTOR_LEFT_PWM_PIN),
                0
            );

            pwm_set_chan_level(
                slice_left_int2,
                pwm_gpio_to_channel(MOTOR_LEFT_DIR_PIN),
                level
            );
        }
    }

        // Configuración del motor derecho.
        else if(motor == 2){
            if (!reverse) {
                // Adelante
                pwm_set_chan_level(
                    slice_right_int1,
                    pwm_gpio_to_channel(MOTOR_RIGHT_PWM_PIN),
                    level
                );

                pwm_set_chan_level(
                    slice_right_int2,
                    pwm_gpio_to_channel(MOTOR_RIGHT_DIR_PIN),
                    0
                );
            }else{
                // Atrás
                pwm_set_chan_level(
                    slice_right_int1,
                    pwm_gpio_to_channel(MOTOR_RIGHT_PWM_PIN),
                    0
                );

                pwm_set_chan_level(
                    slice_right_int2,
                    pwm_gpio_to_channel(MOTOR_RIGHT_DIR_PIN),
                    level
                );
            }
        }
    }
//Control de dirección del motor.
void mover (float left, float right){
    motor_set_speed(1, left);
    motor_set_speed(2, right);
}
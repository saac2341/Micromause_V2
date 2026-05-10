// PWM.c
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "lib/pwm.h"
#include <stdio.h>
#include <stdint.h>
#include "temp/default.h"
//variables para slinces.
uint slice_left;
uint slice_right;


void motores_init(void){
    //Configuracion de pines con PWM.
    gpio_set_function(MOTOR_LEFT_PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_RIGHT_PWM_PIN, GPIO_FUNC_PWM);

    ///Configuracion de pines de dirección.
    gpio_init(MOTOR_LEFT_DIR_PIN);
    gpio_set_dir(MOTOR_LEFT_DIR_PIN, GPIO_OUT);

    gpio_init(MOTOR_RIGHT_DIR_PIN);
    gpio_set_dir(MOTOR_RIGHT_DIR_PIN, GPIO_OUT);

   //Estados iniciales del PWM
   gpio_put(MOTOR_LEFT_DIR_PIN, 0);
   gpio_put(MOTOR_RIGHT_DIR_PIN, 0);

   //Slices para cada motor.
    slice_left = pwm_gpio_to_slice_num(MOTOR_LEFT_PWM_PIN);
    slice_right = pwm_gpio_to_slice_num(MOTOR_RIGHT_PWM_PIN);

    //Configuracion del PWM para ambos motores.
    pwm_set_wrap(slice_left, PWM_MAX_DUTY_CYCLE);
    pwm_set_wrap(slice_right, PWM_MAX_DUTY_CYCLE);

    pwm_set_clkdiv(slice_left, 125.0f); // Ajusta el divisor de reloj para obtener la frecuencia deseada
    pwm_set_clkdiv(slice_right, 125.0f); // Ajusta el divisor

    // Establecer el nivel inicial del PWM a 0 (motor detenido).
    pwm_set_chan_level(
        slice_left,
        pwm_gpio_to_channel(MOTOR_LEFT_PWM_PIN),
        0
    );

    pwm_set_chan_level(
        slice_right,
        pwm_gpio_to_channel(MOTOR_RIGHT_PWM_PIN),
        0
    );

    ///Habilitar el PWM para ambos motores.
    pwm_set_enabled(slice_left, true);
    pwm_set_enabled(slice_right, true);

}

void motor_set_speed(uint motor, float speed){
    int reverse = (speed < 0);

    if(speed < 0) speed = -speed;

    if(speed > VELOCIDAD_MAX) speed = VELOCIDAD_MAX;

    uint level = (uint)(speed * PWM_MAX_DUTY_CYCLE / VELOCIDAD_MAX);

    if (motor == 1) { // IZQUIERDO

        //Configurar dirección
        gpio_put(MOTOR_LEFT_DIR_PIN, reverse);

        pwm_set_chan_level(
            slice_left,
            pwm_gpio_to_channel(MOTOR_LEFT_PWM_PIN),
            level
        );
} 
else if(motor == 2) { // DERECHO

        //Configurar dirección
        gpio_put(MOTOR_RIGHT_DIR_PIN, reverse);

        pwm_set_chan_level(
            slice_right,
            pwm_gpio_to_channel(MOTOR_RIGHT_PWM_PIN),
            level
        );
    }
}

//Control de dirección del motor.
void mover (float left, float right){
    motor_set_speed(1, left);
    motor_set_speed(2, right);
}
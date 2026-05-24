/*Programa encargado de gestionar la dirección del micromouse a traves de los pines del puente h*/

#include "lib/direccion.h"
#include "pico/stdlib.h"  
#include "temp/default.h"
#include "lib/pwm.h"
#include "lib/encoder.h"
#include "lib/monitor.h"

/// Inicializa los pines de dirección del micromouse, configurándolos como salidas.
void direccion_init() {
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
        gpio_put(PICO_DEFAULT_LED_PIN, 1); // Encender el LED integrado
}
void direccion_izquierda() {
    direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
    sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan completamente
    motor_set_speed(1, -VELOCIDAD_MEDIA); // Motor izquierdo a velocidad media
    motor_set_speed(2, VELOCIDAD_MEDIA); // Motor derecho detenido      
}
void direccion_derecha() {
   direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
   sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan completamente
   motor_set_speed(1, VELOCIDAD_MEDIA); // Motor izquierdo detenido
   motor_set_speed(2, -VELOCIDAD_MEDIA); // Motor derecho a velocidad media
}
void direccion_adelante() {
    direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
    sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan
    direccion_recto(); // Ir hacia adelante utilizando ambos motores a la misma velocidad
}
void direccion_atras() {
    direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
    sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan completamente
    motor_set_speed(1, -VELOCIDAD_MEDIA); // Motor izquierdo a velocidad máxima en reversa
    motor_set_speed(2, -VELOCIDAD_MEDIA); // Motor derecho a velocidad máxima en reversa
}
void direccion_parar() {
    motor_set_speed(1, 0); // Detener motor izquierdo
    motor_set_speed(2, 0); // Detener motor derecho
}
void direccion_recto() {
    static int32_t last_left_steps = 0;
    static int32_t last_right_steps = 0;
    
    encoder_data_t data = encoder_leer();

    int32_t vel_left = data.left_steps - last_left_steps;
    int32_t vel_right = data.right_steps - last_right_steps;

    // Actualizar los pasos anteriores
    last_left_steps = data.left_steps;
    last_right_steps = data.right_steps;

    int32_t error = vel_left - vel_right;
    float kp = 0.5f; // Ganancia proporcional para la corrección

    int correction = (int)(kp * error);

    int pwm_left = VELOCIDAD_MEDIA - correction;
    int pwm_right = VELOCIDAD_MEDIA + correction;

    if (pwm_left > VELOCIDAD_MAX) pwm_left = VELOCIDAD_MAX;
    if (pwm_right > VELOCIDAD_MAX) pwm_right = VELOCIDAD_MAX;

    if (pwm_left < 0) pwm_left = 0;
    if (pwm_right < 0) pwm_right = 0;

    motor_set_speed(1, pwm_left);
    motor_set_speed(2, pwm_right);
}
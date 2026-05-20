/*Programa encargado de gestionar la dirección del micromouse a traves de los pines del puente h*/

#include "lib/direccion.h"
#include "pico/stdlib.h"  
#include "temp/default.h"
#include "lib/pwm.h"

/// Inicializa los pines de dirección del micromouse, configurándolos como salidas.
void direccion_init() {
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
        gpio_put(PICO_DEFAULT_LED_PIN, 1); // Encender el LED integrado
}
void direccion_izquierda() {
    motor_set_speed(1, -VELOCIDAD_MEDIA); // Motor izquierdo a velocidad media
    motor_set_speed(2, VELOCIDAD_MEDIA); // Motor derecho detenido      
}
void direccion_derecha() {
   motor_set_speed(1, VELOCIDAD_MEDIA); // Motor izquierdo detenido
   motor_set_speed(2, -VELOCIDAD_MEDIA); // Motor derecho a velocidad media
}
void direccion_adelante() {
    motor_set_speed(1, VELOCIDAD_MAX); // Motor izquierdo a velocidad máxima
    motor_set_speed(2, VELOCIDAD_MAX); // Motor derecho a velocidad máxima
}
void direccion_atras() {
    motor_set_speed(1, -VELOCIDAD_MAX); // Motor izquierdo a velocidad máxima en reversa
    motor_set_speed(2, -VELOCIDAD_MAX); // Motor derecho a velocidad máxima en reversa
}
void direccion_parar() {
    motor_set_speed(1, 0); // Detener motor izquierdo
    motor_set_speed(2, 0); // Detener motor derecho
}
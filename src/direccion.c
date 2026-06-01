/*Programa encargado de gestionar la dirección del micromouse a traves de los pines del puente h*/

#include "lib/direccion.h"
#include "pico/stdlib.h"  
#include "temp/default.h"
#include "lib/pwm.h"
#include "lib/encoder.h"
#include "lib/monitor.h"
#include <stdlib.h>
#include <stdio.h>

/// Inicializa los pines de dirección del micromouse, configurándolos como salidas.
void direccion_init() {
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
        gpio_put(PICO_DEFAULT_LED_PIN, 1); // Encender el LED integrado
}
void direccion_izquierda() {
    direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
    sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan completamente
    motor_set_speed(1, -VELOCIDAD_MAX); // Motor izquierdo a velocidad media
    motor_set_speed(2, VELOCIDAD_MEDIA); // Motor derecho detenido      
}
void direccion_derecha() {
   direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
   sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan completamente
   motor_set_speed(1, VELOCIDAD_MEDIA); // Motor izquierdo detenido
   motor_set_speed(2, -VELOCIDAD_MAX); // Motor derecho a velocidad media
}
void direccion_adelante() {
    direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
    sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan
    direccion_recto(); // Ir hacia adelante utilizando ambos motores a la misma velocidad
}
void direccion_atras() {
    direccion_parar(); // Detener antes de cambiar de dirección para evitar daños
    sleep_ms(100); // Pequeña pausa para asegurar que los motores se detengan completamente
    motor_set_speed(1, -VELOCIDAD_MAX); // Motor izquierdo a velocidad máxima en reversa
    motor_set_speed(2, -VELOCIDAD_MAX); // Motor derecho a velocidad máxima en reversa
}
void direccion_parar() {
    motor_set_speed(1, 0); // Detener motor izquierdo
    motor_set_speed(2, 0); // Detener motor derecho
}
void direccion_recto() {
    static int32_t last_left_steps = 0;
    static int32_t last_right_steps = 0;
    
    encoder_data_t data = encoder_leer();

    int32_t error = data.left_steps - data.right_steps; // Error basado en la diferencia de pasos entre las ruedas

    float kp = 0.1f; // Ganancia proporcional para la corrección

    int correction = (int)(kp * error);

   motor_set_speed(1, VELOCIDAD_MEDIA - correction); // Ajustar velocidad del motor izquierdo
   motor_set_speed(2, VELOCIDAD_MEDIA + correction); // Ajustar velocidad del motor derecho
}

int PASOS_CELDA = 200; // Número de pasos del encoder que corresponden a una celda completa, este valor debe ser calibrado según el robot y la configuración de los motores.
// Función para avanzar una celda completa, asumiendo que una celda equivale a un número específico de pasos del encoder.
void avanzar_celda() {
    encoder_reset(); // Reiniciar los contadores de pasos
    while (true){
        direccion_recto(); // Mantener la dirección recta
        encoder_data_t data = encoder_leer();
        if (data.left_steps >= PASOS_CELDA &&
        data.right_steps >= PASOS_CELDA) {
            break; // Salir del bucle cuando se haya avanzado una celda completa
        }
    }
    direccion_parar(); // Detener el movimiento una vez que se haya avanzado la celda
}

///Funciones para que gire a 90 grados a la izquierda o derecha, o para que avance o retroceda, utilizando los motores de manera adecuada para cada dirección.
#define PASOS_GIRO_90 95 // Número de pasos del encoder que corresponden a un giro de 90 grados, este valor debe ser calibrado según el robot y la configuración de los motores.
void grados_izquierda_90() {
    encoder_reset(); // Reiniciar los contadores de pasos
    while(true){
        motor_set_speed(1, -VELOCIDAD_MEDIA); // Motor izquierdo a velocidad media hacia atrás
        motor_set_speed(2, VELOCIDAD_MEDIA); // Motor derecho a velocidad media hacia adelante
        encoder_data_t data = encoder_leer();
        if (abs(data.left_steps)>= PASOS_GIRO_90 &&
        abs(data.right_steps) >= PASOS_GIRO_90) {
            break; // Salir del bucle cuando se haya girado 90 grados
        }   
    }
    direccion_parar(); // Detener el movimiento después de girar
}
void grados_derecha_90() {
    encoder_reset(); // Reiniciar los contadores de pasos
    while(true){
        motor_set_speed(1, VELOCIDAD_MEDIA); // Motor izquierdo a velocidad media hacia adelante
        motor_set_speed(2, -VELOCIDAD_MEDIA); // Motor derecho a velocidad media en reversa
        encoder_data_t data = encoder_leer();
        if (abs(data.left_steps)>= PASOS_GIRO_90 &&
        abs(data.right_steps) >= PASOS_GIRO_90) {
            break; // Salir del bucle cuando se haya girado 90 grados
        }   
    }
    direccion_parar(); // Detener el movimiento después de girar
}
#define PASOS_GIRO_180 190 // Número de pasos del encoder que corresponden a un giro de 180 grados, este valor debe ser calibrado según el robot y la configuración de los motores.
void grados_180() {
    encoder_reset(); // Reiniciar los contadores de pasos
    while(true){
        motor_set_speed(1, -VELOCIDAD_MEDIA); // Motor izquierdo a velocidad media en reversa
        motor_set_speed(2, -VELOCIDAD_MEDIA); // Motor derecho a velocidad media en reversa
        encoder_data_t data = encoder_leer();
        if (abs(data.left_steps)>= PASOS_GIRO_180 &&
        abs(data.right_steps) >= PASOS_GIRO_180) {
            break; // Salir del bucle cuando se haya girado 180 grados
        }   
    }
    direccion_parar(); // Detener el movimiento después de girar
}
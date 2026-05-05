/PROGRAMA PARA CONTROLAR LOS MOTORES/

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "temp/default.h"

int main() {
    stdio_init_all();
    direccion_init();
    motores_init();

    while (true) {
        // Prueba de movimiento hacia adelante
         direccion_adelante();
            motor_set_speed(1, VELOCIDAD_MEDIA);
            motor_set_speed(2, VELOCIDAD_MEDIA);

        // Prueba de movimiento hacia atrás
        direccion_atras(); // Velocidad media
        motor_set_speed(1, VELOCIDAD_MEDIA);
        motor_set_speed(2, VELOCIDAD_MEDIA);
        sleep_ms(2000); // Mover durante 2 segundos

        // Prueba de giro a la izquierda
        direccion_izquierda(); // Velocidad media
        motor_set_speed(1, VELOCIDAD_MEDIA);
        motor_set_speed(2, VELOCIDAD_MEDIA);
        sleep_ms(1000); // Girar durante 1 segundo

        // Prueba de giro a la derecha
        direccion_derecha(); // Velocidad media
        motor_set_speed(1, VELOCIDAD_MEDIA);
        motor_set_speed(2, VELOCIDAD_MEDIA);
        sleep_ms(1000); // Girar durante 1 segundo

        // Detener los motores
        direccion_parar();
        motor_set_speed(1, 0);
        motor_set_speed(2, 0);
        sleep_ms(2000); // Esperar antes de repetir el ciclo
    }

    return 0;
}
/*PROGRAMA PARA CONTROLAR LOS MOTORES*/

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "temp/default.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    direccion_init();
    motores_init();

    while (true) {
        // Prueba de movimiento hacia adelante
        direccion_adelante();
        printf("Adelante\n");
        sleep_ms(5000); // Mover durante 2 segundos
        // Prueba de movimiento hacia atrás
        direccion_atras(); // Velocidad media
        printf("Atrás\n");
        sleep_ms(5000); // Mover durante 2 segundos

        // Prueba de giro a la izquierda
        direccion_izquierda(); // Velocidad media
        printf("Izquierda\n");
        sleep_ms(5000); // Girar durante 2 segundos

        // Prueba de giro a la derecha
        direccion_derecha(); // Velocidad media
        printf("Derecha\n");
        sleep_ms(5000); // Girar durante 2 segundos

        // Detener los motores
        direccion_parar();
        printf("Parado\n");
        sleep_ms(5000); // Esperar antes de repetir el ciclo
    }

    return 0;
}
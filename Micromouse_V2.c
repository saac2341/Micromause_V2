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
        direccion_adelante(); // Velocidad máxima
        printf("Adelante\n");
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo
        direccion_atras(); // Velocidad media
        printf("Atrás\n");
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo
        direccion_izquierda(); // Velocidad media
        printf("Izquierda\n");
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo
        direccion_derecha(); // Velocidad media
        printf("Derecha\n");    
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo

    }

    return 0;
}
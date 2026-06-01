/*PROGRAMA PARA CONTROLAR LOS MOTORES*/

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "temp/default.h"
#include <stdio.h>
#include "lib/comunicacion.h"

int main() {
    stdio_init_all();
    direccion_init();
    motores_init();
    setup_uart();

    sleep_ms(10000); // Esperar a que se inicialice la conexión serial
    uart_puts(UART_ID, "Prueba de motores iniciada\n");

    while (true) {
        // Prueba de movimiento hacia adelante
        direccion_adelante(); // Velocidad máxima
        printf("Adelante\n");
        uart_puts(UART_ID, "Adelante\n");
        sleep_ms(5000); // Mover durante 5 segundos

        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo

        direccion_atras(); // Velocidad media
        printf("Atrás\n");
        uart_puts(UART_ID, "Atrás\n");
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo
        direccion_izquierda(); // Velocidad media
        printf("Izquierda\n");
        uart_puts(UART_ID, "Izquierda\n");
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo
        direccion_derecha(); // Velocidad media
        printf("Derecha\n");
        uart_puts(UART_ID, "Derecha\n");
        sleep_ms(5000); // Mover durante 5 segundos
        direccion_parar(); // Detener los motores
        sleep_ms(1000); // Esperar 1 segundo

    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

#include "pico/stdlib.h"

#include "lib/pwm.h"
#include "lib/direccion.h"
#include "lib/sensorinfrarrojo.h"
#include "lib/encoder.h"
#include "lib/acelerometro.h"
#include "lib/monitor.h"
#include "lib/comunicacion.h"
#include "maze_solver.h"

#include "temp/default.h"

int main() {

    stdio_init_all();
    sleep_ms(5000); // Esperar a que se inicialice la conexión serial

    // Inicializacion de motores y direccion
    motores_init();
    direccion_init();

    // Inicializacion de sensores infrarrojos
    sensor_infrarrojo_init_BACK();
    sensor_infrarrojo_init_FRONT();
    sensor_infrarrojo_init_LEFT();
    sensor_infrarrojo_init_RIGHT();

    // Inicializacion de encoder y acelerometro
    encoder_init();
    acelerometro_init();

    // Inicializacion del algoritmo del laberinto
    maze_solver_init();

    // Inicializacion UART
    setup_uart();

    // LED integrado
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // Encender LED indicando inicio
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    printf("Inicio de exploracion\n");

    while(true) {

        // Exploracion del laberinto
        flood_explore();

        printf("Centro encontrado\n");

        // Detener motores al finalizar
        direccion_parar();

        // Mantener detenido el programa
        while(true) {
            sleep_ms(1000);
        }
    }
}
#include <stdio.h>
#include <stdbool.h>

#include "pico/stdlib.h"


#include "lib/pwm.h"
#include "lib/direccion.h"
#include "lib/sensorinfrarrojo.h"
#include "lib/encoder.h"
#include "lib/acelerometro.h"
#include "lib/monitor.h"
#include "lib/button.h"
#include "lib/comunicacion.h"
#include "maze_solver.h"

#include "temp/default.h"
int main() {

    stdio_init_all();

    motores_init();
    direccion_init();

    sensor_infrarrojo_init_BACK();
    sensor_infrarrojo_init_FRONT();
    sensor_infrarrojo_init_LEFT();
    sensor_infrarrojo_init_RIGHT();

    encoder_init();
    acelerometro_init();

    maze_solver_init();

    gpio_init(BUTTON_PIN_INICIO);
    gpio_set_dir(BUTTON_PIN_INICIO, GPIO_IN);
    gpio_pull_down(BUTTON_PIN_INICIO);

    gpio_init(BUTTON_PIN_RESET);
    gpio_set_dir(BUTTON_PIN_RESET, GPIO_IN);
    gpio_pull_down(BUTTON_PIN_RESET);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    bool started = false;

    while(true) {

        // Esperando inicio
        if(!started) {

            gpio_put(PICO_DEFAULT_LED_PIN, 0);

            if(gpio_get(BUTTON_PIN_INICIO)) {

                sleep_ms(50);

                if(gpio_get(BUTTON_PIN_INICIO)) {

                    printf("Inicio de exploracion\n");

                    started = true;

                    gpio_put(PICO_DEFAULT_LED_PIN, 1);
                }
            }
        }

        // Exploracion
        else {

            flood_explore();

            printf("Centro encontrado\n");

            started = false;
        }

        // Reset
        if(gpio_get(BUTTON_PIN_RESET)) {

            sleep_ms(50);

            if(gpio_get(BUTTON_PIN_RESET)) {

                printf("Reset del laberinto\n");

                maze_solver_init();

                started = false;

                direccion_parar();

                while(gpio_get(BUTTON_PIN_RESET))
                    sleep_ms(10);
            }
        }

        sleep_ms(10);
    }
}
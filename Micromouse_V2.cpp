/*Programa de prueba encargado de verificar los sensores y detección*/

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

#include "temp/default.h"

int main() {

    stdio_init_all();

    motores_init();
    direccion_init();

    button_init();

    sensor_infrarrojo_init_BACK();
    sensor_infrarrojo_init_FRONT();
    sensor_infrarrojo_init_LEFT();
    sensor_infrarrojo_init_RIGHT();

    encoder_init();
    acelerometro_init();
    setup_uart();

    bool robot_iniciado = false;

    printf("Micromouse listo\n");
    printf("Presione el boton de inicio\n");

    // Bucle principal
    while(true){

        // ==========================
        // ESPERA DE INICIO
        // ==========================
        if(!robot_iniciado){

            direccion_parar();

            if(button_pressed(BUTTON_PIN_INICIO)){

                robot_iniciado = true;

                printf("Robot iniciado\n");

                gpio_put(PICO_DEFAULT_LED_PIN, 1);

                sleep_ms(300);
            }

            sleep_ms(20);
            continue;
        }

        // ==========================
        // BOTON RESET
        // ==========================
        if(button_pressed(BUTTON_PIN_RESET)){

            direccion_parar();

            robot_iniciado = false;

            printf("Robot detenido\n");

            gpio_put(PICO_DEFAULT_LED_PIN, 0);

            sleep_ms(300);

            continue;
        }

        // ==========================
        // LEER SENSORES
        // ==========================
        monitor_data_t data = monitor_leer_datos();

        monitor_imprimir(data);
        // ==========================
        // CONTROL DE MOVIMIENTO
        // ==========================
        if (data.ir.front) {

            direccion_adelante();

        } else if (data.ir.left) {

            direccion_izquierda();

        } else if (data.ir.right) {

            direccion_derecha();

        } else if (data.ir.back) {

            direccion_atras();

            // Evita vibraciones en reversa
            sleep_ms(200);

        } else {

            direccion_parar();
        }

        sleep_ms(100);
    }

    return 0;
}
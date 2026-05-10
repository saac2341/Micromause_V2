/*Programa para probar que funciones el algoridmo de busqueda*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "lib/sensorinfrarrojo.h"
#include "lib/encoder.h"
#include "lib/acelerometro.h"
#include "lib/monitor.h"
#include "temp/default.h"
#include "lib/maze_solver.h"

int main(){
    stdio_init_all();
  
    // Inicialización
    motores_init();
    direccion_init();
    sensor_infrarrojo_init_BACK();
    sensor_infrarrojo_init_FRONT();
    sensor_infrarrojo_init_LEFT();
    sensor_infrarrojo_init_RIGHT();
    encoder_init();
    acelerometro_init();

    maze_solver_init(); // Inicializar el laberinto

    while (true){
         ///PRENDER PIN INTEGRADO DE LAS rASPBERRY PARA INDICAR QUE EL PROGRAMA ESTA CORRIENDO
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
        gpio_put(PICO_DEFAULT_LED_PIN, 1); // Encender el LED integrado
    
        monitor_data_t data = monitor_leer_datos();
        monitor_imprimir(data); // Imprimir los datos del monitor para depuración

        update_maze_monitor(data); // Actualizar el laberinto con los datos del monitor

        static int flood_counter = 0;
        if (++flood_counter > 20) {
            flood_fill_update(); // Actualizar las distancias en el laberinto cada cierto tiempo
            flood_counter = 0;  
        }

        int next_direction = get_next_direction(data); // Determinar la siguiente dirección a tomar
        execute_move(next_direction, data); // Ejecutar el movimiento basado en la dirección y los

        if (check_color_center(data)) {
            printf("¡Centro del laberinto alcanzado!\n");
            break; // Salir del bucle si se ha alcanzado el centro
        }
        sleep_ms(100); // Pequeña pausa para estabilidad
    }
}

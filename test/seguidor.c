/*Programa de prueba encargado de verificar los sensores y 
de deteccion*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "lib/sensorinfrarrojo.h"
#include "lib/encoder.h"
#include "lib/acelerometro.h"
#include "lib/monitor.h"
#include "temp/default.h"

int main() {
    motores_init();
    direccion_init();
    sensor_infrarrojo_init_BACK();
    sensor_infrarrojo_init_FRONT();
    sensor_infrarrojo_init_LEFT();
    sensor_infrarrojo_init_RIGHT();
    encoder_init();
    acelerometro_init();
    bool roboT_iniciado = false;

    // Bucle principal
    while(true){
        stdio_init_all();
        // Leer sensores infrarrojos.
        monitor_data_t data = monitor_leer_datos();
        monitor_imprimir(data);

        // Control básico de motores basado en los sensores infrarrojos.
        if (data.ir.front) {
            direccion_adelante();
            sleep_ms(10); // Avanzar un poco antes de verificar nuevamente
        } else if (data.ir.left) {
            direccion_izquierda();
            sleep_ms(10); // estabilidad
        } else if (data.ir.right) {
            direccion_derecha();
            sleep_ms(10); // estabilidad
        } else if (data.ir.back) {
            direccion_atras();
            sleep_ms(10); // Retroceder un poco antes de verificar nuevamente
        }else{
            direccion_parar();
            sleep_ms(10); // estabilidad
        }
        sleep_ms(100); // Pequeña demora para evitar lecturas demasiado rápidas
    }

    return 0;
}
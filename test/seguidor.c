#include <stdio.h>
#include "pico/stdlib.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "lib/sensorinfrarrojo.h"
#include "lib/encoder.h"
#include "lib/acelerometro.h"
#include "lib/monitor.h"
#include "temp/default.h"
#include "lib/comunicacion.h"
#include "lib/button.h"

void setup(){
    stdio_init_all();
    sleep_ms(5000); // Esperar a que se inicialice la conexión serial


    // Inicialización
    printf("Inicializando componentes...\n");
    uart_puts(UART_ID, "Inicializando componentes...\n");
    motores_init();
    printf("Motores inicializados.\n");
    uart_puts(UART_ID, "Motores inicializados.\n");
    direccion_init();
    printf("Dirección inicializada.\n");
    uart_puts(UART_ID, "Dirección inicializada.\n");
    sensor_infrarrojo_init_BACK();
    printf("Sensor infrarrojo trasero inicializado.\n");
    uart_puts(UART_ID, "Sensor infrarrojo trasero inicializado.\n");
    sensor_infrarrojo_init_FRONT();
    printf("Sensor infrarrojo frontal inicializado.\n");
    uart_puts(UART_ID, "Sensor infrarrojo frontal inicializado.\n");
    sensor_infrarrojo_init_LEFT();
    printf("Sensor infrarrojo izquierdo inicializado.\n");
    uart_puts(UART_ID, "Sensor infrarrojo izquierdo inicializado.\n");
    sensor_infrarrojo_init_RIGHT();
    printf("Sensor infrarrojo derecho inicializado.\n");
    uart_puts(UART_ID, "Sensor infrarrojo derecho inicializado.\n");
    encoder_init();
    printf("Encoders inicializados.\n");
    uart_puts(UART_ID, "Encoders inicializados.\n");
    acelerometro_init();
    printf("Acelerómetro inicializado.\n");
    uart_puts(UART_ID, "Acelerómetro inicializado.\n");
    printf("Inicialización completa.\n");
    uart_puts(UART_ID, "Inicialización completa.\n");
    button_init();
    printf("Botones inicializados.\n");
    uart_puts(UART_ID, "Botones inicializados.\n");

}

void loop(){
    ///Activacíon por boton Inicio, luego el programa se ejecuta continuamente hasta que se presione el boton de reset.
     while (gpio_get(BUTTON_PIN_INICIO)) {
        sleep_ms(100); // Evitar consumo excesivo de CPU
    }
    while (true){
        //Funcon para monitorizar el estado del micromouse y actualizar el laberinto.
        monitor_data_t data = monitor_leer_datos();
        monitor_imprimir(data);

        //lógica de movimiento basada en los sensores infrarrojos.
        if(!data.ir.front){
            direccion_recto();
            sleep_ms(10); // Avanzar un poco antes de verificar nuevamente

        }else if(!data.ir.left){
            grados_izquierda_90();
            sleep_ms(10); // estabilidad
        }
        else if(!data.ir.right){
            grados_derecha_90();
            sleep_ms(10); // estabilidad
        }
        else if(!data.ir.back){
            direccion_atras();
            sleep_ms(10); // Retroceder un poco antes de verificar nuevamente
        }
        else {
            direccion_parar();
            sleep_ms(10); // estabilidad
        }

        sleep_ms(20); // estabilidad
    }
}

void main() {
    setup();
    loop();
    return 0;
}

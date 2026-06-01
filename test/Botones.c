/*Programa que testea los botones*/

#include "pico/stdlib.h"
#include "temp/default.h"
#include <stdio.h>
#include "lib/comunicacion.h"


void main(){
    stdio_init_all();
    setup_uart();
    sleep_ms(5000); // Esperar a que se inicialice la conexión serial
    uart_puts(UART_ID, "Prueba de botones iniciada\n");
    // Configurar los pines de los botones como entrada con pull-up
    gpio_init(BUTTON_PIN_INICIO);
    gpio_set_dir(BUTTON_PIN_INICIO, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_INICIO);

    gpio_init(BUTTON_PIN_RESET);
    gpio_set_dir(BUTTON_PIN_RESET, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_RESET);

     while (true) {
        if (!gpio_get(BUTTON_PIN_RESET)) {
            printf("Botón de reset presionado. Reiniciando programa...\n");
            uart_puts(UART_ID, "Botón de reset presionado. Reiniciando programa...\n");
            // Aquí puedes agregar la lógica para reiniciar el programa, como volver a esperar el botón de inicio
            while (gpio_get(BUTTON_PIN_INICIO)) {
                sleep_ms(100); // Evitar consumo excesivo de CPU
            }
            printf("Botón de inicio presionado. Iniciando programa...\n");
            uart_puts(UART_ID, "Botón de inicio presionado. Iniciando programa...\n");
        }
        sleep_ms(100); // Evitar consumo excesivo de CPU
    }
}
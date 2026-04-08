/*LIBREIA ENCARGADA DE GESTIONAR LOS BOTONES DE INICIO Y RESETEO*/
#include "temp/default.h"
#include "lib/button.h"
#include <stdio.h>
#include "pico/stdlib.h"

void button_init() {
    // Configurar los pines de los botones como entradas con pull-up
    gpio_init(BUTTON_PIN_INICIO);
    gpio_set_dir(BUTTON_PIN_INICIO, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_INICIO);

    gpio_init(BUTTON_PIN_RESET);
    gpio_set_dir(BUTTON_PIN_RESET, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_RESET);
}

bool button_pressed(uint pin) {
    // Leer el estado del botón (activo bajo)
    if(!gpio_get(pin)) {
        slept_ms(20); // Pequeña demora para evitar rebotes
        if(!gpio_get(pin)) {
            return true; // Botón presionado
        }
    }
    return false; // Botón no presionado
}


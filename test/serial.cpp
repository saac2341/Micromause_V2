///Serial de prueba para verificar que el microcontrolador se comunica correctamente con la computadora. Se puede usar para enviar comandos y recibir respuestas, lo que es útil para depurar y controlar el micromouse durante el desarrollo.

#include "pico/stdlib.h"
#include <stdio.h>

int main(){
    stdio_init_all();
    sleep_ms(2000); // Esperar a que se inicialice la conexión serial

    while (true){
        printf("Hola, mundo!\n"); // Enviar un mensaje por el puerto serial
        sleep_ms(1000); // Esperar 1 segundo antes de enviar el siguiente mensaje
    }
}
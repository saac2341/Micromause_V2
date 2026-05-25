///Libreria encargada de la comunicacion entre el micromouse y la computadora, permitiendo enviar datos de los sensores y recibir comandos para controlar el micromouse.
#ifndef COMUNICACION_H
#define COMUNICACION_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

void setup_uart(void);

#ifdef __cplusplus
}
#endif
#endif /* COMUNICACION_H */
































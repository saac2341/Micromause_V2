/*Libreria de gestion de botones*/
#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "pico/stdlib.h"

void button_init();
bool button_pressed(uint pin);

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H */
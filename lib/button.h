/*Libreria de gestion de botones*/
#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "pico/stdlib.h"

void button_init();
bool button_pressed(uint pin);

#endif /* BUTTON_H */
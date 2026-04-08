/*Libreria encargada de leer el sensor infrarrojo*/

#ifndef SENSORINFRARROJO_H
#define SENSORINFRARROJO_H

#include <stdbool.h>

void sensor_infrarrojo_init_BACK();
bool infrarrojo_leer_BACK(void);

void sensor_infrarrojo_init_FRONT();
bool infrarrojo_leer_FRONT(void);

void sensor_infrarrojo_init_LEFT();
bool infrarrojo_leer_LEFT(void);

void sensor_infrarrojo_init_RIGHT();
bool infrarrojo_leer_RIGHT(void);


#endif
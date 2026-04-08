/*Libreria encargada de gestionar los encoders de ambos motores*/

#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <inttypes.h>

//Descripción de las funciones que se van a usar para el encode
typedef struct {
    int32_t left_steps; // Contador de pasos para la rueda izquierda
    int32_t right_steps; // Contador de pasos para la rueda derecha

    float left_distance; // Distancia recorrida por la rueda izquierda en cm
    float right_distance; // Distancia recorrida por la rueda derecha en cm
} encoder_data_t;

//Funciones publicas.
void encoder_init(void); //iniciador de encoder.

void encoder_reset(void); //reiniciar los contadores de pasos.

encoder_data_t encoder_leer(void); //funcion para leer los pasos y distancia recorrida por cada rueda, devuelve una estructura con esta información.

#endif 
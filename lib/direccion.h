/*Libreria encargada de controlar el moviemiento*/

#ifndef DIRECCION_H
#define DIRECCION_H

/// Control de la dirección del micromouse, utilizando los pines correspondientes para cada dirección.
void direccion_init();
void direccion_adelante();
void direccion_atras();
void direccion_izquierda();
void direccion_derecha();
void direccion_parar();

#endif
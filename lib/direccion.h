/*Libreria encargada de controlar el moviemiento*/

#ifndef DIRECCION_H
#define DIRECCION_H

#ifdef __cplusplus
extern "C" {
#endif

/// Control de la dirección del micromouse, utilizando los pines correspondientes para cada dirección.
void direccion_init();
void direccion_adelante();
void direccion_atras();
void direccion_izquierda();
void direccion_derecha();
void direccion_parar();

/// @brief Función para avanzar una celda completa, utilizando el control de velocidad para mantener la dirección recta.
void avanzar_celda();

/// @brief Control de la dirección del micromouse para que vaya recto, utilizando ambos motores a la misma velocidad.
void direccion_recto();

///Funciones para que gire a 90 grados a la izquierda o derecha, o para que avance o retroceda, utilizando los motores de manera adecuada para cada dirección.
void grados_izquierda_90();
void grados_derecha_90();
void grados_180();

#ifdef __cplusplus
}
#endif

#endif /* DIRECCION_H */
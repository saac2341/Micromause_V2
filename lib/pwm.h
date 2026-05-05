/*Libreria encargada de gestionar le PWM de los motores*/

#ifndef PWM_H
#define PWM_H
#include <stdint.h>
#include <pico/stdlib.h>

/// Inicializacion de motores.
void motores_init(void);

///Control de velocidad del motor.
void motor_set_speed(uint motor, float speed);

//Control de dirección del motor.
void mover (float left, float right);

#endif /* PWM_H */
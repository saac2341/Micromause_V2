/*Libreria encargada de gestionar le PWM de los motores*/

#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <pico/stdlib.h>

/// Inicializacion de motores.
void motores_init(void);

///Control de velocidad del motor.
void motor_set_speed(uint motor, float speed);

//Control de dirección del motor.
void mover (float left, float right);

#ifdef __cplusplus
}
#endif
#endif /* PWM_H */
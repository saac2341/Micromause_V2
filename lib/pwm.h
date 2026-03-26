/*Libreria encargada de gestionar le PWM de los motores*/

#ifndef PWM_H
#define PWM_H
/// Inicializacion de motores.
void motores_init(void);

///Control de velocidad del motor.
void motor_set_speed(uint motor, float speed);

#endif /* PWM_H */
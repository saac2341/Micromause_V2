/*Libreria encargada de gestionar los datos del acelerometro y giroscopio*/

#ifndef ACELEROMETRO_H
#define ACELEROMETRO_H

//Estas librerias son para el acelerometro/giroscopio MPU6050, se pueden cambiar por otras dependiendo del modelo que se use
//Descripcion de las funciones que se van a usar para el acelerometro/giroscopio
typedef struct {
    float ax; // Aceleración en el eje x
    float ay; // Aceleración en el eje y
    float az; // Aceleración en el eje z
} acelerometro_data_t;

void acelerometro_init(void);

acelerometro_data_t acelerometro_leer(void);

#endif 
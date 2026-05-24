#include <stdio.h>
#include "pico/stdlib.h"
#include "lib/pwm.h"
#include "lib/encoder.h"
#include "lib/direccion.h"

int main() {

    stdio_init_all();

    motores_init();
    direccion_init();
    encoder_init();

    sleep_ms(2000);

    encoder_reset();

    direccion_adelante();

    while(true){

        encoder_data_t data = encoder_leer();

        printf("L:%ld\tR:%ld\n",
               data.left_steps,
               data.right_steps);

        sleep_ms(100);
    }

    return 0;
}
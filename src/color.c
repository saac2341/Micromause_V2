//Logica del sensor de color.
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "lib/color.h"
#include "temp/default.h"

#define I2C_PORT i2c0
#define TCS34725_ADDR 0x29

void color_init(void) {
    // Inicializar el I2C
    i2c_init(I2C_PORT, 100000);

    gpio_set_function(COLOR_SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_function(COLOR_SDA_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(COLOR_SCL_PIN);
    gpio_pull_up(COLOR_SDA_PIN);

    // Configurar el sensor de color
    uint8_t buf[2];

    buf[0] = 0x80 | 0x00;
    buf[1] = 0x01; // Activar el sensor
    i2c_write_blocking(I2C_PORT , TCS34725_ADDR , 
    buf , 2, false);

    sleep_ms(10);

    buf[1] = 0x03 ; // Configurar el tiempo de integración
    i2c_write_blocking(I2C_PORT , TCS34725_ADDR ,
    buf , 2, false);

}

void color_read(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    uint8_t reg = 0x80 | 0x00; // Registro de datos de color
    uint8_t buf[8];
    
    i2c_write_blocking(I2C_PORT, TCS34725_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, TCS34725_ADDR, buf, 8, false);

    *c = (buf[1] << 8) | buf[0]; // Clear
    *r = (buf[3] << 8) | buf[2]; // Red
    *g = (buf[5] << 8) | buf[4]; // Green
    *b = (buf[7] << 8) | buf[6]; // Blue
}


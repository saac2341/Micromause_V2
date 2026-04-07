/*LIBRERIA ENCARGADA DE GESTIONAR EL MODULO SD*/

//Librerias.
#include "lib/SD_module.h"
#include "hardware/spi.h"
#include "temp/default.h"
#include "pico/stdlib.h"
#include "lib/fatfs/ff.h"
#include "lib/fatfs/diskio.h"

static FATFS fs; // Sistema de archivos

//Inicializacion del modulo SD.
bool sd_init(void) {
    // Configurar pines SPI
    spi_init(spi0, 1000 * 1000); // Inicializar SPI a 1 MHz
    gpio_set_function(SD_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SD_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SD_MISO_PIN, GPIO_FUNC_SPI);

    gpio_init(SD_CS_PIN);
    gpio_set_dir(SD_CS_PIN, GPIO_OUT);
    gpio_put(SD_CS_PIN, 1); // Desactivar el chip select

    //Montar Fat
    if (f_mount (&fs, "", 1) != FR_OK) {
        return false;
    }
    return true;
}
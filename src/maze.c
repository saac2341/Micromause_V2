/*Logica para la gestion de la memoria SD*/

///Libreiras.
#include "lib/SD_module.h"
#include "hardware/spi.h"
#include "temp/default.h"
#include "lib/maze.h"
#include "lib/monitor.h"
#include <stdio.h>
#include <string.h>

//Variables globales.
static FATFS fs; // Sistema de archivos
static FIL file; // Archivo para escribir los checkpoints

//Iniciado de memoria SD.
bool SD_Init(){
    spi_init(spi0, 1000 * 1000); // Inicializar SPI a 1 MHz
    gpio_set_function(SD_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SD_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SD_MISO_PIN, GPIO_FUNC_SPI);

    gpio_init(SD_CS_PIN);
    gpio_set_dir(SD_CS_PIN, GPIO_OUT);
    gpio_put(SD_CS_PIN, 1); // Desactivar el chip select

    FRESULT fr;
    fr = f_mount(&fs, "", 1); // Montar el sistema de archivos
    if (fr != FR_OK) {
        return false;
    }
    return true;
}

//Crear un nuevo archivo para guardar los checkpoints.
bool SD_createFile(const char* filename) {
    FRESULT fr;
    fr = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (fr != FR_OK) {
        return false;
        return false;
    }
    return true;
}

//Escribir un checkpoint en el archivo.
bool SD_write_Checkpoint(Checkpoint_t *cp) {
    char buffer[64];
    UNIT bw;

    sprintf (buffer, "%d,%d,%d,%d,%d\n", 
        cp->step, cp->x, cp->y, cp->direction, cp->event);
    
        if (f_write(&file, buffer, strlen(buffer), &bw) != FR_OK) {
        return false;
        }
        return true;
}

//Guardar el estado del laberinto en el archivo.
bool SD_save_maze(uint8_t maze[16][16]) {
    FIL maze_file;
    UNIT bw;

    if (f_open(&maze_file, "maze.txt", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
        return false;
    }
    char line[64];
    for (int y=0 ; y<16 ; y++){
        for (int x=0 ; x <16 ; x++){
            sprintf(line, "%d ", maze[y][x]);
            f_write(&maze_file, line, strlen(line), &bw);
        }
        f_write(&maze_file, "\n", 1, &bw);
    }
    f_close(&maze_file);
    return true;
}

//Cerrar el archivo.
void SD_closeFile() {
    f_close(&file);
}

//Actualizar laberinto.
void monitor_actualizar_laberinto(monitor_data_t data) {
    // Actualizar el estado del laberinto basado en los sensores infrarrojos
    if (data.ir.front) {
        maze_set_wall(pos_x, pos_y, 0x01); // Pared al frente
    }
    if (data.ir.right) {
        maze_set_wall(pos_x, pos_y, 0x02); // Pared a la derecha
    }
    if (data.ir.back) {
        maze_set_wall(pos_x, pos_y, 0x04); // Pared atrás
    }
    if (data.ir.left) {
        maze_set_wall(pos_x, pos_y, 0x08); // Pared a la izquierda
    }
}
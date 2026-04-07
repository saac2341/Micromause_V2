/*Logica para la gestion de la memoria SD*/

///Libreiras.
#include "hardware/spi.h"
#include "lib/SD_module.h"
#include "temp/default.h"
#include "lib/maze.h"
#include "lib/monitor.h"
#include "lib/fatfs/ff.h"
#include "lib/fatfs/diskio.h"
#include <string.h>

static FIL file; // Variable para el archivo abierto

bool log_create(const char *filename){
    if (f_open(&file, filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK) {
        return true; // Archivo creado exitosamente
    }
    return false; // Error al crear el archivo
}

bool log_write_line(const char *text) {
    UINT bw; // Variable para almacenar el número de bytes escritos
    if (f_write(&file, text, strlen(text), &bw) == FR_OK && bw == strlen(text)) {
        return true; // Línea escrita exitosamente
    }
    return false; // Error al escribir la línea
}

void log_close(void) {
    f_close(&file); // Cerrar el archivo
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
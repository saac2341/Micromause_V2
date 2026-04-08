/*LIBRERIA ENCARGADA DE GESTIONAR EL ALGORIDMO DE BUSQUEDA DEL LABERINTO*/
#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include <stdint.h>
#include <pico/stdlib.h>
#include "lib/monitor.h"

#define MAX_SIZE 16 // Tamaño máximo del laberinto      

//Estructura para representar una celda del laberinto
typedef struct {
    uint8_t walls; // Bits para representar las paredes (0-3: N, E, S, W)
    uint8_t distance; // Distancia desde la celda de inicio
    uint8_t visited; // Bandera para marcar si la celda ha sido visitada
} cell_t;

extern cell_t maze[MAX_SIZE][MAX_SIZE]; // Laberinto representado como una matriz de celdas
extern int robot_direccion;

void maze_solver_init(); // Inicializa el laberinto y la dirección del robot
void update_maze_monitor(monitor_data_t data); // Actualiza el laberinto basado en los datos del monitor
void flood_fill_update(void);
int get_next_direction (monitor_data_t data); // Determina la siguiente dirección a tomar basada en el laberinto y los datos del monitor
void execute_move(int next_direction, monitor_data_t data); // Ejecuta un movimiento basado en la dirección y los datos del monitor
bool check_color_center(monitor_data_t data); // Verifica si el robot ha llegado al centro del laberinto basado en los datos del monitor    

#endif
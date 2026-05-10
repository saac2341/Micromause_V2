/*LIBRERIA ENCARGADA DE GESTIONAR EL ALGORIDMO DE BUSQUEDA DEL LABERINTO*/
#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include <stdint.h>
#include <pico/stdlib.h>
#include "lib/monitor.h"
#include <stdbool.h>

#define MAX_SIZE 16 // Tamaño máximo del laberinto      

//Estructura para representar una celda del laberinto
typedef struct {
    uint8_t walls; // Bits para representar las paredes (0-3: N, E, S, W)
    uint8_t distance; // Distancia desde la celda de inicio
    uint8_t visited; // Bandera para marcar si la celda ha sido visitada
} cell_t;

/// @brief Estructura para representar un nodo en la búsqueda del laberinto
typedef struct {
    int x, y;
}node_t;

void enqueue (int x, int y); // Agrega un nodo a la cola de búsqueda

node_t dequeue(); // Elimina y devuelve el nodo al frente de la cola de búsqueda

bool queue_empty(); // Verifica si la cola de búsqueda está vacía

void queue_reset(); // Reinicia la cola de búsqueda

bool wall_between (int x1, int y1, int x2, int y2); // Verifica si hay una pared entre dos celdas adyacentes

extern cell_t maze[MAX_SIZE][MAX_SIZE]; // Laberinto representado como una matriz de celdas
extern int robot_direccion;

void maze_solver_init(); // Inicializa el laberinto y la dirección del robot
void update_maze_monitor(monitor_data_t data); // Actualiza el laberinto basado en los datos del monitor
void flood_fill_update(void);
int get_next_direction (void ); // Determina la siguiente dirección a tomar basada en el laberinto y los datos del monitor
void execute_move(int next_direction); // Ejecuta un movimiento basado en la dirección y los datos del monitor
void execute_move_fast(int next_direction); // Ejecuta un movimiento rápido basado en la dirección y los datos del monitor
bool check_color_center(void); // Verifica si el robot ha llegado al centro del laberinto basado en los datos del monitor 
void flood_explore(void); // Algoritmo de exploración basado en el flujo de inundación para encontrar el centro del laberinto
void flood_optimize(void); // Algoritmo de optimización basado en el flujo de inundación para encontrar la ruta más corta al centro del laberinto

bool at_center_dynamic(void); // Verifica si el robot ha alcanzado el centro del laberinto

#endif
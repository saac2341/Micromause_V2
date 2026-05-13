/*LIBRERIA ENCARGA DE LA SOLUCION DEL LABERINTO*/

#include "lib/maze_solver.h"
#include "lib/monitor.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "temp/default.h"
#include <stdio.h>
#include "lib/color.h"
#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef COLOR_CENTRO
#define COLOR_CENTRO 1
#endif

/// Variable global para representar el laberinto y el estado del robot
int center_x = 7, center_y = 7; // Coordenadas del centro del laberinto
bool center_found = false; // Indica si se ha encontrado el centro
bool reached_center = false; // Indica si se ha alcanzado el centro

cell_t maze[MAX_SIZE][MAX_SIZE]; // Laberinto representado como una matriz de celdas
int robot_direccion; // Dirección actual del robot
int pos_x = 0, pos_y = 0; // Posición actual del robot

int dx[4] = {0, 1, 0, -1}; // Desplazamientos en x para N, E, S, W
int dy[4] = {-1, 0, 1, 0}; // Desplazamientos en y para N, E, S, W

///Cola para la búsqueda del laberinto
node_t queue[MAX_SIZE * MAX_SIZE];
int q_head = 0, q_tail = 0;

// Funciones para gestionar la cola de búsqueda del laberinto
void enqueue (int x, int y) {
    queue [q_tail++] = (node_t){x, y};
}

// Verifica si la cola de búsqueda está vacía
node_t dequeue() {
    return queue[q_head++];
}

bool queue_empty() {
    return q_head == q_tail;
}

// Reinicia la cola de búsqueda
void queue_reset() {
    q_head = q_tail = 0;
}


//Ejecuta un movimiento basado en la dirección y los datos del monitor.
bool wall_between (int x1, int y1, int x2, int y2) {
    int dx = x2 - x1 , dy = y2 - y1;
    if (dy == -1) return maze[y1][x1].walls & 0x01; // Norte
    if (dx == 1) return maze[y1][x1].walls & 0x02; // Este
    if (dy == 1) return maze[y1][x1].walls & 0x04; // Sur
    if (dx == -1) return maze[y1][x1].walls & 0x08; // Oeste
    return true; // Si no es adyacente, consideramos que hay una pared
}

//INICIADOR DE LA LIBRERIA.
void maze_solver_init() {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            maze[i][j].walls = 0x0F;
            maze[i][j].distance = 255; // Distancia inicial infinita
            maze[i][j].visited = 0;
        }
    }
    maze[7][7].distance = 0; // Distancia del centro a sí mismo es 0
    printf("Maze solver initialized.\n");
}

//Actualizador del laberinto.
void update_maze_monitor(monitor_data_t data){
    uint8_t *walls = &maze[pos_y][pos_x].walls;

    switch (robot_direccion)
    {
        case 0: //NORTE
            if(data.ir.front) maze[pos_y][pos_x].walls &= ~0x01; // Pared al frente
            if(data.ir.right) maze[pos_y][pos_x].walls &= ~0x02; // Pared a la derecha
            if(data.ir.back) maze[pos_y][pos_x].walls &= ~0x04; // Pared atrás
            if(data.ir.left) maze[pos_y][pos_x].walls &= ~0x08; // Pared a la izquierda
            break;
        case 1: //ESTE
            if(data.ir.front) maze[pos_y][pos_x].walls &= ~0x02; // Pared al frente
            if(data.ir.right) maze[pos_y][pos_x].walls &= ~0x04 ; // Pared a la derecha
            if(data.ir.back) maze[pos_y][pos_x].walls &= ~0x08      ; // Pared atrás
            if(data.ir.left) maze[pos_y][pos_x].walls &= ~0x01; // Pared a la izquierda
            break; 
        case 2: //SUR
            if(data.ir.front) maze[pos_y][pos_x].walls &= ~0x04; // Pared al frente
            if(data.ir.right) maze[pos_y][pos_x].walls &= ~0x08; // Pared a la derecha
            if(data.ir.back) maze[pos_y][pos_x].walls &= ~0x01; // Pared atrás
            if(data.ir.left) maze[pos_y][pos_x].walls &= ~0x02; // Pared a la izquierda
            break;
        case 3: //OESTE
            if(data.ir.front) maze[pos_y][pos_x].walls &= ~0x08; // Pared al frente
            if(data.ir.right) maze[pos_y][pos_x].walls &= ~0x01; // Pared a la derecha
            if(data.ir.back) maze[pos_y][pos_x].walls &= ~0x02; // Pared atrás
            if(data.ir.left) maze[pos_y][pos_x].walls &= ~0x04; // Pared a la izquierda  
            break;
    }
    maze[pos_y][pos_x].visited = 1; // Marcar la celda como visitada
}

// Algoridmo de flujo de inundacion para actualizar las distancias en el laberinto.
void flood_fill_update(void) {
    //Reseteamos las distancias excepto el centro
    float INF;
    for (int y=0; y <MAX_SIZE; y++){
        for(int x = 0; x < MAX_SIZE; x++){
            maze[y][x].distance = INF;
        }
        queue_reset();
    }
    // Si se ha encontrado el centro, usar sus coordenadas como objetivo, sino usar el centro del laberinto
    int goal_x = center_found ? center_x : 7;
    int goal_y = center_found ? center_y : 7;
    // Inicializar la distancia del objetivo a 0 y agregarlo a la cola
    maze[goal_y][goal_x].distance = 0;
    enqueue(goal_x, goal_y);

    // Realizar la búsqueda en anchura para actualizar las distancias
    while (!queue_empty()) {
        
        node_t current = dequeue();
        
        for (int d = 0; d < 4; d++){
            int nx = current.x + dx[d];
            int ny = current.y + dy[d];

            if (nx <0 || ny < 0 || nx >= MAX_SIZE || ny >= MAX_SIZE)
            continue; // Ignorar fuera de límites

            if (wall_between(current.x, current.y, nx, ny))
                continue; // Ignorar paredes

            if (maze[ny][nx].distance > maze[current.y][current.x].distance + 1) {
                maze[ny][nx].distance = maze[current.y][current.x].distance + 1;
                enqueue(nx, ny);
            }
        }
    }
}

/// Determina la siguiente dirección a tomar basada en el laberinto y los datos del monitor.
int get_next_direction (void) {
    int best_dir = robot_direccion;
    uint8_t best_dist = maze [pos_y][pos_x].distance;

    //Priorizar movimientos Izquierda, Frente, Derecha
    int options[4]={
        (robot_direccion + 3) % 4, // Izquierda
        robot_direccion,             // Frente
        (robot_direccion + 1) % 4, // Derecha
        (robot_direccion + 2) % 4  // Atrás
    };

    for (int i = 0; i < 4; i++) {
        int dir = options[i];
        int nx = pos_x + dx[dir];
        int ny = pos_y + dy[dir];

        if(nx < 0 || ny < 0 || nx >= MAX_SIZE || ny >= MAX_SIZE)
        continue; // Ignorar fuera de límites

        if (!wall_between(pos_x, pos_y, nx, ny) && 
            maze[ny][nx].distance < best_dist) {
            best_dist = maze[ny][nx].distance;
            best_dir = dir;
            }
       return best_dir;
    }
}

/// Ejecuta el movimiento hacia la siguiente dirección determinada.

void execute_move(int next_direction) {
    int turn = (next_direction - robot_direccion + 4) % 4;
   
    if (turn == 0) direccion_adelante();
    else if (turn == 1) direccion_derecha();
    else if (turn == 2) direccion_atras();
    else direccion_izquierda();

    motor_set_speed(1, VELOCIDAD_MEDIA);
    motor_set_speed(2, VELOCIDAD_MEDIA);
    sleep_ms(500); // Simulación de tiempo de movimiento

    ///actualizar posición y dirección del robot
    robot_direccion = next_direction;
    pos_x += dx[robot_direccion];
    pos_y += dy[robot_direccion];
    printf("==> Dir: %d, Pos: (%d, %d)", robot_direccion, pos_x, pos_y);
}

//Verifica si el robot ha llegado al centro del laberinto basado en los datos del monitor.
bool check_color_center(void) {
    static int confirm = 0;
    uint16_t r = 0, g = 0, b = 0, c = 0;

    /* Leer color al sensor (función devuelve void) y comparar el canal/valor 'c' */
    color_read(&r, &g, &b, &c);
    if (c == COLOR_CENTRO) {
        confirm++;
        if (confirm >= 3) { // Confirmar con varias lecturas
            center_x = pos_x;
            center_y = pos_y;

            center_found =true;
            reached_center = true;

            printf("Meta encontrada en (%d, %d)\n", center_x, center_y);
            return true;
        }
    } else {
        confirm = 0; // Resetear si no se detecta el color
    }
    return false;
}

void flood_explore(void) {
    while (!reached_center) {
        monitor_data_t data = monitor_leer_datos();
        update_maze_monitor(data);
        
        if(check_color_center()){
            flood_fill_update(); // Actualizar distancias al encontrar el centro
        }
        flood_fill_update(); // Actualizar distancias en cada iteración

        int next_dir = get_next_direction();
        execute_move(next_dir);
    }
}

void flood_optimize(void) {
    center_x = 0;
    center_y = 0;
    center_found = false;

    while (pos_x != 0 || pos_y != 0) {
        flood_fill_update(); // Actualizar distancias al centro
        int next_dir = get_next_direction();
        execute_move(next_dir);
    }

    center_found = true;

    while(!(pos_x == center_x && pos_y == center_y)){
        flood_fill_update(); // Actualizar distancias al centro
        int next_dir = get_next_direction();
        execute_move(next_dir);
    }
}

void execute_move_fast(int next_direction) {
    int turn = (next_direction - robot_direccion + 4) % 4;
   
    if (turn == 0) direccion_adelante();
    else if (turn == 1) direccion_derecha();
    else if (turn == 2) direccion_atras();
    else direccion_izquierda();

    motor_set_speed(1, VELOCIDAD_MAX);
    motor_set_speed(2, VELOCIDAD_MAX);
    sleep_ms(300); // Simulación de tiempo de movimiento más rápido

    ///actualizar posición y dirección del robot
    robot_direccion = next_direction;
    pos_x += dx[robot_direccion];
    pos_y += dy[robot_direccion];
    printf("==> Dir: %d, Pos: (%d, %d)", robot_direccion, pos_x, pos_y);
}
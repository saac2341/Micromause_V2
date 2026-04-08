/*LIBRERIA ENCARGA DE LA SOLUCION DEL LABERINTO*/

#include "lib/maze_solver.h"
#include "lib/monitor.h"
#include "lib/pwm.h"
#include "lib/direccion.h"
#include "temp/default.h"
#include <stdio.h>
#include "pico/stdlib.h"

cell_t maze[MAX_SIZE][MAX_SIZE]; // Laberinto representado como una matriz de celdas
int robot_direccion; // Dirección actual del robot
int pos_x = 0, pos_y = 0; // Posición actual del robot

int dx[4] = {0, 1, 0, -1}; // Desplazamientos en x para N, E, S, W
int dy[4] = {-1, 0, 1, 0}; // Desplazamientos en y para N, E, S, W

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
    bool changed = true;   
    while (changed) {
        changed = false;
        for (int y= 0 ; y < MAX_SIZE; y++){
            for (int x = 0; x < MAX_SIZE; x++) {
                if (x==7 && y==7) continue; // Saltar el centro

                uint8_t min_dist = 255;
                 if (!(maze[y][x].walls & 0x01) && y > 0) min_dist = MIN(min_dist, maze[y-1][x].distance);
                if (!(maze[y][x].walls & 0x02) && x < MAX_SIZE-1) min_dist = MIN(min_dist, maze[y][x+1].distance);
                if (!(maze[y][x].walls & 0x04) && y < MAX_SIZE-1) min_dist = MIN(min_dist, maze[y+1][x].distance);
                if (!(maze[y][x].walls & 0x08) && x > 0) min_dist = MIN(min_dist, maze[y][x-1].distance);

                if (min_dist != 255 && maze[y][x].distance != min_dist + 1) {
                maze[y][x].distance = min_dist + 1;
                changed = true;
                }
            }       
        }   
    }
}

/// Determina la siguiente dirección a tomar basada en el laberinto y los datos del monitor.
int get_next_direction (monitor_data_t data) {
    int best_dir = robot_direccion;
    uint8_t best_dist = maze [pos_y][pos_x].distance;

    //Priorizar movimientos Izquierda, Frente, Derecha, Atrás
    int options[3] = {(robot_direccion + 3) % 4, robot_direccion, (robot_direccion + 1) % 4}; // Izquierda, Frente, Derecha
    for (int i = 0; i < 3; i++) {
        int nx = pos_x + dx[options[i]];
        int ny = pos_y + dy[options[i]];

        if (nx >= 0 && nx < MAX_SIZE && ny >= 0 && ny < MAX_SIZE) {
            if (!(wall_between(pos_x, pos_y, nx, ny)) &&
                maze[ny][nx].distance < best_dist) {
                best_dist = maze[ny][nx].distance;
                best_dir = options[i];
            }
        }
    }
    return best_dir;
}


void execute_move(int next_direction, monitor_data_t data) {
    int turn = (next_direction - robot_direccion + 4) % 4;
   
    if (turn == 0){
        direccion_adelante();
        motor_set_speed(1, VELOCIDAD_MEDIA);
        motor_set_speed(2, VELOCIDAD_MEDIA);
        sleep_ms(10); // Avanzar un poco antes de verificar nuevamente
    }
    else if (turn == 1){
        direccion_derecha();
        motor_set_speed(1, VELOCIDAD_MEDIA);
        motor_set_speed(2, 0);
        sleep_ms(10); // estabilidad
    }
    else if (turn == 2){
        direccion_atras();
        motor_set_speed(1, VELOCIDAD_MEDIA);
        motor_set_speed(2, VELOCIDAD_MEDIA);
        sleep_ms(10); // Retroceder un poco antes de verificar nuevamente
    }
    else if (turn == 3){
        direccion_izquierda();
        motor_set_speed(1, 0);
        motor_set_speed(2, VELOCIDAD_MEDIA);
        sleep_ms(10); // estabilidad
    }

    ///actualizar posición y dirección del robot
    robot_direccion = next_direction;
    pos_x += dx[robot_direccion];
    pos_y += dy[robot_direccion];
    printf("==> Dir: %d, Pos: (%d, %d)", robot_direccion, pos_x, pos_y);
}

//Verifica si el robot ha llegado al centro del laberinto basado en los datos del monitor.
bool check_color_center(monitor_data_t data) {
    return data.ir.front && data.ir.right && data.ir.back && data.ir.left;
}
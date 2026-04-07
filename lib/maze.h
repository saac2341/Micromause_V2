/*Libreria enfocadad a la base de datos desde el monitor*/
#ifndef MAXE_H
#define MAXE_H

#include <stdbool.h>
#include "lib/monitor.h"

bool log_create(const char *filename);

bool log_write_line(const char *text);

void log_close(void);


///Actualizar laberinto 
void monitor_actualizar_laberinto(monitor_data_t data);
#endif /* MAXE_H */
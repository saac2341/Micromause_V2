///LIBREIA ENCARGADA DE GESTIONAR EL SENSOR DE COLOR TCS34725

#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>
///funcines de lectura 
void color_init(void);
void color_read(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);

#endif
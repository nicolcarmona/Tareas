#ifndef PIEZAS_H
#define PIEZAS_H
#include <stdbool.h>
#include <stdlib.h>

struct Juego; /* Forward declaration */
typedef struct Pieza{
    char tipo; /* ’P’=Peon, ’C’=Caballo, ’A’=Alfil, ’T’=Torre, ’Q’=Reina, ’R’=Rey */
    int hp;
    int x, y;
} Pieza;

typedef struct Celda {
    Pieza *pieza; /* NULL si la celda esta vacia */
} Celda;

Pieza* crear_pieza(char tipo, int hp, int x, int y); //funcion extra para crear las piezas [lo imagine como los inicializadores de las clases en c++]    
Pieza* spawn_enemigo(struct Juego* juego, char tipo, int hp, int y,int i); //funcion extra para no escribir el mismo bloque a cada rato cuando spawnea un enemigo
void eliminar_pieza(struct Juego *juego, int i); //funcion extra para liberar la memoria de las piezas
void spawn_nivel(struct Juego *juego, int nivel);
void mover_enemigos(struct Juego *juego);
bool verificar_estado_rey(struct Juego *juego); /* Revisa si el Rey esta en Jaque */

#endif
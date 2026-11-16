#ifndef MAIN_H
#define MAIN_H
#include "tablero.h"
#include "armas.h"
#include "piezas.h"

typedef struct Juego{
    Tablero *t;
    Armas arsenal;
    Pieza *jugador; /* El Rey */
    Pieza** enemigos; //extra para tener la cantida de enemigos
    int numeros_enemigos; //extra cantidad de enemigos totales
    int nivel_actual; /* 1, 2 o 3 */
    int turno_enemigos; /* Contador para gestionar piezas lentas como la Torre */
    int turno_escudo; // extra para la arma especial
} Juego;

// Rol: Inicia el ciclo de juego, maneja el bucle principal de entrada (WASD+QEZC / 1234), gestiona el avance de niveles y libera la memoria general al terminar o perder.
#endif
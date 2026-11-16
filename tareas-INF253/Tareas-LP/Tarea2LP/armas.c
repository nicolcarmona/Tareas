#include "main.h"
#include <stdio.h>
#include <stdlib.h>

bool escopeta(struct Juego *j, int dir_x, int dir_y){
    /*
    ***
    Parametros: Puntero de tipo de dato Juego, 2 enteros, con las direcciones en x e y.
    ***
    Retorno: Un booleano
    ***
    Objetivo: Crear el movimiento, disparo, de la escopeta.
    */
    if (j->arsenal.municion_actual[0] <= 0) {
        printf("Oh no... No te queda municion en la escopeta!\n");
        return false;
    }
    j->arsenal.municion_actual[0]--;
    int disparo_x = j->jugador->x + dir_x;
    int disparo_y = j->jugador->y + dir_y;

    if (disparo_x >= 0 && disparo_x < j->t->W && disparo_y >= 0 && disparo_y < j->t->H){ //Si el disparo se encuentra en los limites del tablero
        Celda* destino = (Celda*)j->t->celdas[disparo_y][disparo_x];
        if (destino->pieza != NULL){
            destino->pieza->hp -= 2;
            printf("IMPACTO!! - 2 HP inflingido a %c\n", destino->pieza->tipo);
            if (destino->pieza->hp <= 0){
                printf("˗ˏˋ ✸ ˎˊ˗ %c ha caido!! ˗ˏˋ ✸ ˎˊ˗ \n", destino->pieza->tipo);
                for(int i = 0; i < j->numeros_enemigos; i++){
                    if(j->enemigos[i] != NULL && j->enemigos[i] == destino->pieza){
                        eliminar_pieza(j, i); // liberamos la memoria de la pieza
                        break;
                    }
                }
            }
            //logica de cono de los disparos
            int centro_x = disparo_x + dir_x;
            int centro_y = disparo_y + dir_y;
            int izq_x = disparo_x - dir_y;
            int izq_y = disparo_y + dir_y;
            int der_x = disparo_x + dir_y;
            int der_y = disparo_y + dir_y;

            if(centro_x >= 0 && centro_x < j->t->W && centro_y >= 0 && centro_y < j->t->H){ //Mecanica de disparo en el centro
                Celda* destino2 = (Celda*)j->t->celdas[centro_y][centro_x];
                if (destino2->pieza != NULL){
                    destino2->pieza->hp -= 1;
                    printf("IMPACTO!! - 1 HP inflingido a %c\n", destino2->pieza->tipo);
                    if (destino2->pieza->hp <= 0){
                        printf("%c ha caido!!\n", destino2->pieza->tipo);
                        for(int i = 0; i < j->numeros_enemigos; i++){
                            if(j->enemigos[i] != NULL && j->enemigos[i] == destino2->pieza){
                                eliminar_pieza(j, i);
                                break;
                            }
                        }
                    }
                }
            }
            if(izq_x >= 0 && izq_x < j->t->W && izq_y >= 0 && izq_y < j->t->H){ //Mecanica de disparo a la izquierda
                Celda* destino2 = (Celda*)j->t->celdas[izq_y][izq_x];
                if (destino2->pieza != NULL){
                    destino2->pieza->hp -= 1;
                    printf("IMPACTO!! - 1 HP inflingido a %c\n", destino2->pieza->tipo);
                    if (destino2->pieza->hp <= 0){
                        printf("%c ha caido!!\n", destino2->pieza->tipo);
                        for(int i = 0; i < j->numeros_enemigos; i++){
                            if(j->enemigos[i] != NULL && j->enemigos[i] == destino2->pieza){
                                printf("Eliminando enemigo en indice %d\n", i);
                                eliminar_pieza(j, i);
                                break;
                            }
                        }
                    } 
                }
            }
            if(der_x >= 0 && der_x < j->t->W && der_y >= 0 && der_y < j->t->H){ //Mecanica de disparo a la derecha
                Celda* destino2 = (Celda*)j->t->celdas[der_y][der_x];
                if (destino2->pieza != NULL){
                    destino2->pieza->hp -= 1;
                    printf("IMPACTO!! - 1 HP inflingido a %c\n", destino2->pieza->tipo);
                    if (destino2->pieza->hp <= 0){
                        printf("%c ha caido!!\n", destino2->pieza->tipo);
                        for(int i = 0; i < j->numeros_enemigos; i++){
                            if(j->enemigos[i] != NULL && j->enemigos[i] == destino2->pieza){
                                printf("Eliminando enemigo en indice %d\n", i);
                                eliminar_pieza(j, i);
                                break;
                            }
                        }
                    } 
                }
            }
        }
    }
    return true;
}

bool francotirador(struct Juego *j, int dir_x, int dir_y){
    /*
    ***
    Parametros: Puntero de tipo de dato Juego, 2 enteros, con las direcciones en x e y.
    ***
    Retorno: Un booleano
    ***
    Objetivo: Crear el movimiento, disparo, del Sniper/francotirador.
    */

    if (j->arsenal.municion_actual[1] <= 0) {
        printf("Oh no... No te queda municion en el francotirador!\n");
        return false;
    }
    j->arsenal.municion_actual[1]--;

    int limite = j->t->W + j->t->H; //su limite es el tablero, ya que tiene largo "infinito"
    for(int i = 1; i <= limite; i++){
        int disparo_x = j->jugador->x + (i * dir_x);
        int disparo_y = j->jugador->y + (i * dir_y);
        
        if (disparo_x >= 0 && disparo_x < j->t->W && disparo_y >= 0 && disparo_y < j->t->H){
            Celda* destino = (Celda*)j->t->celdas[disparo_y][disparo_x];
            if (destino->pieza != NULL){
                destino->pieza->hp -= 3;
                printf("IMPACTO!! - 3 HP inflingido a %c\n", destino->pieza->tipo);
                if (destino->pieza->hp <= 0){
                    printf("˗ˏˋ ✸ ˎˊ˗ %c ha caido!! ˗ˏˋ ✸ ˎˊ˗ \n", destino->pieza->tipo);
                    for(int k = 0; k < j->numeros_enemigos; k++){
                        if(j->enemigos[k] != NULL && j->enemigos[k] == destino->pieza){
                            eliminar_pieza(j, k);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    return true;
}

bool granada(struct Juego *j, int dir_x, int dir_y){
    /*
    ***
    Parametros: Puntero de tipo de dato Juego, 2 enteros, con las direcciones en x e y.
    ***
    Retorno: Un booleano
    ***
    Objetivo: Crear el movimiento, disparo, de la granada.
    */
    if (j->arsenal.municion_actual[2] <= 0) {
        printf("Oh no... No te quedan granadas!\n");
        return false;
    }
    j->arsenal.municion_actual[2]--;

    int impacto_x = j->jugador->x + (dir_x * 3); //Ya que la granada hace un impacto en todo el alrededor (3x3), se multiplica por 3.
    int impacto_y = j->jugador->y + (dir_y * 3);
    for(int direccion_y = -1; direccion_y <= 1; direccion_y++){
        for(int direccion_x = -1; direccion_x <= 1; direccion_x++){
            int celda_x = impacto_x + direccion_x; //Sumar el impacto con las celdas que se veran afectadas (es decir las casillas del alrededor)
            int celda_y = impacto_y + direccion_y;
            if (celda_x >= 0 && celda_x < j->t->W && celda_y >= 0 && celda_y < j->t->H){ //Limites
                Celda* destino = (Celda*)j->t->celdas[celda_y][celda_x];
                if (destino->pieza != NULL){
                    destino->pieza->hp -= 2;
                    printf("IMPACTO!! - 2 HP inflingido a %c\n", destino->pieza->tipo);
                    if (destino->pieza->hp <= 0){
                        printf("˗ˏˋ ✸ ˎˊ˗ %c ha caido!! ˗ˏˋ ✸ ˎˊ˗ \n", destino->pieza->tipo);
                        for(int k = 0; k < j->numeros_enemigos; k++){
                            if(j->enemigos[k] != NULL && j->enemigos[k] == destino->pieza){
                                eliminar_pieza(j, k);
                                break;
            
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool especial(struct Juego *j, int dir_x, int dir_y){
    /*
    ***
    Parametros: Puntero de tipo de dato Juego, 2 enteros, con las direcciones en x e y. 
    ***
    Retorno: Un puntero de tipo de dato tablero.
    ***
    Objetivo: Crear el texto de la arma especial y la duracion del escudo.
    */
    if(j->arsenal.municion_actual[3] <= 0){
        printf("Oh, no... escudo no está disponible!\n");
        return false;
    }
    j->arsenal.municion_actual[3]--;
    j->turno_escudo = 2;
    printf("¡Escudo activado! El Rey está protegido por 2 turnos.\n");
    return true;
}

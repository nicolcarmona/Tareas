#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "tablero.h"


int main(){
     /*
    ***
    Parametros: No recibe parametros
    ***
    Retorno: Un entero
    ***
    Objetivo: Inicia el ciclo de juego, maneja el bucle principal de entrada (WASD+QEZC / 1234), gestiona el avance de niveles y libera la memoria general al terminar o perder.
    */
    
    //Inicializamos:
    Juego juego;
    juego.nivel_actual = 1;
    juego.turno_enemigos = 0;
    juego.t = tablero_crear(12, 12);
    spawn_nivel(&juego, 1);
    juego.turno_escudo = 0;

    juego.arsenal.disparar[0] = escopeta;
    juego.arsenal.disparar[1] = francotirador;
    juego.arsenal.disparar[2] = granada;
    juego.arsenal.disparar[3] = especial;

    juego.arsenal.municion_maxima[0] = 2;
    juego.arsenal.municion_actual[0] = 2;

    juego.arsenal.municion_maxima[1] = 1; 
    juego.arsenal.municion_actual[1] = 1;

    juego.arsenal.municion_maxima[2] = 2; 
    juego.arsenal.municion_actual[2] = 2;

    juego.arsenal.municion_maxima[3] = 1;
    juego.arsenal.municion_actual[3] = 1;

    //Ciclo de juego
    while(juego.jugador->hp > 0){
        if(verificar_estado_rey(&juego)) printf("¡JAQUE! El Rey está en peligro!\n"); //comprobar el estado del rey
        tablero_imprimir(&juego);
        char tecla, direccion_disparo;
        printf("ACCIONES: Disparo: [1] Escopeta [2] Sniper [3] Granada [4] Especial\n");
        printf("Movimiento:\n");
        printf("[Q][W][E]\n");
        printf("[A] R [D]\n");
        printf("[Z][S][C]\n");
        printf("> Ingrese accion (Tecla de Movimiento o Numero de Arma): " );
        scanf(" %c", &tecla);

        int jx = 0, jy = 0,turno_valido = 0; //jx y jy son las direccion que toma el jugador.
        bool Mov_O_Disparo = false; //Variable para saber si es movimiento o va a ser disparo, Mov: false, Disparo: true
        int dir_valida = false;
        switch(tecla) { //Movimiento del jugador por terminal
            case 'w': case 'W': 
                jx = 0, jy = 1;
                Mov_O_Disparo = false;
                break;
            case 's': case 'S': 
                jx = 0 , jy= -1; 
                Mov_O_Disparo = false;
                break;
            case 'a': case 'A': 
                jx = -1 , jy = 0;
                Mov_O_Disparo = false;
                break;
            case 'd': case 'D': 
                jx = 1, jy = 0;
                Mov_O_Disparo = false;
                break;
            case 'q': case 'Q': 
                jx = -1, jy = 1; 
                Mov_O_Disparo = false;
                break;
            case 'e': case 'E': 
                jx = 1, jy = 1;
                Mov_O_Disparo = false;
                break;
            case 'z': case 'Z': 
                jx = -1, jy = -1;
                Mov_O_Disparo = false;
                break;
            case 'c': case 'C': 
                jx = 1, jy = -1;
                Mov_O_Disparo = false;
                break;
            
            case '1': //disparos
                Mov_O_Disparo = true;
                printf("> Direccion de disparo (Q, W, E, A, S, D, Z, C) ");
                scanf(" %c", &direccion_disparo);
                switch(direccion_disparo) {
                    case 'w': case 'W': jx = 0, jy = 1, dir_valida = true; break;
                    case 's': case 'S': jx = 0 , jy= -1, dir_valida = true; break;
                    case 'a': case 'A': jx = -1 , jy = 0, dir_valida = true; break;
                    case 'd': case 'D': jx = 1, jy = 0, dir_valida = true; break;
                    case 'q': case 'Q': jx = -1, jy = 1, dir_valida = true; break;
                    case 'e': case 'E': jx = 1, jy = 1, dir_valida = true;break;
                    case 'z': case 'Z': jx = -1, jy = -1, dir_valida = true; break;
                    case 'c': case 'C': jx = 1, jy = -1, dir_valida = true;break;
                    default: printf("Dirección inválida\n"); break;
                }
                if(dir_valida) turno_valido = juego.arsenal.disparar[0](&juego, jx, jy); //uso de dir_valida, para evitar otro valor de direccion que no exista [esto es porque si ponia por ejemplo 2 de direccion le quitaba vida al rey]
                break;

            case '2':
                Mov_O_Disparo = true;
                printf("> Direccion de disparo (Q, W, E, A, S, D, Z, C) ");
                scanf(" %c", &direccion_disparo);
                switch(direccion_disparo) {
                    case 'w': case 'W': jx = 0, jy = 1, dir_valida = true; break;
                    case 's': case 'S': jx = 0 , jy= -1, dir_valida = true; break;
                    case 'a': case 'A': jx = -1 , jy = 0, dir_valida = true; break;
                    case 'd': case 'D': jx = 1, jy = 0, dir_valida = true; break;
                    case 'q': case 'Q': jx = -1, jy = 1, dir_valida = true; break;
                    case 'e': case 'E': jx = 1, jy = 1, dir_valida = true; break;
                    case 'z': case 'Z': jx = -1, jy = -1, dir_valida = true; break;
                    case 'c': case 'C': jx = 1, jy = -1, dir_valida = true;break;
                    default: printf("Dirección inválida \n"); break;
                }
                if(dir_valida) turno_valido = juego.arsenal.disparar[1](&juego, jx, jy);
                break;

            case '3':
                Mov_O_Disparo = true;
                printf("> Direccion de disparo (Q, W, E, A, S, D, Z, C) ");
                scanf(" %c", &direccion_disparo);
                switch(direccion_disparo) {
                    case 'w': case 'W': jx = 0, jy = 1, dir_valida = true; break;
                    case 's': case 'S': jx = 0 , jy= -1, dir_valida = true; break;
                    case 'a': case 'A': jx = -1 , jy = 0, dir_valida = true; break;
                    case 'd': case 'D': jx = 1, jy = 0, dir_valida = true; break;
                    case 'q': case 'Q': jx = -1, jy = 1, dir_valida = true; break;
                    case 'e': case 'E': jx = 1, jy = 1, dir_valida = true; break;
                    case 'z': case 'Z': jx = -1, jy = -1, dir_valida = true; break;
                    case 'c': case 'C': jx = 1, jy = -1, dir_valida = true; break;
                    default: printf("Dirección inválida \n"); break;
                }
                if(dir_valida) turno_valido = juego.arsenal.disparar[2](&juego, jx, jy);
                break;

            case '4':
                Mov_O_Disparo = true;
                turno_valido = juego.arsenal.disparar[3](&juego, 0, 0);
                break;       
        }

        if (Mov_O_Disparo == false){ //Movimiento del rey
            int nueva_pos_y = juego.jugador->y + jy;
            int nueva_pos_x = juego.jugador->x + jx;
            if (nueva_pos_y >= 0 && nueva_pos_y < juego.t->H && nueva_pos_x >= 0 && nueva_pos_x < juego.t->W){ //colision entre el rey y el tablero, para que no salga de el
                Celda* destino = (Celda*)juego.t->celdas[nueva_pos_y][nueva_pos_x];
                if(destino->pieza != NULL) printf("Movimiento invalido\n");
                else{
                    turno_valido = 1;
                    ((Celda*)juego.t->celdas[juego.jugador->y][juego.jugador->x])->pieza = NULL;
                        juego.jugador->x += jx;
                        juego.jugador->y += jy;
                        ((Celda*)juego.t->celdas[juego.jugador->y][juego.jugador->x])->pieza = juego.jugador;
                        if(juego.arsenal.municion_actual[0] < juego.arsenal.municion_maxima[0]) juego.arsenal.municion_actual[0]++;
                }
            }   
            else printf("Movimiento invalido \n"); //en caso de que quiera ir a donde haya una celda ocupada por un enemigo
        }
        //si el turno es 1, es porque es el turno de los enemigos
        if (turno_valido == 1){
            mover_enemigos(&juego);
            juego.turno_enemigos++;
            if(juego.jugador->hp > 0) printf("Las piezas enemigas avanzan...\n");
            int contador_enemigos = 0;
            for(int i = 0; i < juego.numeros_enemigos ; i++){
                if(juego.enemigos[i] != NULL){
                    contador_enemigos++;
                }
            }
            if(contador_enemigos == 0){
                if(juego.nivel_actual == 1){
                    printf("NIVEL 1 COMPLETADO\n");
                    printf("El Rey entra al jardin del Rey...\n");
                    free(juego.enemigos); //Liberacion de memoria de los enemigos
                    tablero_liberar(juego.t); //Liberacion de memoria del tablero para pasar al siguiente nivel
                    juego.t = tablero_crear(8, 8);
                    spawn_nivel(&juego, 2);
                    for(int i = 0; i < 4; i++){
                        juego.arsenal.municion_actual[i] = juego.arsenal.municion_maxima[i];
                    }
                    juego.nivel_actual++;
                }
                else if(juego.nivel_actual == 2){
                    printf("NIVEL 2 COMPLETADO\n");
                    printf("El Rey entra al castillo...\n");
                    free(juego.enemigos);
                    tablero_liberar(juego.t);
                    juego.t = tablero_crear(6, 6);
                    spawn_nivel(&juego, 3);
                    for(int i = 0; i < 4; i++){
                        juego.arsenal.municion_actual[i] = juego.arsenal.municion_maxima[i];
                    }
                    juego.nivel_actual++;
                }
                else{
                    printf("El Rey volvió a tomar el control, has sobrevivido a la revolucíon\n");
                    free(juego.enemigos);
                    break;
                }
            }
        }
    }
    free(juego.jugador); //Liberacion de memoria del rey

    for(int i = 0; i < juego.numeros_enemigos; i++){ //Liberacion de memoria de los enemigos,
        if(juego.enemigos[i] != NULL){
            free(juego.enemigos[i]);
        }
    }
free(juego.enemigos);
    if(juego.t != NULL) tablero_liberar(juego.t); //Liberacion de memoria del tablero
    return 0;
}
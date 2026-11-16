#include <stdio.h>
#include <stdlib.h>
#include "tablero.h"
#include "piezas.h"
#include "main.h"


struct Tablero* tablero_crear(int ancho, int alto) {
    /*
    ***
    Parametros: Dos enteros.
    ***
    Retorno: Un puntero de tipo de dato tablero.
    ***
    Objetivo: Es crear el tablero dependiendo de las dimensiones que se entregue en el parametro.
    */

    Tablero *tablero = (Tablero*)malloc(sizeof(Tablero)); //Espacio de memoria del tablero
    tablero->H =alto;
    tablero->W =ancho;
    tablero->celdas = (void ***)malloc(alto * sizeof(void**)); //espacio de memoria de las filas en el tablero
    for (int i = 0; i < alto; i++){
        tablero->celdas[i] = (void **)malloc(ancho * sizeof(void*)); //Espacio de memoria para las columnas
        for (int j = 0; j < ancho; j++){
            tablero->celdas[i][j] = (void*)malloc(sizeof(Celda));//espacio de memoria para la posicion en si, en donde estara la pieza
            ((Celda*)tablero->celdas[i][j])->pieza = NULL;
        }
    }
    return tablero;
}

void tablero_imprimir(struct Juego *juego){
    /*
    ***
    Parametros: un puntero de tipo de dato juego.
    ***
    Retorno: no tiene retorno (funcion tipo void).
    ***
    Objetivo: Imprimir por terminal el tablero.
    */

    for(int i = juego->t->H - 1; i >= 0; i--){ //invertimos para que al imprimir las filas salgan de mayor a menor
        if (i + 1 >= 10)  printf("%d", i+1); //esto no mas es para que no se descuadre el tablero
        else printf("%d ", i+1);
        for(int j = 0; j < juego->t->W; j++){
            if(((Celda*)juego->t->celdas[i][j])->pieza == NULL) printf("[ ]"); //el tablero sin nada
            else printf("[%c]", ((Celda*)juego->t->celdas[i][j])->pieza->tipo); //el tablero con la pieza
        }
        printf("\n");
    }
    //todo el siguiente for es para imprimir los numeros de las columnas y que no se descuadre
    for (int i = 0; i < juego->t->W; i++){
        if (i+1 == 1)printf("   %d", i + 1);
        else if (i + 1 >= 10)  printf(" %d", i+1);
        else if(i+1 == 9) printf("  %d ", i + 1);
        else printf("  %d", i + 1);
    }
    printf("\n");
}

void tablero_liberar(struct Tablero *tablero){
    /*
    ***
    Parametros: Un puntero de tipo de dato tablero.
    ***
    Retorno: No tiene retorno.
    ***
    Objetivo: Liberar la memoria dinamica almacenada del tablero.
    */

    //obtenemos las dimesiones del alto y el ancho
    for (int i = 0; i < tablero->H ; i++){ 
        for(int j = 0; j < tablero->W; j++){
            free(tablero->celdas[i][j]); //liberamos la pieza en la celda creada con memoria dinamica
        }
        free(tablero->celdas[i]); //liberamos la celda en correspondiente ala fila
    }
    free(tablero->celdas); //liberamos la celda en si
    free(tablero); //liberamos todo el tablero
}


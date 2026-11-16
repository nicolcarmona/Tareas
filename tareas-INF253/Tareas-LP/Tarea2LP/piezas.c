#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Pieza* crear_pieza(char tipo, int hp, int x, int y){
    /*
    ***
    Parametros: un caracter donde recibe si es peon... y tres enteros con la vida y las posiciones x e y.
    ***
    Retorno: Un puntero de tipo de dato pieza
    ***
    Objetivo: Es crear una pieza para no repetir la misma logica multiples veces.
    */

    Pieza* p = (Pieza*)malloc(sizeof(Pieza)); //Creamos la pieza con memoria dinamica
    //asignamos valores
    p->tipo = tipo;
    p->hp = hp;
    p->x = x;
    p->y = y;
    return p;
}

Pieza* spawn_enemigo(struct Juego* juego, char tipo, int hp, int y, int i){
    /*
    ***
    Parametros: Un puntero de tipo de dato juego, un caracter donde recibe si es peon... y tres enteros con la vida, posicion en y, y la posicion i (indice) para saber a que enemigo corresponde en el arreglo).
    ***
    Retorno: Un puntero de tipo de dato pieza.
    ***
    Objetivo: Es crear la logica de aparicion de los enemigos.
    */
    juego->enemigos[i] = crear_pieza(tipo, hp, 0, y); //Creamos al enemigo
    do {
        juego->enemigos[i]->x = rand() % juego->t->W; //Sentencia que se repetira para encontrar una celda que este vacia a la hora de aparecer por primera vez
    }
    while(((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza != NULL);
    ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = juego->enemigos[i]; //Asignamos al enemigo a la pieza de aquella celda.
    
    return juego->enemigos[i]; //Devolvemos el enemigo especifico.
}

void eliminar_pieza(struct Juego *juego, int i){
    /*
    ***
    Parametros: Un puntero de tipo de dato juego y un entero i con el que se liberara la memoria del enemigo en especifico.
    ***
    Retorno: no tiene retorno
    ***
    Objetivo: Liberar la memoria de una pieza
    */
    ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = NULL; //Primero le asignamos nulo a la pieza.
    free(juego->enemigos[i]); //Luego liberamos al enemigo en ese lugar.
    juego->enemigos[i] = NULL; //Luego asignamos al enemigo como nulo
}

void spawn_nivel(struct Juego *juego, int nivel){
    /*
    ***
    Parametros: Un puntero de tipo de dato juego y un entero de los niveles.
    ***
    Retorno: No tiene retorno.
    ***
    Objetivo: Crear a los enemigos dependiendo del nivel en el que este
    */
    srand(time(NULL)); //para usar random
    juego->jugador = crear_pieza('R', 6, rand() % (juego->t->W - 2) + 1, 0); //Creamos al rey en una posicion aleatoria menos las esquinas
    ((Celda*)juego->t->celdas[juego->jugador->y][juego->jugador->x])->pieza = juego->jugador; //Asignamos la pieza de la celda que sea el rey (jugador)

    //Enemigos, NIVEL 1, creamos a los enemigos del nivel 1, 4 peones, 2 caballos y 2 alfiles:
    if (nivel == 1){
        juego->numeros_enemigos = 8;
        juego->enemigos = (Pieza**)malloc(8 * sizeof(Pieza*));
        for (int i = 0; i < 4; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'P',1, juego->t->H-2, i);
        }
        for(int i = 4; i < 6; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'C', 2, juego->t->H-1, i);
        }
        for(int i = 6; i < 8; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'A', 2, juego->t->H-1, i);
        }
        printf("===================================================\n");
        printf("Nivel: 1 (Plaza principal) | Enemigos restantes: %d\n", juego->numeros_enemigos);
        printf("Arsenal: [1] Escopeta (2/2) | [2] Sniper (1/1) | [3] Granada (2/2) | [4] Escudo (1/1)\n");
    }

     //Enemigos, NIVEL 2, creamos a los enemigos del nivel 2, 4 peones, 2 caballos y 2 torres:
    if (nivel == 2){
        juego->numeros_enemigos = 8;
        juego->enemigos = (Pieza**)malloc(8 * sizeof(Pieza*));

        for (int i = 0; i < 4; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'P',1, juego->t->H-2, i);
        }
        for(int i = 4; i < 6; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'C', 2, juego->t->H-1, i);
        }
        for(int i = 6; i < 8; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'T', 4, juego->t->H-1, i); 
        }
        printf("===================================================\n");
        printf("Nivel: 2 (Jardín del Rey) | Enemigos restantes: %d\n", juego->numeros_enemigos);
        printf("Arsenal: [1] Escopeta (2/2) | [2] Sniper (1/1) | [3] Granada (2/2) | [4] Escudo (1/1)\n");
    }

    //Enemigos, NIVEL 3, creamos a los enemigos del nivel 3, 2 peones, 1 reina y 1 alfiles y 1 torre:
    if (nivel == 3){
        juego->numeros_enemigos = 5;
        juego->enemigos = (Pieza**)malloc(5 * sizeof(Pieza*));
        for (int i = 0; i < 2; i++){
            juego->enemigos[i] = spawn_enemigo(juego, 'P',1, juego->t->H-2, i);
        }
        juego->enemigos[2] = spawn_enemigo(juego, 'Q',3 , juego->t->H-1, 2);
        
        juego->enemigos[3] = spawn_enemigo(juego, 'A', 2, juego->t->H-1, 3);
        
        juego->enemigos[4] = spawn_enemigo(juego, 'T', 4, juego->t->H-1, 4);

        printf("===================================================\n");
        printf("Nivel: 3 (Entrada del castillo - Ubicación Final) | Enemigos restantes: %d\n", juego->numeros_enemigos);
        printf("Arsenal: [1] Escopeta (2/2) | [2] Sniper (1/1) | [3] Granada (2/2) | [4] Escudo (1/1)\n");
    }
}

void mover_enemigos(struct Juego *juego){
    /*
    ***
    Parametros: Un puntero de tipo de dato juego.
    ***
    Retorno: No tiene retorno.
    ***
    Objetivo: Mover a los enemigos y verificar si el rey murio (checkmate).
    */
    for(int i = 0; i < juego->numeros_enemigos; i++){
        if(juego->enemigos[i] != NULL){
            if(juego->enemigos[i]->tipo == 'P'){
                int distancia_con_rey_y = juego->jugador->y - juego->enemigos[i]->y; //Distancia y con el rey
                int distancia_con_rey_x  = juego->jugador->x - juego->enemigos[i]->x; //Distancia x con el rey

                int mover_y = (distancia_con_rey_y > 0) ? 1 : -1;  //Movimiento peon, solo eje y, esto funciona igual que un if/else, pero mas corto, entonces si la distancia es mayor a 0, puede subir (1) o bajar (-1)
                if(abs(distancia_con_rey_x) == 1 && distancia_con_rey_y == mover_y && juego->turno_escudo <= 0){ //Si el movimiento que hara es donde esta el rey, entonces jaque mate al rey ademas, se usa abs() [valor absoluto] para que no de valores negativos (ya que algunas operaciones pueden terminar siendo negativas pero solo necesitamos el valor de cuanto da esa distancia, no su signo)
                    juego->jugador->hp = 0; //Si el rey esta en jaque mate (es decir esta en su diagonal o frontal)
                    printf("☠︎︎ Checkmate, fin del juego ☠︎︎\n");
                }
                else {
                    int nueva_pos_y = juego->enemigos[i]->y + mover_y;
                    if(nueva_pos_y >= 0 && nueva_pos_y < juego->t->H){ //para validar que este en el rango del tablero para que no se salga
                        Celda* destino = (Celda*)juego->t->celdas[nueva_pos_y][juego->enemigos[i]->x]; //Esto es para ver si la celda en la que se va a mover el enemigo esta ocupada o no

                        if(nueva_pos_y == juego->jugador->y && juego->enemigos[i]->x == juego->jugador->x && juego->turno_escudo <= 0){ //Si la nueva posicion corresponde a la posicion del rey entonces rip rey
                            juego->jugador->hp = 0;
                            printf("☠︎︎ Checkmate, fin del juego ☠︎︎\n");
                        }
                        // si no hay pieza en esa celda, entonces se quedara ahi
                        else if(destino->pieza == NULL){
                            ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = NULL;
                            juego->enemigos[i]->y = nueva_pos_y;
                            ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = juego->enemigos[i];
                            
                        }
                    }   
                }
            }
            else if(juego->enemigos[i]->tipo == 'C'){
                int movimientos_caballo[8][2] = {{2,-1},{2,1},{-2,1},{-2,-1},{1,2},{1,-2},{-1, 2},{-1,-2}}; //Los posibles movimientos del caballo
                long int mejor_distancia = 9999999999; //Esto es para obtener el mejor movimiento del caballo hacia el rey, aquel mov que acorta mas distancia
                //Mejor_y e mejor_x, para guardar la mejor posicion en y o x para acortar la distancia.
                int mejor_y = -1;
                int mejor_x = -1;
                for(int j = 0; j < 8; j++){
                    int mover_y = juego->enemigos[i]->y + movimientos_caballo[j][1]; //Movimientos en y
                    int mover_x = juego->enemigos[i]->x + movimientos_caballo[j][0]; //Movimientos en x
                    if (mover_x < juego->t->W && mover_y < juego->t->H && mover_x >= 0 && mover_y >= 0){ //Verificamos el limite
                        Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x];
                        if(mover_y == juego->jugador->y && mover_x == juego->jugador->x  && juego->turno_escudo <= 0){ //SI esta en la misma posicion que el rey, entonces checkmate al rey
                            mejor_y = juego->jugador->y;
                            mejor_x = juego->jugador->x;
                            juego->jugador->hp = 0;
                            printf("☠︎ Checkmate, fin del juego ☠︎\n");
                            break;
                        }
                        //Si la pieza es nula, se calculara la mejor distancia para acercarse al rey (usando la formula clasica de Pitagora)
                        else if(destino->pieza == NULL){
                            int distancia_y = juego->jugador->y - mover_y;
                            int distancia_x = (juego->jugador->x) - mover_x;
                            int distancia = (distancia_y * distancia_y) + (distancia_x * distancia_x);
                            if (distancia < mejor_distancia){ //Si la distacia nueva es mejor (mas corta) entonces se cambiara la nueva distancia y sus valores.
                                mejor_distancia = distancia;
                                mejor_y = mover_y;
                                mejor_x = mover_x;
                            } 
                        }
                    }              
                }
                if (mejor_y != -1 && mejor_x != -1){ //Si son distintos a -1, el enemigo va a cambiarse a ese nuevo lugar, dejando la celda donde estaba nula y actualizando sus valores.
                    ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = NULL;
                    juego->enemigos[i]->y = mejor_y;
                    juego->enemigos[i]->x = mejor_x;
                    ((Celda*)juego->t->celdas[mejor_y][mejor_x])->pieza = juego->enemigos[i];
                }       
            }
            else if(juego->enemigos[i]->tipo == 'A'){
                int movimientos_alfil[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
                long int mejor_distancia = 9999999999;
                int mejor_y = -1;
                int mejor_x = -1;
                for(int j = 0; j < 4; j++){
                    for(int k = 1; k <= 3; k++){ //aqui esto permite calcular las casillas en las que se podra mover, siendo el maximo 3.
                        int mover_y = juego->enemigos[i]->y + (movimientos_alfil[j][1] * k);
                        int mover_x = juego->enemigos[i]->x + (movimientos_alfil[j][0] * k);
                        if(mover_x >= juego->t->W || mover_y >= juego->t->H || mover_x < 0 || mover_y < 0) break; //si sale de los limites del tablero entonces rompemos el for de las "k".
                        
                        Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x];
                        if(mover_y == juego->jugador->y && mover_x == juego->jugador->x && juego->turno_escudo <= 0){
                            mejor_y = juego->jugador->y;
                            mejor_x = juego->jugador->x;
                            juego->jugador->hp = 0;
                            printf("☠︎ Checkmate, fin del juego ☠︎\n");
                            break;
                        }

                        else if(destino->pieza == NULL){
                            int distancia_y = juego->jugador->y - mover_y;
                            int distancia_x = (juego->jugador->x) - mover_x;
                            int distancia = (distancia_y * distancia_y) + (distancia_x * distancia_x);
                            if (distancia < mejor_distancia){
                                mejor_distancia = distancia;
                                mejor_y = mover_y;
                                mejor_x = mover_x;
                            } 
                        }
                        else break;
                    }
                        
                }
                if (mejor_y != -1 && mejor_x != -1){
                    ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = NULL;
                    juego->enemigos[i]->y = mejor_y;
                    juego->enemigos[i]->x = mejor_x;
                    ((Celda*)juego->t->celdas[mejor_y][mejor_x])->pieza = juego->enemigos[i];
                } 
            }
            else if(juego->enemigos[i]->tipo == 'T'){
                //Misma logica que con el alfil, con la unica diferencia es que la torre se mueve en turnos pares.
                if (juego->turno_enemigos % 2 == 0){
                    int movimientos_torre[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
                    long int mejor_distancia = 9999999999;
                    int mejor_y = -1;
                    int mejor_x = -1;
                    for(int j = 0; j < 4; j++){
                        for(int k = 1; k <= 3; k++){
                            int mover_y = juego->enemigos[i]->y + (movimientos_torre[j][1] * k);
                            int mover_x = juego->enemigos[i]->x + (movimientos_torre[j][0] * k);
                            if(mover_x >= juego->t->W || mover_y >= juego->t->H || mover_x < 0 || mover_y < 0) break;
                            
                            Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x];
                            if(mover_y == juego->jugador->y && mover_x == juego->jugador->x && juego->turno_escudo <= 0){
                                mejor_y = juego->jugador->y;
                                mejor_x = juego->jugador->x;
                                juego->jugador->hp = 0;
                                printf("☠︎ Checkmate, fin del juego ☠︎\n");
                                break;
                            }

                            else if(destino->pieza == NULL){
                                int distancia_y = juego->jugador->y - mover_y;
                                int distancia_x = (juego->jugador->x) - mover_x;
                                int distancia = (distancia_y * distancia_y) + (distancia_x * distancia_x);
                                if (distancia < mejor_distancia){
                                    mejor_distancia = distancia;
                                    mejor_y = mover_y;
                                    mejor_x = mover_x;
                                } 
                            }
                            else break;
                        }
                            
                    }
                    if (mejor_y != -1 && mejor_x != -1){
                        ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = NULL;
                        juego->enemigos[i]->y = mejor_y;
                        juego->enemigos[i]->x = mejor_x;
                        ((Celda*)juego->t->celdas[mejor_y][mejor_x])->pieza = juego->enemigos[i];
                    } 
                }
            }
            else if(juego->enemigos[i]->tipo == 'Q'){
                //Unificamos la logica del alfil y la torre.
                int movimientos_reina[8][2] = {{1,1},{1,-1},{-1,1},{-1,-1}, {0,1},{0,-1},{1,0},{-1,0}};
                long int mejor_distancia = 9999999999;
                int mejor_y = -1;
                int mejor_x = -1;
                for(int j = 0; j < 8; j++){
                    for(int k = 1; k <= 4; k++){
                        int mover_y = juego->enemigos[i]->y + (movimientos_reina[j][1] * k);
                        int mover_x = juego->enemigos[i]->x + (movimientos_reina[j][0] * k);
                        if(mover_x >= juego->t->W || mover_y >= juego->t->H || mover_x < 0 || mover_y < 0) break;
                        
                        Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x];
                        if(mover_y == juego->jugador->y && mover_x == juego->jugador->x && juego->turno_escudo <= 0){
                            mejor_y = juego->jugador->y;
                            mejor_x = juego->jugador->x;
                            juego->jugador->hp = 0;
                            printf("☠︎ Checkmate, fin del juego ☠︎\n");
                            break;
                        }

                        else if(destino->pieza == NULL){
                            int distancia_y = juego->jugador->y - mover_y;
                            int distancia_x = (juego->jugador->x) - mover_x;
                            int distancia = (distancia_y * distancia_y) + (distancia_x * distancia_x);
                            if (distancia < mejor_distancia){
                                mejor_distancia = distancia;
                                mejor_y = mover_y;
                                mejor_x = mover_x;
                            } 
                        }
                        else break;
                    }
                        
                }
                if (mejor_y != -1 && mejor_x != -1){
                    ((Celda*)juego->t->celdas[juego->enemigos[i]->y][juego->enemigos[i]->x])->pieza = NULL;
                    juego->enemigos[i]->y = mejor_y;
                    juego->enemigos[i]->x = mejor_x;
                    ((Celda*)juego->t->celdas[mejor_y][mejor_x])->pieza = juego->enemigos[i];
                } 
            }
        }      
    }
    //esto es parte del arma especial.
    if(juego->turno_escudo > 0){ //si el escudo esta activado
        juego->turno_escudo--; // se desminuira el turno
        printf("Escudo activo! Turnos restantes: %d\n", juego->turno_escudo);
    }
}

bool verificar_estado_rey(struct Juego *juego){
    /*
    ***
    Parametros: Un puntero de tipo de dato juego.
    ***
    Retorno: Un booleano.
    ***
    Objetivo: Verifica si el rey se encuentra en Jaque.
    */
    for(int i = 0; i < juego->numeros_enemigos; i++){
        if(juego->enemigos[i] != NULL && juego->enemigos[i]->hp > 0){
            if(juego->enemigos[i]->tipo == 'P'){
                int distancia_con_rey_y = juego->jugador->y - juego->enemigos[i]->y;
                int distancia_con_rey_x = juego->jugador->x - juego->enemigos[i]->x;

                int mover_y = (distancia_con_rey_y > 0) ? 1 : -1;
                if (mover_y == distancia_con_rey_y && (abs(distancia_con_rey_x) <= 1)) return true; //Si donde se movio el peon, esta a la misma distancia que se encuentra el rey, entonces esta el jaque
            }
            else if(juego->enemigos[i]->tipo == 'C'){
                int distancia_con_rey_y = juego->jugador->y - juego->enemigos[i]->y;
                int distancia_con_rey_x = juego->jugador->x - juego->enemigos[i]->x;

                if ((abs(distancia_con_rey_x) == 2 && abs(distancia_con_rey_y)== 1) || (abs(distancia_con_rey_y) == 2 && abs(distancia_con_rey_x) == 1)) return true; //Si donde se movio el caballo, esta a la misma distancia que se encuentra el rey, entonces esta el jaque
            }
            else if(juego->enemigos[i]->tipo == 'A'){
                int movimientos_alfil[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
                for(int j = 0; j < 4; j++){
                    for(int k = 1; k <= 3; k++){
                        int mover_y = juego->enemigos[i]->y + (movimientos_alfil[j][1] * k);
                        int mover_x = juego->enemigos[i]->x + (movimientos_alfil[j][0] * k);
                        if(mover_x >= juego->t->W || mover_y >= juego->t->H || mover_x < 0 || mover_y < 0) break;

                        if(mover_y == juego->jugador->y && mover_x == juego->jugador->x) return true; //Si donde se movio el alfil, esta a la misma distancia que se encuentra el rey, entonces esta el jaque                    
                        
                        Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x];

                        if(destino->pieza != NULL) break; //Esto es debido a que el alfil no puede atravesar piezas, asi que no podria ver si el rey se encuentra en jaque si hay una pieza por medio
                    }
                }
            }
            else if(juego->enemigos[i]->tipo == 'T'){
                int movimientos_torre[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
                for(int j = 0; j < 4; j++){
                    for(int k = 1; k <= 3; k++){
                        int mover_y = juego->enemigos[i]->y + (movimientos_torre[j][1] * k);
                        int mover_x = juego->enemigos[i]->x + (movimientos_torre[j][0] * k);
                        if(mover_x >= juego->t->W || mover_y >= juego->t->H || mover_x < 0 || mover_y < 0) break;
                        
                        if(mover_y == juego->jugador->y && mover_x == juego->jugador->x) return true; //Si donde se movio la torre, esta a la misma distancia que se encuentra el rey, entonces esta el jaque
                        
                        Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x];

                        if(destino->pieza != NULL) break; //Esto es debido a que la torre no puede atravesar piezas, asi que no podria ver si el rey se encuentra en jaque si hay una pieza por medio

                    }
                }
            }
            else if(juego->enemigos[i]->tipo == 'Q'){
                int movimientos_reina[8][2] = {{1,1},{1,-1},{-1,1},{-1,-1}, {0,1},{0,-1},{1,0},{-1,0}};
                for(int j = 0; j < 8; j++){
                    for(int k = 1; k <= 4; k++){
                        int mover_y = juego->enemigos[i]->y + (movimientos_reina[j][1] * k);
                        int mover_x = juego->enemigos[i]->x + (movimientos_reina[j][0] * k);
                        if(mover_x >= juego->t->W || mover_y >= juego->t->H || mover_x < 0 || mover_y < 0) break;

                        if(mover_y == juego->jugador->y && mover_x == juego->jugador->x) return true; //Si donde se movio el peon, esta a la misma distancia que se encuentra el rey, entonces esta el jaque
                        
                        Celda* destino = (Celda*)juego->t->celdas[mover_y][mover_x]; //Esto es debido a que la reina no puede atravesar piezas, asi que no podria ver si el rey se encuentra en jaque si hay una pieza por medio

                        if(destino->pieza != NULL) break;
                    }
                }
            }
        }
    }
    return false;
}

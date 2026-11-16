# Tarea 2 - INF253

**Nicol Carmona**

------------------------------------------

- **Sistema Operativo**

    Distributor ID: Ubuntu

    Description:    Ubuntu 24.04.2 LTS

    Release:        24.04

    Codename:       noble

-------------------------------------------
## ¿Cómo funciona?: 
En la terminal, se ejecturará el juego, tu posicion es la de "R" en el tablero.
Movimiento: WASDQEZC / Para armas = 1234 y su direccion de disparo en WASDQEZC
Tu objetivo es pasar todos los niveles y ganar!

-------------------------------------------

## Compilación del código: 
Utilizando Makefile se emplearon 3 códigos:

-make -> Para compilar

-make run -> Para compilar y ejecutar

-make clean -> Para borrar los archivos compilados

-------------------------------------------
## Cosas a tener en consideración acerca del código: 

### Arma especial:
Decidí que el arma especial, sería un escudo que dure 2 turnos desde que se activa, la idea es que protega al jugador cuando está en jaque mate, permitiendo que se mueva o dispare (en el segundo turno), esta no se recarga y solo se puede ocupar 1 vez por nivel.

### Observaciones y supuestos:
1) Ya que el PDF, solo dice que el Rey muere si está en una casilla alcanzable por un enemigo, se asumió que podía morir aunque no esté en jaque (No como el ajedrez).

2) No se hizo cambios en los headers, pero si se puso nombres a las typedef y structs, ya que al principio me daba error para compilar.

3) Se agregaron funciones extras en piezas.h para no escribir mismas logicas múltiples veces.

5) Se supuso, en relación al movimiento del peon, este se puede mover en el eje y (Hacia arriba y abajo), por lo que el ataque "frontal al rey" se lograría si el rey está arriba del peon o abajo.

6) Favor de no poner dobles WW o SS, al movimiento, ya que puede pasar que mueva doble.
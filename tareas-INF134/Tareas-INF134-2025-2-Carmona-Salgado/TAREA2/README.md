# Tarea 2 - INF134

*Integrantes:* Nicol Carmona ~ Martina Salgado.
- **Sistema Operativo:**

	Distributor ID: Ubuntu

	Description:    Ubuntu 24.04.2 LTS

	Release:        24.04

	Codename:       noble

- **Compilador:**

  	g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
  
  	gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0

  	***C++ 17***

-------------------------------------------
## Características de funcionamiento:
Este código recrea mediante la terminal el juego de cartas "Balatro", un juego de Poker al estilo solitario utilizando arboles ABB, listas enlazadas y diversas funciones.

-------------------------------------------
## ¿Cómo funciona?: 
El juego consiste en vencer 3 ciegas utilizando las cartas aleatorias en tu mano, superando el puntaje de cada pozo evitando quedarte sin jugadas. 

#### Modificacion ciega jefe elegida: 
Se eligió el boss de grillete que disminuye el tamaño de la mano del jugador

-------------------------------------------

## Compilación del código: 
Utilizando Makefile se emplearon 3 código (Al compilar por primera vez es un proceso algo tardado, favor de tener paciencia)

-make -> Para compilar

-make run -> Para compilar y ejecutar

-make clean -> Para borrar los archivos compilados

-------------------------------------------
## Cosas a tener en consideración acerca del código: 
En la parte del código en que se implementa la mano "Color", se utiliza la cantidad de cartas del jugador elige en vez de asumir que siempre serán 5 cartas, debido a que en el enunciado se especifica TODAS las cartas jugadas, y que el usuario puede jugar hasta cinco cartas. Detallamos esto puesto que en el discord hubo una pregunta acerca de esta mano y la cantidad de cartas, pero preferimos apegarnos al enunciado. Para el calculo de las fichas se utilizó el valor de la carta y no su categoría. 

Se implementaron dos funciones auxiliares con el propósito de hacer más fácil el cálculo de las fichas en la función FichasPorRonda; una de ellas es para calcular la sumatoria de las cartas con distinto valor, y la otra para obtener la suma de los valores que se repiten.

Los archivos nicol.cpp e ina.cpp son los documentos en los que cada una trabajó para evitar sobreescrituras de código y problemas con los push/pull, luego unimos todo en el archivo main.cpp

En relación al github, este repositorio tiene 3 contribudores ya que en la anterior tarea nuestras las parejas fueron otras personas y se creó otra carpeta no más en este repositorio, pero en los commits se puede ver que solo escribimos nosotras y no la otra persona.

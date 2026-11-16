# Tarea 3 - INF134

*Integrantes:* Nicol Carmona ~ Martina Salgado
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
Este código consiste en probar 5 funciones con informacion de un grafo escrito en un archivo txt, cada funcion entregará información distinta.
Simulando las redes de comunicacion de facebook aka sansabook

-------------------------------------------
## ¿Cómo funciona?: 
 En la terminal se presenta un menú de 6 opciones.
 1. Sugerir amigos
 2. Usuario más popular
 3. Contar comunidades
 4. Calcular influencia
 5. Puentes encontrados
 0. Salir
Cada opcion te entrega ciertos datos
Hasta que no se ingrese un 0, este se repitirá solicitando nuevas opciones.
-------------------------------------------

## Compilación del código: 
Utilizando Makefile se emplearon 3 código (Al compilar por primera vez es un proceso algo tardado, favor de tener paciencia)

-make -> Para compilar

-make run -> Para compilar y ejecutar

-make clean -> Para borrar los archivos compilados

-------------------------------------------
## Cosas a tener en consideración acerca del código: 
Se agregó validaciones por ejemplo, al escribir el ID, pero se asumirá que no se ingresarán letras para intentarlo, ya que eso hace que se cree un bucle infinito (Ya que recibe un int y no string)


Los archivos nicol.cpp e ina.cpp son los documentos en los que cada una trabajó para evitar sobreescrituras de código y problemas con los push/pull, luego unimos todo en el archivo main.cpp


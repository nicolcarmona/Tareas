# Tarea 3 - INF253 - JAVA

**Nicol Carmona**

-------------------------------------------
## ¿Cómo funciona?: 
El jugador inicia con un menú donde puede decidir donde ir mediante ciertas opciones.

-------------------------------------------

## Compilación del código: 
Utilizando Makefile se emplearon 3 códigos:

-make -> Para compilar

-make run -> Para ejecutar lo compilado

-make clean -> Para borrar los archivos compilados

-------------------------------------------

## Probabilidad EnemigoSimulador:
Eligí un 30% de que aparezcan 2 enemigos. Además para atacar, Cloud eligirá a quien ataca, mediante un sub menú.

-------------------------------------------

## Cosas que se agregó:
1) Metodos extra en jugador:
    a) recbirDMG: para el daño que recibe Cloud y logica de cargado de limite.
    b) agregarMateriaMochila: Permite agregar las materias en la mochila del jugador. 
    c) cargarlimite: Sirve para validaciones del calculo del ataque limite de Cloud.
    d) un get y set de la derrota: es para que vuelva a sector 7 cuando muera.

2) Metodos extra en arma:
    a) equiparMateria: para agregar las amterias para el arma.
3) Se modificó el argumento del metodo lanzarSuperNova de Sephiroth agregando Jugador cloud, para poder poner su vida en 0. Además, se agregó un metodo extra: resetContador: reinicia el contador de lanzar la supernova a 0.

4) Metodo extra en Gongaga: 
    a) crearEnemigo: simplemente es para poder crear instancias de enemigos y no ocupar las mismas hasta que dejen de aparecer enemigos (me pasó compilando xd) 

5) Clase extra en compontentes, llamada Combate: Es la logica del combate para todos los enemigos.
    a) turnoEnemigo: logica que se va a repetir en cada turno del enemigo (ataque)
    b) verificarMuertos: logica que tambien se repite para ver si los enemigos estan vivos (por las probabilidades de que aparezcan mas de uno)
    c) iniciarCombate: inicia el combate valga la redundancia.

6) Se modificó el argumento de accionZona(Jugador) de la clase abstracta, por accionZona(Jugador, Scanner), ya que al compilar había un warning por no cerrar el Scanner y eso, luego me daba error al compilar.


### Supuestos:
1) Se asumió que se escribirá correctamente la opcion elegida es decir 1, 2, para evitar que aparezcan errores que pueda hacer que se cierre el programa. (se agregaron igualmente algunos try-catch)

2) Ya que no se especifica en qué momento, el jugador puede colocar materia a su arma, decidí que podría ser en el menu, accediendo a la mochila (Es decir siempre puede hacerlo, respetando claro las reglas del arma).

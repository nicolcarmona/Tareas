# Tarea 1 - INF253

**Nicol Carmona**

- **Sistema Operativo**

    Distributor ID: Ubuntu

    Description:    Ubuntu 24.04.2 LTS

    Release:        24.04

    Codename:       noble

    Python Version:  Python 3.12.3

-------------------------------------
## Características de funcionamiento:
Este código consiste en analizar un archivo de texto "programa.txt" donde se encuentra la información de un código en formato c++, siendo capaz de separar en distintos archivos de texto cada estilo de cada funcion (snake_case, camelCase, PascalCase o desconocido en caso que no entre en ninguna función)

-------------------------------------
## Instrucciones de uso:
1. Tener Python instalado
2. Colocar programa.txt en el mismo directorio que Evaluador.py
3. Ejecutar "python3 Evaluador.py"

-------------------------------------
## Cosas que se tuvo en consideración a la hora de crear el código:
- el programa no contempla palabras con tildes ni presencia de "ñ" tampoco estructuras como struct o class (por la complejidad de crear un nuevo dato y punteros)

- Casos desconocidos son: Presencia de digitos en estilos, mezclas de estilos, todo mayúscula o minúscula

- En las funciones, condiciones y etc, se asumió que podria existir (int i =           0), ya que esto no entrega error de sintaxis en c++, debido a que el compilador ignora los espacios de mas.

- En la funcion, se asumió que el parametro también estaba en snake_case, ya que si la funcion es snake, no tendría sentido que el parametro sea de otro

- El conteo de llaves es general como se puede ver el PDF [version 21-03] por lo que al estar abierta una estructura de control y tambien una funcion, esto cuenta como "error de cierre de llave" general y solo se suma 1 error de sintaxis.

- Las palabras reservadas se asumió que estarán bien escritas.

- Ya que en el eBNF entregado, la variable es un unico resultado, se asumió que no pedirá operaciones como por ejemplo float AreaTriangulo = (base * altura)/2

-En relación a la generación de archivos, este programa NO genera txt vacíos, así que si en el programa.txt no hay funciones snake o camel o pascal o desconocido, estas no se crearán, solo se crean cuando se detectan esas funciones

### Errores de sintaxis que se consideraron:

1) cierre ";" en variables declaradas

2) cierre de "}" en funciones o estructuras de forma general. 

3) funciones y variables mal declaradas (tipo de dato juntos, o parentesis no puestos)

4) el programa es capaz de soportar comentarios y funciones en una unica linea


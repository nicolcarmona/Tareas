-- Nicol Carmona --

- ¿Cómo funciona?
    Opcion 1:
    1) Abrir "malla.pl" con SWI-Prolog
    2) Realizar las consultas en la terminal
    Opcion 2:
    1) Abrir SWI-Prolog
    2) Click en "File" y luego click en consultar
    3) En la terminal debería aparecer "true" (confirmando que se realizo la conexión correctamente)
    4) Escribir las consultas en la terminal.

- Predicados auxiliares:
    1. ramos_disponibles = Entrega los ramos disponibles en la malla.
    2. seleccionar_ramos = Selecciona los ramos que cumplan las condiciones solicitadas.
    3. plan_optimo = Entrega el mejor plan correspondiente al maximo de creditos.
    4. ramos_disponibles_reforma = Entrega los ramos disponibles luego de aplicarle la reforma.
    5. plan_optimo_reforma = Entrega el mejor plan correspondiente al maximo de creditos, luego de aplicarle la reforma.

- Comentarios menores:
    - En relación al ejemplo del la pregunta 4.4. Creo que está mal. Ya que IWG-400 es de 2do semestre, por lo que MAT-070 tiene prioridad ya que es de 1r semestre, por lo tanto no se haría ningun cambio, quedarian vacias.
    - No se agregó una descripcion como tal en los comentarios de los predicados ya que, creo que las Salidas + los comentarios de la propia funcion, lo explican bien

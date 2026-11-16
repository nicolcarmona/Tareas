#lang scheme
;P1:
;ARGUMENTOS: recibe un daemon y una lista puertos en la que se va a iterar
;FUNCION: mediante recursion simple, en cada elemento de la lista puertos se le evalua un daemon.
;RETORNO: si la lista esta vacia retornara una lista vacia y si eso es falso, el retornara una lista con los elementos de puertos evaluando el daemon (por ejemplo en puerto x =  5 y el daemon es (x + 15)mod 10 -> (5 + 15)%10, en resto es 0, entonces en la lista el primer elemento sera 0) y asi sucesivamente se sigue llamando a la funcion hasta terminar la lista
(define (icebreaker-simple daemon puertos)
  (if (null? puertos) '() (cons (daemon (car puertos)) (icebreaker-simple daemon (cdr puertos))))
)

;ARGUMENTOS: recibe un daemon, una lista puertos y una lista acumulador (su objetivo es ir guardando los elementos de puerto despues de evualuar el daemon para no llenar el stack de memoria)
;FUNCION: realizar la recursion de forma indirecta por cola de la lista puertos
;RETORNO: si la lista esta vacia, invierte la lista acumulador (para que se vea en orden original), si es falso, entonces, mediante recursion va aplicando el daemon en el primer elemento y lo ingresa en el acumulador, con el resto de los elementos de la lista ve los elementos que quedan en la lista (con daemon aplicado) y va aplicando el nuevo acumulador para las iteraciones
(define (icebreaker-recursion-cola daemon puertos acumulador)
  (if (null? puertos) (reverse acumulador) (icebreaker-recursion-cola daemon (cdr puertos) (cons (daemon (car puertos)) acumulador)))
 )

;ARGUMENTOS: un daemon y una lista puertos
;FUNCION: llamar la funcion auxiliar que aplica la recursion mediante cola
;RETORNO: una lista con recursion
(define (icebreaker-cola daemon puertos)
    (icebreaker-recursion-cola daemon puertos '()) ;aqui hacemos llamamos a la funcion donde se hace la recursion de la cola
)
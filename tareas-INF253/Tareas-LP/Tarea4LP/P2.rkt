#lang scheme
;P2:
;ARGUMENTOS: recibe una funcion con algun criterio
;FUNCION: entregar una lista que cumpla las condiciones de vulnerabilidad
;RETORNO: una lista con las 'X' marcadas en numeros que no son vulnerables
(define(crear-gusano vulnerabilidad)
  (define gusano (lambda (memoria) ;creamos un gusano para poder hacer recursion con la lista que es entregada (memoria)
    (cond
      ((null? memoria) '()) ; caso si memoria esta vacia
      ((pair? (car memoria)) (cons (gusano (car memoria)) (gusano (cdr memoria)))); caso si memoria tiene listas anidadas, por recursion va viendo los elementos de la lista pasando por el primer elemento hasta el resto.
      ((number? (car memoria)) (cons (if (vulnerabilidad (car memoria)) (car memoria) 'X) (gusano (cdr memoria)))) ;si son numeros (n) entonces, por la condicion de vunerabilidad, si el numero es vulnerable se mantiene tal cual, pero  si no, se le aplicara la x y se seguira revisando la lista por recursion
    )
   )
  )
  gusano ;retorna la lista con las X
)
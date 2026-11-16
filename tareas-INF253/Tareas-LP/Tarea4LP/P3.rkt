#lang scheme
;P3:
;ARGUMENTOS: recibe un numero y una lista de daemons
;FUNCION: aplicar recursion en las listas anidadas del daemon para poder aplicarlo en el numero
;RETORNO: una lista con los numeros que les aplico los daemons
(define (aplicar-daemons numero daemons) 
  (if (null? daemons) numero (aplicar-daemons ((car daemons) numero) (cdr daemons)))
)

;ARGUMENTOS: recibe un mapa y una lista de daemons
;FUNCION: ejectutar un ataque (aplicar los daemons) en la lista del mapa
;RETORNO: retorna una lista con los valores aplicados del ataque
(define(ejecutor-cascada mapa daemons)
  (cond
    ((null? mapa) '())
    ((equal? (car mapa) 'X)(ejecutor-cascada (cdr mapa) daemons)) ;si es una x, entonces la eliminamos de la lista (es decir simplemente no la incluimos en la lista retornada
    ((pair? (car mapa)) (cons (ejecutor-cascada (car mapa) daemons) (ejecutor-cascada (cdr mapa) daemons))) ; si es un lista (lista en el mapa) realizamos recursion para iterar en la lista y ver si se le puede aplicar el daemon (es decir si tiene numeros o X en su interior por eso usamos la recurison) 
    ((number? (car mapa)) (cons (aplicar-daemons (car mapa) daemons) (ejecutor-cascada (cdr mapa) daemons))) ; si es un numero, aplicamos la funcion extra que itera en la lista de los daemons y se la aplica en el numero del mapa
  ) ; y con cons se junta todo para ser retornado en la terminal :)
)
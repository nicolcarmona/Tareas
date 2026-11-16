#lang scheme
;P4:
;ARGUMENTOS: recibe un token (una palabra)
;FUNCION: aplicarle una serie de "caracteristicas" a una palabra para obtener la suma total de sus elementos en ascii
;RETORNO: la suma total de los numeros ascii del token
(define (hash-desconexion token)
  ;paso 1: string->list token (transformar a lista de caracteres)
  ;paso 2: aplicartle filter char-alphabetic? a lo anterior (filtra caracteres que no son del alfabeto)
  ;paso 3: map char->integer a lo anterior (transformar caracteres anteriores a su valor ASCII, uso map para aplicarlo a cada elemento de la lista)
  ;paso 4: foldl + 0 a lo anterior (acumulador para sumar los numeros anteriores)
  (foldl + 0 (map char->integer(filter char-alphabetic? (string->list token))))
)

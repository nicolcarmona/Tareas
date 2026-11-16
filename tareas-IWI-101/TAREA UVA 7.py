def mas_popular(lista):
    #reinicio variables
    lista_todo = []
    lista_sin = []
    lista_final = []
    max = -1

    #Sacar 2 listas, una con todos los platos de la lista y una sin las repeticiones
    for listas in lista:
        for platos in listas:
            lista_todo.append(platos)
            if platos not in lista_sin:
                lista_sin.append(platos)

    #Realizar conteo de los platos en la lista con todos los platos y sacar el maximo con su nombre 
    for nombre in lista_sin:
        conteo = lista_todo.count(nombre)
        if max < conteo:
            max = conteo
            nombre_plato = nombre

    #Agregar el maximo y el nombre del plato a la lista final
    lista_final.append(max)
    lista_final.append(nombre_plato)

    return lista_final

def similares(plato_base , recomendaciones):
    lista_similar = []
    lista_sin_base = []
    lista_sin_repetir = []
    lista_elementos= []
    lista_final = []

    #Crear una lista con todas las listas del plato base que se busca
    for listas in recomendaciones:
        if plato_base in listas:
            lista_similar.append(listas)

    #Crear 2 listas, una donde estan todos los platos donde aparece el plato base (exceptuando el plato base) y una sin las repeticiones dentro de la lista
    for cada_lista in lista_similar:
        for platos in cada_lista:
            if plato_base != platos:
                    lista_sin_base.append(platos)
                    if platos not in lista_sin_repetir:
                        lista_sin_repetir.append(platos)

    #Realizar el conteo y agregarla a una lista con 2 sublistas donde estará la cantidad del plato y el plato
    for platos in lista_sin_repetir:
        conteo = lista_sin_base.count(platos)
        lista_elementos.append([conteo , platos])
        lista_elementos.sort()
        lista_elementos.reverse()

    #Crear la lista final con solamente los nombres de los platos 
    for listas in lista_elementos:
         lista_final.append(listas[1])

    return lista_final    

recomendaciones = [
    ["Pad thai", "Costillar cantones", "Lasagna"],
    ["Ceviche", "Lomo saltado", "Pastel de choclo"],
    ["Pastel de choclo", "Cazuela", "Ceviche"],
    ["Lasagna"],
    ["Fettuccine al pesto", "Lasagna"],
    ["Ceviche", "Pastel de choclo", "Lasagna", "Cazuela"]
    ]

print (mas_popular(recomendaciones))
print(similares("Ceviche", recomendaciones))

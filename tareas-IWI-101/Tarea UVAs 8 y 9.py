#FUNCIÓN 1:
def ganadores_tipo_torneo(nombre_archivo, tipo, año):
    #Reinciio de variables
    archivo = open(nombre_archivo)
    clasificacion = {}
    elementos = []
    
    #Procesar cada línea del archivo y traspasarlo a una lista cada línea.
    for lineas in archivo:
        años, perdedor, sets_perdedor, ronda , tipos, torneo , ganador, sets_ganador = lineas.strip().split(";")
        elementos.append([años, perdedor.strip(), sets_perdedor, ronda , tipos, torneo , ganador.strip(), sets_ganador])
    #Procesar cada lista que corresponde a una línea del archivo.
    for listas in elementos:
        #Establecer las restrincciones correspondientes (Para que identifique lo que se busca y traspasarlo a un diccionario).
        if str(año) == listas[0] and tipo == listas[4] and listas[3] == "The Final":
            marcador = "{}" "-" "{}".format(listas[7], listas[2])
            if listas[6] not in clasificacion:
                clasificacion[listas[6]] = []
            clasificacion[listas[6]].append([listas[1], listas[5], marcador])
    archivo.close()
    return clasificacion
print(ganadores_tipo_torneo("datos_atp.csv","Masters",2005))

#FUNCIÓN 2:
def construir_resumen(nombre_archivo, año1, año2):
    #Reinicio de variables y creación del nuevo archivo
    archivo = open(nombre_archivo)
    resultado = open("resumen_ATP_{}-{}.txt".format(año1,año2), "w")
    resultado.write("Asociación de Tenis de Pythonia\n")
    resultado.write("Resumen {}-{}\n".format(año1, año2))
    elementos = []
    cantidad_jugadores = []
    año_variable = (año1)

    #Procesamiento de cada línea del archivo y meterlo a una lista:
    for lineas in archivo:
        años, perdedor, sets_perdedor, ronda , tipos, torneo , ganador, sets_ganador = lineas.strip().split(";")
        elementos.append([años, perdedor.strip(), sets_perdedor, ronda , tipos, torneo , ganador.strip(), sets_ganador])
    
    #Ciclo while para cada año que va a procesar con su correspondiente reinicio de variables.
    while año_variable <= año2:  
        i = 1
        conteo = {}
        valores = []
        resultado.write("\n")
        resultado.write("Jugadores con más partidos ganados en {}\n".format(año_variable))
        #Conteo:
        for listas in elementos: 
            if listas[0] == str(año_variable):
                if listas[6] not in conteo:
                    conteo[listas[6]] = 0
                conteo[listas[6]] += 1
        #Ciclo while para el conteo la posición de los 10 mejores.
        while i <= 10:
            resultado.write("\n")
            #Creación de la lista con el conteo:
            for llave in conteo:
                valores.append([conteo[llave], llave])
                valores.sort()
                valores.reverse()
                valores = valores[:10]
            for elemento in valores:
                resultado.write("{}. {} con {} triunfos\n".format(i, elemento[1] , elemento[0]))
                i+=1
                if elemento[1] not in cantidad_jugadores:
                    cantidad_jugadores.append(elemento[1])
        año_variable += 1
    resultado.close()
    archivo.close()
    
    return(len(cantidad_jugadores))
print(construir_resumen("datos_atp.csv", 2003, 2004))
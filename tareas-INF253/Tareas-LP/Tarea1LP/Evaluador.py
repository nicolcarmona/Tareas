import re

#Expresiones regulares:
#Basicas:
Digito = "[0-9]"
LetrasMin = "[a-z]"
LetrasMay = "[A-Z]"
Letra = ("[a-zA-Z]")
Palabra = (f"{Letra}({Digito})*")

#Tipo de datos y operacional:
Operador = (r"(\+\+|\-\-|\*|/|%|\+|\-|==|=|\+=|\-=|\*=|/=|%=|&=|\|=|^=|>>=|<<=|!=|>=|<=|<|>|&&|\|\||!)")
Booleano = ("(true|false)")
CadenaTexto = (f'("{Palabra}")')
Caracter = (f"('{Letra}')")
Valor = (f"({Digito}+|{Booleano}|{CadenaTexto}|{Caracter})")
TipoDato = ("(int|bool|void|char|string|float)")

#Estilos:
snake_case = (f"(_?{LetrasMin}+(_{LetrasMin}+)+_?|_{LetrasMin}+|{LetrasMin}+_)")
camelCase = (f"({LetrasMin}+({LetrasMay}{LetrasMin}+)+)")
PascalCase = (f"({LetrasMay}{LetrasMin}+)+")
Desconocido = (f"({LetrasMin}+|{LetrasMay}+|_?{LetrasMay}+(_{LetrasMay}+)+|_?{LetrasMin}+({LetrasMay}|_)({LetrasMin}|{LetrasMay}|_)*|(_?{LetrasMay}{LetrasMin}+)+(_{LetrasMin}+)*|_?{Letra}+({Digito}|_{Letra}|{Letra})*{Digito}({Letra}|{Digito}|_)*)")
DesconocidoInvalido= (f"{Digito}+{Letra}+") #error de sintaxis que empiece con un numero
NombreValido = (f"({snake_case}|{camelCase}|{PascalCase}|{Desconocido})")



#Estructuras avanzadas:
Argumento = (rf"({TipoDato} {NombreValido} *(, *{TipoDato} {NombreValido})*)")
DeclaracionFuncion = (rf"({TipoDato} *{NombreValido} *\({Argumento}?\) *{{?)")
#Error de sintaxis donde no hay () ni espacios o funcion mal escrita
DeclaracionFuncionSinEspacioSinParentesis = (rf"({TipoDato}{NombreValido} *{Argumento} *{{)")
DeclaracionFuncionSinParentesis = (rf"({TipoDato} +{NombreValido} *{{)")
DeclaracionConArgumentoSinParentesis = (rf"({TipoDato} *{NombreValido} *{Argumento} *{{)")
DeclaracionFuncionSinEspacio = (rf"({TipoDato}{NombreValido} *\({Argumento}\) *{{)")


DeclaracionVariable = (rf"({TipoDato} *{NombreValido} *({Operador} *{Valor})? *;?)")
DeclaracionVariableSinCierre = (rf"({TipoDato} {NombreValido} *({Operador}? *{Valor})?)")
DeclaracionVariableSinEspacio = (rf"({TipoDato}{NombreValido} *({Operador}? *{Valor})?;)")
DeclaracionVariableSinEspacioNiCierre = (rf"({TipoDato}{NombreValido} *({Operador}? *{Valor})?)")


DeclaracionVariableSnake = (rf"{TipoDato} {snake_case} *({Operador}? *{Valor})?;?")
DeclaracionVariableCamel = (rf"{TipoDato} {camelCase} *{Operador}? *{Valor}?;?")
DeclaracionVariablePascal = (rf"{TipoDato} {PascalCase} *{Operador}? *{Valor}?;?")
DeclaracionVariableDesconocido = (rf"{TipoDato} {Desconocido} *{Operador}? *{Valor}?;?")
DeclaracionVariableDesconocidoInvalida = (rf"{TipoDato} {DesconocidoInvalido} *{Operador}? *{Valor}?;?")



Condicion = (rf"( *{NombreValido} *{Operador} *{Valor} *)")
EstructuraControl = (rf"((if|while) *\(?{Condicion}\)? *{{)")
EstructuraControlSinParentesis = (rf"((if|while) *{Condicion} *{{)")
EstructuraControlSinLlave = (rf"((if|while) *{Condicion} *)")

InicioBloque = ("{")
CierreBloque = ("}")
Retorno = (rf"return *{NombreValido}?;?")
RetornoInvalido = (rf"return *{NombreValido}?")
ComentarioUnicaLinea = (rf"(// *{Palabra})")
ComentarioMultiLinea = (rf"(/\* *{Palabra} * \*/)")

#-----------Codigo--------#
ArchivoTXT = open("programa.txt","r") #Leer el archivo txt

def CrearArchivosGuardarInfo(Archivo):
    '''
    ***
    Parametro 1 : file
    ...
    ***
    dist [Se retorna los diccionarios donde se almacena toda la informacion]
    ***
    Esta funcion se encarga de crear los archivos de texto y guardar la informacion que se imprimira por terminal retornando los diccionarios con la informarcion
    '''

    #Inicializadores:
    ContadorLlaves = 0
    EstiloActual = None
    snake_casetxt = None
    camelCasetxt= None
    PascalCasetxt = None
    DesconocidoTXT = None
    #inicializamos los diccionarios que nos servira para guardar la informacion y asi imprimir por terminal:
    DiccionarioConTodoDeSnake = {"HaySnake": False,"ContadorFunciones": 0, "MensajeFuncion": [], "CantidadVariables": 0, "CantidadEstiloDistinto": 0, "MensajeEstilo": [], "ErroresSintaxis": 0, "MensajesErrores": []}
    DiccionarioConTodoDecamel = {"HayCamel": False, "ContadorFunciones": 0, "MensajeFuncion": [], "CantidadVariables": 0, "CantidadEstiloDistinto": 0, "MensajeEstilo": [], "ErroresSintaxis": 0, "MensajesErrores": []}
    DiccionarioConTodoDePascal = {"HayPascal": False, "ContadorFunciones": 0, "MensajeFuncion": [], "CantidadVariables": 0, "CantidadEstiloDistinto": 0, "MensajeEstilo": [], "ErroresSintaxis": 0, "MensajesErrores": []}
    DiccionarioConTodoDeDesconocido = {"HayDesconocido": False, "ContadorFunciones": 0, "MensajeFuncion": [], "CantidadVariables": 0, "CantidadEstiloDistinto": 0, "MensajeEstilo": [], "ErroresSintaxis": 0, "MensajesErrores": []}
    
    #Las siguientes 4 lineas, sirven unicamente para detencion cuando el archivo esta en una unica linea, por ejemplo int CasasVecindario{int CasasTotales =500; bool ImpuestoPagado = false; if(ImpuestoPagado == false){...}}. Estas lineas lo que hara es separar el contenido:
    contenido = Archivo.read()
    contenido = contenido.replace(";", ";\n") #la estructura de replace es remplazar (los caracteres que queremos cambiar ";"), a que lo queremos cambiar (en este caso ";\n" [es decir punto coma con salto de linea])
    contenido = contenido.replace("{", "{\n") 
    contenido = contenido.replace("}", "}\n")
    Lineas = contenido.splitlines(keepends=True) #con esto, combierte lo anterior en una lista de listas (para poder recorrerla en el for) splitlineas es aquello que lo transfroma en lista (ya que busca todos los saltos de lineas y los va separando por linea) y luego keepends = true es para mantener los saltos de linea (es un parametro opcional pero como en LineaSinComentario [que se vera mas adelante] utilizo "$" que es el final de la linea, si no fuera true, el programa podria romperse porque no sabria cual es el final)

    #Se analiza cada linea del archivo
    for Linea in Lineas:
        LineaSinComentario = re.sub(r'//.*$', '', Linea).strip() #re.sub sirve para sustituir una variable en el orden: patron (//), remplazo (''), cadena (Linea) esto es para eliminar los comentarios de las lineas del archivo, además el patron aquí sería //.*$(donde ".*" es capaz de detectar cualquier caracter y "$"es hasta el final de la liena)
        LineaParaDeteccionLlaveFuncion = re.sub(r'^\}', '', LineaSinComentario).strip() #esto es por si una funcion EMPIEZA con }, 
        #buscamos las funciones (ademas de trabajar inmediatamente con los posibles errores de sintaxis)
        EncontrarFuncion = re.fullmatch(DeclaracionFuncion, LineaParaDeteccionLlaveFuncion)
        EncontrarFuncionInvalida1= re.fullmatch(DeclaracionFuncionSinEspacio , LineaParaDeteccionLlaveFuncion)
        EncontrarFuncionInvalida2= re.fullmatch(DeclaracionFuncionSinEspacioSinParentesis , LineaParaDeteccionLlaveFuncion)
        EncontrarFuncionInvalida3= re.fullmatch(DeclaracionFuncionSinParentesis , LineaParaDeteccionLlaveFuncion)
        EncontrarFuncionInvalida4 = re.fullmatch(DeclaracionConArgumentoSinParentesis, LineaParaDeteccionLlaveFuncion)
        EncontrarFuncionInvalida5= re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)

        if EncontrarFuncion or EncontrarFuncionInvalida1 or EncontrarFuncionInvalida2 or EncontrarFuncionInvalida3 or EncontrarFuncionInvalida4 or EncontrarFuncionInvalida5:
                #Primero revisa si la funcion anterior se cerro correctamente [esto para ver los errores de sintaxis con las llaves en funciones (es decir si esta cerrada la funcion anterior y asi)]
                if EstiloActual != None and ContadorLlaves != 0: #Si hay un estilo todavía activo y el conteo de llaves es mayor a 0 [hay una funcion abierta]
                    if EstiloActual == "snake":
                        if ContadorLlaves > 0:
                            DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                            DiccionarioConTodoDeSnake["MensajesErrores"].append(f"'Error en '{LineaFuncionSnakeActual}':Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")
                        elif ContadorLlaves < 0:
                            DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                            DiccionarioConTodoDeSnake["MensajesErrores"].append(f"'Error en '{LineaFuncionSnakeActual}':Sobran llaves de cierre.")
                    elif EstiloActual == "camel":
                        if ContadorLlaves > 0:
                            DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                            DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en '{LineaFuncionCamelActual}':Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")               
                        elif ContadorLlaves < 0:
                            DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                            DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en '{LineaFuncionCamelActual}':Sobran llaves de cierre.")               
                    elif EstiloActual == "Pascal":
                        if ContadorLlaves > 0:
                            DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                            DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en '{LineaFuncionPascalActual}':Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")
                        elif ContadorLlaves < 0:
                            DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                            DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en '{LineaFuncionPascalActual}':Sobran llaves de cierre.")
                    
                    elif EstiloActual == "Desconocido":
                        if ContadorLlaves > 0:
                            DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                            DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en '{LineaFuncionDesconocidoActual}': Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")
                        elif ContadorLlaves < 0:
                            DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                            DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en '{LineaFuncionDesconocidoActual}': Sobran llaves de cierre.")
                
                #buscamos cada estilo correspondiente
                ContadorLlaves = 0 #como vamos a buscar el nuevo estilo, se reinicia el contador :)
                BuscarSnake =re.fullmatch(rf"{TipoDato} *{snake_case} *\({Argumento}?\).*", LineaParaDeteccionLlaveFuncion) #Para lograr aplicar que todo el string sea igual al patron que se busca, primero ve si es un tipo de dato y luego lo siguiente del tipo de dato es que este escrito en el estilo que corresponde y ver si la funcion tiene o no argumento, ademass para que acepte cualquier cosa que este despues de eso esta el ".*" (cualquier caracter 0 o mas veces [esto es para los "{}"]) y el strip es para eliminar los saltos de linea
                BuscarCamel =re.fullmatch(rf"{TipoDato} *{camelCase} *\({Argumento}?\).*", LineaParaDeteccionLlaveFuncion)           
                BuscarPascal = re.fullmatch(rf"{TipoDato} *{PascalCase} *\({Argumento}?\).*", LineaParaDeteccionLlaveFuncion)
                BuscarDesconocido = re.fullmatch(rf"{TipoDato} *{Desconocido} *\({Argumento}?\).*", LineaParaDeteccionLlaveFuncion)
                
                BuscarSnakeSinParentesis = re.fullmatch(rf"{TipoDato} *{snake_case} *{Argumento}? *{{?", LineaParaDeteccionLlaveFuncion)
                BuscarCamelSinParentesis = re.fullmatch(rf"{TipoDato} *{camelCase} *{Argumento}? *{{?", LineaParaDeteccionLlaveFuncion)
                BuscarPascalSinParentesis = re.fullmatch(rf"{TipoDato} *{PascalCase} *{Argumento}? *{{?", LineaParaDeteccionLlaveFuncion)
                BuscarDesconocidoSinParentesis = re.fullmatch(rf"{TipoDato} *{Desconocido} *{Argumento}? *{{?", LineaParaDeteccionLlaveFuncion)
                
                #ahora buscamos y almacenamos los datos de cada estilo, ademas de agregar algunos errores
                if BuscarSnake or BuscarSnakeSinParentesis:
                    LineaFuncionSnakeActual = LineaSinComentario
                    DiccionarioConTodoDeSnake["MensajeFuncion"].append(f"({LineaFuncionSnakeActual.strip()})")
                    if snake_casetxt is None:
                        snake_casetxt = open("snake.txt", "w")
                        DiccionarioConTodoDeSnake["HaySnake"] = True
                    EstiloActual = "snake"
                    DiccionarioConTodoDeSnake["ContadorFunciones"] +=1
                    BuscarFuncionInvalidaSinEspacio = re.fullmatch(DeclaracionFuncionSinEspacio, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinEspacioNiParentesis = re.fullmatch(DeclaracionFuncionSinEspacioSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesis = re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYConArgumento = re.fullmatch(DeclaracionConArgumentoSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYSinArgumento= re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)

                    if BuscarFuncionInvalidaSinEspacio or BuscarFuncionInvalidaSinEspacioNiParentesis or BuscarFuncionInvalidaSinParentesis or BuscarSnakeSinParentesis or BuscarFuncionInvalidaSinParentesisYConArgumento or BuscarFuncionInvalidaSinParentesisYSinArgumento:
                        DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                        DiccionarioConTodoDeSnake["MensajesErrores"].append(f"Error en {LineaFuncionSnakeActual.strip()}: Funcion mal declarada: {LineaSinComentario}")

                elif BuscarCamel or BuscarCamelSinParentesis:
                    LineaFuncionCamelActual = LineaSinComentario
                    DiccionarioConTodoDecamel["MensajeFuncion"].append(f"({LineaFuncionCamelActual.strip()})")
                    if camelCasetxt is None:
                        camelCasetxt = open("camel.txt", "w")
                        DiccionarioConTodoDecamel["HayCamel"] = True
                    EstiloActual = "camel"
                    DiccionarioConTodoDecamel["ContadorFunciones"] +=1
                    BuscarFuncionInvalidaSinEspacio = re.fullmatch(DeclaracionFuncionSinEspacio, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinEspacioNiParentesis = re.fullmatch(DeclaracionFuncionSinEspacioSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesis = re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYConArgumento = re.fullmatch(DeclaracionConArgumentoSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYSinArgumento= re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)

                    if BuscarFuncionInvalidaSinEspacio or BuscarFuncionInvalidaSinEspacioNiParentesis or BuscarFuncionInvalidaSinParentesis or BuscarCamelSinParentesis or BuscarFuncionInvalidaSinParentesisYSinArgumento or BuscarFuncionInvalidaSinParentesisYConArgumento :
                        DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                        DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en {LineaFuncionCamelActual.strip()}: Funcion mal declarada: {LineaSinComentario}")

                elif BuscarPascal or BuscarPascalSinParentesis:
                    LineaFuncionPascalActual = LineaSinComentario
                    DiccionarioConTodoDePascal["MensajeFuncion"].append(f"({LineaFuncionPascalActual.strip()})")
                    if PascalCasetxt is None:
                        PascalCasetxt = open("pascal.txt", "w")
                        DiccionarioConTodoDePascal["HayPascal"] = True
                    EstiloActual = "Pascal"
                    DiccionarioConTodoDePascal["ContadorFunciones"] +=1
                    BuscarFuncionInvalidaSinEspacio = re.fullmatch(DeclaracionFuncionSinEspacio, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinEspacioNiParentesis = re.fullmatch(DeclaracionFuncionSinEspacioSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesis = re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYConArgumento = re.fullmatch(DeclaracionConArgumentoSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYSinArgumento= re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)

                    if BuscarFuncionInvalidaSinEspacio or BuscarFuncionInvalidaSinEspacioNiParentesis or BuscarFuncionInvalidaSinParentesis or BuscarPascalSinParentesis or BuscarFuncionInvalidaSinParentesisYSinArgumento or BuscarFuncionInvalidaSinParentesisYConArgumento:
                        DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                        DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en {LineaFuncionPascalActual.strip()}: Funcion mal declarada: {LineaSinComentario}")

                elif BuscarDesconocido or BuscarDesconocidoSinParentesis:
                    LineaFuncionDesconocidoActual = LineaSinComentario
                    DiccionarioConTodoDeDesconocido["MensajeFuncion"].append(f"({LineaFuncionDesconocidoActual.strip()})")
                    if DesconocidoTXT is None:
                        DesconocidoTXT = open("Desconocido.txt", "w")
                        DiccionarioConTodoDeDesconocido["HayDesconocido"] = True
                    EstiloActual = "Desconocido"
                    DiccionarioConTodoDeDesconocido["ContadorFunciones"] +=1
                    BuscarFuncionInvalidaSinEspacio = re.fullmatch(DeclaracionFuncionSinEspacio, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinEspacioNiParentesis = re.fullmatch(DeclaracionFuncionSinEspacioSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesis = re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYConArgumento = re.fullmatch(DeclaracionConArgumentoSinParentesis, LineaParaDeteccionLlaveFuncion)
                    BuscarFuncionInvalidaSinParentesisYSinArgumento= re.fullmatch(DeclaracionFuncionSinParentesis, LineaParaDeteccionLlaveFuncion)

                    if BuscarFuncionInvalidaSinEspacio or BuscarFuncionInvalidaSinEspacioNiParentesis or BuscarFuncionInvalidaSinParentesis or BuscarDesconocidoSinParentesis or BuscarFuncionInvalidaSinParentesisYSinArgumento or BuscarFuncionInvalidaSinParentesisYConArgumento:
                        DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                        DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en {LineaFuncionDesconocidoActual.strip()}: Funcion mal declarada: {LineaSinComentario}")    
            
        #aqui se crea los archivos txt de cada tipo, ademas de obtener mas datos para almacenarlos (errores, estilo, etc) en el diccionario para poder imprimirlo en la terminal :D
        if EstiloActual == "snake":
            snake_casetxt.write(Linea)
            BuscarVariable= re.fullmatch(DeclaracionVariable, LineaSinComentario)
            if BuscarVariable:
                DiccionarioConTodoDeSnake["CantidadVariables"] +=1
                BuscarVariableSnake = re.fullmatch(DeclaracionVariableSnake, LineaSinComentario)
                if not BuscarVariableSnake:
                    DiccionarioConTodoDeSnake["CantidadEstiloDistinto"] +=1
                    DiccionarioConTodoDeSnake["MensajeEstilo"].append(f"{LineaSinComentario}: No es snake_case")
            #errores:
                BuscarVariableInvalida = re.fullmatch(DeclaracionVariableSinCierre, LineaSinComentario)
                BuscarVariableInvalida2 = re.fullmatch(DeclaracionVariableSinEspacioNiCierre, LineaSinComentario)
                BuscarVariableInvalida3 = re.fullmatch(DeclaracionVariableSinEspacio, LineaSinComentario)
                if BuscarVariableInvalida or BuscarVariableInvalida2 or BuscarVariableInvalida3:
                    DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                    if BuscarVariableInvalida:
                        DiccionarioConTodoDeSnake["MensajesErrores"].append(f"Error en {LineaFuncionSnakeActual.strip()}: Falta ';' en la linea {LineaSinComentario}")
                    else:
                        DiccionarioConTodoDeSnake["MensajesErrores"].append(f"Error en {LineaFuncionSnakeActual.strip()}: Variable mal declarada en linea {LineaSinComentario}")
            BuscarReturnInvalido = re.fullmatch(RetornoInvalido, LineaSinComentario)
            if BuscarReturnInvalido:
                    DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                    DiccionarioConTodoDeSnake["MensajesErrores"].append(f"Error en {LineaFuncionSnakeActual.strip()}: Falta ';' en linea {LineaSinComentario}")
            
            BuscarEstructuraControlInvalida =re.fullmatch(EstructuraControlSinParentesis, LineaSinComentario)
            BuscarEstructuraControlInvalida2= re.fullmatch(EstructuraControlSinLlave, LineaSinComentario)
            if BuscarEstructuraControlInvalida or BuscarEstructuraControlInvalida2:
                DiccionarioConTodoDeSnake["ErroresSintaxis"] +=1
                DiccionarioConTodoDeSnake["MensajesErrores"].append(f"Error en {LineaFuncionSnakeActual.strip()}: Estructura de control mal declarada: {LineaSinComentario}")

        elif EstiloActual == "camel":
            camelCasetxt.write(Linea)
            BuscarVariable= re.fullmatch(DeclaracionVariable, LineaSinComentario)
            if BuscarVariable:
                DiccionarioConTodoDecamel["CantidadVariables"] +=1
                BuscarVariablecamel = re.fullmatch(DeclaracionVariableCamel, LineaSinComentario)
                if not BuscarVariablecamel:
                    DiccionarioConTodoDecamel["CantidadEstiloDistinto"] +=1
                    DiccionarioConTodoDecamel["MensajeEstilo"].append(f"{LineaSinComentario}: No es camelCase")
            #errores:
                BuscarVariableInvalida = re.fullmatch(DeclaracionVariableSinCierre, LineaSinComentario)
                BuscarVariableInvalida2 = re.fullmatch(DeclaracionVariableSinEspacioNiCierre, LineaSinComentario)
                BuscarVariableInvalida3 = re.fullmatch(DeclaracionVariableSinEspacio, LineaSinComentario)
                if BuscarVariableInvalida or BuscarVariableInvalida2 or BuscarVariableInvalida3:
                    DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                    if BuscarVariableInvalida:
                        DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en {LineaFuncionCamelActual.strip()}: Falta ';' en linea {LineaSinComentario}")
                    else:
                        DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en {LineaFuncionCamelActual.strip()}: Variable mal declarada: {LineaSinComentario}")
            BuscarReturnInvalido = re.fullmatch(RetornoInvalido, LineaSinComentario)
            if BuscarReturnInvalido:
                    DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                    DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en {LineaFuncionCamelActual.strip()}: Falta ';' en linea {LineaSinComentario}")
            
            BuscarEstructuraControlInvalida =re.fullmatch(EstructuraControlSinParentesis, LineaSinComentario)
            if BuscarEstructuraControlInvalida:
                DiccionarioConTodoDecamel["ErroresSintaxis"] +=1
                DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en {LineaFuncionCamelActual.strip()}: Estructura de control mal declarada: {LineaSinComentario}")
        
        elif EstiloActual == "Pascal":
            PascalCasetxt.write(Linea)
            BuscarVariable= re.fullmatch(DeclaracionVariable, LineaSinComentario)
            if BuscarVariable:
                DiccionarioConTodoDePascal["CantidadVariables"] +=1
                BuscarVariablesPascal = re.fullmatch(DeclaracionVariablePascal, LineaSinComentario)
                if not BuscarVariablesPascal:
                    DiccionarioConTodoDePascal["CantidadEstiloDistinto"] +=1
                    DiccionarioConTodoDePascal["MensajeEstilo"].append(f"{LineaSinComentario}: No es PascalCase")
            #errores:
                BuscarVariableInvalida = re.fullmatch(DeclaracionVariableSinCierre, LineaSinComentario)
                BuscarVariableInvalida2 = re.fullmatch(DeclaracionVariableSinEspacioNiCierre, LineaSinComentario)
                BuscarVariableInvalida3 = re.fullmatch(DeclaracionVariableSinEspacio, LineaSinComentario)
                if BuscarVariableInvalida or BuscarVariableInvalida2 or BuscarVariableInvalida3:
                    DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                    if BuscarVariableInvalida:
                        DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en {LineaFuncionPascalActual.strip()}: Falta ';' en linea {LineaSinComentario}")
                    else:
                        DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en {LineaFuncionPascalActual.strip()}: Variable mal declarada: {LineaSinComentario}")
            BuscarReturnInvalido = re.fullmatch(RetornoInvalido, LineaSinComentario)
            if BuscarReturnInvalido:
                    DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                    DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en {LineaFuncionPascalActual.strip()}: Falta ';' en linea {LineaSinComentario}")
            
            BuscarEstructuraControlInvalida =re.fullmatch(EstructuraControlSinParentesis, LineaSinComentario)
            if BuscarEstructuraControlInvalida:
                DiccionarioConTodoDePascal["ErroresSintaxis"] +=1
                DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en {LineaFuncionPascalActual.strip()}: Estructura de control mal declarada: {LineaSinComentario}")

        elif EstiloActual == "Desconocido":
            DesconocidoTXT.write(Linea)
            BuscarVariable= re.fullmatch(DeclaracionVariable, LineaSinComentario)
            if BuscarVariable:
                DiccionarioConTodoDeDesconocido["CantidadVariables"] +=1
                BuscarVariablesDesconocido = re.fullmatch(DeclaracionVariableDesconocido, LineaSinComentario)
                if not BuscarVariablesDesconocido:
                    DiccionarioConTodoDeDesconocido["CantidadEstiloDistinto"] +=1
                    DiccionarioConTodoDeDesconocido["MensajeEstilo"].append(f"{LineaSinComentario} no es Desconocido")
            #errores:
                BuscarVariableInvalida = re.fullmatch(DeclaracionVariableSinCierre, LineaSinComentario)
                BuscarVariableInvalida2 = re.fullmatch(DeclaracionVariableSinEspacioNiCierre, LineaSinComentario)
                BuscarVariableInvalida3 = re.fullmatch(DeclaracionVariableSinEspacio, LineaSinComentario)
                BuscarVariableInvalida4 = re.fullmatch(DeclaracionVariableDesconocidoInvalida, LineaSinComentario)
                if BuscarVariableInvalida or BuscarVariableInvalida2 or BuscarVariableInvalida3 or BuscarVariableInvalida4:
                    DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                    if BuscarVariableInvalida:
                        DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en {LineaFuncionDesconocidoActual.strip()}: Falta ';' en linea {LineaSinComentario}")
                    else:
                        DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en {LineaFuncionDesconocidoActual.strip()}: Variable mal declarada: {LineaSinComentario}")

            BuscarReturnInvalido = re.fullmatch(RetornoInvalido, LineaSinComentario)
            if BuscarReturnInvalido:
                    DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                    DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en {LineaFuncionDesconocidoActual.strip()}: Falta ';' en linea {LineaSinComentario}")
            
            BuscarEstructuraControlInvalida =re.fullmatch(EstructuraControlSinParentesis, LineaSinComentario)
            if BuscarEstructuraControlInvalida:
                DiccionarioConTodoDeDesconocido["ErroresSintaxis"] +=1
                DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en {LineaFuncionDesconocidoActual.strip()}: Estructura de control mal declarada: {LineaSinComentario}")                

        #Esta parte de codigo, permite saber cuando una funcion inicio y termino para poder poner los bloques de funciones en los txt correspondiente ademas de tener el conteo de llaves del programa (llaves y estructuras)
        if EstiloActual != None: 
            ContadorLlaves += len(re.findall(r'\{', LineaSinComentario)) #findall devuelve una lista, entonces con len, nos devolvera la cantida de elementos (en este caso corchetes) de la lista, ademas, re.findall funciona de la siguiente manera -> (patron["{" ó "}" depediendo el caso], cadena[LineaSinComentarior]
            ContadorLlaves -= len(re.findall(r'\}', LineaSinComentario))
            if ContadorLlaves == 0:
                EstiloActual = None
    #permite saber si la ultima funcion termino correctamente sus llaves
    if EstiloActual != None and ContadorLlaves != 0:
        if EstiloActual == "snake":
            if ContadorLlaves > 0:
                DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                DiccionarioConTodoDeSnake["MensajesErrores"].append(f"'Error en '{LineaFuncionSnakeActual}':Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")
            elif ContadorLlaves < 0:
                DiccionarioConTodoDeSnake["ErroresSintaxis"] += 1
                DiccionarioConTodoDeSnake["MensajesErrores"].append(f"'Error en '{LineaFuncionSnakeActual}':Sobran llaves de cierre.")
        
        elif EstiloActual == "camel":
            if ContadorLlaves > 0:
                DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en '{LineaFuncionCamelActual}':Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")               
            elif ContadorLlaves < 0:
                DiccionarioConTodoDecamel["ErroresSintaxis"] += 1
                DiccionarioConTodoDecamel["MensajesErrores"].append(f"Error en '{LineaFuncionCamelActual}':Sobran llaves de cierre.")               
                    
        elif EstiloActual == "Pascal":
            if ContadorLlaves > 0:
                DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en '{LineaFuncionPascalActual}':Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")
            elif ContadorLlaves < 0:
                DiccionarioConTodoDePascal["ErroresSintaxis"] += 1
                DiccionarioConTodoDePascal["MensajesErrores"].append(f"Error en '{LineaFuncionPascalActual}':Sobran llaves de cierre.")
        elif EstiloActual == "Desconocido":
            if ContadorLlaves > 0:
                DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en '{LineaFuncionDesconocidoActual}': Bloque sin cerrar. Faltan {ContadorLlaves} llaves de cierre.")
            elif ContadorLlaves < 0:
                DiccionarioConTodoDeDesconocido["ErroresSintaxis"] += 1
                DiccionarioConTodoDeDesconocido["MensajesErrores"].append(f"Error en '{LineaFuncionDesconocidoActual}': Sobran llaves de cierre.")
                
    #cerramos los archivos en caso de que se abrieron
    if PascalCasetxt != None:
        PascalCasetxt.close()
    if snake_casetxt != None:
        snake_casetxt.close()
    if camelCasetxt != None:
        camelCasetxt.close()
    if DesconocidoTXT != None:
        DesconocidoTXT.close()

    ArchivoTXT.close()
    return DiccionarioConTodoDeSnake, DiccionarioConTodoDecamel, DiccionarioConTodoDePascal, DiccionarioConTodoDeDesconocido
    
Snake, Camel, Pascal, Desconocido = CrearArchivosGuardarInfo(ArchivoTXT)          

def ImprimirTerminal(Snake, Camel, Pascal, Desconocido):
    '''
    ***
    Parametro 1 : dict
    Parametro 2 : dict
    Parametro 3 : dict
    Parametro 4 : dict
    ...
    ***
    None
    ***
    Esta funcion se encarga de imprimir por terminal la información solicitada
    '''
    print("=== REPORTE DE EVALUACIÓN DE PRACTICANTES ===")
    if Snake["HaySnake"]:
        print ("PRACTICANTE: Snake")
        print(f"- Funciones creadas: {Snake['ContadorFunciones']} {Snake['MensajeFuncion']}")
        print(f"- Variables declaradas: {Snake['CantidadVariables']}")
        print(f"- Diferencias de Estilo: {Snake['CantidadEstiloDistinto']} {Snake['MensajeEstilo']}")
        print(f"- Errores de Sintaxis: {Snake['ErroresSintaxis']}")
        for Mensaje in Snake['MensajesErrores']:
            print(f"  - {Mensaje}")
    if Camel["HayCamel"]:
        print ("PRACTICANTE: Camel")
        print(f"- Funciones creadas: {Camel['ContadorFunciones']} {Camel['MensajeFuncion']}")
        print(f"- Variables declaradas: {Camel['CantidadVariables']}")
        print(f"- Diferencias de Estilo: {Camel['CantidadEstiloDistinto']} {Camel['MensajeEstilo']}")
        print(f"- Errores de Sintaxis: {Camel['ErroresSintaxis']}")
        for Mensaje in Camel['MensajesErrores']:
            print(f"  - {Mensaje}")
    if Pascal["HayPascal"]:
        print ("PRACTICANTE: Pascal")
        print(f"- Funciones creadas: {Pascal['ContadorFunciones']} {Pascal['MensajeFuncion']}")
        print(f"- Variables declaradas: {Pascal['CantidadVariables']}")
        print(f"- Diferencias de Estilo: {Pascal['CantidadEstiloDistinto']} {Pascal['MensajeEstilo']}")
        print(f"- Errores de Sintaxis: {Pascal['ErroresSintaxis']}")
        for Mensaje in Pascal['MensajesErrores']:
            print(f"  - {Mensaje}")
    if Desconocido["HayDesconocido"]:
        print ("PRACTICANTE: Desconocido")
        print(f"- Funciones creadas: {Desconocido['ContadorFunciones']} {Desconocido['MensajeFuncion']}")
        print(f"- Variables declaradas: {Desconocido['CantidadVariables']}")
        print(f"- Diferencias de Estilo: {Desconocido['CantidadEstiloDistinto']} {Desconocido['MensajeEstilo']}")
        print(f"- Errores de Sintaxis: {Desconocido['ErroresSintaxis']}")
        for Mensaje in Desconocido['MensajesErrores']:
            print(f"  - {Mensaje}")
    
ImprimirTerminal(Snake, Camel, Pascal, Desconocido) 
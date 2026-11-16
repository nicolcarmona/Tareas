nombre_per = input("Nombre: ")
nombre_pet= input("Nombre de su mascota: ")

#variables.
abecedario= "qwertyuiopasdfghjklñzxcvbnmáéíóú"
numeros= "0123456789"
fin = False
caracteres = ''' ¡!¿?@#$%&_-+*=|}{[].,;:<>/\'" ''' + '''~''' + ''' ^ '''

#inicio código.
while fin == False:
    #reinicio de variables:
    minus = False
    mayus = False
    num = False
    carac = False
    no_valido = False
    patron = ""
    repetido = False
    mascota = False
    persona = False
    
    contraseña = input("Contraseña propuesta (FIN para terminar): ")

    for c in contraseña:

        if c in abecedario.lower():
            minus = True
                  
        if c in abecedario.upper():
            mayus = True

        if c in numeros:
            num = True
        
        if c in caracteres:
            carac = True
    
        if c not in (caracteres + abecedario.lower() + abecedario.upper() + numeros):
            no_valido = True
        
        if c in patron:
            patron += c

        else:
            patron = c

        if patron == c * 5:
            repetido = True
            real = patron

        if nombre_pet.lower() in contraseña.lower():
            mascota = True

        if nombre_per.lower() in contraseña.lower():
            persona = True

#comprobar errores:

    if contraseña == "FIN":
        fin = True
        
    elif " " in contraseña:
     	print ("La contraseña no debe tener espacios.")
    
    elif len(contraseña) < 10:
        print ("Contraseña muy corta, debe tener al menos 10 caracteres.")

    elif minus == False :
        print ("Debe incluir letras minúsculas")

    elif mayus == False:
        print ("Debe incluir letras mayúsculas")

    elif num == False:
        print ("Debe incluir dígitos numéricos.")

    elif no_valido == True:
        print ("La contraseña contiene caracteres inválidos.")        
    
    elif carac == False:
        print ("Debe incluir caracteres especiales válidos.")
    
    elif repetido == True:
        print ("Contraseña no debe contener patrones:", real)
    
    elif mascota == True:
        print ("Contraseña no debe incluir el nombre de su mascota.")

    elif persona == True:
        print ("Contraseña no debe incluir su nombre.")

    else:
        print ("Contraseña válida!")
print ("Bievenido a la Pizzeria Pythonia di Napoli")
tarjeta = input("Tienes tarjeta de comelón frecuente (si/no)? ")
tipo_pizza = input("De qué quieres tu pizza? ")
base_pizza = 3000

if tipo_pizza == "pimiento" or tipo_pizza == "albahaca" or tipo_pizza == "tofu" or tipo_pizza == "nueces" or tipo_pizza == "brócoli" or tipo_pizza == "pepperoni" or tipo_pizza == "jamón" or tipo_pizza == "salmón":
    print ("Puedes pedir doble ", tipo_pizza)
    doble = input ("Quieres (si/no)? ")
    bebida = input ("Deseas llevar combo con bebida? (si/no): ")
    print  ("Puedes agregar un complemento:")
    print  ("1. Empanadas de queso")
    print  ("2. Alitas de pollo")
    print ("3. Papas fritas")
    print ("0. Nada")
    complemento = int(input("Opción: "))

    if complemento == 1:
        tipo_complemento = "empanadas de queso"
    elif complemento == 2:
        tipo_complemento = "alitas de pollo"
    else:
        tipo_complemento = "papas fritas"


    if tipo_pizza == "pimiento" or tipo_pizza == "albahaca":
        ingrediente = "vegetariana"
        base_pizza = base_pizza + 500
        costo_doble = 500

    elif tipo_pizza == "tofu" or tipo_pizza == "nueces" or tipo_pizza == "brócoli":
        ingrediente = "vegana"
        base_pizza = base_pizza + 700
        costo_doble = 700
    else:
        ingrediente = "no vegetariana"
        base_pizza = base_pizza + 1000
        costo_doble = 1000

    if bebida == "si":
        costo_bebida = 1000
    else:
         costo_bebida = 0

    if complemento > 0:
         costo_complemento = 500
    else:
         costo_complemento = 0
    
    if doble == "si" and tarjeta == "si":
        base_pizza = (base_pizza + costo_doble) * 0.9

    elif doble == "no" and tarjeta == "si":
         base_pizza = (base_pizza * 0.9)
    
    elif doble == "si" and tarjeta == "no":
         base_pizza = base_pizza + costo_doble
    else:
        base_pizza = base_pizza

    costo_final = base_pizza + costo_complemento + costo_bebida


    if (doble == "si" and bebida == "si" and complemento > 0):     
            print ("Disfruta tu pizza", ingrediente, "con mozzarela, tomate y doble ", tipo_pizza, "con complemento de", tipo_complemento,"!")
            print ("No olvides la bebida de tu combo.")
            print ("el total de tu compra es: $" , costo_final)     

    elif (doble == "si" and bebida == "si"):
            print ("Disfruta tu pizza", ingrediente, "con mozzarela, tomate y doble ", tipo_pizza)
            print ("No olvides la bebida de tu combo.")
            print ("el total de tu compra es: $" , costo_final)     

    elif (doble == "no" and bebida == "si"):
            print ("Disfruta tu pizza", ingrediente, "con mozzarela, tomate y", tipo_pizza)
            print ("No olvides la bebida de tu combo.")
            print ("el total de tu compra es: $" , costo_final)     

    elif (doble == "no" and bebida == "no" and complemento > 0 ):
            print ("Disfruta tu pizza", ingrediente, "con mozzarela, tomate y", tipo_pizza, "con complemento de", tipo_complemento,"!")
            print ("el total de tu compra es: $" , costo_final)     

    else: 
             print ("Disfruta tu pizza", ingrediente, "con mozzarela, tomate y", tipo_pizza)
             print ("el total de tu compra es: $" , costo_final)     

else:
    print ("No contamos con", tipo_pizza, "en nuestra pizzería.")
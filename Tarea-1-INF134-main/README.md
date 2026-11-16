# Tarea-1-INF134
Matilde Martínez
Nicol Carmona
----------------------------------------------------------------------------------------------------------------------------------------------
Nota: En la operacion 3 el usuario debe entregar un valor entre [0,1] para la transparecia de la imagen y en la 4 un valor entre [0,255] para el limite entre blanco y negro.  

Respuestas preguntas teóricas:
1. ¿Por qué si los pixeles de la imagen son números enteros ∈ [0,255], utilizamos el tipo de dato unsigned char?

R: Se utiliza el entero sin signo "unsigned char" debido a que es capaz de almacenar números enteros positivos de rango 0 hasta 255, siendo de un máximo de 1 byte (8 bits), lo que permite optimizar el uso de memoria sin desperdiciar de esta. Además los pixeles de las imagenes, en la escala rgb se tiene 3 canales, (r, g y b) y cada uno requiere de 8 bits (1 byte) para su procesamiento como las imágenes a color (RGB) necesitan 24 bits, o sea 8 bits por canal (color), y esto representa 256 niveles de tonalidades (espacios desde el 0 al 255), se necesita una función que determine un "espacio" para que se puedan procesar estas tonalidades. Esta función la cumple el "unsigned char", ya que el "char" por si solo considera desde -127 lo cual nos dejaria con espacios sin utilizar debido a que estos serían negativos.

2. ¿Cuales serían las diferencias entre usar unsigned int versus unsigned char? Responder cuantitativamente para una imagen RGB de dimensiones (N,N,3)
   
R: No existe una diferencia real entre caracteres y enteros pero el tipo char es un caso particular de un entero de 1 byte que se utiliza principalmente para representar y manipular datos textuales, mientras que el entero int, es de 4 bytes y se emplea para cálculos numéricos y operaciones basadas en números enteros. Entonces la gran diferencia va en el espacio utilizado, como se menciona anteriormente, una imagen RGB necesita de 24 bits en total, esto quiere decir 8 bits por canal, esto se lo entrega la función "unsigned char", mientras que al utilizar "unsigned int",  se le estaría asignando un total de 32 bits a cada canal, por lo cual desperdiciariamos 24 bits por canal. Es por esto que se hace mas eficiente el uso de char en cuanto a la memoria.
Para el caso de una imagen de dimensiones (N,N,3), tenemos que el espacio que ocupa esta imagen sería de (N* N * 3 * 8)=24N^2 [bits], este sería el espacio utilizado en el caso de utilizar la función "unsigned char", meintras que en el caso de "unsigned int" el espacio utilizado, sería de (N * N * 3 * 32) [bits]= 96 N^2 [bits] lo que reafirma lo anterior de que es más conveniente el uso de unsigned char en relación al uso de la memoria.

3. Usando este esquema de almacenamiento unidimensional: ¿Cuál sería el índice del primer pixel del canal azul?

R: El índice del primer pixel del canal azul sería 2 debido a que en una imagen de orden secuencial RGB, sería R,G,B,R,G,B... parte desde desde 0, por lo tanto para rojo sería 0, verde, sería 1 y azúl, sería 2.

4. ¿Cómo podemos convertir una imagen RGB a escala de grises?

R: Se utilizará la función rgb_to_gray. Los valores se convertirán de RGB a escala de grises mediante la fórmula 0.299 ∙ Rojo + 0.587 ∙ Verde + 0.114 ∙ Azul, lo que tomará un pixel que es por ejemplo (100, 83, 57) y reemplazará estos valores en la fórmula, arrojandonos en este caso el valor apróximado de 85 (85,119), lo que reemplazará cada uno de los valores de los pixeles por 85 (85,85,85) esto transformará ese pixel a una tonalidad de gris

6. ¿Cuáles el error, y como podría resolverse a nivel de código?

R: Demostrado a través de código. La diferencia es que en el error, no se revisa cada uno de los canales del pixel como R, G, B, si no que se revisan todos juntos inmediatamente como RGB, RGB... Esto se resuelve dentro del mismo if y else, agregandole img->data[pixel + c] en cada caso y de esta manera nos aseguramos que revise cada canal.


Bibliografía
Koren, N. (19 de octubre de 2004), "Making fine prints in your digital darkroom
Getting started",[Sitio Web] Recuperado de
https://www.normankoren.com/makingfineprints.html"

Feofiloff, P. (2 de enero 2019), "The types int and char", São Paulo, Brasil. [Entrada de blog] Recuperado de https://www.ime.usp.br/~pf/algorithms/chapters/int-and-char

Josue, M (27 de abril de 2021) "Entendiendo el concepto de canales en una imagen" Medium, [Entrada de blog] Recuperado de https://medium.com/featurepreneur/understanding-the-concept-of-channels-in-an-image-6d59d4dafaa9  

Zukhriddin. (26 de enero de 2023) "RGB vs BGR | Relaciones entre profundidad de color, píxeles y bytes" Medium, [Entrada de blog] Recuperado de https://zrruziev.medium.com/rgb-vs-bgr-relationships-between-color-depth-pixel-and-bytes-7821fa9c6320

Microsoft Learn. (23 de enero, 2024). Introducción a los formatos de píxel nativos. [Articulo] . Recuperado de https://learn.microsoft.com/es-es/windows/win32/wic/-wic-codec-native-pixel-formats
 
PTC, (s.f) "Ejemplo: escala de grises y color en imágenes" [Entrada de blog] Recuperado de https://support.ptc.com/help/mathcad/r8.0/es/index.html#page/PTC_Mathcad_Help/example_grayscale_and_color_in_images.html



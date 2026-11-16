#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

// Importacion de librerias. Los archivos correspondientes deben estar en el mismo directorio que el .cpp.
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <string> 
#include <fstream>

using namespace std;

// Struct que almacena la data de una imagen
struct Imagen{
    unsigned char* data;
    int width, height, channels;
};

// Abrir imagen desde memoria local
Imagen* load(const char* filename) {
    Imagen* img = new Imagen();
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img;
}

// Guardar imagen en memoria local
void save(Imagen* img, const char* filename) {
    stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
    cout << "Imagen guardada:  " << filename << "\n";
}

// Pregunta 5: A) Objetivo, poner la imagen en modo espejo.
void operacion_1(Imagen*img) { 
    int canales_rgb = img->channels;
    int ancho = img->width;
    int altura = img-> height;

    for (int y=0; y < altura; y++) {
        for (int x=0; x < (ancho)/2; x++){
            for (int c=0 ; c < canales_rgb ; c++){           
                int pixel = (y * ancho + x)* canales_rgb + c ;
                int reflejo = (y * ancho * canales_rgb) + (ancho * canales_rgb) - ((x + 1 ) * canales_rgb) + c ; 
                //variable temporal para ir intercambiando los pixeles de posición en sentido espejo
                unsigned char temporal = img->data[pixel];
                img->data[pixel] = img->data[reflejo];
                img->data[reflejo] = temporal;
            }
        }
    }
}
// Pregunta 5: B) Objetivo, poner la imagen en modo rotar.
void operacion_2(Imagen*img) {
    int canales_rgb = img->channels;
    int ancho = img->width;
    int altura = img-> height;
    //puntero para ir guardando la imagen a medida que se va rotando
    unsigned char* img_rotada = new unsigned char[ancho * altura * canales_rgb];

    for (int y=0; y < altura ; y++){
        for (int x=0; x < ancho; x++){
            for (int c= 0;c < canales_rgb; c++){
                int pixel = (y * ancho + x)* canales_rgb + c ;
                int rotar = (x * altura + (altura - y - 1) )* canales_rgb + c;
                img_rotada[rotar] = img->data[pixel];
                    
            }   
        } 
    }
    for (int i = 0; i < (ancho * altura * canales_rgb); i++){
        img->data[i] =img_rotada[i];
    }
    
    delete [] img_rotada;
    int temporal = img->width;
    img->width = img->height;
    img->height = temporal;

    
}
//Pregunta 5: objetivo, bajar la opacidad de la imagen a un valor entregado
void operacion_3(Imagen*img , float grado){
    int canales_rgb = img->channels;
    int ancho = img->width;
    int altura = img-> height;
    for (int y=0; y < altura ; y++){
        for (int x=0; x < ancho; x++){
            for (int c= 0;c < canales_rgb; c++){
                int pixel = (y * ancho + x)* canales_rgb + c ;
                //toma el valor ingresado para grado y lo va aplicando por pixel
                img->data[pixel] = img->data[pixel] * grado + ((1.0 - grado) * 255);
            }
        }
    }
}
    
//Pregunta 5: objetivo pasar la imagen a blanco y negro
void operacion_4(Imagen*img , int color){
    int canales_rgb = img->channels;
    int ancho = img->width;
    int altura = img-> height;
    for (int y=0; y < altura ; y++){
        for (int x=0; x < ancho; x++){
            for (int c= 0;c <=2; c++){
                int pixel = (y * ancho + x) * canales_rgb ;
                //if para los pixeles que su tonalidad sea menor a la tonalidad ingresada en color
                int suma_colores= (0.299 * img->data[pixel] + 0.587 * img->data[pixel+1] + 0.114 * img->data[pixel+2]);
                    if (suma_colores < color ){
                        //los tranforma a negro
                        img->data[pixel+c] = 0;
                    }
                //else para los pixeles que su tonalidad sea mayor a la tonalidad ingresada en color
                    else {
                        //los transforma a blanco
                        img->data[pixel+c] = 255 ;
                    }
            }
        }
    }
}

//Pregunta 6: operacion 4 pero con el error de no procesar cada canal por pixel 
void operacion_6_error(Imagen*img , int color){
    int canales_rgb = img->channels;
    int ancho = img->width;
    int altura = img-> height;
    for (int y=0; y < altura ; y++){
        for (int x=0; x < ancho; x++){
            for (int c= 0; c <= 2; c++){
                int pixel = (y * ancho + x) * canales_rgb + c ;
                if (img->data[pixel] < color){
                    img->data[pixel] = 0;
                }
                else { 
                    img->data[pixel] = 255 ;

                }
                    
            }
        }
    }
}

//Pregunta 7, 7.1 y 7.2; crear ascii art con un arreglo entregado, entregarlo en la terminal y en un archivo txt
void to_ascii(Imagen*img , char* array, int largo) {
    int canales_rgb = img->channels;
    int ancho = img->width;
    int altura = img->height;
    int altura_pequeña = altura / 2;
    int ancho_pequeño = ancho / 2;
    string ascii_art  = "";

    for (int y = 0; y < altura_pequeña; y++) {
        for (int x = 0; x < ancho_pequeño; x++) {
            int pixel = ((y *2) * ancho + (x*2)) * canales_rgb; //Se multiplica por 2 y se divide la altura y el ancho para que se vea más pequeño en la consola.
            unsigned char rojo = img->data[pixel];
            unsigned char verde = img->data[pixel + 1];
            unsigned char azul = img->data[pixel + 2];
            unsigned char agris = (0.299 * rojo + 0.587 * verde + 0.114 * azul); //aplicar la formula NTSC para asignarle un gris a la imagen
            int sustituir_caracter = (agris * largo) / 256; //va evaluando que caracter tomar del array dependiendo del intervalo
            ascii_art += array[min(sustituir_caracter, largo-1)]; // 7.1, agregamos el caracter nuevo al string creado anteriormente
        }
        ascii_art += '\n';  // salto de linea despues de cada fila
    }
    cout << ascii_art;

    ofstream save_ascii("ascii_art.txt"); //Pregunta 7.2 stream del archivo
    if (save_ascii.is_open()) { //abre el archivo
        save_ascii << ascii_art; //guarda el ascii :D
        save_ascii.close(); 
    }    
    else {
        cout<<"Error al abrir el archivo \n ";
    }
}

int main() {
    int color;
    float grado;
    //arreglo por el cual se van a sustituir los pixeles de la imagen 
    char array[] = {'w', 'p','m', 'a', 'Z', 'N','J', 'A', '#', '?', '|'};  
    int largo = sizeof(array) / sizeof(array[0]);

    //Cargamos la imagen y aplicamos la operacion 1
    Imagen* img1 = load("minion.png");
    operacion_1(img1);
    save(img1,"operacion1.png");
    delete[] img1;

    //Cargamos la imagen y aplicamos la operacion 2
    Imagen* img2 = load("minion.png");
    operacion_2(img2);
    save(img2,"operacion2.png");
    delete[] img2;

    Imagen* img3 = load("minion.png");

    //Datos para operacion 3
    cout << "Ingrese grado de atenuación: ";
    cin >> grado;
    if (grado < 0) {
        grado = 0;
    }
    if (grado > 1) {
        grado = 1;
    } 
    operacion_3(img3, grado);  
    save(img3,"operacion3.png");
    delete[] img3;
//cargamos la imagen y aplicamos la operacion 4 y 6 (o sea la 4 con error)
    Imagen* img4 = load("minion.png");
    Imagen* img_error = load("minion.png");
    //Datos para operacion 4 y 6.
    cout << "Ingrese limite entre blanco y negro: ";
    cin >> color;
    operacion_4(img4, color);  
    save(img4, "operacion4.png");

    operacion_6_error(img_error, color);
    save(img_error, "operacion6.png");
    delete[] img4;
    delete[] img_error;
//cargamos la imagen y la pasamos a ascii art
    Imagen* img = load("minion.png");
    to_ascii(img, array, largo); 
    delete[] img;

    return 0;
}
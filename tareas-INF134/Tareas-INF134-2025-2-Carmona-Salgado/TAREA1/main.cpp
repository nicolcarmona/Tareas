#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

int CantidadDeRegistros; //Variable global para utilizarla en las otras funciones con la cantidad de registros que se obtendra en la funcion 1

struct Dato{

    unsigned int Id;      
    char Nombre [50];    
    char Fecha_Nacimiento [11]; 
    int Notas [3];      
    char Curso [7];      
    unsigned short VTR;   
};

void Menú(){

    std::cout << 
        "1) Agregar un alumno.\n" <<
        "2) Obtener promedio de un estudiante.\n" << 
        "3) Obtener promedio por evaluación de una asignatura.\n" <<
        "4) Obtener los cursos en los que está inscrito un estudiante.\n" <<
        "5) Obtener los reprobados de un curso con cierto VTR.\n" <<
        "6) Generar informe por cursos.\n" <<
        "0) Salir del programa.\n" <<
        "Ingrese su opción: ";  
}

void Mostrar_Datos_Alumno(Dato* datos, unsigned int tamanio){

    /*
    *    Descripción: 
    *            Imprimir por consola los datos cargados en el parametro 'datos', mostrando los primeros 5 o menos en caso de que 'tamanio' sea menor a 5.
    *
    *    Parametros:
    *            Dato* datos: Puntero/arreglo que contiene los datos a querer mostrar.
    *            int tamanio: Tamaño del arreglo.
    *    
    *    Retorno:
    *            Función tipo void, no retorna nada.
    *    
    */
    
    std::cout << std::left 
                    << std::setw(8) << "ID" 
                    << std::setw(50) << "NOMBRE" 
                    << std::setw(12) << "CURSO" 
                    << std::setw(17) << "FECHA NAC." 
                    << std::setw(5) << "VTR" 
                    << std::setw(8)  << "NOTA 1"
                    << std::setw(8)  << "NOTA 2"
                    << std::setw(8)  << "NOTA 3"
                    << std::endl;

    for (unsigned int i = 0; i < 5 && i < tamanio; i++) {

        std::cout << std::left
                    << std::setw(8) << datos[i].Id 
                    << std::setw(50) << datos[i].Nombre 
                    << std::setw(12) << datos[i].Curso 
                    << std::setw(17) << datos[i].Fecha_Nacimiento 
                    << std::setw(5) << datos[i].VTR 
                    << std::setw(8)  << datos[i].Notas[0]  
                    << std::setw(8)  << datos[i].Notas[1]  
                    << std::setw(8)  << datos[i].Notas[2]  
                    << std::endl;
    }
}

//Funcion 1: 
/*Descripcion: 
    *            Su objetivo es leer un archivo binario y devolver un puntero con la informacion del archivO
    *
    *    Parametros:
    *            Un string constante con referencia al archivo.dat que se leera
    *    
    *    Retorno:
    *            Funcion tipo Dato, retorna un puntero con la informacion correspondiente.
*/

Dato* Leer_archivo(const string &nombre_archivo){
    ifstream Archivo;
    Archivo.open(nombre_archivo, ios::in | ios::binary); //Abrir el archivo
    if (!Archivo.is_open()) cout << "No se pudo abrir el archivo" << endl; //Comprobar si se pudo abrir el archivo

    Archivo.read((char*) &CantidadDeRegistros, sizeof(unsigned int)); //Leer la cantidad de registros del archivo
    Dato* Datos = new Dato[CantidadDeRegistros]; //Para retornar en memoria dinamica los datos
    Archivo.read((char*)Datos, CantidadDeRegistros*sizeof(Dato)); //Ya que son N registros, esto servira para leer la siguiente cantidad de lineas

    Archivo.close();
    return Datos;
}

//Función 2:
/*Descripcion: 
    *            El objetivo de la funcion es eliminar aquellos que estan duplicados en el archivo original
    *
    *    Parametros:
    *            Un puntero referenciado del archivo y un entero referenciado con la cantidad de datos (cantidad de registros)
    *    
    *    Retorno:
    *            Funcion tipo void, no retorna nada
*/
void Eliminar_Duplicados(Dato*& datos , int& cantidad_datos){
    Dato* DatosNoDuplicados = new Dato[cantidad_datos]; //Arreglo para guardar los nuevos datos
    int CantidadNueva = 1;
    DatosNoDuplicados[0] = datos[0]; //Se guarda la primera posicion para evitar problemas al usar "i-1"
    for (int i = 1; i < cantidad_datos ; i++){
        bool CursoIgual = true;
        for(int j = 0; j < 7 ; j++){
            if (datos[i].Curso[j] != datos[i-1].Curso[j]){
                CursoIgual = false;
            }
        }
        if(datos[i].Id != datos[i-1].Id || CursoIgual == false ){ //Si la id es distinta a la anterior se guardara o si el curso es distinto al anterior se guardara tambien
            DatosNoDuplicados[CantidadNueva] = datos[i]; //Se usa una nueva cantidad para evitar problemas de posiciones y de memoria
            CantidadNueva++;
        }
    }    
    Dato* DatosNuevos = new Dato[CantidadNueva]; //Arreglo con la memoria adecuada
    for (int i = 0; i < CantidadNueva; i++) DatosNuevos[i] = DatosNoDuplicados[i]; //Insertar en el arreglo con la memoria adecuada los datos no duplicados
    delete[] datos; //Liberar la memoria dinamica que no se utliza
    delete[] DatosNoDuplicados;
    datos = DatosNuevos; //Actualizar los datos
    cantidad_datos = CantidadNueva; 
}

//Funcion 3: 
/*Descripcion: 
    *           Al recibir información a partir de lo escrito en la consola la función integrará datos de un nuevo alumno al arreglo previamente redimensionado.
    *
    *    Parametros:
    *            Un puntero referenciado a la variable original y una variable de tipo Dato para asignarle los valores correspondientes.
    *    
    *    Retorno:
    *            Funcion tipo void, no retorna nada.
*/
void Agregar_Alumno ( Dato *& datos , Dato Alumno_nuevo ) {
// Pedimos datos y asignamos el correspondiente al struct.
    cout << "\nIngrese los datos del estudiante :\n"; 
    cout << "ID (Número mayor a 1500) :\n"; cin >> Alumno_nuevo.Id;
    
    while (Alumno_nuevo.Id < 1500){
        cout << "Valor ingresado invalido. Por favor volver a intentar :"; cin >> Alumno_nuevo.Id;
    }
    cin.ignore();

    cout << "Primer nombre y primer apellido :\n"; cin.getline(Alumno_nuevo.Nombre, 50);

    cout << "Fecha de nacimiento (formato YYYY/MM/DD) :\n"; cin.getline(Alumno_nuevo.Fecha_Nacimiento, 11);

    cout << "Notas de las 3 evaluaciones (separadas por espacio) :\n"; 
    cin >> Alumno_nuevo.Notas[0];
    cin >> Alumno_nuevo.Notas[1];
    cin >> Alumno_nuevo.Notas[2];

    cin.ignore();

    cout << "Sigla del curso (ejemplo : INF134) :\n"; cin.getline(Alumno_nuevo.Curso, 7);

    cout << "VTR (1-3) :\n"; cin >> Alumno_nuevo.VTR;

    bool idRegistrado = false; //Para asegurarnos de no generar duplicados.

    for (int i=0; i<CantidadDeRegistros; i++){
        bool coincide_asignatura = true; 
        for(int j = 0; j < 7; j++){
            if (datos[i].Curso[j] != Alumno_nuevo.Curso[j]) {
                coincide_asignatura = false;
            }
           if (coincide_asignatura && datos[i].Id == Alumno_nuevo.Id) {
            idRegistrado = true; //Hay dato identico.
            }
        }
    }    
    

    if (idRegistrado==false){
        int NuevaCantidad = CantidadDeRegistros + 1;
        Dato* DatosConNuevoAlumno = new Dato[NuevaCantidad]; //Arreglo dinamico para reasignar el tamaño con el nuevo alumno.

        for (int i = 0; i<CantidadDeRegistros ;i++){
            DatosConNuevoAlumno[i] = datos[i];
        }
        DatosConNuevoAlumno[CantidadDeRegistros]=Alumno_nuevo;
        delete[] datos;
        datos = DatosConNuevoAlumno;
        CantidadDeRegistros = NuevaCantidad; //Nuevo tamaño.

        cout << "\n¡Alumno agregado exitosamente!" << endl;
    
    } 
    else {
        cout << "Alumno ya ingresado en ese curso , no es posible ingresarlo otra vez ." << endl;
    }
}

//Funcion 4:
/*Descripcion: 
    *            El objetivo de la funcion es encontrar el Estudiante pedido para leer sus datos y retornar el promedio obtenido en el ramo.
    *
    *    Parametros:
    *            Un puntero de tipo Dato al archivo, un unsigned int del id a buscar y un puntero tipo char de la asignatura
    *    
    *    Retorno:
    *            Funcion tipo int, retorna una variable tipo int según el caso. (Promedio en la asignatura)
*/
int Calcular_Promedio_Estudiante ( Dato * datos , unsigned int id_alumno , char* asignatura_a_buscar ) {
    bool ExisteCurso = false;
    bool IdEnCurso =  false;
    int promedio;
    for (int i = 0; i < CantidadDeRegistros; i++){
        int contador = 0;
        for(int j = 0; j < 7; j++){
            if (datos[i].Curso[j] == asignatura_a_buscar[j]){
                contador++;
                if(contador == 7){ // Caso de que todos los caracteres concuerdan.
                    ExisteCurso = true;
                    if (datos[i].Id == id_alumno) {
                        IdEnCurso = true; // Efectivamente existe el alumno en el curso.
                        float suma_notas = (datos[i].Notas[0] + datos[i].Notas[1] + datos[i].Notas[2])/3.0;
                        suma_notas = round(suma_notas);
                        promedio = suma_notas;
                        return promedio;

                    }
                }
            }
        }
    }
    if (ExisteCurso == false){
        return -1; // Caso curso no encontrado.
    }
    if (IdEnCurso == false){
        return -2; // Caso persona no registrada en el curso.
    }
    return -3;
};

//Funcion 5:
/*Descripcion: 
    *            El objetivo de la funcion es calcular por el promedio de cada nota en una asignatura en especifico que se pedira por consola
    *
    *    Parametros:
    *            Un puntero del archivo a ejecutar y un puntero char que contiene la asignatura pedida por consola
    *    
    *    Retorno:
    *            Funcion tipo entero puntero, retorna un arreglo de tamaño tres que contiene cada nota
*/

int* Calcular_Promedio_Asignatura(Dato* datos , char* asignatura_a_buscar){
    int CantidadNotas = 0;
    int* SumaNotas = new int[3];

    for(int i  = 0; i < 3; i++){
        SumaNotas[i] = 0; //Inicializacion del arreglo dinamico
    }
    for (int i = 0; i < CantidadDeRegistros; i++){
        bool CursoIgual = true;
        for (int j = 0; j < 7; j++){
            if (datos[i].Curso[j] != asignatura_a_buscar[j]){
                CursoIgual = false;
                break;
            }
        }
        if (CursoIgual){ //En caso de que la asignatura sea la pedida, se sumaran las notas correspondientes
            SumaNotas[0] += datos[i].Notas[0];
            SumaNotas[1] += datos[i].Notas[1];
            SumaNotas[2] += datos[i].Notas[2];
            CantidadNotas++;
        }   
    }
    for (int i = 0; i < 3; i++){SumaNotas[i] = round((float)SumaNotas[i] / CantidadNotas);} //mediante un cast se divide suma de notas y la cantidad de notas (que es como la cantidad de estudiantes en la asignatura) y se redondea
    return SumaNotas;

}


//Funcion 6:
/*Importante: En la tarea esta funcion aparece como "void Listar_Cursos_Estudiante(Dato* datos , char* asignatura_a_buscar){};"
pero, en la consola no se pide la asignatura si no el id, asi que se cambio considerando eso.
*/

/*Descripcion: 
    *            El objetivo de la funcion mostrar por consola los cursos en los que esta el estudiante pedido por la terminal
    *
    *    Parametros:
    *            Un puntero del archivo a ejecutar y un unsigned int con la Id la cual se le buscara los cursos
    *    
    *    Retorno:
    *            Funcion tipo void, no retorna nada
*/
void Listar_Cursos_Estudiante(Dato* datos , unsigned int id){ 
    Dato* CursosEstudianteAUX = new Dato[CantidadDeRegistros];
    int CantidadDeCursos = 0;
    for (int i = 0; i < CantidadDeRegistros; i++){
        if (datos[i].Id == id){
            CursosEstudianteAUX[CantidadDeCursos] = datos[i];
            CantidadDeCursos++;
        }
    }
    if (CantidadDeCursos == 0) cout << "No existe registro para el estudiante con Id " << id << "." << endl;
    else cout << "Las asignaturas inscritas por el estudiante son: ";

    Dato* CursoEstudiante = new Dato[CantidadDeCursos];
    for ( int i = 0; i < CantidadDeCursos; i++) CursoEstudiante[i] = CursosEstudianteAUX[i]; //Redirrecionar la memoria
    for ( int i = 0; i < CantidadDeCursos; i++) cout << CursoEstudiante[i].Curso << " "; //Se imprime por consola los cursos
    delete[] CursosEstudianteAUX; //liberacion de memoria
    delete[] CursoEstudiante;
}


//Funcion 7:
/*Descripcion: 
    *            El objetivo de la funcion es listar la cantidad de reprobados en una asignatura y vtr pedido en la consola
    *
    *    Parametros:
    *            Un puntero de tipo Dato al archivo, un unsigned short de los vtr y un puntero tipo char de la asignatura
    *    
    *    Retorno:
    *            Funcion tipo puntero int, retorna un arreglo de enteros
*/
int* Listar_Reprobados_VTR(Dato* datos , unsigned short VTR_a_buscar , char*asignatura_a_buscar){  
    int* DatosVTR = new int[CantidadDeRegistros]; //Aquí DatosVTR es un arreglo temporal como se hizo en la funciones anteriores
    int PersonasReprobar = 0; //Para guardar la cantidad de personas que reprobaron
    for(int i = 0; i < CantidadDeRegistros; i++){
        int ContadorVTR = 0;
        for (int j = 0; j < 7 ; j++){
            if (asignatura_a_buscar[j] == datos[i].Curso[j]){
                ContadorVTR++;
                if (ContadorVTR == 7  && VTR_a_buscar == datos[i].VTR){
                    int PromedioEstudiante = Calcular_Promedio_Estudiante(datos, datos[i].Id, asignatura_a_buscar); //Se llama a la funcion de calcular el promedio del estudiante para obtener los promedios de cada estudiante y comprobar si reprobaron o aprobaron
                    if (PromedioEstudiante < 55){
                        DatosVTR[PersonasReprobar] = datos[i].Id; //Se guarda los datos de aquel que reprobo el ramo
                        PersonasReprobar++;
                    }
                }
            }
        }
    }
    int* ListaPersonasReprobadas = new int[PersonasReprobar+1]; //Se una +1, ya que en el espacio 0, estara la cantidad de gente que reprobo
    for(int i = 0; i < PersonasReprobar; i++){
        ListaPersonasReprobadas[i+1] = DatosVTR[i];
    }

    delete[] DatosVTR; // liberacion de memoria y remplazo del primer espacio
    ListaPersonasReprobadas[0] = PersonasReprobar;
    return ListaPersonasReprobadas;
}

//Función 8
/*Descripcion: 
    *            El objetivo de la funcion es generar un informe de cada asignatura dentro del archivo con caracteristicas especificas
    *
    *    Parametros:
    *            Un puntero de tipo Dato al archivo
    *    
    *    Retorno:
    *            Funcion tipo void, no retorna nada
*/
void Generar_Informe (Dato* datos) {
    char DatosCurso[CantidadDeRegistros][7]; //Un doble arreglo como matriz para guardar la cantidad de asignaturas que pueden existir en el archivo y la cantidad de caracteres del curso
    int CantidadCursos = 0;
    for (int i = 0; i < CantidadDeRegistros; i++){
        bool CursoIgual= true;
        for (int j = 0; j < 7; j++){
            if (!CantidadCursos || DatosCurso[CantidadCursos-1][j] != datos[i].Curso[j]){ //En caso de que no existan cantidad de cursos (posicion 0) o el curso no este en el arreglo la flag sera falsa
                CursoIgual = false;
            }
        }
        if(!CursoIgual){ //Aqui si el curso no es igual, se guardara el curso
            for (int j = 0; j < 7; j++){
                DatosCurso[CantidadCursos][j] = datos[i].Curso[j];
            }
            CantidadCursos++;
        }
    }
    for (int i = 0; i < CantidadCursos; i++){
        int EstudiantesEnAsignatura = 0;
        int Reprobados = 0;
        int Aprobados = 0;
        int Maximo[3] = {-1, -1, -1}; //inicializados en -1
        int Minimo[3] = {101, 101, 101}; //Inicializados en 101
        ofstream Archivo; //abrir el archivo como salida
        string Nombre = string(DatosCurso[i]) + ".txt";
        Archivo.open(Nombre, ios::out);
        for (int j = 0 ; j < CantidadDeRegistros; j++){
            if(string(DatosCurso[i]) == string(datos[j].Curso)){ //Comparacion de cursos mediante cast de string, antes de esto mismo se hizo con un for para ver caracter por caracter 
                EstudiantesEnAsignatura++;
                Archivo << datos[j].Id << " " << datos[j].Nombre << " " << datos[j].Curso << " " << datos[j].Fecha_Nacimiento << " " << datos[j].VTR << " ";
                for (int k = 0; k < 3; k++){
                    Archivo << datos[j].Notas[k] << " ";
                    if (Maximo[k] < datos[j].Notas[k]) Maximo[k] = datos[j].Notas[k]; //calculo de maximo
                    if (Minimo[k] > datos[j].Notas[k]) Minimo[k] = datos[j].Notas[k]; //Calculo de minimo
                }
                Archivo << Calcular_Promedio_Estudiante(datos, datos[j].Id, datos[j].Curso) << endl;
                if (Calcular_Promedio_Estudiante(datos, datos[j].Id, datos[j].Curso) < 55) Reprobados++;
                else Aprobados++;
            }
        }
        int* Lista = Listar_Reprobados_VTR(datos, 3, DatosCurso[i]);
        Archivo << EstudiantesEnAsignatura << endl;
        Archivo << "Aprobados: " << Aprobados << endl;
        Archivo << "Reprobados: " << Reprobados << endl;
        Archivo << "Porcentaje de aprobación: " << round((float)(Aprobados) / EstudiantesEnAsignatura * 100) << " %" << endl;
        Archivo << "Maximos: " << Maximo[0] << " " << Maximo[1] << " " << Maximo[2] << endl;
        Archivo << "Minimos: " << Minimo[0] << " " << Minimo[1] << " " << Minimo[2] << endl;
        Archivo << "VTR3 reprobados: " << Lista[0] << endl;
        Archivo << "Ids: "; 
        for (int j = 0; j < Lista[0]; j++) Archivo << Lista[j+1] << " ";
        Archivo.close();
        delete[] Lista;
    }
}

int main(){
    Dato* Archivo = Leer_archivo("datos.dat");
    Eliminar_Duplicados(Archivo, CantidadDeRegistros);
    //Mostrar_Datos_Alumno(Archivo, CantidadDeRegistros);
    bool flag = true;
    while(flag){
        Menú();
        string Opcion, VTR, Id;
        char Curso[7];
        cin >> Opcion;
        
        if (Opcion == "1"){
            Dato nuevoAlumno;
            Agregar_Alumno(Archivo, nuevoAlumno);
            cout << endl;
        }
        else if (Opcion == "2"){
            string id;
            char asignatura[7];
            
            cout << "\nIngrese los datos del estudiante: \n";
            cout << "ID: "; cin >> id;
            cout << "Curso: "; 
            cin >> asignatura;
            int promedioEstudiante = Calcular_Promedio_Estudiante(Archivo,(unsigned int)stoi(id),asignatura);
            if (promedioEstudiante != -1 && promedioEstudiante != -2){
                cout << "El promedio del estudiante es: " <<promedioEstudiante<<endl;
            }
            else if (promedioEstudiante == -1)
            {
                cout << "No existe el curso " << asignatura << endl;
            }
            else if (promedioEstudiante == -2) {
                cout << "No existe un estudiante de ID " << id << " en el curso " << asignatura << endl;
            }
            cout << endl;
        }
        else if (Opcion == "3"){
            cout << "Ingrese la asignatura a calcular el promedio por evaluación: ";
            cin >> Curso;
            int* PromedioAsignatura = Calcular_Promedio_Asignatura(Archivo, Curso);
            cout << "El promedio por evaluaciÓon de la asignatura " << Curso << " es " << PromedioAsignatura[0] << " " << PromedioAsignatura[1] << " " << PromedioAsignatura[2] <<endl;
            cout << endl;
            delete[] PromedioAsignatura;
        }
        else if (Opcion == "4"){
            cout << "Ingrese el Id del alumno a buscar: ";
            cin >> Id;
            Listar_Cursos_Estudiante(Archivo, (unsigned int)stoi(Id)); //Se utiliza un primero un stoi para pasar de string a entero y luego un cast para cambiarlo a usigned int            
            cout << endl;
        }
        else if (Opcion == "5"){
            cout << "Ingrese el VTR: ";
            cin >> VTR;
            cout << "Ingrese el curso: ";
            cin >> Curso;
            int* Lista = Listar_Reprobados_VTR(Archivo, (unsigned short)stoi(VTR), Curso);
            cout << "Cantidad de reprobados: " << Lista[0] << endl;
            cout << "Ids: ";
            for (int i = 0; i < Lista[0]; i++) cout << Lista[i+1] << " ";
            cout << endl;
            delete[] Lista;
        
        }
        else if (Opcion == "6"){
            Generar_Informe(Archivo);
            cout << endl;
        }
        else if (Opcion == "0"){
           
            break;
        }
        else {
            cout << "Opción no valida, intente nuevamente" << endl;
        }
    }
    delete[] Archivo;
    return 0;

}

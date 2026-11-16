#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//ELEMENTOS FUNDAMENTALES [Nodo, Cola, Arcos, Grafo].

//NODO:

//Se crea una estructura para representar un nodo en la cola de BFS
struct NodoCola{
    int Vertice, Distancia;
    NodoCola* Siguiente;
    //Creamos el constructor del conjunto de nodos, siendo v, el vertice y d, la distancia del viaje.
    NodoCola(int v, int d){
         Vertice=  v;
         Distancia= d;
         Siguiente= nullptr;
        }
};

//COLA:

//Se utiliza la misma estructura de la clase cola que en la tarea anterior para la implementacion del algoritmo BFS
class Cola{
private:
    NodoCola* Head;
    NodoCola* Tail;
    
public:
    //Se crea el constructor donde inicializa todo como vacio
    Cola(){Head = nullptr, Tail = nullptr;}
    //Y su destructor donde mientras la cola no este vacia, se va a eliminar el nodo
    ~Cola(){
        while (!EstaVacia()) {
            QuitarNodo();
        }
    }

    //Se crea la funcion AgregarNodo para poder ir agregando los nodos (con su vertice y distancia) a la cola
    void AgregarNodo(int Vertice, int Distancia){
        NodoCola* Temporal = new NodoCola(Vertice, Distancia);
        if (Tail == nullptr) {
            Head = Tail = Temporal;
        } 
        else {
            Tail->Siguiente = Temporal;
            Tail = Temporal;
        }
    }
    //Se crea la funcion QuitarNodo, para poder eliminar los elementos de la cola.
    NodoCola QuitarNodo(){
        //Si la cabeza esta vacia, devolverá los valores de -1 y -1 lo que hará detenerse.
        if (!Head) {
            return NodoCola(-1, -1);
        }
        //Se obtiene el valor del primer elemento de la cola y se guarda en una variable auxiliar para luego poder acceder al siguiente elemento de la cola.
        NodoCola Resultado = *Head;
        NodoCola* aux = Head;
        Head = Head->Siguiente;
        if (!Head){
            Tail = nullptr;
        }
        delete aux;
        return Resultado;
    }
    //Retorna true en caso de que la cabeza de la cola no este vacio por lo tanto la cola no este vacia.
    bool EstaVacia(){
        if (!Head) return true;
        else return false;
    }
};

//CAMINOS:

//Se crea una estructura para representar los caminos en la lista enlazada con su constructor inicial.
struct Arco{
    int Destino;
    Arco* Siguiente;
    Arco(int d){
        Destino= d;
        Siguiente= nullptr;
    }
};

//GRAFO [Mediante lista enlazada y BFS]:

//Se crea la clase Grafo para poder utilizar una lista enlazada para representar el grafo con sus nodos y arcos.
class Grafo{
private:
    Arco** ListaEnlazada;
    int NumeroDeNodos;
    
public:
    //Constructur del grafo
    Grafo(int n){
        NumeroDeNodos = n;
        //La lista (Y todos los elementos del grafo, como distancias, etc) tendran punteros con size de n+1 para evitar problemas con la posicion 0.
        ListaEnlazada = new Arco*[NumeroDeNodos +1];
        for (int i = 0; i <= NumeroDeNodos; i++) {
            //Se inicializara vacio.
            ListaEnlazada[i] = nullptr;
        }
    }
    //Desctructor del grafo donde se eliminará cada elemento del grafo y su memoria.
    ~Grafo(){
        for (int i = 0; i <= NumeroDeNodos; i++){
            Arco* Actual = ListaEnlazada[i];
            while (Actual != nullptr) {
                Arco* Temporal = Actual;
                Actual = Actual->Siguiente;
                delete Temporal;
            }
        }
        delete[] ListaEnlazada;
    }
    //Se agregan los caminos al grafo
    void AgregarArco(int Origen, int Destino){
        Arco* aux = new Arco(Destino);
        aux->Siguiente = ListaEnlazada[Origen];
        ListaEnlazada[Origen] = aux;
    }

    //Se crea el algoritmo de la busqueda a lo ancho que retornara un array de distancias desde el nodo origen
    int* BFS(int Origen){
        //Se crea el array de distancias y el array de visitados [De nuevo con +1 para evitar problemas con la posicion 0]
        int* Distancias = new int[NumeroDeNodos + 1];
        bool* Visitado = new bool[NumeroDeNodos + 1];
        //Donde inicializa todo como -1 y 0 para evitar elementos basura
        for (int i = 0; i <= NumeroDeNodos; i++) {
            Distancias[i] = -1;
            Visitado[i] = false;
        }
        //Llamado de la clase cola para poder utilizarla y se crea el recorrido.
        Cola Cola;
        Cola.AgregarNodo(Origen, 0);
        Distancias[Origen] = 0;
        Visitado[Origen] = true;

        //Mientras la cola no este vacia, se hara el recorrido.
        while (!Cola.EstaVacia()){
            //Toma como nodo actual el primer elemento de la cola para procesarlo.
            NodoCola Actual = Cola.QuitarNodo();
            int NodoActual = Actual.Vertice;
            int DistanciaActual = Actual.Distancia;
            Arco* Vecino = ListaEnlazada[NodoActual];
            //Mientras el vecino sea distinto a nulo
            while (Vecino != nullptr){
                //Si a donde debe ir no esta visitado, este luego se marcara como visitado y la distancia actual se le sumara 1 
                if (!Visitado[Vecino->Destino]){
                    Visitado[Vecino->Destino] = true;
                    Distancias[Vecino->Destino] = DistanciaActual + 1;
                    //Y este se agregara a la cola
                    Cola.AgregarNodo(Vecino->Destino, Distancias[Vecino->Destino]);
                }
                Vecino = Vecino->Siguiente;
            }
        }
        //Liberar memoria y devolver la distancia.
        delete[] Visitado;
        return Distancias;
    }
    
    //Se reconstruira el camino del BFS con los caminos más corto, de la misma manera como en el anterior caso solo que ahora se agregara el arreglo raiz donde guardará el nodo inicial y se agrega la longitud como parametro para guardar el destino.
    int* ReconstruirCamino(int Origen, int Destino, int& Longitud){
        //Se vuelve a crear arreglos de las distancias, del nodo padre (raiz) y aquellos que fueron visitados.
        int* Distancias = new int[NumeroDeNodos + 1];
        int* Raiz = new int[NumeroDeNodos + 1];
        bool* Visitado = new bool[NumeroDeNodos + 1];
        //inicializando todo como -1 y falso. 
        for (int i = 0; i <= NumeroDeNodos; i++){
            Distancias[i] = -1;
            Raiz[i] = -1;
            Visitado[i] = false;
        }
        
        Cola cola;
        cola.AgregarNodo(Origen, 0);
        Distancias[Origen] = 0;
        Visitado[Origen] = true;
        
        while (!cola.EstaVacia()){
            NodoCola Actual = cola.QuitarNodo();
            int NodoActual = Actual.Vertice;
            int DistanciaActual = Actual.Distancia;
            if (NodoActual == Destino)break;
            Arco* Vecino = ListaEnlazada[NodoActual];
            //Aquí es donde se guarda el nuevo camino donde la raiz será el nodo actual.
            while (Vecino != nullptr){
                if (!Visitado[Vecino->Destino]){
                    Visitado[Vecino->Destino] = true;
                    Distancias[Vecino->Destino] = DistanciaActual + 1;
                    Raiz[Vecino->Destino] = NodoActual;
                    cola.AgregarNodo(Vecino->Destino, DistanciaActual + 1);
                }
                Vecino = Vecino->Siguiente;
            }
        }
        //Liberacion de memoria y si no hay camino
        if (Distancias[Destino] == -1){
            Longitud = 0;
            delete[] Distancias;
            delete[] Raiz;
            delete[] Visitado;
            return nullptr;
        }
        //Aqui es donde la longitud sera la distancia del destino más corto y el camino sera el arreglo donde se guardara el largo de este.
        Longitud = Distancias[Destino] + 1;
        int* Camino = new int[Longitud];
        
        int Actual = Destino;
        for (int i = Longitud - 1; i >= 0; i--){
            Camino[i] = Actual;
            Actual = Raiz[Actual];
        }
        //Liberacion de memoria y retorno del camino.
        delete[] Distancias;
        delete[] Raiz;
        delete[] Visitado;
        return Camino;
    }
};

//SISTEMA UBER.

//Se crea la clase sistema uber para manejar la informacion y toda la funcion. 
class SistemaUber{
private:
    Grafo* GrafoActual;
    int* Conductores;
    int NumeroConductores;
    int NumeroNodos;
    
public:
    //Se crea el constructor donde se lee el mapa.
    SistemaUber(string NombreArchivo){
        CargarMapaUber(NombreArchivo);
    }
    //Se crea el destructor donde se libera la memoria.    
    ~SistemaUber(){
        delete GrafoActual;
        delete[] Conductores;
    }
    //se crea la funcion para leer el mapa.
    void CargarMapaUber(string NombreArchivo){
        ifstream Uber(NombreArchivo);
        if (!Uber.is_open()) {
            cerr << "No se pudo abrir el mapa!" << endl;
            return;
        }
        int NumerosArcos;
        Uber >> NumeroNodos >> NumerosArcos >> NumeroConductores;
        GrafoActual = new Grafo(NumeroNodos);
        Conductores = new int[NumeroConductores];
        //Se obtiene los datos del origen y el destino del data
        for (int i = 0; i < NumerosArcos; i++){
            int PosicionInicial, PosicionFinal;
            Uber >> PosicionInicial >> PosicionFinal;
            GrafoActual->AgregarArco(PosicionInicial, PosicionFinal);
        }
        //Para guardar en el arreglo cada conductor
        for (int i = 0; i < NumeroConductores; i++){
            Uber >> Conductores[i];
        }
        
        Uber.close();
    }
    //Se crea solicitar uber con el origen y el destino del data
    void SolicitarUber(int Origen, int Destino){
        // Encontrar el conductor más cercano
        int ConductorOptimo = -1;
        int DistanciaMinima = -1;
        
        for (int i = 0; i < NumeroConductores; i++){
            //Se crea el arreglo con las distancias del grafo actual del data y se aplicara el algoritmo de bfs con size de los conductores.
            int* Distancias = GrafoActual->BFS(Conductores[i]);
            if (Distancias[Origen] != -1) {
                //Se crean distintas condiciones para establecer la distancia minima como la distancia del origen y establecer cual conductor es mejor, mientras menor sea la distancias se eligirá en caso de empate es aquel que tenga menor 
                if (DistanciaMinima == -1 || Distancias[Origen] < DistanciaMinima || (Distancias[Origen] == DistanciaMinima && Conductores[i] < ConductorOptimo)){
                    DistanciaMinima = Distancias[Origen];
                    ConductorOptimo = Conductores[i];
                }
            }
            //Liberacion de memoria
            delete[] Distancias;
        }
        //Si no hay conductor optimo
        if (ConductorOptimo == -1){
            cout << "Ruta: {} - Costo: -1\n";
            return;
        }
        
        //Se construye la ruta de la persona al destino
        int LargoViaje;
        int* RutaViaje = GrafoActual->ReconstruirCamino(Origen, Destino, LargoViaje);
        //En el caso de que no haya ruta
        if (RutaViaje == nullptr){
            cout << "Ruta: {} - Costo: -1\n";
            return;
        }
        
        int DistanciaViaje = LargoViaje - 1;
        int Costo = 300 * DistanciaMinima + 500 * DistanciaViaje;
        
        //Se muestra la ruta
        cout << "Ruta: {";
        for (int i = 0; i < LargoViaje; i++){
            cout << RutaViaje[i];
            if (i < LargoViaje - 1) cout << ", ";
        }
        
        cout << "} - Costo: " << Costo << endl;
        
        //Se actualiza la posicion del conductor
        for (int i = 0; i < NumeroConductores; i++){
            if (Conductores[i] == ConductorOptimo){
                Conductores[i] = Destino;
                break;
            }
        }
        //Liberacion de memoria
        delete[] RutaViaje;
    }
   //Se crea la funcion para poder ejecutar el programa
    void Ejecutar(){
        int Origen, Destino;
        bool Flag = true;
        while (Flag){
            cout << "Ingrese viaje: ";
            cin >> Origen >> Destino;
            if (Origen == -1 && Destino == -1) {
                break;
            }
            SolicitarUber(Origen, Destino);
        }
    }
};

//Aqui es donde se llama todo para poder utilizar el sistema con el constructor del mapa y ya luego el mapa se podrá ejecutar.
int main() {
    SistemaUber Mapa("data2.txt");
    Mapa.Ejecutar();
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Vertice{
    int ID;
    Vertice* Siguiente;
};

struct NodoCola{
    int info;
    NodoCola* siguiente;
};

class Cola{
    private:
        NodoCola* inicio;
        NodoCola* final;
        int tamano;
    public:
        Cola(){
            inicio = nullptr;
            final = nullptr;
            tamano = 0;
        }
        ~Cola(){ //destructor.
            while(!colaVacia()){
                desencolar();
            }
        };

        /*       Descripcion: 
            *            Esta funcion simula la insercion en la cola un nodo        
            *
            *    Parametros:
            *            Un entero
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void encolar(int usuario){ //para la funcion calcular influencia
            NodoCola* visitado = new NodoCola();
            visitado->info = usuario;
            visitado->siguiente = nullptr;

            if(colaVacia()){
                inicio = final = visitado;
            }
            else {
                final->siguiente = visitado;
                final = visitado;
            }
            tamano++;
        }

        /*       Descripcion: 
            *            Esta funcion simula el eliminar en la cola un nodo        
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void desencolar(){
            if(colaVacia()){
                cout << "Cola vacía, no hay elementos para desencolar" << endl;
                return;
            }
            NodoCola* temp = inicio;
            inicio = inicio->siguiente;
            if (inicio == nullptr){
                final = nullptr;
            }
            delete temp;
            tamano--;
            return;
        }

        /*       Descripcion: 
            *            Esta funcion busca confirmar si la cola esta vacia o no    
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo bool, retorna verdadero o false
        */
        bool colaVacia(){
            return inicio == nullptr;
        }
        int primerValor(){
            if(inicio == nullptr) return -1;
            return inicio->info;
        }
};

class Grafo{
    private:
        Vertice** ListaDeAdyacencia;
        int CantidadDeUsuarios;
        int CantidadDeRelaciones;
    public:
        Grafo(){ //Constructor
            ListaDeAdyacencia = nullptr;
            CantidadDeUsuarios = 0;
            CantidadDeRelaciones = 0;
        }
        ~Grafo(){ //Destructor
            if (ListaDeAdyacencia != nullptr){
                for(int i = 0; i < CantidadDeUsuarios; i++){
                    Vertice* VerticeActual = ListaDeAdyacencia[i];
                    while(VerticeActual != nullptr){
                        Vertice* Temporal = VerticeActual->Siguiente;
                        delete VerticeActual;
                        VerticeActual = Temporal;
                    }
                }
                delete[] ListaDeAdyacencia;
            }
        }

        /*       Descripcion: 
            *            Esta funcion busca crear el grafo mediante el metodo de lista de adyacencia. El grafo se crea apartir de informacion entregada en una archivo tipo txt      
            *
            *    Parametros:
            *            Un string constante que sera el nombre del archivo
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void CrearGrafoConListaDeAdyacencia(const string &nombre_archivo){
            ifstream Archivo;
            Archivo.open(nombre_archivo, ios::in); //Abrir el archivo
            if (!Archivo.is_open()){
                cout << "No se pudo abrir el archivo" << endl; //Comprobar si se pudo abrir el archivo
                return;
            }
            Archivo >> CantidadDeUsuarios; 
            Archivo >> CantidadDeRelaciones;

            int IdActual;
            int IdSiguiente; 
            ListaDeAdyacencia = new Vertice*[CantidadDeUsuarios];
            for(int i = 0; i < CantidadDeUsuarios; i++){
                ListaDeAdyacencia[i] = nullptr;
            }
            for(int j = 0; j < CantidadDeRelaciones; j++){
                Vertice* VerticeActualA = new Vertice; //Se crea solo un espacio de memoria
                Archivo >> IdActual >> IdSiguiente;

                //Lo siguiente es la insercion a la lista de adyacencia, siguiendo la misma estructura de insercion en la cabeza en listas enlazadas implementado en la tarea anterior
                //insercion de 2da columna
                VerticeActualA->ID = IdSiguiente; //El nuevo elemento que queremos insertar
                VerticeActualA->Siguiente = ListaDeAdyacencia[IdActual]; //La cabeza actual pasara a ser el siguiente vertice
                ListaDeAdyacencia[IdActual] = VerticeActualA; // y ahora la cabeza actual pasa a ser la insertada
                //Insercion de 1ra columna, misma logica anterior, pero con los datos de la primera fila
                Vertice* VerticeActualB = new Vertice;
                VerticeActualB->ID =IdActual;
                VerticeActualB->Siguiente = ListaDeAdyacencia[IdSiguiente];
                ListaDeAdyacencia[IdSiguiente] = VerticeActualB;
            }
            Archivo.close();
        }

        /*       Descripcion: 
            *            El objetivo de esta funcion es imprimir el grafo en la terminar con forma de lista de adyacencia (es decir, columna de nodos y columna con conexiones)      
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void ImprimirGrafo(){
            for (int i = 0; i < CantidadDeUsuarios; i++){
                cout << "Nodo " << i << ": ";
                Vertice* VerticeActual = ListaDeAdyacencia[i]; //Para iterar en la lista, si se hace con la propia lista, se destruira
                if (VerticeActual == nullptr) { //Sin conexiones
                    cout << "(sin vecinos)";
                }
                while(VerticeActual != nullptr){ //Mientras si tenga conexiones
                    cout << VerticeActual->ID << " ";
                    VerticeActual = VerticeActual->Siguiente; //Pasa a la siguiente
                }
                cout << endl;
            }
        }

        /*      Descripcion: 
            *            Esta funcion entrega el texto con las opciones   
            *
            *    Parametros:
            *            No
            *    
            *    Retorno:
            *            Funcion tipo string, retorna la opcion elegida
        */
        string TextoInicial(){
            string Opcion;
            cout << "Bienvenido a Sansabook, ¿Qué función desea probar?" << endl;
            cout << "Opciones disponibles: " << endl;
            cout << "1. Sugerir amigos\n" << "2. Usuario más popular\n" << "3. Contar comunidades\n" << "4. Calcular influencia\n" << "5. Encontrar puentes\n" << "0. Salir\n"; 
            cout << "Inserte opción: ";
            cin >> Opcion;
            return Opcion;
        }

        /*       Descripcion: 
            *            El objetivo de esta funcion es entregar los amigos sugeridos de un nodo en especifico, entrega aquellos que se encuentran en el grado 2 de distancia en el grafo       
            *
            *    Parametros:
            *            Un entero
            *    
            *    Retorno:
            *            Funcion tipo vertice, retorna los vertices (id) sugeridos para el nodo que uno buscó
        */
        Vertice* sugerir_amigos(int id_usuario){
            bool* EstadosDeVisitados = new bool[CantidadDeUsuarios]; //Aqui vamos a guardar a los amigos de grado 1
            bool* EstadoSugeridos = new bool[CantidadDeUsuarios];
            Vertice* Sugerencias = nullptr; //Y aqui a los amigos de los amigos, o sea grado 2 (esta es la lista que vamos a retornar)
            for(int i = 0; i < CantidadDeUsuarios; i++){ //inicializador
                EstadosDeVisitados[i] = false;
                EstadoSugeridos[i] = false;
            }
            //Queremos implementar la logica de "visitar" a los nodos marcandolos, entonces si esta visitado, los evitamos poner mas veces en la lista que hay que retornar
            EstadosDeVisitados[id_usuario] = true; //Para evitar sugerirse asi mismo, misma logica con los que ya son sus amigos
            
            Vertice* AmigoActual = ListaDeAdyacencia[id_usuario]; //Iterar en los amiguis del numero
            while(AmigoActual != nullptr){
                EstadosDeVisitados[AmigoActual->ID] = true; //1 ~ true para los visitados, 0 ~ false para los no visitados
                AmigoActual = AmigoActual->Siguiente; //pasamos al siguiente
            }
            AmigoActual = ListaDeAdyacencia[id_usuario]; //hay que iterar de nuevo pero esta vez los amigos del amigo, por lo que volvemos al inicio
            while (AmigoActual != nullptr){
                Vertice* AmigoDelAmigoActual = ListaDeAdyacencia[AmigoActual->ID];
                while (AmigoDelAmigoActual != nullptr){
                    if(EstadosDeVisitados[AmigoDelAmigoActual->ID] == false && EstadoSugeridos[AmigoDelAmigoActual->ID] == false){ //Todos menos el usuario, los amigos directos y duplicados
                        Vertice* AmigoSugerido = new Vertice; //Creamos un espacio de memoria para insertarlo a la lista de amigos sugerido, lo siguiente sera la misma logica de insertar en la cabeza
                        AmigoSugerido->ID = AmigoDelAmigoActual->ID;
                        AmigoSugerido->Siguiente = Sugerencias;
                        Sugerencias = AmigoSugerido;
                        EstadoSugeridos[AmigoSugerido->ID] = true; //para que no salgan de nuevo
                    }
                    AmigoDelAmigoActual = AmigoDelAmigoActual->Siguiente;
                }
                AmigoActual = AmigoActual->Siguiente;
            }
            delete[] EstadosDeVisitados;
            delete[] EstadoSugeridos;
            return Sugerencias;
        }

        /*       Descripcion: 
            *            Esta funcion entrega el usuario más popular (es decir aquel que tiene mas conexiones)      
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo entero, retorna el ID del usuario más popular.
        */
        int usuario_mas_popular(){
            int Maximo = -1;
            int IdPopular = -1;
            for (int i = 0; i < CantidadDeUsuarios; i++){
                int ContadorAmigos = 0;
                Vertice* Actual = ListaDeAdyacencia[i]; //Iterar en las conexiones de los vertices
                while (Actual != nullptr){ //el que tenga mas amigos se usara para compararlo luego
                    ContadorAmigos++;
                    Actual = Actual->Siguiente;
                }
                if (ContadorAmigos > Maximo){ //aqui se hace el cambio, si el que tiene mas amiguitos debe ser el nuevo maximo
                    Maximo = ContadorAmigos;
                    IdPopular = i;
                }
            }
            return IdPopular;
        }

        /*       Descripcion: 
            *            Esta funcion cuenta las comunidades que hay el grafo (Aquellos usuarios conectados son una comunidades y un nodo solo tambien)       
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo int, retorna la cantidad de comunidades que hay en el grafo
        */
        int contar_comunidades(){
            if (CantidadDeUsuarios == 0) return -1;

            bool* visitados = new bool[CantidadDeUsuarios];
            for (int i = 0; i < CantidadDeUsuarios; i++ ){
                visitados[i] = false;
            }
            int comunidades = 0;

            for (int i = 0; i < CantidadDeUsuarios; i++){
                if(!visitados[i]){
                    comunidades++;
                    visitados[i] = true;
                    Cola cola;
                    cola.encolar(i);
                    
                    while(!cola.colaVacia()){
                        int actual = cola.primerValor();
                        cola.desencolar();

                        Vertice* temp = ListaDeAdyacencia[actual];
                        while(temp != nullptr){
                            if (!visitados[temp->ID]){
                                visitados[temp->ID] = true;
                                cola.encolar(temp->ID);
                            }
                            temp = temp->Siguiente;
                        }
                    }
                }
            }
            delete[] visitados;
            return comunidades;
        }

        /*       Descripcion: 
            *            El objetivo de esta funcion, es calcular la influencia de un nodo en especifico, es decir la cantidad de amigos totales + la cantidad de los amigos sugeridos
            *
            *    Parametros:
            *            Un entero
            *    
            *    Retorno:
            *            Funcion tipo int, retorna la cantidad total de influencia
        */
        int calcular_influencia(int id_usuario){
            if(id_usuario < 0 || id_usuario >= CantidadDeUsuarios) return -1;
            int influencia = 0;

            bool *alcanzados = new bool[CantidadDeUsuarios];
            for (int i = 0; i < CantidadDeUsuarios; i++ ){
                alcanzados[i] = false;
            }
            alcanzados[id_usuario] = true;

            Vertice* amigoDirecto = ListaDeAdyacencia[id_usuario];
            while (amigoDirecto != nullptr){
                alcanzados[amigoDirecto->ID] = true;

                Vertice* amistaddAmistad = ListaDeAdyacencia[amigoDirecto->ID];
                while (amistaddAmistad != nullptr){
                    alcanzados[amistaddAmistad->ID] = true;

                    amistaddAmistad = amistaddAmistad->Siguiente;
                }
                amigoDirecto = amigoDirecto->Siguiente;
            }

            for (int i = 0; i < CantidadDeUsuarios; i++){
                if(alcanzados[i] && i != id_usuario){
                    influencia++;
                }
            }
            delete[] alcanzados;
            return influencia;
        }

       /*       Descripcion: 
            *            Esta funcion busca encontrar los puentes que hay en el grafo, es decir que si se elimina un nodo en especifico y hace que se incremente la cantidad de comunidades, es un puente     
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo vertice, retorna los usuarios que son puentes
        */
        Vertice* encontrar_puentes() {
            if (CantidadDeUsuarios == 0) return nullptr;
            Vertice* Puentes = nullptr;
            Vertice* UltimoPuente = nullptr; 
            int ConexionesIniciales = contar_comunidades();

            for(int i = 0; i < CantidadDeUsuarios; i++){ //Primero ir eliminando cada nodo y para identificar que conexiones quedan
                bool* visitados = new bool[CantidadDeUsuarios];
                    for (int j = 0; j < CantidadDeUsuarios; j++){ //Inicializamos vacio
                        visitados[j] = false; 
                    }
                visitados[i] = true; //El nodo que estamos eliminando lo marcamos como verdadero para que en el bfs se lo salte
                int ConexionSinNodo = 0;
                
                for (int j = 0; j < CantidadDeUsuarios; j++){
                    if(!visitados[j]){
                        ConexionSinNodo++;
                        Cola cola;
                        cola.encolar(j); //Ingresamos a la cola el nodo 
                        visitados[j] = true; 
                        
                        while(!cola.colaVacia()){
                            int actual = cola.primerValor();
                            cola.desencolar();

                            Vertice* Vecino = ListaDeAdyacencia[actual];//visitamos los vecinos de nodo actual
                            while(Vecino != nullptr){
                                int IDVecino = Vecino->ID;
                                if (IDVecino != i && !visitados[IDVecino]){ //si no es el nodo actual y no esta visitado, lo visitamos y lo ingresamos a la cola
                                    visitados[IDVecino] = true;
                                    cola.encolar(IDVecino);
                                }
                                Vecino = Vecino->Siguiente;
                            }
                        }
                    }
                }
                
                delete[] visitados;
                if (ConexionSinNodo > ConexionesIniciales) { //si todavia quedan componentes tonce e puente
                    Vertice* PuenteNuevo = new Vertice();
                    PuenteNuevo->ID = i;
                    PuenteNuevo->Siguiente = nullptr;
                
                    if (Puentes == nullptr){//Agregar a la lista de puentes
                        Puentes = PuenteNuevo;
                        UltimoPuente = PuenteNuevo;
                    }
                    else {
                        UltimoPuente->Siguiente = PuenteNuevo;
                        UltimoPuente = PuenteNuevo;
                    }
                }
            }
            return Puentes;
        }

        /*       Descripcion: 
            *            Esta funcion es el menu que se ejecutara en la terminal       
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void MenuInteractivo(){
            string Opcion;
            int ID;
            Opcion = TextoInicial();
            while (Opcion != "0"){
                bool Flag = true;
                if (Opcion == "1"){
                    cout << "Inserte ID a buscar (Numero): ";
                    while(Flag){
                        cin >> ID;
                        if (ID < CantidadDeUsuarios && ID >= 0){
                            Flag = false;
                            Vertice* Sugerencias = sugerir_amigos(ID);
                            cout << "Sugerencias: ";
                            Vertice* Actual = Sugerencias;
                            if (Sugerencias == nullptr){
                                cout << "No se encuentran sugerencias" << endl;
                            }
                            while (Actual != nullptr){
                                cout << Actual->ID << " ";
                                Actual = Actual->Siguiente;
                            }
                            while(Sugerencias != nullptr){ //Liberacion de memory
                                Vertice* Temporal = Sugerencias;
                                Sugerencias = Sugerencias->Siguiente;
                                delete Temporal;
                            }
                        }

                        else{
                            cout << "ID inválido, intente nuevamente: ";
                        }
                        cout << endl;
                    }
                    cout << "\nProbar otra funcion: ";
                    cin >> Opcion;
                }
                else if (Opcion == "2"){
                    int Popular = usuario_mas_popular();
                    cout << "El usuario más popular es: " << Popular << endl;
                    cout << "\nProbar otra funcion: ";
                    cin >> Opcion;

                }
                else if (Opcion == "3"){
                    cout << "Hay un total de: " << contar_comunidades() << " comunidades" << endl;
                    cout << "\nProbar otra funcion: ";
                    cin >> Opcion;
                }
                else if (Opcion == "4"){
                    cout << "Inserte ID a buscar (Numero): ";
                    while(Flag){
                        cin >> ID;
                        if (ID < CantidadDeUsuarios && ID >= 0){
                            int influencia = calcular_influencia(ID);
                            cout << "La influencia de " << ID << " es: " << influencia;
                            Flag = false;
                        }
                        else{
                            cout << "ID inválido, intente nuevamente: ";
                        }
                    }
                    cout << endl;
                    cout << "\nProbar otra funcion: ";
                    cin >> Opcion; 
                }
                else if (Opcion == "5"){
                    Vertice* puentes = encontrar_puentes();
                    if(puentes == nullptr){
                        cout << "No se encontraron puentes"<< endl;
                    } else {
                        Vertice* temporal = puentes;
                        cout << "Los puentes son: ";
                        while(temporal != nullptr){
                            cout << temporal->ID << " ";
                            temporal = temporal->Siguiente;
                        }
                        cout << endl;
                    }
                    
                    while(puentes != nullptr){ //liberacion de memoria
                        Vertice* temp = puentes;
                        puentes = puentes->Siguiente;
                        delete temp;
                    }
                    cout << "\nProbar otra funcion: ";
                    cin >> Opcion;
                }
                else if(Opcion == "0"){
                    break;
                }
                else {
                    cout << "Inserte una opción válida: ";
                    cin >> Opcion;
            }
        }
    }
};

int main(){
    Grafo grafo;
    grafo.CrearGrafoConListaDeAdyacencia("datos.txt");
    //grafo.ImprimirGrafo(); //En caso de querer ver el grafo como lista de adyacencia 
    grafo.MenuInteractivo();
    return 0;
}
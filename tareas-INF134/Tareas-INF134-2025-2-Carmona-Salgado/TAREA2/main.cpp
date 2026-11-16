#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Esta tarea contiene MUCHÍSIMOS errores, algún día la arreglaré (Cuando no sea fin de semestre como ahora.)

struct Carta{
    char Palo;
    int Categoria;
    int Valor;
    bool Jugada;
};

//desde código nico
//TODO ACERCA DEL ARBOL:
struct NodoArbol{
    Carta CartaPalo;
    NodoArbol* Izquierda;
    NodoArbol* Derecha;
};
class Arbol{
    private:
        NodoArbol Nodos[13]; //Son 13 cartas, por lo tanto no necesitamos mas nodos por palo
        Carta PaloActual[13];
        NodoArbol* Raiz;
        Carta CartaInvalida;
        
        /*       Descripcion: 
            *           El objetivo de la funcion es ir insertando los nodos para formar el arbol ABB, donde en la izquierda estaran los menores y a la derecha los mayores, ya que las cartas vienen en orden ascendente, sabemos que la primera mitad seran menores y la segunda mitad mayones, asi que con esa informacion se va armando el arbol
            *
            *    Parametros:
            *            Dos enteros que seran el intervalo para realizar el arbol ABB
            *    
            *    Retorno:
            *            Funcion tipo NodoArbol, retorna la direccion de memoria del Nodo en la posicion media que sera el padre
        */
        NodoArbol* Insercion(int PosicionNodoInicial, int PosicionNodoFinal ){
            if (PosicionNodoInicial > PosicionNodoFinal) return nullptr; //Caso donde ya se recorrio todas las cartas por lo que ya no hay un rango valido
            int PosicionNodoMedio = (PosicionNodoInicial + PosicionNodoFinal) / 2; //Ya que las cartas estan ordenadas de 1 a 13, sabemos que el valor del medio, sera mayor a la primera mitad y menor a la segunda mitad
            Nodos[PosicionNodoMedio].CartaPalo = PaloActual[PosicionNodoMedio]; //Se obitene el numero que esta en la posicion media (por ejemplo el numero 7 y de ahí se va realizando el arbol) por lo que este sera el numero raiz
            Nodos[PosicionNodoMedio].Izquierda = Insercion(PosicionNodoInicial, PosicionNodoMedio - 1); //intervalo primera mitad
            Nodos[PosicionNodoMedio].Derecha = Insercion(PosicionNodoMedio + 1, PosicionNodoFinal); //intervalo mitad final
            return &Nodos[PosicionNodoMedio]; // el nodo padre
        }

         /*       Descripcion: 
            *           Ordena las cartas de forma in orden, va visitando los nodos de forma izquierda, raiz, derecha.
            *
            *    Parametros:
            *            Es el nodo actual que se le revisara sus conexiones (hijos)
            *    
            *    Retorno:
            *           Funcion tipo void, no retorna.
        */
        void InOrden(NodoArbol* NodoActual){ 
            if (NodoActual == nullptr) return;
            InOrden(NodoActual->Izquierda);
            InOrden(Raiz);
            InOrden(NodoActual->Derecha);
        }

    public:
        /*       Descripcion: 
            *            Es el constructor de la funcion, inicializa todo como nulo y una carta invalida en caso de que las cosas fallen
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            No tiene
        */
        Arbol() : Raiz(nullptr) { //Constructor
            for (int i = 0; i < 13; i++) {
                Nodos[i].Izquierda = nullptr;
                Nodos[i].Derecha = nullptr;
            }
            CartaInvalida.Palo = 'X';
            CartaInvalida.Categoria = 0;
            CartaInvalida.Valor = 0;
            CartaInvalida.Jugada = false;
        }
        /*       Descripcion: 
            *           Crea el arbol insertando la informacion correspondiente de cada palo 
            *
            *    Parametros:
            *            Un char los cuales seran C (Corazones), D (Diamantes), T (Trevoles), E (Espadas)
            *    
            *    Retorno:
            *            Tipo void no retorna
        */
        void CreacionArbolDeCartas(char Palo){
            for (int i = 0; i < 13; i++){
                PaloActual[i].Palo = Palo;
                PaloActual[i].Categoria = i + 1;
                if (PaloActual[i].Categoria == 1){
                    PaloActual[i].Valor = 11;
                }
                else if (PaloActual[i].Categoria >= 11){
                    PaloActual[i].Valor = 10;
                }
                else {
                    PaloActual[i].Valor = PaloActual[i].Categoria;
                }
                PaloActual[i].Jugada = false;
            }
            Raiz = Insercion(0, 12);
        }

        /*       Descripcion: 
            *          Muestra las cartas disponibles
            *
            *    Parametros:
            *            No contiene parametro
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void ComandoDisponibles(){
            for (int i = 0; i < 13; i++) {
                if (PaloActual[i].Jugada == false) cout << PaloActual[i].Categoria << PaloActual[i].Palo << " ";
            }
            cout << endl;
        }

        /*       Descripcion: 
            *          Muestra las cartas no disponibles
            *
            *    Parametros:
            *            No contiene parametro
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void ComandoNoDisponibles(){
            for (int i = 0; i < 13; i++) {
                if (PaloActual[i].Jugada == true) cout << PaloActual[i].Categoria << PaloActual[i].Palo << " ";
            }
            cout << endl;
        }

        /*       Descripcion: 
            *          Reinicia la jugada de la carta para cuando se reinicie la ronda o con nuevas jugadas
            *
            *    Parametros:
            *            No contiene parametro
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void ReiniciarCartas() {
            for (int i = 0; i < 13; i++) {
                PaloActual[i].Jugada = false;
            }
        }

        /*       Descripcion: 
            *          Entrega todas las cartas de cada palo, en caso de que no haya una carta de dicho palo, entonces entregará una carta invalida
            *
            *    Parametros:
            *            La posicion de dicha carta
            *    
            *    Retorno:
            *            Tipo Carta, entrega información de dicha carta en esa posicion 
        */
        Carta ObtenerCartas(int Posicion) {
            if (Posicion >= 0 && Posicion <= 12) {
                return PaloActual[Posicion];
            }
            return CartaInvalida;
        }
        
        /*       Descripcion: 
            *          Marca una carta como jugada basandose en su categoria
            *
            *    Parametros:
            *            La categoria de la carta (1-13)
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void MarcarCartaJugada(int Categoria) {
            if (Categoria >= 1 && Categoria <= 13) {
                PaloActual[Categoria - 1].Jugada = true;
            }
        }
};
  
//TODO ACERCA DE LAS LISTAS
struct NodoLista{
    Carta Cartas;
    NodoLista* Siguiente;
};

class ListaMazoBaraja{
    private:
        NodoLista* Cabeza;
        NodoLista NodosTotales[52]; //Un total de 52 cartas tiene el mazo
        int ContadorCarta;
        Carta CartaInvalida;
    public:

        /*       Descripcion: 
            *            Es el constructor de la funcion, inicializa todo como nulo y una carta invalida en caso de que las cosas fallen
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            No tiene
        */
        ListaMazoBaraja() : Cabeza(nullptr), ContadorCarta(0){ //Constructor
            for (int i = 0; i < 52; i++) {
                NodosTotales[i].Siguiente = nullptr;
            }
            CartaInvalida.Palo = 'X';
            CartaInvalida.Categoria = 0;
            CartaInvalida.Valor = 0;
            CartaInvalida.Jugada = false;
        }

        /*       Descripcion: 
            *            Es el destructor de la funcion, vacia el mazo
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            No tiene
        */
        ~ListaMazoBaraja(){ //Destructor
            VaciarMazo();
        }

        /*       Descripcion: 
            *            Crea el mazo que se utilizara en el juego, insertando todos en una lista
            *
            *    Parametros:
            *            Son los todos los arboles para insertarnos el un solo mazo
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void CrearMazoBarajado(Arbol Arboles[4]){
            Carta TodasLasCartas[52];
            int ContadorCartas = 0;
            for(int i = 0; i < 4; i++){
                for (int j = 0; j < 13; j++){
                    TodasLasCartas[ContadorCartas] = Arboles[i].ObtenerCartas(j); //Obtenemos todas las cartas de cada arbol 
                    ContadorCartas++;
                }
            }
            //Barajeo:
            for (int i = 0; i < 52; i++){
                int Random = rand() % 52; //Obtener numeros aleatorios de 1 y 52
                //Intercambiar posicion i con la posicion Random
                Carta CartasTemporal = TodasLasCartas[i];
                TodasLasCartas[i] = TodasLasCartas[Random];
                TodasLasCartas[Random] = CartasTemporal;
            }
            //ahora crear la lista enlazada:
            for(int i = 0; i < 52; i++){
                NodosTotales[i].Cartas = TodasLasCartas[i];
                NodosTotales[i].Siguiente = nullptr; //para evitar problemas de sobreescribir los nodos y mas en el numero final (el 52 debe siempre el siguiente apuntar a un nulo)
                if (i == 0){
                    Cabeza = &NodosTotales[i]; //si la posicion es 0, la cabeza sera esa carta
                }
                else{
                    NodosTotales[i-1].Siguiente = &NodosTotales[i]; //y con esto podremos hacer las conexioens entre nodos que se podrian perder al tener todos los nodos siguientes como nulos
                }
            }
            ContadorCarta = 52;
        }

        /*       Descripcion: 
            *        Entrega cartas al jugador de la baraja desde el inicio (cabeza)    
            *
            *    Parametros:
            *            No contiene parametros
            *    
            *    Retorno:
            *            Tipo Carta, retorna la carta del jugador recien obtenida
        */
        Carta SacarCartasDelJugador(){
            if(Cabeza == nullptr) return CartaInvalida;
            Carta CartaDelJugador = Cabeza->Cartas; //La primera carta del jugador sera la que esta en la cabeza
            Cabeza = Cabeza->Siguiente; //Mover la cabeza al siguiente nodo
            ContadorCarta--;
            return CartaDelJugador; 
        }

        /*       Descripcion: 
            *            Entrega la cantidad de cartas en el mazo
            *
            *    Parametros:
            *            No contiene parametros
            *    
            *    Retorno:
            *            Retorna un entero con la cantidad de cartas del mazo
        */
        int ObtenerCantidadCartas(){
            return ContadorCarta;
        }

        /*       Descripcion: 
            *            Vacia el mazo para cuando sea necesario
            *
            *    Parametros:
            *            No recibe parametros
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void VaciarMazo(){
            Cabeza = nullptr;
            ContadorCarta = 0;
            
        }
};

class ListaManoJugador{
    private:
        NodoLista* Cabeza;
        NodoLista NodosJugador[8];
        int ContadorCartasJugador; //esta siempre debe ser 8, ademas se utilizara para detectar la posicion para colocar la carta 
    public:
        /*       Descripcion: 
            *            Inicializa todo en nulo
            *
            *    Parametros:
            *            No tiene
            *    
            *    Retorno:
            *            No tiene
        */
       ListaManoJugador() : Cabeza(nullptr), ContadorCartasJugador(0){ //Constructor
            for (int i = 0; i < 8; i++) {
                NodosJugador[i].Siguiente = nullptr;
            }
        }

        /*       Descripcion: 
            *            Vacia las cartas por cada ronda o cuando se necesite
            *
            *    Parametros:
            *            No tiene 
            *    
            *    Retorno:
            *            No tiene
        */
        ~ListaManoJugador(){ //Destructor
            VaciarCartas();
        }

        NodoLista* getCabeza(){
            return Cabeza;
        }

        /*       Descripcion: 
            *            Inserta las cartas en la lista de la mano del jugador, esta debe tener a la izquierda A, J, Q... y asi
            *
            *    Parametros:
            *            La carta actual que se insertara (esta carta es la que obtenemos en la funcion de sacar cartas en la clase del mazo)
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void InsertarCartas(Carta &CartaActual){
            NodosJugador[ContadorCartasJugador].Cartas = CartaActual; //Carta que insertamos, muy importante para entender el ciclo de insercion!
            
            if (Cabeza == nullptr){ //Inserta en la posicion 0 y cabeza tomara ese valor
                Cabeza = &NodosJugador[ContadorCartasJugador];
                ContadorCartasJugador++;
                return;
            }
            
            // Determinar si debe ir antes de la cabeza
            bool insertarAntesCabeza = false;
            if (CartaActual.Categoria == 1) {
                // Si es As, va al inicio
                insertarAntesCabeza = true;
            } else if (Cabeza->Cartas.Categoria != 1 && CartaActual.Categoria > Cabeza->Cartas.Categoria) {
                // Si NO es As, y cabeza NO es As, y es mayor que cabeza
                insertarAntesCabeza = true;
            }
            
            if (insertarAntesCabeza) { //Insercion en la primera posicion post cabeza, si es un as o la carta es distinta al as y esta es mayor al valor anterior (cabeza) entonces cabeza cambiara a ser el siguiente nodo
                NodosJugador[ContadorCartasJugador].Siguiente = Cabeza; 
                Cabeza = &NodosJugador[ContadorCartasJugador];
                ContadorCartasJugador++;
                return;
            }
            
            //Insercion de medio o final (siguientes posiciones)
            NodoLista* PunteroParaRecorrer = Cabeza; //Necesitamos recorrer la lista enlazada completa asi que se crea un puntero para recorrer desde el inicio
            while (PunteroParaRecorrer->Siguiente != nullptr){
                bool insertarAqui = false;
                
                if (CartaActual.Categoria != 1) {
                    // Si NO es As
                    if (PunteroParaRecorrer->Siguiente->Cartas.Categoria == 1) {
                        // NUNCA insertar antes de un As
                        insertarAqui = false;
                    } else if (CartaActual.Categoria > PunteroParaRecorrer->Siguiente->Cartas.Categoria) {
                        // Insertar si es mayor que el siguiente
                        insertarAqui = true;
                    }
                }
                
                if (insertarAqui) {
                    NodosJugador[ContadorCartasJugador].Siguiente = PunteroParaRecorrer->Siguiente; //Hacemos la conexion entre el puntero que queremos insertar y el siguiente del puntero de la posicion donde estamos recorriendo (Es decir, el siguiente del que insertamos sera el siguiente de un puntero en x posicion)
                    PunteroParaRecorrer->Siguiente = &NodosJugador[ContadorCartasJugador]; //y con este hacemos la conexion entre el nodo de la posicion en la que estamos y el que insertamos (Es decir, el siguiente de una posicion x sera el nodo del que insertamos)
                    ContadorCartasJugador++;
                    return;
                }
                PunteroParaRecorrer = PunteroParaRecorrer->Siguiente; //esto es para las iteraciones, o sea que pase al siguiente nodo
            }
            
            PunteroParaRecorrer->Siguiente = &NodosJugador[ContadorCartasJugador]; //y esto es para intersectar al final, con numeros como 2
            ContadorCartasJugador++;
        }

        /*       Descripcion: 
            *            Con un puntero auxiliar, recorre todas las cartas, cumpliendo su objetivo de mostrar todas las cartas del jugador
            *
            *    Parametros:
            *            No recibe parametros
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void MostrarCartas(){
            NodoLista* Recorrer = Cabeza;
            while(Recorrer != nullptr){
                cout << Recorrer->Cartas.Categoria << Recorrer->Cartas.Palo << " ";
                Recorrer = Recorrer->Siguiente;
            }
            cout << endl;
        }

        /*       Descripcion: 
            *            Su objetivo es entregar la cantidad de cartas que tiene el jugador
            *
            *    Parametros:
            *            No recibe
            *    
            *    Retorno:
            *            Un entero con la cantidad de cartas que tiene el jugador
        */
        int CantidadCartas(){
            return ContadorCartasJugador;
        }    

        /*       Descripcion: 
            *            Descarta una carta dependiendo de su posicion realizando las nuevas conexiones entre las cartas que todavia quedan en el mazo del jugador. Esta funcion nuevamente es de forma recursiva, es decir que se va llamando la funcion por cada carta descartada
            *
            *    Parametros:
            *            Un entero de nombre posicion entre 0 y 7 
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void DescartePorPosicion(int Posicion){
            if (Cabeza == nullptr || Posicion < 0 || Posicion >= ContadorCartasJugador) return; //Si esta vacia, o no es un rango valido la posicion no se hara nada
            if (Posicion == 0){
                Cabeza = Cabeza->Siguiente; //Si la posicion es 0, entonces la cabeza va a cambiar a ser el nodo siguiente, descartando la cabeza anterior 
                ContadorCartasJugador--; //y así se disminuye la cantidad de cartas que tiene el jugador
                return;
            }
            NodoLista* Recorrer = Cabeza;
            int PosicionActual = 0;
            while (PosicionActual < Posicion - 1 && Recorrer->Siguiente != nullptr){ //Se recorre hasta la posicion anterior y ahí se hace la nueva conexion entre el anterior y el siguiente del descartado
                Recorrer = Recorrer->Siguiente;
                PosicionActual++;
            }
            if (Recorrer->Siguiente != nullptr){ //Si el siguiente no es nulo
                Recorrer->Siguiente = Recorrer->Siguiente->Siguiente; //El siguiente del será el siguiente del descartado saltando la posicion descartada 
                ContadorCartasJugador--;
            }
        }

        /*       Descripcion: 
            *            Vacia las cartas de la mano del jugador
            *
            *    Parametros:
            *            No recibe 
            *    
            *    Retorno:
            *            Tipo void, no retorna
        */
        void VaciarCartas(){
            Cabeza = nullptr;
            ContadorCartasJugador = 0;
        }

        /*       Descripcion: 
            *            Ordena las cartas de mayor a menor utilizando el método bubble sort, el cual consiste en comparar cada posicion con la posicion siguiente y en caso de que esten de menor a mayor, se intercambia
            *
            *    Parametros:
            *            Un arreglo de enteros con las posiciones y un entero de la cantidad de cartas que o se jugaran o se descartaran
            *    
            *    Retorno:
            *            Funcion tipo void, no retorna
        */
        void OrdenarPosiciones(int Posicion[], int CantidadDeCartas){ //debido a que en el descarte, estas nuevas conexiones se hacen de forma recursiva (llamar la funcion nuevamente) las posiciones van cambiando, por lo tanto si antes querias eliminar la posicion 2, pero antes cambiaste la 3, ahora la posicion 2 no sera la misma que antes, así que para evitar esos problemas, se hizo esta funcion para ordenar de mayor a menor las posiciones 
            for (int i = 0; i < CantidadDeCartas - 1; i++){ //Se asume que el utlimo valor siempre sera el mayor
                for (int j = 0; j < CantidadDeCartas - i - 1; j++){ //Cada vez se van comparando menos elementos ya que ya estan ordenado (por eso el -i)
                    if (Posicion[j] < Posicion[j + 1]){ //Compara la posicion actual con la posoicion siguiente y en caso de que sea menor, se hace el intercambio quedando de mayor a menor
                        int Temp = Posicion[j];
                        Posicion[j] = Posicion[j + 1];
                        Posicion[j + 1] = Temp;
                    }
                }
            }
        }
};  

//función auxiliar para sumar los valores de las cartas.
int sumarCartas(ListaManoJugador &ManoAJugar){
    int suma = 0;
    NodoLista* carta = ManoAJugar.getCabeza();

    while (carta != nullptr){
        suma += carta->Cartas.Valor;
        carta = carta->Siguiente;}

    return suma;
}

//otra función auxiliar para no crear punteros a la cabeza y recorrer toda la lista para cada mano.
int sumarCategorias(ListaManoJugador &mano, int categoria, int cantidad){
    NodoLista *cartita = mano.getCabeza();
    int suma = 0, repeticiones = 0;

    while (cartita != nullptr && repeticiones < cantidad){
        if(cartita->Cartas.Categoria == categoria) {
            suma += cartita->Cartas.Valor;
            repeticiones ++;
        }
        cartita = cartita->Siguiente;
    }
    return suma;
}

int FichasporMano (ListaManoJugador &ManoAJugar, string &tipoMano) {
    int PalosEnMano[4] = {0};
    int CategoriaEnMano[14] = {0}; //indices del 0 al 13.
    NodoLista *actual = ManoAJugar.getCabeza();
    int CartasJugador = ManoAJugar.CantidadCartas();
    int fichasObtenidas = 0;

    while (actual != nullptr){
        CategoriaEnMano[actual->Cartas.Categoria]++; //guarda el num de veces q aparece la categoria de una carta.
        if(actual->Cartas.Palo == 'E') PalosEnMano[0]++;
        else if(actual->Cartas.Palo == 'C') PalosEnMano[1]++;
        else if(actual->Cartas.Palo == 'T') PalosEnMano[2]++;
        else if(actual->Cartas.Palo == 'D') PalosEnMano[3]++;

        actual = actual->Siguiente; //avanza el ciclo.
    }
    //implementacion de manos de mayor a menor puntaje.
    //1. Póker.
    for (int i=1; i<=13; i++){ //empieza en 1 por el as.
        if(CategoriaEnMano[i] == 4) {
            tipoMano = "Poker";
            fichasObtenidas = 400 + sumarCategorias(ManoAJugar,i,4);
            return fichasObtenidas;}
    }
    //2. Color
    for (int i = 0; i < 4; i++) {
        if (PalosEnMano[i] == CartasJugador) {
            tipoMano = "Color";
            fichasObtenidas = 200 + sumarCartas(ManoAJugar);
            return fichasObtenidas;}
    }
    //3. Escalera.
    int cartasConsecutivas = 0;
    bool esEscala = false;
    for (int i=1; i <= 13; i++){
        if (CategoriaEnMano[i] > 0){//va revisando que las posiciones continuas estén con algún elemento.
            cartasConsecutivas++;
            if (cartasConsecutivas == 5){
                esEscala = true;
            }
        }
        else{
            cartasConsecutivas = 0; //se reinicia el contador en caso de que se encuentre una posicion vacia.
        }
    }//caso en que la escalera sea 10 J Q K A
    if(CategoriaEnMano[10]>0 && CategoriaEnMano[11]>0 && CategoriaEnMano[12]>0 &&
        CategoriaEnMano[13]>0 && CategoriaEnMano[1]>0) {
            esEscala = true;
    }
    if (esEscala == true){
        tipoMano = "Escalera";
        fichasObtenidas = 150 + sumarCartas(ManoAJugar);
        return fichasObtenidas;
    }
    //4. Tercia.
    for(int i = 1; i <= 13; i++){
        if (CategoriaEnMano[i] == 3){
            tipoMano = "Tercia";
            fichasObtenidas = 120 + sumarCategorias(ManoAJugar,i,3);
            return fichasObtenidas;
        }
    }
    //5. Doble par y par.
    int pares = 0, sumaPar = 0;
    for (int i = 1; i <= 13; i++){
        if (CategoriaEnMano[i]== 2){
            pares ++;
            sumaPar += sumarCategorias(ManoAJugar,i,2);
        }
    }
    if(pares == 2) {
        tipoMano = "Doble Par";
        fichasObtenidas = 80 + sumaPar;
        return fichasObtenidas;
    }
    else if(pares == 1){
        tipoMano = "Par";
        fichasObtenidas = 40 + sumaPar;
        return fichasObtenidas;
    }
    //6. carta +alta.
    int maxValor = 0;
    actual = ManoAJugar.getCabeza(); //reiniciamos el puntero
    while(actual != nullptr){
        if (actual->Cartas.Valor > maxValor) maxValor = actual->Cartas.Valor;
        actual = actual->Siguiente;
    }
    tipoMano = "Carta mas alta";
    fichasObtenidas = 50 + maxValor;
    return fichasObtenidas;
}

/*       Descripcion: 
    *          Marca todas las cartas de la mano del jugador como jugadas en los arboles correspondientes
    *
    *    Parametros:
    *            La mano del jugador y el arreglo de arboles
    *    
    *    Retorno:
    *            Tipo void, no retorna
*/
void MarcarCartasJugadas(ListaManoJugador &mano, Arbol Arboles[4]){
    NodoLista* actual = mano.getCabeza();
    while(actual != nullptr){
        char palo = actual->Cartas.Palo;
        int categoria = actual->Cartas.Categoria;
        
        if(palo == 'E') Arboles[0].MarcarCartaJugada(categoria);
        else if(palo == 'C') Arboles[1].MarcarCartaJugada(categoria);
        else if(palo == 'T') Arboles[2].MarcarCartaJugada(categoria);
        else if(palo == 'D') Arboles[3].MarcarCartaJugada(categoria);
        
        actual = actual->Siguiente;
    }
}

void Ronda (int pozo, int manosRonda, int descartesRonda, int &fichasTotal, bool ciegaJefe, bool &gana){
    ListaMazoBaraja Mazo;
    ListaManoJugador ManoJugador;
    int manos = manosRonda, descartes = descartesRonda;
    int CantidadDeCartas = 0;
    char Jugada;
    Carta CartaIndividual;

    Arbol Arboles[4];
    Arboles[0].CreacionArbolDeCartas('E');
    Arboles[1].CreacionArbolDeCartas('C');
    Arboles[2].CreacionArbolDeCartas('T');
    Arboles[3].CreacionArbolDeCartas('D');
    Mazo.CrearMazoBarajado(Arboles);

    int tamanoMano = 8;

    if (ciegaJefe){
        cout << "\nModificador de partida: El grillete. (-1 carta)" << endl;
        tamanoMano = 7;    
    }
    
    for (int i = 0; i < tamanoMano; i++){ //8 cartas del jugador 
        CartaIndividual = Mazo.SacarCartasDelJugador();
        ManoJugador.InsertarCartas(CartaIndividual);
    }
    
    MarcarCartasJugadas(ManoJugador, Arboles);

    while(manos > 0 && fichasTotal < pozo){
        cout << "\n"<< fichasTotal << " / " << pozo << " fichas\n";
        cout << Mazo.ObtenerCantidadCartas() << " / 52 cartas\n";
        cout <<  manos << "J / " << descartes << "D\n";
        ManoJugador.MostrarCartas();
        
        cout << "Juega: ";
        cin >> Jugada;

        if (Jugada == 'M'){
            cout << "\nDisponibles -" << endl;
            for (int i = 0; i < 4; i++){
                Arboles[i].ComandoDisponibles();
            }
            cout << "\nNo disponibles -" << endl;
            for (int i = 0; i < 4; i++){
                Arboles[i].ComandoNoDisponibles();
            }
        }
        else if (Jugada == 'D'){
            if(descartes > 0){
                cin >> CantidadDeCartas;
                int PosicionElegida[8];
                for (int i = 0; i < CantidadDeCartas; i++){
                    cin >> PosicionElegida[i];
                }
                ManoJugador.OrdenarPosiciones(PosicionElegida, CantidadDeCartas);
                for (int i = 0; i < CantidadDeCartas; i++){
                    ManoJugador.DescartePorPosicion(PosicionElegida[i]);
                }
                //reponer las cartas que eliminó el jugador 
                while(ManoJugador.CantidadCartas() < tamanoMano){
                    CartaIndividual = Mazo.SacarCartasDelJugador();
                    ManoJugador.InsertarCartas(CartaIndividual);
                }
                MarcarCartasJugadas(ManoJugador, Arboles);
                descartes--;
            }
            else {
                cout << "No hay descartes restantes." << endl;
            }
        }
        else if (Jugada == 'J'){
            if(manos > 0){
                cin >> CantidadDeCartas;
                int PosCartasElegidas[8];
                //para que el jugador ingrese los índices de las cartas que quiere jugar.
                for (int i = 0; i < CantidadDeCartas; i++){
                    cin >> PosCartasElegidas[i];
                }
                //creación de nueva lista que tendrá las cartas elegidas.
                ListaManoJugador ManoAJugar;
                for (int i = 0; i < CantidadDeCartas; i++){
                    NodoLista* posicion = ManoJugador.getCabeza();
                    for (int j = 0; j < PosCartasElegidas[i]; j++){
                        posicion = posicion->Siguiente;
                    }
                    ManoAJugar.InsertarCartas(posicion->Cartas);
                }
                
                string TipoMano; //variable vacía q guardará el tipo de mano q se encuentre.
                int fichasPorRonda = FichasporMano(ManoAJugar, TipoMano); //aquí se llamará a la función que calcula el valor d las manos, q tendrá como parámetro la nueva lista de las cartas y el string anterior.
                cout << "Mano jugada: " << TipoMano << endl;
                cout << "Fichas anotadas: " << fichasPorRonda << endl;
                fichasTotal += fichasPorRonda;
                manos--;
                //eliminar las cartas elegidad y reponerlas
                ManoJugador.OrdenarPosiciones(PosCartasElegidas, CantidadDeCartas);
                for (int i = 0; i < CantidadDeCartas; i++){
                    ManoJugador.DescartePorPosicion(PosCartasElegidas[i]);
                }
                while(ManoJugador.CantidadCartas() < tamanoMano){
                    CartaIndividual = Mazo.SacarCartasDelJugador();
                    ManoJugador.InsertarCartas(CartaIndividual);
                }
                MarcarCartasJugadas(ManoJugador, Arboles);
            }
            else {
                cout << "No hay manos restantes." << endl;
            }
        }
    }
    
    if (fichasTotal >= pozo) {
        gana = true;
        return;
    }
    if(manos == 0){
        gana = false;
        cout << "\nFin del juego. Has perdido!\n";
        return;
    }
}


int main(){
    srand(time(0));
    int FichasTotales = 0;
    bool gana = false;

    cout << "\nBienvenido al maravilloso juego de DataBalatro!" << endl;

    cout << "\nComienza la ciega pequena, pozo a vencer: 250 fichas." << endl;
    Ronda(250, 4, 3, FichasTotales, false, gana);
    if(gana == true){
        cout << "\nCiega pequena vencida: " << FichasTotales << " / 250 fichas.\n";
        gana = false;
        
        cout << "\nComienza la ciega grande, pozo a vencer: 350 fichas." << endl;
        Ronda(350, 4, 3, FichasTotales, false, gana);
        if(gana == true){
            cout << "\nCiega grande vencida: " << FichasTotales << " / 350 fichas.\n";
            gana = false;
            
            cout << "\nComienza la ciega jefe, pozo a vencer: 500 fichas." << endl;
            Ronda(500, 4, 3, FichasTotales, true, gana);
            if(gana == true){
                cout << "\nCiega jefe vencida: " << FichasTotales << " / 500 fichas.\n";
                cout << "\nFelicidades! Has ganado el juego!\n";
            }
        }
    }
    
    return 0;
}
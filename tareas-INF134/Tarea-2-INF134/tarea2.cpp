#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
using namespace std;

//JUGADOR:
//Se crea la class jugador, con sus correspondientes funciones, como efectos y el return de estos mismos.
class Player{
    private:
        int vida = 30;
        int ataque = 10;
        float precision = 1.0;
        int recuperacion = 3;
    public:
        void AgregarVida(int vida_agregada){
            vida += vida_agregada;
        }
        void AgregarPrecision(float precision_agregada){
            precision += precision_agregada;
        }
        void AgregarAtaque(int ataque_agregado){
            ataque += ataque_agregado;
        }
        void AgregarRecuperacion(int recuperacion_agregada){
            recuperacion += recuperacion_agregada;
        }
        void AgregarVidaDespuesDelCombate (){
            vida += recuperacion;
        }
        int Vida(){
            return vida;
        }
        int Ataque(){
            return ataque;
        }
        int Recuperacion(){
            return recuperacion;
        }
        float Precision(){
            return precision;
        }

};

//ARBOL, MOVIMIENTO DEL JUGADOR:

//Se crea el struct de nodos, donde se guardan las variables para parte de la creación del arbol.
struct ConjuntoNodos{
    int Vertice; 
    string Nombre, Tipo, Descripcion;
    ConjuntoNodos* PrimerHijo , *SegundoHijo, *TercerHijo;
    //Constructor del conjunto de nodos para que se incialice vacios.
    ConjuntoNodos() : PrimerHijo(nullptr), SegundoHijo(nullptr), TercerHijo(nullptr) {};
};
//Se crea un espacio de memoria asegurado del nodo para poder acceder a el dentro del main.
ConjuntoNodos* Nodo(int Vertice, string Nombre, string Tipo, string Descripcion){
    ConjuntoNodos* NodoEspacioAsegurado = new ConjuntoNodos;
    NodoEspacioAsegurado->Vertice = Vertice;
    NodoEspacioAsegurado->Nombre = Nombre;
    NodoEspacioAsegurado->Tipo = Tipo;
    NodoEspacioAsegurado->Descripcion = Descripcion;
    return NodoEspacioAsegurado;
};

//Se crea la class del arbol, que contiene el nodo, el tamaño que es número total de nodos que contiene y la posición actual que irá cambiando.
class ArbolTernario{
    private:
        ConjuntoNodos** Nodo;
        int NumeroTotalDeNodos;
        int PosicionActual = 0;
        ConjuntoNodos* NodoActual;
    public:
        // Se crea GuardarTamanho, con el fin de tener guardado el numero total de nodos, además de poder acceder a cada uno de los elementos en el arreglo si fuera necesario.
        void GuardarTamanho(int NumeroDeNodo){
            Nodo = new ConjuntoNodos*[NumeroDeNodo];
            NumeroTotalDeNodos = NumeroDeNodo;   
        }
        // Se crea LimpiarMemoriaDeNodos para liberar la memoria dinamica de nodos.
        void LimpiarMemoriaDeNodos() {
            if (Nodo) {
                for (int i = 0; i < NumeroTotalDeNodos; ++i) {
                    delete Nodo[i]; 
                }
                delete[] Nodo;
                Nodo = nullptr; 
                NumeroTotalDeNodos = 0;
                PosicionActual = 0;
            }
        }
        // Se establece Crear con el fin de poder ir guardadando nuevos nodos con la información correspondiente (Vertice, nombre, descripción)  
        void Crear(ConjuntoNodos* NodoNuevo){
            Nodo[PosicionActual] = NodoNuevo;
            PosicionActual++;
            
        }
        // Se establece como primer nodo siempre el de la posición 0.
        void PrimerNodo(){
            NodoActual = Nodo[0];
        }
        //Se crean los arcos en el arbol, estableciendo 3 casos, donde, si "padre (o raíz)" está vacio/nulo, es decir no tiene hijo 1, se establecerá como el hijo 1, y así sucesivamente
        void PadreHijo(int Padre, int Hijo){
            if (!Nodo[Padre]->PrimerHijo){ 
                Nodo[Padre]->PrimerHijo = Nodo[Hijo];
            }
            else if (!Nodo[Padre]->SegundoHijo){
                Nodo[Padre]->SegundoHijo = Nodo[Hijo];
            }
            else {
                Nodo[Padre]->TercerHijo = Nodo[Hijo];
            }
        }
        //Se crea el movimiento del jugador para ir a opción 1, opción 2...
        void MovimientoJugador(){
            string Eleccion;
            bool flag = true;
            //Si el nodo donde estamos, no tiene hijo, será nulo, así que será un nodo fin.
            if (!NodoActual->PrimerHijo){
                NodoActual = nullptr;
                return;
            }
            while (flag){
                int TotalOpciones = 0;
                if (NodoActual->PrimerHijo) TotalOpciones++;
                if (NodoActual->SegundoHijo) TotalOpciones++;
                if (NodoActual->TercerHijo) TotalOpciones++;
                cout << "¿A qué lugar te gustaría ir? \n";
                this_thread::sleep_for(chrono::seconds(1));

                //Da todas las opciones donde se podría ir.
                for (int i = 0; i < TotalOpciones; i++) {
                    if (i == 0 && NodoActual->PrimerHijo)
                        cout << i+1 << "." << NodoActual->PrimerHijo->Nombre << '\n';
                    if (i == 1 && NodoActual->SegundoHijo)
                        cout << i+1 << "." << NodoActual->SegundoHijo->Nombre << '\n';
                    if (i == 2 && NodoActual->TercerHijo)
                        cout << i+1 << "." << NodoActual->TercerHijo->Nombre << '\n';
                }

                cin >> Eleccion;
                //Casos a donde irá el jugador gracias a la opción que escogió.
                if (Eleccion == "1"){
                    NodoActual = NodoActual->PrimerHijo;
                    flag = false;
                }
                else if (Eleccion == "2"){
                    NodoActual = NodoActual->SegundoHijo;
                    flag = false;
                }
                else if (Eleccion == "3" && NodoActual->TercerHijo ){
                    NodoActual = NodoActual->TercerHijo;
                    flag = false;
                }
                else{
                    cout << "Haz elegido una opción incorrecta, ";
                }
            }   
        }
        //Retorna el nodo actual.
        ConjuntoNodos* RetornarNodoActual(){
            return NodoActual;
        }
};

//EVENTOS:


// Se crea EventoOpciones, donde se guardan el nombre, la descripcion del la opcion de un evento escogido, el tipo de efecto (Precision, ataque...) y el efecto (Negativo, positivo.).
struct EventoOpciones{
    string Nombre, DescripcionOpcion, NombreDelEfecto, Efecto ;
};

//Se crea un espacio de memoria asegurado de la opción del evento para poder acceder a el dentro del main.
EventoOpciones* EventoOpcionesEspacioAsegurado(string Nombre, string DescripcionOpcion, string NombreDelEfecto, string Efecto){
    EventoOpciones* EventoOpcionesEspacioAsegurado = new EventoOpciones;
    EventoOpcionesEspacioAsegurado->Nombre = Nombre;
    EventoOpcionesEspacioAsegurado->DescripcionOpcion = DescripcionOpcion;
    EventoOpcionesEspacioAsegurado->NombreDelEfecto = NombreDelEfecto;
    EventoOpcionesEspacioAsegurado->Efecto = Efecto;
    return EventoOpcionesEspacioAsegurado;
};

//Se crea Evento, donde se guarda los datos del evento, como su nombre, su descripción, sus dos opciones, y la probabilidad de que salga dicho evento.
struct Evento{
    string Nombre, DescripcionEvento;
    EventoOpciones OpcionA , OpcionB;
    float ProbabilidadDeQueSalgaElEvento;
};
//Se crea un espacio de memoria asegurado del evento para poder acceder a el dentro del main.
Evento * EventoEspacioAsegurado(string Nombre, float Probabilidad, string Descripcion, EventoOpciones OpcionA, EventoOpciones OpcionB){
    Evento *EventoEspacioAsegurado = new Evento;
    EventoEspacioAsegurado->Nombre= Nombre;
    EventoEspacioAsegurado->DescripcionEvento= Descripcion;
    EventoEspacioAsegurado->ProbabilidadDeQueSalgaElEvento= Probabilidad;
    EventoEspacioAsegurado->OpcionA = OpcionA;
    EventoEspacioAsegurado->OpcionB = OpcionB;
    return EventoEspacioAsegurado;
}

//Toma de decisiones acerca de las opciones del evento que apareció con su respectivo efecto, ya sea positivo o negativo..
Evento* EscogerOpcion(Evento* EventoActual, Player& jugador){
    cout << "A)" + EventoActual->OpcionA.Nombre + '\n';
    cout << "B)" + EventoActual->OpcionB.Nombre + '\n';
    string Opcion;
    
    bool flag = true;   
    while (flag){
        cout << "¿Qué opción eligirás? ";
        cin >> Opcion;
        //Si la opción es A, entra aquí, donde depende del nombre del efecto, dentrá consecuencias, ya sea positivas o negativas.
        if (Opcion == "A" or Opcion == "a"){
            cout << EventoActual->OpcionA.DescripcionOpcion;
            if (EventoActual->OpcionA.NombreDelEfecto == "Vida"){
                jugador.AgregarVida(stoi(EventoActual->OpcionA.Efecto));
            }
            if (EventoActual->OpcionA.NombreDelEfecto == "Precision"){
                jugador.AgregarPrecision(stof(EventoActual->OpcionA.Efecto));
            }
            if (EventoActual->OpcionA.NombreDelEfecto == "Ataque"){
                jugador.AgregarAtaque(stoi(EventoActual->OpcionA.Efecto));
            }

            cout << ' ' + EventoActual->OpcionA.NombreDelEfecto + ' ' + EventoActual->OpcionA.Efecto + '\n';
            flag = false;
        }
        //Si la opción es B, entra aquí, donde depende del nombre del efecto, dentrá consecuencias, ya sea positivas o negativas.
        else if (Opcion == "B" or Opcion == "b"){
            cout << EventoActual->OpcionB.DescripcionOpcion;
            if (EventoActual->OpcionB.Nombre == "Vida"){
                jugador.AgregarVida(stoi(EventoActual->OpcionB.Efecto));
            }
            if (EventoActual->OpcionB.NombreDelEfecto == "Precision"){
                jugador.AgregarPrecision(stof(EventoActual->OpcionB.Efecto));
            }
        cout << EventoActual->OpcionB.NombreDelEfecto + ' ' + EventoActual->OpcionB.Efecto + '\n';
            flag = false;
        }
        else {
            cout << "Haz ingresado una opción incorrecta ";
        }
    }
    return EventoActual;
}
//Las mejoras de combate, donde el jugador puede elegir que mejorar de estos 4 casos.
struct MejorasDeCombate {
    int Ataque, Vida, Recuperacion;
    float Precision;
};

void MejoraEscogida(Player& Jugador, MejorasDeCombate Mejora){
    bool flag = true;
    string Opcion;
    cout << "1. Ataque \n";
    cout << "2. Vida \n";
    cout << "3. Recuperación \n";
    cout << "4. Precision\n";
    while (flag){
        cin >> Opcion;
        if (Opcion == "1"){
            Jugador.AgregarAtaque(Mejora.Ataque);
            flag = false;
            cout << "Haz mejorado tu ataque, ahora tienes: " + to_string(Jugador.Ataque()) + " de ataque\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (Opcion == "2"){
            Jugador.AgregarVida(Mejora.Vida);
            flag = false;
            cout << "Haz mejorado tu vida, ahora tienes: " + to_string(Jugador.Vida()) + " de vida\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (Opcion == "3"){
            Jugador.AgregarRecuperacion(Mejora.Recuperacion);
            cout << "Haz mejorado tu recuperacion, ahora tienes: " + to_string(Jugador.Recuperacion()) + " de recuperacion\n";
            this_thread::sleep_for(chrono::seconds(1));
            flag = false;
        }
        else if (Opcion == "4"){
            Jugador.AgregarPrecision((Mejora.Precision));
            cout << "Haz mejorado tu precision, ahora tienes: " + to_string(Jugador.Precision()) + " de precision\n";
            this_thread::sleep_for(chrono::seconds(1));
            flag = false;
        }
        else{
            cout << "Haz ingresado una opcion incorrecta\n";
        }
    }
}


//ENEMIGOS, TDA COLA [un infierno]:

//Se crea Enemigo, donde se guarda las variables del enemigo, como su nombre, vida, ataque, precision y probabilidad.
struct Enemigo{
    string Nombre;
    int Vida, Ataque;
    float Precision, ProbabilidadDeQueAparezca;

    //Se crea un constructor "copia" para copiar los enemigos (Estos se utilizarán en el combate para editar una copia de los enemigos y no al enemigo base.
    Enemigo(Enemigo& copia) {
        Nombre = copia.Nombre;
        Vida = copia.Vida;
        Ataque = copia.Ataque;
        Precision = copia.Precision;
        ProbabilidadDeQueAparezca = copia.ProbabilidadDeQueAparezca;
    }
    //Y un constructor por defecto.
    Enemigo() = default;
};

//Se crea un espacio de memoria asegurado del enemigo para poder acceder a el dentro del main.
Enemigo* EnemigoEspacioAsegurado(string Nombre, int Vida, int Ataque, float Precision, float Probabilidad){
    Enemigo* EnemigoEspacioAsegurado= new Enemigo;
    EnemigoEspacioAsegurado->Nombre = Nombre;
    EnemigoEspacioAsegurado->Vida = Vida;
    EnemigoEspacioAsegurado->Ataque= Ataque;
    EnemigoEspacioAsegurado->Precision= Precision;
    EnemigoEspacioAsegurado->ProbabilidadDeQueAparezca= Probabilidad;
    return EnemigoEspacioAsegurado;
};

//Se crea EnemigosEnCombate para poder seleccionar los enemigos y al siguiente enemigo escogido para ingresarlos en la cola después.

struct EnemigosEnCombate{
    Enemigo* EnemigoEscogido;
    EnemigosEnCombate* SiguienteEnemigo;
};

//Se crea la TDA Cola, 
class ColaCombate{
    private:
    EnemigosEnCombate* Head; //Head como cabeza siendo inicio de la cola.
    EnemigosEnCombate * Tail; //Tail como cola siendo el final de la ya nombrada.
    public:
    //Constructor para inicializar todo vacio.
    ColaCombate(){Head = nullptr, Tail = nullptr;}

    //Función para agregar al enemigo que fue seleccionado por su probabilidad, además de crear un espacio de memoria asegurada para el enemigo.
    void AgregarEnemigo(Enemigo* Enemy){
        EnemigosEnCombate* EspacioAseguradoParaLosEnemigosSeleccionados = new EnemigosEnCombate;
        EspacioAseguradoParaLosEnemigosSeleccionados->EnemigoEscogido = Enemy;
        EspacioAseguradoParaLosEnemigosSeleccionados->SiguienteEnemigo = nullptr; //Inicializa al siguiente enemigo como vacio.
        if (Tail) {Tail->SiguienteEnemigo = EspacioAseguradoParaLosEnemigosSeleccionados;} //Si el final no está vacio, pasa al siguiente enemigo y lo guarda.
        else{ Head = EspacioAseguradoParaLosEnemigosSeleccionados;} //Si no, se guardará en el inicio (cabeza)
        Tail = EspacioAseguradoParaLosEnemigosSeleccionados;
    }
    //Se crea EliminarEnemigo para eliminar los enemigos en la cola.
    void EliminarEnemigo(){
        if (!Head) return; //Si la cabeza está vacia, entonces no retornará nada.
        EnemigosEnCombate* aux = Head; //Se establece un auxiliar que toma el valor de la cabeza
        delete aux->EnemigoEscogido; //Primero se elimina la copia del enemigo (guardada en aux) y luego el nodo.
        Head = Head->SiguienteEnemigo; // En la cabeza, guarda al Enemigo siguiente.
        if (!Head) {
            Tail = nullptr; //Si la cabeza está vacía, la cola también lo estará.
        }
        delete aux;
    }
    // Se crea MoverCabezaAlFinal para mover los turnos de los enemigos.
    void MoverCabezaAlFinal(){
        if (!Head || Head == Tail) { //Si la cabeza está vacia o la cabeza es igual al final entonces retornará nada,
            return;
        }
        EnemigosEnCombate* AntiguoHead = Head; //Remplaza los valores, siendo el enemigo anterior "AntiguoHead"
        Head = Head->SiguienteEnemigo; //y Head toma como valor el enemigo siguiente.

        AntiguoHead->SiguienteEnemigo = nullptr;  //El enemigo anterior no tiene enemigo siguiente, por lo tanto.
        Tail->SiguienteEnemigo = AntiguoHead; // La cola tomará el valor del enemigo anterior
        Tail = AntiguoHead; //Lo que lo traerá al final.

        if (Head == nullptr) {
            Head = Tail; // Si la cola queda vacía, Head y Tail apuntan al mismo nodo.
        }
    }
    //Retorna el primer enemigo que fue escogido.
    Enemigo* PrimerEnemigo(){
        return Head->EnemigoEscogido;
    }
    //Retorna true, en caso de que la cabeza no esté vacia, por lo tanto la cola no esté vacia.
    bool Vacia(){
        if (!Head) return true;
        else return false;
    }

    //Tiene com finalizadad vaciar la cola en caso de que algún enemigo quedó del combate anterior.
    void VaciarCola(){
        while (Head != nullptr) {
            EnemigosEnCombate* aux = Head; 
            delete aux->EnemigoEscogido; //Primero se elimina la copia del enemigo (guardada en aux) y luego el nodo.
            Head = Head->SiguienteEnemigo;
            delete aux;
        }
        Tail = nullptr;
    }
};



int main (){
    //Se crea para el uso de numeros aleatorios. Uso de librería <random> 
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    // Se crean las identidades Arbol, Jugador para el uso de las class y se crea Enemigo** y Evento** para guardar la información que se obitene en el archivo y poder acceder a ella para la formación del juego.
    ArbolTernario Arbol;
    Player Jugador;
    
    MejorasDeCombate Mejora;
    Enemigo** DatosEnemigo;
    Evento** DatosEvento;
    fstream Mapa;
    ColaCombate Cola;
    //Se inicializan en 0, las cantidades de cada habitación (O también de cada nodo), evento y enemigos.
    int CantidadDeHabitaciones = 0;
    int CantidadDeEventos = 0;
    int CantidadDeEnemigos = 0;

    //Abrir el mapa, en caso de que falle, se manda el mensaje de que no se pudo abrir.
    Mapa.open("data.map",ios::in);
    if (!Mapa.is_open()){
        cout << "¡No se pudo abrir la aventura!" << endl;
        exit(1);
    }

    //Inicio de obtener los datos del .map para luego utilizarlos.
    string Linea;
    while (getline(Mapa, Linea)) {
        //Datos de las habitaciones:
        if (Linea == "HABITACIONES"){
            int Vertice;
            string Nombre, TipoDeHabitacion, Descripcion;
            Mapa >> CantidadDeHabitaciones;
            Arbol.GuardarTamanho(CantidadDeHabitaciones); //Se guardan las cantidad de habitaciones en guardar tamaño para tener la cantidad total de nodos.
            Mapa.ignore();
            for (int i = 0 ; i < CantidadDeHabitaciones; i++){
                Mapa >> Vertice >> Nombre >> TipoDeHabitacion; //Guarda el vertice, el nombre de la habitación y su tipo de habitación ya sea combate, evento.
                Mapa.ignore(); //Salto de línea.
                getline(Mapa, Descripcion);
                Arbol.Crear(Nodo(Vertice, Nombre, TipoDeHabitacion, Descripcion)); //Se crea el nodo con esa información.
            } 
        }
        //Datos de los caminos que puede tomar el jugador.
        if (Linea == "ARCOS"){
                int Padre, Hijo;
                string flecha; //Solamente como auxiliar para asegurar que Padre e hijo si tomaron correctamente los valores.
                int CantidadDeArcos;
                Mapa >> CantidadDeArcos;
                Mapa.ignore();
                for (int i= 0; i < CantidadDeArcos;i++){
                    Mapa >> Padre >> flecha >> Hijo;
                    Arbol.PadreHijo(Padre, Hijo); //Así se obitenen las relaciones
                }
        }
        //Datos de los enemigos fundamental para el combate.
        if (Linea == "ENEMIGOS"){
            string x, Nombre; //Nuevamente "x" como auxilitar para que se ingresen por si acaso correctamente los datos.
            int Vida, Ataque;
            float Precision, Probabilidad;
            Mapa >> CantidadDeEnemigos;
            DatosEnemigo = new Enemigo*[CantidadDeEnemigos]; //Se establece este array, para guardar la cantidad de enemigos que deberá guardar DatosEnemigo, además será lo que utlizará el constructur de copia, para crear los "nuevos" enemigos.
            Mapa.ignore();
            for(int i=0; i < CantidadDeEnemigos; i++){
                Mapa >> Nombre >> x >> x >> Vida >> x >> x >> Ataque >> x >> x >> Precision >> x >> x >> Probabilidad;
                DatosEnemigo[i]= EnemigoEspacioAsegurado(Nombre, Vida, Ataque, Precision, Probabilidad); //Se guardan los datos de enemigo.
            }
        }
        //Datos de los eventos.
        if (Linea == "EVENTOS"){
            EventoOpciones* Opciones[2]; //Se establece el array Opciones con dos casos, ya que son A y B.
            Mapa >> CantidadDeEventos;
            DatosEvento = new Evento*[CantidadDeEventos]; //Se establece este array para guardar la cantidad de eventos que guardará DatosEvento
            Mapa.ignore();

            for (int i = 0; i < CantidadDeEventos ; i++){
                string Nombre, DescripcionDelEvento, LineasDentroDeEvento, x;
                float ProbabilidadDeQueSalgaDichoEvento;
                getline(Mapa, LineasDentroDeEvento);
                Mapa >> Nombre;
                Mapa.ignore();
                Mapa >> x >> ProbabilidadDeQueSalgaDichoEvento;
                Mapa.ignore();
                getline(Mapa, DescripcionDelEvento);

                for (int a = 0; a < 2; a++){
                    string NombreDeLaOpcion, DescripcionDeLaOpcion, NombreDelEfecto, Efecto;
                    Mapa >> x;
                    getline(Mapa, NombreDeLaOpcion);
                    getline(Mapa, DescripcionDeLaOpcion);
                    Mapa >> Efecto >> NombreDelEfecto;
                    Mapa.ignore();
                    Opciones[a] = EventoOpcionesEspacioAsegurado(NombreDeLaOpcion, DescripcionDeLaOpcion, NombreDelEfecto, Efecto); //Se guarda la información de las opciones (Esto se utilizará luego en Evento* EventoOpciones para ver que opción eligirá el jugador.)
                } 
            DatosEvento[i]= EventoEspacioAsegurado(Nombre, ProbabilidadDeQueSalgaDichoEvento, DescripcionDelEvento, *Opciones[0], *Opciones[1]);

            //liberación de memoria.
            delete Opciones[0];
            delete Opciones[1];
            }
        }
        //Datos de las mejoras de combate
        if (Linea == "MEJORAS DE COMBATE"){
            string x;
            int Vida, Ataque, Recuperacion;
            float Precision;
            Mapa >> Vida >> x >> Precision >> x >> Ataque >> x >> Recuperacion;
            Mejora.Vida =Vida;
            Mejora.Precision = Precision;
            Mejora.Ataque = Ataque;
            Mejora.Recuperacion = Recuperacion;
        }
    }  
    
    Mapa.close();
    //Fin de la toma de información.
   
    //Reproducción de historia:
    Arbol.PrimerNodo();
    ConjuntoNodos* NodoActual = Arbol.RetornarNodoActual(); //Te retorna el nodo donde te encuentras.
    bool JugadorEstaVivo = true; // Booleano para asegurar que todo pase si el jugador está vivo.
    for (int i = 0; i < CantidadDeHabitaciones && JugadorEstaVivo;i++){
        if (!NodoActual || JugadorEstaVivo == false) { // Si el nodo actual está vacio (Nodo final) o el jugador se murió será el fin de la historia.
            cout << " :・° FIN :・° \n";
            break;
        }
        cout << "༒︎  " + NodoActual->Nombre + " ༒︎ " + '\n';
        this_thread::sleep_for(chrono::seconds(1));
        cout << NodoActual->Descripcion + '\n';
        this_thread::sleep_for(chrono::seconds(1));
        
        //Caso 1, el tipo de habitación es un evento:
        if (NodoActual->Tipo == "(EVENTO)"){
            cout << "✩ ¡Haz entrado a un evento! ✩ \n";
            float Random = float(dist(gen)) / 100; //Numero aleatorio: entre 0 y 1.
            float AcumulacionDeEventos = 0.0; //Se utilizará para poder guardar el evento que concuerde con Random para que se eliga de manera aleatoria.
            int Seleccionado;
            for (int a = 0; a < CantidadDeEventos; a++){
                if (Random <= AcumulacionDeEventos + DatosEvento[a]->ProbabilidadDeQueSalgaElEvento){ //Si el numero aleatorio es menor o igual al acumulacion de la probabilidad del evento + la probabilidad de que salga un evento, este será escogido, en otro caso, no será escogido.
                    Seleccionado = a;
                    break;
                }
                else{
                    AcumulacionDeEventos += DatosEvento[a]->ProbabilidadDeQueSalgaElEvento; //Si no es escogido, a la probablidad acumulada del evento que no fue escogido, se le sumará la probablidad del evento que salió.
                }
            }
            cout << "*ੈ ✩ ‧ ₊ ˚ " + DatosEvento[Seleccionado]->Nombre + " *ੈ ✩ ‧ ₊ ˚\n";
            this_thread::sleep_for(chrono::seconds(1));
            cout << DatosEvento[Seleccionado]->DescripcionEvento +"\n";
            this_thread::sleep_for(chrono::seconds(1));
            EscogerOpcion(DatosEvento[Seleccionado], Jugador); //Aquí se llama la función de EscogerOpcion para que el jugador al elegir dicha opción, pase que lo corresponde a la opcion escogida.        }
        }
        //Caso 2, cuando el Nodo donde te encuentras es de combate. (Inserte emoji calavera)
        if (NodoActual->Tipo == "(COMBATE)"){
            cout << " ⚔ Haz entrado a un combate ⚔ \n";
            this_thread::sleep_for(chrono::seconds(1));
            if (CantidadDeEnemigos == 0){
                cout << "Pero no llego nadie... Combate cancelado." << endl;

            } else {
                int NumeroAleatorioDeEnemigos = dist(gen) % 4 + 1; //Se crea un numero aleatorio entre 1 y 4.
                Enemigo** EnemigosQuePelearan = new Enemigo*[NumeroAleatorioDeEnemigos]; //Se establece el array que guardará la cantidad de enemigos que pelearán y su información.
                int ContadorDeEnemigosCreados = 0;
                bool Seleccionado = false;
           
                for (int i = 0; i < NumeroAleatorioDeEnemigos; i++){
                    EnemigosQuePelearan[i] = nullptr; //Inicializado vacio.
                    float AcumulacionDeEnemigos = 0.0; //Se utilizará para poder guardar el enemigo que concuerde con NumeroAleatorioDeEnemigos para que se eliga de manera aleatoria.
                    float NumeroAleatorio = float(dist(gen)) / 100; //Se crea un numero aleatorio entre 0 y 1 para la eleccion del enemigo por su probabilidad.
                    for (int a = 0 ; a < CantidadDeEnemigos ; a++){
                        if (NumeroAleatorio <= AcumulacionDeEnemigos + DatosEnemigo[a]->ProbabilidadDeQueAparezca || a == CantidadDeEnemigos - 1){
                            EnemigosQuePelearan[i] = new Enemigo(*DatosEnemigo[a]); //Se guardan los datos del enemigo copiado en el arreglo.
                            Seleccionado = true; //
                            break;
                        }
                    else{
                        AcumulacionDeEnemigos += DatosEnemigo[a]->ProbabilidadDeQueAparezca; //Acumulacion de enemigos y acumulación de eventos funcionan de la misma manera, ambos, van comparando el numero aleatorio con la probablidad de que este aparezca dicho enemigo o evento, si no concuerda, este se irá sumando, hasta que uno se seleccione.
                    }
                }
                //Ingreso a la cola del enemigo escogido.
                if (Seleccionado && EnemigosQuePelearan[i] != nullptr) { //Si seleccionado es true es verdadero (es decir si se escogieron los enemigos) y el arreglo de enemigos que pelearán está vacio, entonces esté ingresará a al cola.
                    Cola.AgregarEnemigo(EnemigosQuePelearan[i]);
                    ContadorDeEnemigosCreados++;
                    cout << "[Te encontraste con " + EnemigosQuePelearan[i]->Nombre + ']' + '\n';
                } else {
                    cerr << "Advertencia: No se pudo crear el enemigo " << i+1 << "/" << NumeroAleatorioDeEnemigos << endl;
                }
            }

            if (ContadorDeEnemigosCreados == 0) {
                cout << "No se pudo generar ningún enemigo para el combate.\n";
                delete[] EnemigosQuePelearan;
            } else if (ContadorDeEnemigosCreados > 0) { //Aquí comienza la creación del combate.
                bool TurnoJugador = true;
                int EnemigosVivos = ContadorDeEnemigosCreados;
                int EnemigosPorAtacar = EnemigosVivos;

                while (!Cola.Vacia() && JugadorEstaVivo){
                    this_thread::sleep_for(chrono::seconds(1));
                    Enemigo* EnemigoActual = Cola.PrimerEnemigo(); //Abreviación de cola.PrimerEnemigo().
                    
                    if (TurnoJugador){
                        float NumeroAleatorio = float(dist(gen)) / 100; //Se crea numero aleatorio entre 0 y 1 para que si la precision es mayor o igual a este numero, va atacar si no, fallará.
                        if (NumeroAleatorio <= Jugador.Precision()){
                            EnemigoActual->Vida -= Jugador.Ataque();
                            cout << "Ataque de jugador a " + EnemigoActual->Nombre + " con " + to_string(Jugador.Ataque()) + " de ataque\n";
                            this_thread::sleep_for(chrono::seconds(1));
                            cout << "¡Al enemigo le queda: " + to_string(EnemigoActual->Vida) + " de vida! \n"; 
                            this_thread::sleep_for(chrono::seconds(1));
                        } else { 
                            cout << "¡Oh no!, haz fallado el ataque\n";
                        }

                        if (EnemigoActual->Vida <= 0) {
                            EnemigosVivos--;
                            cout << "¡Has derrotado a " + EnemigoActual->Nombre + "!\n";
                            Cola.EliminarEnemigo(); //Al enemigo derrotado se borra de la cola.

                            if (EnemigosVivos == 0){
                                cout << " 𐃯 ¡Combate terminado! Felicidades, has ganado 𐃯 \n";
                                this_thread::sleep_for(chrono::seconds(1));
                                Jugador.AgregarVidaDespuesDelCombate();
                                cout << "Haz recuperado un poco de vida\n";
                                this_thread::sleep_for(chrono::seconds(1));
                                cout << "Ahora... ¡Decide que quieres mejorar\n";
                                MejoraEscogida(Jugador, Mejora);
                                break;
                            }
                        }
                        else {
                            if (!Cola.Vacia() && EnemigosVivos > 0) {
                                Cola.MoverCabezaAlFinal(); //Si no murió entonces, el enemigo rotará al final.
                            }
                        } 
                        EnemigosPorAtacar = EnemigosVivos; //Para que ataquen todos los enemigos antes de que ataque el jugador.
                        TurnoJugador = false;           
                    }
                    else{
                        if (Cola.Vacia())break; //Si no hay más enemigos entonces el combate a sido finalizado.

                        float NumeroAleatorio = float(dist(gen)) / 100; //Se crea numero aleatorio entre 0 y 1 para que si la precision es mayor o igual a este numero, va atacar si no, fallará.
                        if (NumeroAleatorio <= EnemigoActual->Precision){
                            Jugador.AgregarVida(-EnemigoActual->Ataque);
                            cout << "¡Ataque de " + EnemigoActual->Nombre + " con " + to_string(EnemigoActual->Ataque) + " de ataque!\n";
                            this_thread::sleep_for(chrono::seconds(1));
                            cout << "Te queda: " + to_string(Jugador.Vida()) + " de vida\n";
                        }
                        else{
                            cout << "¡" + EnemigoActual->Nombre + " falló el ataque, es tu oportunidad!\n";
                        }

                        //Caso donde muere el jugador.
                        if (Jugador.Vida() <= 0){
                            cout << "Oh no, moriste. Suerte en la próxima ( ˚ ˃̣̣̥  ⌓ ˂̣̣̥  )\n";
                            Cola.VaciarCola();
                            JugadorEstaVivo = false;
                            break;
                        }

                        if (!Cola.Vacia()) {
                            Cola.MoverCabezaAlFinal(); //Nuevamente rotación de enemigos.
                        }
                        EnemigosPorAtacar--;
 
                        if(EnemigosPorAtacar <= 0){
                            TurnoJugador = true; //Luego de que atacaron todos los enemigos, puede atacar el jugador.
                        }
                    }
                    
                }
                delete[] EnemigosQuePelearan; //Liberación de memoria.
                if(!Cola.Vacia()){ //Limpiar la cola por si quedan enemigos residuales.
                    Cola.VaciarCola();
                }
                }
                
            }   
        }

        if (!JugadorEstaVivo) break;
        Arbol.MovimientoJugador(); //Llamada de la funcion para que el jugador se pueda mover para tomar una decision (arcos).
        NodoActual = Arbol.RetornarNodoActual();

        }


    // Liberación de memoria dinámica.
    for (int k = 0; k < CantidadDeEnemigos; k++) { if(DatosEnemigo && DatosEnemigo[k]) delete DatosEnemigo[k]; }
    if(DatosEnemigo) delete[] DatosEnemigo;

    for (int k = 0; k < CantidadDeEventos; k++) { if(DatosEvento && DatosEvento[k]) delete DatosEvento[k]; } 
    if(DatosEvento) delete[] DatosEvento;

    Arbol.LimpiarMemoriaDeNodos();
    
    return 0;
}

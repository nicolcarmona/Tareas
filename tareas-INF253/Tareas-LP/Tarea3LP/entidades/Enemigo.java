package entidades;
import componentes.Estadisticas;

public abstract class Enemigo{
    public String nombre;
    protected int xpRecompensa;
    protected int chatarraRecompensa;
    protected Estadisticas stats;

    public Enemigo(String nombre, int xpRecompensa, int chatarrarecompensa, int hp, int fuerza){
        /*       Descripcion: 
        *            constructor que inicializa los datos del enemigo
        *
        *    Parametros:
        *            un String nombre, un entero con la cantidad de experiencia de la recompensa, un entero que entrega la cantidad de chatarra de la recompensa, un entero hp con la vida y un entero con la fuerza.
        *    
        *    Retorno:
        *            no tiene
        */
        this.nombre = nombre;
        this.xpRecompensa = xpRecompensa;
        this.chatarraRecompensa = chatarrarecompensa;
        this.stats = new Estadisticas(hp, fuerza);
    }
    public int getXpRecompensa(){
        return xpRecompensa;
    }
    public int getChatarraRecompensa(){
        return chatarraRecompensa;
    }
    public Estadisticas getEstadisticas(){
        return stats;
    }

    /*       Descripcion: 
        *            metodo abstracto que heredaran los enemigos
        *
        *    Parametros:
        *            Objeto cloud tipo Jugador.
        *    
        *    Retorno:
        *            metodo tipo void, no tiene.
        */
    public abstract void atacar(Jugador cloud);

    public void giveXpRecompensa(Jugador cloud){
        /*       Descripcion: 
        *            Entrega la experiencia de la recompensa a cloud
        *
        *    Parametros:
        *            Objeto cloud tipo Jugador.
        *    
        *    Retorno:
        *            metodo tipo void, no tiene.
        */
        cloud.recibirXP(this.xpRecompensa);
    }
}
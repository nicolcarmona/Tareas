package entidades;
import java.util.List;
import java.util.Random;

import componentes.Elemento;
import componentes.Vulnerable;


public class EnemigoSalvaje extends Enemigo implements Vulnerable{
    private List<Elemento> debilidades;
    private List<Elemento> resistencias;
    private List<Elemento> inmunidades;

    public EnemigoSalvaje(String nombre, int hp, int fuerza, List<Elemento> debilidades, List<Elemento> resistencias, List<Elemento> inmunidades) {
        /*       Descripcion: 
        *            constructor que inicializa los valores del enemigo salvaje
        *
        *    Parametros:
        *            un String nombre, un entero con la vida, un entero con la fuerza, una lista de elementos que seran las debilidades, una lista con elementos que son las resistencias y una lista de elementos que seran las inmunidades
        *    
        *    Retorno:
        *            no tiene
        */
        super(nombre, new Random().nextInt(21) + 80, new Random().nextInt(26) + 50,  hp, fuerza);
        this.debilidades = debilidades;
        this.resistencias = resistencias;
        this.inmunidades = inmunidades;
    }

    public double evaluarDebilidad(Elemento elementoMagia){
        /*   Descripcion: 
        *            este metodo evalua la debilidad del enemigo
        *
        *    Parametros:
        *            un Elemento que sera el tipo de la debilidad/resitencia/inmunidad
        *    
        *    Retorno:
        *            Un tipo double
        */
        if (debilidades.contains(elementoMagia)) {
            return 2.0;
        }
        else if (resistencias.contains(elementoMagia)) {
            return 0.5;
        }
        else if (inmunidades.contains(elementoMagia)) {
            return 0.0;
        }
        else {
            return 1.0;
        }
    }

    public void giveChatarraRecompensa(Jugador cloud){
        /*       Descripcion: 
        *            metodo que entrega la chatarra de la recompensa del enemigo a cloud
        *
        *    Parametros:
        *            Un objeto cloud de tipo Jugador
        *    
        *    Retorno:
        *            no tiene
        */
        cloud.setChatarra(cloud.getChatarra() + chatarraRecompensa);
    }
    
    public void atacar(Jugador cloud){
        /*       Descripcion: 
        *            un metodo que es la logica del ataque de los enemigos
        *
        *    Parametros:
        *            Objeto cloud tipo Jugador
        *    
        *    Retorno:
        *            no tiene
        */
        int probabilidad = new Random().nextInt(100) + 1;
        if (probabilidad <= 85){
            int daño = (int)(stats.getFuerza() * 1.25);
            cloud.recibirDMG(daño);
            System.out.println("¡" + nombre + " atacó a Cloud!");

        }
        else{
            System.out.println("¡" + nombre + " ha fallado!");
        }
    }
}
package mapa;
import java.util.List;
import entidades.Enemigo;
import entidades.Jugador;
import java.util.Scanner;

public abstract class Zona{
    public String nombre;
    protected int nivelRequerido;
    protected List<Enemigo> enemigosDisponibles;

    public Zona(String nombre, int nivelRequerido, List<Enemigo> enemigosDisponbles){
        /*       Descripcion: 
        *            constructor que inicializa los valores de las zonas
        *
        *    Parametros:
        *            string nombre, un entero con el nivel para poder entrar a la zona y una lista con los enemigos disponibles.
        *    
        *    Retorno:
        *            no tiene
        */
        this.nombre = nombre;
        this.nivelRequerido = nivelRequerido;
        this.enemigosDisponibles = enemigosDisponbles;
    }

    public int getNivelRequerido(){
        return nivelRequerido;
    }

    public List<Enemigo> getEnemigosDispo(){
        return enemigosDisponibles;
    }

    /*       Descripcion: 
        *            metodo abstracto que heredaran las sub clases
        *
        *    Parametros:
        *            cloud Jugador y un scanner para obtener lo que pondra el jugador en la consola
        *    
        *    Retorno:
        *            no tiene
        */
    public abstract void accionZona(Jugador cloud, Scanner scanner);

    public boolean validarAcceso(Jugador cloud){
        /*       Descripcion: 
        *            metodo que valida el acceso a la zonas
        *
        *    Parametros:
        *            objeto jugador cloud
        *    
        *    Retorno:
        *            un booleano
        */
        if (cloud.getNivel() >= nivelRequerido){
            return true;
        }
        else{
            return false;
        }

    }
}
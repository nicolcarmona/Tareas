package entidades;
import java.util.Random;

public class EnemigoSimulador extends Enemigo{
    public EnemigoSimulador(){ 
        /*       Descripcion: 
        *            constructor que inicializa los datos del enemigo simulador
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        super("Soldado Común", new Random().nextInt(6) + 15, 0, 50, 15);
    }

    public void atacar(Jugador cloud){
        /*       Descripcion: 
        *            un metodo que ve la logica de ataque del enemigo simulador a cloud
        *
        *    Parametros:
        *            objeto cloud tipo jugador
        *    
        *    Retorno:
        *            no tiene
        */
        int probabilidad = new Random().nextInt(100) + 1;
        if(probabilidad <= 85){
            int daño = (int)(stats.getFuerza() * 1.25);
            if ((cloud.getStats().getHpActual() - daño) < 1){
                cloud.getStats().setHpActual(1);
            }
            else{
                cloud.recibirDMG(daño);
            }
            System.out.println("¡" + nombre + " atacó a Cloud!");
        }
        else{
            System.out.println("¡" + nombre + " ha fallado!");
        }
    }

    public boolean checkDanoSeguro(Jugador cloud){
        /*       Descripcion: 
        *            ve si para cloud es seguro atacar o no
        *
        *    Parametros:
        *            objeto cloud de tipo Jugador
        *    
        *    Retorno:
        *            retorna un booleano
        */
        int daño = (int)(stats.getFuerza() * 1.25);
        if ((cloud.getStats().getHpActual() - daño) < 1){
            return false;
        }
        else{
            return true;
        }
    }
}

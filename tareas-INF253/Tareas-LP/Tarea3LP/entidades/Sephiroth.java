package entidades;

import java.util.Random;

public class Sephiroth extends Enemigo{
    private int contadorSuperNova;
    public Sephiroth(){ 
        /*       Descripcion: 
        *            constructor que inicializa los valores de Sephiroth
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        super("Sephiroth", 0, 0, 500, 40);
    }

    public int getContadorSuperNova(){
        return contadorSuperNova;
    }

    public void resetContador(){
        /*       Descripcion: 
        *            metodo que reinicia el contador al aplicar un ataque cargado limite
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        contadorSuperNova = 0;
    }

    public void lanzarSuperNova(Jugador cloud){
        /*       Descripcion: 
        *            metodo que al lanzar la super nova mata a cloud
        *
        *    Parametros:
        *            objeto cloud tipo Jugador
        *    
        *    Retorno:
        *            no tiene
        */
        cloud.getStats().setHpActual(0);
    }

    public void atacar(Jugador cloud){
        /*       Descripcion: 
        *            metodo del ataque de sephiroth
        *
        *    Parametros:
        *            objeto cloud tipo Jugador
        *    
        *    Retorno:
        *            no tiene
        */
        contadorSuperNova++;
        if (contadorSuperNova >= 10){ //si hay 10 entonces chao cloud
            System.out.println("¡Sephiroth lanzó SUPER NOVA! ¡Daño devastador!");
            lanzarSuperNova(cloud);
        }
        else{
            int probabilidad = new Random().nextInt(100) + 1; 
            //probabilidad de ataque de sephiroth
            if(probabilidad <= 90){
                int daño = (int)(stats.getFuerza() * 1.25);
                cloud.recibirDMG(daño);
                System.out.println("¡Sephiroth atacó a Cloud y le infligió " + daño + " de daño!");

            }
            else{
                System.out.println("¡Sephiroth ha fallado!");
            }
        }
    }

}
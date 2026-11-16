package mapa;
import java.util.Arrays;
import java.util.Scanner;

import entidades.*;
import componentes.*;

public class NucleoPlaneta extends Zona{
    private int materiasMinimasRequeridas;

    public NucleoPlaneta(){
        /*       Descripcion: 
        *            constructor que inicializa los valores del nucleo
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        super("Núcleo del Planeta", 20, Arrays.asList(new Sephiroth()));
        materiasMinimasRequeridas = 2;
    }

    public void iniciarCombate(Jugador cloud){
        System.out.println("======================================================\n");
        System.out.println("<<< INICIANDO COMBATE CONTRA BOSS FINAL >>>\n");
        System.out.println("<<<< SEPHIROTH >>>>\n");
       
        boolean batalla =  new Combate(cloud, Arrays.asList(new Sephiroth())).iniciarBatalla(false, false);
        if(batalla){
            //si gano, entonces saldra una animacion de una espada, queria que fuera un chocobo pero no encontre el ascii art
            try{
                Thread.sleep(1000);
                System.out.println(" >> ¡Has derrotado a Sephiroth! <<\n");
                Thread.sleep(1000);
                System.out.println(">> ¡Cloud ha salvado el planeta! <<\n");
                Thread.sleep(1000);
                System.out.println("   /|\n");
                Thread.sleep(500);
                System.out.println("   |\\|\n");
                Thread.sleep(500);
                System.out.println("   |||\n");
                Thread.sleep(500);
                System.out.println("   |||\n");
                Thread.sleep(500);
                System.out.println("   |||\n");
                Thread.sleep(500);
                System.out.println("   |||\n");
                Thread.sleep(500);
                System.out.println("   |||\n");
                Thread.sleep(500);
                System.out.println("   |||\n");
                Thread.sleep(500);
                System.out.println("~-[{o}]-~\n");
                Thread.sleep(500);
                System.out.println("   |/|\n");
                Thread.sleep(500);
                System.out.println("   |/|\n");
                Thread.sleep(500);
                System.out.println("   `0'\n");
                Thread.sleep(1000);
                System.out.println(" >> Gracias por jugar, cerrando juego...<<\n");
                System.exit(0);

            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }
            
    public void accionZona(Jugador cloud, Scanner Scanner){
        /*       Descripcion: 
        *            metodo de la accion de la zona de nucleo
        *
        *    Parametros:
        *            dos objetos, cloud de tipo Jugador y un scanner para leer lo que el jugador pone en la terminal.
        *    
        *    Retorno:
        *            no tiene
        */
        System.out.println("======================================================\n");
            System.out.println("ZONA: Núcleo del Planeta | NIVEL:" + cloud.getNivel()+ "\n");
            System.out.println("HP: " + cloud.getStats().getHpActual() + "/" + cloud.getStats().getHpMax() + "| MP: " + cloud.getStats().getMpActual() + "/" + cloud.getStats().getMpMax() + "\n"); ;
            System.out.println("XP: "+ cloud.getXpActual() + " | MATERIAS EQUIPADAS:" + cloud.getBusterSword().getMaterias().size() + "/5");
            System.out.println("BARRA LIMITE: " + cloud.getLimiteActual() + "/100 \n");
            System.out.println("======================================================\n");
        if(cloud.getBusterSword().getMaterias().size() < materiasMinimasRequeridas){
            System.out.println("Necesitas al menos 2 materias equipadas!");
        }
        else{
            iniciarCombate(cloud);
        }
    }
}
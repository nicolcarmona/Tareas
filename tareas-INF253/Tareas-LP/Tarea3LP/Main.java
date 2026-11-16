import mapa.*;
import entidades.*;

import java.util.List;
import java.util.Scanner;

import componentes.*;

public class Main{
    public static void main(String[] args){
        /*       Descripcion: 
        *            constructor donde se va a hacer todo el juego, se inicializa todo.
        *
        *    Parametros:
        *            firma estandar del main en java
        *    
        *    Retorno:
        *            no tiene metodo void.
        */
        Jugador cloud = new Jugador();
        Sector7 sector7 = new Sector7();
        Gongaga gongaga = new Gongaga();
        NucleoPlaneta nucleo = new NucleoPlaneta();
        
        Zona zonaActual = sector7;
        
        try(Scanner scanner = new Scanner(System.in)){
            while(true){
                System.out.println("======================================================\n");
                System.out.println("<<< MAPA >>> \n");
                System.out.println("======================================================\n");
                System.out.println("ZONA: " + zonaActual.nombre + " | NIVEL:" + cloud.getNivel()+ "\n");
                System.out.println("HP: " + cloud.getStats().getHpActual() + "/" + cloud.getStats().getHpMax() + "| MP: " + cloud.getStats().getMpActual() + "/" + cloud.getStats().getMpMax() + "\n"); ;
                System.out.println("XP: "+ cloud.getXpActual() + " | MATERIAS EQUIPADAS:" + cloud.getBusterSword().getMaterias().size() + "/5" + " | Chatarra : "+ cloud.getChatarra());
                System.out.println("BARRA LIMITE: " + cloud.getLimiteActual() + "/100 \n");
                System.out.println("======================================================\n");
                System.out.println("1. Explorar zona actual\n");
                System.out.println("2. Explorar zona siguiente\n");
                System.out.println("3. Ver estadisticas de Cloud\n");
                System.out.println("4. Ver mochila y equipar materia en arma\n");
                System.out.println("5. Salir del juego\n");
                System.out.println("> ¿Qué deseas hacer? \n");  
                int opcion = scanner.nextInt();

                //movimiento de zonas
                if(opcion == 1){
                    zonaActual.accionZona(cloud, scanner);
                    if(cloud.getFueDerrotado()){
                        zonaActual = sector7;
                        cloud.setFueDerrotado(false);
                    }
                }

                else if(opcion == 2){
                    System.out.println("> Zonas disponibles: \n");
                    System.out.println("1. Sector 7\n");
                    System.out.println("2. Gongaga (Requiere nivel 5)\n");
                    System.out.println("3. Núcleo del Planeta (Requiere nivel 20)\n");
                    System.out.println("> ¿A dónde deseas viajar? ");
                    int destino = scanner.nextInt();
                    
                    if(destino == 1){
                        zonaActual = sector7;
                    }
                    else if(destino == 2){
                        if(gongaga.validarAcceso(cloud)){
                            zonaActual = gongaga;
                        }else{
                            System.out.println("<< Necesitas nivel 5!");
                        }
                    }
                    else if(destino == 3){
                        if(nucleo.validarAcceso(cloud)){
                            zonaActual = nucleo;
                        }else{
                            System.out.println("<< Necesitas nivel 20!");
                        }
                    }
                }
                
                else if (opcion == 3){
                    System.out.println("--- ESTADISTICAS ---\n");

                    System.out.println("Fuerza: " + cloud.getStats().getFuerza() + "| Magia: " + cloud.getStats().getMagia() + "\n");
                    System.out.println("Arma equipada: " + cloud.getBusterSword().nombre + "\n Materias equipadas: ");
                    List<Materia> materias = cloud.getBusterSword().getMaterias();
                    for(int i = 0; i < materias.size(); i++){
                        System.out.println((i+1) + ". " + materias.get(i).getElemento());
                    }
                    System.out.println("\n");
                }

                else if(opcion == 4){
                    if(cloud.getMochila().size() == 0){
                        System.out.println(">> No tienes materias en la mochila <<\n");
                    }
                    else{
                        for(int i = 0; i < cloud.getMochila().size(); i++){
                            System.out.println((i+1) + ". " + cloud.getMochila().get(i).getElemento());
                        }
                        System.out.println("¿Desea equipar una materia en su arma? (1: SI, 0: NO) ");
                        int eleccion = scanner.nextInt();
                        if (eleccion == 1){
                            System.out.println("¿Qué materia desea equipar al arma? (Responda en el orden que se mostró en la mochila)");
                            int eleccion2 = scanner.nextInt() - 1;   
                            cloud.getBusterSword().equiparMateria(cloud.getMochila().get(eleccion2));
                        }
                    }
                }

                else if (opcion == 5){
                    System.exit(0);
                }
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
}
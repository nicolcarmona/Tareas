package mapa;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;


import entidades.*;
import componentes.*;


public class Sector7 extends Zona{
    private List<Mejora> tiendaLocal;

    public Sector7(){
        /*       Descripcion: 
        *            constructor que inicializa los valores de la zona con su unico enemigo y los de la tienda
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        super("Sector 7", 0, Arrays.asList(new EnemigoSimulador()));
        tiendaLocal = new ArrayList<>();
        tiendaLocal.add(new Mejora("Mejora de Vitalidad", 100, TipoStat.HP_MAX, 20));
        tiendaLocal.add(new Mejora("Mejora de Éter", 120, TipoStat.MP_MAX, 10));
        tiendaLocal.add(new Mejora("Mejora Física", 150, TipoStat.FUERZA, 10));
    }

    
    public void iniciarSimulador(Jugador cloud){
        /*       Descripcion: 
        *            metodo para iniciar la batalla de la simulacion
        *
        *    Parametros:
        *            objeto cloud tipo jugador
        *    
        *    Retorno:
        *            no tiene
        */
        Random rand = new Random();
        List<Enemigo> enemigos = new ArrayList<>(); 
        enemigos.add(new EnemigoSimulador());//si o si aparece 1
        if(rand.nextInt(100) + 1 > 70){ //30% de que aparezcan 2
            enemigos.add(new EnemigoSimulador());
        }
        System.out.println("==============================================\n");
        System.out.println(">>> INICIANDO SIMULACION <<<\n");
        new Combate(cloud, enemigos).iniciarBatalla(true, true);

    }

    public void abrirTienda(Jugador cloud, Scanner scanner){
        /*       Descripcion: 
        *            metodo para poder ver la tienda y agregar los stats al jugador al comprarlo
        *
        *    Parametros:
        *            dos objetos, uno cloud tipo jugador y otro scanner para ver la opcion del jugador en la terminal
        *    
        *    Retorno:
        *            no tiene
        */
        boolean Menu = false;
        System.out.println("==============================================\n");
        System.out.println(">>> BIENVENIDO A LA TIENDA <<<\n");

        while(!Menu){
            System.out.printf("< Mejoras disponibles: >\n");
            System.out.println("1. Mejora de Vitalidad: Aumenta +20 HP maximo Costo: 100 de chatarra\n");
            System.out.println("2. Mejora de Éter: Aumenta +10 MP maximo Costo: 120 de chatarra\n");
            System.out.println("3. Mejora fisica: Aumenta +10 de fuerza Costo: 150 de chatarra\n");
            System.out.println("4. Salir de la tienda\n");
            System.out.println(">> ¿Qué mejora desea adquerir?: ");
            int opcion = scanner.nextInt();
            System.out.println("\n");            

            if(opcion == 1){
                Mejora mejora = tiendaLocal.get(0);
                if(cloud.getChatarra() >= mejora.getCostoChatarra()){
                    cloud.setChatarra(cloud.getChatarra() - mejora.getCostoChatarra());
                    if(mejora.getStatAfectado() == TipoStat.HP_MAX){
                        cloud.getStats().setHpMax(cloud.getStats().getHpMax() + mejora.getValorBono());
                    }
                    System.out.println("Mejora aplicada!\n");
                }
                else{
                    System.out.println("No tienes suficiente cantidad de chatarra\n");
                }
            }

            else if(opcion == 2){
                Mejora mejora = tiendaLocal.get(1);
                if(cloud.getChatarra() >= mejora.getCostoChatarra()){
                    cloud.setChatarra(cloud.getChatarra() - mejora.getCostoChatarra());
                    if(mejora.getStatAfectado() == TipoStat.MP_MAX){
                        cloud.getStats().setMpMax(cloud.getStats().getMpMax() + mejora.getValorBono());
                    }
                    System.out.println("Mejora aplicada!\n");
                }
                else{
                    System.out.println("No tienes suficiente cantidad de chatarra\n");
                }
            }

            else if(opcion == 3){
                Mejora mejora = tiendaLocal.get(2);
                if(cloud.getChatarra() >= mejora.getCostoChatarra()){
                    cloud.setChatarra(cloud.getChatarra() - mejora.getCostoChatarra());
                    if(mejora.getStatAfectado() == TipoStat.FUERZA){
                        cloud.getStats().setFuerza(cloud.getStats().getFuerza() + mejora.getValorBono());
                    }
                    System.out.println("Mejora aplicada!\n");
                }
                else{
                    System.out.println("No tienes suficiente cantidad de chatarra\n");
                }
            }

            else if(opcion == 4){
                Menu = true;
            }

            else{
                System.out.println("Opcion no disponible, vuelve a intentarlo");
            } 
        }       
    }

    public void accionZona(Jugador cloud, Scanner scanner){
        /*       Descripcion: 
        *            metodo de la accion que se puede hacer en el sector7
        *
        *    Parametros:
        *            2 objetos, cloud tipo jugador y un scanner para leer la opcion del jugador en la terminal
        *    
        *    Retorno:
        *            no tiene
        */
        boolean SigueMenu = true;
        
        while(SigueMenu){
            System.out.println("======================================================\n");
            System.out.println("ZONA: Sector 7 | NIVEL:" + cloud.getNivel()+ "\n");
            System.out.println("HP: " + cloud.getStats().getHpActual() + "/" + cloud.getStats().getHpMax() + "| MP: " + cloud.getStats().getMpActual() + "/" + cloud.getStats().getMpMax() + "\n"); ;
            System.out.println("XP: "+ cloud.getXpActual() + " | MATERIAS EQUIPADAS:" + cloud.getBusterSword().getMaterias().size() + "/5" + " | Chatarra : "+ cloud.getChatarra());
            System.out.println("BARRA LIMITE: " + cloud.getLimiteActual() + "/100 \n");
            System.out.println("======================================================\n");
            System.out.println("1. Entrar al simulador de combate\n");
            System.out.println("2. Abrir tienda\n");
            System.out.println("3. Descansar en la posada (Recupera HP y MP)\n");
            System.out.println("4. Ver estadisticas de Cloud\n");
            System.out.println("5. Salir del Sector 7\n");
            System.out.println("> ¿Qué deseas hacer? \n");  
            int opcion = scanner.nextInt();

            if(opcion == 1){
                iniciarSimulador(cloud);
            }
            else if(opcion == 2){
                abrirTienda(cloud, scanner);
            }
            else if(opcion == 3){ 
                //esto aparecia en la demo, asi que asumi que era necesario ponerlo
                System.out.println("Cloud ha tenido una reparadora sienta\n");
                System.out.println(">> HAS RECUPERADO EL MAXIMO DE HP Y MP <<\n");
                cloud.getStats().setHpActual(cloud.getStats().getHpMax());
                cloud.getStats().setMpActual(cloud.getStats().getMpMax());
            }   
            else if (opcion == 4){
                System.out.println("--- ESTADISTICAS ---\n");
                System.out.println("Fuerza: " + cloud.getStats().getFuerza() + "| Magia: " + cloud.getStats().getMagia() + "\n");
                System.out.println("Arma equipada: " + cloud.getBusterSword().nombre + "\n Materias equipadas: ");
                List<Materia> materias = cloud.getBusterSword().getMaterias();
                for(int i = 0; i < materias.size(); i++){
                    System.out.println((i+1) + ". " + materias.get(i).getElemento());
                }
                System.out.println("\n");
            }
            else if (opcion == 5){
                SigueMenu = false;
            }
        }
    }
}

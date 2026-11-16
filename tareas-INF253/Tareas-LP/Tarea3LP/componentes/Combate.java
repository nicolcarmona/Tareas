package componentes;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Random;
import entidades.*;

//Clase extra que agrege para manejar el combate y no reutilizar tanto codigo 
public class Combate {
    private Jugador cloud;
    private List<Enemigo> enemigos;
    private Scanner scanner;
    private Random rand;
    
    public Combate(Jugador cloud, List<Enemigo> enemigos){
        /*       Descripcion: 
        *            Constructor publico de la clase combate, inicializa los valores que uno le pasa cuando es llamada       
        *
        *    Parametros:
        *            cloud de tipo clase Jugador, una lista con los enemigos
        *    
        *    Retorno:
        *            No retorna, ya que es un constructor.
        */
        this.cloud = cloud;
        this.enemigos = enemigos;
        this.scanner = new Scanner(System.in);
        this.rand = new Random();
    }

    private void turnoEnemigo(List<Enemigo> enemigos, Jugador cloud, Random rand){
        /*       Descripcion: 
        *            metodo para manejar los turnos de los enemigos       
        *
        *    Parametros:
        *            lista con enemigos, un objeto cloud de clase Jugador, un numero random (para elegir que enemigo ataca cuando son mas de 1)
        *    
        *    Retorno:
        *            Metodo tipo void, no retorna
        */
        System.out.println("--- TURNO ENEMIGO ---");
        if(enemigos.size() == 1){ //si es 1, y esta vivo, simplemente ataca el que esta en la primera posicion
            if(enemigos.get(0).getEstadisticas().getHpActual() > 0){
                enemigos.get(0).atacar(cloud);
            }
        }
        else{
            int probabilidadJuntos = 0; //para guardar los valores de probabilidad que ataquen todos juntillos
            if(enemigos.size() == 2) probabilidadJuntos = 50;
            if(enemigos.size() == 3) probabilidadJuntos = 33;

            int probAtaque = rand.nextInt(100) + 1; //el numero random que se va a comparar con la anterior probabilidad
            if(probAtaque <= probabilidadJuntos){
                //para evitar que ataquen enemigos fantasmas (aka muertos)
                for(int i = 0; i < enemigos.size(); i++){
                    if(enemigos.get(i).getEstadisticas().getHpActual() > 0){
                        enemigos.get(i).atacar(cloud);
                    }
                }
            }
            else{
                //en caso de que solo ataque uno, guardamos todos los enemigos vivos, y obtenemos que ataque uno aleatorio
                List<Integer> enemigosVivos = new ArrayList<>();
                for(int i = 0; i < enemigos.size(); i++){
                    if(enemigos.get(i).getEstadisticas().getHpActual() > 0){
                        enemigosVivos.add(i);
                    }
                }
                int enemigosVivoAleatorio = enemigosVivos.get(rand.nextInt(enemigosVivos.size()));
                enemigos.get(enemigosVivoAleatorio).atacar(cloud);
            }
        }
    }

    private boolean verificarMuertos(List<Enemigo> enemigos, Jugador cloud){
        /*       Descripcion: 
        *            metodo que verifica si los enemigos estan muertos para ver si gano el combate y aplicar recompensas
        *
        *    Parametros:
        *            Una lista con los enemigos y una lista con los enemigos
        *    
        *    Retorno:
        *            Un booleano que devuelve si estan todos muertos o no
        */
        boolean todosMuertos = true;
        for(int i = 0; i < enemigos.size(); i++){
            if(enemigos.get(i).getEstadisticas().getHpActual() > 0){ //si hay enemigos vivos entonces tdaovia no ha ganado y no se aplican las recompensas
                todosMuertos = false;
            }
        }
        if(todosMuertos){
            //logica para entrega de recompensas
            System.out.println(" >>> COMBATE COMPLETADO <<<\n");
            for(int i = 0; i < enemigos.size(); i++){ //por cada enemigo entrega recompensas
                int nivelAntes = cloud.getNivel();
                enemigos.get(i).giveXpRecompensa(cloud);
                if(cloud.getNivel() > nivelAntes){
                    System.out.println("¡Cloud subió de nivel " + cloud.getNivel() + "!");
                }
                if(enemigos.get(i) instanceof EnemigoSalvaje){ //si el enemigo es salvaje entonces entregara chatarra
                    ((EnemigoSalvaje) enemigos.get(i)).giveChatarraRecompensa(cloud);
                    System.out.println(">> Obtuviste " + enemigos.get(i).getChatarraRecompensa() + " de chatarra!");
                }
            }
        }
        return todosMuertos;
    }

    public boolean iniciarBatalla(boolean puedeHuir, boolean esSimulador){
        /*       Descripcion: 
        *            metodo para aplicar la logica de la batalla
        *
        *    Parametros:
        *            dos boleanos, puedeHuir permite ver si cloud puede huir o no (sephiroth no lo permite) y esSimulador ve si la batalla es de simulacion o no
        *    
        *    Retorno:
        *            Un booleano que devuelve si se gano el combate o no
        */

        System.out.println("--- Aparecieron enemigos: ---\n");
        for(int i = 0; i < enemigos.size(); i++){
            //muestra todos los enemigos y sus datos
            if(enemigos.get(i).getEstadisticas().getHpActual() > 0){
                System.out.println(enemigos.get(i).nombre + " | HP: " + enemigos.get(i).getEstadisticas().getHpActual() + "\n");
            }
        }

        boolean combateActivo = true;
        int hpMinimo = esSimulador ? 1 : 0; //si es simulador entonces, el hp minimo va a ser 1, si no 0
        while(combateActivo && cloud.getStats().getHpActual() > hpMinimo){
            //logica combate:
            System.out.println("======================================================\n");
            System.out.println("--- CLOUD ESTADISTICAS ---\n");
            System.out.println("HP: " + cloud.getStats().getHpActual() + "/" + cloud.getStats().getHpMax() + "| MP: " + cloud.getStats().getMpActual() + "/" + cloud.getStats().getMpMax() + "\n"); ;
            System.out.println("XP: "+ cloud.getXpActual() + " | MATERIAS EQUIPADAS:" + cloud.getBusterSword().getMaterias().size() + "/5");
            System.out.println("BARRA LIMITE: " + cloud.getLimiteActual() + "/100 \n");
            System.out.println("======================================================\n");

            System.out.println("--- TU TURNO --- \n");
            System.out.println("1. Ataque fisico\n");
            System.out.println("2. Ataque mágico (Requiere MP)\n");
            System.out.println("3. Ataque cargado\n");
            System.out.println("4. Huir\n");
            System.out.println("Eleccion: \n");
            
            int opcion;
            //para evitar que explote si uno pone otra opcion no valida
            try{
                opcion = scanner.nextInt();
            }catch(Exception e){
                System.out.println("Opción inválida, intenta de nuevo");
                scanner.nextLine();
                continue;
            }
            
            if(opcion == 1){
                //logica daño fisico
                System.out.println(">> ¿A quién deseas atacar? (Responda con el numero correspondiente) <<");
                for(int i = 0; i < enemigos.size(); i++){
                    if(enemigos.get(i).getEstadisticas().getHpActual() > 0){
                        System.out.println((i+1) + ". " + enemigos.get(i).nombre + " | HP: " + enemigos.get(i).getEstadisticas().getHpActual());
                    }
                }

                //para evitar que explote si se pone el numero equivocado (se aplicaron 3 posibles casos, algo que no sea numero, fuera del rango de los objetivos y uno que este vivo)
                int objetivo = -1;
                try{
                    objetivo = scanner.nextInt() - 1;
                }catch(Exception e){
                    System.out.println(">> Opción inválida, intenta de nuevo\n");
                    scanner.nextLine();
                    continue;
                }
                if(objetivo < 0 || objetivo >= enemigos.size()){
                    System.out.println(">> Opción inválida, intenta de nuevo\n");
                    continue;
                }
                
                if(enemigos.get(objetivo).getEstadisticas().getHpActual() <= 0){
                    System.out.println(">> Ese enemigo ya está derrotado, elige otro\n");
                    continue;
                }

                Enemigo enemigo = enemigos.get(objetivo);
                int daño = cloud.getBusterSword().calcularDanoFisico(); //calculo del daño fisico
                enemigo.getEstadisticas().recibirDMG(daño);
                cloud.cargarLimite(daño / 5); 
                System.out.println("¡Cloud atacó con su Buster Sword\n Inflinges " + daño + " de daño a " + enemigos.get(objetivo).nombre);
                
                if(enemigos.get(objetivo).getEstadisticas().getHpActual() <= 0){
                    System.out.println("Has derrotado a " + enemigos.get(objetivo).nombre + "\n");
                }

                combateActivo = !verificarMuertos(enemigos, cloud); //si siguien vivos, entonces sigue la batalla
                if(combateActivo){
                    turnoEnemigo(enemigos, cloud, rand);
                    if(enemigo instanceof Sephiroth){
                        System.out.println("-- CONTADOR SUPER NOVA: " + ((Sephiroth) enemigo).getContadorSuperNova() + "/10\n"); // para que aparezca en la pantalla cuando le falta a sephiroth para que hace su ataque
                    }
                }
            }
            
            else if(opcion == 2){
                //logica del ataque magico
                if(cloud.getBusterSword().getMaterias().size() >= 1 && cloud.getStats().getMpActual() >= 10 + (5 * cloud.getBusterSword().getMaterias().size())){
                    System.out.println(">> ¿Qué elemento deseas usarás? ");
                    List<Materia> materias = cloud.getBusterSword().getMaterias();

                    for(int i = 0; i < materias.size(); i++){
                        System.out.println((i+1) + ". " + materias.get(i).getElemento());
                    }

                    //evitar que eliga la eleccion incorrecta mismos casos como antes del objetivo
                    int eleccion = -1;
                    try{
                        eleccion = scanner.nextInt() - 1;
                    }catch(Exception e){
                        System.out.println(">> Opción inválida, intenta de nuevo\n");
                        scanner.nextLine();
                        continue;
                    }
                    if(eleccion < 0 || eleccion >= materias.size()){
                        System.out.println(">> Opción inválida, intenta de nuevo\n");
                        continue;
                    }

                    Elemento elemento = materias.get(eleccion).getElemento();
                    int daño = cloud.getBusterSword().calcularDanoMagico(elemento);

                    if(elemento == Elemento.CURA){
                        //si es cura, se cura así mismo y pasa el turno de los enemigos
                        cloud.getStats().setHpActual(cloud.getStats().getHpActual() + daño);
                        System.out.println("¡Cloud se curó " + daño + " HP!\n");
                        turnoEnemigo(enemigos, cloud, rand);
                    }

                    else{
                        //si no, elige a quien atacar
                        System.out.println(">> ¿A quién deseas atacar? (Responda con el numero correspondiente)");
                        for(int i = 0; i < enemigos.size(); i++){
                            if(enemigos.get(i).getEstadisticas().getHpActual() > 0){
                                System.out.println((i+1) + ". " + enemigos.get(i).nombre + " | HP: " + enemigos.get(i).getEstadisticas().getHpActual());
                            }
                        }

                        int objetivo = -1;
                        try{
                            objetivo = scanner.nextInt() - 1;
                        }catch(Exception e){
                            System.out.println(">> Opción inválida, intenta de nuevo\n");
                            scanner.nextLine();
                            continue;
                        }
                        if(objetivo < 0 || objetivo >= enemigos.size()){
                            System.out.println(">> Opción inválida, intenta de nuevo\n");;
                            continue;
                        }
                        if(enemigos.get(objetivo).getEstadisticas().getHpActual() <= 0){
                            System.out.println(">> Ese enemigo ya está derrotado, elige otro\n");
                            continue;
                        }
                        Enemigo enemigo = enemigos.get(objetivo);

                        double multiplicador = 1.0; //dependiendo del enemigo sube o baja
                        if(enemigo instanceof Vulnerable){
                            multiplicador = ((Vulnerable) enemigo).evaluarDebilidad(elemento); 
                        }

                        int danoFinal = (int)(daño * multiplicador);
                        enemigo.getEstadisticas().recibirDMG(danoFinal);
                        cloud.cargarLimite(daño / 5);
                        //en la pantalla saldra la cantidad que le hizo daño al enemigo, por si no es "coherente" con los datos normales de Cloud
                        System.out.println("¡Cloud atacó con su Buster Sword\n Inflinges " + danoFinal + " de daño a " + enemigos.get(objetivo).nombre);
                        
                        if(enemigos.get(objetivo).getEstadisticas().getHpActual() <= 0){
                            System.out.println("Has derrotado a " + enemigos.get(objetivo).nombre + "\n");
                        }

                        combateActivo = !verificarMuertos(enemigos, cloud);
                        if(combateActivo){
                            turnoEnemigo(enemigos, cloud, rand);
                        }
                    }
                }
                else if(cloud.getStats().getMpActual() < 10 + (5 * cloud.getBusterSword().getMaterias().size())){
                        System.out.println(">> No tienes MP suficiente <<\n");   
                }
                else{
                    System.out.println(">> No tienes materias equipas <<\n");
                }
            }
            
            else if(opcion == 3){
                if(cloud.getLimiteActual() == 100){
                    
                    System.out.println(">> ¿A quién deseas atacar? (Responda con el numero correspondiente)");
                    for(int i = 0; i < enemigos.size(); i++){
                        if(enemigos.get(i).getEstadisticas().getHpActual() > 0){
                            System.out.println((i+1) + ". " + enemigos.get(i).nombre + " | HP: " + enemigos.get(i).getEstadisticas().getHpActual());
                        }
                    }
                    int objetivo = -1;
                    try{
                        objetivo = scanner.nextInt() - 1;
                    }catch(Exception e){
                        System.out.println(">> Opción inválida, intenta de nuevo\n");
                        scanner.nextLine();
                        continue;
                    }
                    if(objetivo < 0 || objetivo >= enemigos.size()){
                        System.out.println(">> Opción inválida, intenta de nuevo\n");
                        continue;
                    }
                    if(enemigos.get(objetivo).getEstadisticas().getHpActual() <= 0){
                        System.out.println(">> Ese enemigo ya está derrotado, elige otro\n");
                        continue;
                    }

                    int daño = cloud.getBusterSword().calcularDanoLimite();
                    Enemigo enemigo = enemigos.get(objetivo);
                    enemigo.getEstadisticas().recibirDMG(daño);
                    
                    System.out.println("¡Cloud atacó con su Buster Sword\n Inflinges " + daño + " de daño a " + enemigos.get(objetivo).nombre);
                    cloud.setLimiteActual(0);

                    if(enemigo instanceof Sephiroth){
                        ((Sephiroth) enemigo).resetContador(); //resetea el contador de la super nova de sephiroth
                    }

                    if(enemigos.get(objetivo).getEstadisticas().getHpActual() <= 0){
                        System.out.println("Has derrotado a " + enemigos.get(objetivo).nombre + "\n");
                    }
                    combateActivo = !verificarMuertos(enemigos, cloud);
                    if(combateActivo){
                        turnoEnemigo(enemigos, cloud, rand);
                    }
                }
                else{
                    System.out.println("La barra límite no está cargada");
                }
            }
            else if(opcion == 4 && puedeHuir){
                //50/50 de poder huir
                if(rand.nextInt(100) + 1 > 50){
                    System.out.println("¡Cloud logró escapar!\n");
                    combateActivo = false;
                }
                else{
                    System.out.println("Cloud no logró escapar\n");
                    combateActivo = !verificarMuertos(enemigos, cloud);
                    if(combateActivo){
                        turnoEnemigo(enemigos, cloud, rand);
                    }
                } 
            }
            else if(opcion == 4 && !puedeHuir){
                System.out.println("¡No puedes huir!\n");
            }
        }
        boolean cloudGano = true;
        //rip Cloud, se aplica penalizacion 
        if(cloud.getStats().getHpActual() <= 0){
            System.out.println("Cloud ha sido derrotado...\n");
            System.out.println(">> Has perdido toda tu chatarra y materias <<\n");
            cloud.getStats().setHpActual(cloud.getStats().getHpMax());
            cloud.penalizacion();
            cloudGano = false;
        }
        return cloudGano; //retorna si cloud gano o no.
    }

}
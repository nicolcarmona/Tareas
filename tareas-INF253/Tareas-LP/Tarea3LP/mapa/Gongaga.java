package mapa;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;

import entidades.*;
import componentes.*;

public class Gongaga extends Zona{
    private List<Materia> poolMaterias;

    public Gongaga(){
        /*       Descripcion: 
        *            constructor que inicializa los valores de Gongaga
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        super("Gongaga", 5, new ArrayList<>());
        poolMaterias = new ArrayList<>();
        enemigosDisponibles.add(new EnemigoSalvaje("Planta Carnívora", 80, 15, Arrays.asList(Elemento.FUEGO, Elemento.HIELO), new ArrayList<>(), Arrays.asList(Elemento.RAYO)));
        enemigosDisponibles.add(new EnemigoSalvaje("Sapo de la Jungla", 60, 12, Arrays.asList(Elemento.RAYO, Elemento.HIELO), Arrays.asList(Elemento.FUEGO), new ArrayList<>()));
        enemigosDisponibles.add(new EnemigoSalvaje("Robot Centinela", 100, 20, Arrays.asList(Elemento.RAYO), Arrays.asList(Elemento.FISICO, Elemento.HIELO), new ArrayList<>()));
    }

    public EnemigoSalvaje crearEnemigo(int enemigoElegido){
        /*       Descripcion: 
        *            metodo extra que crea instancias de los enemigos
        *
        *    Parametros:
        *            un entero que sera que enemigo se eligio de forma al azar
        *    
        *    Retorno:
        *            reotrna EnemigoSalvaje
        */
        if(enemigoElegido == 0){
            return new EnemigoSalvaje("Planta Carnívora", 80, 15, 
                Arrays.asList(Elemento.FUEGO, Elemento.HIELO), 
                new ArrayList<>(), 
                Arrays.asList(Elemento.RAYO));
        }
        else if(enemigoElegido == 1){
            return new EnemigoSalvaje("Sapo de la Jungla", 60, 12, 
                Arrays.asList(Elemento.RAYO, Elemento.HIELO), 
                Arrays.asList(Elemento.FUEGO), 
                new ArrayList<>());
        }
        else{
            return new EnemigoSalvaje("Robot Centinela", 100, 20, 
                Arrays.asList(Elemento.RAYO), 
                Arrays.asList(Elemento.FISICO, Elemento.HIELO), 
                new ArrayList<>());
        }
    }

    public List<Enemigo> generarGrupoEnemigo(){
        /*       Descripcion: 
        *            Metodo que genera grupos de enemigos (emboscada)
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            retorna una lista de enemigos
        */
        Random rand = new Random();
        int probabilidadAparicion = rand.nextInt(100) + 1;
        List<Enemigo> grupoEnemigos = new ArrayList<>();

        if(probabilidadAparicion <= 60){
            grupoEnemigos.add(crearEnemigo(rand.nextInt(3))); //solo se crea 1
        }
        else if(probabilidadAparicion <= 90){ //Se crean 2
            grupoEnemigos.add(crearEnemigo(rand.nextInt(3)));
            grupoEnemigos.add(crearEnemigo(rand.nextInt(3)));
        }
        else{ //se crean 3
            grupoEnemigos.add(crearEnemigo(rand.nextInt(3)));;
            grupoEnemigos.add(crearEnemigo(rand.nextInt(3)));;
            grupoEnemigos.add(crearEnemigo(rand.nextInt(3)));;
        }
        return grupoEnemigos;
    }

    public void accionZona(Jugador cloud, Scanner scanner){
        /*       Descripcion: 
        *            metodo que entrega la accion de la zona, puede sufrir una enboscada o puede encontrar una materia
        *
        *    Parametros:
        *            dos objetos uno cloud tipo jugador y otro Scanner para obtener lo que el jugador podra en pantalla
        *    
        *    Retorno:
        *            no tiene
        */
        System.out.println("======================================================\n");
            System.out.println("ZONA: Gongaga | NIVEL:" + cloud.getNivel()+ "\n");
            System.out.println("HP: " + cloud.getStats().getHpActual() + "/" + cloud.getStats().getHpMax() + "| MP: " + cloud.getStats().getMpActual() + "/" + cloud.getStats().getMpMax() + "\n"); ;
            System.out.println("XP: "+ cloud.getXpActual() + " | MATERIAS EQUIPADAS:" + cloud.getBusterSword().getMaterias().size() + "/5");
            System.out.println("BARRA LIMITE: " + cloud.getLimiteActual() + "/100 \n");
            System.out.println("======================================================\n");
    

        Random rand = new Random();
        Elemento[] elementos = {Elemento.FUEGO, Elemento.HIELO, Elemento.RAYO, Elemento.CURA};

        int probabilidadEmboscada = rand.nextInt(100) + 1;
        
        if(probabilidadEmboscada <= 70){
            System.out.println("==============================================\n");
            System.out.println(">>> INICIANDO COMBATE <<<");
            new Combate(cloud, generarGrupoEnemigo()).iniciarBatalla(true, false);
        }
        else{
            Elemento elementoAleatorio = elementos[rand.nextInt(4)];
            System.out.println("==============================================\n");
            System.out.println(">>> HAZ ENCONTRADO MATERIA " + elementoAleatorio + "<<<\n");
            Materia materias = new Materia("Materia " + elementoAleatorio, elementoAleatorio); //crea la instancia de la materia para agregarla a la mochilaw
            poolMaterias.add(materias);
            cloud.agregarMateriaMochila(materias);
        }
    }
}
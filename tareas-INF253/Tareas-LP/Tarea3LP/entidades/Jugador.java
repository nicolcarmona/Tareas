package entidades;
import java.util.List;
import java.util.ArrayList;

import componentes.Estadisticas;
import componentes.Materia;
import componentes.Elemento;


public class Jugador{
    public String nombre;
    private int nivel;
    private int xpActual;
    private int chatarra;
    private int limiteActual;
    private Estadisticas stats;
    private List<Materia> mochila;
    private Arma busterSword;
    private boolean fueDerrotado; //atributo extra


    public Jugador(){
        /*       Descripcion: 
        *            constructor que inicializa los datos del Jugador
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        nivel = 1;
        xpActual = 0;
        chatarra = 0;
        limiteActual = 0;
        stats = new Estadisticas();
        mochila = new ArrayList<>();
        busterSword = new Arma();
        fueDerrotado = false;
    }

    //Estos dos metodos son extras para devolver el atributo extra 
    public boolean getFueDerrotado(){
        return fueDerrotado;
    }

    public void setFueDerrotado(boolean valor){
        fueDerrotado = valor;
    }

    public void recibirXP(int xp){
        /*       Descripcion: 
        *            metodo de la logica de la experiencia que recibe cloud
        *
        *    Parametros:
        *            Un entero xp con la experiencia
        *    
        *    Retorno:
        *            no tiene
        */
        xpActual = xpActual + xp;
        while(xpActual >= 10 * nivel){
            xpActual = xpActual - (10 * nivel);
            nivel++;
            //aumenta los stats por cada nivel subido
            stats.setHpMax(stats.getHpMax() + 10);
            stats.setMpMax(stats.getMpMax() + 5);
            stats.setFuerza(stats.getFuerza() + 4);
            stats.setMagia(stats.getMagia() + 6);
        }
    }

    public void cargarLimite(int valor){
        /*       Descripcion: 
        *            metodo que carga el limite de la barra. 
        *
        *    Parametros:
        *            un entero valor (el limite)
        *    
        *    Retorno:
        *            no tiene
        */
        limiteActual += valor;
        if(limiteActual > 100){
            limiteActual = 100;
        }

    }

    public void recibirDMG(int daño){
        /*       Descripcion: 
        *            Un metodo del daño que recibe CLoud
        *
        *    Parametros:
        *            un entero daño, que es el daño que hacen los enemigos
        *    
        *    Retorno:
        *            no tiene
        */
        stats.recibirDMG(daño);
        cargarLimite(daño / 2); //carga el limite con la condicion.

    }

    public Estadisticas getStats(){
        return stats;
    }

    public int getNivel(){
        return nivel;
    }
    
    public int getChatarra(){
        return chatarra;
    }

    public int getLimiteActual(){
        return limiteActual;
    }

    public List<Materia> getMochila(){
        return mochila;
    }

    public int getXpActual(){
        return xpActual;
    }

    public void setChatarra(int valor){
        this.chatarra = valor;
    }

    public void setLimiteActual(int valor){
        this.limiteActual = valor;
    }

    public void agregarMateriaMochila(Materia materia){
        /*       Descripcion: 
        *            un metodo que sirve para agregar materias a la mochila
        *
        *    Parametros:
        *            un objeto materia de tipo Materia, que se la materia que se guardara (mucha redundancia)
        *    
        *    Retorno:
        *            no tiene
        */
        mochila.add(materia);
    }

    public void penalizacion(){
        /*       Descripcion: 
        *            metodo de la penalizacion que pasa cuando cloud se muere
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        mochila.clear();
        chatarra = 0;
        fueDerrotado = true; //para que pueda volver al sector 7
    }

    public class Arma{
        public String nombre;
        private List<Materia> materiasEquipadas;

        public Arma(){
            /*       Descripcion: 
        *            constructor que inicializa los datos del arma
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
            this.nombre = "Buster Sword";
            materiasEquipadas = new ArrayList<>();
        }

        public List<Materia> getMaterias(){
            return materiasEquipadas;
        }

        public int calcularDanoMagico(Elemento elemento){
        /*       Descripcion: 
        *            Metodo de la logica que calcula el daño magico
        *
        *    Parametros:
        *            objeto elemento del tipo Elemento, es el elemento que elige el jugador para aplicar el daño
        *    
        *    Retorno:
        *            un entero que sera el daño que hace
        */
            int contadorMaterias = 0;
            for (int i = 0; i < materiasEquipadas.size(); i++){
                if (materiasEquipadas.get(i).getElemento() == elemento){ //calculamos las materias
                    contadorMaterias++;
                }
            }
            int danoMagico = (int)(stats.getMagia() * (1.0 + (0.5 * contadorMaterias))); //calculamos el daño
            int costoMp = 10 + (5 * contadorMaterias); //cantidad de mp que cuesta aplicar el daño magico
            stats.setMpActual(stats.getMpActual() - costoMp); //cambiamos el valor del mp actual

            return danoMagico;
        }

        public int calcularDanoFisico(){
        /*       Descripcion: 
        *            Metodo de la logica que calcula el daño fisico
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            un entero que sera el daño que hace
        */
            int danoFisico = (int)(stats.getFuerza() * 1.25);
            return danoFisico;
        }

        public int calcularDanoLimite(){
        /*       Descripcion: 
        *            Metodo de la logica que calcula el daño limite
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            un entero que sera el daño que hace
        */
            int danoLimite = stats.getFuerza() * 5;
            return danoLimite;
        }

        public void equiparMateria(Materia materia){
        /*       Descripcion: 
        *            Metodo para equipar la materia en el arma
        *
        *    Parametros:
        *            objeto elemento del tipo Elemento, es el elemento que elige el jugador para aplicar el daño
        *    
        *    Retorno:
        *            un entero que sera el daño que hace
        */
            if (materiasEquipadas.size() < 5) {
                materiasEquipadas.add(materia); //agregamos a la materia
                mochila.remove(materia); //la quitamos de la mochila
            }
            else{
                System.out.println(">> Todas las ranuras han sido ocupadas.");
            }
        }
    }

    public Arma getBusterSword(){
        return busterSword;
    }

}
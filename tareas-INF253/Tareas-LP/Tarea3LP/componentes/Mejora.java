package componentes;

public class Mejora{
    private String nombre;
    private int costoChatarra;
    private TipoStat statAfectado;
    private int valorBono;

    public String getNombre(){
        return this.nombre;
    }
    public int getCostoChatarra(){
        return this.costoChatarra;
    }
    public TipoStat getStatAfectado(){
        return this.statAfectado;
    }
    public int getValorBono(){
        return this.valorBono;
    }

    public Mejora(String nombre, int costoChatarra, TipoStat statAfectado, int valorBono){
        /*       Descripcion: 
        *            constructor que inicializa los datos de la mejora
        *
        *    Parametros:
        *            un String nombre, un entero con el costo de la chatarra, stat afectado de tipo tipostat es a que le afectara la mejora, un entero valorbono que es el valor de la bonificacion (cuanto mejora) 
        *    
        *    Retorno:
        *            no tiene
        */
        this.nombre = nombre;
        this.costoChatarra = costoChatarra;
        this.statAfectado = statAfectado;
        this.valorBono = valorBono;
    }

}

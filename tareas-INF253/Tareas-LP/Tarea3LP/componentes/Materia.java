package componentes;

public class Materia{
    private String nombre;
    private Elemento elemento;
    
    public String getNombre(){
        return nombre;
    }
    public void setNombre(String valor) {
        nombre = valor;
    }

    public Elemento getElemento(){
        return elemento;
    }
    public void setElemento(Elemento valor){
        elemento = valor;
    }
    public Materia(String nombre, Elemento elemento){
        /*       Descripcion: 
        *            constructor que inicializa los valores de materia
        *
        *    Parametros:
        *            Un string nombre y un elemento de tipo Elemento.
        *    
        *    Retorno:
        *            no tiene
        */
        this.nombre = nombre;
        this.elemento = elemento;
    }
}
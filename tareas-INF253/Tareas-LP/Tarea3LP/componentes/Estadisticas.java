package componentes;

public class Estadisticas{
    private int hpActual;
    private int hpMaximo;
    private int mpActual;
    private int mpMaximo;
    private int fuerza;
    private int magia;
    
    public Estadisticas(){
        /*       Descripcion: 
        *            constructor que inicializa los datos de clo
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        hpMaximo = 200;
        mpMaximo = 50;
        fuerza = 15;
        magia = 15;
        hpActual = hpMaximo;
        mpActual = mpMaximo;
    }
   
    public Estadisticas(int hpMaximo, int fuerza) {
        /*       Descripcion: 
        *            constructor que inicializa los datos del enemigo
        *
        *    Parametros:
        *            no tiene
        *    
        *    Retorno:
        *            no tiene
        */
        this.hpMaximo = hpMaximo;
        this.hpActual = hpMaximo;
        this.fuerza = fuerza;
        this.mpMaximo = 0;
        this.mpActual = 0;
        this.magia = 0;
    }

    public int getHpMax(){
        return hpMaximo;
    }
    public int getHpActual(){
        return hpActual;
    }
    public void setHpMax(int valor) {
        hpMaximo = valor;
    }
    public void setHpActual(int valor) {
        if(valor > hpMaximo){
            hpActual = hpMaximo;
        }
        else{
            hpActual = valor;
        }
    }

    public int getMpMax(){
        return mpMaximo;
    }
    public int getMpActual(){
        return mpActual;
    }
    public void setMpMax(int valor) {
        mpMaximo = valor;
    }
    public void setMpActual(int valor) {
        if(valor > mpMaximo){
            mpActual = mpMaximo;
        }
        else{
            mpActual = valor;
        }
    }

    public int getFuerza(){
        return fuerza;
    }
    public void setFuerza(int valor) {
        fuerza = valor;
    }

    public int getMagia(){
        return magia;
    }
    public void setMagia(int valor) {
        magia = valor;
    }

    public void recibirDMG(int valor){
        /*       Descripcion: 
        *            metodo para calcular el daño recibido en Cloud y en enemigos
        *
        *    Parametros:
        *            Un entero valor, este toma valores de daños
        *    
        *    Retorno:
        *            metodo tipo void, no retorna
        */
        if (valor >= hpActual){
            hpActual = 0;
        }
        else{
            hpActual = hpActual - valor;
        }
    }
}

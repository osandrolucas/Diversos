package br.edu.ifrs.progweb1.util;

public class CD{
    
    private String titulo;
    private int ano;
    private boolean coletanea;
    private String artista;
    private String geneto;

    @Override
    public String toString(){
        return null;
    };    

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public boolean isColetanea() {
        return coletanea;
    }

    public void setColetanea(boolean coletanea) {
        this.coletanea = coletanea;
    }

    public String getArtista() {
        return artista;
    }

    public void setArtista(String artista) {
        this.artista = artista;
    }

    public String getGeneto() {
        return geneto;
    }

    public void setGeneto(String geneto) {
        this.geneto = geneto;
    }
    
    
}

package br.edu.ifrs.progweb1.util;

public class MinhaPilha implements Pilha {

    @Override
    public void inserir(Object obj) {
        pilha.add(obj);
    }

    @Override
    public int totalizar() {
        return 0;
    }

    @Override
    public void limpar() {
        
    }

    @Override
    public void ordenar() {
        
    }

    @Override
    public Object remover(Object obj) {
        pilha.remove(obj);
        return null;
    }

}

package br.edu.ifrs.progweb1.util;

import java.util.*;

public interface Pilha {

    //1.1 A pilha irá conter elementos
    public LinkedList<Object> Pilha = new LinkedList<>();

    //1.3 Defina os métodos abaixo usando genéricos onde for possível:
    public void inserir();

    public void remover();

    public int totalizar();

    public void limpar();

    public void ordenar();

    @Override
    public String toString();

}

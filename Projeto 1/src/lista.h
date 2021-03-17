#include "bibliotecas.h"
#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

    /*
    createList na dinamica, ira retornar uma lista vazia, com os outros dados internos da lista setados para o funcionamento do codigo
    createList na estatica, ira retornar uma lista vazia, com os outros dados internos da lista setados para o funcionamento do codigo com o espaco passado no nx do geo inicial
    */
    lista createList(int tamanho);

    //getSize retorna o numero de elementos da lista (length do TAD)
    int getSize(lista sequence);

    //insert insere o item passado no final da lista, o comprimento da lista sera aumentado em 1 e retorna um indicador para o item acrescentado.
    celula insert(lista sequence, item elemento);

    //Desde que a celula passada exista, a funcao removeNode ira remover a celula passada como argumento, diminuindo o tamanho da lista em 1.
    void removeNode(lista sequence, celula current);

    //Desde que a celula passada no argumento exista e possua um void* elemento, getItem ira retornar o valor do item na celula 
    item getItem(lista sequence, celula current);

    //Desde que a celula passada no argumento exista, insere o elemento passado na celula imediatamente anterior a passada no argumento
    celula insertBefore(lista sequence, celula current, item elemento);

    //Desde que a celula passada no argumento exista, insere o elemento passado na celula imediatamente apos a passada no argumento
    celula insertAfter(lista sequence, celula current, item elemento);
    
    //Retorna o endereco da cabeca da lista, desde que a lista possua tamanho > 0, caso contrario, retorna NULL
    celula getHead(lista sequence);

    //Desde que a celula passada no argumento exista, retorna o endereco da proxima celula, caso a celula passada como argumento for a ultima, retorna NULL
    celula getNext(lista sequence, celula current);
    
    //Retorna o endereco da cauda da lista, desde que a lista possua tamanho > 0, caso contrario , retorna NULL
    celula getLast(lista sequence);

    //Desde que a celula passada no argumento exista, retorna o endereco da celula anterior, casa a celula passada for a primeira, retorna NULL
    celula getPrevious(lista sequence, celula current);

    //Libera a lista passada como argumento
    void freeList(lista sequence, int tamanho);
    
    //Retorna o endereco de determinada posicao da lista
    celula atPos(lista sequence, int index);

    //Aumenta visitas 
    void raiseVisitas(lista sequence);

    //Retorna visitas feitas
    long int getVisitas(lista sequence);

    //Retorna o tamanho original
    long int getOriginalSize(lista sequence);
    
#endif
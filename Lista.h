#include "Pilha.h"

#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>


typedef struct _lista{
    int size;
    struct _lista *next;
    struct _carro **head;
}Lista;

Lista* criaLista(int size);
Lista* criaListaGaragem(int qntdPilhas);
Lista* criaPilhaGaragem(int qntdPilha, int vagas);


#endif

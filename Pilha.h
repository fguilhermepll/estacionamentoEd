#ifndef PILHA_H
#define PILHA_H
#include "Lista.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _carro{
    char *placa;
    int chegada;
    struct _carro* nextCarro;
}Carro;

Carro* criaCarro();

void push(Lista* head, Carro* carro, int i);
void pop(Carro* stack);
#endif

#include "Pilha.h"

Carro* criaCarro(){

    Carro* novoStack = (Carro*) malloc (sizeof(Carro));

    novoStack->nextCarro = NULL;
    novoStack->placa = "v";
    novoStack->chegada = -1;

    return novoStack;
}

// Recebe um CARRO, e o seta como "v", flag para NULO.
void pop(Carro* stack){
    stack->placa = "v";
    stack->chegada = -1;
    stack = stack->nextCarro;
}

void push(Lista* head, Carro* carro, int i){
    Carro* aux = head->head[i];
    while(strcmp(aux->placa, "v") == 0 && aux != NULL){ //Vai para o ultimo elemento da stack
        if(aux->nextCarro == NULL || strcmp(aux->nextCarro->placa, "v")){
            aux->placa = carro->placa;
            aux->chegada = carro->chegada;
            break;
        }
        aux = aux->nextCarro;
    }
}

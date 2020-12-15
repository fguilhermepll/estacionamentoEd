#include "Lista.h"

Lista* criaLista(int size){
    Lista* novaLista = (Lista*) malloc(sizeof(Lista));
    novaLista->size = size;
    novaLista->head = (Carro**) malloc(sizeof(Carro*) * size);
    novaLista->next = NULL;
    return novaLista;
}

Lista* criaListaGaragem(int qntdPilhas){
    Lista* lista = criaLista(qntdPilhas); // quantas heads vao ser armazenadas
    lista->size = 3;
    return lista;
}

Lista* criaPilhaGaragem(int qntdPilha, int vagas){
    Carro* pilha = NULL;
    Carro* auxNode = NULL;
    Lista* list = criaLista(qntdPilha);
    for(int i = 0; i < qntdPilha; i++){  // fazer "i" pilhas, apenas as heads para serem armazenadas em Lista
        pilha = criaCarro();
        list->head[i] = pilha;
    }
    for(int j = 0; j < qntdPilha; j++){
        for(int i = 0; i < vagas - 1; i++){
            if(i <= 0){
                Carro* novoNode = criaCarro();
                novoNode->chegada = i;
                list->head[j]->nextCarro = novoNode;
                auxNode = list->head[j]->nextCarro;
            }else{
                auxNode->nextCarro = criaCarro();
                auxNode = auxNode->nextCarro;
                auxNode->chegada = i;
            }
        }
    }
    return list;
}

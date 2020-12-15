#include "Auxliares.h"


//Insere por ordem de chegada, as pilhas vão sendo preenchidas de forma sequencial
//dando preferência para as pilhas mais vazias, até encher todo o estacionamento

void insereCarro(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas){
    int escolha = 0;
    printf("Digite a placa do carro [7 dígitos]:");
    char *aux = (char*) malloc(sizeof(char) * 9);
    fgets(aux, 9, stdin);
    aux[strcspn(aux, "\n")] = 0;
    if(strlen(aux) < 7){
        printf("Por favor, insira uma placa válida [de 7 digitos].\n");
        return;
    }else if(strlen(aux) > 7){
        printf("Por favor, insira uma placa válida [de 7 digitos ou menos].\n");
        return;
    }
    Carro* carro = criaCarro();
    carro->placa = (char*) malloc(sizeof(char) * 9);
    strcpy(carro->placa, aux);

    printf("Seu carro está na rua, deseja inserir na garagem? \n");
    printf("[1]Sim [2]Nao:");
    scanf("%d", &escolha);
    fflush(stdin);
    if(escolha == 2){
        printf("\n");
        return;
    }else if(escolha == 1){
        EnqueueR(rua, carro, rua->size);
        /////////////////////////////////////////////////////////////////////////////
        escolha = simulaInsere(estacionamento, rua, qntdPilhas, vagas);
        /////////////////////////////////////////////////////////////////////////////
        if(escolha > qntdPilhas){
                printf("Você inseriu um comando inválido.1\n");
                DequeueFnoPrint(rua, rua->size);
                return;
        }
        if(escolha == 1){
            int recomenda = recomendaVaga(estacionamento, estacionamento->size);
            push(estacionamento, carro, recomenda);
        }else{
            printf("Em qual pilha deseja inserir? de 1 até %d:\n", qntdPilhas);
            scanf("%d", &escolha);
            fflush(stdin);
            escolha = escolha - 1;
            if(escolha > qntdPilhas){
                printf("Você inseriu uma pilha inexistente.");
                DequeueFnoPrint(rua, rua->size);
                return;
            }
            int numCarrosFila = quantidadeCarroGaragemFila(estacionamento, escolha, aux);
            if(numCarrosFila >= vagas){
                printf("Você nao pode estacionar nessa pilha, está lotada.\n");
                DequeueFnoPrint(rua, rua->size);
                free(aux);
                return;
            }
            push(estacionamento, carro, escolha);
        }
    }else{
        printf("\nVocê inseriu um comando inválido.2\n");
        DequeueFnoPrint(rua, rua->size);
        return;
    }
    DequeueFnoPrint(rua, rua->size);
    free(aux);
}


//Remove um carro de acordo com a placa indicada
//caso tenha algum carro no caminho, esse carro vai para a rua e assim por diante
void removeCarro(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas){
    int qntddCarro = quantidadeCarroGaragem(estacionamento);
    if(qntddCarro == 0){
        printf("Garagem vazia, voce nao pode remover nenhum carro.\n");
        return;
    }

    int decida = 0;
    //Acha em qual pilha da lista está o carro
    printf("Insira a placa do carro que deseja remover: ");
    char *aux = (char*) malloc (sizeof(char)*9);
    fgets(aux, 9, stdin);
    aux[strcspn(aux, "\n")] = 0;
    //////////////////////////////////////////////
    simulaRemocao(estacionamento, rua, qntdPilhas, vagas, aux);
    //////////////////////////////////////////////
    printf("Deseja efetivar a retirada carro? [1]Sim [2]Nao: ");
    scanf("%d", &decida);
    fflush(stdin);

    if(decida == 1){
        Carro* carro = criaCarro();

        int vagaIndice = procuraCarroPlaca(&estacionamento, aux);
        int carros = quantidadeCarroGaragemFila(estacionamento, vagaIndice, aux);

        Carro* cAux = estacionamento->head[vagaIndice];

        for(int i = 0; i < carros; i++){
            while(strcmp(cAux->placa, "v") == 0)
                cAux = cAux->nextCarro;
            Carro* carroHold = criaCarro();
            carroHold->placa = cAux->placa;
            carroHold->chegada = cAux->chegada;
            EnqueueF(rua, carroHold, rua->size);
            pop(cAux);
        }
        carro = DequeueFv2(rua, rua->size);
        for(int i = 0; i < carros - 1; i++){
            push(estacionamento, carro, vagaIndice);
            carro = DequeueFv2noPrint(rua, rua->size);
        }
    }else if(decida == 2){
        return;
    }
}

void imprimeGaragem(Lista* estacionamento){
    int i = 0;
    while(i < estacionamento->size){
        Carro* pAux = estacionamento->head[i];
        printf("\t\t");
        while(pAux != NULL){
            if(!strcmp(pAux->placa, "v")){
                printf("---------------|");
            }else{
                printf("----%s----|", pAux->placa);
            }
            pAux = pAux->nextCarro;
            if(pAux == NULL){
                i++;
                break;
            }
        }
        printf("\n");
    }
}

// Faz um loop pelo estacionamento inteiro e
// decide qual é a pilha com menos carros e
// retorna seu indice
// Função auxiliar.
int recomendaVaga(Lista* lista, int qntdPilhas){
    int i = 0, carros = 0, salvaI = 0, qntdCarros = 0;
    while(i < qntdPilhas){
        Carro* pAux = lista->head[i];
        carros = 0;
        while(pAux != NULL){
            if(!strcmp(pAux->placa, "v")){
                pAux = pAux->nextCarro;
            }else{
                carros++;
                pAux = pAux->nextCarro;
            }
        }
        if(qntdCarros > carros){
            qntdCarros = carros;
            salvaI = i;
        }
        qntdCarros = carros;
        i++;
    }

    return salvaI;
}


// Analisa quantos carros tem na fila até o dado Carro
// Função auxiliar a função de Remoção.
int quantidadeCarroGaragemFila(Lista* estacionamento, int i, char* placa){
    int carros = 0;
    char *placaAux = (char*) malloc (sizeof(char) * 9);
    strcpy(placaAux, placa);
    Carro* auxC = estacionamento->head[i];
        while(auxC != NULL){
            if(strcmp(auxC->placa, "v") != 0 && strcmp(auxC->placa, placaAux) != 0){
                auxC = auxC->nextCarro;
                carros++;
            }else if(strcmp(auxC->placa, "v") != 0 || strcmp(auxC->placa, placaAux) == 0){
                carros++;
                auxC = auxC->nextCarro;
            }else{
                auxC = auxC->nextCarro;
            }
        }
    free(placaAux);
    return carros;
}

// Retorna quantos carros tem no estacionamento
// Função auxiliar.
int quantidadeCarroGaragem(Lista* estacionamento){
    int i = 0, carros = 0;
    int size = estacionamento->size;
    while(i < size){
        Carro* auxC = estacionamento->head[i];
        while(auxC != NULL){
            if(!strcmp(auxC->placa, "v")){
                auxC = auxC->nextCarro;
            }else{
                carros++;
                auxC = auxC->nextCarro;
            }
        }
        i++;
    }
    return carros;
}

// Dada placa, procura pela mesma e retorna o indice da pilha em
// que esse carro está inserido
// Função auxiliar a remoção.
int procuraCarroPlaca(Lista** lista, char *placa){
    char *placaAux = (char*) malloc (sizeof(char) * 9);
    strcpy(placaAux, placa);
    int i = 0, j = 0, carros = 0;
    int size = (*lista)->size;
    while(i < size){
        carros = 0;
        Carro* pAux = (*lista)->head[i];
        while(pAux != NULL){
            if(!strcmp(pAux->placa, placaAux)){
                //printf("Carro encontrado!\n");
                j = i;
                i = size;
                break;
            }else{
                carros++;
                pAux = pAux->nextCarro;
            }
        }
        i++;
    }
    free(placaAux);
    return j;

}

// Simula o Insere para então efetuar caso o usuário deseje
// Função auxiliar a Insere.
int simulaInsere(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas){
    int escolha = 0;

    Lista* estacionamentoCopia = copiaGaragem(estacionamento, qntdPilhas, vagas);
    int recomendaCopia = recomendaVaga(estacionamentoCopia, estacionamentoCopia->size);

    Carro* carroCopia = criaCarro();
    carroCopia->placa = "-AQUI--";

    push(estacionamentoCopia, carroCopia, recomendaCopia);
    printf("Deseja inserir seu carro na vaga recomendada? (no lugar do \"AQUI\")");
    printf("\n");
    imprimeGaragem(estacionamentoCopia);

    printa(rua, rua->size);
    printf("\n[1]:Sim [2]:Nao\n");
    scanf("%d", &escolha);
    fflush(stdin);
    printf("\n");
    free(carroCopia);
    freeEstacionamento(estacionamentoCopia, qntdPilhas, vagas);
    return escolha;
}

// Simula remoção para então efetivar, caso o usuário deseje.
// Função auxiliar a Remoção.
void simulaRemocao(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas, char* aux){
    aux = (char*) malloc (sizeof(char) * 9);
    int decida = 0;
    //////////////////////////////////////////////
    printf("Demonstrando sequencia: \n");
    printf("Digite [1] e pressione ENTER para continuar.\n");
    scanf("%d", &decida);

    if(decida == 1){
        Lista* estacionamentoCopia = copiaGaragem(estacionamento, qntdPilhas, vagas);
        Carro* carro = criaCarro();

        int vagaIndice = procuraCarroPlaca(&estacionamentoCopia, aux);
        int carros = quantidadeCarroGaragemFila(estacionamentoCopia, vagaIndice, aux);
        Carro* cAux = estacionamentoCopia->head[vagaIndice];

        printf("Manobrando todos os carros da pilha em que se encontra seu carro:\n");
        imprimeGaragem(estacionamentoCopia);
        printa(rua, rua->size);
        for(int i = 0; i < carros; i++){
            printf("Proxima tela? [1]Sim");
            scanf("%d", &decida);
            fflush(stdin);
            //system("cls");
            while(strcmp(cAux->placa, "v") == 0)
                cAux = cAux->nextCarro;

            Carro* carroHold = criaCarro();
            carroHold->placa = cAux->placa;
            carroHold->chegada = cAux->chegada;
            EnqueueF(rua, carroHold, rua->size);
            pop(cAux);
            imprimeGaragem(estacionamentoCopia);
            printa(rua, rua->size);
        }
        carro = DequeueFv2(rua, rua->size);
        for(int i = 0; i < carros - 1; i++){
            printf("Proxima tela? [1]Sim");
            scanf("%d", &decida);
            fflush(stdin);
            //system("cls");
            imprimeGaragem(estacionamentoCopia);
            printa(rua, rua->size);

            printf("Proxima tela? [1]Sim");
            scanf("%d", &decida);
            fflush(stdin);

            push(estacionamentoCopia, carro, vagaIndice);
            imprimeGaragem(estacionamentoCopia);
            carro = DequeueFv2(rua, rua->size);
            printa(rua, rua->size);
        }
        freeEstacionamento(estacionamentoCopia, qntdPilhas, vagas);
    }
    //////////////////////////////////////////
    free(aux);
}

void freeEstacionamento(Lista* estacionamento, int qntdPilhas, int vagas){
    int i = 0;
    Carro* cAux;
    while(i < qntdPilhas){
        while(estacionamento->head[i] != NULL){
            cAux = estacionamento->head[i];
            estacionamento->head[i] = estacionamento->head[i]->nextCarro;
            free(cAux);
        }
        i++;
    }

    free(estacionamento);
}
// Faz uma cópia de um estacionamento/garagem
// Função auxiliar.
Lista* copiaGaragem(Lista* estacionamento, int qntdPilhas, int vagas){
    Lista* estacionamentoCopia = criaPilhaGaragem(qntdPilhas, vagas);
    int i = 0;
    estacionamentoCopia->size = estacionamento->size;
    while(i < qntdPilhas){
        Carro* pCar = estacionamento->head[i];
        Carro* pCar2 = estacionamentoCopia->head[i];
        while(pCar != NULL){
            pCar2->placa = pCar->placa;
            pCar2 = pCar2->nextCarro;
            pCar = pCar->nextCarro;
        }
        i++;
    }

    return estacionamentoCopia;

}

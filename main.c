#include <locale.h>
#include "deque.h"
#include "Lista.h"
#include "Auxliares.h"
/*
->=============COMENTÁRIOS EXPLICANDO O TRABALHO E DOCUMENTAÇÃO===========<-

deque.h/c:
    Implementação da Deque, que é a estrutura usada para definir a "RUA" do trabalho
Lista.h/c
    Implementação da Lista Encadeada, usada para composição do estacionamento, a lista guarda o HEAD de cada pilha de carros.
Pilha.h/c
    Definição da estrutura de dados Pilha, onde cada elemento é um "CARRO".
Auxliares.h/c
    Todas as funções requeridas do trabalho, "INSERÇÃO", "REMOÇÃO", "IMPRESSÃO DA GARAGEM" e "IMPRESSÃO DA RUA".
    E algumas funções extras pra auxiliar essas principais.

HEURÍSTICA:
    Inserção:
        Insere os carros por ordem de chegada, o primeiro a chegar entrará na primeira fila, o segundo a chegar na segunda,
        e assim por diante.

        O algoritmo dará preferência para as pilhas com menos carros.
    Remoção:
        Remove os carros pela placa fornecida pelo usuario, caso tenha algum carro atrás do escolhido
        terá uma manobra dos mesmos até que o carro desejado possa sair do estacionamento.



->  --------------------------------------------------------------  <-
*/


int main() {
    setlocale(LC_ALL, "Portuguese");

    deque* rua = NULL;
    Lista* estacionamento = NULL;
    int escolha = 0;
    int ruaSize, qntdPilha, vagas;
    rua = initialize();

    printf("============ Crie um estacionamento para comecar o programa.============\n");
    printf("Insira a quantidade de pilhas de carro na garagem: \n");
    scanf("%d", &qntdPilha);
    printf("Insira a quantidade de carros por pilha na garagem [vagas]: ");
    scanf("%d", &vagas);
    printf("\n");
    printf("Insira o tamanho da rua [tem que ser minimamente igual a quantidade de vagas]: ");
    scanf("%d", &ruaSize);
    if(ruaSize < vagas){
        printf("Nao eh possivel criar esse estacionamento.\n");
        printf("A rua tem que ter um valor minimo de %d\n", vagas);
        exit(0);
    }
    printf("\n");

    rua->size = ruaSize;
    estacionamento = criaPilhaGaragem(qntdPilha, vagas);

    while(escolha != EOF){
        printf("[1] Para inserir um carro na garagem\n");
        printf("[2] Para remover um carro da garagem\n");
        printf("[3] Para imprimir a garagem\n");
        printf("[4] Sair\n");
        scanf("%d", &escolha);
        fflush(stdin);
        if(escolha == 1){
            insereCarro(estacionamento, rua, qntdPilha, vagas);
        }else if(escolha == 2){
            removeCarro(estacionamento, rua, qntdPilha, vagas);
        }else if(escolha == 3){
            imprimeGaragem(estacionamento);
            printa(rua, rua->size);
        }else if(escolha == 4){
            freeEstacionamento(estacionamento, qntdPilha, vagas);
            exit(0);
        }else{
            printf("Escolha invalida.\n");
            freeEstacionamento(estacionamento, qntdPilha, vagas);
            exit(0);
        }
    }
    return 0;
}

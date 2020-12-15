#include <locale.h>
#include "deque.h"
#include "Lista.h"
#include "Auxliares.h"
/*
->=============COMENT�RIOS EXPLICANDO O TRABALHO E DOCUMENTA��O===========<-

deque.h/c:
    Implementa��o da Deque, que � a estrutura usada para definir a "RUA" do trabalho
Lista.h/c
    Implementa��o da Lista Encadeada, usada para composi��o do estacionamento, a lista guarda o HEAD de cada pilha de carros.
Pilha.h/c
    Defini��o da estrutura de dados Pilha, onde cada elemento � um "CARRO".
Auxliares.h/c
    Todas as fun��es requeridas do trabalho, "INSER��O", "REMO��O", "IMPRESS�O DA GARAGEM" e "IMPRESS�O DA RUA".
    E algumas fun��es extras pra auxiliar essas principais.

HEUR�STICA:
    Inser��o:
        Insere os carros por ordem de chegada, o primeiro a chegar entrar� na primeira fila, o segundo a chegar na segunda,
        e assim por diante.

        O algoritmo dar� prefer�ncia para as pilhas com menos carros.
    Remo��o:
        Remove os carros pela placa fornecida pelo usuario, caso tenha algum carro atr�s do escolhido
        ter� uma manobra dos mesmos at� que o carro desejado possa sair do estacionamento.



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

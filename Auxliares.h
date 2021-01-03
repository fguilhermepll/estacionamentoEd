#ifndef AUXILIAR_H
#define AUXILIAR_H
#include "Lista.h"
#include "deque.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int recomendaVaga(Lista* lista, int qntdPilhas);
int quantidadeCarroGaragemFila(Lista* estacionamento, int i, char* placa);
int quantidadeCarroGaragem(Lista* estacionamento);
int procuraCarroPlaca(Lista** lista, char *placa);

void insereCarro(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas);
void removeCarro(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas);
void imprimeGaragem(Lista* estacionamento);
void freeEstacionamento(Lista* estacionamento, int qntdPilhas, int vagas);

void simulaRemocao(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas, char* aux);
int simulaInsere(Lista* estacionamento, deque* rua, int qntdPilhas, int vagas);

Lista* copiaGaragem(Lista* estacionamento, int qntdPilhas, int vagas);

#endif 

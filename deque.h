#ifndef DEQUE_H
#define DEQUE_H
#include "Pilha.h"

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include<stdio.h>
#endif

typedef struct _deque
{
    Carro** carroData;
    int rear,front, size;
}deque;

deque *initialize();

int isFull(deque *dq);
int isEmpty(deque *dq);

void EnqueueF(deque *dq, Carro* carro, int ruaSize);
void EnqueueR(deque *dq, Carro* carro, int ruaSize);
void DequeueF(deque *dq, int ruaSize);
void DequeueR(deque *dq, int ruaSize);
void printa(deque *dq, int ruaSize);
void DequeueF(deque *dq, int ruaSize);
void DequeueFnoPrint(deque *dq, int ruaSize);

Carro* DequeueFv2noPrint(deque *dq, int ruaSize);
Carro* DequeueFv2(deque *dq, int ruaSize);

#endif

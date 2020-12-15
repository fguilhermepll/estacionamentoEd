#include "deque.h"

void printa(deque *dq, int ruaSize){
    int local_front = dq->front;
    int local_rear = dq->rear;
	if(isEmpty(dq)){
        printf("A rua está vazia.\n");
		return;
    }
	printf("Carros na rua:\n");
	printf("------------\n");
	if( local_front <= local_rear ){
	    while(local_front <= local_rear){
            if(strcmp(dq->carroData[local_front]->placa, "v") != 0){
                printf("| %s  |\n",dq->carroData[local_front]->placa);
            }
			local_front++;
        }
    }else{
        while(local_front <= ruaSize-1){
            if(strcmp(dq->carroData[local_front]->placa, "v") != 0){
                printf("| %s  |\n",dq->carroData[local_front]->placa);
            }
			local_front++;
        }
		local_front = 0;
		while(local_front <= local_rear){
		    if(strcmp(dq->carroData[local_front]->placa, "v") != 0){
                printf("| %s  |\n",dq->carroData[local_front]->placa);
            }
			local_front++;
		}
	}
	printf("------------");
	printf("\n");
}


void DequeueFnoPrint(deque *dq, int ruaSize){
    if (dq->front == -1){
        //printf("A rua está vazia.\n");
		return;
    }
	if(dq->front == dq->rear){	 /*deque tem apenas um elemento*/
        dq->front = -1;
		dq->rear=-1;
    }
	else
		if(dq->front == ruaSize-1)
			dq->front = 0;
		else
			dq->front = dq->front+1;
}

void DequeueF(deque *dq, int ruaSize){
    if (dq->front == -1){
        printf("A rua está vazia.\n");
		return;
    }
	printf("O carro removido da rua foi: [%s]\n",dq->carroData[dq->front]->placa);
	if(dq->front == dq->rear){	 /*deque tem apenas um elemento*/
        dq->front = -1;
		dq->rear=-1;
    }
	else
		if(dq->front == ruaSize-1)
			dq->front = 0;
		else
			dq->front = dq->front+1;
    free(dq->carroData[dq->front]->placa);
}

Carro* DequeueFv2noPrint(deque *dq, int ruaSize){
    if (dq->front == -1){
        printf("A rua está vazia.\n");
		return NULL;
    }
    if(strcmp(dq->carroData[dq->front]->placa, "v") != 0){
    }
	if(dq->front == dq->rear){	 /*deque tem apenas um elemento*/
        dq->front = -1;
		dq->rear=-1;
    }
	else
		if(dq->front == ruaSize-1)
			dq->front = 0;
		else
			dq->front = dq->front+1;
    return dq->carroData[dq->front];
}

Carro* DequeueFv2(deque *dq, int ruaSize){
    if (dq->front == -1){
        printf("A rua está vazia.\n");
		return NULL;
    }
    if(strcmp(dq->carroData[dq->front]->placa, "v") != 0){
        printf("O carro removido da rua foi: [%s]\n",dq->carroData[dq->front]->placa);
    }
	if(dq->front == dq->rear){	 /*deque tem apenas um elemento*/
        dq->front = -1;
		dq->rear=-1;
    }
	else
		if(dq->front == ruaSize-1)
			dq->front = 0;
		else
			dq->front = dq->front+1;
    return dq->carroData[dq->front];
}

void DequeueR(deque *dq, int ruaSize){
    if (isEmpty(dq)){
        printf("Rua esta vazia.\n");
		return;
    }

	printf("O carro removido da rua foi: [%s]\n",dq->carroData[dq->rear]->placa);

	if(dq->front == dq->rear){	  /*deque tem apenas um elemento*/
        dq->front = -1;
		dq->rear = -1;
    }else if(dq->rear == 0)
			dq->rear= ruaSize - 1;
		else
			dq->rear= dq->rear - 1;
}

//Insere um elemento no início da deque
void EnqueueF(deque *dq, Carro* carro, int ruaSize){
    if(isFull(dq)){
        printf("A rua esta cheia\n");
        return;
    }else{
        if(isEmpty(dq)){
            dq->front = 0;
            dq->rear = 0;
        }else if(dq->front == 0) // front está na primeira posição da deque
            dq->front = ruaSize - 1;
        else
            dq->front = dq->front - 1; // decrementa front em '1'
    }
    dq->carroData[dq->front] = carro;
}

//Insere um elemento no fim da deque.
void EnqueueR(deque *dq, Carro* carro, int ruaSize){
	if(isFull(dq)){
	    printf("A rua esta cheia\n");
		return;
    }else{
        if (isEmpty(dq)){ //Se a deque estiver vazia inicialmente
            dq->front = 0;
            dq->rear = 0;
        }else if(dq->rear == ruaSize-1){  //rear é a ultima posicao da deque
            dq->rear = 0;
        }else{
            dq->rear = dq->rear+1;
        }
    }
	dq->carroData[dq->rear] = carro;
}

deque *initialize(){
    deque *dq;
    dq = (deque*) malloc(sizeof(deque));
    dq->front = -1;
    dq->rear = -1;
    dq->size = 0;
    dq->carroData = (Carro**) malloc(sizeof(Carro*));
    if(dq == NULL) return NULL;
    return dq;
}

int isEmpty(deque *dq){
    if(dq->front == -1 && dq->rear == -1)
        return 1;
    return 0;
}

int isFull(deque *dq){
    if(dq->front == dq->rear + 1)
        return 1;
    return 0;
}

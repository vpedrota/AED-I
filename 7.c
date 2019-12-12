#include "stdio.h"
#include "stdlib.h"

struct elemento {
    int valor;
    struct elemento *anterior;
};

typedef struct elemento tipoElemento;

struct pilha
{
    tipoElemento *topo;
    int tamanho;
};

typedef struct pilha tipoPilha;

void inicializa(tipoPilha *pilha){
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

void adicionar(tipoPilha *pilha, int valor){
    tipoElemento *elemento = (tipoElemento*)malloc(sizeof(tipoElemento));
    pilha->tamanho++;
    elemento->valor = valor;

    if(pilha->tamanho == 0){
        pilha->topo = elemento;
        elemento->anterior = NULL;
        return;
    }

    elemento->anterior = pilha->topo;
    pilha->topo = elemento;
}

void remover(tipoPilha *pilha, int elemento){
    tipoPilha *aux = pilha->topo;
    if(elemento != pilha->topo->valor){
        printf("Não foi possível remover esse carro agora\n");
        return ;
    }

    pilha->topo = pilha->topo->anterior;
    pilha->tamanho--;
    free(aux);
}

void imprimir(tipoPilha *pilha){
    tipoElemento *aux = pilha->topo;
    for(; aux->anterior != NULL; aux = aux->anterior){
        printf("%d ", aux->valor);
    }
    printf("%d",aux->valor);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    tipoPilha pilha;
    inicializa(&pilha);
    int operacoes, i, opcao, valor;
    scanf("%d", &operacoes);
    for (i = 0; i < operacoes; i++){
        scanf("%d %d", &opcao, &valor);
        if(opcao == 1){
            adicionar(&pilha, valor);
            imprimir(&pilha);
        }
        else if(opcao == 2){
            remover(&pilha, valor);
            imprimir(&pilha);
        }
    }
    return 0;
}

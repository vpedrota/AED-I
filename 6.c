#include "stdio.h"

#define tamanhoMAX 1000

struct filaCircular {
    int primeiro;
    int ultimo;
    int elementos[tamanhoMAX];
};
typedef struct filaCircular tipoFC;

void inicializaFila (tipoFC *filaAux){
    int i;
    filaAux->primeiro = -1;
    filaAux->ultimo = -1;
    for (i=0; i<tamanhoMAX; i++)
        filaAux->elementos[i]=0;
}

void imprimir(tipoFC *lista){
    int i;
    for (i = lista->ultimo; i >= lista->primeiro; i--) {
        printf("%d ", lista->elementos[i]);
    }
    printf("\n");
}

int filaVazia(tipoFC *filaAux){
    if ((filaAux->primeiro==filaAux->ultimo) && (filaAux->ultimo==-1))
        return 1; // fila está vazia
    return 0; // fila não está vazia
}
void remover(tipoFC *fila){
    if(filaVazia(fila)){
        printf("A fila está vazia\n");
        return ;
    }
    fila->primeiro++;
}


void inserir(int codigo, tipoFC *fila) {
    if(filaVazia(fila)){
        fila->primeiro++;
        fila->ultimo++;
        fila->elementos[0] = codigo;
        return ;
    }
    fila->ultimo++;
    fila->elementos[fila->ultimo] = codigo;
}

void concluir(tipoFC *fila){
    if(filaVazia(fila)){
        printf("A fila está vazia\n");
        return;
    }
    int codigo = fila->elementos[fila->primeiro];
    remover(fila);
    inserir(codigo, fila);
}


int main(int argc, char const *argv[]) {
    int vezes, i, opcao, codigo;
    tipoFC fila;
    inicializaFila(&fila);

    scanf("%d", &vezes);
    for (i = 0; i < vezes; i++) {
        scanf("%d", &opcao);
        if(opcao == 1){
            scanf("%d", &codigo);
            inserir(codigo, &fila);
        }
        else if(opcao == 2){
            remover(&fila);
        }
        else{
            concluir(&fila);
        }

        //imprimir(&fila);
    }
    imprimir(&fila);
    return 0;
}

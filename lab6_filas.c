#include <stdio.h>

#define tamanhoMAX 100

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


int filaVazia(tipoFC *filaAux){
  if ((filaAux->primeiro==filaAux->ultimo) && (filaAux->ultimo==-1)){
    return 1;
  }
  else return 0;
}


int filaCheia(tipoFC *filaAux){
  if (((filaAux->ultimo + 1) % tamanhoMAX) == filaAux->primeiro){
    return 1;
    }
  else return 0;
}


void inserir(tipoFC *filaAux, int codigo){

  int posicao = (filaAux->ultimo + 1) % tamanhoMAX;
  if (!filaVazia(filaAux)) {
    filaAux->ultimo = posicao;
    filaAux->elementos[posicao] = codigo;
    return;
  }

    filaAux->ultimo = posicao;
    filaAux->primeiro++;
    filaAux->elementos[posicao] = codigo;
    return ;

}

void remover(tipoFC *filaAux){

  if(!filaVazia(filaAux)){
    filaAux->primeiro++;
    return;
  }

  printf("A fila está vazia\n");
}


void conclusao(tipoFC *filaAux){
  int codigo;
  if(!filaVazia(filaAux)){
    codigo = filaAux->elementos[filaAux->primeiro];
    filaAux->primeiro++;
    int posicao = (filaAux->ultimo + 1) % tamanhoMAX;
    filaAux->ultimo = posicao;
    filaAux->elementos[posicao] = codigo;

    return;
  }
  printf("A fila está vazia\n");

}


int main(){
  int i, movimentacoes, operacao, codigo;
  tipoFC filaAux;
  inicializaFila(&filaAux);

  scanf("%d", &movimentacoes);
  for (i = 0; i < movimentacoes; i++) {
    scanf("%d", &operacao);
    if (operacao == 1) {
      scanf("%d", &codigo);
      inserir(&filaAux, codigo);
    }
    else if (operacao == 2) {
      remover(&filaAux);
    } else {
      conclusao(&filaAux);
    }
  }


  for (i = filaAux.ultimo; i >= filaAux.primeiro; i--) {
    printf("%d ", filaAux.elementos[i]);
  }


  return 0;
}

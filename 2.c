/* Programa: Piscina

   Autor: Victor pedrota

   Versao: 1.0 - 17/07/2019

*/

// ##################### Bibliotecas Externas ##############################
#include <stdio.h>
#include <stdlib.h>

#define N 10

// ########################## TAD X.h ######################################
typedef struct{
  int valor;
  int prox;
} info;

typedef struct{
  int tamanho;
  int primeiro;
  int ultimo;
  int posLivre[N];
  info elemento[N];
} estrutura;

 // coloque o codigo da sua implementação e definicao da TAD aqui
int proxPosLivre(estrutura *lista)
{
  int i;
  for (i=0;i < N;i++){
      if (lista->posLivre[i]==1)
          return i;
  }
  return -1;
}

void imprimir(estrutura *lista){  //imprimi tudo

  int i, tamanho = lista->tamanho, pos;
  if(tamanho == 0)
    return ;

  pos = lista->primeiro;
  while(pos != -1){
    printf("%d ", lista->elemento[pos].valor);
    pos=lista->elemento[pos].prox;
  }
  printf("\n");

}


void inicializaLista (estrutura *lista)
{
  int i;
  lista->tamanho = 0;
  lista->primeiro = -1;
  lista->ultimo = -1;

  for (i=0; i<N; i++){
      lista->elemento[i].valor = 0;
      lista->elemento[i].prox = -1;
      lista->posLivre[i] = 1;
  }
}

int buscar(estrutura *lista, int carteira)
{
  int pos;
  pos = lista->primeiro;
  while(pos != -1){
      if(carteira == lista->elemento[pos].valor){
          return pos;
      }
      pos=lista->elemento[pos].prox;
  }
  return -1;
}

void inserir(estrutura *lista, int carteira, int *vetor)
{
  int i,j, aux, posicao = proxPosLivre(lista), n, pos, pos2, tamanho, aux2 = 0;
  if (posicao!=-1){

    lista->elemento[posicao].valor = carteira;
    lista->posLivre[posicao] = 0;

    conta_ano(lista, carteira, vetor);

    if (lista->tamanho==0){
      lista->primeiro = posicao;
      lista->elemento[posicao].prox = -1;

    }
    else{

      pos = lista->elemento[lista->primeiro].prox;

      if(pos == -1){
        lista->elemento[lista->primeiro].prox = posicao;
        lista->ultimo = posicao;
        lista->tamanho++;
        pos = lista->primeiro;
        ordena(lista);
        imprimir(lista);
        //imprimir_teste(lista);
        return ;
      }

      while(pos != -1){
        if(lista->elemento[pos].prox == -1)
          break;
        pos = lista->elemento[pos].prox;
      }

      lista->elemento[pos].prox = posicao;
    }

    lista->ultimo = posicao;
    lista->tamanho++;
    tamanho = lista->tamanho;
    ordena(lista);
    imprimir(lista);
    //imprimir_teste(lista);
  }
  else {
    printf("Dia cheio\n");
    imprimir(lista);
  }
}

void retirar(estrutura *lista, int carteira, int *vetor){
    int pos,i;
  pos = buscar(lista, carteira);
  if(pos == -1){
    printf("Não foi reservado\n");
    imprimir(lista);
    return ;
  }

  if(lista->tamanho == 1){
    lista->primeiro = -1;
    lista->ultimo = -1;
    lista->tamanho = 0;
    lista->posLivre[0] = 1;
    imprimir(lista);
    return ;
  }

  lista->posLivre[lista->ultimo] = 1;
  while(pos != -1){
    lista->elemento[pos].valor = lista->elemento[lista->elemento[pos].prox].valor;
    pos=lista->elemento[pos].prox;
  }
  lista->tamanho--;
  lista->ultimo--;
  lista->elemento[lista->ultimo].prox = -1;
  //imprimir_teste(lista);
  imprimir(lista);

}

// ###################### Funcoes e Procedimentos do programa ##############
void ordena(estrutura *lista){
  int pos, pos2, aux;
  pos = lista->primeiro;
  while (pos != -1) {
    pos2 = lista->primeiro;
    while (pos2 != -1) {
      if(lista->elemento[pos2].valor >= lista->elemento[pos].valor){
        aux = lista->elemento[pos].valor;
        lista->elemento[pos].valor = lista->elemento[pos2].valor;
        lista->elemento[pos2].valor = aux;

      }
      pos2 = lista->elemento[pos2].prox;
    }
    pos = lista->elemento[pos].prox;
  }
}

void imprimir_teste(estrutura *lista){
  int i;
  for ( i = 0; i < 10; i++) {
    printf("%d ", lista->posLivre[i]);
  }
  printf("\n");
}

void conta_ano(estrutura *lista,int carteira, int *vetor) {
  int i,j;
  if(buscar(lista,carteira) < 10){
    for (i = 0; i < 8; i++) {
      if(carteira >= 10000*(i+1) && carteira < 10000*(i+1) + 10000){
        vetor[i]++;
        break;
      }
    }
  }
}

// ############################ Principal ###################################
int main(){

  estrutura lista;
  int i, opcao, acao, carteira, pos, vetor[9];

  for(i = 0; i < 8; i++){
    vetor[i]=0;
  }

  inicializaLista(&lista);
  scanf("%d", &acao);
  for(i=0;i<acao;i++){
    scanf("%d %d", &opcao, &carteira);
    if(opcao == 1){
      inserir(&lista, carteira, vetor);
    }
    else if (opcao == 2){
      retirar(&lista, carteira, vetor);
    }
  }

  for (i = 0; i < 8; i++) {
    printf("%d: %d\n", 2012+(i), vetor[i]);
  }
  return 0;
}

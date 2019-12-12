/* Programa: Laboratório #1 - lab1.c

Autor: VICTOR HUGO GODOI PEDROTA

Versao: 1.0 - 06/09/2019

*/

// ##################### Bibliotecas Externas ##############################
#include<stdio.h>
#include<stdlib.h>
// ########################## TAD X.h ######################################

typedef struct{
  int ultimo;
  int tamanho;
  int lista[10];
} dados;

// ###################### Funcoes e Procedimentos do programa ##############

void criar(dados *biblioteca) {
  int  i;
  biblioteca->ultimo=0;
  biblioteca->tamanho = 0;
  for ( i = 0; i < 10; i++) {
    biblioteca->lista[i] = 0;
  }
}

int buscar(dados *biblioteca, int numero){
  int i, n = biblioteca->tamanho;
  for (i = 0; i < n; i++) {
    if(biblioteca->lista[i] == numero)
    return 1;
  }
  return 0;
}

void inserir(dados *biblioteca, int *reservas) {
  int numero;
  scanf("%d", &numero);
  if(biblioteca->tamanho == 10){
    printf("Lista de reserva cheia\n");
    return ;
  }
  biblioteca->tamanho++;
  biblioteca->lista[biblioteca->tamanho-1] = numero;
  biblioteca->ultimo = numero;
  (*reservas)++;
  printf("Sua reserva foi realizada\n");
}


void imprimir(dados *biblioteca){
  int i, n = biblioteca->tamanho;
  for (i = 0; i < n; i++) {
    printf("-%d-\n", biblioteca->lista[i]);
  }
}


void remover(dados *biblioteca, int *retidas){
  int i, n = biblioteca->tamanho, pos, numero;
  scanf("%d", &numero);

  if(!buscar(biblioteca, numero)){
    printf("Voce nao possui reserva desse livro\n");
    return;
  }

  if(numero == biblioteca->ultimo){
    biblioteca->tamanho--;
    biblioteca->ultimo = biblioteca->lista[biblioteca->tamanho-1];
  }
  else{
    for (i = 0; i < n; i++) {
      if(biblioteca->lista[i] == numero){
        pos = i;
      }
    }
    biblioteca->tamanho--;
    n--;
    for (i = pos; i < n; i++) {
      biblioteca->lista[i] = biblioteca->lista[i+1];
    }
  }
  (*retidas)++;
  printf("O livro foi retirado com sucesso\n");
}

// Coloque as demais funcoes do seu programa aqui


// ############################ Principal ###################################

int main(int argc, char const *argv[]) {
  dados lista;
  int n_operacoes, i=0, operacao, retidas=0, reservas=0;
  criar(&lista);
  scanf("%d", &n_operacoes);
  for(;;){
    if(i >= n_operacoes)
    break;
    scanf("%d", &operacao);
    if(operacao == 1){
      inserir(&lista, &reservas);
    }
    else if(operacao == 2){
      remover(&lista, &retidas);
    }
    i++;
  }
  printf("Voce realizou %d reservas e %d retiradas\n", reservas, retidas );
  //imprimir(&lista);
  return 0;
}

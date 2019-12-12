/* Programa: jogo 12

   Autor: Victor Pedrota

   Versao: 1.0 - 03/10/2019

*/

// ##################### Bibliotecas Externas ##############################

#include "stdio.h"
#include "stdlib.h"

typedef struct Node{
  int numero;
  struct Node* proximo;
  struct Node* anterior;
} Node;

Node* primeiro = NULL;
Node* ultimo = NULL;
int tamanho = 0;

int conta_tamanho(){
  Node* aux = primeiro;
  if (aux == NULL)
      return 0;
  return 1 + conta_tamanho(aux->proximo);
}

void imprimir() {
  Node* elemento = primeiro;

  while(elemento != NULL) {
    printf("%d ", elemento->numero);
    elemento = elemento->proximo;
  }
  printf("\n");
}


void imprimir_inverso() {
  Node* elemento = ultimo;
  if(ultimo == NULL)
    return ;
  while(elemento != NULL) {
    printf("%d ", elemento->numero);
    elemento = elemento->anterior;
  }
  printf("\n");
}

void inserir_numero(int numero) {
  Node* temp = (Node*)malloc(sizeof(Node));

  temp->numero = numero;
  tamanho++;

  if(primeiro == NULL){
    primeiro = temp;
    ultimo = temp;
    temp->proximo = NULL;
    temp->anterior = NULL;
    return ;
  }

  ultimo->proximo = temp;
  temp->proximo = NULL;
  temp->anterior = ultimo;
  ultimo = temp;
}

void inserir_numero_meio(int numero, int pos){
  int i;
  Node *aux = primeiro;
  Node* temp = (Node*)malloc(sizeof(Node));
  temp->numero = numero;

  if(pos > tamanho)
    return;

  if(primeiro == NULL){
    primeiro = temp;
    ultimo = primeiro;
    temp->anterior = NULL;
    temp->proximo = NULL;
    tamanho++;
    return ;
  }

  if(pos == 0){
    temp->proximo = primeiro;
    temp->anterior = NULL;
    aux->anterior = temp;
    primeiro = temp;
    tamanho++;
    return;
  }

  if(pos == tamanho){
    ultimo->proximo = temp;
    temp->proximo = NULL;
    ultimo = temp;
    tamanho++;
    return;
  }
  for (i = 0; i < pos-1; i++) {
    aux = aux->proximo;
  }
  temp->proximo = aux->proximo;
  aux->proximo = temp;
  temp->anterior = aux;
  temp->proximo->anterior = temp;
  tamanho++;
}

void remover(Node* elemento){
  tamanho--;
  if(elemento->anterior == NULL){
    primeiro = elemento->proximo;
    primeiro->anterior = NULL;
    free(elemento);
    return ;
  }

  if(elemento->proximo == NULL){
    ultimo = elemento->anterior;
    ultimo->proximo = NULL;
    free(elemento);
    return ;
  }

  elemento->anterior->proximo = elemento->proximo;
  elemento->proximo->anterior = elemento->anterior;
  free(elemento);
}

int checa_soma(Node* aux){

  int soma;
  if(primeiro == NULL)
    return 0;

  if(tamanho < 3)
    return 0;

  if(tamanho == 3 && primeiro->proximo->numero + primeiro->numero + primeiro->proximo->proximo->numero != 12)
    return 0;

  if(tamanho == 3 && primeiro->proximo->numero + primeiro->numero + primeiro->proximo->proximo->numero == 12){
    primeiro = NULL;
    tamanho = 0;
    ultimo = NULL;
    return 0;
  }

  if(aux->proximo == NULL){
    if(aux->numero + aux->anterior->numero + aux->anterior->anterior->numero == 12){
      remover(aux->anterior->anterior);
      remover(aux->anterior);
      remover(aux);
      return checa_soma(primeiro);
    }
    return 0;
  }

  if(aux->anterior == NULL){
    if(aux->numero + aux->proximo->numero + aux->proximo->proximo->numero == 12){
      remover(aux->proximo->proximo);
      remover(aux->proximo);
      remover(aux);
      return checa_soma(primeiro);

    }
    return checa_soma(aux->proximo);
  }

    soma = aux->numero + aux->anterior->numero + aux->proximo->numero;
    if(soma == 12){
      remover(aux->proximo);
      remover(aux->anterior);
      remover(aux);
      return checa_soma(primeiro);
    }
    return checa_soma(aux->proximo);
}


int main(int argc, char const *argv[]) {
  int i, numero, pos, soma;
  Node* aux;
  for (i = 0; i < 10; i++) {
    scanf("%d", &numero);
    inserir_numero(numero);
  }

  for (i = 0; i < 5; i++) {
    imprimir();
    //imprimir_inverso();
    scanf("%d %d", &numero, &pos);
    inserir_numero_meio(numero, pos);
    checa_soma(primeiro);
  }
  imprimir();
  if(primeiro == NULL){
    printf("Eba, você ganhou!\n");
  }
  else{
    printf("Ih, não foi dessa vez\n" );
  }
  return 0;
}

#include "stdio.h"
#include "stdlib.h"


typedef struct Node{
  int numero;
  struct Node* proximo;
  struct Node* anterior;
} Node;

Node* primeiro = NULL;
int tamanho = 0;

void imprimir() {
  Node* elemento = primeiro;

  while(elemento->proximo != primeiro) {
    printf("%d ", elemento->numero);
    elemento = elemento->proximo;
  }
  printf("%d \n",elemento->numero);
}

void remover(Node* aux){

  Node* elemento;

  if(tamanho == 1){
    free(primeiro);
    primeiro = NULL;
    tamanho = 0;
    return;
  }


  if(aux == primeiro && tamanho != 1){
    primeiro->anterior->proximo = primeiro->proximo;
    primeiro->proximo->anterior = primeiro->anterior;
    primeiro = primeiro->proximo;
    free(aux);
    tamanho--;
    return;
  }

  aux->proximo->anterior = aux->anterior;
  aux->anterior->proximo = aux->proximo;
  tamanho--;
}

void inserir_numero(int numero) {
  Node* temp = (Node*)malloc(sizeof(Node));
  Node* elemento = primeiro;

  temp->numero = numero;
  tamanho++;

  if(primeiro == NULL){
    primeiro = temp;
    temp->proximo = NULL;
    temp->anterior = NULL;
    return ;
  }



  if(primeiro->proximo == NULL){
    primeiro->proximo = temp;
    temp->anterior = primeiro;
    primeiro->anterior = temp;
    temp->proximo = primeiro;
    return;
  }

  primeiro->anterior->proximo = temp;
  temp->anterior = primeiro->anterior;
  temp->proximo = primeiro;
  primeiro->anterior = temp;

}

int main(int argc, char const *argv[]) {
  int n_criancas, i, numero, passadas,passadas2, n_paes, count = 0;
  Node* aux = primeiro;
  scanf("%d", &n_criancas);
  for (i = 0; i < n_criancas; i++) {
    scanf("%d", &numero);
    inserir_numero(numero);
  }
  imprimir();

  scanf("%d", &n_paes);
  passadas = n_paes%n_criancas;
  passadas2 = n_paes/n_criancas;

  aux = primeiro;
  while(count < passadas-1){
    aux = aux->proximo;
    count++;
  }

  if(n_paes == 1 || passadas == 1){
    printf("Passadas na lista: %d\n", passadas2);
    remover(primeiro);
    imprimir();
    return 0;
  }

  if(passadas == 0){
    printf("Passadas na lista: %d\n", passadas2);
    remover(primeiro->anterior);
    imprimir();
    //printf("ddd\n" );
    return 0;
  }

  printf("Passadas na lista: %d\n", passadas2);
  remover(aux);
  imprimir();


  return 0;
}

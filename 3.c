/* Programa: Exemplo

   Autor: victor pedrota

   Versao: 1.0 - 26/09/2019

*/

#include "stdio.h"
#include "stdlib.h"

// ########################## TAD X.h ######################################
typedef struct Node{
  int quantidade, codigo, alugados;
  float preco;
  struct Node* proximo;
} Node;

Node* primeiro = NULL;

void imprimir() {
  Node* elemento = primeiro;
  while(elemento != NULL) {
    printf("%d ", elemento->codigo);
    printf("%f\n", elemento->preco * elemento->alugados);
    elemento = elemento->proximo;
  }
}

Node* procurar(int codigo) {
  Node *elemento = primeiro;
  if(elemento == NULL){
    return NULL;
  }

  if(elemento->codigo == codigo)
    return elemento;

  while(elemento != NULL){
    if(elemento->codigo == codigo)
        return elemento;
    elemento = elemento->proximo;
  }
  return NULL;
}

void inserir_cadastro(int codigo) {
  Node* temp;
  int quantidade;
  float preco;

  scanf("%d %f", &quantidade, &preco);

  if(procurar(codigo) != NULL){
    printf("O jogo já está cadastrado\n");
    return ;
  }

  temp = (Node*)malloc(sizeof(Node));
  temp->codigo = codigo;
  temp->preco = preco;
  temp->quantidade = quantidade;
  temp->proximo = primeiro;
  temp->alugados = 0;
  primeiro = temp;
}

void adicionar_jogo(int codigo) {
  int quantidade;
  Node* elemento;
  scanf("%d", &quantidade);
  elemento = procurar(codigo);
  if(elemento == NULL){
    printf("Não há\n");
    return ;
  }
  elemento->quantidade += quantidade;
}

void remover_jogo(int codigo) {
  Node* elemento = procurar(codigo);
  if(elemento == NULL || elemento->quantidade == 0){
    printf("Não há\n");
    return ;
  }

  elemento->quantidade--;
  elemento->alugados++;
}

void remover_cadastro(int codigo) {
  Node* aux;
  Node* elemento = procurar(codigo);


  if(elemento == NULL ){
    printf("Não há\n");
    return ;
  }


  //caso esteja no começo
  if(elemento == primeiro){
    primeiro = elemento->proximo;
    free(elemento);
    return ;
  }

  aux = primeiro;
  while(aux->proximo->codigo != elemento->codigo || aux->proximo == NULL){
    aux = aux->proximo;
  }

  aux->proximo = elemento->proximo;
  free(elemento);
}

//ordenando a lista
void ordernar(){
  Node *x, *y, *e;
  x = primeiro;
  primeiro = NULL;
  while(x != NULL){
    e = x;
    x = x->proximo;
    if (primeiro != NULL){
      if(e->preco <= primeiro->preco){
        y = primeiro;
        while ((y->proximo != NULL) && (e->preco <= y->proximo->preco)){
          y = y->proximo;
        }
        e->proximo = y->proximo;
        y->proximo = e;
      }
    else{
      e->proximo = primeiro;
      primeiro = e ;
      }
    }
    else{
      e->proximo = NULL;
      primeiro = e ;
    }
  }
}

int main(int argc, char const *argv[]) {
  int acoes, i, codigo, opcao;
  scanf("%d", &acoes);

  for (i = 0; i < acoes; i++) {
    scanf("%d %d", &opcao, &codigo);
    switch(opcao){
      case 1:
        inserir_cadastro(codigo);
        break;
      case 2:
        adicionar_jogo(codigo);
        break;
      case 3:
        remover_jogo(codigo);
        break;
      case 4:
        remover_cadastro(codigo);
        break;
    }
    //imprimir();
  }
  ordernar();
  imprimir();
  return 0;
}

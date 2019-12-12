#include "stdio.h"
    #include "stdlib.h"
    #include "string.h"

    struct pessoa {
      char nome[50];
      int ano_nascimento;
      char sexo;
      char pai[50];
      struct pessoa *esq;
      struct pessoa *dir;
    };

    typedef struct pessoa Herdeiro;
    Herdeiro* raiz = NULL;
    int ehigual(char* pai, char* nome){
      int i, tam = strlen(pai);

      for(i = 0; i < tam; i++){
        if(nome[i] != pai[i]){
          return 0;
        }
      }
      return 1;
    }

    Herdeiro* busca_loka(Herdeiro *carinha, char* nome){

      if(carinha != NULL && (carinha->esq != NULL || carinha->dir != NULL) ){
        if(ehigual(nome, carinha->esq->nome) || ehigual(nome, carinha->dir->nome)){
          return carinha;
        }
        busca_loka(carinha->dir, nome);
        busca_loka(carinha->esq, nome);
      }
    }


    void imprime ( Herdeiro *aux ){
      if (aux!= NULL){
        printf("%s\n", aux->nome);
        imprime(aux->dir);
        imprime(aux->esq);
      }
    }

    Herdeiro* root = NULL;
    Herdeiro* insereNo (int ano_nascimento, char sexo, char* nome, char* pai ){
      Herdeiro* novo = (Herdeiro*) malloc(sizeof(Herdeiro));
      novo->ano_nascimento = ano_nascimento;
      novo->sexo = sexo;
      int i, tam = strlen(nome);
      for (i = 0; i < tam; i++) {
        novo->nome[i] = nome[i];
      }
      tam = strlen(pai);
      for (i = 0; i < tam; i++) {
        novo->pai[i] = pai[i];
      }
      novo->dir = NULL;
      novo->esq= NULL;
      return novo;
    }

    void insere(int ano_nascimento, char sexo, char* nome, char* pai, Herdeiro* root){
      if(root !=   NULL ){
        insere(ano_nascimento, sexo, nome, pai,root->esq);
        if(ehigual(root->nome, pai)){
            //("cadastrou ");
            //printf("%s  %s",root->nome, nome);
            if(root->esq == NULL && root->dir == NULL)
              root->esq = insereNo(ano_nascimento, sexo,nome, pai);
            else if (root->esq != NULL && root->dir == NULL){
              if(ano_nascimento < 2011){
                if(root->esq->sexo == 'M' && sexo == 'F'){
                  root->dir = root->esq;
                  root->esq = insereNo(ano_nascimento, sexo,nome, pai);
                }
                else if(((root->esq->sexo == 'M' && sexo == 'M') || (root->esq->sexo == 'F' && sexo == 'F')) && ano_nascimento > root->esq->ano_nascimento){
                  root->dir = root->esq;
                  root->esq = insereNo(ano_nascimento, sexo,nome, pai);
                }
                else
                  root->dir = insereNo(ano_nascimento, sexo,nome, pai);
              }
              else if(ano_nascimento >= 2011){
                if( ano_nascimento > root->esq->ano_nascimento){
                  root->dir = root->esq;
                  root->esq = insereNo(ano_nascimento, sexo,nome, pai);
                }
                else
                  root->dir = insereNo(ano_nascimento, sexo,nome, pai);
              }
            }

        }
        insere(ano_nascimento, sexo, nome, pai,root->dir);
      }

    }

    void remover(Herdeiro* root){
      char nome[50];
      Herdeiro *aux = NULL;
      scanf("%s", nome);
      if(ehigual(raiz->nome, nome)){
        raiz = NULL;
        return;
      }

      aux = busca_loka(root, nome);
      if(aux == NULL)
        return;
      if(aux->esq != NULL){
        if(ehigual(aux->esq->nome, nome)){
          aux->esq = NULL;
          return;
        }
      }
      if(aux->dir != NULL){
        if(ehigual(aux->dir->nome, nome)){
          aux->dir = NULL;
          return;
        }
      }

    }

    int main(int argc, char const *argv[]) {
      int numero_herdeiros, ano_nascimento, i, opcao;
      char nome[50], sexo, pai[50];

      scanf("%s %c %d", nome, &sexo, &ano_nascimento);
      raiz = insereNo(ano_nascimento, sexo, nome, "");
      scanf("%d",&numero_herdeiros);

      for (i = 0; i < numero_herdeiros; i++) {
        scanf("%d", &opcao);
        if(opcao == 1){
          scanf("%s %c %d %s", nome, &sexo, &ano_nascimento, pai);
          insere(ano_nascimento, sexo, nome, pai, raiz);
        }
        else{
          remover(raiz);
        }
      }
      imprime(raiz);
      return 0;
    }

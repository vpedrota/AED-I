
    #include <stdio.h>
    #include <stdlib.h>

// ########################## TAD X.h ######################################

    typedef struct {

    	int camaras;
    	int caminhos;
    	int vertice[50];
    	int MatrizAdj[50][50];

    } Labirinto;


// ###################### Funcoes e Procedimentos do programa ##############

    void iniciarGrafo(Labirinto *Aux){
    	int i, k;
    	for (i=0; i<50; i++) {
    		for (k=0; k<50; k++) {
    			Aux->MatrizAdj[i][k]=0;
    		}
    	}
    }


    int rodaMatriz(Labirinto *Aux, int I, int F, int arestas){
    	int i, aux = 0;
    	for (i=0; i<Aux->camaras; i++) {
    		if (Aux->MatrizAdj[I][i] == 1 && F==i) {
    			arestas += 1;
    		} else if (Aux->vertice[i] == 0 && Aux->MatrizAdj[I][i] == 1) {
    			Aux->vertice[i] = 1;
    			arestas = rodaMatriz(Aux, i, F, arestas);
    			Aux->vertice[i] = 0;
    		}
    	}
    	return arestas;
    }

// ############################ Principal ###################################

    int main()
    {
    	int i, V1, V2, salaoInicial, salaoFinal, arestas=0;

    	Labirinto labirinto;
    	iniciarGrafo(&labirinto);
    	scanf("%d %d", &labirinto.camaras, &labirinto.caminhos);
    	for (i=0; i<labirinto.caminhos; i++) {
    		scanf("%d %d", &V1, &V2);
    		labirinto.MatrizAdj[V1][V2] = 1;
    	}
    	scanf("%d %d", &salaoInicial, &salaoFinal);
    	for (i=0; i<50; i++) {
    		labirinto.vertice[i] = 0;
    	}
    	labirinto.vertice[salaoInicial] = 1;
    	arestas = rodaMatriz(&labirinto, salaoInicial, salaoFinal, arestas);

    	printf("%d\n", arestas);
    	return 0;
    }

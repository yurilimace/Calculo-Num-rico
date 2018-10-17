#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPSILON 0.000001

double **alocaMatriz(int numLinhas, int numColunas){
    /*Se tiver memória disponível, aloca uma matriz de double com L linhas e c Colunas
      e devolve um ponteiro para essa matriz; Caso contrário, devolve um ponteiro nulo.*/
    double **matriz;
    int i, j;
    matriz = malloc(sizeof(double *)*numLinhas);

    if(matriz == NULL){
        return NULL;
    }

    for(i = 0; i < numLinhas; i++)
    {
        matriz[i] = malloc(sizeof(double)*numColunas);
        if(matriz[i] == NULL){
            for(j = 0; i < numColunas; j++){
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }
    return  matriz;
}

void lerMatriz(double **matriz, int numLinhas, int numColunas){
    /*Ler valores para uma matriz alocada dinamicamente de double com L linhas e C colunas*/
    int i, j;
    for(i = 0; i < numLinhas; i++){
        for(j = 0; j < numColunas; j++){
            printf("m[%d][%d] = ", i + 1, j + 1);
            scanf("%lf", &matriz[i][j]);
        }
    }
}//Fim da matriz

void imprimirMatriz(double **matriz, int numLinhas, int numColunas){
    /*Imprime valores de uma matriz alocada dinamicamente de double com L linhas e C colunas*/
    int i, j;
    for(i = 0; i < numLinhas; i++){
        for(j = 0; j < numColunas; j++){
            printf("%10.3lf", matriz[i][j]);
        }
        printf("\n");
    }
}





void jordan(double **m,int n, int *colunas){
    int i,j,k,p,aux;
    double mult;
    for(i=0;i<n;i++){
        if (m[i][i] == 0){
            j = i+1;
            while(j<n && m[i][j] == 0){
                j++;
            }
            if(j<n){
               for(p=0;p<n;p++){
                  aux = m[p][i];
                  m[p][i] = m[p][j];
                  m[p][j] = aux;
               }
               aux = colunas[i];
               colunas[i] = colunas[j];
               colunas[j] = aux;
            }
            else{
                for(k=0;k<n;k++){
                    m[k][i] = 0;
                }
            }
        }
        if(m[i][i]!=0){
            for(j=0; j<n;j++){
                if(j!=i){
                    mult = m[j][i]/m[i][i];
                    for(k=0;k<n+1;k++){
                        m[j][k] = m[j][k] - (mult * m[i][k]);
                    }
                }
            }
        }
    }
}


int sretro(double **m, int n, double x[]){
    /*Recebe m, a matriz aumentada de um SL TS com n variáveis.
    Se o SL for determinado, armazena em x a solução do SL e dovolve 0;
    Se for indeterminado, armazena uma solução do SL e devolve 1;*/
    int i, j, tipo = 0;
    double soma;
    for(i = n - 1; i >= 0; i--){
        soma = 0;
        for(j = i + 1; j < n; j++){
            soma += m[i][j] * x[j];
        }
        if(m[i][i] == 0){
            if(fabs(m[i][n] - soma) < EPSILON){
                x[i] = 0; //Variável Livre
                tipo = 1;
            }
            else{
                return 2; //SL incompatível
            }
        }
        else{
            x[i] = (m[i][n] - soma)/m[i][i];
        }
    }
    return tipo;
}



int main(){
    int i, n, tipo;
    int *colunas;
    double **m, *x;

    printf("Quantidade de variáveis: ");
    scanf("%d", &n);

    m = alocaMatriz(n, n + 1);
    x = malloc(sizeof(double) *n);

    if(m == NULL || x == NULL){ //Faltou memória
        printf("\nFaltou memória\n");
        return 1;
    }

    colunas = malloc(sizeof(int)*n);

    if(colunas == NULL){
        printf("\n Faltou Memória \n");
    }

    for(i=0;i<n;i++){
        colunas[i] = i+1;
    }


    lerMatriz(m, n, n + 1);
    imprimirMatriz(m, n, n + 1);
    jordan(m,n,colunas);
    printf("matriz triagularizada \n\n\n");
    imprimirMatriz(m,n,n+1);

    tipo = sretro(m,n,x);
    if(tipo == 2){
        printf("Sistema Linear Incompativel");
    }
    else{
        printf("\nSL %sDeterminado\n", tipo ? "IN" : "");
        for(i = 0; i < n; i++){
            printf("x[%d] = %10.3lf\n",colunas[i], x[i]);
        }
    }


    return 0;
}

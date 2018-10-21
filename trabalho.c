#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EPSILON 0.000001

void Converte_Octal(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m,vai;
    double aux;

    for(i=0;Inteiro>=1;i++){
        resultado[i] = Inteiro % 8;
        Inteiro = Inteiro / 8;
    }

    for(j = i-1;j>=0;j--){
        printf("%d",resultado[j]);
    }
    printf(",");

    for(k =0;Fracionario!=0 && k<=19;k++){
        Fracionario = Fracionario * 8;
        Fracionario = modf(Fracionario,&aux);
        vai = (int) aux;
        printf("%d",vai);
    }



}



// Conversão para binário feito
void Converte_binario(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m,vai;
    double aux;

    for(i=0;Inteiro>=1;i++){
        resultado[i] = Inteiro % 2;
        Inteiro = Inteiro / 2;
    }

    for(j = i-1;j>=0;j--){
        printf("%d",resultado[j]);
    }
    printf(",");

    for(k =0;Fracionario!=0 && k<=19;k++){
        Fracionario = Fracionario * 2;
        Fracionario = modf(Fracionario,&aux);
        vai = (int) aux;
        printf("%d",vai);
    }


}



void Converte_Hexa(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m,vai;
    double aux;

    for(i=0;Inteiro>=1;i++){
        resultado[i] = Inteiro % 16;
        Inteiro = Inteiro / 16;
    }

    for(j = i-1;j>=0;j--){
        if(resultado[j] == 10){
            printf("A");
        }
        else if(resultado[j]==11){
                printf("B");
        }
        else if(resultado[j]==12){
                printf("C");
        }
        else if(resultado[j]==13){
                printf("D");
        }
        else if(resultado[j]==14){
                printf("E");
        }
        else if(resultado[j]==11){
                printf("F");
        }
        else{
            printf("%d",resultado[j]);
        }

    }
    printf(",");

    for(k =i;Fracionario!=0 && k<=19;k++){
        Fracionario = Fracionario * 16;
        Fracionario = modf(Fracionario,&aux);
        vai = (int) aux;
        if(vai == 10){
            printf("A");
        }
        else if(vai ==11){
                printf("B");
        }
        else if(vai == 12){
                printf("C");
        }
        else if(vai ==13){
                printf("D");
        }
        else if(vai ==14){
                printf("E");
        }
        else if(vai == 15){
                printf("F");
        }
        else{
            printf("%d",vai);
        }
    }



}



void ConverteNumero(){
    int i,j;
    double teste;
    int Parte_inteira;
    double Parte_fracionaria;
    int  *resultado; //Armazena o resultado das sucessivas divisões

    printf("Digite o numero decimal ");
    scanf("%lf",&teste);

    Parte_inteira = floor(teste);
    Parte_fracionaria = teste - Parte_inteira;

    resultado = malloc(sizeof(resultado)*30);

    if(resultado == NULL){
        printf("Não alocado Falta de memoria");
    }


    Converte_binario(Parte_inteira,Parte_fracionaria,resultado);
    printf("\n");
    Converte_Octal(Parte_inteira,Parte_fracionaria,resultado);
    printf("\n");
    Converte_Hexa(Parte_inteira,Parte_fracionaria,resultado);
    printf("\n");



}


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



void SistemaLinear(FILE *file){
    double **matriz,*x;
    int n,i,j,tipo;
    int *colunas;
    fscanf(file,"%d \r\n",&n);
    printf("%d \r\n",n);
    matriz = alocaMatriz(n,n+1);
    x = malloc(sizeof(double)*n);

    if(matriz == NULL || x == NULL){
        printf("Memoria insuficiente");
    }

    colunas = malloc(sizeof(int)*n);

    if(colunas == NULL){
        printf("Memoria Insuficiente");
    }


    for(i = 0 ;i < n ;i++){
        colunas[i] = i+1;
    }

    for ( i = 0 ; i < n ; i++ ){
         for(j = 0 ; j < n+1 ; j++){
            fscanf(file,"%lf",&matriz[i][j]);
         }
    }

    imprimirMatriz(matriz,n,n+1);
    jordan(matriz,n,colunas);
    printf("matriz triagularizada \n\n\n");
    imprimirMatriz(matriz,n,n+1);
    tipo = sretro(matriz,n,x);
    if(tipo == 2){
        printf("Sistema Linear Incompativel");
    }

    else{
        printf("\nSL %sDeterminado\n", tipo ? "IN" : "");
        for(i = 0; i < n; i++){
            printf("x[%d] = %10.3lf\n",colunas[i], x[i]);
        }

    }



}





int main(){
    char op;
    FILE *file;
    char *fileName;
    fileName = malloc(sizeof(char)*35);

    if(fileName == NULL){
        printf("Falta de memoria");
    }



    while(op != 'F'){
        printf("C - Conversao \n");
        printf("S - Sistema Linear \n");
        printf("E - Equaçao Algébrica \n");
        printf("F - Finalizar \n\n");
        printf("Escolha uma opcao\n\n");
        fflush(stdin);
        fpurge(stdin);
        scanf("%c",&op);
        if(op == 'C'){
            ConverteNumero();
            printf("\n\n");
        }
        else if(op == 'S'){
            fflush(stdin);
            fpurge(stdin);
            printf("digite o nome do arquivo \n");
            gets(fileName);
            strcat(fileName,".txt\0");
            file = fopen(fileName,"r");

            if(file == NULL){
                printf("Arquivo nao encontrado\n\n");
            }

            else{
                printf("Arquivo Encontrado \n");
                SistemaLinear(file);
            }

        }

        else if(op == 'E'){
            printf("Equacao Algebrica \n\n\n");
        }

        else if(op == 'F'){
            printf("Programa Finalizado");
            break;
        }
        else{
            printf("Digite uma opcao valida \n\n\n");
        }

    }

    return 0;
}






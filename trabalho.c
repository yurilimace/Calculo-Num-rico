#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EPSILON 0.000001

void converteOctal(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m;
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
        printf("%d",(int) aux);
    }
}

// Conversão para binário feito
void converteBinario(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m;
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
        printf("%d",(int) aux);
    }
}

void converteHexa(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m;
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
        if((int) aux == 10){
            printf("A");
        }
        else if((int) aux ==11){
                printf("B");
        }
        else if((int) aux == 12){
                printf("C");
        }
        else if((int) aux ==13){
                printf("D");
        }
        else if((int) aux ==14){
                printf("E");
        }
        else if((int) aux == 15){
                printf("F");
        }
        else{
            printf("%d",(int) aux);
        }
    }
}

void converteNumero(){
    int i,j;
    double teste;
    int parteInteira;
    double parteFracionaria;
    int  *resultado; //Armazena o resultado das sucessivas divisões

    printf("Digite o numero decimal ");
    scanf("%lf",&teste);

    parteInteira = floor(teste);
    parteFracionaria = teste - parteInteira;

    resultado = malloc(sizeof(resultado)*30);

    if(resultado == NULL){
        printf("Não alocado Falta de memoria");
    }


    converteBinario(parteInteira,parteFracionaria,resultado);
    printf("\n");
    converteOctal(parteInteira,parteFracionaria,resultado);
    printf("\n");
    converteHexa(parteInteira,parteFracionaria,resultado);
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



void sistemaLinear(FILE *file){
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

float calculaL(int grau,int coeficientes[]){

    //n: grau do polinomio
    int n=grau;

    // k: maior índice dentre os índices dos coeficientes negativos
    // b: módulo  do menor coeficiente negativo
    // an: coeficiente do x?n
    int an,b,k,i;

    b = 0;
    k = 0;
    an = coeficientes[n];

    for(i=grau;i>=0;i--){

        if(coeficientes[i]<b){
            b=coeficientes[i];
        }

        if(coeficientes[i]<0 && i>k){
            k=i;
        }
    }

    b = b*(-1);

    // Formula do calculo do L
    return 1 + pow(((float)b/(float)an),1/(n-k));
}

void lagrange(int grau,int coeficientes[]){

    int i,j;
    int coeficientes2[grau+1];
    float Ls[4];

    // calculo do L 
    for(i=grau;i>=0;i--){
        coeficientes2[i] = coeficientes[i];
    }

    if(coeficientes2[grau]<0){
        for(i=grau;i>=0;i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[0] = calculaL(grau,coeficientes2);

    // calculo do L1
    j=0;
    for(i=grau;i>=0;i--){
        coeficientes2[i] = coeficientes[j];
        j = j+1;
    }

    if(coeficientes2[grau]<0){
        for(i=grau;i>=0;i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[1] = calculaL(grau,coeficientes2);

    // calculo do L2
    for(i=grau;i>=0;i--){
        coeficientes2[i] = coeficientes[i];
        if(i%2!=0){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    if(coeficientes2[grau]<0){
        for(i=grau;i>=0;i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[2] = calculaL(grau,coeficientes2);

    // calculo do L3
    j=0;
    for(i=grau;i>=0;i--){
        coeficientes2[i] = coeficientes[j];
        if(i%2!=0){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
        j = j+1;
    }

    if(coeficientes2[grau]<0){
        for(i=grau;i>=0;i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[3] = calculaL(grau,coeficientes2);

    //printf("\nLs: %f ; %f ; %f ; %f ",Ls[0],Ls[1],Ls[2],Ls[3]);

    printf("\n Intervalo onde se encontram as raizes reais positivas:");
    printf("\n %.6f <= X+ <= %.6f ",1/Ls[1],Ls[0]);
    printf("\n\n Intervalo onde se encontram as raizes reais negativas:");
    printf("\n %.6f <= X- <= %.6f ",Ls[2]*(-1),(-1/Ls[3]));

}

void equacaoAlgebrica(){
    int grau=1;
    int i;

    printf("Digite o grau da equacao: ");
    scanf("%i",&grau);

    int coeficientes[grau+1];

    for(i=grau;i>=0;i--){
        printf("\nDigite o coeficiente a%i: ",i);
        scanf("%i",&coeficientes[i]);

        if((i==grau) && (coeficientes[i]<=0)){

            printf("\nCoeficiente an digitado eh menor que zero. Tente novamente com outro valor.\n");
            i = grau + 1;
        }

        if((i==0) && (coeficientes[i]==0)){

            printf("\nCoeficiente a0 digitado eh igual a zero. Tente novamente com outro valor.\n");
            i = i + 1;
        }
    }
    lagrange(grau,coeficientes);
}



int main(){
    char entradaUsuario;
    FILE *file;
    char *fileName;
    fileName = malloc(sizeof(char)*35);

    if(fileName == NULL){
        printf("Falta de memoria");
    }

    while(entradaUsuario != 'F'){
        printf("C - Conversao \n");
        printf("S - Sistema Linear \n");
        printf("E - Equaçao Algébrica \n");
        printf("F - Finalizar \n\n");
        printf("Escolha uma opcao\n\n");
        //Limpar o buffer no Windows
        fflush(stdin);
        //Limpar o buffer no Linux
        fpurge(stdin);
        scanf("%c",&entradaUsuario);
        if(entradaUsuario == 'C'){
            converteNumero();
            printf("\n\n");
        }
        else if(entradaUsuario == 'S'){
            //Limpar o buffer no Windows
            fflush(stdin);
            //Limpar o buffer no Linux
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
                sistemaLinear(file);
            }
        }

        else if(entradaUsuario == 'E'){
            equacaoAlgebrica();
            printf("\n\n");
        }

        else if(entradaUsuario == 'F'){
            printf("Programa Finalizado");
            break;
        }
        else{
            printf("Digite uma opcao valida \n\n\n");
        }

    }

    return 0;
}

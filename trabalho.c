#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EPSILON 0.000001


/* Exercício Programa da Disciplina Calculo Numérico Tarde
   Curso Engenharia da Computação   */



/* Autores
    Angelo
    Italo Bruno
    João Gabriel
    José Yuri
    Luan Pontes
*/


/*  O programa desenvolvido abaixo visa implementar na linguagem C alguns conteudos abordados em sala como a conversão
    de base numerica,resolução de sistemas lineares utilizando o metodo de Jordan,Teorema de Lagrange para exibir o in-
    tervalo onde se encontram as raizes reais negativas e positivas da equação,Assim como o Teorema de Bolzano para a ve-
    rificações de raizes impares e o metodo da bisseção para calcular uma aproximação para a raiz contida nesse intervalo  */

/* o Programa funciona da seguinte maneira ao selecionar C o usuário digita um numero inteiro para ser realizada a conversão
 para a base binária,octal e hexadecimal, ao selecionar S o usuário deve digitar o nome do arquivo que contém a matriz aumentada
 para a resolução do sistema linear que será resolvido utilizando o metodo de jordan para triagularizar a matriz e a substituição
 retroativa para a resolução do sistema, ao selecionar E o usuário digita o grau da equação e também os coeficentes*/



void limpaBuffer(){
    /*Função criada para poder executar o comando de limpeza do buffer do teclado nos seguintes sistemas operacionais
    Linux, Windows e IOS*/
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        fpurge(stdin);
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        fflush(stdin);
    #endif


}


/* Funções necessarias para a conversão de base numérica*/


void converteOctal(int Inteiro,double Fracionario,int *resultado){
    /*Converte o numero digitado pelo usuario para a base octal*/
    int i,j,k,m; //variaveis
    double aux;

    for(i=0;Inteiro>=1;i++){
        resultado[i] = Inteiro % 8;
        Inteiro = Inteiro / 8;
    }

    for(j = i-1;j>=0;j--){
        printf("%d",resultado[j]);
    }
    printf(",");
    //laço para calcular a parte fracionária da conversão parando quando for 0 ou quando a parte fracionaria atingir a precisão de 20 casas decimais
    for(k =0;Fracionario!=0 && k<=19;k++){
        Fracionario = Fracionario * 8;
        Fracionario = modf(Fracionario,&aux);
        printf("%d",(int) aux);
    }
}

/*Converte o numero digitado pelo usuario para a base binaria*/
void converteBinario(int Inteiro,double Fracionario,int *resultado){
    int i,j,k,m; //variaveis
    double aux;

    for(i=0;Inteiro>=1;i++){
        resultado[i] = Inteiro % 2;
        Inteiro = Inteiro / 2;
    }

    for(j = i-1;j>=0;j--){
        printf("%d",resultado[j]);
    }
    printf(",");
    //laço para calcular a parte fracionária da conversão parando quando for 0 ou quando a parte fracionaria atingir a precisão de 20 casas decimais
    for(k =0;Fracionario!=0 && k<=19;k++){
        Fracionario = Fracionario * 2;
        Fracionario = modf(Fracionario,&aux);
        printf("%d",(int) aux);
    }
}

void converteHexa(int Inteiro,double Fracionario,int *resultado){
    /*Converte o numero digitado pelo usuario para a base hexadecimal*/
    int i,j,k,m;
    double aux;

    for(i=0;Inteiro>=1;i++){
        resultado[i] = Inteiro % 16;
        Inteiro = Inteiro / 16;
    }
    //substitui para o caracter correspondente na base hexadecimal quando o numero foi maior que 9
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
    //laço para calcular a parte fracionária da conversão parando quando for 0 ou quando a parte fracionaria atingir a precisão de 20 casas decimais
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
    /*Função que agrupa e chama os outros metodos para conversão de base numerica*/
    int i,j;
    double numero;
    int parteInteira;
    double parteFracionaria;
    int  *resultado; //Armazena o resultado das sucessivas divis˜es

    printf("Digite o numero decimal ");
    scanf("%lf",&numero);

    parteInteira = floor(numero); //armazena a parte inteira do numero
    parteFracionaria = numero - parteInteira;

    resultado = malloc(sizeof(resultado)*30);

    if(resultado == NULL){
        printf("N˜o alocado Falta de memoria");
    }


    converteBinario(parteInteira,parteFracionaria,resultado);
    printf("\n");
    converteOctal(parteInteira,parteFracionaria,resultado);
    printf("\n");
    converteHexa(parteInteira,parteFracionaria,resultado);
    printf("\n");
}

/* Fim das funções necessárias para a realização da conversão de base*/


double **alocaMatriz(int numLinhas, int numColunas){
    /*Se tiver mem˜ria dispon˜vel, aloca uma matriz de double com L linhas e c Colunas
      e devolve um ponteiro para essa matriz; Caso contr˜rio, devolve um ponteiro nulo.*/
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
                  aux = m[p][i];  /* faz a troca dos elementos da coluna*/
                  m[p][i] = m[p][j];
                  m[p][j] = aux;
               }
               /*troca o coeficiente das colunas em que foi necessário a troca */
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
    /*Recebe m, a matriz aumentada de um SL TS com n vari˜veis.
    Se o SL for determinado, armazena em x a solu˜˜o do SL e dovolve 0;
    Se for indeterminado, armazena uma solu˜˜o do SL e devolve 1;*/
    int i, j, tipo = 0;
    double soma;
    for(i = n - 1; i >= 0; i--){
        soma = 0;
        for(j = i + 1; j < n; j++){
            soma += m[i][j] * x[j];
        }
        if(m[i][i] == 0){
            if(fabs(m[i][n] - soma) < EPSILON){
                x[i] = 0; //Vari˜vel Livre
                tipo = 1;
            }
            else{
                return 2; //SL incompat˜vel
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

    // k: maior ˜ndice dentre os ˜ndices dos coeficientes negativos
    // b: m˜dulo  do menor coeficiente negativo
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
    return 1 + pow(((float)b/(float)an), 1/(float)(n-k));
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

int bolzano(float a,float b,int coeficientes[],int grau){

    float pa = 0;
    float pb = 0;
    int i;

    for(i=grau;i>=0;i--){

        pa = pa + ((float)coeficientes[i] * (float)pow(a,i));
        pb = pb + ((float)coeficientes[i] * (float)pow(b,i));

    }

    if((pa*pb)<0){

        return 1;

    }
    if((pa*pb)>0){

        return 0;

    }

}

void bissecao(float a, float b,int coeficientes[],int grau){

    double pa,pb,pm,m,erro,a2,b2;
    int i,j;

    j=0;
    a2 = a;
    b2 = b;

    erro = (double)(b2-a2)/(double)2;

    while(j<1001 && erro>=pow(10,-8)){

        pa = 0;
        pb = 0;
        pm = 0;
        m = (b2+a2)/(double)2;
        erro = (b2-a2)/(double)2;

        for(i=grau;i>=0;i--){

            pa = pa + ((double)coeficientes[i] * (double)pow(a2,i));
            pb = pb + ((double)coeficientes[i] * (double)pow(b2,i));

        }

        for(i=grau;i>=0;i--){

            pm = pm + ((double)coeficientes[i] * (double)pow(m,i));

        }

        if(pa*pm>0){
            a2=m;
        }
        if(pa*pm<0){
            b2=m;
        }
        if(pa*pm==0){
            j = 10000;
        }

        j = j+1;

    }

    printf("\n\n Raiz aproximada do polinomio: %.30lf \n Valor do erro: %.30lf",m,erro);

}


void equacaoAlgebrica(){

    int grau=1;
    int i,j,contador;
    float a,b;

    printf("\n Digite o grau da equacao: ");
    scanf("%i",&grau);

    while(grau==0) {
        printf("O grau nao pode ser zero.\n");
        printf("\n Digite o grau da equacao: "); 
        scanf("%i",&grau);
    }

    int coeficientes[grau+1];

    for(i=grau;i>=0;i--){

        printf("\n  Digite o coeficiente a%i: ",i);
        scanf("%i",&coeficientes[i]);

        if((i==grau) && (coeficientes[i]<=0)){

            printf("\n  ERRO: Coeficiente an digitado eh menor que zero. Tente novamente com outro valor.\n");
            i = grau + 1;

        }

        if((i==0) && (coeficientes[i]==0)){

            printf("\n  ERRO: Coeficiente a0 digitado eh igual a zero. Tente novamente com outro valor.\n");
            i = i + 1;

        }

        if(i==0){

            contador = 0;

            for(j=grau;j>=0;j--){

                if(coeficientes[j]>=0){

                    contador = contador + 1;

                }

            }

            if(contador==grau+1){

                printf("\n  ERRO: Todos os coeficientes digitados sao positivos. Necessario haver pelo menos um coeficiente negativo. Tente novamente com outros valores.\n");
                i = grau+1;

            }

        }

    }

    // calculo dos limites das ra˜zes usando o teorema de lagrange

    printf("\n -> Teorema de Lagrange: \n");

    lagrange(grau,coeficientes);

    //verificando se a quantidade de ra˜zes ˜ ˜mpar ou par usando o Teorema de Bolzano

    printf("\n\n -> Teorema de Bolzano: \n");
    printf("\n  Escolha um intervalo");
    printf("\n\n   Digite o primeiro valor do intervalo: ");
    scanf("%f",&a);
    printf("   Digite o ultimo valor do intervalo: ");
    scanf("%f",&b);

    if(bolzano(a,b,coeficientes,grau)==0){

        printf(" \n  O polinomio possui uma quantidade par de raizes reais no intervalo [%f,%f]",a,b);

    }
    if(bolzano(a,b,coeficientes,grau)==1){

        printf(" \n  O polinomio possui uma quantidade impar de raizes reais no intervalo [%f,%f]",a,b);

        printf("\n\n -> Metodo da Bissecao:");

        bissecao(a,b,coeficientes,grau);

    }

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
        printf("E - Equa˜ao Alg˜brica \n");
        printf("F - Finalizar \n\n");
        printf("Escolha uma opcao\n\n");
        //Limpar o buffer no Windows
        limpaBuffer();
        //Limpar o buffer no Linux
        //fpurge(stdin);
        scanf("%c",&entradaUsuario);
        if(entradaUsuario == 'C' || entradaUsuario == 'c'){
            converteNumero();
            printf("\n\n");
        }
        else if(entradaUsuario == 'S' || entradaUsuario == 's'){
            //Limpar o buffer no Windows
            limpaBuffer();
            //Limpar o buffer no Linux
            //fpurge(stdin);
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

        else if(entradaUsuario == 'E' || entradaUsuario == 'e'){
            equacaoAlgebrica();
            printf("\n\n");
        }

        else if(entradaUsuario == 'F'|| entradaUsuario == 'f'){
            printf("Programa Finalizado");
            break;
        }
        else{
            printf("Digite uma opcao valida \n\n\n");
        }

    }

    return 0;
}

/*  
    Exercício Programa da Disciplina Cálculo Numérico - Tarde
    Curso: Engenharia da Computação.

    Autores:
    Angelo Lopes
    Italo Bruno
    João Gabriel
    José Yuri
    Luan Pontes

    O algoritmo desenvolvido abaixo visa implementar na linguagem C os seguintes conteúdos abordados em sala:
    - Conversão de base numérica (binária, octal e hexadecimal).
    - Resolução de sistemas lineares utilizando o método de Jordan.
    - Teorema de Lagrange para exibir o intervalo onde se encontra as raízes reais negativas e positivas de uma equação.
    - Teorema de Bolzano para a verificações de raizes impares.
    - Método da bisseção para calcular uma aproximação para a raíz contida nesse intervalo.
*/

//Importação de bibliotecas e definição de constantes que serão utilizadas no algoritmo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EPSILON 0.000001

//=============================== Função auxiliar ===============================
void limpaBuffer(){
    /*
        Função que possibilita executar o comando de limpeza do buffer do teclado 
        nos seguintes sistemas operacionais: Linux, Windows e IOS.
    */
    #if defined(__linux__) || defined(__unix__)
        __fpurge(stdin);
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        fflush(stdin);
    #endif

    #if defined(__APPLE__)
        fpurge(stdin);
    #endif
}//Fim da função limpaBuffer()

/*
    ============================= Conversão de bases numéricas =============================
    Funções:
    1 - converteOctal(int parteInteira, double parteFracionaria, int *resultadoConversao):
        converte o número digitado pelo usuário para a base octal.

    2 - converteBinario(int parteInteira, double parteFracionaria, int *resultadoConversao): 
        converte o número digitado pelo usuário para a base binária.

    3 - converteHexa(int parteInteira, double parteFracionaria, int *resultadoConversao):    
        converte o número digitado pelo usuário para a base hexadecimal.

    4 - converteNumero(): 
        Função que agrupa e chama os outros métodos para conversão de base numérica.
*/

void converteOctal(int parteInteira,double parteFracionaria, int *resultadoConversao){
    /*
        Função que converte o número digitado pelo usuário para a base octal.
    */
    //Variáveis que serão utilizadas.
    int i, j, k; 
    double aux;
    /*
        Verificação se o número <= 0. Caso seja 0, o número 0 será printado e a função finalizada.
        Caso seja negativo, converto para positivo, printo o sinal "-" e continuo a função normalmente. 
    */
    if(parteInteira == 0){
        printf("0");
        return;
    }
    if(parteInteira < 0){
        parteInteira = parteInteira * -1;
        printf("-");
    }

    for(i = 0; parteInteira >= 1; i++){
        resultadoConversao[i] = parteInteira % 8;
        parteInteira = parteInteira / 8;
    }

    for(j = i-1; j >= 0; j--){
        printf("%d", resultadoConversao[j]);
    }
    if(parteFracionaria > 0)
        printf(",");
    /*
        Laço para calcular a parte fracionária da conversão parando quando for 0 ou 
        quando a parte fracionária atingir a precisão de 20 casas decimais.
    */
    for(k = 0; parteFracionaria != 0 && k <= 19; k++){
        parteFracionaria = parteFracionaria * 8;
        parteFracionaria = modf(parteFracionaria, &aux);
        printf("%d", (int) aux);
    }
}//Fim da função converteOctal()

void converteBinario(int parteInteira,double parteFracionaria,int *resultadoConversao){
    /*
        Função que converte o número digitado pelo usuario para a base binária.
    */
    //Variáveis que serão utilizadas.
    int i, j, k; 
    double aux;
    /*
        Verificação se o número <= 0. Caso seja 0, o número 0 será printado e a função finalizada.
        Caso seja negativo, converto para positivo, printo o sinal "-" e continuo a função normalmente. 
    */
    if(parteInteira == 0){
        printf("0");
        return;
    }
    if(parteInteira < 0){
        parteInteira = parteInteira * -1;
        printf("-");
    }

    for(i = 0; parteInteira >= 1; i++){
        resultadoConversao[i] = parteInteira % 2;
        parteInteira = parteInteira / 2;
    }

    for(j = i-1; j >= 0; j--){
        printf("%d", resultadoConversao[j]);
    }
    if(parteFracionaria > 0)
        printf(",");
    /* 
        Laço para calcular a parte fracionária da conversão parando quando for 0 ou quando a 
        parte fracionária atingir a precisão de 20 casas decimais.
    */
    for(k = 0; parteFracionaria != 0 && k <= 19; k++){
        parteFracionaria = parteFracionaria * 2;
        parteFracionaria = modf(parteFracionaria, &aux);
        printf("%d", (int) aux);
    }
}//Fim da função converteBinario()

void converteHexa(int parteInteira,double parteFracionaria,int *resultadoConversao){
    /*
        Converte o numero digitado pelo usuario para a base hexadecimal.
    */
    //Variáveis que serão utilizadas.
    int i, j, k; 
    double aux;
    /*
        Verificação se o número <= 0. Caso seja 0, o número 0 será printado e a função finalizada.
        Caso seja negativo, converto para positivo, printo o sinal "-" e continuo a função normalmente. 
    */
    if(parteInteira == 0){
        printf("0");
        return;
    }
    if(parteInteira < 0){
        parteInteira = parteInteira * -1;
        printf("-");
    }

    for(i = 0; parteInteira >= 1; i++){
        resultadoConversao[i] = parteInteira % 16;
        parteInteira = parteInteira / 16;
    }
    //Substitui para o caractere correspondente na base hexadecimal quando o número foi maior que 9.
    for(j = i-1; j >= 0 ; j--){
        if(resultadoConversao[j] == 10){
            printf("A");
        }
        else if(resultadoConversao[j]==11){
                printf("B");
        }
        else if(resultadoConversao[j]==12){
                printf("C");
        }
        else if(resultadoConversao[j]==13){
                printf("D");
        }
        else if(resultadoConversao[j]==14){
                printf("E");
        }
        else if(resultadoConversao[j]==11){
                printf("F");
        }
        else{
            printf("%d",resultadoConversao[j]);
        }
    }
    if(parteFracionaria > 0)
        printf(",");
    /*
        Laço para calcular a parte fracionária da conversão parando quando for 0 ou quando 
        a parte fracionária atingir a precisão de 20 casas decimais.
    */
    for(k = i; parteFracionaria != 0 && k <= 19; k++){
        parteFracionaria = parteFracionaria * 16;
        parteFracionaria = modf(parteFracionaria, &aux);
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
            printf("%d", (int) aux);
        }
    }
}//Fim da função converteHexa()

void converteNumero(){
    /*
        Função que agrupa e chama os outros métodos para conversão de base numérica
    */
    //Variáveis que serão utilizadas
    int i, j;
    double numero;
    int parteInteira;
    double parteFracionaria;
    int  *resultadoConversao; //Armazena o resultadoConversao das sucessivas divisões

    printf("Digite um número: ");
    scanf("%lf", &numero);

    parteInteira = floor(numero); //armazena a parte inteira do número
    parteFracionaria = numero - parteInteira;

    resultadoConversao = malloc(sizeof(resultadoConversao) * 30);

    if(resultadoConversao == NULL){
        printf("\nNão alocado - Falta de mémoria\n");
    }

    printf("\nNúmero %lf em binário: ", numero);
    converteBinario(parteInteira, parteFracionaria, resultadoConversao);
    printf("\n");
    printf("Número %lf em octal: ", numero);
    converteOctal(parteInteira, parteFracionaria, resultadoConversao);
    printf("\n");
    printf("Número %lf em hexadecimal: ", numero);
    converteHexa(parteInteira, parteFracionaria, resultadoConversao);
    printf("\n");
}//Fim da função converteNumero()

/*
    ==================== Resolução de sistemas lineares usando o método de Jordan ====================
    Funções:
    1 - double **alocaMatriz(int numLinhas, int numColunas):
        aloca uma matriz de double com L linhas e c Colunas e devolve um ponteiro para essa matriz.

    2 - void lerMatriz(double **matriz, int numLinhas, int numColunas):
        Ler valores para uma matriz alocada dinamicamente de double com L linhas e C colunas.

    3 - void imprimirMatriz(double **matriz, int numLinhas, int numColunas):
        Imprime valores de uma matriz alocada dinamicamente de double com L linhas e C colunas.

    4 - void jordan(double **m,int n, int *colunas):
        Resolve o sistema linear através do método de jordan, na qual se obtém um SL equivalente 
        que seja diagonal.

    5 - int sretro(double **m, int n, double x[]):
    Recebe m, a matriz aumentada de um SL TS com n variáveis.
    Se o SL for determinado, armazena em x a solução do SL e dovolve 0;
    Se for indeterminado, armazena uma solução do SL e devolve 1.

    6 - void sistemaLinear(FILE *file):
    Função que agrupa e chama os outros métodos para a resolução do SL através do método de jordan.

*/

double **alocaMatriz(int numLinhas, int numColunas){
    /*
        Se tiver memória disponível, aloca uma matriz de double com L linhas e c Colunas
        e devolve um ponteiro para essa matriz; Caso contrário, devolve um ponteiro nulo.
    */
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
}//Fim da função alocaMatriz()

void lerMatriz(double **matriz, int numLinhas, int numColunas){
    /*
        Ler valores para uma matriz alocada dinamicamente de double com L linhas e C colunas
    */
    int i, j;
    for(i = 0; i < numLinhas; i++){
        for(j = 0; j < numColunas; j++){
            printf("m[%d][%d] = ", i + 1, j + 1);
            scanf("%lf", &matriz[i][j]);
        }
    }
}//Fim da função lerMatriz()

void imprimirMatriz(double **matriz, int numLinhas, int numColunas){
    /*
        Imprime valores de uma matriz alocada dinamicamente de double com L linhas e C colunas
    */
    int i, j;
    for(i = 0; i < numLinhas; i++){
        for(j = 0; j < numColunas; j++){
            printf("%10.3lf", matriz[i][j]);
        }
        printf("\n");
    }
}//Fim da função imprimirMatriz()

void jordan(double **m, int n, int *colunas){
    int i, j, k, p, aux;
    double mult;
    for(i = 0; i < n; i++){
        if (m[i][i] == 0){
            j = i + 1;
            while(j < n && m[i][j] == 0){
                j++;
            }
            if(j < n){
               for(p = 0; p < n; p++){
                  aux     = m[p][i];  /* faz a troca dos elementos da coluna*/
                  m[p][i] = m[p][j];
                  m[p][j] = aux;
               }
               /*troca o coeficiente das colunas em que foi necess�rio a troca */
               aux        = colunas[i];
               colunas[i] = colunas[j];
               colunas[j] = aux;
            }
            else{
                for(k = 0; k < n; k++){
                    m[k][i] = 0;
                }
            }
        }
        if(m[i][i] != 0){
            for(j = 0; j < n; j++){
                if(j != i){
                    mult = m[j][i] / m[i][i];
                    for(k = 0; k < n + 1; k++){
                        m[j][k] = m[j][k] - (mult * m[i][k]);
                    }
                }
            }
        }
    }
}//Fim da função jordan()

int sretro(double **m, int n, double x[]){
    /*
        Recebe m, a matriz aumentada de um SL TS com n variáveis.
        Se o SL for determinado, armazena em x a solução do SL e dovolve 0;
        Se for indeterminado, armazena uma solução do SL e devolve 1
    */
    int i, j, tipo = 0;
    double soma;
    for(i = n - 1; i >= 0; i--){
        soma = 0;
        for(j = i + 1; j < n; j++){
            soma += m[i][j] * x[j];
        }
        if(m[i][i] == 0){
            if(fabs(m[i][n] - soma) < EPSILON){
                x[i] = 0; //Vari�vel Livre
                tipo = 1;
            }
            else{
                return 2; //SL incompat�vel
            }
        }
        else{
            x[i] = (m[i][n] - soma)/m[i][i];
        }
    }
    return tipo;
}//Fim da sretro()

void sistemaLinear(FILE *file){
    /*
        Função que agrupa e chama os outros métodos para a resolução do SL através do método de jordan.
    */
    double **matriz, *x;
    int n, i, j, tipo;
    int *colunas;
    fscanf(file, "%d \r\n", &n);
    printf("%d \r\n", n);
    matriz = alocaMatriz(n, n+1);
    x = malloc(sizeof(double) * n);

    if(matriz == NULL || x == NULL){
        printf("Memória Insuficiente");
    }

    colunas = malloc(sizeof(int)*n);

    if(colunas == NULL){
        printf("Memória Insuficiente");
    }


    for(i = 0 ;i < n ;i++){
        colunas[i] = i+1;
    }

    for ( i = 0 ; i < n ; i++ ){
         for(j = 0 ; j < n+1 ; j++){
            fscanf(file, "%lf", &matriz[i][j]);
         }
    }

    imprimirMatriz(matriz, n, n+1);
    jordan(matriz, n, colunas);
    printf("matriz triagularizada: \n\n\n");
    imprimirMatriz(matriz, n, n+1);
    tipo = sretro(matriz, n, x);
    if(tipo == 2){
        printf("Sistema Linear Incompativel");
    }

    else{
        printf("\nSL %sDeterminado\n", tipo ? "IN" : "");
        for(i = 0; i < n; i++){
            printf("x[%d] = %10.3lf\n", colunas[i], x[i]);
        }
    }
}//Fim da função sistemaLinear()

/*
    =============================== Resolução de equação algébrica ===============================
    Funções:
    1 - calculaL(int grau, int coeficientes[]):
        Função que calcula os Ls para usar na fórmula de lagrange.
    
    2 - lagrange(int grau, int coeficientes[]):
        Função que calcula os intervalos das raízes positivas e negativas.

    3 - int bolzano(float a, float b, int coeficientes[], int grau):
        Função que calcula se a quantidade de raízes é par, impar ou se não possue raiz.

    4 - void bissecao(float a, float b, int coeficientes[], int grau):
        Função que calcula uma raíz aproximada do polinômio.

    5 - void equacaoAlgebrica():
        Função que agrupa e chama os outros métodos para a resolução da equação algébrica.
*/

float calculaL(int grau, int coeficientes[]){
    /*
        Função que calcula os Ls para usar na fórmula de lagrange.
    */

    //n: grau do polinômio
    int n = grau;
    // k: maior índice dentre os índices dos coeficientes negativos
    // b: módulo  do menor coeficiente negativo
    // an: coeficiente do xn
    int an, b, k, i;

    b = 0;
    k = 0;
    an = coeficientes[n];

    for(i = grau; i >= 0; i--){

        if(coeficientes[i] < b){
            b = coeficientes[i];
        }

        if(coeficientes[i] < 0 && i > k){
            k = i;
        }
    }

    b = b * (-1);

    // Fórmula do cálculo do L
    return 1 + pow(((float)b/(float)an), 1/(float)(n-k));
}//Fim da função calculaL()

void lagrange(int grau, int coeficientes[]){
    /*
        Função que calcula os intervalos das raízes positivas e negativas.
    */
    int i, j;
    int coeficientes2[grau + 1];
    float Ls[4];

    // calculo do L
    for(i = grau; i >= 0; i--){
        coeficientes2[i] = coeficientes[i];
    }

    if(coeficientes2[grau] < 0){
        for(i = grau; i >= 0; i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[0] = calculaL(grau, coeficientes2);

    // calculo do L1
    j = 0;
    for(i = grau; i >= 0; i--){
        coeficientes2[i] = coeficientes[j];
        j = j + 1;
    }

    if(coeficientes2[grau] < 0){
        for(i = grau; i >= 0; i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[1] = calculaL(grau, coeficientes2);

    // calculo do L2
    for(i = grau; i >= 0; i--){
        coeficientes2[i] = coeficientes[i];
        if(i%2 != 0){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    if(coeficientes2[grau] < 0){
        for(i = grau; i >= 0; i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[2] = calculaL(grau, coeficientes2);

    // calculo do L3
    j = 0;
    for(i = grau; i >= 0; i--){
        coeficientes2[i] = coeficientes[j];
        if(i%2 != 0){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
        j = j + 1;
    }

    if(coeficientes2[grau] < 0){
        for(i = grau; i >= 0; i--){
            coeficientes2[i] = coeficientes2[i] * (-1);
        }
    }

    Ls[3] = calculaL(grau, coeficientes2);

    printf("\n Intervalo onde se encontram as raizes reais positivas: ");
    printf("\n %.6f <= X+ <= %.6f ", 1/Ls[1], Ls[0]);
    printf("\n\n Intervalo onde se encontram as raizes reais negativas:");
    printf("\n %.6f <= X- <= %.6f ", Ls[2]*(-1), (-1/Ls[3]));

}//Fim da função lagrange()

int bolzano(float a, float b, int coeficientes[], int grau){
    /*
        Função que calcula se a quantidade de raízes é par, impar ou se não possue raiz.
    */

    float pa = 0;
    float pb = 0;
    int i;

    for(i = grau; i >= 0; i--){

        pa = pa + ((float)coeficientes[i] * (float)pow(a,i));
        pb = pb + ((float)coeficientes[i] * (float)pow(b,i));

    }

    if((pa * pb) < 0){
        return 1;
    }
    if((pa * pb) > 0){
        return 0;
    }
}//Fim da função bolzano()

void bissecao(float a, float b, int coeficientes[], int grau){
    /*
        Função que calcula uma raíz aproximada do polinômio.
    */

    double pa, pb, pm, m, erro, a2 = a, b2 = b;
    int i, j = 0;
    erro = (double)(b2-a2)/(double)2;

    while(j < 1001 && erro >= pow(10,-8)){
        pa = 0;
        pb = 0;
        pm = 0;
        m  = (b2+a2)/(double)2;
        erro = (b2-a2)/(double)2;

        for(i = grau; i >= 0; i--){
            pa = pa + ((double)coeficientes[i] * (double)pow(a2,i));
            pb = pb + ((double)coeficientes[i] * (double)pow(b2,i));
        }

        for(i = grau; i >= 0; i--){
            pm = pm + ((double)coeficientes[i] * (double)pow(m,i));
        }
        if(pa * pm > 0){
            a2 = m;
        }
        if(pa * pm < 0){
            b2 = m;
        }
        if(pa * pm == 0){
            j = 10000;
        }
        j = j+1;
    }

    printf("\n\n Raiz aproximada do polinomio: %.30lf \n Valor do erro: %.30lf",m,erro);

}//Fim da função bissecao()

void equacaoAlgebrica(){
    /*
        Função que agrupa e chama os outros métodos para a resolução da equação algébrica.
    */
    int grau = 1;
    int i, j, contador;
    float a, b;

    printf("\nDigite o grau da equação: ");
    scanf("%i", &grau);

    while(grau == 0) {
        printf("O grau não pode ser zero.\n");
        printf("\nDigite o grau da equação: "); 
        scanf("%i", &grau);
    }

    int coeficientes[grau + 1];

    for(i = grau; i >= 0; i--){

        printf("\nDigite o coeficiente a%i: ",i);
        scanf("%i", &coeficientes[i]);

        if((i == grau) && (coeficientes[i] <= 0)){
            printf("\nERRO: Coeficiente an digitado é menor que zero. Tente novamente com outro valor.\n");
            i = grau + 1;
        }

        if((i==0) && (coeficientes[i]==0)){
            printf("\nERRO: Coeficiente a0 digitado é igual a zero. Tente novamente com outro valor.\n");
            i = i + 1;
        }

        if(i == 0){
            contador = 0;
            for(j = grau; j >= 0; j--){
                if(coeficientes[j] >= 0){
                    contador = contador + 1;
                }
            }
            if(contador == grau + 1){
                printf("\n  ERRO: Todos os coeficientes digitados são positivos. Necessário haver pelo menos um coeficiente negativo. Tente novamente com outros valores.\n");
                i = grau + 1;
            }
        }
    }

    // Cálculo dos limites das raízes usando o teorema de lagrange

    printf("\n-> Teorema de Lagrange: \n");

    lagrange(grau, coeficientes);

    //Verificando se a quantidade de raízes é ímpar ou par usando o Teorema de Bolzano
    printf("\n\n -> Teorema de Bolzano: \n");
    printf("\n  Escolha um intervalo");
    printf("\n\n   Digite o primeiro valor do intervalo: ");
    scanf("%f", &a);
    printf("   Digite o ultimo valor do intervalo: ");
    scanf("%f", &b);

    if(bolzano(a, b, coeficientes,grau) == 0){
        printf(" \n  O polinomio possui uma quantidade par de raizes reais no intervalo [%f,%f]",a,b);
    }
    if(bolzano(a, b, coeficientes, grau) == 1){
        printf(" \n  O polinomio possui uma quantidade impar de raizes reais no intervalo [%f,%f]",a,b);
        printf("\n\n -> Metodo da Bissecao:");
        bissecao(a, b, coeficientes, grau);
    }
}//Fim da função equacaoAlgebrica()

//=============================== Função Principal ===============================
int main(){
    char entradaUsuario;
    FILE *file;
    char *fileName;
    fileName = malloc(sizeof(char)*35);

    if(fileName == NULL){
        printf("Falta de memória");
    }

    while(entradaUsuario != 'F'){
        printf("C - Conversão \n");
        printf("S - Sistema Linear \n");
        printf("E - Equação Algébrica \n");
        printf("F - Finalizar \n\n");
        printf("Escolha uma opcao: ");
        //Limpar o buffer no Windows
        limpaBuffer();
        scanf("%c", &entradaUsuario);
        if(entradaUsuario == 'C' || entradaUsuario == 'c'){
            converteNumero();
            printf("\n\n");
        }
        else if(entradaUsuario == 'S' || entradaUsuario == 's'){
            //Limpar o buffer no Windows
            limpaBuffer();
            printf("Digite o nome do arquivo: ");
            gets(fileName);
            strcat(fileName,".txt\0");
            file = fopen(fileName,"r");

            if(file == NULL){
                printf("Arquivo não encontrado!!!\n\n");
            }
            else{
                printf("Arquivo Encontrado!\n\n");
                sistemaLinear(file);
            }
        }
        else if(entradaUsuario == 'E' || entradaUsuario == 'e'){
            equacaoAlgebrica();
            printf("\n\n");
        }
        else if(entradaUsuario == 'F'|| entradaUsuario == 'f'){
            printf("Programa Finalizado!\n\n");
            break;
        }
        else{
            printf("Digite uma opção válida!!!\n\n");
        }
    }
    return 0;
}//Fim da função main()
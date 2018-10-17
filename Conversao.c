#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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



int main()
{

    ConverteNumero();
    system("pause");
    return 0;
}

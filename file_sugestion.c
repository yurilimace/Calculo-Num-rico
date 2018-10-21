#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *inputFile;

// lembrem de fechar o arquivo depois com o fclose. Se não pode bugar o file.
//O glauber olha para esse te tipo de coisa
// EXCLUAM ESSE COMENTÁRIO Depoi
// usem o fclose()
// Estou enviando um arquivo com sugestão de tratamento de file.
// Outra sugestão é usar um outro arquivo para salvar os resultados

int main(){
    //Tamanho maximo de caracteres do arquivo
	char string[3001]={'\0'};
    int i;
    char ch;
    //carregar input do arquivo inputFile
        inputFile = fopen("inputFile.txt", "rb");

        if(inputFile == NULL){
            printf("Arquivo nao encontrado.");
            return 1;
        }
        i = 0;

        //Para levar em conta os \n na string de entrada, usamos esse while para ler ate o final do arquivo e salvar cada caractere na variavel
        while (i < sizeof(string)-1 && EOF !=(ch=fgetc(inputFile))){
            string[i++] = ch;
        }
        printf("inputFile:\n%s \n", string);

        fclose(inputFile);

    return 0;
}
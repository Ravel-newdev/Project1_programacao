#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/input.h" 
#include "player.h"

#define MAX_NOME 12
#define MAX_RESPOSTA 30

/* função auxiliar segura para remover todos os \n */
void limpar_newline(char *str){
    int len = strlen(str);
    if(len > 0 && str[len-1] == '\n') str[len-1] = "\0";
}

/* verifica o nome pra ter até 12 caracteres */
void lerNomeValido(char *dest){
    char buffer[200];
    while (1)
    {
        printf("Digite o nome (max 12 caracteres): ");
        fgets(buffer, sizeof(buffer), stdin);
        limpar_newline(buffer);

        if (strlen(buffer) ==0){
            printf("Nome vazio! tente novamente. \n");
            continue;
        }
        if(strlen(buffer) <= MAX_NOME){
            strcpy(dest, buffer);
            return;
        }

        printf("Nome muito grande! Tente novamente. \n");
    }
    
}
/* trata de nomes compostos para a categoria "pessoa" */
void nomecomposto(char *str){
    for(int i = 0; str[1]; i++){
        if(str[i] == ' '){
            str[i] = '\0';
            return;
        }
    }
}
/* lê a resposta válida (de começar com a letra sorteada e o tamanho da palavra); */
void lerRespostaValida(Player *p, char letra_sorteada, int idx_categoria){
    char buffer[300];

    while (1)
    {
        printf("Sua resposta (max de 30 caracteres)");
        fgets(buffer, sizeof(buffer), stdin);
        limpar_newline(buffer);

        if(strlen(buffer) == 0){
            printf("Resposta vazia, vamos tentar de novo");
            continue;
        if (strlen(buffer) > MAX_RESPOSTA){
            printf("Resposta muito grande!");
            continue;
        }

        /* a resposta deve começar com a letra sorteada */
        if (toupper(buffer[0]) != toupper(letra_sorteada)) {
            printf("A resposta deve iniciar com '%c'!\n", letra_sorteada);
            continue;
        }
        /* categoria de pessoas precisa ser adequada apenas uma palavra; */
        if(idx_categoria == 0){
            tratarNomePessoa(buffer);
        }
        strcpy(p -> resposta, buffer);
        return;
        }
    }
}
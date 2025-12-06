

#include <stdio.h>
#include <stdlib.h>
#include "../include/screen.h"

// Função responsável por limpar o terminal
// usando diretivas de pré-processador para identificar o SO
void limparTela() {
    //verifica se é Windows _WIN32 ou Linux/Unix
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear"); // para sistemas baseados em Unix
    #endif
}

// banner do jogo
void exibirBannerInicial() {
    printf("\n");
    printf("****************************************\n");
    printf("* A M E D O N H A            *\n");
    printf("* Trabalho Intermediario        *\n");
    printf("****************************************\n");
    printf("\n");
}
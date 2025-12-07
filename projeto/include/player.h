#ifndef PLAYER_H
#define PLAYER_H

#include "categories.h"

#define MAX_NOME 13     /* Até 12 caracteres + '\0' */
#define MAX_RESP 31     /* Até 30 caracteres + '\0' */

typedef struct {
    char nome[MAX_NOME];
    char resposta[MAX_RESP];
    int pontos_rodada[CAT_TOTAL];
    int pontos;
    int pontuacao_total;
    double tempo_total;
    int respondeu; /* 0 = tempo estourado */
} Player;

void cadastrarJogadores(Player players[], int *n);
void sortearOrdem(Player players[], int n);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"
#include "../include/player.h"
#include "../include/input.h"

const char letras_validas[] = {
    'A','B','C','D','E','F','G','H','I','J','L','M',
    'N','O','P','Q','R','S','T','U','V','X','Z'
};
const int total_letras = 23;

/* Sorteia uma letra válida(todas são exceto as que sofrem bullying, K, W, Y) */
char sorteia_letra() {
    int idx = rand() % total_letras;
    return letras_validas[idx];
}

/* Sorteia categoria sem repetição */
int sorteia_categoria(int used[]) {
    int cat;
    while (1) {
        cat = rand() % 5; /* 0..4 */
        if (!used[cat]) {
            used[cat] = 1;
            return cat;
        }
    }
}

/* Embaralhar jogadores pra n ter erro */
void embaralha(int order[], int n) {
    int i;
    for (i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }
}

void iniciar_jogo() {
    Player jogadores[10];
    int n;
    int i;

    srand(time(NULL));

    do {
        printf("Quantidade de jogadores (2 a 10): ");
        scanf("%d", &n);
        getchar();
    } while (n < 2 || n > 10);

    for (i = 0; i < n; i++) {
        printf("\nJogador %d:\n", i+1);
        lerNomeValido(jogadores[i].nome);
        jogadores[i].pontuacao_total = 0;
        jogadores[i].tempo_total = 0;
    }

    printf("\nJogadores registrados com sucesso!\n");

    /* As próximas partes (rodadas, pontuação, tempo) serão implementadas depois eu juro. */
}

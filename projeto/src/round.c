#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/round.h"
#include "../include/categories.h"
#include "../include/input.h"
#include "../include/timer.h"
#include "../include/scoring.h"
#include "../include/screen.h"
#include "../include/utils.h"
#include "../include/letters.h"

void jogarRodada(Player players[], int n_jogadores, char letra_sorteada) {
    int usadas_cat[CAT_TOTAL] = {0};
    int ordem[10];
    int i, k, j, tmp, idx;
    
    double limite, inicio, fim, tempo_gasto;
    Categoria cat;
    Player *p;

    for (i = 0; i < CAT_TOTAL; i++)
        usadas_cat[i] = 0;

    cat = sortearCategoria(usadas_cat);

    for (i = 0; i < n_jogadores; i++)
        ordem[i] = i;

    /* embaralhar ordem */
    for (i = 0; i < n_jogadores; i++) {
        j = rand() % n_jogadores;
        tmp = ordem[i];
        ordem[i] = ordem[j];
        ordem[j] = tmp;
    }

    for (k = 0; k < n_jogadores; k++) {
        idx = ordem[k];
        p = &players[idx];

        limparTela();

        printf("Categoria: %s\n", nomeCategoria(cat));
        printf("Letra: %c\n\n", letra_sorteada);
        printf("Agora é a vez de: %s\n", p->nome);

        limite = getTempoLimite(k, n_jogadores);

        printf("Tempo limite: %.1f segundos.\n", limite);

        /* Zera para evitar lixo */
        p->resposta[0] = '\0';
        p->respondeu = 1;

        inicio = checarTempoGasto();  /* pega timestamp inicial */

        lerRespostaValida(p, letra_sorteada, cat);

        fim = checarTempoGasto();
        tempo_gasto = fim - inicio;

        if (tempo_gasto > limite) {
            printf("\n❌ Tempo estourado! Resposta ignorada!\n");
            p->respondeu = 0;
            strcpy(p->resposta, "");
        } else {
            p->tempo_total += tempo_gasto;
        }

        pausar();
    }

    /* Depois que todos responderem → pontuar */
    calcularPontuacao(players, n_jogadores);

    limparTela();
    mostrarPlacar(players, n_jogadores);
    pausar();
}

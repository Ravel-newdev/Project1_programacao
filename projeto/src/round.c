#include <stdio.h>
#include <string.h>
#include "round.h"
#include "categories.h"
#include "input.h"
#include "timer.h"
#include "scoring.h"
#include "screen.h"
#include "utils.h"
#include "letters.h"

void jogarRodada(Player players[], int n_jogadores, char letra_sorteada) {
    int usadas_cat[CAT_TOTAL];
    for (int i = 0; i < CAT_TOTAL; i++)
        usadas_cat[i] = 0;

    Categoria cat = sortearCategoria(usadas_cat);

    int ordem[10];
    for (int i = 0; i < n_jogadores; i++)
        ordem[i] = i;

    // embaralhar ordem
    for (int i = 0; i < n_jogadores; i++) {
        int j = rand() % n_jogadores;
        int tmp = ordem[i];
        ordem[i] = ordem[j];
        ordem[j] = tmp;
    }

    double tempo_anterior = 0;

    for (int k = 0; k < n_jogadores; k++) {
        int idx = ordem[k];
        Player *p = &players[idx];

        limparTela();

        printf("Categoria: %s\n", nomeCategoria(cat));
        printf("Letra: %c\n\n", letra_sorteada);
        printf("Agora é a vez de: %s\n", p->nome);

        double limite = tempoLimiteParaJogador(k, n_jogadores);

        printf("Tempo limite: %.1f segundos.\n", limite);

        // Zera para evitar lixo
        p->resposta[0] = '\0';
        p->respondeu = 1;

        double inicio = medirTempoResposta();  // pega timestamp inicial

        lerRespostaValida(p, letra_sorteada);

        double fim = medirTempoResposta();
        double tempo_gasto = fim - inicio;

        if (tempo_gasto > limite) {
            printf("\n❌ Tempo estourado! Resposta ignorada!\n");
            p->respondeu = 0;
            strcpy(p->resposta, "");
        } else {
            p->tempo_total += tempo_gasto;
        }

        pausar();
    }

    // Depois que todos responderem → pontuar
    calcularPontuacao(players, n_jogadores);

    limparTela();
    mostrarPlacar(players, n_jogadores);
    pausar();
}

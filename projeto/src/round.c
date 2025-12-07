#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../include/round.h"
#include "../include/categories.h"
#include "../include/input.h"
#include "../include/timer.h"
#include "../include/scoring.h"
#include "../include/screen.h"
#include "../include/utils.h"

void jogarRodada(Player players[], int n_jogadores, char letra_sorteada, Categoria cat)
{
    Player *p;
    double limite, inicio, fim, tempo_gasto;
    int tamanhoNome;
    int maxNome = 0;
    int i;

    printf("A categoria desta rodada é: %s\n", nomeCategoria(cat));

    printf("A ordem dessa rodada será:\n");
    sortearOrdem(players, n_jogadores);
    for (i = 0; i < n_jogadores; i++) {
        /* lógica de alinhamento dos nomes, aqui para evitar ficar iterando sem necessidade */
        tamanhoNome = strlen(players[i].nome);
        if (tamanhoNome > maxNome) maxNome = tamanhoNome;

        printf("  %d. %s\n", i + 1, players[i].nome);
    }
    printf("\n");

    esperarEnter();

    for (i = 0; i < n_jogadores; i++) {
        p = &players[i];

        limparTela();

        limite = getTempoLimite(i, n_jogadores);

        printf("%s, você deve entrar um '%s', com a letra '%c' em %d segundos: \n", p->nome, nomeCategoria(cat), toupper(letra_sorteada), (int)limite);

        /* Zera para evitar lixo */
        p->resposta[0] = '\0';
        p->respondeu = 1;

        inicio = checarTempoGasto();

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
    }

    calcularPontuacao(players, n_jogadores, cat); 

    limparTela();

    printf("Jogadas realizadas:\n");
    for (i = 0; i < n_jogadores; i++) {
        printf("%-*s: %s\n", maxNome, players[i].nome, players[i].resposta);
    }
}

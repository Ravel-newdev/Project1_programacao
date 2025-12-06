#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "player.h"
#include "round.h"
#include "letters.h"
#include "categories.h"
#include "screen.h"
int main(void)
{
	/* seed para gerar números pseudo-aletórios */
	srand(time(NULL));
	Player players[10];
    int n;

    cadastrarJogadores(players, &n);

    int usadas_cat[CAT_TOTAL] = {0};

    for (int rodada = 0; rodada < CAT_TOTAL; rodada++) {
        limparTela();

        printf("===== RODADA %d =====\n", rodada + 1);

        char letra = sortearLetra(NULL);  // se quiser controlar repetição, basta enviar vetor
        printf("Letra sorteada: %c\n", letra);

        jogarRodada(players, n, letra);
	}
	// fim do jogo
    limparTela();
    printf("===== FIM DO JOGO =====\n");
    resolverEmpatesPorTempo(players, n);
    mostrarPlacar(players, n);
	
    return 0;
}

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../include/player.h"
#include "../include/round.h"
#include "../include/letters.h"
#include "../include/categories.h"
#include "../include/screen.h"
#include "../include/scoring.h"

int main(void)
{
    Player players[10];
    int n;
    
	/* seed para gerar números pseudo-aletórios */
	srand(time(NULL));
    cadastrarJogadores(players, &n);

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

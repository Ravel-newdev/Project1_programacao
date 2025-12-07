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
    int usadas[23] = {0};
    int n;
    
	/* seed para gerar números pseudo-aletórios */
	srand(time(NULL));
    printf("*** JOGO AMEDONHA ***\n\n");
    cadastrarJogadores(players, &n);

    for (int rodada = 0; rodada < CAT_TOTAL; rodada++) {
        printf("===== RODADA %d =====\n", rodada + 1);
        
        char letra = sortearLetra(usadas);
        printf("A letra dessa rodada é: %c\n", letra);
        
        jogarRodada(players, n, letra);
        // limparTela();
	}
	// fim do jogo
    limparTela();
    printf("===== FIM DO JOGO =====\n");
    resolverEmpatesPorTempo(players, n);
    mostrarPlacar(players, n);
	
    return 0;
}

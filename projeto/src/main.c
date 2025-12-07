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

    for (int i = 0; i < n; i++) {
        players[i].pontuacao_total = 0;
        players[i].pontos = 0;
        for (int j = 0; j < CAT_TOTAL; j++) {
            players[i].pontos_rodada[j] = 0;
        }
    }

    for (int rodada = 0; rodada < CAT_TOTAL; rodada++) {
        printf("===== RODADA %d =====\n", rodada + 1);
        
        char letra = sortearLetra(usadas);
        printf("A letra dessa rodada é: %c\n", letra);
        
        jogarRodada(players, n, letra, rodada);
        // limparTela();
	}

	// fim do jogo
    limparTela();
    printf("===== FIM DO JOGO =====\n");
    resolverEmpatesPorTempo(players, n);
    // mostrarPlacar(players, n);
	
    return 0;
}

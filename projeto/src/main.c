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
    Categoria ordem_categorias[CAT_TOTAL];
    int usadas_cat[CAT_TOTAL] = {0};
    int usadas[23] = {0};
    int rodada, n;
    
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

    for (rodada = 0; rodada < CAT_TOTAL; rodada++) {
        limparTela();

        printf("===== RODADA %d =====\n", rodada + 1);
        
        char letra = sortearLetra(usadas);
        printf("A letra dessa rodada é: %c\n", letra);

        Categoria cat_sorteada = sortearCategoria(usadas_cat);
        ordem_categorias[rodada] = cat_sorteada;
        
        jogarRodada(players, n, letra, cat_sorteada);
        mostrarPlacar(players, n, rodada + 1, ordem_categorias);
        pausar();
	}

	// fim do jogo
    limparTela();
    printf("RESULTADO FINAL:\n");
    resolverEmpatesPorTempo(players, n);
    mostrarPlacar(players, n, rodada, ordem_categorias);
	printf("\nO ganhador é: %s\n", players[0].nome);

    return 0;
}

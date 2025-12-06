#include "../include/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarNome(const char *nome) {
    int tamanho = strlen(nome);

    if (tamanho == 0) {
        printf("Nome vazio. Tente novamente.\n");
        return 0;
    }

    if (tamanho >= MAX_NOME) {
        printf("Nome muito longo (máximo %d caracteres). Tente novamente.\n", MAX_NOME - 1);
        return 0;
    }

    return 1;
}

int lerLinha(char *bufferNome, int tamanho) {
    if (!fgets(bufferNome, tamanho, stdin)) {
        return 0;
	}

    return 1;
}

void cadastrarJogadores(Player *players, int *n)
{
	char bufferNome[20];
	int i;
	int nomeValido, tamanhoEntrada;
	
	printf("Quantos jogadores? ");
	scanf("%d", n);

	limparEntrada();

	for (i = 0; i < *n; i++) {
		nomeValido = 0;

		while (!nomeValido) {
			printf("Nome do %dº jogador: ", i+1);
			
            if (!lerLinha(bufferNome, sizeof bufferNome)) {
                exit(EXIT_FAILURE);
            }

			tamanhoEntrada = strlen(bufferNome);

			if (tamanhoEntrada > 0 && bufferNome[tamanhoEntrada - 1] != '\n') {
                /* linha maior que o buffer -> descarta o resto */
                limparEntrada();
            }
 			
			/* remove \n */
    		bufferNome[strcspn(bufferNome, "\n")] = '\0';

			nomeValido = validarNome(bufferNome);

            if (nomeValido) {
                strcpy(players[i].nome, bufferNome);
            }
		}
	}
}
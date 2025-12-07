#include "../include/categories.h"
#include <stdlib.h>

Categoria sortearCategoria(int usadas[])
{
	int disponiveis[CAT_TOTAL];
	int count = 0;
	int indice, i;

	for (i = 0; i < CAT_TOTAL; i++) {
		if (!usadas[i]) {
			disponiveis[count] = i;
			count++;
		}
	}

	if (count == 0) return CAT_TOTAL;

	/* limita o número sorteado de 0 a count-1 */
	indice = rand() % count;
	return (Categoria)disponiveis[indice];
}

const char* nomeCategoria(Categoria c)
{
	char *lista_nomes[] = {"Nome de Pessoa", "Nome de Cidade", "Nome de Animal", "Nome de Comida", "Nome de Profissão"};
	
	return lista_nomes[c];
}

const char* nomeCategoriaPorNumero(int c)
{
	char *lista_nomes[] = {"Nome de Pessoa", "Nome de Cidade", "Nome de Animal", "Nome de Comida", "Nome de Profissão"};
	
	return lista_nomes[c];
}
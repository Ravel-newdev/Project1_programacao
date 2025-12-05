#include "../include/letters.h"
#include <stdlib.h>

char sortearLetra(int usadas[])
{
	char letras[] = "ABCDEFGHIJLMNOPQRSTUVZ";
	int quantidadeLetras = 23;
	int disponiveis[quantidadeLetras];
	int count = 0;
 	int indice, i;

	for (i = 0; i < quantidadeLetras; i++) {
		if (!usadas[i]) {
			disponiveis[count] = i;
			count++;
		}
	}

	indice = rand() % count;
	return letras[indice];
}

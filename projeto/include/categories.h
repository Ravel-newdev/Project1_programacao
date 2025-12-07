#ifndef CATEGORIES_H
#define CATEGORIES_H

typedef enum {
    CAT_PESSOA,
    CAT_CIDADE,
    CAT_ANIMAL,
    CAT_COMIDA,
    CAT_PROFISSAO,
    CAT_TOTAL
} Categoria;

/**
 * int usadas[].
 * 0 -> livre, count-1 -> usada
 *
 * Em disponiveis[i] estará o número equivalente a categoria.
 * Ex: usadas[1, 0, 1, 0, 0]  -> disponiveis[1, 3, 4, 0, 0]
 *
 * Obs: se o retorno for 5 (CAT_TOTAL) não há categorias disponiveis
 */
Categoria sortearCategoria(int usadas[]);

/**
 * Obter o nome de uma categoria a partir do seu número equivalente.
 * Ex: nomeCategoria[2] -> "Nome de Animal"
 */
const char* nomeCategoria(Categoria c);

#endif

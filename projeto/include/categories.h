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

Categoria sortearCategoria(int usadas[]);
const char* nomeCategoria(Categoria c);

#endif

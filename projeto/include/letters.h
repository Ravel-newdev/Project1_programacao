#ifndef LETTERS_H
#define LETTERS_H

/**
 * int usadas[].
 * 0 -> livre, count-1 -> usada
 * 
 * Em disponiveis[i] estará o índice equivalente a letra.
 * Ex: usadas[1, 0, 1, 0, 0]  -> disponiveis[1, 3, 4, 0, 0]
 */
char sortearLetra(int usadas[]);

#endif

#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>

void removeNewline(char *str); 
void flushStdin();
void toUpperCase(char *s);
int temEspaco(const char *s);

//funções de Lógica e Jogo
int comecaComLetra(const char *str, char letra);
void setupRandom();
int sortearNumero(int min, int max);

#endif

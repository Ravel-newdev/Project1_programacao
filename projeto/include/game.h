#ifndef GAME_H
#define GAME_H

#include "player.h"

// Começa o jogo completo
void iniciar_jogo();

// Sorteia uma letra válida (A-Z exceto K,W,Y)
char sorteia_letra();

// Sorteia uma categoria sem repetição
int sorteia_categoria(int used[]);

// Embaralha a ordem dos jogadores
void embaralha(int order[], int n);

#endif

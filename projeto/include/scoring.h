#ifndef SCORING_H
#define SCORING_H

#include "player.h"

void calcularPontuacao(Player players[], int n_jogadores);
void resolverEmpatesPorTempo(Player players[], int n_jogadores);
void mostrarPlacar(Player players[], int n_jogadores);

#endif

#ifndef SCORING_H
#define SCORING_H

#include "categories.h"
#include "player.h"

void calcularPontuacao(Player players[], int n_jogadores, Categoria cat);
void resolverEmpatesPorTempo(Player players[], int n_jogadores);
void mostrarPlacar(Player players[], int n_jogadores, int rodada, Categoria ordem_categorias[]);

#endif

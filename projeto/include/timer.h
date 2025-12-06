#ifndef TIMER_H
#define TIMER_H

#include <time.h>

// calcula e retorna o tempo limite do jogador em segundos
int getTempoLimite(int posicao, int total_jogadores);

//marca como ponto de inicio da contagem
void iniciarContagem();

//calcula e retorna o tempo em segundos (flutuante), desde a ultima chamada de iniciarContagem()
double checarTempoGasto();

#endif



#include <time.h>
#include <stdio.h>
#include "../include/timer.h"

// variável estática para controle interno do módulo
static time_t g_start_time;


//calcula o tempo disponível para o jogador.
//regra: Base (8 + 2N) menos penalidade por ordem (2 * index).
//requisito 5 e 21.


int getTempoLimite(int totalJogadores, int indiceJogador) {
    // a logica: (4 + N - index) * 2 evita operações redundantes
    // mas vamos manter explícito para clareza, mudando a ordem dos fatores
    int bonus_jogadores = totalJogadores * 2;
    int penalidade_ordem = indiceJogador * 2;
    
    int tempo_calculado = 8 + bonus_jogadores - penalidade_ordem;

    //garantia mínima de tempo (defensive programming)
    return (tempo_calculado > 0) ? tempo_calculado : 1;
}
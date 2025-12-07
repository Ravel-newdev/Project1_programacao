#include <time.h>
#include "../include/timer.h"

/* variável estática para controle interno do módulo */
static time_t g_start_time;

/* calcula o tempo disponível para o jogador */

int getTempoLimite(int posicao, int total_jogadores) {
    /* a logica: (4 + N - index) * 2 evita operações redundantes
     * mantendo explícito para clareza, mudando a ordem dos fatores 
     * */
    int bonus_jogadores = total_jogadores * 2;
    int penalidade_ordem = posicao * 2;
    
    int tempo_calculado = 8 + bonus_jogadores - penalidade_ordem;

    /*  garantia mínima de tempo (defensive programming) */
    return (tempo_calculado > 0) ? tempo_calculado : 1;
}

/* marca o timestamp atual como início */
void iniciarContagem() {
    time(&g_start_time);
}

/* retorna delta T em segundos */
double checarTempoGasto() {
    time_t now;
    time(&now);
    /* retorna direto a diferença */
    return difftime(now, g_start_time);
}
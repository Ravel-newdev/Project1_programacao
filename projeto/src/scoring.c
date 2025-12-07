#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "../include/scoring.h"
#include "../include/player.h"
#include "../include/categories.h"

/* comparando strings ignorando case, essa função evita alocação de memória extra,
 * processando caractere a caractere 'in-place'
 * */
static int stringsIguais(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (toupper((unsigned char)*s1) != toupper((unsigned char)*s2))
            return 0; /* diferentes reteurn 0; iguais return 1; */
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

/* funções auxiliar de ordenação */
/* ordena os jogadores por pontuação total decrescente e tempo crescente para desempate */
static void ordenarPlacar(Player *lista, int n_elementos) {
    int i, j;
    
    /* importante para o insertion sort */
    Player chave; /* variável 'chave' para armazenar uma cópia completa de todos os dados de um jogador */

    for (i = 1; i < n_elementos; i++) {
        chave = lista[i]; /* copia o elemento atual para a 'chave' */
        j = i - 1;

        /* loop para deslocar os elementos da parte ordenada que são 'piores' (menor pontuação ou maior tempo)
         * que a 'chave', abrindo espaço para a inserção.
         * */
        while (j >= 0) {
            int precisa_deslocar = 0; /* se o elemento na posição j precisa ser movido para a direita */

            /* critério: maior pontuação primeiro
             * se o jogador J tem pontuação menor que a chave, precisa_deslocar
             * */
            if (lista[j].pontuacao_total < chave.pontuacao_total) {
                precisa_deslocar = 1;
            }

            /* critério de desempate: menor tempo vence o desempate
             * se as pontuações são iguais, mas o tempo de J é maior que a chave, precisa_deslocar.
             * */
            else if (lista[j].pontuacao_total == chave.pontuacao_total) {
                if (lista[j].tempo_total > chave.tempo_total) {
                    precisa_deslocar = 1;
                }
            }
            
            if (precisa_deslocar) {
                lista[j + 1] = lista[j]; /* desloca o elemento para a direita cria o "buraco" */
                j = j - 1;
            } else {
                break; /* 'chave' encontrou sua posição correta, ou seja, lista[j] está em ordem */
            }
        }

        /* insere a 'chave' o elemento original de lista[i] no espaço correto */
        lista[j + 1] = chave; 
    }
}


/* calcula pontuação da rodada
 * lógica: pontos = len(palavra) / ocorrências(palavra)
 * */
void calcularPontuacao(Player *players, int n_jogadores, Categoria cat) {
    int i, k, len, duplicatas, pontosFinais;
    float pontuacaoFloat;
    char *respAtual;

    for (i = 0; i < n_jogadores; i++) {
        respAtual = players[i].resposta;
        len = strlen(respAtual);

        /* zerar valores pra evitar lixo */
        players[i].pontos = 0;
        players[i].pontos_rodada[cat] = 0;

        /* caso onde não respondeu */
        if (len == 0) {
            continue;
        }

        /* conta quantas pessoas deram exatamente a mesma resposta, case insensitive */
        duplicatas = 0;
        for (k = 0; k < n_jogadores; k++) {
            if (strlen(players[k].resposta) > 0 && stringsIguais(respAtual, players[k].resposta)) {
                duplicatas++;
            }
        }

        /* aplica a regra de fração: tamanho / qtd */
        pontuacaoFloat = (float)len / (float)duplicatas;
        pontosFinais = (int)roundf(pontuacaoFloat); /*roundf garante o arredondamento*/

        /* atualiza a struct do jogador atual */
        players[i].pontos_rodada[cat] = pontosFinais;
        players[i].pontos = pontosFinais;
        players[i].pontuacao_total += pontosFinais;
    }
}

/* lógica de desempate, aplicada antes da exibição final */
void resolverEmpatesPorTempo(Player listaParticipantes[], int numeroParticipantes) {
    int pontuacao_base, marcador_fim_empate, indice_vencedor_tempo;
    double tempo_minimo;
    
    int marcador_inicio_empate, iterador_grupo; /* variáveis de controle não-padrão*/

    /*ordenar a lista por pontuação total antes de resolver empates
     *com foco na pontuação para agrupar os empates
     * */
    ordenarPlacar(listaParticipantes, numeroParticipantes);
    
    marcador_inicio_empate = 0;

    while (marcador_inicio_empate < numeroParticipantes) {

        /* encontra o fim do grupo de jogadores com a mesma pontuação */
        pontuacao_base = listaParticipantes[marcador_inicio_empate].pontuacao_total;
        marcador_fim_empate = marcador_inicio_empate;

        while (marcador_fim_empate < numeroParticipantes && 
               listaParticipantes[marcador_fim_empate].pontuacao_total == pontuacao_base) {
            marcador_fim_empate++;
        }

        /* se o grupo tiver mais de um jogador (houve empate) */
        if (marcador_fim_empate - marcador_inicio_empate > 1) {

            /* encontra o jogador mais rápido neste grupo de empate */
            indice_vencedor_tempo = marcador_inicio_empate;
            tempo_minimo = listaParticipantes[marcador_inicio_empate].tempo_total;

            for (iterador_grupo = marcador_inicio_empate + 1; iterador_grupo < marcador_fim_empate; iterador_grupo++) {
                if (listaParticipantes[iterador_grupo].tempo_total < tempo_minimo) {
                    tempo_minimo = listaParticipantes[iterador_grupo].tempo_total;
                    indice_vencedor_tempo = iterador_grupo;
                }
            }
            
            /* aplica o bônus de desempate: +1 ponto para o mais rápido */
            listaParticipantes[indice_vencedor_tempo].pontuacao_total += 1;
        }

        marcador_inicio_empate = marcador_fim_empate; /* move para o próximo grupo */
    }
}

void mostrarPlacar(Player players[], int n_jogadores, int rodada, Categoria ordem_categorias[]) {
    int i, j;
    Categoria cat_atual;

    ordenarPlacar(players, n_jogadores);

    printf("\n\n");

    /* cabeçalho */
    printf("%-17s", "Nome");
    for (i = 0; i < rodada; i++) {
        /* Usa o array de ordem para saber qual categoria foi jogada na rodada 'i' */
        cat_atual = ordem_categorias[i]; 
        printf(" | %-15s", nomeCategoria((Categoria)cat_atual));
    }
    printf(" | Total\n");

    /* separador  */
    printf("-------------------");
    for (i = 0; i < rodada; i++) {
        printf("-----------------");
    }
    printf("--------\n");

    /* linhas do placar  */
    for (i = 0; i < n_jogadores; i++) {
        Player *p = &players[i];

        printf("%-17s", p->nome);
        
        for (j = 0; j < rodada; j++) {
            cat_atual = ordem_categorias[j];
            printf(" | %15d", p->pontos_rodada[cat_atual]); 
        }

        printf(" | %5d\n", p->pontuacao_total);
    }

    printf("\n");
}
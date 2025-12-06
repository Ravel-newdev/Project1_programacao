
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../include/scoring.h"
#include "../include/player.h" //dependencia da struct player
#include "../include/utils.h" //funcoes auxiliares


//comparando strings ignorando case, essa função é 'static'
//para uso interno e evita alocação de memória extra,
//processando caractere a caractere 'in-place'
static int stringsIguais(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (toupper((unsigned char)*s1) != toupper((unsigned char)*s2))
            return 0; //diferentes reteurn 0; iguais return 1;
        s1++;
        s2++;
    }
    return *s1 == *s2;
}



// calcula pontuação da rodada
// lógica: Pontos = len(palavra) / ocorrências(palavra)
void processarPontuacao(Player *listaJogadores, int qtdJogadores) {
    
    for (int i = 0; i < qtdJogadores; i++) {
        char *respAtual = listaJogadores[i].resposta;
        int len = strlen(respAtual);

        //se não respondeu, ignora
        if (len == 0) {
            listaJogadores[i].pontos = 0;
            continue;
        }

        //conta quantas pessoas deram exatamente a mesma resposta, case insensitive
        int duplicatas = 0;
        for (int k = 0; k < qtdJogadores; k++) {
            if (stringsIguais(respAtual, listaJogadores[k].resposta)) {
                duplicatas++;
            }
        }

        // aplica a regra de fração: tamanho / qtd
        // adiciona 0.5f para fazer o arredondamento comercial corretamente ao castar para int
        float pontuacaoFloat = (float)len / (float)duplicatas;
        int pontosFinais = (int)(pontuacaoFloat + 0.5f);

        //atualiza a struct do jogador atual
        listaJogadores[i].pontos = pontosFinais;
        listaJogadores[i].pontuacao_total += pontosFinais;
    }
}
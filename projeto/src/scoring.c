
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../include/scoring.h"
#include "../include/player.h" //dependencia da struct player
#include "../include/utils.h" //funcoes auxiliares


//comparando strings ignorando case, essa função evita alocação de memória extra,
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


//funções auxiliares de ordenação

//troca o conteúdo de duas structs player na memória.
static void trocarJogadores(Player *p1, Player *p2) {
    Player temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

//ordena os jogadores por pontuação total decrescente e tempo crescente para desempate
//chama a função trocarJogadores internamente.
static void ordenarPlacar(Player *lista, int n_elementos) {
    int i, j;
    
    //importante para o insertion sort
    Player chave; //variável 'chave' para armazenar uma cópia completa de todos os dados de um jogador

    for (i = 1; i < n_elementos; i++) {
        chave = lista[i]; // copia o elemento atual para a 'chave'
        j = i - 1;

        // loop para deslocar os elementos da parte ordenada que são 'piores' (menor pontuação ou maior tempo)
        // que a 'chave', abrindo espaço para a inserção.
        while (j >= 0) {
            int precisa_deslocar = 0; //se o elemento na posição j precisa ser movido para a direita

            // critério: maior pontuação primeiro 
            // se o jogador J tem pontuação menor que a chave, precisa_deslocar
            if (lista[j].pontuacao_total < chave.pontuacao_total) {
                precisa_deslocar = 1;
            }

            //critério de desempate: menor tempo vence o desempate
            // se as pontuações são iguais, mas o tempo de J é maior que a chave, precisa_deslocar.
            else if (lista[j].pontuacao_total == chave.pontuacao_total) {
                if (lista[j].tempo_total > chave.tempo_total) {
                    precisa_deslocar = 1;
                }
            }
            
            if (precisa_deslocar) {
                lista[j + 1] = lista[j]; // desloca o elemento para a direita cria o "buraco"
                j = j - 1;
            } else {
                break; //'chave' encontrou sua posição correta, ou seja, lista[j] está em ordem
            }
        }

        //insere a 'chave' o elemento original de lista[i] no espaço correto
        lista[j + 1] = chave; 
    }
}


//calcula pontuação da rodada
// lógica: pontos = len(palavra) / ocorrências(palavra)
void calcularPontuacao(Player *listaJogadores, int qtdJogadores) {
    
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
        int pontosFinais = (int)roundf(pontuacaoFloat); //roundf garante o arredondamento

        //atualiza a struct do jogador atual
        listaJogadores[i].pontos = pontosFinais;
        listaJogadores[i].pontuacao_total += pontosFinais;
    }
}



//lógica de desempate, aplicada antes da exibição final
void resolverEmpatesPorTempo(Player listaParticipantes[], int numeroParticipantes) {
    
    // variáveis de controle não-padrão
    int marcador_inicio_empate, iterador_grupo;

    //ordenar a lista por pontuação total antes de resolver empates
    //com foco na pontuação para agrupar os empates
    ordenarPlacar(listaParticipantes, numeroParticipantes);
    
    marcador_inicio_empate = 0;

    while (marcador_inicio_empate < numeroParticipantes) {

        // encontra o fim do grupo de jogadores com a mesma pontuação
        int pontuacao_base = listaParticipantes[marcador_inicio_empate].pontuacao_total;
        int marcador_fim_empate = marcador_inicio_empate;

        while (marcador_fim_empate < numeroParticipantes && 
               listaParticipantes[marcador_fim_empate].pontuacao_total == pontuacao_base) {
            marcador_fim_empate++;
        }

        //se o grupo tiver mais de um jogador (houve empate)
        if (marcador_fim_empate - marcador_inicio_empate > 1) {

            //encontra o jogador mais rápido neste grupo de empate
            int indice_vencedor_tempo = marcador_inicio_empate;
            double tempo_minimo = listaParticipantes[marcador_inicio_empate].tempo_total;

            for (iterador_grupo = marcador_inicio_empate + 1; iterador_grupo < marcador_fim_empate; iterador_grupo++) {
                if (listaParticipantes[iterador_grupo].tempo_total < tempo_minimo) {
                    tempo_minimo = listaParticipantes[iterador_grupo].tempo_total;
                    indice_vencedor_tempo = iterador_grupo;
                }
            }
            
            //aplica o bônus de desempate: +1 ponto para o mais rápido
            listaParticipantes[indice_vencedor_tempo].pontuacao_total += 1;
        }

        marcador_inicio_empate = marcador_fim_empate; //move para o próximo grupo
    }
}



//exibe os resultados finais

void mostrarPlacar(Player jogadores[], int total_elementos) {
    
    // ordena o array pela pontuação final (desempatada) e tempo de resposta
    // é essencial ordenar a lista novamente após resolverEmpatesPorTempo()
    ordenarPlacar(jogadores, total_elementos);
    
    int classif; //variável para a classificação

    printf("\n\n###########################################\n");
    printf("#### RESULTADO GERAL DO JOGO ####\n");
    printf("###########################################\n\n");
    
    // itera sobre a lista já ordenada e exibe
    for (classif = 0; classif < total_elementos; classif++) {
        Player *competidor_atual = &jogadores[classif];

        // saída com variáveis não-padrão (classif + 1)
        printf(" -> %2dº Lugar: %-20s (Total Acumulado: %3d | Tempo: %.2f segundos)\n",
               classif + 1,
               competidor_atual->nome,
               competidor_atual->pontuacao_total,
               competidor_atual->tempo_total);
    }

    printf("\n###########################################\n");
}
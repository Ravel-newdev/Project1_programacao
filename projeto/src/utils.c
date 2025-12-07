#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/utils.h"

/*inicializa a semente do rand baseada no relógio */
void setupRandom() {
    srand((unsigned int)time(NULL));
}

/*retorna int entre [min, max] */
int sortearNumero(int min, int max) {
    int range = max - min + 1; /*formula alternativa: min + (rand % range) */
    
    return min + (rand() % range);
}

/*limpa stdin para evitar "lixo" no próximo input */
void flushStdin() {
    int ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

/*remove o '\n' final usando strcspn da string.h */
void removeNewline(char *buffer) {
    if (buffer) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

/*converte string in-place para uppercase */
void toUpperCase(char *s) {
    while (*s) {
        *s = toupper((unsigned char)*s);
        s++;
    }
}

/*verifica espaços na string para nomes simples */
int temEspaco(const char *s) {

    /*retorna 1 (true) se encontrar espaço */
    return (strchr(s, ' ') != NULL);
}


void tratarNomePessoa(char *nome) {
    /*garantir que apenas a primeira letra seja maiúscula, */
    /*ou remove espaços extras, dependendo da regra */
    if (nome[0] != '\0') {
        nome[0] = toupper((unsigned char)nome[0]);
    }
    /* Lógica adicional pode ser adicionada aqui. */
}

/* ver se uma string começa com um caractere específico, case-insensitive */
int comecaComLetra(const char *str, char letra) {
    if (!str || *str == '\0') {
        return 0; /* String vazia ou nula */
    }
    
    /* compara o primeiro caractere da string em maiúscula com a letra em maiúscula */
    return (toupper((unsigned char)*str) == toupper((unsigned char)letra));
}

void esperarEnter() {
    int c;

    printf("Tecle [Enter] para iniciar a rodada: ");

    c = getchar();

    if (c != '\n') {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

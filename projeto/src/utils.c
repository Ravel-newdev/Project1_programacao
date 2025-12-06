

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/utils.h"

//inicializa a semente do rand baseada no relógio
void setupRandom() {
    srand((unsigned int)time(NULL));
}

//retorna int entre [min, max]
int sortearNumero(int min, int max) {
    
    //formula alternativa: min + (rand % range)
    int range = max - min + 1;
    return min + (rand() % range);
}

//limpa stdin para evitar "lixo" no próximo input
void flushStdin() {
    int ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}


//remove o '\n' final usando strcspn da string.h
//verificando str[len-1]
void trimNewline(char *buffer) {
    if (buffer) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

// converte string in-place para uppercase
void toUpperCase(char *s) {
    while (*s) {
        *s = toupper((unsigned char)*s);
        s++;
    }
}

//verifica espaços na string para nomes simples
int temEspaco(const char *s) {

    //retorna 1 (true) se encontrar espaço
    return (strchr(s, ' ') != NULL);
}
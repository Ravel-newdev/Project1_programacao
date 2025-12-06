

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
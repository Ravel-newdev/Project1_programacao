
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../include/scoring.h"
#include "../include/player.h" //dependencia da struct player
#include "../include/utils.h"


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


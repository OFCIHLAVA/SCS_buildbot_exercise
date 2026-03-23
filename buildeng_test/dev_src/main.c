#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stddef.h>

extern const char *lib_begl(void);
extern const char *lib_endl(void);
extern const char *lib_endl_ext(void);

static const unsigned char base64_table[256] = {
    ['A']=0,  ['B']=1,  ['C']=2,  ['D']=3,  ['E']=4,  ['F']=5,  ['G']=6,  ['H']=7,
    ['I']=8,  ['J']=9,  ['K']=10, ['L']=11, ['M']=12, ['N']=13, ['O']=14, ['P']=15,
    ['Q']=16, ['R']=17, ['S']=18, ['T']=19, ['U']=20, ['V']=21, ['W']=22, ['X']=23,
    ['Y']=24, ['Z']=25, ['a']=26, ['b']=27, ['c']=28, ['d']=29, ['e']=30, ['f']=31,
    ['g']=32, ['h']=33, ['i']=34, ['j']=35, ['k']=36, ['l']=37, ['m']=38, ['n']=39,
    ['o']=40, ['p']=41, ['q']=42, ['r']=43, ['s']=44, ['t']=45, ['u']=46, ['v']=47,
    ['w']=48, ['x']=49, ['y']=50, ['z']=51, ['0']=52, ['1']=53, ['2']=54, ['3']=55,
    ['4']=56, ['5']=57, ['6']=58, ['7']=59, ['8']=60, ['9']=61, ['+']=62, ['/']=63
};

int base64_decode(const char *in, unsigned char *out, size_t outlen) {
    size_t len = strlen(in);
    size_t i, j;
    unsigned int v = 0;
    int valb = -8;
    for (i = 0, j = 0; i < len && j < outlen; i++) {
        unsigned char c = in[i];
        if (c == '=' || c > 127) break;
        if (base64_table[c] == 0 && c != 'A') continue;
        v = (v << 6) | base64_table[c];
        valb += 6;
        if (valb >= 0) {
            out[j++] = (v >> valb) & 0xFF;
            valb -= 8;
        }
    }
    return j;
}

int main(void) 
{
    const char *endl_string = lib_endl();
    const char *begl_string = lib_begl();
    const char *endl_ext_string = lib_endl_ext();

    char *concat = NULL;
    const char *src = NULL;
    if (endl_string == NULL) {
        size_t len1 = begl_string ? strlen(begl_string) : 0;
        size_t len2 = endl_ext_string ? strlen(endl_ext_string) : 0;
        concat = (char *)malloc(len1 + len2 + 1);
        if (!concat) {
            fprintf(stderr, "Allocation failed\n");
            return 1;
        }
        if (len1) memcpy(concat, begl_string, len1);
        if (len2) memcpy(concat + len1, endl_ext_string, len2);
        concat[len1 + len2] = '\0';
        src = concat;
    } else {
        src = endl_string;
    }

    unsigned char buf[128];
    int decoded_len = base64_decode(src, buf, sizeof(buf) - 1);
    buf[decoded_len] = 0;

    const char *colour = "\033[0;32m";
    if (decoded_len > 1 && buf[1] == 'n') {
        colour = "\033[0;31m";
    }
    printf("%sDecoded: \033[0;0m%s", colour, buf);

    free(concat);
    return 0;
}

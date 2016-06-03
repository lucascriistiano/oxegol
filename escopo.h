#ifndef ESCOPO_H
#define ESCOPO_H

#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "hash.h"

typedef struct escopo_variaveis_s {
    hash_variaveis_t *hash_variaveis;
    struct escopo_variaveis_s *anterior;
} escopo_variaveis_t;

escopo_variaveis_t *cria_escopo(escopo_variaveis_t *escopo_atual); //push
escopo_variaveis_t *apaga_escopo(escopo_variaveis_t *escopo_atual); //pop
variavel_t *consulta_escopos(escopo_variaveis_t *escopo_atual, char *id); //get todos escopos
variavel_t *consulta_escopo_atual(escopo_variaveis_t *escopo_atual, char *id); //get escopo atual
int criar_variavel_escopo_atual(escopo_variaveis_t *escopo_atual, char *id, tipo_t tipo, int tamanho);

#endif
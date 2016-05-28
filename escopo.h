#ifndef ESCOPO_H
#define ESCOPO_H

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct escopo_s {
    tabela_hash_t *tabela_hash;
    struct escopo_s *anterior;
} escopo_t;

escopo_t *cria_escopo(escopo_t *escopo_atual); //push
escopo_t *apaga_escopo(escopo_t *escopo_atual); //pop
variavel_t *consulta_escopos(escopo_t *escopo_atual, char *chave); //get todos escopos
variavel_t *consulta_escopo_atual(escopo_t *escopo_atual, char *chave); //get escopo atual
int criar_variavel_escopo_atual(escopo_t *escopo_atual, char *chave, tipo_t tipo, int tamanho);

#endif
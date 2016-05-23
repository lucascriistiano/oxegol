#ifndef ESCOPO_H
#define ESCOPO_H

#include <stdlib.h>
#include "hash.h"

struct escopo_s {
    tabela_hash_t *tabela_hash;
    struct escopo_s *anterior;
};

typedef struct escopo_s escopo_t;

escopo_t *cria_escopo(escopo_t *escopo_atual); //push
escopo_t *apaga_escopo(escopo_t *escopo_atual); //pop
variavel_t *consulta_escopos(escopo_t *escopo_atual, char *chave); //get todos escopos
variavel_t *consulta_escopo_atual(escopo_t *escopo_atual, char *chave); //get escopo atual
void criar_variavel_escopo_atual(escopo_t *escopo_atual, char *chave, tipo t, int tamanho);


#endif
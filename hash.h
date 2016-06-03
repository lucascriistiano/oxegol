#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "aux.h"

#define TAMANHO_HASH 65536

typedef struct {
    int tamanho;
    variavel_t **tabela;
} hash_variaveis_t;

hash_variaveis_t *criar_hash_variaveis(int tamanho);
void apagar_hash_variaveis(hash_variaveis_t *tabela_hash);
int funcao_hash_variaveis(hash_variaveis_t *tabela_hash, char *id);
variavel_t *criar_nova_variavel(char *id, tipo_t tipo, int tamanho);
int atualiza_variavel(hash_variaveis_t *tabela_hash, char *id, tipo_t tipo, int tamanho);
variavel_t *busca_variavel(hash_variaveis_t *tabela_hash, char *id);


typedef struct {
    int tamanho;
    subprograma_t **tabela;
} hash_subprogramas_t;

hash_subprogramas_t *criar_hash_subprogramas(int tamanho);
void apagar_hash_subprogramas(hash_subprogramas_t *tabela_hash);
int funcao_hash_subprogramas(hash_subprogramas_t *tabela_hash, char *id);
subprograma_t *criar_novo_subprograma(char *id, tipo_t retorno, no_parametro_t *parametros);
int atualiza_subprograma(hash_subprogramas_t *tabela_hash, char *id, tipo_t retorno, no_parametro_t *parametros);
subprograma_t *busca_subprograma(hash_subprogramas_t *tabela_hash, char *id);

#endif
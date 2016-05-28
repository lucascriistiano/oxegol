#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

typedef enum {
    inteiro, real, booleano, caractere, string
} tipo_t;

typedef struct variavel_s {
    char *chave;
    tipo_t tipo;
    int tamanho;
    struct variavel_s *proximo;
} variavel_t;

typedef struct {
    int tamanho;
    variavel_t **tabela;
} tabela_hash_t;

tabela_hash_t *criar_hash(int tamanho);
int funcao_hash(tabela_hash_t *tabela_hash, char *chave);
variavel_t *nova_variavel(char *chave, tipo_t tipo, int tamanho);
int atualiza_variavel(tabela_hash_t *tabela_hash, char *chave, tipo_t tipo, int tamanho);
variavel_t *busca_variavel(tabela_hash_t *tabela_hash, char *chave);

#endif
#ifndef HASH_H
#define HASH_H

enum tipo_e {
    inteiro, real, booleano, caracter, string
};

typedef enum tipo_e tipo_t;

struct variavel_s {
    char *chave;
    tipo_t tipo;
    int tamanho;
    struct variavel_s *proximo;
};

typedef struct variavel_s variavel_t;

struct tabela_hash_s {
    int tamanho;
    struct variavel_s *tabela;
};

typedef struct tabela_hash_s tabela_hash_t;

tabela_hash_t *criar_hash(int tamanho);
int funcao_hash(tabela_hash_t *tabela_hash, char *chave);
variavel_t *nova_variavel(char *chave, tipo_t tipo, int tamanho);
void atualiza_variavel(tabela_hash_t *tabela_hash, char *chave, tipo_t tipo, int tamanho);
variavel_t *busca_variavel(tabela_hash_t *tabela_hash, char *chave);

#endif
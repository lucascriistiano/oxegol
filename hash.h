#ifndef HASH_H
#define HASH_H

enum tipo_e {
    inteiro, real, booleano, caracter, string
};

typedef enum tipo_e tipo;

struct variavel_s {
    char *chave; //Nome concatenado com o escopo separado pelo $ (e01$identificador)
    tipo t; //
    int tamanho;
    struct variavel_s *proximo;
};

typedef struct variavel_s variavel_t;

struct tabela_hash_s {
    int tamanho;
    struct variavel_s **tabela;
};

typedef struct tabela_hash_s tabela_hash_t;

tabela_hash_t *criar_hash(int tamanho);
int funcao_hash(tabela_hash_t *tabela_hash, char *chave);
variavel_t *nova_variavel(char *chave, tipo t, int tamanho);
void atualiza_variavel(tabela_hash_t *tabela_hash, char *chave, tipo t, int tamanho);
variavel_t *busca_variavel(tabela_hash_t *tabela_hash, char *chave);

#endif
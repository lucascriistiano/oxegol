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

typedef struct variavel_s variavel;

struct tabela_hash_s {
    int tamanho;
    struct variavel_s **tabela;
};

typedef struct tabela_hash_s tabela_hash;

tabela_hash *criar_hash(int tamanho);
int funcao_hash(tabela_hash *tabela, char *chave);
variavel *nova_variavel(char *chave, tipo t, int tamanho);
void atualiza_variavel(tabela_hash *tabela, char *chave, tipo t, int tamanho);
variavel *busca_variavel(tabela_hash *tabela, char *chave);

#endif
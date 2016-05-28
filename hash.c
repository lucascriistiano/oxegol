/*
  Código adaptado do github : https://gist.github.com/tonious/1377667
*/
#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include "hash.h"

/* Cria uma nova tabela hash. */
tabela_hash_t *criar_hash(int tamanho) {

    tabela_hash_t *tabela_hash = NULL;
    int i;

    if(tamanho < 1) return NULL;

    /* Aloca a tabela. */
    if((tabela_hash = malloc(sizeof(tabela_hash))) == NULL) {
        return NULL;
    }

    /* Aloca os ponteiros para os nós cabeça. */
    if((tabela_hash->tabela = malloc(sizeof(variavel_t *) * tamanho)) == NULL ) {
        return NULL;
    }
    for(i = 0; i < tamanho; i++) {
        tabela_hash->tabela[i] = NULL;
    }

    tabela_hash->tamanho = tamanho;

    return tabela_hash;
}

/* Transforma a string chave em uma posição na tabela. */
int funcao_hash(tabela_hash_t *tabela_hash, char *chave) {

    unsigned long int valor_hash;
    int i = 0;

    /* Converte nossa string para um inteiro */
    while(valor_hash < ULONG_MAX && i < strlen(chave)) {
        valor_hash = valor_hash << 8;
        valor_hash += chave[i];
        i++;
    }

    return valor_hash % tabela_hash->tamanho;
}

/* Cria o registro na tabela. */
variavel_t *nova_variavel(char *chave, tipo_t tipo, int tamanho) {
    variavel_t *nova_variavel;

    if((nova_variavel = malloc(sizeof(variavel_t))) == NULL) {
        return NULL;
    }

    if((nova_variavel->chave = strdup(chave)) == NULL) {
        return NULL;
    }

    nova_variavel->tipo = tipo;
    nova_variavel->tamanho = tamanho;
    nova_variavel->proximo = NULL;

    return nova_variavel;
}

/* Insere um par chave-valor na tabela hash.*/
int atualiza_variavel(tabela_hash_t *tabela_hash, char *chave, tipo_t tipo, int tamanho) {
    int indice = 0;
    variavel_t *variavel_nova = NULL;
    variavel_t *proximo = NULL;
    variavel_t *ultimo = NULL;

    indice = funcao_hash(tabela_hash, chave);

    proximo = tabela_hash->tabela[indice];

    while(proximo != NULL && proximo->chave != NULL && strcmp(chave, proximo->chave ) > 0) {
        ultimo = proximo;
        proximo = proximo->proximo;
    }

    /* Já existe uma variavel. Não substitui o seu conteúdo e retorna erro. */
    if(proximo != NULL && proximo->chave != NULL && strcmp(chave, proximo->chave) == 0) {
        return 1;

    /* Nenhum par encontrado. Cria uma nova variável. */
    } else {
        variavel_nova = nova_variavel(chave, tipo, tamanho);

        /* Essa posição está no começo da lista ligada. */
        if(proximo == tabela_hash->tabela[indice]) {
            variavel_nova->proximo = proximo;
            tabela_hash->tabela[indice] = variavel_nova;

        /* Essa posição está no final da lista ligada. */
        } else if ( proximo == NULL ) {
            ultimo->proximo = variavel_nova;

        /* Essa posição está no meio da lista ligada. */
        } else  {
            variavel_nova->proximo = proximo;
            ultimo->proximo = variavel_nova;
        }

        return 0;
    }
}

/* Busca uma variavel a partir da tabela hash. */
variavel_t *busca_variavel(tabela_hash_t *tabela_hash, char *chave) {
    int indice = 0;
    variavel_t *variavel_encontrada;

    indice = funcao_hash(tabela_hash, chave);

    /* Step through the bin, looking for our value. */
    variavel_encontrada = tabela_hash->tabela[indice];
    while(variavel_encontrada != NULL && variavel_encontrada->chave != NULL && strcmp(chave, variavel_encontrada->chave) > 0) {
        variavel_encontrada = variavel_encontrada->proximo;
    }

    /* Did we actually find anything? */
    if(variavel_encontrada == NULL || variavel_encontrada->chave == NULL || strcmp(chave, variavel_encontrada->chave) != 0) {
        return NULL;
    } else {
        return variavel_encontrada;
    }

}
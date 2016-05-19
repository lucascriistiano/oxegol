/*
  Código adaptado do github : https://gist.github.com/tonious/1377667
 */
 #define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/* Cria uma nova tabela hash. */
tabela_hash *criar_hash(int tamanho) {

    tabela_hash *tabela = NULL;
    int i;

    if(tamanho < 1) return NULL;

    /* Aloca a tabela. */
    if((tabela = malloc(sizeof(tabela))) == NULL) {
        return NULL;
    }

    /* Aloca os ponteiros para os nós cabeça. */
    if((tabela->tabela = malloc(sizeof(variavel *) * tamanho)) == NULL ) {
        return NULL;
    }
    for(i = 0; i < tamanho; i++) {
        tabela->tabela[i] = NULL;
    }

    tabela->tamanho = tamanho;

    return tabela;
}

/* Transforma a string chave em uma posição na tabela. */
int funcao_hash(tabela_hash *tabela, char *chave) {

    unsigned long int valor_hash;
    int i = 0;

    /* Converte nossa string para um inteiro */
    while(valor_hash < ULONG_MAX && i < strlen(chave)) {
        valor_hash = valor_hash << 8;
        valor_hash += chave[i];
        i++;
    }

    return valor_hash % tabela->tamanho;
}

/* Cria o registro na tabela. */
variavel *nova_variavel(char *chave, tipo t, int tamanho) {
    variavel *nova_variavel;

    if((nova_variavel = malloc(sizeof(variavel))) == NULL) {
        return NULL;
    }

    if((nova_variavel->chave = strdup(chave)) == NULL) {
        return NULL;
    }

    nova_variavel->t = t;
    nova_variavel->tamanho = tamanho;
    nova_variavel->proximo = NULL;

    return nova_variavel;
}

/* Insere um par chave-valor na tabela hash.*/
void atualiza_variavel(tabela_hash *tabela, char *chave, tipo t, int tamanho) {
    int indice = 0;
    variavel *variavel_nova = NULL;
    variavel *proximo = NULL;
    variavel *ultimo = NULL;

    indice = funcao_hash(tabela, chave);

    proximo = tabela->tabela[indice];

    while(proximo != NULL && proximo->chave != NULL && strcmp(chave, proximo->chave ) > 0) {
        ultimo = proximo;
        proximo = proximo->proximo;
    }

    /* Já existe uma variavel.  Substitui o seu conteúdo. */
    if(proximo != NULL && proximo->chave != NULL && strcmp(chave, proximo->chave) == 0) {
        proximo->t = t;
        proximo->tamanho = tamanho;

    /* Nenhum par encontrado. Cria uma nova variável. */
    } else {
        variavel_nova = nova_variavel(chave, t, tamanho);

        /* Essa posição está no começo da lista ligada. */
        if(proximo == tabela->tabela[indice]) {
            variavel_nova->proximo = proximo;
            tabela->tabela[indice] = variavel_nova;

        /* Essa posição está no final da lista ligada. */
        } else if ( proximo == NULL ) {
            ultimo->proximo = variavel_nova;

        /* Essa posição está no meio da lista ligada. */
        } else  {
            variavel_nova->proximo = proximo;
            ultimo->proximo = variavel_nova;
        }
    }
}

/* Busca uma variavel a partir da tabela hash. */
variavel *busca_variavel(tabela_hash *tabela, char *chave) {
    int indice = 0;
    variavel *variavel_encontrada;

    indice = funcao_hash(tabela, chave);

    /* Step through the bin, looking for our value. */
    variavel_encontrada = tabela->tabela[indice];
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
#include <stdio.h>
#include "escopo.h"
#include "hash.h"

escopo_t *cria_escopo(escopo_t *escopo_atual) {
    printf("Criando escopo\n");
    
    if (escopo_atual == NULL) { //Falta fazer testes de alocação
        escopo_atual = (escopo_t*) malloc(sizeof(escopo_t));
        escopo_atual->tabela_hash = (tabela_hash_t*) malloc(sizeof(tabela_hash_t));
        escopo_atual->anterior = NULL;
        return escopo_atual;
    } else {
        escopo_t *novo_escopo = (escopo_t*) malloc(sizeof(escopo_t));
        novo_escopo->tabela_hash = (tabela_hash_t*) malloc(sizeof(tabela_hash_t));
        novo_escopo->anterior = escopo_atual;
        return novo_escopo;
    }
}

escopo_t *apaga_escopo(escopo_t *escopo_atual) {
    printf("Apagando escopo\n");
    
    if(escopo_atual != NULL) {
        escopo_t *escopo_anterior = escopo_atual->anterior;
        free(escopo_atual->tabela_hash);
        free(escopo_atual);
        return escopo_anterior;
    } else {
        return NULL;
    }
}

variavel_t *consulta_escopos(escopo_t *escopo_atual, char *chave) {
    if (escopo_atual != NULL) {
        tabela_hash_t *tabela_hash_escopo_atual = escopo_atual->tabela_hash;
        
        variavel_t *variavel_encontrada =  busca_variavel(tabela_hash_escopo_atual, chave);
        if(variavel_encontrada == NULL) {
            return consulta_escopos(escopo_atual->anterior, chave);   
        } else {
            return variavel_encontrada;
        }
    } else {
        return NULL;
    }
}

variavel_t *consulta_escopo_atual(escopo_t *escopo_atual, char *chave) {
    if (escopo_atual != NULL) {
        tabela_hash_t *tabela_hash_escopo_atual = escopo_atual->tabela_hash;
        
        variavel_t *variavel_encontrada =  busca_variavel(tabela_hash_escopo_atual, chave);
        return variavel_encontrada;
    } else {
        return NULL;
    }
}

int criar_variavel_escopo_atual(escopo_t *escopo_atual, char *chave, tipo_t tipo, int tamanho) {
    if (escopo_atual != NULL) {
        tabela_hash_t *tabela_hash_escopo_atual = escopo_atual->tabela_hash;
        return atualiza_variavel(tabela_hash_escopo_atual, chave, tipo, tamanho);
    } else {
        return 1;
    }
}
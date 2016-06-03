#include "escopo.h"

escopo_variaveis_t *cria_escopo(escopo_variaveis_t *escopo_atual) {
    printf("Criando hashs do escopo\n");
    if (escopo_atual == NULL) {
        if ((escopo_atual = (escopo_variaveis_t*) malloc(sizeof(escopo_variaveis_t))) != NULL) {
            escopo_atual->hash_variaveis = criar_hash_variaveis(TAMANHO_HASH);
            escopo_atual->anterior = NULL;
            return escopo_atual;
        } else {
            printf("Memória insuficiente para alocar hashs do escopo.\n");
            return NULL;
        }
    } else {
        escopo_variaveis_t *novo_escopo = (escopo_variaveis_t*) malloc(sizeof(escopo_variaveis_t));
        novo_escopo->hash_variaveis = (hash_variaveis_t*) malloc(sizeof(hash_variaveis_t));
        novo_escopo->anterior = escopo_atual;
        return novo_escopo;
    }
}

escopo_variaveis_t *apaga_escopo(escopo_variaveis_t *escopo_atual) {
    printf("Apagando hashs do escopo\n");
    if(escopo_atual != NULL) {
        escopo_variaveis_t *escopo_anterior = escopo_atual->anterior;
        apagar_hash_variaveis(escopo_atual->hash_variaveis);
        free(escopo_atual);
        return escopo_anterior;
    } else {
        return NULL;
    }
}

variavel_t *consulta_escopos(escopo_variaveis_t *escopo_atual, char *id) {
    if (escopo_atual != NULL) {
        hash_variaveis_t *hash_variaveis_escopo_atual = escopo_atual->hash_variaveis;

        variavel_t *variavel_encontrada =  busca_variavel(hash_variaveis_escopo_atual, id);
        if(variavel_encontrada == NULL) {
            return consulta_escopos(escopo_atual->anterior, id);
        } else {
            return variavel_encontrada;
        }
    } else {
        return NULL;
    }
}

variavel_t *consulta_escopo_atual(escopo_variaveis_t *escopo_atual, char *id) {
    if (escopo_atual != NULL) {
        hash_variaveis_t *hash_variaveis_escopo_atual = escopo_atual->hash_variaveis;

        variavel_t *variavel_encontrada =  busca_variavel(hash_variaveis_escopo_atual, id);
        return variavel_encontrada;
    } else {
        return NULL;
    }
}

int criar_variavel_escopo_atual(escopo_variaveis_t *escopo_atual, char *id, tipo_t tipo, int tamanho) {
    if (escopo_atual != NULL) {
        hash_variaveis_t *hash_variaveis_escopo_atual = escopo_atual->hash_variaveis;
        return atualiza_variavel(hash_variaveis_escopo_atual, id, tipo, tamanho);
    } else {
        return 1;
    }
}
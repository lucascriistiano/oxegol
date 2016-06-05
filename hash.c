/*
  Código adaptado do github : https://gist.github.com/tonious/1377667
*/
#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include "hash.h"

hash_variaveis_t *criar_hash_variaveis(int tamanho) {
    hash_variaveis_t *tabela_hash = NULL;
    int i;

    if(tamanho < 1) return NULL;

    /* Aloca a tabela. */
    if((tabela_hash = malloc(sizeof(hash_variaveis_t))) == NULL) {
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

void apagar_hash_variaveis(hash_variaveis_t *tabela_hash) {
    // typedef struct {
    //     int tamanho;
    //     variavel_t **tabela;
    // } hash_variaveis_t;

    // typedef struct variavel_s {
    //     char *id;
    //     tipo_t tipo;
    //     int tamanho;
    //     struct variavel_s *proximo;
    // } variavel_t;

    // free(tabela_hash->tabela); //Modificar para limpar tudo e não só o primeiro
    // free(tabela_hash); //Limpar tudo e não só o primeiro

    // if(tabela_hash != NULL) {
    //     variavel_t *anterior = tabela_hash->tabela;
    //     if(anterior != NULL)
    //     variavel_t *atual = tabela_hash->proxima;
    //     while(atual != NULL) {
    //         free(anterior);
    //     }
    //     free(anterior);
    // }
}

int funcao_hash_variaveis(hash_variaveis_t *tabela_hash, char *id) {
    unsigned long int valor_hash;
    int i = 0;

    /* Converte nossa string para um inteiro */
    while(valor_hash < ULONG_MAX && i < strlen(id)) {
        valor_hash = valor_hash << 8;
        valor_hash += id[i];
        i++;
    }

    return valor_hash % tabela_hash->tamanho;
}

variavel_t *criar_nova_variavel(char *id, tipo_t tipo, int tamanho) {
    variavel_t *nova_variavel;

    if((nova_variavel = malloc(sizeof(variavel_t))) == NULL) {
        return NULL;
    }

    if((nova_variavel->id = strdup(id)) == NULL) {
        return NULL;
    }

    nova_variavel->tipo = tipo;
    nova_variavel->tamanho = tamanho;
    nova_variavel->proximo = NULL;

    return nova_variavel;
}

int atualiza_variavel(hash_variaveis_t *tabela_hash, char *id, tipo_t tipo, int tamanho) {
    int indice = 0;
    variavel_t *nova_variavel = NULL;
    variavel_t *proximo = NULL;
    variavel_t *ultimo = NULL;

    indice = funcao_hash_variaveis(tabela_hash, id);

    proximo = tabela_hash->tabela[indice];

    while(proximo != NULL && proximo->id != NULL && strcmp(id, proximo->id ) > 0) {
        ultimo = proximo;
        proximo = proximo->proximo;
    }

    /* Já existe uma variavel. Não substitui o seu conteúdo e retorna erro. */
    if(proximo != NULL && proximo->id != NULL && strcmp(id, proximo->id) == 0) {
        return 1;

    /* Nenhum par encontrado. Cria uma nova variável. */
    } else {
        nova_variavel = criar_nova_variavel(id, tipo, tamanho);

        /* Essa posição está no começo da lista ligada. */
        if(proximo == tabela_hash->tabela[indice]) {
            nova_variavel->proximo = proximo;
            tabela_hash->tabela[indice] = nova_variavel;

        /* Essa posição está no final da lista ligada. */
        } else if ( proximo == NULL ) {
            ultimo->proximo = nova_variavel;

        /* Essa posição está no meio da lista ligada. */
        } else  {
            nova_variavel->proximo = proximo;
            ultimo->proximo = nova_variavel;
        }

        return 0;
    }
}

variavel_t *busca_variavel(hash_variaveis_t *tabela_hash, char *id) {
    int indice = 0;
    variavel_t *variavel_encontrada;

    indice = funcao_hash_variaveis(tabela_hash, id);

    /* Step through the bin, looking for our value. */
    variavel_encontrada = tabela_hash->tabela[indice];
    while(variavel_encontrada != NULL && variavel_encontrada->id != NULL && strcmp(id, variavel_encontrada->id) > 0) {
        variavel_encontrada = variavel_encontrada->proximo;
    }

    /* Did we actually find anything? */
    if(variavel_encontrada == NULL || variavel_encontrada->id == NULL || strcmp(id, variavel_encontrada->id) != 0) {
        return NULL;
    } else {
        return variavel_encontrada;
    }
}

hash_subprogramas_t *criar_hash_subprogramas(int tamanho) {
    hash_subprogramas_t *tabela_hash = NULL;
    int i;

    if(tamanho < 1) return NULL;

    /* Aloca a tabela. */
    if((tabela_hash = malloc(sizeof(hash_subprogramas_t))) == NULL) {
        return NULL;
    }

    /* Aloca os ponteiros para os nós cabeça. */
    if((tabela_hash->tabela = malloc(sizeof(subprograma_t *) * tamanho)) == NULL ) {
        return NULL;
    }
    for(i = 0; i < tamanho; i++) {
        tabela_hash->tabela[i] = NULL;
    }

    tabela_hash->tamanho = tamanho;
    return tabela_hash;
}

void apagar_hash_subprogramas(hash_subprogramas_t *tabela_hash) {
    // typedef struct {
    //     int tamanho;
    //     variavel_t **tabela;
    // } hash_variaveis_t;

    // typedef struct variavel_s {
    //     char *id;
    //     tipo_t tipo;
    //     int tamanho;
    //     struct variavel_s *proximo;
    // } variavel_t;

    // free(tabela_hash->tabela); //Modificar para limpar tudo e não só o primeiro
    // free(tabela_hash); //Limpar tudo e não só o primeiro

    // if(tabela_hash != NULL) {
    //     variavel_t *anterior = tabela_hash->tabela;
    //     if(anterior != NULL)
    //     variavel_t *atual = tabela_hash->proxima;
    //     while(atual != NULL) {
    //         free(anterior);
    //     }
    //     free(anterior);
    // }
}

int funcao_hash_subprogramas(hash_subprogramas_t *tabela_hash, char *id) {
    unsigned long int valor_hash;
    int i = 0;

    /* Converte nossa string para um inteiro */
    while(valor_hash < ULONG_MAX && i < strlen(id)) {
        valor_hash = valor_hash << 8;
        valor_hash += id[i];
        i++;
    }

    return valor_hash % tabela_hash->tamanho;
}

subprograma_t *criar_novo_subprograma(char *id, tipo_t retorno, no_parametro_t *parametros) {
    subprograma_t *novo_subprograma;
    if((novo_subprograma = malloc(sizeof(subprograma_t))) == NULL) {
        return NULL;
    }

    if((novo_subprograma->id = strdup(id)) == NULL) {
        return NULL;
    }

    novo_subprograma->retorno = retorno;

    int num_parametros = 0;
    if(parametros != NULL) {
        num_parametros = 1;
        for(no_parametro_t* parametro = parametros; parametro->proximo != NULL; parametro = parametro->proximo) {
            num_parametros++;
        }
    }
    novo_subprograma->num_parametros = num_parametros;

    tipo_t* copia_tipos_parametros = (tipo_t*) malloc(sizeof(tipo_t) * num_parametros);
    if(num_parametros > 0) {
        int indice = 0;
        for(no_parametro_t* parametro = parametros; parametro->proximo != NULL; parametro = parametro->proximo) {
            copia_tipos_parametros[indice] = parametro->tipo;
        }
    }
    novo_subprograma->tipos_parametros = copia_tipos_parametros;
    novo_subprograma->proximo = NULL;

    printf("Criando subprograma '%s' com %d parametros na hash\n", id, num_parametros);
    return novo_subprograma;
}

//Terminar
int atualiza_subprograma(hash_subprogramas_t *tabela_hash, char *id, tipo_t retorno, no_parametro_t *parametros) {
    int indice = 0;
    subprograma_t *novo_subprograma = NULL;
    subprograma_t *proximo = NULL;
    subprograma_t *ultimo = NULL;

    indice = funcao_hash_subprogramas(tabela_hash, id);

    proximo = tabela_hash->tabela[indice];
    while(proximo != NULL && proximo->id != NULL && strcmp(id, proximo->id) > 0) {
        ultimo = proximo;
        proximo = proximo->proximo;
    }

    /* Já existe uma variavel. Não substitui o seu conteúdo e retorna erro. */
    if(proximo != NULL && proximo->id != NULL && strcmp(id, proximo->id) == 0) {
        return 1;

    /* Nenhum par encontrado. Cria uma nova variável. */
    } else {
        novo_subprograma = criar_novo_subprograma(id, retorno, parametros);

        /* Essa posição está no começo da lista ligada. */
        if(proximo == tabela_hash->tabela[indice]) {
            novo_subprograma->proximo = proximo;
            tabela_hash->tabela[indice] = novo_subprograma;

        /* Essa posição está no final da lista ligada. */
        } else if ( proximo == NULL ) {
            ultimo->proximo = novo_subprograma;

        /* Essa posição está no meio da lista ligada. */
        } else  {
            novo_subprograma->proximo = proximo;
            ultimo->proximo = novo_subprograma;
        }

        return 0;
    }
}

/* Busca uma variavel a partir da tabela hash. */
subprograma_t *busca_subprograma(hash_subprogramas_t *tabela_hash, char *id) {
    int indice = 0;
    subprograma_t *subprograma_encontrado;

    indice = funcao_hash_subprogramas(tabela_hash, id);

    /* Step through the bin, looking for our value. */
    subprograma_encontrado = tabela_hash->tabela[indice];
    while(subprograma_encontrado != NULL && subprograma_encontrado->id != NULL && strcmp(id, subprograma_encontrado->id) > 0) {
        subprograma_encontrado = subprograma_encontrado->proximo;
    }

    /* Did we actually find anything? */
    if(subprograma_encontrado == NULL || subprograma_encontrado->id == NULL || strcmp(id, subprograma_encontrado->id) != 0) {
        return NULL;
    } else {
        return subprograma_encontrado;
    }
}
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

int main( int argc, char **argv ) {

    tabela_hash_t *tabela_hash = criar_hash( 65536 );

    atualiza_variavel( tabela_hash, "key1", 0 , 1);
    atualiza_variavel( tabela_hash, "key2", 1 , 1);
    atualiza_variavel( tabela_hash, "key3", 2 , 1);
    atualiza_variavel( tabela_hash, "key4", 1 , 1);

    variavel_t *v1 = busca_variavel(tabela_hash, "key1");
    printf( "%s %d %d\n", v1->chave, v1->t, v1->tamanho );

    variavel_t *v2 = busca_variavel(tabela_hash, "key2");
    printf( "%s %d %d\n", v2->chave, v2->t, v2->tamanho );

    variavel_t *v3 = busca_variavel(tabela_hash, "key3");
    printf( "%s %d %d\n", v3->chave, v3->t, v3->tamanho );

    variavel_t *v4 = busca_variavel(tabela_hash, "key4");
    printf( "%s %d %d\n", v4->chave, v4->t, v4->tamanho );

    return 0;
}
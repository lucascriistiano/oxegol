#ifndef AUX_H
#define AUX_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    inteiro, real, booleano, caractere, string
} tipo_t;

typedef union valor_u {
  int   ival;  /* valor inteiro */
  float fval;  /* valor float */
  char  cval;  /* valor caractere */
  char* sval;  /* valor string */
  int   bval;  /* valor booleano - verdadeiro: 1; falso: 0; */
} valor_t;

typedef struct {
  tipo_t tipo;
  valor_t valor;
} no_literal_t;

typedef struct variavel_s {
    char *chave;
    tipo_t tipo;
    int tamanho;
    struct variavel_s *proximo;
} variavel_t;

typedef struct no_variavel_s {
  variavel_t *variavel;
  char *codigo;
  struct no_variavel_s* proximo;
} no_variavel_t;

typedef struct indices_array_s {
  int indice;
  struct indices_array_s *proximo;
} indice_array_t;

no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor);
no_variavel_t* criar_no_variavel(tipo_t tipo, valor_t valor);

int alocar_variaveis(tipo_t tipo, indice_array_t *indices_array, no_variavel_t *no_variavel);
int verificar_tipos_atribuicao(tipo_t tipo, indice_array_t *indices_array, no_variavel_t *no_variavel);

#endif
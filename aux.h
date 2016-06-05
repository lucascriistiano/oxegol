#ifndef AUX_H
#define AUX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    inteiro, real, booleano, caractere, string, vazio
} tipo_t;

typedef union valor_u {
  int   ival;  /* valor inteiro */
  float fval;  /* valor float */
  char  cval;  /* valor caractere */
  char* sval;  /* valor string */
  int   bval;  /* valor booleano - verdadeiro: 1; falso: 0; */
} valor_t;

// typedef struct codigo_tipo_s {
//   char* codigo;
//   tipo_t tipo;
// } codigo_tipo_t;

typedef struct variavel_s {
  char *id;
  tipo_t tipo;
  int tamanho;
  struct variavel_s *proximo;
} variavel_t;

typedef struct subprograma_s {
  char *id;
  tipo_t retorno;
  int num_parametros;
  tipo_t* tipos_parametros;
  struct subprograma_s *proximo;
} subprograma_t;

typedef struct no_variavel_s {
  char *id;
  char *codigo;
  tipo_t tipo;
  struct no_variavel_s* proximo;
} no_variavel_t;

typedef struct no_subprograma_s {
  subprograma_t *subprograma;
  char *codigo;
  struct no_subprograma_s* proximo;
} no_subprograma_t;

typedef struct {
  tipo_t tipo;
  valor_t valor;
} no_literal_t;

typedef struct no_expressao_s {
  char* codigo;
  tipo_t tipo;
  struct no_expressao_s *proximo;
} no_expressao_t;

typedef struct no_indices_array_s {
  int indice;
  struct no_indices_array_s *proximo;
} no_indice_array_t;

typedef struct no_operador_s {
  tipo_t tipo;                   // Tipo dos operandos aceitos
  tipo_t retorno;                // Tipo de retorno da aplicação do operador
  int num_op;                    // Numero de operandos
  char *codigo;                  // Operador a ser impresso
  struct no_operador_s *proximo; // Proximas informações de tipos aceitos e retorno do operador
} no_operador_t;

typedef struct no_parametro_s {
  char *id;                       // ID do parâmetro
  tipo_t tipo;                    // Tipo do parâmetro
  struct no_parametro_s *proximo; // Proximos parâmetros identificados
} no_parametro_t;

// codigo_tipo_t* criar_codigo_tipo(char* codigo, tipo_t tipo);
// codigo_tipo_t* criar_codigo_tipo_cast(codigo_tipo_t* codigo_tipo, tipo_t tipo_destino);

no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor);
no_expressao_t* criar_no_expressao(char* codigo, tipo_t tipo);

no_expressao_t* adicionar_no_expressao(no_expressao_t* no_expressao, no_expressao_t* nova_expressao);

no_variavel_t* criar_no_variavel(char* id, char* codigo, tipo_t tipo);
no_indice_array_t* criar_no_indice_array(int indice);
no_operador_t* criar_no_operador(char* codigo, tipo_t tipo, tipo_t retorno, int num_op);
no_parametro_t* criar_no_parametro(char *id, tipo_t tipo);

no_variavel_t* adicionar_no_variavel(no_variavel_t* no_variavel, no_variavel_t* nova_variavel);
no_indice_array_t* adicionar_no_indice_array(no_indice_array_t* indice_array, int indice);
no_operador_t* adicionar_tipo_no_operador(no_operador_t* operador, char* codigo, tipo_t tipo, tipo_t retorno, int num_op);
no_parametro_t* adicionar_no_parametro(no_parametro_t* parametros, no_parametro_t* novo_parametro);

int alocar_variaveis(tipo_t tipo, no_indice_array_t *indices_array, no_variavel_t *no_variavel);
// int verificar_tipos_atribuicao(tipo_t tipo, no_indice_array_t *indices_array, no_variavel_t *no_variavel);
int verificar_compatibilidade_operacao_binaria(no_operador_t* operador, tipo_t tipo_op1, tipo_t tipo_op2);
int verificar_compatibilidade_operacao_unaria(no_operador_t* operador, tipo_t tipo_op);
tipo_t verificar_tipo_retorno(no_operador_t* operador, tipo_t tipo);

int verificar_cast(tipo_t tipo_origem, tipo_t tipo_destino);

char* concatenar_strings(char* primeira, char* segunda);
char* gerar_label(char* comando, int numero);
int escrever_arquivo_c(char* codigo);

typedef struct se_s {
    char *expressao;
    char *comandos;
    struct se_s *proximo;
} se_t;

se_t* criar_se(char* exp, char* comandos);
void adicionar_se(se_t* se, char* exp, char* comandos);

char* gerar_para(int npara, char* id, char* exp_inicializacao, char* exp_parada, char* comandos);
char* gerar_enquanto(int nenquanto, char* exp_parada, char*comandos);
char* gerar_escolha(char* id, char* caso_um_mais, char* caso_contrario);
char* gerar_caso(char* valor, char* comandos);
char* gerar_caso_contrario(char* comandos);
char* gerar_se(int nse, se_t* ses);
char* gerar_comparar_char(char primeira, char segunda);
char* gerar_comparar_strings( char* primeira, char* segunda);
char* gerar_principal(char* comandos_opc);
char* gerar_procedimento( char* id, char* parametros_opc, char* comandos_opc);
char* gerar_funcao(char* id, char* parametros_opc, char* tipo, char* comandos_opc);
char* gerar_declaracao_ca(char* tipo, char* variavel, char* inicializacao);
char* gerar_declaracao_sa(char* tipo, char* variavel);
char* gerar_atribuicao(char* lado_esquerdo, char* lado_direito);
char* gerar_imprima(char* argumentos);
char* gerar_leia(char* id, char* tipo);
char* gerar_concatena_texto(char* destino,char* primeira, char* segunda);
char* gerar_includes();

#endif
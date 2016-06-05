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

typedef struct {
  tipo_t tipo;
  valor_t valor;
} no_literal_t;

typedef struct se_s {
    char *expressao;
    char *comandos;
    struct se_s *proximo;
} se_t;

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

typedef struct no_operador_s {
  tipo_t tipo;                   // Tipo dos operandos aceitos
  tipo_t retorno;                // Tipo de retorno da aplicação do operador
  int num_op;                    // Numero de operandos
  struct no_operador_s *proximo; // Proximas informações de tipos aceitos e retorno do operador
} no_operador_t;

se_t* criar_se(char* exp, char* comandos);
void adicionar_se(se_t* se, char* exp, char* comandos);

no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor);
no_variavel_t* criar_no_variavel(tipo_t tipo, valor_t valor);
no_operador_t* criar_no_operador(tipo_t tipo, tipo_t retorno, int num_op);

int alocar_variaveis(tipo_t tipo, indice_array_t *indices_array, no_variavel_t *no_variavel);
// int verificar_tipos_atribuicao(tipo_t tipo, indice_array_t *indices_array, no_variavel_t *no_variavel);
int verificar_compatibilidade_operacao_binaria(no_operador_t* operador, tipo_t tipo_op1, tipo_t tipo_op2);
int verificar_compatibilidade_operacao_unaria(no_operador_t* operador, tipo_t tipo_op);
tipo_t verificar_tipo_retorno(no_operador_t* operador, tipo_t tipo);

void adicionar_tipo(no_operador_t* operador, tipo_t tipo, tipo_t retorno, int num_op);

char* concatenar_strings(char* primeira, char* segunda);
char* gerar_label(char* comando, int numero);
int escrever_arquivoc(char *codigo);

char* gerar_para(int npara, char* id, char* exp_inicializacao, char* exp_parada, char* comandos);
char* gerar_enquanto(int nenquanto, char* exp_parada, char*comandos);
char* gerar_escolha(char* id, char*  caso_um_mais, char* caso_contrario);
char* gerar_caso(char* valor, char*  comandos);
char* gerar_caso_contrario(char*  comandos);
char* gerar_se(int nse, se_t* ses);
char* gerar_comparar_char(char primeira, char segunda);
char* gerar_comparar_strings( char* primeira, char* segunda);
char * gerar_principal(char* comandos_opc);
char * gerar_procedimento( char* id, char* parametros_opc, char* comandos_opc);
char* gerar_funcao(char* id, char* parametros_opc, char* tipo, char* comandos_opc);
char * gerar_declaracao_ca(char* tipo, char* variavel, char* inicializacao);
char * gerar_declaracao_sa(char* tipo, char* variavel);
char * gerar_atribuicao(char* lado_esquerdo, char* lado_direito );
char* gerar_imprima(char* argumentos);
char* gerar_leia(char* id, char* tipo);
char* gerar_concatena_texto(char* dstino,char* primeira, char* segunda);

#endif
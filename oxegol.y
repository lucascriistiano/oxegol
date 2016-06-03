%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "hash.h"
  #include "escopo.h"
  #include "aux.h"

  int yylex();
  int yyerror(char *s);
  extern int yylineno;
  extern char * yytext;
  extern FILE * yyin;

  int numero_escopo_atual = 0;
  escopo_variaveis_t *escopo_variaveis_atual;
  hash_subprogramas_t *hash_subprogramas;

  void verificar_declaracao_subprograma(hash_subprogramas_t* hash_subprogramas, char* id, tipo_t retorno, no_parametro_t *parametros);
%}

%union {
  //int   ival;  /* valor inteiro */
  //float fval;  /* valor float */
  //char  cval;  /* valor caractere */
  //char* sval;  /* valor string */
  //int   bval;  /* valor booleano - verdadeiro: 1; falso: 0; */
  char* id;  /* id value */

  valor_t valor;
  tipo_t tipo;
  no_literal_t* literal;
  no_operador_t* operadores;
  no_indice_array_t* indices_array;
  no_parametro_t* parametros;

  char* codigo;
};

%token PRINCIPAL PROCEDIMENTO FUNCAO RETORNE GLOBAL
%token PARA DE ATE ENQUANTO ESCOLHA CASO CASOCONTRARIO SE SENAO PARE
%token INTEIRO REAL STRING CARACTERE BOOLEANO BYTE REGISTRO
%token LEIA IMPRIMA COMPARATEXTO CONCATENATEXTO
%token REFERENCIA ACESSO_REGISTRO
%token PONTO DOIS_PONTOS PAR_ESQ PAR_DIR CHAVE_ESQ CHAVE_DIR COLCHETE_ESQ COLCHETE_DIR VIRGULA PONTO_E_VIRGULA ATRIBUICAO
%token RETORNA MAIS MENOS ASTERISCO BARRA MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL IGUAL DIFERENTE MOD E_BITS OU_BITS XOR_BITS DESLOCAMENTO_ESQ DESLOCAMENTO_DIR NAO_BITS
%token E_LOGICO OU_LOGICO NAO_LOGICO
%token INCREMENTO DECREMENTO
%token LITERAL_INTEIRO LITERAL_REAL LITERAL_BOOLEANO LITERAL_STRING LITERAL_CARACTERE
%token ID

%left MAIS MENOS
%left ASTERISCO BARRA MOD

%type<tipo> inicializacao_opc atribuicao tipo expressao var_declaradas terminal_exp terminal_exp_cast_opc argumentos expressao_opc array_tamanho_indice
%type<id> ID

%type<codigo> instrucao
%type<literal> literal
%type<valor> LITERAL_INTEIRO LITERAL_REAL LITERAL_BOOLEANO LITERAL_STRING LITERAL_CARACTERE
%type<operadores> operador_binario operador_logico_binario operador_logico_unario operador_aritmetico operador_relacional operador_unario incremento decremento INCREMENTO DECREMENTO

%type<indices_array> indices_array_opc indices_array array
%type<parametros> parametros_opc parametros parametro
%%

programa: secao_declaracoes_var { /* Joga codigo recebido das declaracoes de variaveis no arquivo */ } secao_declaracoes_adicionais { /* Joga codigo recebido das declaracoes de funcoes no arquivo */ } principal { /* Joga codigo recebido do procedimento principal no arquivo */ }
        ;

secao_declaracoes_var: /* vazio */
                     | GLOBAL DOIS_PONTOS declaracoes_var
                     ;

declaracoes_var: declaracao_var PONTO_E_VIRGULA
               | declaracoes_var declaracao_var PONTO_E_VIRGULA
               ;

// declaracao_var: tipo indices_array_opc var_declaradas  { alocar_variaveis($1, $2, $3);
//                                                          verificar_tipos_declaracao($1, $2, $3); }
//               ;

declaracao_var: tipo indices_array_opc var_declaradas  { if($1 != $3) { printf("Tipos incompatíveis\n");} else { printf("Compatíveis\n"); } }
              ;

var_declaradas: ID inicializacao_opc                         { $$ = $2; }
              | var_declaradas VIRGULA ID inicializacao_opc  { $$ = $4; } //Verificar se os tipos das inicializacoes sao iguais

inicializacao_opc: /* vazio */   {  }
                 | atribuicao    { $$ = $1; }
                 ;

atribuicao: ATRIBUICAO expressao     { $$ = $2; }
          ;

indices_array_opc: /* vazio */      {  }
                 | indices_array    { $$ = $1; }
                 ;

indices_array: array                { /*$$ = criar_no_indice_array(indice);*/ }
             | indices_array array  { /*$$ = adicionar_no_indice_array($1, $2);*/  }
             ;

//array: COLCHETE_ESQ array_tamanho_indice COLCHETE_DIR  { $$ = $2; }
//     ;

array: COLCHETE_ESQ array_tamanho_indice COLCHETE_DIR  {  }
     ;

array_tamanho_indice: terminal_exp   { $$ = $1; }
                    ;

abertura_bloco: CHAVE_ESQ { numero_escopo_atual++;
                            // printf("Entrando no escopo %d\n", numero_escopo_atual);
                            escopo_variaveis_atual = cria_escopo(escopo_variaveis_atual);
                          }
              ;

fechamento_bloco: CHAVE_DIR { escopo_variaveis_atual = apaga_escopo(escopo_variaveis_atual);
                              // printf("Saindo do escopo %d\n", numero_escopo_atual);
                              numero_escopo_atual--;
                            }
                ;


secao_declaracoes_adicionais: /* vazio */
                            | declaracoes
                            ;

declaracoes: declaracao
           | declaracoes declaracao
           ;

declaracao: declaracao_registro
          | declaracao_func
          | declaracao_proc
          ;

principal: PRINCIPAL PAR_ESQ PAR_DIR abertura_bloco comandos_opc fechamento_bloco
         ;

comandos_opc: /* vazio */
            | comando comandos_opc
            ;

comando: se
       | para
       | escolha
       | enquanto
       | instrucao PONTO_E_VIRGULA
       ;

instrucao: retorne                          { }
         | PARE                             { }
         | declaracao_var                   { }
         | ID indices_array_opc atribuicao  { } //Verificar: se id está declarado para todos IDs
         | ID incremento                    { int operando_compativel = verificar_compatibilidade_operacao_unaria($2, inteiro); //só para testes mudar
                                              //int operando_compativel = verificar_compatibilidade_operacao_unaria($2, $1);
                                              if(operando_compativel) { $$ = "incremento"; }
                                              else { yyerror("Tipo não suportado"); }
                                            }
         | ID decremento                    { int operando_compativel = verificar_compatibilidade_operacao_unaria($2, inteiro); //Só para testes mudar
                                              //int operando_compativel = verificar_compatibilidade_operacao_unaria($2, $1);
                                              if(operando_compativel) { $$ = "decremento"; }
                                              else { yyerror("Tipo não suportado"); }
                                            }
         | ID argumentos_chamada            { }
         | ID campos_registro atribuicao    { }
         | IMPRIMA argumentos_chamada       { }
         | LEIA PAR_ESQ ID PAR_DIR          { }
         | COMPARATEXTO PAR_ESQ terminal_exp VIRGULA terminal_exp PAR_DIR {}
         | ID indices_array_opc concatena_texto  {}
         ;

concatena_texto: ATRIBUICAO CONCATENATEXTO PAR_ESQ terminal_exp VIRGULA terminal_exp PAR_DIR //Desalocar a variavel



incremento: INCREMENTO  { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 1); $$ = operadores; }
          ;

decremento: DECREMENTO  { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 1); $$ = operadores; }
          ;

campos_registro: PONTO ID
               | campos_registro PONTO ID

declaracao_func: FUNCAO ID PAR_ESQ parametros_opc PAR_DIR RETORNA tipo { verificar_declaracao_subprograma(hash_subprogramas, $2, $7, $4); } abertura_bloco { /* jogar variaveis na tabela de variaveis */  } comandos_opc fechamento_bloco { /* gera e joga código pra cima */ }
               ;

declaracao_proc: PROCEDIMENTO ID PAR_ESQ parametros_opc PAR_DIR  { verificar_declaracao_subprograma(hash_subprogramas, $2, vazio, $4); } abertura_bloco { /* jogar variaveis na tabela de variaveis */  } comandos_opc fechamento_bloco { /* gera e joga código pra cima */ }
               ;

declaracao_registro: REGISTRO ID abertura_bloco campo_um_mais fechamento_bloco
                   ;

campo_um_mais: campo
             | campo_um_mais campo
             ;

campo: tipo indices_array_opc ID PONTO_E_VIRGULA
     ;

parametros_opc: /* vazio */ { $$ = NULL; }
              | parametros  { $$ = $1; }
              ;

parametros: parametro                     { $$ = $1; }
          | parametro VIRGULA parametros  { $$ = adicionar_no_parametro($1, $3); }
          ;

parametro: ref_opc tipo ID  { $$ = criar_no_parametro($3, $2); }
         ;

ref_opc: /* vazio */ {  }
       | REFERENCIA  {  }
       ;

tipo: INTEIRO               { $$ = inteiro; }
    | REAL                  { $$ = real; }
    | STRING                { $$ = string; }
    | CARACTERE             { $$ = caractere; }
    | BOOLEANO              { $$ = booleano; }
    | BYTE                  { $$ = caractere; }
    | ACESSO_REGISTRO ID    { /* $$ = $2; */ $$ = inteiro; /* só para testes, mudar */ }
    ;

literal: LITERAL_INTEIRO     { $$ = criar_no_literal(inteiro, $1); }
       | LITERAL_REAL        { $$ = criar_no_literal(real, $1); }
       | LITERAL_BOOLEANO    { $$ = criar_no_literal(booleano, $1); }
       | LITERAL_STRING      { $$ = criar_no_literal(string, $1); }
       | LITERAL_CARACTERE   { $$ = criar_no_literal(caractere, $1); }
       ;

se: SE PAR_ESQ expressao PAR_DIR abertura_bloco comandos_opc fechamento_bloco senao_opc
  ;

senao_opc: /* vazio */
         | senao
         | senao_se
         ;

senao: SENAO abertura_bloco comandos_opc fechamento_bloco
     ;

senao_se: SENAO se
        ;

para: PARA PAR_ESQ ID DE expressao ATE expressao PAR_DIR abertura_bloco comandos_opc fechamento_bloco
    ;

escolha: ESCOLHA PAR_ESQ ID PAR_DIR abertura_bloco caso_um_mais caso_contrario fechamento_bloco
       ;

caso_um_mais: caso caso_opc
            ;

caso: CASO literal DOIS_PONTOS comandos_opc
    ;

caso_opc: /* vazio */
        | caso_opc caso
        ;

caso_contrario: CASOCONTRARIO DOIS_PONTOS comandos_opc
              ;

enquanto: ENQUANTO PAR_ESQ expressao PAR_DIR abertura_bloco comandos_opc fechamento_bloco
        ;

retorne: RETORNE expressao_opc
       ;

expressao: terminal_exp_cast_opc operador_binario expressao   { int tipos_compativeis = verificar_compatibilidade_operacao_binaria($2, $1, $3);
                                                                if(tipos_compativeis) { $$ = verificar_tipo_retorno($2, $1); }
                                                                else { yyerror("Tipos incompatíveis"); }
                                                              }
         | operador_unario expressao                          { int operando_compativel = verificar_compatibilidade_operacao_unaria($1, $2);
                                                                if(operando_compativel) { $$ = verificar_tipo_retorno($1, $2); }
                                                                else { yyerror("Tipo não suportado"); }
                                                              }
         | PAR_ESQ expressao PAR_DIR                          { $$ = $2; }
         | PAR_ESQ expressao PAR_DIR operador_binario terminal_exp_cast_opc { $$ = $2; }
         | terminal_exp_cast_opc                              { $$ = $1; }
         ;

expressao_opc: /* vazio */  { }
             | expressao    { $$ = $1; }
             ;

operador_binario: operador_logico_binario  { $$ = $1; }
                | operador_aritmetico      { $$ = $1; }
                | operador_relacional      { $$ = $1; }
                ;

operador_logico_binario: E_LOGICO    { no_operador_t* operadores = criar_no_operador(booleano, booleano, 2); $$ = operadores; }
                       | OU_LOGICO   { no_operador_t* operadores = criar_no_operador(booleano, booleano, 2); $$ = operadores; }
                       | E_BITS      { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); $$ = operadores; }
                       | OU_BITS     { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); $$ = operadores; }
                       | XOR_BITS    { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); $$ = operadores; }
                       ;

operador_aritmetico: MAIS               { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); adicionar_tipo(operadores, real, real, 2); $$ = operadores; }
                   | MENOS              { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); adicionar_tipo(operadores, real, real, 2); $$ = operadores; }
                   | ASTERISCO          { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); adicionar_tipo(operadores, real, real, 2); $$ = operadores; }
                   | BARRA              { no_operador_t* operadores = criar_no_operador(inteiro, real, 2); adicionar_tipo(operadores, real, real, 2); $$ = operadores; }
                   | MOD                { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); $$ = operadores; }
                   | DESLOCAMENTO_ESQ   { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); $$ = operadores; }
                   | DESLOCAMENTO_DIR   { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 2); $$ = operadores; }
                   ;

operador_relacional: MENOR        { no_operador_t* operadores = criar_no_operador(inteiro, booleano, 2); adicionar_tipo(operadores, real, booleano, 2); $$ = operadores; }
                   | MAIOR        { no_operador_t* operadores = criar_no_operador(inteiro, booleano, 2); adicionar_tipo(operadores, real, booleano, 2); $$ = operadores; }
                   | MENOR_IGUAL  { no_operador_t* operadores = criar_no_operador(inteiro, booleano, 2); adicionar_tipo(operadores, real, booleano, 2); $$ = operadores; }
                   | MAIOR_IGUAL  { no_operador_t* operadores = criar_no_operador(inteiro, booleano, 2); adicionar_tipo(operadores, real, booleano, 2); $$ = operadores; }
                   | IGUAL        { no_operador_t* operadores = criar_no_operador(inteiro, booleano, 2); adicionar_tipo(operadores, real, booleano, 2); adicionar_tipo(operadores, booleano, booleano, 2); $$ = operadores; }
                   | DIFERENTE    { no_operador_t* operadores = criar_no_operador(inteiro, booleano, 2); adicionar_tipo(operadores, real, booleano, 2); adicionar_tipo(operadores, booleano, booleano, 2); $$ = operadores; }
                   ;

operador_unario: operador_logico_unario    { $$ = $1; }
               | MENOS                     { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 1); adicionar_tipo(operadores, real, real, 1); $$ = operadores; }
               ;

operador_logico_unario: NAO_LOGICO   { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 1); $$ = operadores; }
                      | NAO_BITS     { no_operador_t* operadores = criar_no_operador(inteiro, inteiro, 1); $$ = operadores; }
                      ;

terminal_exp_cast_opc: PAR_ESQ tipo PAR_DIR terminal_exp  { $$ = $2; } //Verificar se o terminal pode ser convertido nesse tipo
                     | terminal_exp                       { $$ = $1; }
                     ;

terminal_exp: literal                  { $$ = $1->tipo; }  //Retorna o tipo do literal
            | ID                       { $$ = inteiro; /*Só para testes, mudar!!*/ }  //Consulta na tabela a variável e retorna o seu tipo
            | ID argumentos_chamada    {  }  //Consulta na tabela o procedimento/função e retorna o seu tipo de retorno
            | ID indices_array         {  }  //Consulta na tabela o array e retorna o seu tipo
            | ID campos_registro       {  }  //Consulta na tabela o campo do registro e retorna o seu tipo
            ;

argumentos_chamada: PAR_ESQ argumentos PAR_DIR  {  }  //
                  ;

argumentos: expressao                      { $$ = $1; }  //Adicionar e retornar um array com o tipo da expressao
          | expressao VIRGULA argumentos   {  }  //Adicionar e retornar um array com o tipo da expressao
          ;

%%

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s nome_do_arquivo", argv[0]);
    } else {
        char *filename = argv[1];
        FILE *file = fopen(filename,"r+");

        if(file == NULL) {
            printf("Não foi possível abrir o arquivo.\n");
        } else {
            escopo_variaveis_atual = cria_escopo(escopo_variaveis_atual);
            hash_subprogramas = criar_hash_subprogramas(TAMANHO_HASH);

            yyin = file;
            yylineno = 1;
            yyparse();
            //Compilar arquivo
            //Apagar arquivo
        }

        fclose(file);
    }
}

int yyerror (char *msg) {
  fprintf (stderr, "%d: %s próximo de '%s'\n", yylineno, msg, yytext);
  return 0;
}

void verificar_declaracao_subprograma(hash_subprogramas_t* hash_subprogramas, char* id, tipo_t retorno, no_parametro_t *parametros) {
  subprograma_t* subprograma_encontrado = busca_subprograma(hash_subprogramas, id);
  if(subprograma_encontrado == NULL) {
    int subprograma_alocado = atualiza_subprograma(hash_subprogramas, id, retorno, parametros);
    if(subprograma_alocado == 0) {
      printf("DECLAROU %s\n", id);
    }
  } else {
    yyerror("Redefinição de subprograma");
  }
}
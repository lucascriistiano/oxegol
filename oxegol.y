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

  void declarar_variaveis(escopo_variaveis_t* escopo_variaveis_atual, tipo_t tipo, no_indice_array_t* indices_array, no_variavel_t* variaveis);
  void declarar_subprograma(hash_subprogramas_t* hash_subprogramas, char* id, tipo_t retorno, no_parametro_t *parametros);
%}

%union {
  char* id;  /* id value */

  char* codigo;
  tipo_t tipo;
  valor_t valor;

  no_literal_t* literal;
  no_expressao_t* expressao;

  no_variavel_t* variaveis;
  no_indice_array_t* indices_array;
  no_operador_t* operadores;
  no_parametro_t* parametros;
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

%type<id> ID

%type<codigo> secao_declaracoes_var secao_declaracoes_adicionais declaracoes declaracao declaracao_registro declaracao_func declaracao_proc comandos_opc comando se para escolha enquanto principal declaracoes_var declaracao_var instrucao caso caso_opc caso_contrario caso_um_mais
%type<tipo> tipo array_tamanho_indice
%type<valor> LITERAL_INTEIRO LITERAL_REAL LITERAL_BOOLEANO LITERAL_STRING LITERAL_CARACTERE

%type<literal> literal
%type<expressao> expressao terminal_exp terminal_exp_cast_opc atribuicao atribuicao_opc argumentos argumentos_opc

%type<variaveis> var_declaradas id_atribuicao_opc
%type<indices_array> indices_array_opc indices_array array
%type<operadores> operador_binario operador_logico_binario operador_logico_unario operador_aritmetico operador_relacional operador_unario incremento decremento INCREMENTO DECREMENTO
%type<parametros> parametros_opc parametros parametro
%%

programa: secao_declaracoes_var { printf("%s\n", $1); /* escrever_arquivoc($1); */ } secao_declaracoes_adicionais { printf("%s\n", $3); /* escrever_arquivoc($3); */ } principal { printf("%s\n", $5); /* escrever_arquivoc($5); */ }
        ;

secao_declaracoes_var: /* vazio */                        { $$ = ""; }
                     | GLOBAL DOIS_PONTOS declaracoes_var { $$ = $3; }
                     ;

declaracoes_var: declaracao_var PONTO_E_VIRGULA                   { $$ = concatenar_strings($1, ";"); }
               | declaracoes_var declaracao_var PONTO_E_VIRGULA   { char* declaracao_final = concatenar_strings($2, ";");
                                                                    $$ = concatenar_strings($1, declaracao_final); //Deve dar free?
                                                                  }
               ;

declaracao_var: tipo indices_array_opc var_declaradas { declarar_variaveis(escopo_variaveis_atual, $1, $2, $3); $$ = "declaracao"; /* $$ = gerar_declaracao($1, $2, $3); */ }
              ;

var_declaradas: id_atribuicao_opc                         { $$ = $1; }
              | var_declaradas VIRGULA id_atribuicao_opc  { $$ = adicionar_no_variavel($1, $3); } //Verificar se os tipos das inicializacoes sao iguais

id_atribuicao_opc: ID atribuicao_opc  { if($2 == NULL) {
                                          $$ = criar_no_variavel($1, $1, vazio);  //Define variavel não inicializada com o tipo vazio
                                        } else {
                                          char* variavel_com_inicializacao = concatenar_strings($1, $2->codigo);
                                          $$ = criar_no_variavel($1, variavel_com_inicializacao, $2->tipo);
                                        }
                                      }
                                      ;

atribuicao_opc: /* vazio */   { $$ = NULL; }
              | atribuicao    { $$ = $1; }
              ;

atribuicao: ATRIBUICAO expressao  { char* codigo_atribuicao = concatenar_strings("=", $2->codigo);
                                    no_expressao_t* no_expressao = criar_no_expressao(codigo_atribuicao, $2->tipo);
                                    $$ = no_expressao;
                                  }
          ;

indices_array_opc: /* vazio */      {  }
                 | indices_array    { $$ = $1; }
                 ;

indices_array: array                { /*$$ = criar_no_indice_array(indice);*/ }
             | indices_array array  { /*$$ = adicionar_no_indice_array($1, $2);*/  }
             ;

array: COLCHETE_ESQ array_tamanho_indice COLCHETE_DIR  {  }
     ;

array_tamanho_indice: terminal_exp   { $$ = $1->tipo; }
                    ;

abertura_bloco: CHAVE_ESQ { numero_escopo_atual++;
                            escopo_variaveis_atual = cria_escopo(escopo_variaveis_atual);
                          }
              ;

fechamento_bloco: CHAVE_DIR { escopo_variaveis_atual = apaga_escopo(escopo_variaveis_atual);
                              numero_escopo_atual--;
                            }
                ;

secao_declaracoes_adicionais: /* vazio */  { $$ = ""; }
                            | declaracoes  { $$ = $1; }
                            ;

declaracoes: declaracao              { $$ = $1; }
           | declaracoes declaracao  { $$ = concatenar_strings($1, $2); }
           ;

declaracao: declaracao_registro  { $$ = $1; }
          | declaracao_func      { $$ = $1; }
          | declaracao_proc      { $$ = $1; }
          ;

principal: PRINCIPAL PAR_ESQ PAR_DIR abertura_bloco comandos_opc fechamento_bloco  { $$ = "principal"; /* $$ = gerar_principal($5); */ }
         ;

comandos_opc: /* vazio */           { $$ = ""; }
            | comando comandos_opc  { $$ = concatenar_strings($1, $2); }
            ;

comando: se                          { $$ = $1; }
       | para                        { $$ = $1; }
       | escolha                     { $$ = $1; }
       | enquanto                    { $$ = $1; }
       | instrucao PONTO_E_VIRGULA   { $$ = concatenar_strings($1, ";"); }
       ;

instrucao: PARE                                 { $$ = "break"; }
         | declaracao_var                       { $$ = $1; }
         | ID indices_array_opc atribuicao      { /* Verificar se o id está declarado e os limites */ $$ = "atribuicao";  /* $$ = gerar_atribuicao($1, $2, $3); */ } //Verificar: se id está declarado para todos IDs
         | ID incremento                        { int operando_compativel = verificar_compatibilidade_operacao_unaria($2, inteiro); //só para testes mudar
                                                  //int operando_compativel = verificar_compatibilidade_operacao_unaria($2, $1);
                                                  if(operando_compativel) {
                                                    $$ = "incremento";
                                                  } else {
                                                    yyerror("Tipo não suportado");
                                                  }
                                                }
         | ID decremento                        { int operando_compativel = verificar_compatibilidade_operacao_unaria($2, inteiro); //Só para testes mudar
                                                  //int operando_compativel = verificar_compatibilidade_operacao_unaria($2, $1);
                                                  if(operando_compativel) {
                                                    $$ = "decremento";
                                                  } else {
                                                    yyerror("Tipo não suportado");
                                                  }
                                                }
         | ID PAR_ESQ argumentos_opc PAR_DIR    { /*verificar existência e parâmetros de subproc*/  /* gerar e retornar string de chama de subproc */ $$ = "instSubprograma(argumentos)"; }
         | ID campos_registro atribuicao        { /* gerar e retornar string de atribuicao a registro */ $$ = "registro.campo = valor"; }
         | IMPRIMA PAR_ESQ argumentos PAR_DIR   { /* gerar e retornar string do comando do imprima */ $$ = "imprima"; }
         | LEIA PAR_ESQ ID PAR_DIR              { /* gerar e retornar string do comando do leia */ $$ = "leia"; }
         | COMPARATEXTO PAR_ESQ terminal_exp VIRGULA terminal_exp PAR_DIR {  }
         | ID indices_array_opc ATRIBUICAO CONCATENATEXTO PAR_ESQ terminal_exp VIRGULA terminal_exp PAR_DIR  { $$ = "concatena_texto"; /* $$ = gerar_concatena_texto($1, $2, $6, $8); */ } //Desalocar a variavel
         ;

incremento: INCREMENTO  { no_operador_t* operadores = criar_no_operador("++", inteiro, inteiro, 1); $$ = operadores; }
          ;

decremento: DECREMENTO  { no_operador_t* operadores = criar_no_operador("--", inteiro, inteiro, 1); $$ = operadores; }
          ;

campos_registro: PONTO ID
               | campos_registro PONTO ID

declaracao_func: FUNCAO ID PAR_ESQ parametros_opc PAR_DIR RETORNA tipo { declarar_subprograma(hash_subprogramas, $2, $7, $4); } abertura_bloco { /* jogar variaveis na tabela de variaveis */  } comandos_opc retorne { /* verificar se o retorno é do tipo da função */ } fechamento_bloco { $$ = "declaracao_funcao"; /* gera e joga código pra cima */ }
               ;

declaracao_proc: PROCEDIMENTO ID PAR_ESQ parametros_opc PAR_DIR  { declarar_subprograma(hash_subprogramas, $2, vazio, $4); } abertura_bloco { /* jogar variaveis na tabela de variaveis */  } comandos_opc fechamento_bloco { $$ = "declaracao_proc"; /* gera e joga código pra cima */ }
               ;

declaracao_registro: REGISTRO ID abertura_bloco campo_um_mais fechamento_bloco { $$ = "declaracao_registro"; }
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
    | ACESSO_REGISTRO ID    { /*Consultar na hash o tipo e retornar*/ $$ = inteiro; /* só para testes, mudar */ }
    ;

literal: LITERAL_INTEIRO     { $$ = criar_no_literal(inteiro, $1); }
       | LITERAL_REAL        { $$ = criar_no_literal(real, $1); }
       | LITERAL_BOOLEANO    { $$ = criar_no_literal(booleano, $1); }
       | LITERAL_STRING      { $$ = criar_no_literal(string, $1); }
       | LITERAL_CARACTERE   { $$ = criar_no_literal(caractere, $1); }
       ;

se: SE PAR_ESQ expressao PAR_DIR abertura_bloco comandos_opc fechamento_bloco senao_opc  { $$ = "se"; }
  ;

senao_opc: /* vazio */
         | senao
         | senao_se
         ;

senao: SENAO abertura_bloco comandos_opc fechamento_bloco
     ;

senao_se: SENAO se
        ;

para: PARA PAR_ESQ ID DE expressao ATE expressao PAR_DIR abertura_bloco comandos_opc fechamento_bloco  { $$ = "para"; }
    ;

escolha: ESCOLHA PAR_ESQ ID PAR_DIR abertura_bloco caso_um_mais caso_contrario fechamento_bloco  { $$ = "escolha"; }
       ;

caso_um_mais: caso caso_opc  { $$ = concatenar_strings($1, $2); }
            ;

caso: CASO literal DOIS_PONTOS comandos_opc  { $$ = "caso"; }
    ;

caso_opc: /* vazio */     { $$ = ""; }
        | caso_opc caso   { $$ = concatenar_strings($1, $2); }
        ;

caso_contrario: CASOCONTRARIO DOIS_PONTOS comandos_opc   { /*gerar e retornar caso_contario*/ $$ = "caso_contrario"; }
              ;

enquanto: ENQUANTO PAR_ESQ expressao PAR_DIR abertura_bloco comandos_opc fechamento_bloco  { $$ = "enquanto"; }
        ;

retorne: RETORNE expressao PONTO_E_VIRGULA { /* Gerar codigo do retorno e retorna o tipo e o código dele */ }
       ;

expressao: terminal_exp_cast_opc operador_binario expressao   { int tipos_compativeis = verificar_compatibilidade_operacao_binaria($2, $1->tipo, $3->tipo);
                                                                if(tipos_compativeis) {
                                                                  /* criar codigo da expressao concatenando os dois elementos e operador */
                                                                  char* codigo_exp = "codigo_expressao_binaria";
                                                                  tipo_t tipo_retorno = verificar_tipo_retorno($2, $1->tipo);
                                                                  no_expressao_t* no_expressao = criar_no_expressao(codigo_exp, tipo_retorno);
                                                                  $$ = no_expressao;
                                                                } else {
                                                                  yyerror("Tipos incompatíveis");
                                                                }
                                                              }
         | operador_unario expressao                          { int operando_compativel = verificar_compatibilidade_operacao_unaria($1, $2->tipo);
                                                                if(operando_compativel) {
                                                                  /* criar codigo da expressao concatenando elemento e operador */
                                                                  char* codigo_exp = "codigo_expressao_unaria";
                                                                  tipo_t tipo_retorno = verificar_tipo_retorno($1, $2->tipo);
                                                                  no_expressao_t* no_expressao = criar_no_expressao(codigo_exp, tipo_retorno);
                                                                  $$ = no_expressao;
                                                                } else {
                                                                  yyerror("Tipo não suportado");
                                                                }
                                                              }
         | PAR_ESQ expressao PAR_DIR                          { $$ = $2; }
         | PAR_ESQ expressao PAR_DIR operador_binario terminal_exp_cast_opc { int tipos_compativeis = verificar_compatibilidade_operacao_binaria($4, $2->tipo, $5->tipo);
                                                                              if(tipos_compativeis) {
                                                                                /* criar codigo da expressao concatenando os parenteses, codigo da exp, terminal e operador */
                                                                                char* codigo_exp = "codigo_expressao_binaria_parentizada";
                                                                                tipo_t tipo_retorno = verificar_tipo_retorno($4, $2->tipo);
                                                                                no_expressao_t* no_expressao = criar_no_expressao(codigo_exp, tipo_retorno);
                                                                                $$ = no_expressao;
                                                                              } else {
                                                                                yyerror("Tipos incompatíveis");
                                                                              }
                                                                            }
         | terminal_exp_cast_opc                              { $$ = $1; }
         ;

operador_binario: operador_logico_binario  { $$ = $1; }
                | operador_aritmetico      { $$ = $1; }
                | operador_relacional      { $$ = $1; }
                ;

operador_logico_binario: E_LOGICO    { no_operador_t* operadores = criar_no_operador("&&", booleano, booleano, 2); $$ = operadores; }
                       | OU_LOGICO   { no_operador_t* operadores = criar_no_operador("||", booleano, booleano, 2); $$ = operadores; }
                       | E_BITS      { no_operador_t* operadores = criar_no_operador("&", inteiro, inteiro, 2); $$ = operadores; }
                       | OU_BITS     { no_operador_t* operadores = criar_no_operador("|", inteiro, inteiro, 2); $$ = operadores; }
                       | XOR_BITS    { no_operador_t* operadores = criar_no_operador("^", inteiro, inteiro, 2); $$ = operadores; }
                       ;

operador_aritmetico: MAIS               { no_operador_t* operadores = criar_no_operador("+", inteiro, inteiro, 2); adicionar_tipo_no_operador(operadores, "+", real, real, 2); $$ = operadores; }
                   | MENOS              { no_operador_t* operadores = criar_no_operador("-", inteiro, inteiro, 2); adicionar_tipo_no_operador(operadores, "-", real, real, 2); $$ = operadores; }
                   | ASTERISCO          { no_operador_t* operadores = criar_no_operador("*", inteiro, inteiro, 2); adicionar_tipo_no_operador(operadores, "*", real, real, 2); $$ = operadores; }
                   | BARRA              { no_operador_t* operadores = criar_no_operador("/", inteiro, real, 2); adicionar_tipo_no_operador(operadores, "/", real, real, 2); $$ = operadores; }
                   | MOD                { no_operador_t* operadores = criar_no_operador("%", inteiro, inteiro, 2); $$ = operadores; }
                   | DESLOCAMENTO_ESQ   { no_operador_t* operadores = criar_no_operador("<<", inteiro, inteiro, 2); $$ = operadores; }
                   | DESLOCAMENTO_DIR   { no_operador_t* operadores = criar_no_operador(">>", inteiro, inteiro, 2); $$ = operadores; }
                   ;

operador_relacional: MENOR        { no_operador_t* operadores = criar_no_operador("<", inteiro, booleano, 2); adicionar_tipo_no_operador(operadores, "<", real, booleano, 2); $$ = operadores; }
                   | MAIOR        { no_operador_t* operadores = criar_no_operador(">", inteiro, booleano, 2); adicionar_tipo_no_operador(operadores, ">", real, booleano, 2); $$ = operadores; }
                   | MENOR_IGUAL  { no_operador_t* operadores = criar_no_operador("<=", inteiro, booleano, 2); adicionar_tipo_no_operador(operadores, "<=", real, booleano, 2); $$ = operadores; }
                   | MAIOR_IGUAL  { no_operador_t* operadores = criar_no_operador(">=", inteiro, booleano, 2); adicionar_tipo_no_operador(operadores, ">=", real, booleano, 2); $$ = operadores; }
                   | IGUAL        { no_operador_t* operadores = criar_no_operador("==", inteiro, booleano, 2); adicionar_tipo_no_operador(operadores, "==", real, booleano, 2); adicionar_tipo_no_operador(operadores, "==", booleano, booleano, 2); $$ = operadores; }
                   | DIFERENTE    { no_operador_t* operadores = criar_no_operador("!=", inteiro, booleano, 2); adicionar_tipo_no_operador(operadores, "!=", real, booleano, 2); adicionar_tipo_no_operador(operadores, "!=", booleano, booleano, 2); $$ = operadores; }
                   ;

operador_unario: operador_logico_unario    { $$ = $1; }
               | MENOS                     { no_operador_t* operadores = criar_no_operador("-", inteiro, inteiro, 1); adicionar_tipo_no_operador(operadores, "-", real, real, 1); $$ = operadores; }
               ;

operador_logico_unario: NAO_LOGICO   { no_operador_t* operadores = criar_no_operador("!", inteiro, inteiro, 1); $$ = operadores; }
                      | NAO_BITS     { no_operador_t* operadores = criar_no_operador("~", inteiro, inteiro, 1); $$ = operadores; }
                      ;

terminal_exp_cast_opc: PAR_ESQ tipo PAR_DIR terminal_exp  { if(verificar_cast($4->tipo, $2) == 1) {  //Verificar se o terminal pode ser convertido nesse tipo
                                                              //Adicionar geracao de codigo com cast
                                                              $$ = criar_no_expressao($4->codigo, $2); //Substituir primeiro parametro pelo codigo gerado
                                                            } else {
                                                              yyerror("Conversão entre tipos não suportada");
                                                            }
                                                          }
                     | terminal_exp                       { $$ = $1; }
                     ;

terminal_exp: literal                              { /*Converter o literal para string*/ $$ = criar_no_expressao("literal", $1->tipo); }  //Retorna o tipo do nó literal
            | ID                                   { $$ = criar_no_expressao("id", inteiro); }        //Só para testes, mudar para consultar na tabela a variável e retorna o seu tipo
            | ID PAR_ESQ argumentos_opc PAR_DIR    { $$ = criar_no_expressao("id(args)", inteiro); }  //Só para testes, mudar para consultar na tabela o procedimento/função e retorna o seu tipo de retorno
            | ID indices_array                     { $$ = criar_no_expressao("id[i][j]", inteiro); }  //Só para testes, mudar para consultar na tabela o array e retorna o seu tipo
            | ID campos_registro                   { $$ = criar_no_expressao("id.campo", inteiro); }  //Só para testes, mudar para consultar na tabela o campo do registro e retorna o seu tipo
            ;

argumentos_opc: /* vazio */  { $$ = NULL; }
              | argumentos   { $$ = $1; }
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
          // system("./compilaEApaga");
        }

        fclose(file);
    }
}

int yyerror (char *msg) {
  fprintf (stderr, "%d: %s próximo de '%s'\n", yylineno, msg, yytext);
  return 0;
}

void declarar_variaveis(escopo_variaveis_t* escopo_variaveis_atual, tipo_t tipo, no_indice_array_t* indices_array, no_variavel_t* variaveis) {
  //Declarar cada variável
  int i = 1;
  no_variavel_t* no_variavel_atual = variaveis;
  while(no_variavel_atual != NULL) { //Erro aqui -> Não era pra entrar uma segunda vez
    variavel_t* variavel_encontrada = consulta_escopo_atual(escopo_variaveis_atual, no_variavel_atual->id);
    if(variavel_encontrada == NULL) {
      int variavel_declarada = criar_variavel_escopo_atual(escopo_variaveis_atual, no_variavel_atual->id, tipo, 0); //Definir tamanho!!!
      if(variavel_declarada == 0) {
        printf("DECLAROU %s\n", no_variavel_atual->id);
      }
    } else {
      yyerror("Redefinição de variavel");
    }
    no_variavel_atual = no_variavel_atual->proximo;
  }

  //Fazer verificação de tipos para cada variavel inicializada
  // if($1 != $3) {
  //   printf("Tipos incompatíveis\n");
  // } else {
  //   printf("Compatíveis\n");
  // }
}

void declarar_subprograma(hash_subprogramas_t* hash_subprogramas, char* id, tipo_t retorno, no_parametro_t *parametros) {
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

void verificar_chamada_subprograma(hash_subprogramas_t* hash_subprogramas, char* id, no_parametro_t *parametros) {

}
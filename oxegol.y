%{
    #include "stdio.h"
    #include "y.tab.h"

    int yylex();
    int yyerror(char *s);
    extern int yylineno;
    extern char * yytext;
%}

%union {
  int    ival;  /* integer value */
  float  fval;  /* float value */
  char   cval;  /* char value */
  char * sval;  /* string value */
};

%token PRINCIPAL PROCEDIMENTO FUNCAO RETORNE
%token PARA DE ATE ENQUANTO ESCOLHA CASO CASOCONTRARIO SE SENAO PARE
%token INTEIRO REAL STRING CARACTERE BOOLEANO BYTE REGISTRO
%token REFERENCIA
%token DOIS_PONTOS PAR_ESQ PAR_DIR CHAVE_ESQ CHAVE_DIR COLCHETE_ESQ COLCHETE_DIR VIRGULA PONTO_E_VIRGULA ATRIBUICAO
%token RETORNA MAIS MENOS ASTERISCO BARRA MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL IGUAL DIFERENTE MOD E_BITS OU_BITS XOR_BITS DESLOCAMENTO_ESQ DESLOCAMENTO_DIR NAO_BITS
%token E_LOGICO OU_LOGICO NAO_LOGICO
%token INCREMENTO DECREMENTO
%token LITERAL_INTEIRO LITERAL_REAL LITERAL_BOOLEANO LITERAL_STRING LITERAL_CARACTERE
%token ID

%left MAIS MENOS
%left ASTERISCO BARRA MOD

%%

programa: declaracoes_var_opc declaracoes_opc principal
        ;

declaracoes_var_opc: /* vazio */
                   | declaracoes_var
                   ;

declaracoes_var: declaracao_var
               | declaracoes_var declaracao_var
               ;

declaracao_var: tipo ID var_compl
              ;

var_compl: /* vazio */
         | atribuicao
         | array_um_mais
         ;

atribuicao: ATRIBUICAO expressao
          ;

array_um_mais: array
             | array_um_mais array
             ;

array: COLCHETE_ESQ array_tamanho COLCHETE_DIR
     ;

array_tamanho: ID
             | LITERAL_INTEIRO
             ;

declaracoes_opc: /* vazio */
               | declaracoes
               ;

declaracoes: declaracao
           | declaracoes declaracao
           ;

declaracao: declaracao_registro
          | declaracao_func
          | declaracao_proc
          ;

principal: PRINCIPAL CHAVE_ESQ comandos_opc CHAVE_DIR
         ;

comandos_opc: /* vazio */
            | comando PONTO_E_VIRGULA comandos_opc
            ;

declaracao_func: FUNCAO ID PAR_ESQ parametros_opc PAR_DIR RETORNA tipo CHAVE_ESQ comandos_opc CHAVE_DIR
               ;

declaracao_proc: PROCEDIMENTO ID PAR_ESQ parametros_opc PAR_DIR CHAVE_ESQ comandos_opc CHAVE_DIR
               ;

declaracao_registro: REGISTRO ID CHAVE_ESQ campo_um_mais CHAVE_DIR
                   ;

campo_um_mais: campo
             | campo_um_mais campo
             ;

campo: tipo ID PONTO_E_VIRGULA
     ;

parametros_opc: /* vazio */
              | parametros
              ;

parametros: parametro
          | parametro VIRGULA parametros
          ;

parametro: ref_opc tipo ID
         ;

ref_opc: /* vazio */
       | REFERENCIA
       ;

tipo: INTEIRO
    | REAL
    | STRING
    | CARACTERE
    | BOOLEANO
    | BYTE
    | ID
    ;

literal: LITERAL_INTEIRO    { printf("Literal inteiro: %d", yyval.ival); }
       | LITERAL_REAL
       | LITERAL_BOOLEANO
       | LITERAL_STRING
       | LITERAL_CARACTERE
       ;

comando: se
       | para
       | escolha
       | enquanto
       | retorne
       | PARE
       ;

se: SE PAR_ESQ expressao PAR_DIR CHAVE_ESQ comandos_opc CHAVE_DIR senao_opc
  ;

senao_opc: /* vazio */
         | senao
         | senao_se
         ;

senao: SENAO CHAVE_ESQ comandos_opc CHAVE_DIR
     ;

senao_se: SENAO se
        ;

para: PARA PAR_ESQ ID DE expressao ATE expressao PAR_DIR CHAVE_ESQ comandos_opc CHAVE_DIR
    ;

escolha: ESCOLHA PAR_ESQ ID PAR_DIR CHAVE_ESQ caso_um_mais caso_contrario CHAVE_DIR
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

enquanto: ENQUANTO PAR_ESQ expressao PAR_DIR CHAVE_ESQ comandos_opc CHAVE_DIR
        ;

retorne: RETORNE expressao_opc
       ;

expressao: terminal_exp operador_binario expressao
         | operador_unario expressao
         | PAR_ESQ expressao PAR_DIR
         | terminal_exp
         ;

expressao_opc: /* vazio */
             | expressao
             ;

operador_binario: operador_logico_binario
                | operador_aritmetico
                | operador_relacional
                ;

operador_logico_binario: E_LOGICO
                       | OU_LOGICO
                       | E_BITS
                       | OU_BITS
                       | XOR_BITS
                       ;

operador_aritmetico: MAIS       { printf("+\n"); }
                   | MENOS
                   | ASTERISCO
                   | BARRA
                   | MOD
                   | DESLOCAMENTO_ESQ
                   | DESLOCAMENTO_DIR
                   ;

operador_relacional: MENOR
                   | MAIOR
                   | MENOR_IGUAL
                   | MAIOR_IGUAL
                   | IGUAL
                   | DIFERENTE
                   ;

operador_unario: operador_logico_unario
               | INCREMENTO
               | DECREMENTO
               ;

operador_logico_unario: NAO_LOGICO
                      | NAO_BITS
                      ;

terminal_exp: literal
            | ID argumentos_chamada
            ;

argumentos_chamada: /* vazio */
                  | PAR_ESQ argumentos PAR_DIR
                  ;

argumentos: argumento
          | argumento VIRGULA argumentos
          ;

argumento: ID
         | literal
         ;

%%

int main (void) { return yyparse(); }

int yyerror (char *msg) {
  fprintf (stderr, "%d: %s at '%s'\n", yylineno, msg, yytext);
  return 0;
}
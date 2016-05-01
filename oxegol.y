%{
    #include "stdio.h"
    #include "y.tab.h"
%}

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

%%

programa: declaracoes_var_opc declaracoes_opc principal
        ;

declaracoes_var_opc: /* vazio */
                   | declaracao_var declaracoes_var_opc
                   ;

declaracoes_opc: /* vazio */
               | declaracao declaracoes_opc
               ;

principal: PRINCIPAL CHAVE_ESQ comandos_opc CHAVE_DIR
         ;

declaracao_var: tipo ID var_compl
              ;

var_compl: /* vazio */
         | ATRIBUICAO expressao
         | array_um_mais
         ;

array: COLCHETE_ESQ expressao COLCHETE_DIR
     ;

array_um_mais: array
             | array array_um_mais
             ;

declaracao: declaracao_registro
          | declaracao_func
          | declaracao_proc
          ;

declaracao_registro: REGISTRO ID CHAVE_ESQ campo_um_mais CHAVE_DIR
                   ;

declaracao_func: FUNCAO ID PAR_ESQ parametros_opc PAR_DIR RETORNA tipo CHAVE_ESQ comandos_opc CHAVE_DIR
               ;

declaracao_proc: PROCEDIMENTO ID PAR_ESQ parametros_opc PAR_DIR CHAVE_ESQ comandos_opc CHAVE_DIR
               ;

parametros_opc: /* vazio */
              | parametros
              ;

parametros: parametro
          | VIRGULA parametro parametros
          ;

parametro: ref_opc tipo ID
         ;

ref_opc: /* vazio */
       | REFERENCIA
       ;

argumentos: expressao
          | VIRGULA expressao argumentos
          ;

tipo: INTEIRO
    | REAL
    | STRING
    | CARACTERE
    | BOOLEANO
    | BYTE
    | ID
    ;

comandos_opc: /* vazio */
            | comando PONTO_E_VIRGULA comandos_opc
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

escolha: ESCOLHA PAR_ESQ expressao PAR_DIR CHAVE_ESQ caso_um_mais caso_contrario_opc CHAVE_DIR
       ;

caso_um_mais: caso caso_opc
            ;

caso: CASO literal DOIS_PONTOS comandos_opc
    ;

caso_opc: /* vazio */
        | caso caso_opc;

caso_contrario_opc: /* vazio */
                  | caso_contrario
                  ;

caso_contrario: CASOCONTRARIO DOIS_PONTOS comandos_opc
              ;

enquanto: ENQUANTO PAR_ESQ expressao PAR_DIR CHAVE_ESQ comandos_opc CHAVE_DIR
        ;

retorne: RETORNE expressao_opc
       ;

expressao_opc: /* vazio */
             | expressao
             ;

operador_binario: MAIS
                | MENOS
                | ASTERISCO
                | BARRA
                | MENOR
                | MAIOR
                | MENOR_IGUAL
                | MAIOR_IGUAL
                | IGUAL
                | DIFERENTE
                | MOD
                | E_LOGICO
                | OU_LOGICO
                | E_BITS
                | OU_BITS
                | XOR_BITS
                | DESLOCAMENTO_ESQ
                | DESLOCAMENTO_DIR
                ;

operador_unario: NAO_LOGICO
               | NAO_BITS
               | INCREMENTO
               | DECREMENTO
               | MENOS
               ;

expressao: chamada_funcao
         | literal
         | operador_unario expressao
         | PAR_ESQ expressao PAR_DIR
         | expressao operador_binario expressao
         ;

chamada_funcao: ID PAR_ESQ argumentos PAR_DIR
              ;

literal: LITERAL_INTEIRO
       | LITERAL_REAL
       | LITERAL_BOOLEANO
       | LITERAL_STRING
       | LITERAL_CARACTERE
       ;

campo_um_mais: campo
             | campo campo_um_mais
             ;

campo: tipo ID
     ;

%%
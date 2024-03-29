/*
 * Descricao: Definicoes LEX para a linguagem Oxegol
 * Uso: (1) $ flex oxegol.l
 *      (2) $ gcc lex.yy.c -ll (ou -lfl)
 *      (3) $ ./a.out < quicksort.oxe
 */

/* Declaracoes C */
%{
    #include <stdio.h>
    #include <string.h>
    #include "hash.h"
    #include "escopo.h"
    #include "aux.h"
    #include "y.tab.h"

    extern int yyerror (char *msg);
%}

/* Definicoes Lex */
digitos [0-9]+

/* Expressoes Regulares e acoes */
%%
"principal"       { return PRINCIPAL; }
"procedimento"    { return PROCEDIMENTO; }
"funcao"          { return FUNCAO; }
"retorne"         { return RETORNE; }
"global"          { return GLOBAL; }


"para"            { return PARA; }
"de"              { return DE; }
"ate"             { return ATE; }
"enquanto"        { return ENQUANTO; }
"escolha"         { return ESCOLHA; }
"caso"            { return CASO; }
"casocontrario"   { return CASOCONTRARIO; }
"se"              { return SE; }
"senao"           { return SENAO; }
"pare"            { return PARE; }


"inteiro"    { return INTEIRO; }
"real"       { return REAL; }
"string"     { return STRING; }
"caractere"  { return CARACTERE; }
"booleano"   { return BOOLEANO; }
"byte"       { return BYTE; }
"registro"   { return REGISTRO; }

"leia"          { return LEIA; }
"imprima"       { return IMPRIMA; }
"comparatexto"  { return COMPARATEXTO; }
"concatenatexto" { return CONCATENATEXTO; }

"ref"        { return REFERENCIA; }
"reg"        { return ACESSO_REGISTRO; }


\.         { return PONTO; }
":"        { return DOIS_PONTOS; }
"("        { return PAR_ESQ; }
")"        { return PAR_DIR; }
"{"        { return CHAVE_ESQ; }
"}"        { return CHAVE_DIR; }
"["        { return COLCHETE_ESQ; }
"]"        { return COLCHETE_DIR; }
","        { return VIRGULA; }
";"        { return PONTO_E_VIRGULA; }
"="        { return ATRIBUICAO; }


"++"       { return INCREMENTO; }
"--"       { return DECREMENTO; }


"->"       { return RETORNA; }
"+"        { return MAIS; }
"-"        { return MENOS; }
"*"        { return ASTERISCO; }
"/"        { return BARRA; }
"<"        { return MENOR; }
">"        { return MAIOR; }
"<="       { return MENOR_IGUAL; }
">="       { return MAIOR_IGUAL; }
"=="       { return IGUAL; }
"!="       { return DIFERENTE; }
"%"        { return MOD; }
"&"        { return E_BITS; }
"|"        { return OU_BITS; }
"^"        { return XOR_BITS; }
"<<"       { return DESLOCAMENTO_ESQ; }
">>"       { return DESLOCAMENTO_DIR; }
"~"        { return NAO_BITS; }


"e"        { return E_LOGICO; }
"ou"       { return OU_LOGICO; }
"nao"      { return NAO_LOGICO; }

{digitos}                                 { yylval.valor.ival = atoi(yytext); return LITERAL_INTEIRO; }
(({digitos}\.[0-9]*)|([0-9]*\.{digitos})) { yylval.valor.fval = atof(yytext); return LITERAL_REAL; }
("verdadeiro"|"falso")                    { if(strcmp(yytext, "verdadeiro") == 0) { yylval.valor.bval = 1; } else { yylval.valor.bval = 0; } return LITERAL_BOOLEANO; }
\"(\\.|[^"])*\"                           { yylval.valor.sval = strdup(yytext); return LITERAL_STRING; }
'.'                                       { yylval.valor.cval = yytext[1]; return LITERAL_CARACTERE; }

[a-zA-Z][a-zA-Z0-9\_]* { yylval.id = strdup(yytext); return ID; }

\n                               { yylineno++; }
[ \t\r]+                         { /* Nao faz nada para espacos em branco */ }
"/*"((\*+[^/*])|([^*]))*\**"*/"  { /* Nao faz nada para comentarios multi linhas */ }
[/][/].*                         { /* Nao faz nada para comentarios uma linha */ }

.          { printf("Padrao desconhecido: %s\n", yytext); }

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#endif
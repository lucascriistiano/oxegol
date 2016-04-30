/*
 * Descricao: Definicoes LEX para a linguagem Oxegol
 * Uso: (1) $ flex oxegol.l
 *      (2) $ gcc lex.yy.c -ll (ou -lfl)
 *      (3) $ ./a.out < quicksort.oxe
 */

/* Declaracoes C */
%{
#include "tokens.h"
//#include "string.h"
//union { int ival; string sval; double fval; char cval; } yylval;
%}

/* Definicoes Lex */
digitos [0-9]+

/* Expressoes Regulares e acoes */
%%
"principal"       { printf("PRINCIPAL\n"); return PRINCIPAL; }
"procedimento"    { printf("PROCEDIMENTO\n"); return PROCEDIMENTO; }
"funcao"          { printf("FUNCAO\n"); return FUNCAO; }
"retorne"         { printf("RETORNE\n"); return RETORNE; }


"para"            { printf("PARA\n"); return PARA; }
"de"              { printf("DE\n"); return DE; }
"ate"             { printf("ATE\n"); return ATE; }
"faca"            { printf("FACA\n"); return FACA; }
"enquanto"        { printf("ENQUANTO\n"); return ENQUANTO; }
"escolha"         { printf("ESCOLHA\n"); return ESCOLHA; }
"caso"            { printf("CASO\n"); return CASO; }
"casocontrario"   { printf("CASOCONTRARIO\n"); return CASOCONTRARIO; }
"se"              { printf("SE\n"); return SE; }
"senao"           { printf("SENAO\n"); return SENAO; }
"entao"           { printf("ENTAO\n"); return ENTAO; }
"pare"            { printf("PARE\n"); return PARE; }


"inteiro"    { printf("INTEIRO\n"); return INTEIRO; }
"real"       { printf("REAL\n"); return REAL; }
"string"     { printf("STRING\n"); return STRING; }
"caractere"  { printf("CARACTERE\n"); return CARACTERE; }
"booleano"   { printf("BOOLEANO\n"); return BOOLEANO; }
"byte"       { printf("BYTE\n"); return BYTE; }
"registro"   { printf("REGISTRO\n"); return REGISTRO; }


":"        { printf("DOIS_PONTOS\n"); return DOIS_PONTOS; }
"("        { printf("PAR_ESQ\n"); return PAR_ESQ; }
")"        { printf("PAR_DIR\n"); return PAR_DIR; }
"{"        { printf("CHAVE_ESQ\n"); return CHAVE_ESQ; }
"}"        { printf("CHAVE_DIR\n"); return CHAVE_DIR; }
"["        { printf("COLCHETE_ESQ\n"); return COLCHETE_ESQ; }
"]"        { printf("COLCHETE_DIR\n"); return COLCHETE_DIR; }
","        { printf("VIRGULA\n"); return VIRGULA; }
";"        { printf("PONTO_E_VIRGULA\n"); return PONTO_E_VIRGULA; }
"="        { printf("ATRIBUICAO\n"); return ATRIBUICAO; }


"->"       { printf("RETORNA\n"); return RETORNA; }
"+"        { printf("MAIS\n"); return MAIS; }
"-"        { printf("MENOS\n"); return MENOS; }
"*"        { printf("ASTERISCO\n"); return ASTERISCO; }
"/"        { printf("BARRA\n"); return BARRA; }
"<"        { printf("MENOR\n"); return MENOR; }
">"        { printf("MAIOR\n"); return MAIOR; }
"<="       { printf("MENOR_IGUAL\n"); return MENOR_IGUAL; }
">="       { printf("MAIOR_IGUAL\n"); return MAIOR_IGUAL; }
"=="       { printf("IGUAL\n"); return IGUAL; }
"%"        { printf("MOD\n"); return MOD; }
"&"        { printf("E_BITS\n"); return E_BITS; }
"|"        { printf("OU_BITS\n"); return OU_BITS; }
">>"       { printf("DESLOCAMENTO_DIR\n"); return DESLOCAMENTO_DIR; }
"<<"       { printf("DESLOCAMENTO_ESQ\n"); return DESLOCAMENTO_ESQ; }


"e"        { printf("E_LOGICO\n"); return E_LOGICO; }
"ou"       { printf("OU_LOGICO\n"); return OU_LOGICO; }
"nao"      { printf("NAO_LOGICO\n"); return NAO_LOGICO; }


{digitos}                                 { printf("LITERAL_INTEIRO: %d\n", atoi(yytext)); return LITERAL_INTEIRO; }
(({digitos}\.[0-9]*)|([0-9]*\.{digitos})) { printf("LITERAL_REAL: %f\n", atof(yytext)); return LITERAL_REAL; }
("verdadeiro"|"falso")                    { printf("LITERAL_BOOLEANO: %s\n", yytext); return LITERAL_BOOLEANO; }
\"[a-zA-Z0-9\_]*\"                        { printf("LITERAL_STRING: %s\n", yytext); return LITERAL_STRING; }
'.'                                       { printf("LITERAL_CARACTERE: %s\n", yytext); return LITERAL_CARACTERE; }

[a-zA-Z][a-zA-Z0-9\_]* { printf("ID: %s\n", yytext); return ID; }

"/*"((\*+[^/*])|([^*]))*\**"*/" { /* Nao faz nada para comentarios multi linhas */ }
[ \n\t\r]+                      { /* Nao faz nada para espacos em branco */ }

.          { printf("Padrao desconhecido: %s\n", yytext); }

%%
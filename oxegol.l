/*
 * Descricao: Definicoes LEX para a linguagem Oxegol
 * Uso: (1) $ flex oxegol.l
 *      (2) $ gcc lex.yy.c -ll (ou -lfl)
 *      (3) $ ./a.out < quicksort.oxe
 */

/* Declaracoes C */
%{
#include "tokens.h"
// union { int ival; string sval; double fval; char cval; } yylval;
%}

/* Definicoes Lex */
digitos [0-9]+

/* Expressoes Regulares e acoes */
%%
"principal"    { printf("PRINCIPAL\n"); }
"procedimento"    { printf("PROCEDIMENTO\n"); }
"funcao"          { printf("FUNCAO\n"); }
"retorne"         { printf("RETORNE\n"); }


"para"            { printf("PARA\n"); }
"de"              { printf("DE\n"); }
"ate"             { printf("ATE\n"); }
"faca"            { printf("FACA\n"); }
"enquanto"        { printf("ENQUANTO\n"); }
"escolha"         { printf("ESCOLHA\n"); }
"caso"            { printf("CASO\n"); }
"casocontrario"   { printf("CASO_CONTRARIO\n"); }
"se"              { printf("SE\n"); }
"senao"           { printf("SENAO\n"); }
"entao"           { printf("ENTAO\n"); }
"pare"            { printf("PARE\n"); }


"inteiro"    { printf("INTEIRO\n"); }
"real"       { printf("REAL\n"); }
"string"     { printf("STRING\n"); }
"caractere"  { printf("CARACTERE\n"); }
"booleano"   { printf("BOOLEANO\n"); }
"byte"       { printf("BYTE\n"); }
"registro"   { printf("REGISTRO\n"); }


":"        { printf("DOIS_PONTOS\n"); }
"("        { printf("PAR_ESQ\n"); }
")"        { printf("PAR_DIR\n"); }
"{"        { printf("CHAVE_ESQ\n"); }
"}"        { printf("CHAVE_DIR\n"); }
"["        { printf("COLCHETE_ESQ\n"); }
"]"        { printf("COLCHETE_DIR\n"); }
","        { printf("VIRGULA\n"); }
";"        { printf("PONTO_E_VIRGULA\n"); }
"="        { printf("ATRIBUICAO\n"); }

"verdadeiro"                    { printf("LIT_BOOLEANO_VERDADEIRO\n"); }
"falso"                    { printf("LIT_BOOLEANO_FALSO\n"); }

"e"        { printf("E_LOGICO\n"); }
"ou"       { printf("OU_LOGICO\n"); }
"nao"      { printf("NAO_LOGICO\n"); }



[a-zA-Z][a-zA-Z0-9\_]* { printf("ID\n"); }


{digitos}                                 { printf("LITERAL_INTEIRO\n"); }

({digitos}\.[0-9]*)  					{ printf("LITERAL_REAL\n"); }
([0-9]*\.{digitos}) 					{ printf("LITERAL_REAL\n"); }

\"[a-zA-Z0-9\_]*\"                        { printf("LITERAL_STRING\n"); }
"."                                       { printf("LITERAL_CARACTERE\n"); }

"->"       { printf("RETORNENA\n"); }
"+"        { printf("MAIS\n"); }
"-"        { printf("MENOS\n"); }
"*"        { printf("ASTERISCO\n"); }
"/"        { printf("BARRA\n"); }
"<"        { printf("MENOR\n"); }
">"        { printf("MAIOR\n"); }
"<="       { printf("MENOR_IGUAL\n"); }
">="       { printf("MAIOR_IGUAL\n"); }
"=="       { printf("IGUAL\n"); }
"%"        { printf("MOD\n"); }
"&&"       { printf("E_BINARIO\n"); }
"||"       { printf("OU_BINARIO\n"); }
">>"       { printf("DESLOCAMENTO_DIR\n"); }
"<<"       { printf("DESLOCAMENTO_ESQ\n"); }

"/*"[a-zA-Z0-9\_]*"*/" { /* Nao faz nada para comentarios */ }
[ \n\t\r]+               { /* Nao faz nada para espacos em branco */ }

.          { printf("Padrao desconhecido - %s\n", yytext); }
%%
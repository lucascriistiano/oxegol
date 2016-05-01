typedef union {
    int ival;
    char* sval;
    float fval;
    char cval;
} YYSTYPE;
extern YYSTYPE yylval;

#define PRINCIPAL       10
#define PROCEDIMENTO    11
#define FUNCAO          12
#define RETORNE         13

#define PARA            14
#define DE              15
#define ATE             16
#define ENQUANTO        17
#define ESCOLHA         18
#define CASO            19
#define CASOCONTRARIO   20
#define SE              21
#define SENAO           22
#define PARE            23

#define INTEIRO         24
#define REAL            25
#define STRING          26
#define CARACTERE       27
#define BOOLEANO        28
#define BYTE            29
#define REGISTRO        30

#define REFERENCIA      31

#define DOIS_PONTOS     32
#define PAR_ESQ         33
#define PAR_DIR         34
#define CHAVE_ESQ       35
#define CHAVE_DIR       36
#define COLCHETE_ESQ    37
#define COLCHETE_DIR    38
#define VIRGULA         30
#define PONTO_E_VIRGULA 40
#define ATRIBUICAO      41

#define RETORNA          42
#define MAIS             43
#define MENOS            44
#define ASTERISCO        45
#define BARRA            46
#define MENOR            47
#define MAIOR            48
#define MENOR_IGUAL      49
#define MAIOR_IGUAL      50
#define IGUAL            51
#define MOD              52
#define E_BITS           53
#define OU_BITS          54
#define XOR_BITS         55
#define DESLOCAMENTO_ESQ 56
#define DESLOCAMENTO_DIR 57
#define NAO_BITS         58

#define E_LOGICO         59
#define OU_LOGICO        60
#define NAO_LOGICO       61

#define INCREMENTO       62
#define DECREMENTO       63

#define LITERAL_INTEIRO   64
#define LITERAL_REAL      65
#define LITERAL_BOOLEANO  66
#define LITERAL_STRING    67
#define LITERAL_CARACTERE 68

#define ID                69
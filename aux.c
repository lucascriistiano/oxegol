#include "aux.h"

// codigo_tipo_t* criar_codigo_tipo_cast(codigo_tipo_t* codigo_tipo, tipo_t tipo_destino) {
//     char* codigo_original = codigo_tipo->codigo;

//     char* novo_codigo;

//     switch(tipo_destino) {
//         case inteiro:
//             novo_codigo = concatenar_strings("(int)", codigo_original);
//             break;
//         case real:
//             novo_codigo = concatenar_strings("(float)", codigo_original);
//             break;
//         // case booleano:
//         //     novo_codigo = concatenar_strings("(int)", codigo_original);
//         //     break;
//         case caractere:
//             novo_codigo = concatenar_strings("(char)", codigo_original);
//             break;
//         case string:
//             switch(tipo_destino) {
//                 case inteiro:
//                     char* resultado = "";
//                     resultado = concatenar_strings(resultado, "itoa(");
//                     resultado = concatenar_strings(resultado, codigo_original);
//                     resultado = concatenar_strings(resultado, ")");
//                     novo_codigo = resultado;
//                     break;
//                 case real:
//                     char* resultado = "";
//                     resultado = concatenar_strings(resultado, "ftoa(");
//                     resultado = concatenar_strings(resultado, codigo_original);
//                     resultado = concatenar_strings(resultado, ")");
//                     novo_codigo = resultado;
//                     break;
//                 // case booleano:
//                 //     novo_codigo = concatenar_strings("(int)", codigo_original);
//                 //     break;
//                 case caractere:
//                     novo_codigo = concatenar_strings("(char)", codigo_original);
//                     break;
//                 case string:
//                     novo_codigo = concatenar_strings("(char)", codigo_original);
//                     break;
//             }

//             novo_codigo = concatenar_strings("(char)", codigo_original);
//             break;
//     }

//     codigo_tipo_t* codigo_tipo_cast = (codigo_tipo_t*) malloc(sizeof(codigo_tipo_t));
//     codigo_tipo_cast->codigo = strdup(codigo);
//     codigo_tipo_cast->tipo = tipo;
//     return codigo_tipo_cast;
// }

no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor) {
  no_literal_t* no = (no_literal_t*) malloc(sizeof(no_literal_t));
  no->tipo = tipo;

  switch(tipo) {
    case inteiro:
      no->valor.ival = valor.ival;
      break;

    case real:
      no->valor.fval = valor.fval;
      break;

    case booleano:
      no->valor.bval = valor.bval;
      break;

    case caractere:
      no->valor.cval = valor.cval;

    case string:
      no->valor.sval = strdup(valor.sval);  //Criar cópia e desalocar quando for do tipo string
      free(valor.sval);
      break;

    default:
      printf("Tipo %u não reconhecido\n", tipo);
      return NULL;
  }

  return no;
}

no_expressao_t* criar_no_expressao(char* codigo, tipo_t tipo) {
    no_expressao_t* no_expressao = (no_expressao_t*) malloc(sizeof(no_expressao_t));
    no_expressao->codigo = strdup(codigo);  //Criar cópia e desalocar quando for do tipo string?
    no_expressao->tipo = tipo;
    no_expressao->proximo = NULL;
    return no_expressao;
}

no_expressao_t* adicionar_no_expressao(no_expressao_t* no_expressao, no_expressao_t* nova_expressao) {
    no_expressao_t* expressao_atual = no_expressao;
    while(expressao_atual->proximo != NULL) {
        expressao_atual = expressao_atual->proximo;
    }
    expressao_atual->proximo = nova_expressao;
    return no_expressao;
}

no_variavel_t* criar_no_variavel(char* id, char* codigo, tipo_t tipo) {
    no_variavel_t* no_variavel = (no_variavel_t*) malloc(sizeof(no_variavel_t));
    no_variavel->id = strdup(id);  //Criar cópia e desalocar quando for do tipo string?
    no_variavel->codigo = strdup(codigo);  //Criar cópia e desalocar quando for do tipo string?
    no_variavel->tipo = tipo;
    no_variavel->proximo = NULL;
    return no_variavel;
}

no_indice_array_t* criar_no_indice_array(int indice) {
    no_indice_array_t* novo_indice = (no_indice_array_t*) malloc(sizeof(no_indice_array_t));
    novo_indice->indice = indice;
    novo_indice->proximo = NULL;
    return novo_indice;
}

no_operador_t* criar_no_operador(char* codigo, tipo_t tipo, tipo_t retorno, int num_op) {
    //TODO Verificar se conseguiu alocar
    no_operador_t* novo_operador = (no_operador_t*) malloc(sizeof(no_operador_t));
    novo_operador->codigo = strdup(codigo);
    novo_operador->tipo = tipo;
    novo_operador->retorno = retorno;
    novo_operador->num_op = num_op;
    novo_operador->proximo = NULL;
    return novo_operador;
}

no_parametro_t* criar_no_parametro(char *id, tipo_t tipo) {
    no_parametro_t* novo_parametro = (no_parametro_t*) malloc(sizeof(no_parametro_t));
    novo_parametro->id = strdup(id);
    novo_parametro->tipo = tipo;
    novo_parametro->proximo = NULL;
    return novo_parametro;
}

no_variavel_t* adicionar_no_variavel(no_variavel_t* no_variavel, no_variavel_t* nova_variavel) {
    no_variavel_t* variavel_atual = no_variavel;
    while(variavel_atual->proximo != NULL) {
        variavel_atual = variavel_atual->proximo;
    }
    variavel_atual->proximo = nova_variavel;
    return no_variavel;
}

no_indice_array_t* adicionar_no_indice_array(no_indice_array_t* no_indice_array, int indice) {
    //Navega até a última posição
    no_indice_array_t* indice_atual = no_indice_array;
    while(indice_atual->proximo != NULL) {
        indice_atual = indice_atual->proximo;
    }

    no_indice_array_t* novo_indice = criar_no_indice_array(indice);
    indice_atual->proximo = novo_indice;
    return no_indice_array;
}

no_operador_t* adicionar_tipo_no_operador(no_operador_t* no_operador, char* codigo, tipo_t tipo, tipo_t retorno, int num_op) {
    no_operador_t* operador_atual = no_operador;
    while (operador_atual->proximo != NULL) {
        operador_atual = operador_atual->proximo;
    }

    //TODO Verificar se conseguiu alocar (para todos os outros => Ctrl + F malloc)
    no_operador_t* novo_operador = criar_no_operador(codigo, tipo, retorno, num_op);
    operador_atual->proximo = novo_operador;
    return no_operador;
}

no_parametro_t* adicionar_no_parametro(no_parametro_t* no_parametro, no_parametro_t* novo_parametro) {
    //Navega até a última posição
    no_parametro_t* parametro_atual = no_parametro;
    while(parametro_atual->proximo != NULL) {
        parametro_atual = parametro_atual->proximo;
    }
    parametro_atual->proximo = novo_parametro;
    return no_parametro;
}

// int verificar_tipos_atribuicao(tipo_t tipo, indice_array_t *indices_array, no_variavel_t *no_variavel) {
//     //Implementar
// }

int verificar_compatibilidade_operacao_binaria(no_operador_t* operador, tipo_t tipo_op1, tipo_t tipo_op2) {
    // Tipos diferentes são incompatíveis
    if(tipo_op1 != tipo_op2) {
        return 0; //Tipos incompatíveis
    }

    // Verifica se o operador aceita o tipo dos operadores
    no_operador_t* operador_posicionado = operador;
    while(operador_posicionado->tipo != tipo_op1 && operador_posicionado->proximo != NULL) {
        operador_posicionado = operador_posicionado->proximo;
    }
    if(operador_posicionado->tipo != tipo_op1) {
        return 0; // Tipo não aceito
    }

    return 1; // Tipos compatíveis e aceitos pelo operador
}

int verificar_compatibilidade_operacao_unaria(no_operador_t* operador, tipo_t tipo_op) {
    // Verifica se o operador aceita o tipo do operador
    no_operador_t* operador_posicionado = operador;
    while(operador_posicionado->tipo != tipo_op && operador_posicionado->proximo != NULL) {
        operador_posicionado = operador_posicionado->proximo;
    }
    if(operador_posicionado->tipo != tipo_op) {
        return 0; // Tipo não aceito
    }

    return 1; // Tipos aceito pelo operador
}

tipo_t verificar_tipo_retorno(no_operador_t* operador, tipo_t tipo) {
    no_operador_t* operador_posicionado = operador;
    while(operador_posicionado->tipo != tipo && operador_posicionado->proximo != NULL) {
        operador_posicionado = operador_posicionado->proximo;
    }

    return operador_posicionado->retorno;
}

int verificar_cast(tipo_t tipo_origem, tipo_t tipo_destino) {
    if(tipo_origem == tipo_destino) return 1;
    if(tipo_origem == inteiro && (tipo_destino == real || tipo_destino == caractere)) return 1;
    if(tipo_origem == real && tipo_destino == inteiro) return 1;
    if(tipo_origem == caractere && tipo_destino == string) return 1;

    return 0; //Tipos não conversíveis
}

char* concatenar_strings(char* primeira, char* segunda) {
    size_t tamanho = strlen(primeira) + strlen(segunda) + 1;
    char *resultado = malloc(tamanho*sizeof(char));

    sprintf(resultado, "%s%s", primeira, segunda);

    //free(primeira);

    return resultado;
}

char* gerar_concatena_texto(char* destino,char* primeira, char* segunda){
    char *retorno = "";
    retorno = concatenar_strings(retorno, "sprintf(");
    retorno = concatenar_strings(retorno, destino);
    retorno = concatenar_strings(retorno, ",");
    retorno = concatenar_strings(retorno, "%s%s");
    retorno = concatenar_strings(retorno, ",");
    retorno = concatenar_strings(retorno, "primeira");
    retorno = concatenar_strings(retorno, ",");
    retorno = concatenar_strings(retorno, "segunda");
    retorno = concatenar_strings(retorno, ");\n");
    return retorno;
}

char* gerar_label(char* comando, int numero) {
    char numero_char[15];
	sprintf(numero_char, "%d", numero);
	size_t tamanho =(strlen(comando)+strlen(numero_char) + 1);
	char *resultado = malloc(tamanho *sizeof(char));
    sprintf(resultado, "%s%s", comando, numero_char);
    return resultado;
}

char* gerar_para(int npara, char* id, char* exp_inicializacao, char* exp_parada, char* comandos) {
    char *retorno = "";

    //Inicializa contador
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "=");
    retorno = concatenar_strings(retorno, exp_inicializacao);
    retorno = concatenar_strings(retorno, ";\n");

    //Define label para for
    char *label = gerar_label("for", npara);
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, ":\n");

    //Insere comandos já formatados
    retorno = concatenar_strings(retorno, comandos);

    //Verifica se o for é decrescente para decrementar contador
    retorno = concatenar_strings(retorno, "\nif (");
    retorno = concatenar_strings(retorno, exp_inicializacao);
    retorno = concatenar_strings(retorno, ">");
    retorno = concatenar_strings(retorno, exp_parada);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, "goto ");
    char *d = concatenar_strings("decremento", label);
    retorno = concatenar_strings(retorno, d);
    retorno = concatenar_strings(retorno, ";\n}\n");

    //Verifica se o for e crescente para incrementar contador
    retorno = concatenar_strings(retorno, "if (");
    retorno = concatenar_strings(retorno, exp_inicializacao);
    retorno = concatenar_strings(retorno, " < ");
    retorno = concatenar_strings(retorno, exp_parada);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, "goto ");
    char *i = concatenar_strings("incremento", label);
    retorno = concatenar_strings(retorno, i);
    retorno = concatenar_strings(retorno, ";\n}\n");

    retorno = concatenar_strings(retorno, d);
    retorno = concatenar_strings(retorno, ":\n");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "--;\n goto");

    char *c = concatenar_strings("condicao", label);
    retorno = concatenar_strings(retorno, c);
    retorno = concatenar_strings(retorno, ";\n");

    retorno = concatenar_strings(retorno, i);
    retorno = concatenar_strings(retorno, ":\n");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "++;\n goto");
    retorno = concatenar_strings(retorno, c);
    retorno = concatenar_strings(retorno, ";\n");


    //Condição de parada
    retorno = concatenar_strings(retorno, c);
    retorno = concatenar_strings(retorno, ":\nif (");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "!=");
    retorno = concatenar_strings(retorno, exp_parada);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, "goto ");
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, ";}");

    free(label);

    return retorno;
}

char* gerar_enquanto(int nenquanto, char* exp_parada, char*comandos) {
	char *retorno = "";
	//Define label para for
    char *label = gerar_label("while", nenquanto);
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, ":\n");

    //Insere comandos já formatados
    retorno = concatenar_strings(retorno, comandos);

     //Condição de parada
    retorno = concatenar_strings(retorno, "\nif (");
    retorno = concatenar_strings(retorno, exp_parada);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, "goto ");
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, ";\n}\n");

    free(label);
    return retorno;
}

//receber um vetor de strings no caso_um_mais
char* gerar_escolha(char* id, char* caso_um_mais, char* caso_contrario) {
    char *retorno = "switch (";
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, caso_um_mais);
    retorno = concatenar_strings(retorno, caso_contrario);
    retorno = concatenar_strings(retorno, "}");
    return retorno;
}

char* gerar_caso(char* valor, char*  comandos) {
    char *retorno = "case ";
    retorno = concatenar_strings(retorno, valor);
    retorno = concatenar_strings(retorno, ":\n");
    retorno = concatenar_strings(retorno, comandos);
    retorno = concatenar_strings(retorno, "break;\n");
    return retorno;
}

char* gerar_caso_contrario(char*  comandos) {
    char *retorno = "default:\n";
    retorno = concatenar_strings(retorno, comandos);
    return retorno;
}

char* gerar_se(int nse, se_t* ses) {
    char *label = gerar_label("if", nse);
    int nlabel = 0;
    char *labelocal = gerar_label("l", nlabel);

    char *retorno = "if(";
    retorno = concatenar_strings(retorno, ses->expressao);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, "goto ");
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, labelocal);
    retorno = concatenar_strings(retorno, ";}\n");

    nlabel++;

    se_t* se_atual = ses;
    while (se_atual->proximo != NULL) {
        se_atual = se_atual->proximo;

        if(se_atual->expressao != NULL){
            //senao se
            retorno = concatenar_strings(retorno, "if(");
            retorno = concatenar_strings(retorno, se_atual->expressao);
            char *retorno = "){\n";
            retorno = concatenar_strings(retorno, "goto ");
            retorno = concatenar_strings(retorno, label);
            labelocal = gerar_label("l", nlabel);
            retorno = concatenar_strings(retorno, labelocal);
            retorno = concatenar_strings(retorno, ";}\n");
        }
        else{
            //senao
            retorno = concatenar_strings(retorno, se_atual->comandos);
        }
        nlabel++;
    }

    nlabel = 0;
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, labelocal);
    retorno = concatenar_strings(retorno, ":\n");
    retorno = concatenar_strings(retorno, se_atual->comandos);
    retorno = concatenar_strings(retorno, "\n goto exit");
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, ";\n");

    nlabel++;
    se_atual = ses;
    while (se_atual->proximo != NULL) {
        se_atual = se_atual->proximo;

        if(se_atual->expressao != NULL){
            //senao se
            retorno = concatenar_strings(retorno, label);
            retorno = concatenar_strings(retorno, labelocal);
            retorno = concatenar_strings(retorno, ":\n");
            retorno = concatenar_strings(retorno, se_atual->comandos);
            retorno = concatenar_strings(retorno, "\n goto exit");
            retorno = concatenar_strings(retorno, label);
            retorno = concatenar_strings(retorno, ";\n");

        }
        else{
            //senao

        }
        nlabel++;
    }

    retorno = concatenar_strings(retorno, "\n exit");
    retorno = concatenar_strings(retorno, label);
    retorno = concatenar_strings(retorno, ":\n");
    return retorno;
}

char* gerar_funcao(char* id, char* parametros_opc, char* tipo, char* comandos_opc) {
	char* retorno = "";
	retorno = concatenar_strings(retorno, tipo);
	retorno = concatenar_strings(retorno, " ");
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "(");
	retorno = concatenar_strings(retorno, parametros_opc);

    retorno = concatenar_strings(retorno, "){\n");
	retorno = concatenar_strings(retorno, comandos_opc);

	retorno = concatenar_strings(retorno, ")}\n");
	return retorno;
}

char* gerar_procedimento(char* id, char* parametros_opc, char* comandos_opc) {
	char* retorno = "";
	retorno = concatenar_strings(retorno, "void");
	retorno = concatenar_strings(retorno, " ");
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "(");
	retorno = concatenar_strings(retorno, parametros_opc);

    retorno = concatenar_strings(retorno, "){\n");
	retorno = concatenar_strings(retorno, comandos_opc);

	retorno = concatenar_strings(retorno, ")}\n");
    return retorno;
}

char * gerar_principal(char* comandos_opc){
	char* retorno = "int main(){\n";
	retorno = concatenar_strings(retorno, comandos_opc);
	retorno = concatenar_strings(retorno, "return 0;");
	retorno = concatenar_strings(retorno, "}\n");
    return retorno;
}

int escrever_arquivo_c(char *codigo){
    FILE *fp;
    fp = fopen ("temporario.c", "a");
    if (fp == NULL) {
       printf ("Houve um erro ao abrir o arquivo.\n");
       return 1;
    }
    fputs (codigo, fp);

    fclose (fp);
    return 0;
}

char* gerar_comparar_strings( char* primeira, char* segunda) {
    char *retorno = "strcmp(";
    retorno = concatenar_strings(retorno,primeira);
    retorno = concatenar_strings(retorno,",");
    retorno = concatenar_strings(retorno,segunda);
    retorno = concatenar_strings(retorno, ")");
    return retorno;
}

char* gerar_includes() {
    char *retorno = "#include <stdio.h>\n";
    retorno = concatenar_strings(retorno,"#include <stlib.h>\n");
    retorno = concatenar_strings(retorno,"#include <string.h>\n\n");
    return retorno;
}

char* gerar_comparar_char(char primeira, char segunda){
    char* primeira_str = (char*) malloc(2 * sizeof(char));  //Dar free?
    char* segunda_str = (char*) malloc(2 * sizeof(char));  //Dar free?

    sprintf(primeira_str, "%c", primeira);
    sprintf(segunda_str, "%c", segunda);

    char* retorno = "";
    retorno = concatenar_strings(retorno, "(");
    retorno = concatenar_strings(retorno,primeira_str);
    retorno = concatenar_strings(retorno,"==");
    retorno = concatenar_strings(retorno,segunda_str);
    retorno = concatenar_strings(retorno, ")");
    return retorno;
}

char* gerar_leia(char* id, char* tipo){
    char* retorno = "scanf";
    retorno = concatenar_strings(retorno, "(");
    retorno = concatenar_strings(retorno,"%");
    retorno = concatenar_strings(retorno, tipo);
    retorno = concatenar_strings(retorno,",");
    retorno = concatenar_strings(retorno,"&");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, ")");
    retorno = concatenar_strings(retorno, ";\n");
    return retorno;
}

char* gerar_imprima(char* argumentos){
    char* retorno = "printf";
    retorno = concatenar_strings(retorno, "(");
    retorno = concatenar_strings(retorno, argumentos);
    retorno = concatenar_strings(retorno, ")");
    retorno = concatenar_strings(retorno, ";\n");
    return retorno;
}

char* gerar_atribuicao(char* lado_esquerdo, char* lado_direito ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, lado_esquerdo);
	retorno = concatenar_strings(retorno, " = ");
	retorno = concatenar_strings(retorno, lado_direito);
	retorno = concatenar_strings(retorno, ";");
    return retorno;
}

char * gerar_declaracao_sa(char* tipo, char* variavel ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, tipo);
	retorno = concatenar_strings(retorno, variavel);
	retorno = concatenar_strings(retorno, ";");
    return retorno;
}

char * gerar_declaracao_ca(char* tipo, char* variavel, char* inicializacao  ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, tipo);
	retorno = concatenar_strings(retorno, variavel);
	retorno = gerar_atribuicao(retorno, inicializacao);
	retorno = concatenar_strings(retorno, ";");
    return retorno;
}

se_t* criar_se(char* exp, char* comandos){
    se_t* se = (se_t*) malloc(sizeof(se_t));
    se->expressao = exp;
    se->comandos = comandos;
    se->proximo = NULL;
    return se;
}

void adicionar_se(se_t* se, char* exp, char* comandos) {
    se_t* se_atual = se;
    while (se_atual->proximo != NULL) {
        se_atual = se_atual->proximo;
    }

    //TODO Verificar se conseguiu alocar (para todos os outros => Ctrl + F malloc)
    se_t* novo_se = criar_se(exp, comandos);
    se_atual->proximo = novo_se;
}
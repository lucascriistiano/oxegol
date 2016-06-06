#include "aux.h"

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

    return 0; //Tipos não conversíveis
}

char* converter_literal_para_string(no_literal_t* literal) {
  tipo_t tipo_literal = literal->tipo;
  char* literal_string;
  switch(tipo_literal) {
    case inteiro:
      literal_string = malloc(snprintf(NULL, 0, "%d", literal->valor.ival) + 1);
      sprintf(literal_string, "%d", literal->valor.ival);
      break;

    case real:
      literal_string = malloc(snprintf(NULL, 0, "%f", literal->valor.fval) + 1);
      sprintf(literal_string, "%f", literal->valor.fval);
      break;

    case booleano:
      literal_string = malloc(snprintf(NULL, 0, "%d", literal->valor.bval) + 1);
      sprintf(literal_string, "%d", literal->valor.bval);
      break;

    case caractere:
      literal_string = malloc(snprintf(NULL, 0, "%c", literal->valor.cval) + 1);
      sprintf(literal_string, "%c", literal->valor.cval);
      break;

    case string:
      literal_string = malloc(snprintf(NULL, 0, "%s", literal->valor.sval) + 1);
      sprintf(literal_string, "%s", literal->valor.sval);
      break;

    default:
      printf("Tipo %u não reconhecido\n", tipo_literal);
      return NULL;
  }
  return literal_string;
}

char* converter_tipo_para_string(tipo_t tipo) {
  switch(tipo) {
    case inteiro:
      return "int";

    case real:
      return "float";

    case booleano:
      return "int";

    case caractere:
      return "char";

    case string:
      return "char*";

    default:
      printf("Tipo %u não reconhecido\n", tipo);
      return "";
  }
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
    char* numero_char = malloc(snprintf(NULL, 0, "%s%d", comando, numero) + 1);
    sprintf(numero_char, "%s%d", comando, numero);
    return numero_char;
}

char* gerar_cast(no_expressao_t* expressao, tipo_t tipo_destino) {
    if(tipo_destino == inteiro) {
        return concatenar_strings("(int)", expressao->codigo);
    } else if(tipo_destino == real) {
        return concatenar_strings("(float)", expressao->codigo);
    } else if(tipo_destino == caractere) {
        return concatenar_strings("(char)", expressao->codigo);
    } else {
        return concatenar_strings("", expressao->codigo); //Tipo destino de cast não aceito
    }
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
    retorno = concatenar_strings(retorno, "--;\n");
    retorno = concatenar_strings(retorno, "goto ");

    char *c = concatenar_strings("condicao", label);
    retorno = concatenar_strings(retorno, c);
    retorno = concatenar_strings(retorno, ";\n");

    retorno = concatenar_strings(retorno, i);
    retorno = concatenar_strings(retorno, ":\n");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "++;\n");
    retorno = concatenar_strings(retorno, "goto ");
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

char* gerar_caso(no_literal_t* literal, char* comandos) {
    char *retorno = "case ";
    retorno = concatenar_strings(retorno, converter_literal_para_string(literal));
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
    char *label_exit = concatenar_strings(label, "_exit");
    char *label_local_base = concatenar_strings(label, "l");

    char *retorno = "";

    int nlabel = 0;
    se_t* se_atual = ses;
    while(se_atual != NULL) {
        if(se_atual->expressao != NULL) {
            retorno = concatenar_strings(retorno, "if(");
            retorno = concatenar_strings(retorno, se_atual->expressao);
            retorno = concatenar_strings(retorno, ") {\n");
            retorno = concatenar_strings(retorno, "goto ");
            retorno = concatenar_strings(retorno, gerar_label(label_local_base, nlabel));
            retorno = concatenar_strings(retorno, ";\n");
            retorno = concatenar_strings(retorno, "}\n");
            nlabel++;
        } else {
            //Comandos senao
            retorno = concatenar_strings(retorno, se_atual->comandos);
            retorno = concatenar_strings(retorno, "\n");
            retorno = concatenar_strings(retorno, "goto ");
            retorno = concatenar_strings(retorno, label_exit);
            retorno = concatenar_strings(retorno, ";\n\n");
        }

        se_atual = se_atual->proximo;
    }

    nlabel = 0;
    se_atual = ses;
    while (se_atual != NULL) {
        if(se_atual->expressao != NULL){
            //Comandos se/senao se
            retorno = concatenar_strings(retorno, gerar_label(label_local_base, nlabel));
            retorno = concatenar_strings(retorno, ":\n");
            retorno = concatenar_strings(retorno, se_atual->comandos);
            retorno = concatenar_strings(retorno, "\n");
            retorno = concatenar_strings(retorno, "goto ");
            retorno = concatenar_strings(retorno, label_exit);
            retorno = concatenar_strings(retorno, ";\n\n");
            nlabel++;
        }

        se_atual = se_atual->proximo;
    }

    retorno = concatenar_strings(retorno, "\n");
    retorno = concatenar_strings(retorno, label_exit);
    retorno = concatenar_strings(retorno, ":;\n");
    return retorno;
}

char* gerar_funcao(char* id, no_parametro_t* parametros_opc, tipo_t tipo, char* comandos_opc, no_expressao_t* exp_retorne) {
	char* retorno = "\n";
    retorno = concatenar_strings(retorno, converter_tipo_para_string(tipo));
    retorno = concatenar_strings(retorno, " ");
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "(");

    no_parametro_t* parametro_atual = parametros_opc;
    while(parametro_atual != NULL) {
        retorno = concatenar_strings(retorno, converter_tipo_para_string(parametro_atual->tipo));
        retorno = concatenar_strings(retorno, " ");
        retorno = concatenar_strings(retorno, parametro_atual->id);
        if(parametro_atual->proximo != NULL) {
            retorno = concatenar_strings(retorno, ", ");
        }
        parametro_atual = parametro_atual->proximo;
    }

    retorno = concatenar_strings(retorno, "){\n");
	retorno = concatenar_strings(retorno, comandos_opc);
    retorno = concatenar_strings(retorno, "\n");
    retorno = concatenar_strings(retorno, exp_retorne->codigo);
	retorno = concatenar_strings(retorno, "}\n");
	return retorno;
}

char* gerar_procedimento(char* id, no_parametro_t* parametros_opc, char* comandos_opc) {
	char* retorno = "\n";
	retorno = concatenar_strings(retorno, "void");
	retorno = concatenar_strings(retorno, " ");
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "(");

    no_parametro_t* parametro_atual = parametros_opc;
    while(parametro_atual != NULL) {
        retorno = concatenar_strings(retorno, converter_tipo_para_string(parametro_atual->tipo));
        retorno = concatenar_strings(retorno, " ");
        retorno = concatenar_strings(retorno, parametro_atual->id);
        if(parametro_atual->proximo != NULL) {
            retorno = concatenar_strings(retorno, ", ");
        }
        parametro_atual = parametro_atual->proximo;
    }

    retorno = concatenar_strings(retorno, "){\n");
	retorno = concatenar_strings(retorno, comandos_opc);
	retorno = concatenar_strings(retorno, "}\n");
    return retorno;
}

char* gerar_principal(char* comandos_opc){
	char* retorno = "\n";
    retorno = concatenar_strings(retorno, "int main() {\n");

    retorno = concatenar_strings(retorno, comandos_opc);
	retorno = concatenar_strings(retorno, "return 0;");
	retorno = concatenar_strings(retorno, "\n}\n");
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
    retorno = concatenar_strings(retorno,"#include <stdlib.h>\n");
    retorno = concatenar_strings(retorno,"#include <string.h>\n\n");
    return retorno;
}

char* gerar_comparar_char(char* primeira, char* segunda){
    // char* primeira_str = (char*) malloc(2 * sizeof(char));  //Dar free?
    // char* segunda_str = (char*) malloc(2 * sizeof(char));  //Dar free?

    // sprintf(primeira_str, "%c", primeira);
    // sprintf(segunda_str, "%c", segunda);

    char* retorno = "";
    retorno = concatenar_strings(retorno, "(");
    retorno = concatenar_strings(retorno,primeira);
    retorno = concatenar_strings(retorno,"==");
    retorno = concatenar_strings(retorno,segunda);
    retorno = concatenar_strings(retorno, ")");
    return retorno;
}

char* gerar_leia(char* id, tipo_t tipo){
    char* retorno = "scanf(\"";
    switch(tipo){
        case inteiro:
            retorno = concatenar_strings(retorno, "%d");
            break;
        case real:
            retorno = concatenar_strings(retorno, "%f");
            break;
        case booleano:
            retorno = concatenar_strings(retorno, "%i");
            break;
        case caractere:
            retorno = concatenar_strings(retorno, "%c");
            break;
        case string:
            retorno = concatenar_strings(retorno, "%s");
            break;
        case vazio:
            return NULL;
            break;
    }

    retorno = concatenar_strings(retorno,"\", &");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, ");\n");
    return retorno;
}

char* gerar_imprima(no_expressao_t* expressoes){
    char* retorno = "printf(\"";

    no_expressao_t* exp_atual = expressoes;
    while (exp_atual != NULL){
        switch(exp_atual->tipo){
        case inteiro:
            retorno = concatenar_strings(retorno, "%d");
            break;
        case real:
            retorno = concatenar_strings(retorno, "%f");
            break;
        case booleano:
            retorno = concatenar_strings(retorno, "%d");
            break;
        case caractere:
            retorno = concatenar_strings(retorno, "%c");
            break;
        case string:
            retorno = concatenar_strings(retorno, "%s");
            break;
        case vazio:
            break;
        }

        if(exp_atual->proximo != NULL) {
            retorno = concatenar_strings(retorno, " ");
        }
        exp_atual = exp_atual->proximo;
    }
    retorno = concatenar_strings(retorno, "\", ");

    exp_atual= expressoes;
    while (exp_atual != NULL) {
        if(exp_atual->tipo == vazio) {
            continue;
        }

        retorno = concatenar_strings(retorno, exp_atual->codigo);

        if(exp_atual->proximo != NULL) {
            retorno = concatenar_strings(retorno, ", ");
        }
        exp_atual = exp_atual->proximo;
    }

    retorno = concatenar_strings(retorno, ");\n");
    retorno = concatenar_strings(retorno, "printf(\"\\n\");");
    return retorno;
}

char* gerar_expressao_binaria(char* lado_esquerdo, char* lado_direito, char* operador){
	char* retorno = "";
	retorno = concatenar_strings(retorno, lado_esquerdo);
	retorno = concatenar_strings(retorno,  " ");
	retorno = concatenar_strings(retorno, operador);
	retorno = concatenar_strings(retorno,  " ");
	retorno = concatenar_strings(retorno, lado_direito);
    return retorno;
}

char* gerar_expressao_binaria_parentizada(char* lado_esquerdo_parentizado, char* lado_direito, char* operador) {
    char* retorno = "";
    retorno = concatenar_strings(retorno, "(");
    retorno = concatenar_strings(retorno, lado_esquerdo_parentizado);
    retorno = concatenar_strings(retorno, ")");
    retorno = concatenar_strings(retorno,  " ");
    retorno = concatenar_strings(retorno, operador);
    retorno = concatenar_strings(retorno,  " ");
    retorno = concatenar_strings(retorno, lado_direito);
    return retorno;
}

char* gerar_expressao_unaria(char* lado_esquerdo, char* operador){
	char* retorno = "(";
	retorno = concatenar_strings(retorno, lado_esquerdo);
	retorno = concatenar_strings(retorno,  " ");
	retorno = concatenar_strings(retorno, operador);
	retorno = concatenar_strings(retorno, ")");
    return retorno;
}

char* gerar_atribuicao(char* lado_esquerdo, char* lado_direito ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, lado_esquerdo);
	retorno = concatenar_strings(retorno, " = ");
	retorno = concatenar_strings(retorno, lado_direito);
	retorno = concatenar_strings(retorno, ";\n");
    return retorno;
}

char * gerar_incremento(char* id){
	char* retorno = "";
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "++;");
    return retorno;
}

char * gerar_decremento(char* id){
	char* retorno = "";
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "--;");
    return retorno;
}

char* gerar_chamada_sub(char* id, no_expressao_t* argumentos) {
	char* retorno = "";
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "(");

    no_expressao_t* argumento_atual = argumentos;
    while(argumento_atual != NULL) {
        retorno = concatenar_strings(retorno, argumento_atual->codigo);

        if(argumento_atual->proximo != NULL) {
            retorno = concatenar_strings(retorno, ", ");
        }

        argumento_atual = argumento_atual->proximo;
    }

	retorno = concatenar_strings(retorno, ")");
    return retorno;
}

char* gerar_declaracao(tipo_t tipo, no_indice_array_t* indices_array_opc, no_variavel_t* variaveis) {
    char* retorno = "";
    retorno = concatenar_strings(retorno, converter_tipo_para_string(tipo));
    retorno = concatenar_strings(retorno, " ");

    //TODO Adicionar indices array
    // no_indice_array_t* indice_atual = indices_array_opc;
    // while(indice_atual != NULL) {
    //     retorno = concatenar_strings(retorno, "[");

    //     char* indice = malloc(snprintf(NULL, 0, "%d", indice_atual->indice) + 1);
    //     sprintf(indice, "%d", indice_atual->indice);
    //     retorno = concatenar_strings(retorno, indice);
    //     free(indice);

    //     retorno = concatenar_strings(retorno, "]");
    //     indice_atual = indice_atual->proximo;
    // }
    // retorno = concatenar_strings(retorno, " ");

    no_variavel_t* variavel_atual = variaveis;
    while(variavel_atual != NULL) {
        retorno = concatenar_strings(retorno, variavel_atual->codigo);

        if(variavel_atual->proximo != NULL) {
            retorno = concatenar_strings(retorno, ", ");
        }
        variavel_atual = variavel_atual->proximo;
    }
    return retorno;
}

se_t* criar_se(char* expressao, char* comandos){
    se_t* se = (se_t*) malloc(sizeof(se_t));
    se->expressao = expressao;
    se->comandos = comandos;
    se->proximo = NULL;
    return se;
}

// se_t* adicionar_se(se_t* se, char* exp, char* comandos) {
//     se_t* se_atual = se;
//     while (se_atual->proximo != NULL) {
//         se_atual = se_atual->proximo;
//     }

//     se_t* novo_se = criar_se(exp, comandos);
//     se_atual->proximo = novo_se;
//     return se;
// }

se_t* adicionar_se(se_t* se, se_t* novo_se) {
    se_t* se_atual = se;
    while (se_atual->proximo != NULL) {
        se_atual = se_atual->proximo;
    }
    se_atual->proximo = novo_se;
    return se;
}
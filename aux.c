#include "aux.h"

no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor) {
  no_literal_t* no = (no_literal_t*) malloc(sizeof(no_literal_t));
  no->tipo = tipo;
  no->valor = valor;  //Criar cópia e desalocar quando for do tipo string?
  return no;
}

char* concatenar_strings(char* primeira, char* segunda) {
    size_t tamanho = strlen(primeira) + strlen(segunda) + 1;
    char *resultado = malloc(tamanho*sizeof(char));
    sprintf(resultado, "%s%s", primeira, segunda);

    //free(primeira);

    return resultado;
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
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "--;}");

    //Verifica se o for e crescente para incrementar contador
    retorno = concatenar_strings(retorno, "\nif (");
    retorno = concatenar_strings(retorno, exp_inicializacao);
    retorno = concatenar_strings(retorno, " < ");
    retorno = concatenar_strings(retorno, exp_parada);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, id);
    retorno = concatenar_strings(retorno, "++;}");

    //Condição de parada
    retorno = concatenar_strings(retorno, "\nif (");
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
    retorno = concatenar_strings(retorno, ";}");

    free(label);
    return retorno;
}

//receber um vetor de strings no caso_um_mais
char* gerar_escolha(char* id, char*  caso_um_mais, char* caso_contrario) {
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

//senão_opc deve ser um vetor de string
char* gerar_se(char* exp, char* comandos, char* senao_opc, char* comandos_senao) {
    char *retorno = "if(";
    retorno = concatenar_strings(retorno, exp);
    retorno = concatenar_strings(retorno, "){\n");
    retorno = concatenar_strings(retorno, comandos);
    retorno = concatenar_strings(retorno, "}");

    if(strcmp(senao_opc, "") != 0){
        //VER COMO RECEBER OS COMANDOS
    }

    if(strcmp(comandos_senao, "") != 0){
        retorno = concatenar_strings(retorno, "\nelse{\n");
        retorno = concatenar_strings(retorno, comandos_senao);
        retorno = concatenar_strings(retorno, "}");
    }

    return retorno;
}

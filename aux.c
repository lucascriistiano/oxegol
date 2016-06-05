#include "aux.h"

se_t* criar_se(char* exp, char* comandos){
    se_t* se = (se_t*) malloc(sizeof(se_t));
    se->expressao = exp;
    se->comandos = comandos;
    se->proximo = NULL;
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



no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor) {
  no_literal_t* no = (no_literal_t*) malloc(sizeof(no_literal_t));
  no->tipo = tipo;
  no->valor = valor;  //Criar cópia e desalocar quando for do tipo string?
  return no;
}

no_operador_t* criar_no_operador(tipo_t tipo, tipo_t retorno, int num_op) {
    //TODO Verificar se conseguiu alocar
    no_operador_t* novo_operador = (no_operador_t*) malloc(sizeof(no_operador_t));
    novo_operador->tipo = tipo;
    novo_operador->retorno = retorno;
    novo_operador->num_op = num_op;
    novo_operador->proximo = NULL;
    return novo_operador;
}

void adicionar_tipo(no_operador_t* operador, tipo_t tipo, tipo_t retorno, int num_op) {
    no_operador_t* operador_atual = operador;
    while (operador_atual->proximo != NULL) {
        operador_atual = operador_atual->proximo;
    }

    //TODO Verificar se conseguiu alocar (para todos os outros => Ctrl + F malloc)
    no_operador_t* novo_operador = criar_no_operador(tipo, retorno, num_op);
    operador_atual->proximo = novo_operador;
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

char* concatenar_strings(char* primeira, char* segunda) {
    size_t tamanho = strlen(primeira) + strlen(segunda) + 1;
    char *resultado = malloc(tamanho*sizeof(char));
    
    sprintf(resultado, "%s%s", primeira, segunda);

    //free(primeira);

    return resultado;
}

char* gerar_concatena_texto(char* dstino,char* primeira, char* segunda){
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
    retorno = concatenar_strings(retorno, ";}");

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
    retorno = concatenar_strings(retorno, se_t->expressao);
    char *retorno = "){\n";
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
    retorno = concatenar_strings(retorno, se->comandos);
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

char * gerar_procedimento( char* id, char* parametros_opc, char* comandos_opc){
	char* retorno = "";
	retorno = concatenar_strings(retorno, "void");
	retorno = concatenar_strings(retorno, " ");
	retorno = concatenar_strings(retorno, id);
	retorno = concatenar_strings(retorno, "(");
	retorno = concatenar_strings(retorno, parametros_opc);

        retorno = concatenar_strings(retorno, "){\n");
	retorno = concatenar_strings(retorno, comandos_opc);

	retorno = concatenar_strings(retorno, ")}\n");
}

char * gerar_principal(char* comandos_opc){
	char* retorno = "int main(){\n";
	retorno = concatenar_strings(retorno, comandos_opc);
	retorno = concatenar_strings(retorno, "return 0;");
	retorno = concatenar_strings(retorno, ")}\n");
}

int escrever_arquivoc(char *codigo){
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
 
 
 char* gerar_comparar_strings( char* primeira, char* segunda){
    char *retorno = "strcmp(";
    retorno = concatenar_strings(retorno,primeira);
    retorno = concatenar_strings(retorno,",");
    retorno = concatenar_strings(retorno,segunda);
    retorno = concatenar_strings(retorno, ")");
    return retorno; 

}

char* gerar_comparar_char(char primeira, char segunda){
    char* retorno = "";
    retorno = concatenar_strings(retorno, "(");
    retorno = concatenar_strings(retorno,primeira);
    retorno = concatenar_strings(retorno,"==");
    retorno = concatenar_strings(retorno,segunda);
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

char * gerar_atribuicao(char* lado_esquerdo, char* lado_direito ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, lado_esquerto);
	retorno = concatenar_strings(retorno, " = ");
	retorno = concatenar_strings(retorno, "lado_direito");
	retorno = concatenar_strings(retorno, ";");
}

char * gerar_declaracao_sa(char* tipo, char* variavel ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, tipo);
	retorno = concatenar_strings(retorno, variavel);
	retorno = concatenar_strings(retorno, ";");
}

char * gerar_declaracao_ca(char* tipo, char* variavel, char* inicializacao  ){
	char* retorno = "";
	retorno = concatenar_strings(retorno, tipo);
	retorno = concatenar_strings(retorno, variavel);
	retorno = gerar_atribuicao(retorno, inicializacao);
	retorno = concatenar_strings(retorno, ";");
}
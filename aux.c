#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *concatena_strings( char *primeira, char *segunda) {
    size_t tamanho = strlen(primeira) + strlen(segunda) + 1;
    char *resultado = malloc(tamanho*sizeof(char));
    sprintf(resultado, "%s%s", primeira, segunda);
    
    //free(primeira);
    
    return resultado;
}

char *gerar_label(char* comando, int numero) {
    char numero_char[15];
	sprintf(numero_char, "%d", numero);
	size_t tamanho =(strlen(comando)+strlen(numero_char) + 1);
	char *resultado = malloc(tamanho *sizeof(char));
    sprintf(resultado, "%s%s", comando, numero_char);
    return resultado;
}

char *gera_para(int npara, char* id, char* exp_inicializacao, char* exp_parada, char* comandos){
    char *retorno = "";
    
    //Inicializa contador
    retorno = concatena_strings(retorno, id);
    retorno = concatena_strings(retorno, "=");
    retorno = concatena_strings(retorno, exp_inicializacao);
    retorno = concatena_strings(retorno, ";\n");
    
    //Define label para for
    char *label = gerar_label("for", npara);
    retorno = concatena_strings(retorno, label);
    retorno = concatena_strings(retorno, ":\n");
    
    //Insere comandos já formatados
    retorno = concatena_strings(retorno, comandos);
    
    //Verifica se o for é decrescente para decrementar contador
    retorno = concatena_strings(retorno, "\nif (");
    retorno = concatena_strings(retorno, exp_inicializacao);
    retorno = concatena_strings(retorno, ">");
    retorno = concatena_strings(retorno, exp_parada);
    retorno = concatena_strings(retorno, "){\n");
    retorno = concatena_strings(retorno, id);
    retorno = concatena_strings(retorno, "--;}");
    
    //Verifica se o for e crescente para incrementar contador
    retorno = concatena_strings(retorno, "\nif (");
    retorno = concatena_strings(retorno, exp_inicializacao);
    retorno = concatena_strings(retorno, " < ");
    retorno = concatena_strings(retorno, exp_parada);
    retorno = concatena_strings(retorno, "){\n");
    retorno = concatena_strings(retorno, id);
    retorno = concatena_strings(retorno, "++;}");
    
    //Condição de parada
    retorno = concatena_strings(retorno, "\nif (");
    retorno = concatena_strings(retorno, id);
    retorno = concatena_strings(retorno, "!=");
    retorno = concatena_strings(retorno, exp_parada);
    retorno = concatena_strings(retorno, "){\n");
    retorno = concatena_strings(retorno, "goto ");
    retorno = concatena_strings(retorno, label);
    retorno = concatena_strings(retorno, ";}");
    
  
    free(label);
    
    return retorno;
}

char *gera_enquanto( int nenquanto, char* exp_parada, char*comandos){
	char *retorno = "";
	//Define label para for
    char *label = gerar_label("while", nenquanto);
    retorno = concatena_strings(retorno, label);
    retorno = concatena_strings(retorno, ":\n");
    
    //Insere comandos já formatados
    retorno = concatena_strings(retorno, comandos);
    
     //Condição de parada
    retorno = concatena_strings(retorno, "\nif (");
    retorno = concatena_strings(retorno, exp_parada);
    retorno = concatena_strings(retorno, "){\n");
    retorno = concatena_strings(retorno, "goto ");
    retorno = concatena_strings(retorno, label);
    retorno = concatena_strings(retorno, ";}");
      
    free(label);
    return retorno;
}



//receber um vetor de strings no caso_um_mais
char *gera_escolha(char* id, char * caso_um_mais, char* caso_contrario){
    char *retorno = "switch (";  
    retorno = concatena_strings(retorno, id);
    retorno = concatena_strings(retorno, "){\n");
    retorno = concatena_strings(retorno, caso_um_mais);
    retorno = concatena_strings(retorno, caso_contrario);
    retorno = concatena_strings(retorno, "}");      
}

char *gera_caso(char* valor, char * comandos){
    char *retorno = "case ";
    retorno = concatena_strings(retorno, valor);
    retorno = concatena_strings(retorno, ":\n");
    retorno = concatena_strings(retorno, comandos);
    retorno = concatena_strings(retorno, "break;\n");    
}

char *gera_caso_contrario(char * comandos){
    
    char *retorno = "default:\n";
    retorno = concatena_strings(retorno, comandos);
}

//senão_opc deve ser um vetor de string
char* gera_se(char* exp, char* comandos, char* senao_opc, char* comandos_senao){
    char *retorno = "if(";
    retorno = concatena_strings(retorno, exp);
    retorno = concatena_strings(retorno, "){\n");
    retorno = concatena_strings(retorno, comandos);
    retorno = concatena_strings(retorno, "}");
    
    if(senao_opc != ""){
        //VER COMO RECEBER OS COMANDOS
    }
    
    if(comandos_senao != ""){
        retorno = concatena_strings(retorno, "\nelse{\n");
        retorno = concatena_strings(retorno, comandos_senao);
        retorno = concatena_strings(retorno, "}");
    }
}


void main(){
	char *para = gera_para( 1, "casa", "2+3", "200", "<Comandos>");
	char *caso = gera_caso("2","<comandos>");
	char *caso_contrario = gera_caso_contrario("<comandos_caso_contrario>");
    char *escolha = gera_escolha("var", caso , caso_contrario );
    printf("%s", escolha);
    printf("\n\n%s", para);
    
    char *enquanto = gera_enquanto(12, "30>a", "<comandos>");
    printf("\n\n%s", enquanto);
    
    char *se = gera_se("30+20 > 10", "<comandos>", "", "<comandos_senao>");
    printf("\n\n%s", se);
    
}

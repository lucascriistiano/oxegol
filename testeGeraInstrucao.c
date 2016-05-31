#include "aux.h"

int main() {
    char *para = gerar_para( 1, "casa", "2+3", "200", "<Comandos>");
    char *caso = gerar_caso("2","<comandos>");
    char *caso_contrario = gerar_caso_contrario("<comandos_caso_contrario>");
    char *escolha = gerar_escolha("var", caso , caso_contrario );
    printf("%s", escolha);
    printf("\n\n%s", para);

    char *enquanto = gerar_enquanto(12, "30>a", "<comandos>");
    printf("\n\n%s", enquanto);

    char *se = gerar_se("30+20 > 10", "<comandos>", "", "<comandos_senao>");
    printf("\n\n%s", se);

    return 0;
}

programa: declaracao_zero_mais bloco_declaracao_variaveis PRINCIPAL CHAVE_ESQ comandos_zero_mais CHAVE_DIR
          ;

bloco_declaracao_variaveis: /* vazio */
                           |

declaracao_zero_mais:  /* vazio */
                      |
                      declaracao PONTO_E_VIRGULA declaracao_zero_mais
                      ;

declaracao: declaracao_registro
            |
            declaracao_func
            |
            declaracao_proc
            ;

declaracao_registro: REGISTRO ID CHAVE_ESQ campo_um_mais CHAVE_DIR
                     ;

declaracao_func: FUNCAO ID PAR_ESQ parametros_formais_opc PAR_DIR RETORNA tipo CHAVE_ESQ comandos_zero_mais CHAVE_DIR
                 ;

parametros_formais_opc: /* vazio */
                        |
                        parametros_formais
                        ;

parametros_formais: parametro_formal
                    |
                    VIRGULA parametro_formal parametros_formais
                    ;

parametros_reais: expressao
                  |
                  VIRGULA expressao parametros_reais
                  ;

ref_opc: /* vazio */
         |
         REFERENCIA
         ;

tipo: INTEIRO
      |
      REAL
      |
      STRING
      |
      CARACTERE
      |
      BOOLEANO
      |
      BYTE
      |
      ID
      ;

declaracao_proc: PROCEDIMENTO ID PAR_ESQ parametros_formais_opc PAR_DIR CHAVE_ESQ comandos_zero_mais CHAVE_DIR
                 ;

declaracao_var_zero_mais: /* vazio */
                          |
                          declaracao_var declaracao_var_zero_mais
                          ;

declaracao_var: declaracao_var_primitiva
                |
                declaracao_var_array
                |
                declaracao_var_registro
                ;

declaracao_var_primitiva: tipo ID ini_opc
                          ;

ini_opc: /* vazio */
         |
         ATRIBUICAO expressao
         ;

declaracao_var_array: tipo ID array_um_mais
                      ;

array_um_mais: COLCHETE_ESQ expressao COLCHETE_DIR
               |
               COLCHETE_ESQ expressao COLCHETE_DIR array_um_mais
               ;

declaracao_var_registro: ID ID
                         ;

comandos_zero_mais: /* vazio */
                    |
                    comando PONTO_E_VIRGULA comandos_zero_mais
                    ;

comando: se
         |
         para
         |
         escolha
         |
         enquanto
         |
         retorne
         |
         PARE
         ;

se: SE PAR_ESQ expressao_logica PAR_DIR CHAVE_ESQ comandos_zero_mais CHAVE_DIR senao_zero_mais
    ;

senao_zero_mais: /* vazio */
                 |
                 senao
                 |
                 senao_se
                 ;

senao: SENAO CHAVE_ESQ comandos_zero_mais CHAVE_DIR
       ;

senao_se: SENAO se
          ;

para: PARA PAR_ESQ ID DE expressao ATE expressao PAR_DIR CHAVE_ESQ comandos_zero_mais CHAVE_DIR
      ;

escolha: ESCOLHA PAR_ESQ expressao PAR_DIR CHAVE_ESQ caso_um_mais caso_contrario_opc CHAVE_DIR
         ;

caso_contrario_opc: /* vazio */
                    |
                    caso_contrario
                    ;

caso_contrario: CASOCONTRARIO DOIS_PONTOS comandos_zero_mais
                ;

caso_um_mais: caso
              |
              caso caso_um_mais
              ;

caso: CASO literal DOIS_PONTOS comandos_zero_mais
      ;

enquanto: ENQUANTO PAR_ESQ expressao> PAR_DIR CHAVE_ESQ comandos_zero_mais CHAVE_DIR
          ;

retorne: RETORNE expressao_opc
         ;

expressao_opc: /* vazio */
               |
               expressao
               ;

operador_sobre_bits: E_BITS
                     |
                     OU_BITS
                     |
                     XOR_BITS
                     |
                     DESLOCAMENTO_ESQ
                     |
                     DESLOCAMENTO_DIR
                     |
                     NAO_BITS
                     ;

operador_binario: MAIS
                  |
                  MENOS
                  |
                  ASTERISCO
                  |
                  BARRA
                  |
                  MENOR
                  |
                  MAIOR
                  |
                  MENOR_IGUAL
                  |
                  MAIOR_IGUAL
                  |
                  IGUAL
                  |
                  MOD
                  |
                  E_LOGICO
                  |
                  OU_LOGICO
                  ;

operador_unario: NAO_LOGICO
                 |
                 MAIS MAIS
                 |
                 MENOS MENOS
                 |
                 MENOS
                 ;

expressao: chamada_funcao
           |
           literal
           |
           operador_unario expressao
           |
           expressao operador_binario expressao
           |
           PAR_ESQ expressao PAR_DIR
           ;

chamada_funcao: ID PAR_ESQ parametros_reais PAR_DIR
                ;

literal: LITERAL_INTEIRO
         |
         LITERAL_REAL
         |
         LITERAL_BOOLEANO
         |
         LITERAL_STRING
         |
         LITERAL_CARACTERE
         ;

campo_um_mais: campo
               |
               campo campo_um_mais
               ;

campo: tipo ID
       ;
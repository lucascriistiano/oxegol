#!/bin/bash

# ================== COMPILACAO ==================
flex oxegol.l
yacc -d -v oxegol.y
cc -std=c99 lex.yy.c y.tab.c hash.c escopo.c aux.c -o programa.oxe -g

# ============= EXECUCAO DE EXEMPLOS =============
# echo '===== Quicksort ====='
# ./programa.oxe exemplos/quicksort.oxe

# echo '===== Eh primo ====='
# ./programa.oxe exemplos/eprimo.oxe

# echo '===== Menu ====='
# ./programa.oxe exemplos/menu.oxe

# echo '===== Impar ou Par ====='
# ./programa.oxe exemplos/impar_par.oxe

# echo '===== Funcionario ====='
# ./programa.oxe exemplos/funcionario.oxe

# echo '===== Deslocamento ====='
# ./programa.oxe exemplos/deslocamento.oxe

echo '===== Teste Simples ====='
./programa.oxe exemplos/testesimples.oxe

# =================== LIMPEZA ===================
rm lex.yy.c
rm y.output
rm y.tab.c
rm y.tab.h
# rm programa.oxe

# =================== TESTES ===================
# echo '===== Hash ====='
# cc testeHash.c hash.c -o testeHash
# ./testeHash
# rm testeHash

# echo '===== Gerar Instrucoes ====='
# gcc -o testeGeraInstrucao testeGeraInstrucao.c aux.c
# ./testeGeraInstrucao
# rm testeGeraInstrucao
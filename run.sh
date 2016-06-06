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

# echo '===== Teste Simples ====='
# ./programa.oxe exemplos/testesimples.oxe

# ============= EXECUCAO DE EXEMPLOS DA APRESENTACAO =============
# echo '===== Fatorial ====='
# ./programa.oxe exemplos/apresentacao/fatorial.oxe

# echo '===== Fibonacci ====='
# ./programa.oxe exemplos/apresentacao/fibonacci.oxe

# echo '===== Programa A ====='
# ./programa.oxe exemplos/apresentacao/programaA.oxe

# echo '===== Programa B ====='
# ./programa.oxe exemplos/apresentacao/programaB.oxe

# echo '===== Programa C ====='
# ./programa.oxe exemplos/apresentacao/programaC.oxe

echo '===== Programa D ====='
./programa.oxe exemplos/apresentacao/programaD.oxe

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
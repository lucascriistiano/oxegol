#!/bin/bash

# Compilacao e execucao
flex oxegol.l
yacc -d -v oxegol.y
cc lex.yy.c y.tab.c hash.c escopo.c -o programa.oxe

# Executar exemplos
echo '===== Quicksort ====='
./programa.oxe exemplos/quicksort.oxe

echo '===== Eh primo ====='
./programa.oxe exemplos/eprimo.oxe

echo '===== Menu ====='
./programa.oxe exemplos/menu.oxe

echo '===== Impar ou Par ====='
./programa.oxe exemplos/impar_par.oxe

echo '===== Funcionario ====='
./programa.oxe exemplos/funcionario.oxe

echo '===== Deslocamento ====='
./programa.oxe exemplos/deslocamento.oxe

# Compilação do Hash
# gcc -o test testeHash.c hash.c -lm

# Limpeza de arquivos criados
rm lex.yy.c
rm y.output
rm y.tab.c
rm y.tab.h
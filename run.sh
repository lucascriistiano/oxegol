#!/bin/bash

# Compilacao e execucao
flex oxegol.l
yacc -d -v oxegol.y
cc lex.yy.c y.tab.c -o programa.oxe
./programa.oxe < quicksort.oxe

# Limpeza de arquivos criados
rm lex.yy.c
# rm y.output
rm y.tab.c
rm y.tab.h

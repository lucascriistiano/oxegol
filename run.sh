#!/bin/bash

# Compilacao e execucao lex (flex)
flex oxegol.l
gcc lex.yy.c -ll
./a.out < quicksort.oxe

# Compilação yahcc (bison)
bison -v -d oxegol.y

# Limpeza de arquivos criados
rm lex.yy.c
rm a.out

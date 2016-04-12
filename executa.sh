#!/bin/bash

# Compilacao e execucao
flex oxegol.l
gcc lex.yy.c -ll
./a.out < teste.oxe

# Limpeza de arquivos criados
rm lex.yy.c
rm a.out

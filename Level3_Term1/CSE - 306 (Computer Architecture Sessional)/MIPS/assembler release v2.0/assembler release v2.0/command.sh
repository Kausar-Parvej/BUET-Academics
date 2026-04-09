#!/bin/bash

yacc -d -y parser.y
g++ -w -c -o y.o y.tab.c
flex lexer.lex
g++ -w -c -o l.o lex.yy.c
g++ y.o l.o
echo 'All ready, running'
./a.out input.txt POJMBNDECAGIHKLF

#!/bin/bash


#bison -d -o parser.cpp 2005076.y
yacc -d -o parser.cpp 2005076.y
echo 'Generated the parser.cpp and parser.hpp file'

flex -o lex.cpp 2005076.l
echo 'Generated the lex.cpp file'

g++ lex.cpp parser.cpp -fsanitize=address -g -o out
echo 'All ready, running'

./out input.c
#rm lex.yy.c y.tab.c y.tab.h out


yacc -d 2005076.y
echo 'Generated the parser C file'
flex 2005076.l
echo 'Generated the scanner C file'
g++ lex.yy.c y.tab.c -fsanitize=address -g -o out
echo 'All ready, running'
./out input.c
rm lex.yy.c y.tab.c y.tab.h out
yacc -d 2005076.y
echo 'Parsed'
flex 2005076.l
echo 'Scanned'
g++ lex.yy.c y.tab.c utilities.cpp -fsanitize=address -g -o out
echo 'All ready, running'
./out input.c
rm lex.yy.c y.tab.c y.tab.h out

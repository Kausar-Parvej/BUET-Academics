flex -o lex.cpp 2005076.l
g++ lex.cpp -lfl -o lexer.out
./lexer.out input.txt
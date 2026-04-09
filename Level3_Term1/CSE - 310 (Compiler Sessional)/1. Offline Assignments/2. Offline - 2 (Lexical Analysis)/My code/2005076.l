%option noyywrap

%x CHAR
%x STRING
%x SINGLE_COMMENT
%x MULTI_COMMENT

%{
#include<stdio.h>
#include<stdlib.h>

#include "2005076_functions.cpp"

%}

LETTER [A-Za-z]|_
ALPHANUMERIC [a-zA-Z0-9]|_
DIGIT [0-9]
DIGITS {DIGIT}+
NEWLINE \r?\n
WHITESPACE [ \t\v\f]+

ID {LETTER}({ALPHANUMERIC})*
NUMBER ({DIGITS})?(\.{DIGITS})?(E[+-]?{DIGITS})?






%%

{WHITESPACE}							{}
{NEWLINE}+({WHITESPACE}|{NEWLINE})*		{check_indentaion(yytext);}
{NEWLINE}+({WHITESPACE}|{NEWLINE})*"}"	{
											symbol_table.exitScope();
											if(tabCount>0) tabCount--;
											check_indentaion(yytext);
											operator_token("RCURL", "}");
										}





"if"		|
"else"		|
"for"		|
"while"		|
"do"		|
"break"		|
"int"		|
"char"		|
"float"		|
"double"	|
"void"		|
"return"	|
"case"		|
"switch"	|
"default"	| 
"continue"	{keyword_token(yytext);}



"+"|"-"								     	{operator_token("ADDOP", yytext);}
"++"|"--"								    {operator_token("INCOP", yytext);}
"<="|">="|"=="|"!="|">"|"<"	     			{operator_token("RELOP", yytext);}
"*"|"/"|"%"							     	{operator_token("MULOP", yytext);}
"="										    {operator_token("ASSIGNOP", yytext);}
"&&"|"||"								    {operator_token("LOGICOP", yytext);}
"&"|"|"|"^"|"<<"|">>"			     		{operator_token("BITOP", yytext);}
"!"										    {operator_token("NOT", yytext);}
"("										    {operator_token("LPAREN", yytext);}
")"										    {operator_token("RPAREN", yytext);}
"{"										    {symbol_table.enterScope(); operator_token("LCURL", yytext); tabCount++;}
"}"										    {symbol_table.exitScope(); operator_token("RCURL", yytext); if(tabCount>0) tabCount--;}
"["										    {operator_token("LSQUARE", yytext);}
"]"										    {operator_token("RSQUARE", yytext);}
","										    {operator_token("COMMA", yytext);}
";"										    {operator_token("SEMICOLON", yytext);}


{ID}			{identifier_token(yytext);}
{DIGITS}		{constInt_token(yytext);}
{NUMBER}		{constFloat_token(yytext);}




{DIGIT}*(\.{DIGIT}*)\.[\.0-9E+-]*(\.)*									{error_count++; error("TOO_MANY_DECIMAL_POINTS", yytext);}
({DIGIT}*(\.{DIGIT}*)?[E][+-]?{DIGIT}*[\.0-9E+-]*(\.)*)|({DIGITS}\.)	{error_count++; error("ILLFORMED_NUMBER", yytext);}
{NUMBER}{LETTER}+{NUMBER}?												{error_count++; error("INVALID_ID_SUFFIX_NUM_PREFIX", yytext);}


\'				{result_char = ""; BEGIN CHAR;}
\"				{result_str = ""; result_logStr = "\""; string_flag = 1;  BEGIN STRING;}
\/\/			{result_comment = "//"; BEGIN SINGLE_COMMENT;}
\/\*			{result_comment = "/*"; BEGIN MULTI_COMMENT;}


<CHAR>\\\'\'		{result_char += "\'";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\\"\'		{result_char += "\"";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\n\'			{result_char += "\n";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\t\'			{result_char += "\t";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\\\\'		{result_char += "\\";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\a\'			{result_char += "\a";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\f\'			{result_char += "\f";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\r\'			{result_char += "\r";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\b\'			{result_char += "\b";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\v\'			{result_char += "\v";  character_token(result_char); BEGIN INITIAL;}
<CHAR>\\0\'			{result_char += "\0";  character_token(result_char); BEGIN INITIAL;}

<CHAR>\\\'			{result_char += "'\\\'";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\\"			{result_char += "'\\\"";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\n			{result_char += "'\\n";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\t			{result_char += "'\\t";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\\\			{result_char += "'\\\\";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\a			{result_char += "'\\a";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\f			{result_char += "'\\f";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\r			{result_char += "'\\r";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\b			{result_char += "'\\b";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\v			{result_char += "'\\v";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}
<CHAR>\\0			{result_char += "'\\0";  error_count++; error("UNFINISHED_CONST_CHAR", result_char); BEGIN INITIAL;}

<CHAR>\'            {error_count++; error("EMPTY_CONST_CHAR", "''"); BEGIN INITIAL;}
<CHAR>[\r]?\n	{
					error_count++; 
					error("UNFINISHED_CONST_CHAR", "\'");
					line_number++;
					BEGIN INITIAL;
				}
<CHAR><<EOF>>	{
					error_count++; 
					error("UNFINISHED_CONST_CHAR", "\'");
					BEGIN INITIAL;
					file_end();
					return 0;
				}

<CHAR>[^\'\n]*\'		{
						result_char = (string) yytext;
						result_char.pop_back(); 
						
						if(result_char.size() == 1){
							character_token(result_char); 
						}
						else if(result_char.size() == 0){
							error_count++;
							error("EMPTY_CONST_CHAR", "''");
						}
						else{
							error_count++; 
							string temp = "'";
							temp += yytext;
							error("MULTICHAR_CONST_CHAR", temp);
						}

						BEGIN INITIAL;
					}

<CHAR>.			{error_count++; string temp = "'"; temp+=yytext; error("UNFINISHED_CONST_CHAR", temp); BEGIN INITIAL;}




<STRING>\\\'		{result_str += "\'"; result_logStr += "\\\'";}
<STRING>\\\"		{result_str += "\""; result_logStr += "\\\"";}
<STRING>\\n			{result_str += "\n"; result_logStr += "\\n";}
<STRING>\\t			{result_str += "\t"; result_logStr += "\\t";}
<STRING>\\\\		{result_str += "\\"; result_logStr += "\\\\";}
<STRING>\\a			{result_str += "\a"; result_logStr += "\\a";}
<STRING>\\f			{result_str += "\f"; result_logStr += "\\f";}
<STRING>\\r			{result_str += "\r"; result_logStr += "\\r";}
<STRING>\\b			{result_str += "\b"; result_logStr += "\\b";}
<STRING>\\v			{result_str += "\v"; result_logStr += "\\v";}
<STRING>\\0			{result_str += "\0"; result_logStr += "\\0";}


<STRING>\\\r\n		{string_flag = 2; inner_newLine++; result_logStr += "\\\r\n";}
<STRING>\\\n		{string_flag = 2; inner_newLine++; result_logStr += "\\\n";}

<STRING>\r\n|\n		{
						error_count++; 
						line_number += inner_newLine;
						error("UNFINISHED_STRING", result_logStr);
						line_number++;
						inner_newLine = 0;
						BEGIN INITIAL;
					}
<STRING><<EOF>>		{
						error_count++; 
						line_number += inner_newLine;
						inner_newLine = 0;
						error("UNFINISHED_STRING", result_logStr);
						BEGIN INITIAL;
						file_end();
						return 0;
					}

<STRING>\"			{
						result_logStr += "\"";
						string_token(result_str, result_logStr);
						line_number += inner_newLine;
						inner_newLine = 0;
						BEGIN INITIAL;
					}
<STRING>.			{result_str += yytext; result_logStr += yytext;}




<SINGLE_COMMENT>\\[\r]?\n 	{result_comment += "\\\n"; inner_newLine++;}
<SINGLE_COMMENT><<EOF>>		{comment(result_comment, 1); BEGIN INITIAL; file_end(); return 0;}
<SINGLE_COMMENT>[\r]?\n		{
								inner_newLine++;
								comment(result_comment, 1);
								line_number += inner_newLine;
								inner_newLine = 0;
								BEGIN INITIAL;
							}
<SINGLE_COMMENT>.			{result_comment += yytext;}



<MULTI_COMMENT>[\r]?\n		{inner_newLine++; result_comment += "\n";}
<MULTI_COMMENT><<EOF>>		{
								error_count++;
								line_number += inner_newLine;
								inner_newLine = 0;
								error("UNFINISHED_COMMENT", result_comment);
								BEGIN INITIAL;
								file_end();
								return 0;
							}
<MULTI_COMMENT>\*\/			{
								result_comment += "*/";
								comment(result_comment, 2);
								line_number += inner_newLine;
								inner_newLine = 0;
								BEGIN INITIAL;
							}
<MULTI_COMMENT>.			{result_comment += yytext;}






. {error_count++; error("UNRECOGNIZED_CHAR", yytext);}
<<EOF>> 		{file_end(); return 0;}






%%


int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	

	yyin= fin;
	yylex();
	fclose(yyin);
	return 0;




    /*
        chmod +x command.sh
        ./command.sh


		flex -o lex.cpp 2005076.l
		g++ lex.cpp -lfl -o lexer.out
		./lexer.out input.txt			

    */
}

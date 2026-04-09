#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
#include "2005076_SymbolTable.cpp"
#include "parser.hpp"

extern SymbolTable* symbol_table;
extern ofstream log_out;
extern ofstream error_out;

extern YYSTYPE yylval;

int line_number = 1;
int error_count = 0;
int warning_count = 0;

int inner_newLine = 0;

string result_str = "";
string result_logStr = "";
string result_char = "";
string result_comment = "";

int string_flag = 1;


int tabCount = 0;
int current_tab = 0;

string get_upperCase(string str)
{
	for(auto &ch:str) ch = toupper(ch);
	return str;
}

void print_lexeme_log(string str1, string str2){
    log_out<<"Line# "<<line_number<<": Token <"<<str1<<"> Lexeme "<<str2<<" found\n";
}


void terminal_token(string symbol_name, string type, string token_name){
    yylval.symbolInfo = new SymbolInfo(symbol_name, type);
    yylval.symbolInfo->grammar_rule = token_name + " : " + symbol_name;
    yylval.symbolInfo->startLine = line_number;
    yylval.symbolInfo->endLine = line_number;
    yylval.symbolInfo->isTerminal = true;
}

void keyword_token(string keyword){
    //token_out<<"<"<<get_upperCase(keyword)<<", "<<keyword<<">\n";
    print_lexeme_log(get_upperCase(keyword), keyword);
}

void identifier_token(string id){
    //token_out<<"<ID, "<<id<<">\n";
    print_lexeme_log("ID", id);

    yylval.symbolInfo = new SymbolInfo(id, "ID");
    yylval.symbolInfo->isTerminal = true;
    yylval.symbolInfo->startLine = line_number; yylval.symbolInfo->endLine = line_number;
    yylval.symbolInfo->grammar_rule = "ID : " + id;

    // if(symbol_table->currentScope->lookUp(id) == nullptr){
    //     symbol_table->insert(id, "ID");
    // }
    // else
    //     log_out<<"\t"<<id<<" already exists in the current ScopeTable\n";
    
}

void constInt_token(string num){
    //token_out<<"<CONST_INT, "<<num<<">\n";
    print_lexeme_log("CONST_INT", num);

    yylval.symbolInfo = new SymbolInfo(num, "CONS_INT");
    yylval.symbolInfo->isTerminal = true;
    yylval.symbolInfo->startLine = line_number; yylval.symbolInfo->endLine = line_number;
    yylval.symbolInfo->grammar_rule = "CONST_INT : " + num;
}

void operator_token(string op_name, string op_symbol){
    //token_out<<"<"<<op_name<<", "<<op_symbol<<">\n";
    print_lexeme_log(op_name, op_symbol);

    terminal_token(op_symbol, op_name, op_name);
}

void character_token(string ch){
    //token_out<<"<CONST_CHAR, "<<ch<<">\n";
    print_lexeme_log("CONST_CHAR", ch);
}

void string_token(string token_str, string log_str){
    if(string_flag == 1){
        //token_out<<"<SINGLE LINE STRING, ";
        print_lexeme_log("SINGLE LINE STRING", log_str );
    } 
    else if(string_flag == 2){
        //token_out<<"<MULTI LINE STRING, ";
        print_lexeme_log("MULTI LINE STRING", log_str );
    } 
    //token_out<<token_str<<">\n";
}

void constFloat_token(string num){
    //token_out<<"<CONST_FLOAT, "<<num<<">\n";
    print_lexeme_log("CONST_FLOAT", num);

    yylval.symbolInfo = new SymbolInfo(num, "CONS_FLOAT");
    yylval.symbolInfo->isTerminal = true;
    yylval.symbolInfo->startLine = line_number; yylval.symbolInfo->endLine = line_number;
    yylval.symbolInfo->grammar_rule = "CONST_FLOAT : " + num;
}

void comment(string cmt, int flag){
    if(flag == 1){
        print_lexeme_log("SINGLE LINE COMMENT", cmt);
    }
    else if(flag == 2){
        print_lexeme_log("MULTI LINE COMMENT", cmt);
    }
}

void error(string error_msg, string yytex){
    log_out<<"Error at line# "<<line_number<<": "<<error_msg<<" "<<yytex<<"\n";
}

void check_indentaion(string whitespaces){
    int last_nl = 0;

    for(int i=0; i<whitespaces.size(); i++){
        if(whitespaces[i] == '\n'){
            line_number++;
            last_nl = i;
        }
    }

    current_tab = 0;
    for(int i = last_nl+1; i < whitespaces.size(); i++){
        if(whitespaces[i] == '\t') current_tab++;
        if(whitespaces[i] == ' '){
            warning_count++;
            log_out<<"Line# "<<line_number<<": Warning, tab requrired but got space.\n";
            return;
        }
    }
    if(current_tab != tabCount){
        warning_count++;
        log_out<<"Line# "<<line_number<<": warning, "<<tabCount<<" of tabs needed but got "<<current_tab<<" tabs.\n";
    }
}

void file_end(){
    log_out<<"\t"<<symbol_table->currentScope->print_scopeTable();
    
    log_out<<"Total lines: "<<line_number<<"\n";
    log_out<<"Total errors: "<<error_count<<"\n";
    log_out<<"Total warnings: "<<warning_count<<"\n";

    //token_out.close();
    log_out.close();
    cout<<endl<<"\t---->Check output text files<----"<<endl;
    
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
#include "2005076_SymbolTable.cpp"
int symbolTable_size = 11;


ofstream parseTree("parsetree.txt");
ofstream log_out("log.txt");
ofstream error_out("error.txt");

SymbolTable* symbol_table = new SymbolTable(symbolTable_size);
vector<Parameter> stored_fParam;

extern int line_number;
extern int error_count;
extern int warning_count;

int syntaxError_line = 0;

inline void free_symbol(SymbolInfo* symbol){
    if(symbol != nullptr){
        delete symbol;
        symbol = nullptr;
    }
}

void print_error(string error_msg, string error_content, int lineCount){
    error_count++;
	string temp = "";
	if(error_content != "none"){
		temp = "\'" + error_content + "\'";
	}

	error_out<< "Line# "<<lineCount<< ": ";
	error_out<<error_msg <<" "<<temp <<"\n";
}

void log_CFG_rule(string parent, string child){
    log_out<< parent <<" : "<<child<<"\n";
}

string casting(string type1, string type2){
    if(type1 == "error_type" || type2 == "error_type" || type1 == "VOID" || type2 == "VOID"){
        return "error_type";
    }
    else if(type1 == "FLOAT" || type1 == "FLOAT"){
        return "FLOAT";
    }
    return "INT";
}


void function_token(string function_name, string declaration_type, string type_spacifier, vector<Parameter> paramList){
    SymbolInfo* function_symbol = new SymbolInfo(function_name, "FUNCTION");
    function_symbol->func_decType = declaration_type;
    function_symbol->type_specifier = type_spacifier;
    for(Parameter param : paramList){
        function_symbol->add_param(param);
    }

    if(declaration_type == "DEFINITION"){
        stored_fParam.clear();
        stored_fParam = paramList;

        SymbolInfo* temp = symbol_table->lookUp(function_name);
        if(temp == nullptr){
            symbol_table->insert(function_symbol);
        }
        else{
            if(temp->func_decType == "DEFINITION"){
                print_error("Redefinition of function", function_name, line_number);
            }
            else if(temp->func_decType == "null"){
                print_error("\'"+function_name+"\' redeclared as different kind of symbol", "none", line_number);
            }
            else if(temp->parameter_list.size() != paramList.size()){
                print_error("Conflicting types for", function_name, line_number);
            }
            else if(temp->type_specifier != type_spacifier){
                print_error("Conflicting types for", function_name, line_number);
            }
            else{
                for(int k=0; k<temp->parameter_list.size(); k++){
                    if(temp->parameter_list[k].dataType != paramList[k].dataType){
                        print_error("Conflicting types for", function_name, line_number);
                    }
                }
            }

            temp->func_decType = "DEFINITION";
            free_symbol(function_symbol);
        }
    }
    else{
        for(int k=0; k<paramList.size(); k++){
            for(int p=k+1; p<paramList.size(); p++){
                if(paramList[k].param_name == "") continue;
                if(paramList[k].param_name == paramList[p].param_name){
                    print_error("Redefinition of parameter", paramList[k].param_name, line_number);
                    free_symbol(function_symbol);
                    return;
                }
            }
        }
        SymbolInfo* temp = symbol_table->lookUp(function_name);
        if(temp == nullptr){
            symbol_table->insert(function_symbol);
        }
        else{
            if(temp->func_decType != "null"){
                print_error("Redefinition of function", function_name, line_number);
            }
            else{
                print_error("\'"+function_name+"\' redeclared as different kind of symbol", "none", line_number);
            }
            free_symbol(function_symbol);
        }
    }

}

SymbolInfo* nonterminal_token(string symbol_name, string type, string token_name){
    SymbolInfo* temp = new SymbolInfo(symbol_name, type);
    temp->grammar_rule = token_name + " : " + symbol_name;
    temp->startLine = line_number;
    temp->endLine = line_number;
    temp->isTerminal = true;

    return temp;
}

SymbolInfo* errorToken(string grammar_rule){
    SymbolInfo* error_tok = new SymbolInfo("null", "error_token");
    error_tok->isTerminal = true;
    error_tok->startLine = syntaxError_line; error_tok->endLine = syntaxError_line;
    error_tok->grammar_rule = grammar_rule;
    
    return error_tok;
}

void symbol_tokens(string type_spec, vector<Parameter> &elementList){
    if(type_spec == "VOID"){
        string temp = "";
        for(int k=0; k<elementList.size(); k++){
            temp += elementList[k].param_name;
            if(k != elementList.size()-1){
                temp += ", ";
            }
        }
        print_error("Variable or field \'"+temp+"\' declared void", "none", line_number);
    }
    else{
        for(Parameter param : elementList){
            SymbolInfo* temp = symbol_table->find_inCurrentScope(param.param_name);
            if(temp == nullptr){
                SymbolInfo* symbol = new SymbolInfo(param.param_name, "ID");
                param.dataType = type_spec;
                if(param.array_type) symbol->isArray = true;
                symbol->type_specifier = type_spec;
                symbol_table->insert(symbol);
            }
            else if(temp->type_specifier != param.dataType){
                print_error("Conflicting types for", param.param_name, line_number);
            }
            else{
                print_error("Redefinition of variable", param.param_name, line_number);
            }
        }
    }
}

void end_parse(){
   
    log_out<<"Total LInes: "<<line_number<<"\n";
    log_out<<"Total Errors: "<<error_count<<"\n";

    delete symbol_table;

    log_out.close();
    parseTree.close();
    error_out.close();

    cout<<"\n\t---->Sucessfully Compiled, Check the Output files<-----\t\n";
}

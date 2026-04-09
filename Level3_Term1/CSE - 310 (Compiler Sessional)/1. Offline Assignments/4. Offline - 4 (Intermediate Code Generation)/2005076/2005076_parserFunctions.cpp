#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
#include "2005076_SymbolTable.cpp"
#include "2005076_ICGfunctions.cpp"
int symbolTable_size = 11;


ofstream parseTree("parsetree.txt");
ofstream log_out("log.txt");
ofstream error_out("error.txt");

SymbolTable* symbol_table;
vector<SymbolInfo*> forDelete;
vector<Parameter> stored_fParam;

extern int line_number;
extern int error_count;
extern int warning_count;

int syntaxError_line = 0;

void print_logicExOp(SymbolInfo* symbol);

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
    return;
    SymbolInfo* function_symbol = new SymbolInfo(function_name, "FUNCTION");
    function_symbol->func_decType = declaration_type;
    function_symbol->type_specifier = type_spacifier;
    for(Parameter param : paramList){
        function_symbol->add_param(param);
    }

    if(declaration_type == "DEFINITION"){
        stored_fParam.clear();
        stored_fParam = paramList;

        for(int i=0; i<paramList.size(); i++){
            if(paramList[i].param_name == ""){
                free_symbol(function_symbol);
                return;
            }
        }

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



bool println = false;
void traverse(SymbolInfo* symbol){
    if(symbol == nullptr) return;
    //cout<<symbol->grammar_rule<<"\n";

    printLine = symbol->startLine;
    // if(printLine != previous_lineCheck){
    //     assem_code<<";---> line no: "<<printLine<<"\r\n";
    //     previous_lineCheck = printLine;
    // }


    if(symbol->grammar_rule == "start : program"){
        initilize_code();
        traverse(symbol->children[0]);

        printingFunction();
        assem_code<<"END main\r\n";
    }
    else if(symbol->grammar_rule == "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON"){
        traverse(symbol->children[0]);
        traverse(symbol->children[3]);
    }
    else if(symbol->grammar_rule == "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON"){
        traverse(symbol->children[0]);
    }
    else if(symbol->grammar_rule == "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement"){
        traverse(symbol->children[0]);
        traverse(symbol->children[3]);

        initilize_functionPrint(symbol->children[1]->getName());
        traverse(symbol->children[5]);
        functionReturn(symbol->children[1]->getName(), symbol->children[5]->offset);
    }

    else if(symbol->grammar_rule == "func_definition : type_specifier ID LPAREN RPAREN compound_statement"){
        traverse(symbol->children[0]);
        initilize_functionPrint(symbol->children[1]->getName());
        //printLabel(create_newLabel());
        traverse(symbol->children[4]);
        functionReturn(symbol->children[1]->getName(), symbol->children[4]->offset);
    }


    else if(symbol->grammar_rule == "parameter_list : parameter_list COMMA type_specifier ID"){
        traverse(symbol->children[0]);
        traverse(symbol->children[2]);
    }


    else if(symbol->grammar_rule == "compound_statement : LCURL statements RCURL"){
        if(symbol->end_label == "") symbol->end_label = create_newLabel();
        symbol->children[1]->end_label = symbol->end_label;
        traverse(symbol->children[1]);
    }

    else if (symbol->grammar_rule == "var_declaration : type_specifier declaration_list SEMICOLON"){
        traverse(symbol->children[0]);
        traverse(symbol->children[1]);
        for(SymbolInfo* sym : symbol->children[1]->dec_List){
            if(symbol->is_global == false){
                if(sym->isArray){
                    //assem_code<<"\tSUB SP, "<<to_string(2*sym->array_size)<<"\n";
                    print_code("SUB SP, " + to_string(2*sym->array_size));
                }
                else print_code("SUB SP, 2");
            }
        }
    }
    
    else if(symbol->grammar_rule == "statements : statement"){
        symbol->children[0]->end_label = symbol->end_label;
        traverse(symbol->children[0]);
        assem_code<<symbol->end_label<<":\r\n";        
    }
    else if(symbol->grammar_rule == "statements : statements statement"){
        symbol->children[0]->end_label = create_newLabel();
        symbol->children[1]->end_label = symbol->end_label;
        traverse(symbol->children[0]);
        traverse(symbol->children[1]);
        assem_code<<symbol->end_label<<":\n";
    }

    else if(symbol->grammar_rule == "statement : compound_statement"){
        symbol->children[0]->end_label = create_newLabel();
        traverse(symbol->children[0]);
    }
    else if(symbol->grammar_rule == "statement : expression_statement"){
        traverse(symbol->children[0]);
    }


    else if(symbol->grammar_rule == "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"){
        traverse(symbol->children[2]);

        string lLoop = create_newLabel();
        print_code(lLoop+": ",false);
        symbol->children[3]->is_conditional = true;
        symbol->children[3]->true_label = create_newLabel();
        symbol->children[3]->flase_label = symbol->end_label;
        symbol->children[6]->end_label = create_newLabel();
        
        traverse(symbol->children[3]);
        print_code(symbol->children[3]->true_label+": ", false);
        traverse(symbol->children[6]);
        traverse(symbol->children[4]);
        print_code("JMP "+lLoop);

    }
    else if(symbol->grammar_rule == "statement : IF LPAREN expression RPAREN statement"){
        symbol->children[2]->true_label = create_newLabel();
        symbol->children[2]->flase_label = symbol->end_label;
        symbol->children[2]->is_conditional = true;
        symbol->children[4]->end_label = symbol->end_label;

        traverse(symbol->children[2]);
        print_code(symbol->children[2]->true_label+": ", false);
        traverse(symbol->children[4]);
    }
    else if(symbol->grammar_rule == "statement : IF LPAREN expression RPAREN statement ELSE statement"){
        symbol->children[2]->true_label = create_newLabel();
        symbol->children[2]->flase_label = create_newLabel();
        symbol->children[2]->is_conditional = true;
        symbol->children[4]->end_label = symbol->children[2]->flase_label;
        symbol->children[6]->end_label = symbol->end_label;

        traverse(symbol->children[2]);
        print_code(symbol->children[2]->true_label+": ", false);
        traverse(symbol->children[4]);
        print_code("JMP "+symbol->end_label);
        print_code(symbol->children[2]->flase_label+": ",false);
        traverse(symbol->children[6]);
    }

    else if(symbol->grammar_rule == "statement : WHILE LPAREN expression RPAREN statement"){
        string lLoop = create_newLabel();
        print_code(lLoop+": ",false);
        symbol->children[2]->is_conditional = true;
        symbol->children[2]->true_label = create_newLabel();
        symbol->children[2]->flase_label = symbol->end_label;
        symbol->children[4]->end_label = symbol->end_label;
        
        traverse(symbol->children[2]);
        print_code(symbol->children[2]->true_label+": ", false);
        traverse(symbol->children[4]);
        print_code("JMP "+lLoop);
        
    }
    else if(symbol->grammar_rule == "statement : RETURN expression SEMICOLON"){
        traverse(symbol->children[1]);
        print_code("MOV DX, CX");
        print_code("JMP "+symbol->children[0]->getName()+"_exit");
    }
    else if(symbol->grammar_rule == "statement : PRINTLN LPAREN ID RPAREN SEMICOLON"){
        println_code(symbol);
    }




    else if(symbol->grammar_rule == "expression_statement : expression SEMICOLON"){
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->is_conditional = symbol->is_conditional;

        traverse(symbol->children[0]);
    }
    else if(symbol->grammar_rule == "variable : ID"){
        if(symbol->is_global == false){
            stackPush("BP");
            print_code("MOV BX, " + to_string(symbol->offset));
            print_code("ADD BP, BX");
        }
    }
    else if(symbol->grammar_rule == "variable : ID LSQUARE expression RSQUARE"){
        traverse(symbol->children[2]);
        if(symbol->is_global){
            print_code("LEA SI, "+symbol->children[0]->getName());
            print_code("ADD SI, CX");
            print_code("ADD SI, CX");
            stackPush("BP");
            print_code("MOV BP, SI");
        }
        else{
            stackPush("BP");
            print_code("MOV BX, CX");
            print_code("ADD BX, BX");
            print_code("ADD BX, "+to_string(symbol->offset));
            print_code("ADD BP, BX");
        }
    }


    else if(symbol->grammar_rule == "expression : logic_expression"){
        symbol->children[0]->is_conditional = symbol->is_conditional;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->true_label = symbol->true_label;

        traverse(symbol->children[0]);
    }
    
    else if(symbol->grammar_rule == "expression : variable ASSIGNOP logic_expression"){
        traverse(symbol->children[2]);
        symbol->children[2]->is_conditional = false;
        symbol->children[0]->is_conditional = false;
        if(symbol->children[0]->is_global && !symbol->children[0]->isArray){
            traverse(symbol->children[0]);
            print_code("MOV "+symbol->children[0]->getName()+", CX");
        }
        else{
            stackPush("CX");
            traverse(symbol->children[0]);
            stackPop("AX");
            stackPop("CX");
            print_code("MOV [BP], CX");
            print_code("MOV BP, AX");
        }
        
        if(symbol->is_conditional) print_code("JMP "+symbol->true_label);
    }

    else if(symbol->grammar_rule == "logic_expression : rel_expression"){
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->is_conditional = symbol->is_conditional;
        traverse(symbol->children[0]);
        
    }
    else if(symbol->grammar_rule == "logic_expression : rel_expression LOGICOP rel_expression"){
        print_logicExOp(symbol);
    }


    else if(symbol->grammar_rule == "rel_expression : simple_expression"){
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->is_conditional = symbol->is_conditional;
        traverse(symbol->children[0]);
    }
    else if(symbol->grammar_rule == "rel_expression : simple_expression RELOP simple_expression"){
        traverse(symbol->children[0]);
        stackPush("CX");
        traverse(symbol->children[2]);

        string code = get_relationOp(symbol->children[1]->getName());
        stackPop("AX");
        print_code("CMP AX, CX");
        if(symbol->flase_label == "") symbol->flase_label = create_newLabel();
        if(symbol->true_label == "") symbol->true_label = create_newLabel();
        print_code(code + " " + symbol->true_label);
        print_code("JMP " + symbol->flase_label);

        if(symbol->is_conditional == false){
            string endLabel = create_newLabel();
            print_code(symbol->true_label + ": ", false);
            print_code("MOV CX, 1");
            print_code("JMP " + endLabel);
            print_code(symbol->flase_label + ": ", false);
            print_code("MOV CX, 0");
            print_code(endLabel + ": ", false);
        }

    }


    else if(symbol->grammar_rule == "simple_expression : term"){
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->is_conditional = symbol->is_conditional;
        traverse(symbol->children[0]);
    }
    else if(symbol->grammar_rule == "simple_expression : simple_expression ADDOP term"){
        traverse(symbol->children[0]);
        stackPush("CX");
        traverse(symbol->children[2]);
        stackPop("AX");

        if(symbol->children[1]->getName() == "+") print_code("ADD CX, AX");
        if(symbol->children[1]->getName() == "-"){
            print_code("SUB AX, CX");
            print_code("MOV CX, AX");
        } 
        if(symbol->is_conditional) end_Condition(symbol);
    }



    else if(symbol->grammar_rule == "term : unary_expression"){
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->is_conditional = symbol->is_conditional;
        traverse(symbol->children[0]);
    }
    else if(symbol->grammar_rule == "term : term MULOP unary_expression"){
        traverse(symbol->children[0]);
        stackPush("CX");
        traverse(symbol->children[2]);
        stackPop("AX");

        if(symbol->children[1]->getName() == "*"){
            print_code("IMUL CX");
            print_code("MOV CX, AX");
        }
        else if(symbol->children[1]->getName() == "/"){
            print_code("CWD");
            print_code("IDIV CX");
            print_code("MOV CX, AX");
        }
        else if(symbol->children[1]->getName() == "%"){
            print_code("CWD");
            print_code("IDIV CX");
            print_code("MOV CX, DX");
        }

        if(symbol->is_conditional) end_Condition(symbol);
    }



    else if(symbol->grammar_rule == "unary_expression : ADDOP unary_expression"){
        symbol->children[1]->is_conditional = symbol->is_conditional;
        symbol->children[1]->flase_label = symbol->flase_label;
        symbol->children[1]->true_label = symbol->true_label;

        traverse(symbol->children[1]);
        if(symbol->children[0]->getName() == "-") print_code("NEG CX");
    }

    else if(symbol->grammar_rule == "unary_expression : NOT unary_expression"){
        symbol->children[1]->is_conditional = symbol->is_conditional;
        symbol->children[1]->flase_label = symbol->true_label;
        symbol->children[1]->true_label = symbol->flase_label;

        traverse(symbol->children[1]);
        if(symbol->is_conditional == false){
            string a1 = create_newLabel();
            string a2 = create_newLabel();
            print_code("JCXZ " + a2);
            print_code("MOV CX, 0");
            print_code("JMP " + a1);
            print_code(a2 + ": ", false);
            print_code("MOV CX, 1");
            print_code(a1 + ": ", false);
        }
    }

    else if(symbol->grammar_rule == "unary_expression : factor"){
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[0]->is_conditional = symbol->is_conditional;
        traverse(symbol->children[0]);
    }

    else if(symbol->grammar_rule == "factor : variable"){
        traverse(symbol->children[0]);
        if(symbol->children[0]->is_global && !symbol->children[0]->isArray){
            print_code("MOV CX, "+symbol->children[0]->getName());
        }
        else{
            print_code("MOV CX, [BP]");
            stackPop("BP");
        }
        if(symbol->is_conditional) end_Condition(symbol);
    }

    else if(symbol->grammar_rule == "factor : ID LPAREN argument_list RPAREN"){
        traverse(symbol->children[0]);
        traverse(symbol->children[2]);

        print_code("CALL " + symbol->children[0]->getName());
        print_code("MOV CX, DX");
        print_code("ADD SP, " + to_string(symbol->children[2]->offset));
        if(symbol->is_conditional) end_Condition(symbol);
    }

    else if(symbol->grammar_rule == "factor : LPAREN expression RPAREN"){
        traverse(symbol->children[1]);
        if(symbol->is_conditional) end_Condition(symbol);
    }
    

    else if(symbol->grammar_rule == "factor : CONST_INT"){
        traverse(symbol->children[0]);
        print_code("MOV CX, "+symbol->getName());
        if(symbol->is_conditional) end_Condition(symbol);
    }
    else if(symbol->grammar_rule == "factor : CONST_FLOAT"){
        traverse(symbol->children[0]);
        print_code("MOV CX, "+symbol->getName());
        if(symbol->is_conditional) end_Condition(symbol);
    }

    else if(symbol->grammar_rule == "factor : variable INCOP"){
        traverse(symbol->children[0]);
        if(symbol->children[0]->is_global && !symbol->children[0]->isArray){
            print_code("MOV CX, " + symbol->children[0]->getName());
        }
        else print_code("MOV CX, [BP]");
        print_code("MOV AX, CX");

        if(symbol->children[1]->getName() == "++") print_code("INC CX");
        if(symbol->children[1]->getName() == "--") print_code("DEC CX");

        if(symbol->children[0]->is_global && !symbol->children[0]->isArray) print_code("MOV " +symbol->children[0]->getName()+ ", CX");
        else {
            print_code("MOV [BP], CX");
            stackPop("BP");
        }
        print_code("MOV CX, AX");
        if(symbol->is_conditional) end_Condition(symbol);
    }



    else if(symbol->grammar_rule == "arguments : arguments COMMA logic_expression"){
        traverse(symbol->children[0]);
        traverse(symbol->children[2]);
        print_code("PUSH CX");
    }
    else if(symbol->grammar_rule == "arguments : logic_expression"){
        traverse(symbol->children[0]);
        print_code("PUSH CX");
    }

    else{
        for(SymbolInfo* childSymbol : symbol->children){
            traverse(childSymbol);
            //cout<<childSymbol->grammar_rule<<"\n";
        }
    }
}


void print_logicExOp(SymbolInfo* symbol){
    symbol->children[2]->is_conditional = symbol->is_conditional;
    symbol->children[0]->is_conditional = symbol->is_conditional;
    if(symbol->children[1]->getName() == "||"){
        symbol->children[2]->true_label = symbol->true_label;
        symbol->children[2]->flase_label = symbol->flase_label;
        symbol->children[0]->true_label = symbol->true_label;
        symbol->children[0]->flase_label = create_newLabel()+"false";
    }
    else{
        symbol->children[0]->true_label = create_newLabel()+"true";
        symbol->children[0]->flase_label = symbol->flase_label;
        symbol->children[2]->true_label = symbol->true_label;
        symbol->children[2]->flase_label = symbol->flase_label;
    }

    traverse(symbol->children[0]);

    if(symbol->is_conditional){
        if(symbol->children[1]->getName() == "||") print_code(symbol->children[0]->flase_label+": ", false);
        else print_code(symbol->children[0]->true_label+": ",false);
    }
    else stackPush("CX");
    traverse(symbol->children[2]);

    if(symbol->is_conditional == false){
        stackPop("AX");
        string a1 = create_newLabel();
        string a2 = create_newLabel();
        string a3 = create_newLabel();
        if(symbol->children[1]->getName() == "||"){
            string a4 = create_newLabel();
            print_code("CMP AX, 0");
            print_code("JE " + a1);
            print_code("JMP " + a2);
            print_code(a1 + ":", false);
            print_code("JCXZ " + a3);
            print_code(a2 + ":", false);
            print_code("MOV CX, 1");
            print_code("JMP " + a4);
            print_code(a3 + ":", false);
            print_code("MOV CX, 0");
            print_code(a4 + ":", false);
        }
        else{
            print_code("CMP AX, 0");
            print_code("JE " + a1);
            print_code("JCXZ " + a1);
            print_code("JMP " + a2);
            print_code(a1 + ": ",false);
            print_code("MOV CX, 0");
            print_code("JMP " + a3);
            print_code(a2 + ": ", false);
            print_code("MOV CX, 1");
            print_code(a3 + ": ", false);
        }
    }
}

void end_parse(){
   
    log_out<<"Total LInes: "<<line_number<<"\n";
    log_out<<"Total Errors: "<<error_count<<"\n";

    cout<<"in end parse\n";
    for(SymbolInfo* symbol : forDelete){
        delete symbol;
    }
    delete symbol_table;

    log_out.close();
    parseTree.close();
    error_out.close();
    assem_code.close();

    cout<<"\n\t---->Sucessfully Compiled, Check the Output files<-----\t\n";
}

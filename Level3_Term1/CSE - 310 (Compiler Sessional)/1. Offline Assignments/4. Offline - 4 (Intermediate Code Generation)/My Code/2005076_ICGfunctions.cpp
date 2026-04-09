#pragma once
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
#include "2005076_SymbolInfo.cpp"

extern ofstream assem_code;

int label_number = 1;
map<int, string> labelMap;

vector<SymbolInfo*> global_variables;
int previous_lineCheck = 0;
int printLine  = 0;




void initilize_code(){
    assem_code<<".MODEL SMALL\r\n.STACK 1000H\r\n.DATA\r\n\tnumber DB \"00000$\"\r\n";
    for(SymbolInfo* si : global_variables){
        if(si->isArray){
            assem_code<<"\t"<<si->getName()<<" DW "<<si->array_size<<" DUP (0000H)\r\n";
            cout<<"in initialize array ... size= "<<si->array_size<<"\n";
        }
        else{
            assem_code<<"\t"<<si->getName()<<" DW 1 DUP (0000H)\r\n";
        }
    }
    assem_code<<".CODE\r\n";
}

void print_code(string code, bool hasTab = true){
    if(hasTab) assem_code<<"\t";
    assem_code<<code;
    if(previous_lineCheck != printLine){
        assem_code<<"           ; line: "<<printLine;
        previous_lineCheck = printLine;
    }
    assem_code<<"\r\n";
}

void stackPush(string var){
    print_code("PUSH " + var);
}
void stackPop(string var){
    print_code("POP " + var);
}

void idPrint(string id){
    stackPush("AX");
    print_code("MOV AX, "+id);
    print_code("CALL PRINT_OUTPUT");
    print_code("CALL PRINT_NEWLINE");
    stackPop("AX");
}


void initilize_functionPrint(string function){
    if(function == "main"){
        print_code("main PROC",false);
        print_code("MOV AX, @DATA");
        print_code("MOV DS, AX");
    }
    else{
        print_code(function + " PROC", false);
    }
    stackPush("BP");
    print_code("MOV BP, SP");
}

void functionReturn(string function, int offset){
    assem_code<<function<<"_exit:\r\n";
    if(function == "main"){
        print_code("MOV AX, 4CH");
        print_code("INT 21H");
    }
    assem_code<<"\tADD SP, "<<-offset<<"\r\n";
    stackPop("BP");
    if(function != "main") print_code("RET");
    assem_code<<function<<" ENDP\r\n";
}

string create_newLabel(){
    string newLabel = "L"+to_string(label_number);
    label_number++;
    return newLabel;
}

void printLabel(string label){
    assem_code<< label << ":\r\n";
}

void println_code(SymbolInfo* symbol){
    if(symbol->is_global){
        print_code("MOV AX, "+symbol->children[2]->getName());
        print_code("CALL PRINT_OUTPUT");
        print_code("CALL PRINT_NEWLINE");
    }
    else{
        stackPush("BP");
        print_code("MOV BX, "+to_string(symbol->offset));
        print_code("ADD BP, BX");
        print_code("MOV AX, [BP]");
        print_code("CALL PRINT_OUTPUT");
        print_code("CALL PRINT_NEWLINE");
        stackPop("BP");
    }
}

string get_relationOp(string sign){
    string code = "";
    if(sign == ">") code = "JG";
    else if(sign == "<") code = "JL";
    else if(sign == ">=") code = "JGE";
    else if(sign == "<=") code = "JLE";
    else if(sign == "==") code = "JE";
    else if(sign == "!=") code = "JNE";

    return code;
}

void end_Condition(SymbolInfo* symbol){
    print_code("JCXZ " + symbol->flase_label);
    print_code("JMP " + symbol->true_label);
}



void printingFunction() {
    assem_code<< "\r\n;-------------------------------\r\n;         print library   \r\n;-------------------------------";
    assem_code << "\r\nPRINT_OUTPUT PROC\r\n\tPUSH AX\r\n\tPUSH BX\r\n\tPUSH CX\r\n\tPUSH DX\r\n";
    assem_code << "\t; dividend in DX:AX\r\n\t; divisor in source, CX\r\n\tMOV CX, 10\r\n";
    assem_code << "\tXOR BL, BL \r\n\tCMP AX, 0\r\n\tJGE STACK_OP "
               "\r\n";
    assem_code << "\tMOV BH, 1\r\n\tNEG AX\r\nSTACK_OP:\r\n\tXOR DX, "
               "DX\r\n\tDIV CX\r\n";
    assem_code << "\t; quotient in AX, remainder in DX\r\n\tPUSH DX\r\n\tINC BL ; len++\r\n\tCMP AX, "
               "0\r\n\tJG STACK_OP\r\n";
    assem_code << "\tMOV AH, 02\r\n\tCMP BH, 1 \r\n\tJNE "
               "PRINT_LOOP\r\n";
    assem_code << "\tMOV DL, '-'\r\n\tINT 21H\r\nPRINT_LOOP:\r\n\tPOP DX\r\n\tXOR DH, DH\r\n\tADD "
               "DL, '0'\r\n\tINT 21H\r\n";
    assem_code << "\tDEC BL\r\n\tCMP BL, 0\r\n\tJG PRINT_LOOP\r\n\tPOP DX\r\n\tPOP CX\r\n\tPOP "
               "BX\r\n\tPOP AX\r\n\tRET\r\nPRINT_OUTPUT ENDP\r\n";

    assem_code << "\r\nPRINT_NEWLINE PROC\r\n\tPUSH AX\r\n\tPUSH DX\r\n\tMOV AH, 02\r\n\tMOV DL, "
               "0DH\r\n\tINT 21H\r\n";
    assem_code
        << "\tMOV DL, 0AH\r\n\tINT 21H\r\n\tPOP DX\r\n\tPOP AX\r\n\tRET\r\nPRINT_NEWLINE ENDP\r\n";
    assem_code<<";-------------------------------\r\n\n";
}

string emit_lastBlank(const string& string_line) {
    vector<char> space = {' ', '\t', '\r', '\n'};
    int start = 0;
    int size = string_line.size();
    while (start < size && find(space.begin(), space.end(), string_line[start]) != space.end()) start++;
    if (start == size) return "";
    int end = size - 1;
    while (end > start && find(space.begin(), space.end(), string_line[end]) != space.end()) end--;
    return string_line.substr(start, end - start + 1);
}

vector<string> split_string(const string& string_line) {
    vector<string> operands;
    int idx = 0;
    while (idx < string_line.size()) {
        int start = idx;
        while (idx < string_line.size() && string_line[idx] != ' ') idx++;
        if (idx > start) operands.push_back(string_line.substr(start, idx - start));
        if (operands.back().back() == ',') operands.back().pop_back();
        idx++;
    }
    return operands;
}


void code_optimizer(){
    ifstream file_in;
    ofstream opt_fileOUt;
    file_in.open("2005076_code.asm");
    opt_fileOUt.open("2005076_optCode.asm");
    using namespace std;
    string input_line;
    while(getline(file_in, input_line)){
        string modified_line = emit_lastBlank(input_line);
        vector<string> substr = split_string(modified_line);
        if(substr.empty() == false){
            if(substr.front() == "ADD" && substr[2] == "0") continue;
            else if(substr.front() == "IMUL" && substr[2] == "1") continue;

            else if(substr.front() == "PUSH"){
                vector<string> first_substr = substr;
                string first_line = input_line;
                if(getline(file_in, input_line)){
                    modified_line = emit_lastBlank(input_line);
                    substr = split_string(modified_line);
                    if(substr.front() == "POP" && substr[1] == first_substr[1]) continue;
                    else{
                        opt_fileOUt<< first_line <<"\n";
                        opt_fileOUt<< input_line <<"\n";
                        continue;
                    }
                }
                else{
                    opt_fileOUt<< first_line <<"\n";
                    continue;
                }
            }
            else if(substr.front() == "MOV"){
                vector<string> first_substr = substr;
                string first_line = input_line;
                if(getline(file_in, input_line)){
                    modified_line = emit_lastBlank(input_line);
                    substr = split_string(modified_line);
                    if(substr.front() == "MOV" && substr[1] == first_substr[2] && substr[2] == first_substr[1]) continue;
                    else{
                        opt_fileOUt<< first_line <<"\n";
                        opt_fileOUt<< input_line <<"\n";
                        continue;
                    }
                }
                else{
                    opt_fileOUt<< first_line <<"\n";
                    continue;
                }
            }
        }
        opt_fileOUt<<input_line<<"\n";
    }
    file_in.close();
    opt_fileOUt.close();
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
#include "SymbolTable.cpp"

#define input_file "input.txt"
#define output_file "output.txt"

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int bucket_number;
    fin >> bucket_number;
    int flag = 0;
    bool check;

    SymbolTable symbol_table(bucket_number);
    fout<<"\tScopeTable# 1 created\n";

    int inputCount = 0;
    string inputLine;
    getline(fin, inputLine);
    string inputWords[4];
    string temp;
    int cmdCount = 1;

    while(!fin.eof()){
        getline(fin, inputLine);
        inputCount = 0;
        flag = 0;
        fout<<"Cmd "<<cmdCount<<": "<<inputLine<<"\n";
        cmdCount++;

        stringstream ss(inputLine);
        while(ss >> temp){
            inputWords[inputCount] = temp;
            inputCount++;
            if(inputCount > 4){
                flag = 1;
                break;
            }
        }

        if(flag == 1) {
            fout<<"\tWrong number of arugments\n";
            continue;
        }

        if(inputWords[0] == "Q"){
            ScopeTable *temp = symbol_table.currentScope;
            while(temp->parentScope != nullptr){
                fout<<"\tScopeTable# "<<symbol_table.currentScope->get_scopeID()<<" deleted\n";
                symbol_table.exitScope();
                temp = symbol_table.currentScope;
            }
            fout<<"\tScopeTable# 1 deleted\n";
            break;
        }


        else if(inputWords[0] == "I"){
            if(inputCount == 3){
                check = symbol_table.insert(inputWords[1], inputWords[2]);
                if(check){
                    fout << "\tInserted  at position <" << symbol_table.currentScope->item_position.first << ", "<<symbol_table.currentScope->item_position.second <<"> of ScopeTable# "<<symbol_table.currentScope->get_scopeID()<<"\n";
                }
                else if(!check){
                    fout<<"\t'"<<inputWords[1]<<"' already exists in the current ScopeTable# "<<symbol_table.currentScope->get_scopeID()<<"\n";
                }
            }
            else
                fout<<"\tWrong number of arugments for the command I\n";
        }
        else if(inputWords[0] == "L"){
            if(inputCount == 2){
                SymbolInfo *temp = symbol_table.lookUp(inputWords[1]);
                if(temp == nullptr){
                    fout<<"\t'"<<inputWords[1]<<"' not found in any of the ScopeTables\n";
                }
                else{
                    fout <<"\t'"<<inputWords[1]<<"' found at position <" << symbol_table.findScope->item_position.first << ", "<<symbol_table.findScope->item_position.second <<"> of ScopeTable# "<<symbol_table.findScope->get_scopeID()<<"\n";
                }
            }
            else
                fout<<"\tWrong number of arugments for the command L\n";
        }

        else if(inputWords[0] == "D"){
            if(inputCount == 2){
                check = symbol_table.remove(inputWords[1]);
                if(!check){
                    fout<<"\tNot found in the current ScopeTable# "<<symbol_table.currentScope->get_scopeID()<<"\n";
                }
                else{
                    fout <<"\tDeleted '"<<inputWords[1]<<"' from position <" << symbol_table.currentScope->item_position.first << ", "<<symbol_table.currentScope->item_position.second <<"> of ScopeTable# "<<symbol_table.currentScope->get_scopeID()<<"\n";
                }
            }
            else
                fout<<"\tWrong number of arugments for the command D\n";
        }
        else if(inputWords[0] == "P"){
            if(inputCount == 2){
                if(inputWords[1] == "C"){
                    fout<<"\t";
                    fout<<symbol_table.print_currentScope();
                }
                else if(inputWords[1] == "A"){
                    fout<<symbol_table.print_allScope();
                }
                else
                    fout<<"\tInvalid argument for the command P\n";
            }
            else
                fout<<"\tWrong number of arugments for the command P\n";
        }
        else if(inputWords[0] == "S"){
            if(inputCount == 1){
                symbol_table.enterScope();
                fout<<"\tScopeTable# "<<symbol_table.currentScope->get_scopeID()<<" created\n";
            }
            else
                fout<<"\tWrong number of arugments for the command S\n";
        }
        else if(inputWords[0] == "E"){
            if(inputCount == 1){
                if(symbol_table.currentScope->get_scopeID() == "1"){
                    fout<<"\tScopeTable# 1 cannot be deleted\n";
                }
                else{
                    fout<<"\tScopeTable# "<<symbol_table.currentScope->get_scopeID()<<" deleted\n";
                    symbol_table.exitScope();
                }
            }
            else
                fout<<"\tWrong number of arugments for the command E\n";
        }

    }

    fin.close();
    fout.close();

    cout<<endl<<"\t---->Check output.txt<----"<<endl;

    return 0;
}

#include <string>
using namespace std;

#include "2005076_ScopeTable.cpp"


class SymbolTable{
private:
    int total_scope;
    int bucket_number;
    int current_scopeId;


public:
    ScopeTable *currentScope;
    ScopeTable *findScope;

    SymbolTable(int bucket){
        currentScope = nullptr;
        total_scope = 1;
        bucket_number = bucket;
        current_scopeId = 1;

        ScopeTable *newScope = new ScopeTable(bucket_number, current_scopeId);
        newScope->parentScope = currentScope;
        currentScope = newScope;
    }
    ~SymbolTable(){
        ScopeTable *temp = currentScope;
        while(temp != nullptr){
            currentScope = currentScope->parentScope;
            delete temp;
            temp = currentScope;
        }
    }

    void enterScope(){
        ScopeTable *newScope = new ScopeTable(bucket_number, currentScope->childCounter);
        currentScope->childCounter++;
        newScope->parentScope = currentScope;
        currentScope = newScope;


    }
    bool exitScope(){
        if(currentScope->parentScope == nullptr){
            return false;
        }

        currentScope = currentScope->parentScope;
        return true;
    }

    bool insert(string name, string type){
        bool temp = currentScope->insert(name, type);
        return temp;
    }
    bool remove(string name){
        bool temp = currentScope->Delete(name);
        return temp;
    }

    SymbolInfo* lookUp(string name){
        ScopeTable *temp = currentScope;
        while(temp != nullptr){
            SymbolInfo *symbol = temp->lookUp(name);
            if(symbol != nullptr){
                findScope = temp;
                return symbol;
            }
            temp = temp->parentScope;
        }

        return nullptr;
    }

    string print_currentScope(){
        return currentScope->print_scopeTable();
    }

    string print_allScope(){
        ScopeTable *temp = currentScope;
        string print("");
        while(temp != nullptr){
            print.append("\t");
            print.append(temp->print_scopeTable());
            temp = temp->parentScope;
        }
        return print;
    }

};

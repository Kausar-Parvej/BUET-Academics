#include <string>
#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

struct Parameter{
public:
    string dataType;
    string param_name;
    bool array_type;

    Parameter(const string &name, const string &type){
        param_name = name;
        dataType = type;
        this->array_type = false;
    }
    Parameter(const Parameter &obj){
        this->param_name = obj.param_name;
        this->dataType = obj.dataType;
        this->array_type = obj.array_type;
    }

};

class SymbolInfo{
private:
    string name;
    string type;

public:

    SymbolInfo *next_symbolInfo;

    string grammar_rule;
    vector<Parameter> parameter_list;
    vector<SymbolInfo*> children;
    bool isTerminal = false;
    bool isArray = false;
    string func_decType = "null";
    string type_specifier;
    int startLine = -5, endLine = -5;

    void setName(string str){
        this->name = str;
    }
    void setType(string str){
        this->type = str;
    }

    string getName(){
        return this->name;
    }
    string getType(){
        return this->type;
    }

    SymbolInfo(){
        this->name = "";
        this->type = "";
        this->next_symbolInfo = NULL;
    }

    SymbolInfo(string nam, string typ){
        this->name = nam;
        this->type = typ;
        this->next_symbolInfo = NULL;
        func_decType = "NOT_FUNCTION";
        this->type_specifier = "none";
    }

    SymbolInfo(const SymbolInfo &object){
        this->name = object.name;
        this->type = object.type;
        this->grammar_rule = object.grammar_rule;
        this->isTerminal = object.isTerminal;
        this->startLine = object.startLine; this->endLine = object.endLine;
        this->next_symbolInfo = nullptr;
        this->func_decType = object.func_decType;
        this->type_specifier = object.type_specifier;

        this->isArray = object.isArray;

        for(Parameter parameter : object.parameter_list){
            this->parameter_list.push_back(parameter);
        }
    }

    void print_inParseTree(ostream &tree_out, int tree_level){
        for(int i=0; i<tree_level; i++){
            tree_out<<" ";
        }
        tree_out<< grammar_rule;
        if(isTerminal == false){
            tree_out<<" ";
        }
        tree_out << "\t";
        tree_out<<"<Line: "<<startLine;
        if(!isTerminal) tree_out<<"-"<<endLine;
        tree_out<<">\n";
        for(SymbolInfo* childSymbol : children){
            childSymbol -> print_inParseTree(tree_out, tree_level+1);
        }
    }
    // void clearChild(){
    //     for(int i=0; i<children.size(); i++){
    //         SymbolInfo* temp = children[i];
    //         children[i] = nullptr;
    //         delete temp;
    //     }
    //     children.clear();
    // }
    ~SymbolInfo(){
        //cout<<type + " deleted in destructor\n";
        for(SymbolInfo *temp : children){
            if(temp != nullptr){
                delete temp;
            }
        }
     
        children.clear();
        parameter_list.clear();
    }

    void add_branch(SymbolInfo* child){
        //if(isTerminal) return;
        children.push_back(child);

        if(startLine == -5){
            this->startLine = child->startLine;
        }
        else{
            this->startLine = startLine < child->startLine ? startLine:child->startLine;
        }
        if(endLine == -5){
            this->endLine = child->endLine;
        }
        else{
            this->endLine = endLine > child->endLine ? endLine:child->endLine;
        }
    }

    void add_param(const Parameter &param){
        parameter_list.push_back(param);
    }

    void set_ParamList(vector<Parameter> & plist){
        this->parameter_list.clear();
        for(Parameter p : plist){
            parameter_list.push_back(p);
        }
    }
};


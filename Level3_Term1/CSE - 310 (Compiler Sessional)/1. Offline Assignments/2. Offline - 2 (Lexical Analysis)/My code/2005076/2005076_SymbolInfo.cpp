#include <string>
using namespace std;

class SymbolInfo{
private:
    string name;
    string type;

public:

    SymbolInfo *next_symbolInfo;

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
    }
    ~SymbolInfo(){
        this->next_symbolInfo = nullptr;
    }
};


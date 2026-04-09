#include <string>
using namespace std;

#include "SymbolInfo.cpp"

class ScopeTable
{
private:
    int bucket_number;
    SymbolInfo **hashTable;
    int total_symbol;
    

    unsigned long long sdbmHash(string str){
        unsigned long long hash = 0;
        int c;

        for (int i = 0; i < str.size(); i++)
        {
            c = (int)str[i];
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash % this->bucket_number;
    }


public:
    ScopeTable *parentScope;
    int scopeID;
    int childCounter;
    pair<int, int> item_position;

    ScopeTable(int size, int id){
        this->scopeID = id;
        this->bucket_number = size;
        this->total_symbol = 0;
        this->childCounter = 1;
        this->parentScope = nullptr;
        this->hashTable = new SymbolInfo *[size];
        for (int i = 0; i < size; i++)
        {
            this->hashTable[i] = nullptr;
        }
    }
    ~ScopeTable(){
        for (int i = 0; i < bucket_number; i++)
        {
            SymbolInfo *temp = hashTable[i];
            while (temp != nullptr)
            {
                SymbolInfo *temp2 = temp->next_symbolInfo;
                delete temp;
                temp = temp2;
            }
        }
        delete[] hashTable;
    }

    bool insert(string name, string type){
        int tempCounter = 2;
        int hash_index = sdbmHash(name);
        if (this->hashTable[hash_index] == nullptr)
        {
            hashTable[hash_index] = new SymbolInfo(name, type);
            total_symbol++;

            //cout << "Inserted  at position <" << hash_index+1 << ", 1> of ScopeTable# "<<get_scopeID()<<"\n";
            item_position.first = hash_index+1;
            item_position.second = 1;
            return true;
        }

        else
        {
            SymbolInfo *temp = hashTable[hash_index];
            while (temp->next_symbolInfo != nullptr)
            {
                if (temp->getName() == name)
                {
                    return false;
                }
                temp = temp->next_symbolInfo;
                tempCounter++;
            }
            if (temp == nullptr || temp->getName() == name)
            {
                return false;
            }
            temp->next_symbolInfo = new SymbolInfo(name, type);
            total_symbol++;

            //cout << "Inserted  at position <" << hash_index+1 << ", "<<tempCounter <<"> of ScopeTable# "<<get_scopeID()<<"\n";
            item_position.first = hash_index+1;
            item_position.second = tempCounter;
            return true;
        }
    }

    SymbolInfo *lookUp(string name){
        int tempCount = 1;
        int hash_index = sdbmHash(name);

        if (hashTable[hash_index] == nullptr)
        {
            return nullptr;
        }
        else
        {
            SymbolInfo *temp = hashTable[hash_index];
            while (temp != nullptr)
            {
                if (temp->getName() == name)
                {
                    //cout <<"'"<<name<<"' found at position <" << hash_index+1 << ", "<<tempCount <<"> of ScopeTable# "<<get_scopeID()<<"\n";
                    item_position.first = hash_index+1;
                    item_position.second = tempCount;
                    return temp;
                }
                temp = temp->next_symbolInfo;
                tempCount++;
            }
            return nullptr;
        }
    }

    bool Delete(string name){
        int tempCount = 2;
        int hash_index = sdbmHash(name);
        if (hashTable[hash_index] == nullptr)
            return false;
        else
        {
            SymbolInfo *temp = hashTable[hash_index];
            if (temp->getName() == name)
            {
                hashTable[hash_index] = temp->next_symbolInfo;
                delete temp;
                total_symbol--;

                //cout <<"Deleted '"<<name<<"' from position <" << hash_index+1 << ", "<<1 <<"> of ScopeTable# "<<get_scopeID()<<"\n";
                item_position.first = hash_index+1;
                item_position.second = 1;
                return true;
            }
            while (temp->next_symbolInfo != nullptr)
            {
                if (temp->next_symbolInfo->getName() == name)
                {
                    SymbolInfo *remove = temp->next_symbolInfo;
                    temp->next_symbolInfo = temp->next_symbolInfo->next_symbolInfo;
                    delete remove;
                    total_symbol--;

                    //cout <<"Deleted '"<<name<<"' from position <" << hash_index+1 << ", "<<tempCount <<"> of ScopeTable# "<<get_scopeID()<<"\n";
                    item_position.first = hash_index+1;
                    item_position.second = tempCount;
                    return true;
                }
                temp = temp->next_symbolInfo;
            }
            return false;
        }
    }

    string get_scopeID(){
        string id("");
        if(this->parentScope != nullptr){
            id.append(this->parentScope->get_scopeID());
            id.append(".");
        }
        id.append(to_string(this->scopeID));
        return id;
    }

    string print_scopeTable(){
        string print("");
        print.append("ScopeTable# ");
        print.append(this->get_scopeID());
        print.append("\n");
        for(int i=0; i<this->bucket_number; i++){
            print.append("\t");
            print.append(to_string(i+1));
            SymbolInfo *temp = hashTable[i];
            while(temp != nullptr){
                print.append(" --> (");
                print.append(temp->getName());
                print.append(",");
                print.append(temp->getType());
                print.append(")");
                temp = temp->next_symbolInfo;
            }
            print.append("\n");
        }
        return print;
    }
};

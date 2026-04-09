#include <bits/stdc++.h>
using namespace std;

struct node{
    string key;
    int value;
    node *next;
};

unsigned long hash_function1(string key, long long c, long long rem){
    long long h = 0;
    for(int i=0; i<key.length(); i++){
        h = (h*c + key[i])%rem;
    }
    return h;
}

unsigned long long hash_function2(string key, long long prime_const, long long mod) {
    unsigned long long hash_value = 0;
    unsigned long long pow = 1;

    for (char c : key) {
        hash_value = (hash_value + (c - 'a' + 1) * pow) % mod;
        pow = (pow * prime_const) % mod;
    }

    return hash_value;
}

unsigned long long aux_hash(string key, long long max_size) {
    int prime1 = 37;
    int prime2 = 43;
    
    unsigned long long hash1 = hash_function2(key, prime1, max_size);
    unsigned long long hash2 = hash_function1(key, prime2, max_size);
    
    unsigned long long final_hash = (hash1 + hash2) % max_size;
    return final_hash;
}



node *createNode(string k, int v){
    node *newNode;
    newNode->key = k;
    newNode->value = v;
    newNode->next = NULL;

    return newNode;
}

class Chaining_hash{
private:
    int max_size;
    int present_size;
    int constt = 17;
    node **hash_table;

public:
    Chaining_hash(int size){
        this->max_size = size;
        this->present_size = 0;
        this->hash_table = new node*[size];
        for(int i=0; i<size; i++){
            this->hash_table[i] = NULL;
        }
    }
    ~Chaining_hash(){
        delete[] hash_table;
    }

    void insert(string, int);
    void Delete(string);
    int find(string);
};

void Chaining_hash :: insert(string key, int value){
    int i = hash_function1(key, constt, max_size);
    if(this->hash_table[i] == NULL){
        hash_table[i] = createNode(key,value);
    }

    else{
        node* temp = hash_table[i];
        while(temp->next != NULL){
            if(temp->key == key){
                return;
            }
            temp = temp->next;
        }
        if(temp != NULL && temp->key == key){
            return;
        }
        temp->next = createNode(key, value);
    }
    present_size++;
}

void Chaining_hash :: Delete(string key){
    int index = hash_function1(key, constt, max_size);
    if(hash_table[index] == NULL) return;
    else{
        node* temp = hash_table[index];
        if(temp->key == key){
            hash_table[index] = temp->next;
            delete temp;
            present_size--;
            return;
        }
        while(temp->next != NULL){
            if(temp->next->key == key){
                node *rmv = temp->next;
                temp->next = temp->next->next;
                delete rmv;
                present_size--;
                return;
            }
            temp = temp->next;
        }
    }
}

int Chaining_hash :: find(string key){
    int index = hash_function1(key, constt, max_size);
    if(hash_table[index] == NULL){
        return NULL;
    }

    else{
        node* temp = hash_table[index];
        while(true){
            if(temp->key == key){
                return temp->value;
            }
            if(temp->next == NULL) return NULL;
            temp = temp->next;
        }
    }
}


class Probing_hash{
    int max_size;
    int present_size;

    int prob_number;
    int constant1 = 17;
    int constant2 = 29;
    string probing;
    node* hashTable;

    Probing_hash(int size, string probing_type){
        max_size = size;
        probing = probing_type;
        present_size = 0;
        prob_number = 0;
        this->hashTable = new node[size];
    }

    ~Probing_hash(){
        delete[] hashTable;
    }

    void insert(string key, int value);
    void Delete(string key);
    int find(string kay);

};

void Probing_hash :: insert(string key, int value){
    if(present_size >= max_size) 
        return;
    
    int index = 0;
    if(probing == "DOUBLE_HASH"){

    }
}



int main()
{
    int hash_size;
    cout<<"Enter Hash Size:\n";
    cin>>hash_size;

    Chaining_hash chain_hash(hash_size);

    int test = 5000;

    cout<<"size: "<<test<<" method: Separate chaining Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash2 average probes:  \n";
    cout<<"size: "<<test<<" method: Double hashing Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Double hashing Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Double hashing Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Double hashing Hash2 average probes:  \n";
    cout<<"size: "<<test<<" method: Custom probing Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Custom probing Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Custom probing Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Custom probing Hash2 average probes:  \n";

    cout<<"\n";

    test = 1000;

    cout<<"size: "<<test<<" method: Separate chaining Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash2 average probes:  \n";
    cout<<"size: "<<test<<" method: Double hashing Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Double hashing Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Double hashing Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Double hashing Hash2 average probes:  \n";
    cout<<"size: "<<test<<" method: Custom probing Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Custom probing Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Custom probing Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Custom probing Hash2 average probes:  \n";

    test = 20000;

    cout<<"\n";

    cout<<"size: "<<test<<" method: Separate chaining Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Separate chaining Hash2 average probes:  \n";
    cout<<"size: "<<test<<" method: Double hashing Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Double hashing Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Double hashing Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Double hashing Hash2 average probes:  \n";
    cout<<"size: "<<test<<" method: Custom probing Hash1 collision count: \n";
    cout<<"size: "<<test<<" method: Custom probing Hash1 average probes:  \n";
    cout<<"size: "<<test<<" method: Custom probing Hash2 collision count: \n";
    cout<<"size: "<<test<<" method: Custom probing Hash2 average probes:  \n";

    return 0;
}
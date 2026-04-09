#include <bits/stdc++.h>
using namespace std;
#include <experimental/random>
using namespace experimental;

struct node{
    string key;
    int value;
    node *next;

    node(){
        key = "";
        value = -2;
        next = NULL;
    }
    node(string k, int v){
        key = k;
        value = v;
        next = NULL;
    }
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
    long long  prime1 = 37;
    long long prime2 = 41;

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
    long long max_size;
    int present_size;
    long long constt = 31;
    node **hash_table;

public:
    int collision_count;
    int prob_count;
    int hash_f ;
    Chaining_hash(int size, int hf){
        hash_f = hf;
        this->max_size = size;
        this->present_size = 0;
        this->hash_table = new node*[size];
        for(int i=0; i<size; i++){
            this->hash_table[i] = nullptr;
        }
        collision_count = 0;
        prob_count = 0;
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
    if(this->hash_table[i] == nullptr){
        hash_table[i] = new node(key,value);
    }

    else{
        collision_count++;
        node* temp = hash_table[i];
        while(temp->next != nullptr){
            if(temp->key == key){
                return;
            }
            temp = temp->next;
        }
        if(temp != nullptr && temp->key == key){
            return;
        }
        temp->next = new node(key, value);
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
    prob_count++;
    if(hash_table[index] == nullptr){
        return -2;
    }

    else{
        node* temp = hash_table[index];
        while(true){
            if(temp->key == key){
                return temp->value;
            }
            if(temp->next == NULL) return -2;
            temp = temp->next;
            prob_count++;
        }
    }
}


class Probing_hash{
    long long max_size;
    int present_size;

    long long constant1 = 37;
    long long constant2 = 29;
    string probing;
    node* hashTable;

    public:
    int dh_collisionCount;
    int dh_probCount;
    int cp_collisionCount;
    int cp_probCount;

    Probing_hash(int size, string probing_type){
        max_size = size;
        probing = probing_type;
        present_size = 0;
        this->hashTable = new node[size];

        dh_collisionCount=0;
        dh_probCount=0;
        cp_collisionCount=0;
        cp_probCount=0;
    }

    ~Probing_hash(){
        delete[] hashTable;
    }

    unsigned long long double_hash(string key, long long i){
        return (hash_function1(key, constant2, max_size) + i*aux_hash(key, max_size))%max_size;
    }
    unsigned long long customProb_hash(string key, long long i){
        return (hash_function1(key, constant1, max_size) + constant1*i*aux_hash(key, max_size) + constant2*i*i)%max_size;
    }

    void insert(string key, int value);
    void Delete(string key);
    int find(string kay);

};

void Probing_hash :: insert(string key, int value){
    if(present_size >= max_size)
        return;

    long long index = 0;
    if(probing == "DOUBLE_HASH"){
        if(present_size >= max_size)
            return;
        long long hash_i = double_hash(key,index);
        //cout<<"hash_i = "<<hash_i<<"\n";
        while(hashTable[hash_i].key != "" && hashTable[hash_i].key != "-1" && index <= max_size){
            if(hashTable[hash_i].key == key){
                //hashTable[hash_i].value = value;
                return;
            }
            index++;
            hash_i = double_hash(key,index);
            dh_collisionCount++;
        }
        hashTable[hash_i] = node(key,value);
        present_size ++;
    }

    else if(probing == "CUSTOM_PROBING"){
        int hash_i = customProb_hash(key,index);
        while(hashTable[hash_i].key != "" && hashTable[hash_i].key != "-1"){
            if(hashTable[hash_i].key == key){
                //hashTable[hash_i].value = value;
                return;
            }
            index++;
            hash_i = customProb_hash(key,index);
            cp_collisionCount++;
        }
        hashTable[hash_i] = node(key,value);
        present_size ++;
    }
}

void Probing_hash :: Delete(string key){
    long long index = 0;
    if(probing == "DOUBLE_HASH"){
        int hash_i = double_hash(key,index);
        while(hashTable[hash_i].key != "" && index < max_size){
            if(hashTable[hash_i].key == key){
                hashTable[hash_i].key = "-1";
                hashTable[hash_i].value = -2;
                present_size--;
                return;
            }
            index++;
            hash_i = double_hash(key,index);
        }
    }

    else if(probing == "CUSTOM_PROBING"){
        int hash_i = customProb_hash(key,index);
        while(hashTable[hash_i].key != "" && index < max_size){
            if(hashTable[hash_i].key == key){
                hashTable[hash_i].key = "-1";
                hashTable[hash_i].value = -2;
                present_size--;
                return;
            }
            index++;
            hash_i = customProb_hash(key,index);
        }
    }
}

int Probing_hash :: find(string key){
    long long index = 0;
    if(probing == "DOUBLE_HASH"){
        int hash_i = double_hash(key,index);
        dh_probCount++;
        while(hashTable[hash_i].key != "" && index < max_size){
            if(hashTable[hash_i].key == key){
                return hashTable[hash_i].value;
            }
            index++;
            hash_i = double_hash(key,index);
            dh_probCount++;
        }
    }

    else if(probing == "CUSTOM_PROBING"){
        int hash_i = customProb_hash(key,index);
        cp_probCount++;
        while(hashTable[hash_i].key != "" && index < max_size){
            if(hashTable[hash_i].key == key){
                return hashTable[hash_i].value;
            }
            index++;
            hash_i = customProb_hash(key,index);
            cp_probCount++;
        }
    }
    return -2;
}




bool isPrime(long long num)
{
    if (num <= 1)  return false;
    if (num <= 3)  return true;

    if (num%2 == 0 || num%3 == 0) return false;

    for (long long i=5; i*i<=num; i=i+6)
        if (num%i == 0 || num%(i+2) == 0)
           return false;

    return true;
}
long long nextPrime(long long Num)
{
    if (Num <= 1)
        return 2;

    long long p = Num;
    bool flag = false;

    while (!flag) {
        p++;

        if (isPrime(p))
            flag = true;
    }

    return p;
}

string generate_randWord(int min_length, int max_length){
    string rand_word;
    int len = randint(min_length, max_length);
    for (int i = 0; i < len; i++){
        rand_word += (char)randint((int)'a', (int)'z');
    }
    return rand_word;
}


int main()
{
    int hash_size = 5000;
    // cout<<"Enter Hash Size:\n";
    // cin>>hash_size;
    hash_size = nextPrime(hash_size);

    vector<string> words;
    while(true){
        string temp = generate_randWord(5,10);
        words.push_back(temp);
        //cout<<temp<<"\n";

        if(words.size() >= 5000) break;
    }

    Chaining_hash chain_hash(hash_size);
    Probing_hash probHash_doubleHash(hash_size, "DOUBLE_HASH");
    Probing_hash probHash_customProb(hash_size, "CUSTOM_PROBING");

    for(int i=0; i<words.size(); i++){
       chain_hash.insert(words[i],i);
        probHash_doubleHash.insert(words[i],i);
        probHash_customProb.insert(words[i],i);
    }

    for(int i=0; i<1000; i++){
        int index = randint(0,999);
        chain_hash.find(words[index]);
        probHash_doubleHash.find(words[index]);
        probHash_customProb.find(words[index]);
    }

    cout<<"for N' = 5000\n\n";

    cout<<"size: "<<hash_size<<" method: Separate chaining Hash1 collision count: "<<chain_hash.collision_count<<"\n";
    cout<<"size: "<<hash_size<<" method: Separate chaining Hash1 average probes: "<<chain_hash.prob_count<<"\n";

    cout<<"size: "<<hash_size<<" method: Double hashing Hash1 collision count: "<<probHash_doubleHash.dh_collisionCount<<"\n";
    cout<<"size: "<<hash_size<<" method: Double hashing Hash1 average probes: "<<probHash_doubleHash.dh_probCount<<"\n ";

    cout<<"size: "<<hash_size<<" method: Custom probing Hash1 collision count: "<<probHash_customProb.cp_collisionCount<<"\n";
    cout<<"size: "<<hash_size<<" method: Custom probing Hash1 average probes:  "<<probHash_customProb.cp_probCount<<"\n";

    hash_size = 10000;
    hash_size = nextPrime(hash_size);

    vector<string> words2;
    while(true){
        string temp1 = generate_randWord(5,10);
        words2.push_back(temp1);

        if(words2.size() >= 10000) break;
    }

    Chaining_hash chain_hash2(hash_size);
    Probing_hash probHash_doubleHash2(hash_size, "DOUBLE_HASH");
    Probing_hash probHash_customProb2(hash_size, "CUSTOM_PROBING");

    for(int i=0; i<words2.size(); i++){
       chain_hash2.insert(words2[i],i);
        probHash_doubleHash2.insert(words2[i],i);
        probHash_customProb2.insert(words2[i],i);
    }

    for(int i=0; i<1000; i++){
        int index2 = randint(0, 999);
        chain_hash2.find(words2[index2]);
        probHash_doubleHash2.find(words[index2]);
        probHash_customProb2.find(words[index2]);
    }

    cout<<"for N' = 10000\n\n";

    cout<<"size: "<<hash_size<<" method: Separate chaining Hash1 collision count: "<<chain_hash2.collision_count<<"\n";
    cout<<"size: "<<hash_size<<" method: Separate chaining Hash1 average probes: "<<chain_hash2.prob_count<<"\n";

    cout<<"size: "<<hash_size<<" method: Double hashing Hash1 collision count: "<<probHash_doubleHash2.dh_collisionCount<<"\n";
    cout<<"size: "<<hash_size<<" method: Double hashing Hash1 average probes: "<<probHash_doubleHash2.dh_probCount/1000<<"\n";

    cout<<"size: "<<hash_size<<" method: Custom probing Hash1 collision count: "<<probHash_customProb2.cp_collisionCount<<"\n";
    cout<<"size: "<<hash_size<<" method: Custom probing Hash1 average probes:  "<<probHash_customProb2.cp_probCount/1000<<"\n";



    hash_size = 20000;
    hash_size = nextPrime(hash_size);

    vector<string> words3;
    while(true){
        string temp3 = generate_randWord(5,10);
        words3.push_back(temp3);
        if(words3.size() >= 20000) break;
    }

    Chaining_hash chain_hash3(hash_size);
    Probing_hash probHash_doubleHash3(hash_size, "DOUBLE_HASH");
    Probing_hash probHash_customProb3(hash_size, "CUSTOM_PROBING");

    for(int i=0; i<words.size(); i++){
       chain_hash3.insert(words3[i],i);
        probHash_doubleHash3.insert(words3[i],i);
        probHash_customProb3.insert(words3[i],i);
    }

    for(int i=0; i<1000; i++){
        int index3 = randint(0, 999);
        chain_hash3.find(words3[index3]);
        probHash_doubleHash3.find(words3[index3]);
        probHash_customProb3.find(words3[index3]);
    }

    cout<<"for N' = 20000\n\n";

    cout<<"size: "<<hash_size<<" method: Separate chaining Hash1 collision count: "<<chain_hash3.collision_count<<"\n";
    cout<<"size: "<<hash_size<<" method: Separate chaining Hash1 average probes: "<<chain_hash3.prob_count<<"\n";

    cout<<"size: "<<hash_size<<" method: Double hashing Hash1 collision count: "<<probHash_doubleHash3.dh_collisionCount<<"\n";
    cout<<"size: "<<hash_size<<" method: Double hashing Hash1 average probes: "<<probHash_doubleHash3.dh_probCount<<"\n";

    cout<<"size: "<<hash_size<<" method: Custom probing Hash1 collision count: "<<probHash_customProb3.cp_collisionCount<<"\n";
    cout<<"size: "<<hash_size<<" method: Custom probing Hash1 average probes:  "<<probHash_customProb3.cp_probCount<<"\n";


    return 0;

}

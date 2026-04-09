#include <bits/stdc++.h>
using namespace std;
#include <experimental/random>
using namespace experimental;

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


float max_load;

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
    Chaining_hash(int size){
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

    float get_laodFactor(){
        return (float) present_size/max_size;
    }

    unsigned long long double_hash(string key, long long i){
        return (hash_function1(key, constant2, max_size) + i*aux_hash(key, max_size))%max_size;
    }
    unsigned long long double_hash2(string key, long long i, long long nsize){
        return (hash_function1(key, constant2, nsize) + i*aux_hash(key,nsize))%nsize;
    }
    unsigned long long customProb_hash(string key, long long i){
        return (hash_function1(key, constant1, max_size) + constant1*i*aux_hash(key, max_size) + constant2*i*i)%max_size;
    }

    void reHash(long long s){
        node* temp;
        long long newsize = s;
        newsize = nextPrime(newsize);
        temp = new node[newsize];

        for(int i=0; i<max_size; i++){
            long in=0;
            string k = hashTable[i].key;
            long long index = double_hash2(k,in,newsize);

            while(temp[index].key != "" && temp[index].key!= "-1"){
                in++;
                index = double_hash2(k,in,newsize);
                dh_collisionCount++;
            }
            temp[index] = hashTable[i];

        }
        node* temp2 = hashTable;
        hashTable = temp;
        delete[] temp2;

        cout<<"Rehash is Called\n";

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
        if(get_laodFactor() > max_load){
            reHash(2*max_size);
        }

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
        if(get_laodFactor() < 0.3*max_load){
            reHash(max_size/2);
        }
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
    int hash_size;
    cout<<"Enter Initial Hash Size:\n";
    cin>>hash_size;

    float load_factor;
    cout<<"Enter max load factor:";
    cin>>load_factor;
    max_load = load_factor;

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
        probHash_doubleHash.insert(words[i],i);
    }
    return 0;

}

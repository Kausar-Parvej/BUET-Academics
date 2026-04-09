#include <bits/stdc++.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct node
{
    int key;
    int degree;
    node *parent;
    node *left_child;
    node *right_sibling;
};

node *new_node(int val){
    node *temp = new node;
    temp->key = val;
    temp->degree = 0;
    temp->parent = NULL;
    temp->left_child = NULL;
    temp->right_sibling = NULL;

    return temp;
}

class Binomial_heap
{

public:

    list<node *> Head_List;
    node *tempHead;
    int node_count;

    node *initialize_node()
    {
        node *newNode;
        newNode = NULL;
        return newNode;
    }

    Binomial_heap(){
        tempHead = initialize_node();
        node_count = 0;
    }

    node* node_link(node *n1, node *n2){
        if(n2->key > n1->key){
            swap(n2,n1);
        }

        n1->parent = n2;
        n1->right_sibling = n2->left_child;
        n2->left_child = n1;
        n2->degree = n2->degree + 1;

        return n2;
    }

    void reverse_sibling(node *n){
        if (n->right_sibling != NULL){
            reverse_sibling(n->right_sibling);
            (n->right_sibling)->right_sibling = n;
        }
        else{
            tempHead = n;
        }
    }

    void print_tree(node *head){
        fout << "Binomial Tree, B" << head->degree << "\n";

        queue<node*> q;
        queue<node*> q2;
        q.push(head);
        for (int i = 0; i <= head->degree; i++){

            fout << "Level " << i << " : ";
            while(!q.empty()){
                node* temp = q.front();
                q.pop();
                fout<<temp->key<<" ";

                if(temp->left_child != NULL){
                    node* temp2 = temp->left_child;
                    while(temp2 != NULL){
                        q2.push(temp2);
                        temp2 = temp2->right_sibling;
                    }
                }
            }
            while(!q2.empty()){
                q.push(q2.front());
                q2.pop();
            }
            fout<<"\n";
        }
    }

    void print_heap()
    {
        fout << "\nPrinting Binomial Heap...\n";
        auto iter = Head_List.begin();
        while (iter != Head_List.end())
        {
            print_tree(*iter);
            iter++;
        }
        fout<<"\n";
    }

    node *find_min();
    node *extract_min();
    void insert(node *);
    list<node *> union_(list<node *>, list<node*>);
    void merge();
};

list<node *> Binomial_heap :: union_(list<node *>heads1, list<node *>heads2){
    list<node *> headlist;
    auto iter1 = heads1.begin();
    auto iter2 = heads2.begin();

    while(iter1 != heads1.end() && iter2 != heads2.end()){
        if((*iter1)->degree <= (*iter2)->degree){
            headlist.push_back(*iter1);
            iter1++;
        }
        else{
            headlist.push_back(*iter2);
            iter2++;
        }
    }

    while(iter2 != heads2.end()){
        headlist.push_back(*iter2);
        iter2++;
    }

    while(iter1 != heads1.end()){
        headlist.push_back(*iter1);
        iter1++;
    }

    return headlist;
}

void Binomial_heap :: merge(){
    if(Head_List.size() <= 1) return;

    auto iter1 = Head_List.begin();
    auto iter2 = Head_List.begin();
    auto iter3 = Head_List.begin();

    if(Head_List.size() == 2){
        iter2 = iter1;
        iter2++;
        iter3 = Head_List.end();
    }
    else{
        iter2++;
        iter3++;
        iter3++;
    }
    while(iter1 != Head_List.end()){
        if(iter2 == Head_List.end()) iter1++;
        else if((*iter1)->degree < (*iter2)->degree){
            iter1++;
            iter2++;
            if(iter3 != Head_List.end()) iter3++;
        }
        else if(iter3 != Head_List.end() && (*iter1)->degree == (*iter2)->degree && (*iter2)->degree == (*iter3)->degree){
            iter1++;
            iter2++;
            iter3++;
        }
        else if(iter2 != Head_List.end() && (*iter1)->degree == (*iter2)->degree ){
            *iter1 = node_link(*iter1,*iter2);
            iter2 = Head_List.erase(iter2);
            if(iter3 != Head_List.end()) iter3++;

        }
    }
}

void Binomial_heap :: insert(node *n){
    list<node *> temp_list;
    temp_list.push_back(n);

    Head_List = union_(Head_List ,temp_list);
    merge();
}

node *Binomial_heap :: find_min(){
    auto iter = Head_List.begin();
    node* min_node;
    min_node = *iter;

    while(iter != Head_List.end()){
        if((*iter)->key < min_node->key) min_node = *iter;
        iter ++;
    }
    return min_node;
}

node* Binomial_heap ::extract_min(){
    node* min_node = find_min();
    auto iter = Head_List.begin();

    list<node *> new_headlist;
    while(iter != Head_List.end()){
        if(*iter != min_node){
            new_headlist.push_back(*iter);
        }
        iter++;
    }

    list<node *> list2;
    node* temp_node = min_node->left_child;
    node* new_tree;
    while(temp_node != NULL){
        new_tree = temp_node;
        temp_node = temp_node->right_sibling;
        new_tree -> right_sibling = NULL;
        list2.push_front(new_tree);
    }

    Head_List = union_(new_headlist,list2);
    merge();
    return min_node;
}



int main()
{
    char ch;
    int value;

    Binomial_heap myheap;

    node *temp;

    //while(fin>>ch){
    while(!fin.eof()){
        fin>>ch;

        if (ch == 'I')
        {
            fin >> value;
            temp = new_node(value);
            myheap.insert(temp);
        }
        else if (ch == 'P')
        {
            myheap.print_heap();
        }
        else if (ch == 'F')
        {
            temp = myheap.find_min();
            if (temp== NULL)
                fout << "Empty Heap\n";
            else
                fout << "Find-Min returned " << temp->key << "\n";
        }
        else if (ch == 'E')
        {
            temp = myheap.extract_min();
            if (temp == NULL)
                fout << "Empty Heap\n";
            else
                fout << "Extract-Min returned " << temp->key << "\n";
        }
        else if (ch == 'U')
        {
            Binomial_heap heap2;
            int a;
            string str;
            getline(fin, str);
            stringstream ss(str);
            string word;
            while(ss >> word){
                a = stoi(word);
                node *temp_node = new_node(a);
                heap2.insert(temp_node);
            }

            if(!heap2.Head_List.empty()){
                myheap.Head_List = myheap.union_(myheap.Head_List, heap2.Head_List);
                myheap.merge();
            }

        }

        if(fin.peek()==fin.eof())
            break;
    }

    cout<<"\n\t Check output.txt\n";

    return 0;
}

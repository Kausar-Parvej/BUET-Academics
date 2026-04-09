#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

ifstream fin("in.txt");
ofstream fout("out_avl.txt");
ofstream report("report_avl.txt");


class node
{
public:
    int element;
    node *left;
    node *right;
    int height;

    node(int item, node *lc = NULL, node *rc = NULL, int h = 1){
        element = item;
        left = lc;
        right = rc;
        height = h;
    }
};

class Bst_AVL
{
private:
    node *root;
    int nodeCount;

    void clear(node *rootNode){
        if (rootNode == NULL)
            return;

        clear(rootNode->left);
        clear(rootNode->right);
        delete rootNode;
    }
    int maxx(int x, int y){
        return (x > y) ? x:y;
    }

    int height(node* Node){
        if(Node == NULL) return 0;
        else return Node->height;
    }

    int get_skew(node* Node){
        if(Node == NULL) return 0;
        return (height(Node->left) - height(Node->right));
    }

    node* left_rotate(node* v){
        node* rv = v->right;
        node* lrv = rv->left;

        v->right = lrv;
        rv->left = v;

        v->height = maxx(height(v->left),height(v->right)) + 1;
        rv->height = maxx(height(rv->left),height(rv->right)) + 1;

        return rv;
    }

    node* right_rotate(node* v){
        node* lv = v->left;
        node* rlv = lv->right;

        v->left = rlv;
        lv->right = v;

        v->height = maxx(height(v->left),height(v->right)) + 1;
        lv->height = maxx(height(lv->left),height(lv->right)) + 1;

        return lv;
    }

    node* insert_help(node *rootNode, int item){
        if (rootNode == NULL || nodeCount == 0)
            return new node(item);

        if (item < rootNode->element){
            rootNode->left = insert_help(rootNode->left, item);
        }
        else if(item > rootNode->element){
            rootNode->right = insert_help(rootNode->right, item);
        }
        else
            return rootNode;


        rootNode->height = maxx(height(rootNode->left),height(rootNode)) + 1;

        int skew = get_skew(rootNode);
        if(skew > 1 && item < rootNode->left->element){
            return right_rotate(rootNode);
        }

        else if(skew > 1 && item > rootNode->left->element){
            rootNode->left = left_rotate(rootNode->left);
            return right_rotate(rootNode);
        }

        else if(skew < -1 && item > rootNode->right->element){
            return left_rotate(rootNode);
        }

        else if(skew < -1 && item < rootNode->right->element){
            rootNode->right = right_rotate(rootNode->right);
            return left_rotate(rootNode);
        }

        return rootNode;

    }

    node* find_help(node* rootNode, int item){
        if (rootNode == NULL || nodeCount == 0)
            return NULL;

        if (item < rootNode->element)
            return find_help(rootNode->left, item);
        else if (item > rootNode->element)
            return find_help(rootNode->right, item);

        else
            return rootNode;
    }

    node* min_node(node* rootNode){
        node* temp = rootNode;
        while(temp->left != NULL){
            temp = temp->left;
        }
        return temp;
    }

    node* delete_help(node* rootNode, int item){
        if (rootNode == NULL){
            return NULL;
        }

        if (item < rootNode->element){
            rootNode->left = delete_help(rootNode->left, item);
        }
        else if (item > rootNode->element){
            rootNode->right = delete_help(rootNode->right, item);
        }
        else {
            if( (rootNode->left == NULL) || (rootNode->right == NULL) ){
                node* temp;
                if(rootNode->left == NULL) temp = rootNode->right;
                else temp = rootNode->left;

                if(temp == NULL){
                    temp = rootNode;
                    rootNode = NULL;
                }
                else{
                    *rootNode = *temp;
                }
                free(temp);
            }

            else{
                node* temp = min_node(rootNode->right);

                rootNode->element = temp->element;
                rootNode->right = delete_help(rootNode->right,temp->element);
            }
        }

        if(rootNode == NULL) return rootNode;
        rootNode->height = maxx(height(rootNode->right), height(rootNode->left)) + 1;

        int skew = get_skew(rootNode);
        if(skew > 1 && get_skew(rootNode->left) >= 0){
            return right_rotate(rootNode);
        }

        if(skew > 1 && get_skew(rootNode->left) < 0){
            rootNode->left = left_rotate(rootNode->left);
            return right_rotate(rootNode);
        }

        if(skew < -1 && get_skew(rootNode->right) <= 0){
            return left_rotate(rootNode);
        }

       if(skew < -1 && get_skew(rootNode->right) > 0){
            rootNode->right = right_rotate(rootNode->right);
            return left_rotate(rootNode);
        }

        return rootNode;
    }

    void currentState_help(node* rootNode)
    {
        if (rootNode == NULL){
            return;
        }

        fout << rootNode->element;

        if (rootNode->left == NULL && rootNode->right == NULL)
            return;

        fout << "(";
        currentState_help(rootNode->left);
        fout<<",";
        currentState_help(rootNode->right);
        fout << ")";
    }

    void inOrder(node* rootnode)
    {
        if (rootnode == NULL)
            return;

        inOrder(rootnode->left);
        fout << rootnode->element << " ";
        inOrder(rootnode->right);
    }

public:
    Bst_AVL()
    {
        root = NULL;
        nodeCount = 0;
    }

    ~Bst_AVL()
    {
        clear(root);
    }

    void insert(int item){
        root = insert_help(root, item);
        nodeCount++;
    }

    void find(int item){
        if (find_help(root, item) == NULL)
            fout << "not found" << endl;
        else
            fout << "found" << endl;
    }

    void Delete (int item){
        node* temp = find_help(root, item);

        if (temp == NULL || nodeCount == 0)
        {
            fout << "Invalid Operation" << endl;
            return;
        }
        else{
            root = delete_help(root, item);
            nodeCount--;
            return;
        }
    }

    void traversal(){
        if (nodeCount == 0){
            fout << "Empty tree" << endl;
            return;
        }

        inOrder(root);
        fout << endl;
    }

    void current_state(){
        if (root == NULL || nodeCount == 0){
            fout << "Empty Tree" << endl;
            return;
        }
        else{
            currentState_help(root);
            fout << endl;
        }
    }
};

int main()
{
    double insert_time = 0.0;
    double delete_time = 0.0;
    double find_time = 0.0;
    double trav_time = 0.0;
    
    Bst_AVL mybst;
    char ch;
    int a;

    while (!fin.eof()){
        fin >> ch;

        if (ch == 'I')
        {
            fin >> a;

            auto begin = steady_clock::now();
            mybst.insert(a);
            auto end = steady_clock::now();
            insert_time += duration_cast<nanoseconds>(end - begin).count();

            mybst.current_state();
        }
        else if (ch == 'D')
        {
            fin>>a;

            auto begin = steady_clock::now();
            mybst.Delete(a);
            auto end = steady_clock::now();
            delete_time += duration_cast<nanoseconds>(end - begin).count();

            mybst.current_state();
        }


        else if (ch == 'F')
        {
            fin >> a;

            auto begin = steady_clock::now();
            mybst.find(a);
            auto end = steady_clock::now();
            find_time += duration_cast<nanoseconds>(end - begin).count();
        }


        else if (ch == 'T')
        {
            auto begin = steady_clock::now();
            mybst.traversal();
            auto end = steady_clock::now();
            trav_time += duration_cast<nanoseconds>(end - begin).count();
        }
        if(fin.peek()==fin.eof()){
            break;
        }
    }

    double total_time = (insert_time + delete_time + find_time + trav_time);

    report<<"\tOperation     Time(ms)\n";
    report<<"\t----------    ----------\n\n";
    report<<"\tinsert        "<<insert_time*0.000001<<"\n";
    report<<"\tdelete        "<<delete_time*0.000001<<"\n";
    report<<"\tsearch        "<<find_time*0.000001<<"\n";
    report<<"\ttraversal     "<<trav_time*0.000001<<"\n";
    report<<"\tTotal         "<<total_time*0.000001<<"\n";

    fin.close();
    fout.close();
    report.close();

    cout << endl
         << "  ---->Check out_avl.txt and report_avl.txt<----" << endl;

    return 0;
}

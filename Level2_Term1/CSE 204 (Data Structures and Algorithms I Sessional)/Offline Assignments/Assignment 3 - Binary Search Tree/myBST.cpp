#include <bits/stdc++.h>
#include <fstream>
#define output_file "output.txt"

using namespace std;

template <class data_type>
class node
{
public:
    data_type element;
    node *left;
    node *right;

    node(data_type item, node *lc = nullptr, node *rc = nullptr)
    {
        element = item;
        left = lc;
        right = rc;
    }
};

template <class data_type>
class MyBst
{
private:
    node<data_type> *root;
    int nodeCount;
    ofstream fout;

    void clear(node<data_type> *rootNode)
    {
        if (rootNode == nullptr)
            return;

        clear(rootNode->left);
        clear(rootNode->right);
        delete rootNode;
    }
    node<data_type> *for_insert(node<data_type> *rootNode, data_type item)
    {
        if (rootNode == nullptr || nodeCount == 0)
            return new node<data_type>(item);

        if (item < rootNode->element)
        {
            rootNode->left = for_insert(rootNode->left, item);
        }
        else
        {
            rootNode->right = for_insert(rootNode->right, item);
        }

        return rootNode;
    }

    node<data_type> *for_find(node<data_type> *rootNode, data_type item)
    {
        if (rootNode == nullptr || nodeCount == 0)
            return nullptr;

        if (item < rootNode->element)
            return for_find(rootNode->left, item);
        else if (item > rootNode->element)
            return for_find(rootNode->right, item);

        else
            return rootNode;
    }

    node<data_type> *for_delete(node<data_type> *rootNode, data_type item)
    {
        if (rootNode == nullptr)
        {
            return nullptr;
        }

        else if (item < rootNode->element)
        {
            rootNode->left = for_delete(rootNode->left, item);
        }
        else if (item > rootNode->element)
        {
            rootNode->right = for_delete(rootNode->right, item);
        }

        else
        {
            node<data_type> *temp = rootNode;
            /*if (rootNode->left == nullptr)
            {
                rootNode = rootNode->right;
                delete temp;
            }
            else if (rootNode->right == nullptr)
            {
                rootNode = rootNode->left;
                delete temp;
            }*/

            if (rootNode->left == nullptr && rootNode->right == nullptr)
            {
                rootNode = nullptr;
                delete temp;
                rootNode = nullptr;
            }
            else
            {
                // return nullptr;
            }
        }
        return rootNode;
    }

    void for_currentState(node<data_type> *rootNode)
    {
        if (rootNode == nullptr)
        {
            return;
        }

        fout << rootNode->element;

        if (rootNode->left == nullptr && rootNode->right == nullptr)
            return;

        fout << "(";
        for_currentState(rootNode->left);
        fout << ")";
        fout << "(";
        for_currentState(rootNode->right);
        fout << ")";
    }

    void preOrder(node<data_type> *rootnode)
    {
        if (rootnode == nullptr)
            return;

        fout << rootnode->element << " ";
        preOrder(rootnode->left);
        preOrder(rootnode->right);
    }

    void postOrder(node<data_type> *rootnode)
    {
        if (rootnode == nullptr)
            return;

        postOrder(rootnode->left);
        postOrder(rootnode->right);
        fout << rootnode->element << " ";
    }

    void inOrder(node<data_type> *rootnode)
    {
        if (rootnode == nullptr)
            return;

        inOrder(rootnode->left);
        fout << rootnode->element << " ";
        inOrder(rootnode->right);
    }

public:
    MyBst()
    {
        root = nullptr;
        nodeCount = 0;
        fout.open(output_file);
    }

    ~MyBst()
    {
        fout.close();
        clear(root);
    }

    void insert(data_type item)
    {
        root = for_insert(root, item);
        nodeCount++;
    }

    void find(data_type item)
    {
        if (for_find(root, item) == nullptr)
            fout << "False" << endl;
        else
            fout << "True" << endl;
    }

    void Delete(data_type item)
    {
        node<data_type> *temp = for_find(root, item);

        if (temp == nullptr || nodeCount == 0)
        {
            fout << "Invalid Operation" << endl;
            return;
        }
        else
        {
            if (temp->left == nullptr && temp->right == nullptr)
            {
                /*node<data_type> *temp2 = root;

                if (root->element == item)
                {
                    root = nullptr;
                    delete temp2;
                }
                while (temp2->left->element != item && temp2->right->element != item)
                {
                    if (item < temp2->element)
                        temp2 = temp2->left;
                    else
                        temp2 = temp2->right;
                }
                if (temp2->left->element == item)
                {
                    delete temp2->left;
                    temp2->left = nullptr;
                }
                else if (temp2->right->element == item)
                {
                    delete temp2->right;
                    temp2->right = nullptr;
                }*/
                for_delete(root, item);
                nodeCount--;

                current_state();
                return;
            }
            else
            {
                fout << "Invalid Operation" << endl;
                return;
            }
        }
    }

    void traversal(string order)
    {
        if (nodeCount == 0)
        {
            fout << "Empty tree" << endl;
            return;
        }

        if (order.compare("Pre") == 0)
            preOrder(root);

        else if (order.compare("Post") == 0)
        {
            postOrder(root);
        }

        else if (order.compare("In") == 0)
        {
            inOrder(root);
        }
        fout << endl;
    }

    void current_state()
    {
        if (root == nullptr || nodeCount == 0)
        {
            fout << "Empty tree" << endl;
            return;
        }
        else
        {
            for_currentState(root);
            fout << endl;
        }
    }
};

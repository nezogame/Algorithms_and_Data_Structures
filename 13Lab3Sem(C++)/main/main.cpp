// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;



struct Node {
    int key, priority;
    Node* left, * right;

    Node(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};
class Treap {
    Node* root;
    void insert(Node*& root, Node* node);
    void print(const string& prefix, const Node* node, bool isLeft);
    void remove(Node*& root, int key);
public:
    Treap() : root(nullptr) {};
    void split(Node* root, int key, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);
    void insert(int key,int priority);
    void print();
    void remove(int key);
};



    void Treap::split(Node* root, int key, Node*& left, Node*& right) {
        if (root == nullptr) {
            left = right = nullptr;
        }
        else if (key < root->key) {
            split(root->left, key, left, root->left);
            right = root;
        }
        else {
            split(root->right, key, root->right, right);
            left = root;
        }
    }
    Node* Treap::merge(Node* left, Node* right) {
        if (left == nullptr || right == nullptr) {
            return (left == nullptr) ? right : left;
        }
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        }
        right->left = merge(left, right->left);
        return right;
    }
    void Treap::insert(Node*& root, Node* node) {
        Node* left = nullptr;
        Node* right = nullptr;
        split(root, node->key, left, right);
        root = merge(merge(left, node), right);
    }
    void Treap::insert(int key, int priority) {
        Node* node = new Node(key, priority);
        insert(root, node);
    }
    void Treap::print(const string& prefix, const Node* node, bool isLeft)
    {
        if (node != nullptr)
        {
            cout << prefix;
            cout << (isLeft ? "|--" : "L--");
            cout << node->key<<":"<< node->priority << endl;
           
            print(prefix + (isLeft ? "|   " : "    "), node->left, true);
            print(prefix + (isLeft ? "|   " : "    "), node->right, false);

        }
    }
    void Treap::print()
    {
        if (root == nullptr) {
            cout << "Tree is empty!!!\n";
        }
        else {
            print("", root, false);
        }
    }
    void Treap::remove(Node*& root, int key) {
        Node* left = nullptr;
        Node* right = nullptr;
        split(root, key, left, right);
        Node* node = nullptr;
        split(left, key - 1, left, node);
        node = merge(node->left, node->right);
        root = merge(merge(left, node), right);
    }
    void Treap::remove(int key) {
        remove(root, key);
    }
    bool Interface(Treap& treap) {

        int action, key, priority, value;
        std::cout << "Choose your action (from 1 to 3).\n"
            "1 is add elemet to treap\n"
            "2 is remove elemet from treap\n"
            "3 is print out treap\n"
            "0 if you want to finish the program " << endl;

        cin >> action;
        cout << endl;
        switch (action) {
        case 1:

            cout << "Enter key: " << endl;
            cin >> key;
            cout << "Enter priority: " << endl;
            cin >> priority;
            treap.insert(key, priority);
            break;
        case 2:
            std::cout << "Input KEY: " << endl;
            cin >> key;
            treap.remove(key);
            break;
        case 3:
            treap.print();
            break;
        case 0:
            std::cout << "Thanks for using, bye bye";
            return false;
            break;
        default:
            cout << "Wrong number!!!";
        }
        cout << "\n\n";
        return true;
    }
int main()
{
    bool result;
    Treap question;
    do {
        result = Interface(question);
    } while (result != false);
    
    /*question.insert(15);
    question.insert(15);*/

}



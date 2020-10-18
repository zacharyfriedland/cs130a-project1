// tst.h
// Zachary Friedland
// Ternary Search Tree (TST) header file

#ifndef TST_H
#define TST_H

#include <string>
#include <utility>
using namespace std;

class TST {
    public:
        TST();          // constructor
        ~TST();         // destructor
        bool insert(string word);
        string lookup(string word);
        bool remove(string word);
        void range_search(string phrase);
        void printInOrder();

    private:
        struct Node {
            pair<string, int> kleft;    // uses kleft.first and kleft.second;
            pair<string, int> kright;

            Node* left;
            Node* mid;
            Node* right;
            Node* parent;

            Node(pair<string,int> val1 = make_pair("", 0), pair<string,int> val2 = make_pair("", 0)) :
                         kleft(val1), kright(val2), left(nullptr), mid(nullptr), right(nullptr), parent(nullptr) { }
        };

        Node* root;                     // one root per TST
        void clear(Node* n);            // for destructor
        bool insert(string word, Node* n);  // overloading
        int lookup(string word, Node* n);
        void printInOrder(Node* n);
        void printRange(string target1, string target2, Node* n);
        Node* getNode(string word, Node* n);
        Node* getPredecessorNode(string word);
        Node* getSuccessorNode(string word);
        void reorderTree(Node* n);
};

#endif
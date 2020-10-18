// tst.cpp
// Implements TST class
#include "tst.h"
#include <string>
#include <iostream>
#include <sstream> 

TST::TST() : root(nullptr){ }   

TST::~TST(){
    // cout << "destructor" << endl;
    clear(root);
    root = nullptr;
}   

void TST::clear(Node* n){
    if(n) {
        clear(n->left);
        clear(n->mid);
        clear(n->right);
        delete n;
    }
}  

bool TST::insert(string word){
    if(!root){
        root = new Node(make_pair(word, 1), make_pair("", 0));
        return true;
    }
    return insert(word, root);
}

string TST::lookup(string word){
    if(!root){
        return word + " not found";
    }
    int result = lookup(word, root);
    if(result > 0){
        return word + " found, count = " + to_string(result);
    }
    else{
        return word + " not found";
    }
}

bool TST::remove(string word){
    
}

void TST::range_search(string phrase){
    stringstream input(phrase);
    string to;
    string target1;
    string target2;
    input >> target1;
    input >> to;
    input >> target2;

    printRange(target1, target2, root);
} 

void TST::printRange(string target1, string target2, Node* n){
    if(n){
        printRange(target1, target2, n->left);
        if(n->kleft.second > 0 && n->kleft.first >= target1 && n->kleft.first <= target2)
            std::cout << n->kleft.first << endl;
        printRange(target1, target2, n->mid);
        if(n->kright.second > 0 && n->kright.first >= target1 && n->kright.first <= target2)
            std::cout << n->kright.first << endl;
        printRange(target1, target2, n->right);
    }
}

bool TST::insert(string word, Node* n){
    if(word == n->kleft.first){
        n->kleft.second++;
        return true;
    }
    else if(word == n->kright.first){
        n->kright.second++;
        return true;
    }

    if(n->kleft.second == 0 && word < n->kright.first){
        n->kleft.first = word;
        n->kleft.second = 1;
        return true;
    }
    else if(n->kleft.second == 0 && word > n->kright.first){
        n->kleft.first = n->kright.first;
        n->kleft.second = n->kright.second;
        n->kright.first = word;
        n->kright.second = 1;
    }
    else if(n->kright.second == 0 && word > n->kleft.first){
        n->kright.first = word;
        n->kright.second = 1;
        return true;
    }
    else if(n->kright.second == 0 && word < n->kleft.first){
        n->kright.first = n->kleft.first;
        n->kright.second = n->kleft.second;
        n->kleft.first = word;
        n->kleft.second = 1;
    }

    if(word < n->kleft.first){
        if(n->left){
            return insert(word, n->left);
        }
        else{
            n->left = new Node(make_pair(word, 1), make_pair("", 0));
            n->left->parent = n;
            return true;
        }
    }
    else if(word > n->kleft.first && word < n->kright.first){
        if(n->mid){
            return insert(word, n->mid);
        }
        else{
            n->mid = new Node(make_pair(word, 1), make_pair("", 0));
            n->mid->parent = n;
            return true;
        }
    }
    else if(word > n->kright.first){
        if(n->right){
            return insert(word, n->right);
        }
        else{
            n->right = new Node(make_pair(word, 1), make_pair("", 0));
            n->right->parent = n;
            return true;
        }
    }
    return false;
}

int TST::lookup(string word, Node* n){
    if(!n){
        return 0;
    }
    if(n){
        if(n->kleft.first == word){
            return n->kleft.second;
        }
        if(n->kright.first == word){
            return n->kright.second;
        }
        else if(word < n->kleft.first){
            return lookup(word, n->left);
        }
        else if(word > n->kleft.first && word < n->kright.first){
            return lookup(word, n->mid);
        }
        else if(word > n->kright.first){
            return lookup(word, n->right);
        }
    }
    return 0;
}

void TST::printInOrder(){
    printInOrder(root);
}

void TST::printInOrder(Node* n){
    if(n){
        printInOrder(n->left);
        if(n->kleft.second > 0)
            std::cout << n->kleft.first << " " << n->kleft.second << endl;
        printInOrder(n->mid);
        if(n->kright.second > 0)
            std::cout << n->kright.first << " " << n->kright.second << endl;
        printInOrder(n->right);
    }
}

// struct Node {
//     pair<string, int> word1;    // uses word1.first and word1.second;
//     pair<string, int> word2;

//     Node* left;
//     Node* mid;
//     Node* right;

//     Node(pair<string,int> val1 = make_pair("", 0), pair<string,int> val2 = make_pair("", 0)) :
//                     word1(val1), word2(val2) { }
// };
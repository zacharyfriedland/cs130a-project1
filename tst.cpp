// tst.cpp
// Zachary Friedland
// Implements TST class
#include "tst.h"
#include <string>
#include <iostream>
#include <sstream> 

TST::TST() : root(nullptr){ }   

TST::~TST(){
    clear(root);
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
        std::cout << word << " inserted, new count = " << root->kleft.second << endl;
        return true;
    }
    return insert(word, root);
}

bool TST::insert(string word, Node* n){
    // update count if word exists
    if(word == n->kleft.first){
        n->kleft.second++;
        std::cout << word << " inserted, new count = " << n->kleft.second << endl;
        return true;
    }
    else if(word == n->kright.first){
        n->kright.second++;
        std::cout << word << " inserted, new count = " << n->kright.second << endl;
        return true;
    }
    
    else if(n->kright.second == 0 && word > n->kleft.first){
        n->kright.first = word;
        n->kright.second = 1;
        std::cout << word << " inserted, new count = " << n->kright.second << endl;
        return true;
    }
    else if(n->kright.second == 0 && word < n->kleft.first){
        n->kright.first = n->kleft.first;
        n->kright.second = n->kleft.second;
        n->kleft.first = word;
        n->kleft.second = 1;
        std::cout << word << " inserted, new count = " << n->kleft.second << endl;
        return true;
    }

    if(word < n->kleft.first){
        if(n->left){
            return insert(word, n->left);
        }
        else{
            n->left = new Node(make_pair(word, 1), make_pair("", 0));
            n->left->parent = n;
            n = n->left;
            std::cout << word << " inserted, new count = " << n->kleft.second << endl;
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
            n = n->mid;
            std::cout << word << " inserted, new count = " << n->kleft.second << endl;
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
            n = n->right;
            std::cout << word << " inserted, new count = " << n->kleft.second << endl;
            return true;
        }
    }
    return false;
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

TST::Node* TST::getNode(string word, Node* n){
    if(n){
        if(n->kleft.first == word || n->kright.first == word){
            return n;
        }
        else if(word < n->kleft.first){
            return getNode(word, n->left);
        }
        else if(word > n->kleft.first && word < n->kright.first){
            return getNode(word, n->mid);
        }
        else if(word > n->kright.first){
            return getNode(word, n->right);
        }
    }
    return 0;
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

void TST::printInOrder(){
    printInOrder(root);
}

void TST::printInOrder(Node* n){
    if(n){
        printInOrder(n->left);
        if(n->kleft.second > 0){
            std::cout << n->kleft.first << " " << n->kleft.second << endl;
        }
        printInOrder(n->mid);
        if(n->kright.second > 0)
            std::cout << n->kright.first << " " << n->kright.second << endl;
        printInOrder(n->right);
    }
}

TST::Node* TST::getPredecessorNode(string word){
    Node* n = getNode(word, root);
    if(!n){
        return 0;
    }
    // if n has a left child
    if(n->left){
        n = n->left;
        while(n->right)
            n = n->right;
        return n;
    }
    // if n has a middle 
    else if(n->mid){
        n = n->mid;
        while(n->left)
            n = n->left;
        return n;
    }
    // worst case n has a right
    // if(n->right)
    else{
        n = n->right;
        while(n->left)
            n = n->left;
        return n;
    }
    return 0;
}

TST::Node* TST::getSuccessorNode(string word){
    Node* n = getNode(word, root);
    if(!n){
        return 0;
    }
    // if n has a right child
    if(n->right){
        n = n->right;
        while(n->left)
            n = n->left;
        return n;
    }
    // if n has a middle 
    else if(n->mid){
        n = n->mid;
        while(n->right)
            n = n->right;
        return n;
    }
    // worst case n has only a left
    // if(n->left)
    else{
        n = n->left;
        while(n->right)
            n = n->right;
        return n;
    }
    return 0;
}

void TST::reorderTree(Node* n){
    // if root is empty now
    if(n == root && n->kleft.second == 0 && n->kright.second == 0){
        root = nullptr;
        delete n;
    }
    if(n){
        // recurse through left subtree
        reorderTree(n->left);
        // if there are no keys left
        if(n->kleft.second == 0 && n->kright.second == 0){
            delete n;
        }
        // if there is a kright with no kleft
        else if(n->kleft.second == 0 && n->kright.second > 0){
            n->kleft.first = n->kright.first;
            n->kleft.second = n->kright.second;
            n->kright.first = "";
            n->kright.second = 0;
        }
        reorderTree(n->mid);
        reorderTree(n->right);
    }
}

bool TST::remove(string word){
    // word doesn't exist
    if(!getNode(word, root)){
        return true;
    }
    // word exists and to be deleted
    if(getNode(word, root)){
        Node* target = getNode(word, root);
        // word is in kleft
        if(word == target->kleft.first){
            // decrement count if > 1
            if(target->kleft.second > 1){
                target->kleft.second--;
                cout << word << " deleted, new count = " << target->kleft.second << endl;
                return true;
            }
            else if(target->kleft.second == 1){
                // no children
                if(!target->left && !target->mid && !target->right){
                    // root case
                    if(root == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            root = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kleft to be deleted with kright present
                        target->kleft.first = target->kright.first;
                        target->kleft.second = target->kright.second;
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                    // left child
                    else if(target->parent->left == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            target->parent->left = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kleft to be deleted with kright present
                        target->kleft.first = target->kright.first;
                        target->kleft.second = target->kright.second;
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                    // mid child
                    else if(target->parent->mid == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            target->parent->mid = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kleft to be deleted with kright present
                        target->kleft.first = target->kright.first;
                        target->kleft.second = target->kright.second;
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                        
                    }
                    // right child
                    else if(target->parent->right == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            target->parent->right = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kleft to be deleted with kright present
                        target->kleft.first = target->kright.first;
                        target->kleft.second = target->kright.second;
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                }
                // if children present
                else{
                    // get next smallest word
                    Node* tmp = getPredecessorNode(word);
                    // left subtree
                    // if predecessor node has a kright
                    if(tmp->kright.second > 0){
                        if(tmp->kright.first < target->kleft.first){
                            target->kleft.first = tmp->kright.first;
                            target->kleft.second = tmp->kright.second;
                            tmp->kright.first = "";
                            tmp->kright.second = 0;
                            std::cout << word << " deleted" << endl;
                            reorderTree(root);
                            return true;
                        }
                    }
                    else if(tmp->kright.second < 1){
                        if(tmp->kleft.first < target->kleft.first){
                                target->kleft.first = tmp->kleft.first;
                                target->kleft.second = tmp->kleft.second;
                                tmp->kright.first = "";
                                tmp->kright.second = 0;
                                std::cout << word << " deleted" << endl;
                                reorderTree(root);
                                return true;
                        }
                    }
                    // mid subtree
                    else if(tmp->kleft.first > target->kleft.first && tmp->kleft.first < target->kright.first){
                        target->kleft.first = tmp->kleft.first;
                        target->kleft.second = tmp->kleft.second;
                        tmp->kleft.first = "";
                        tmp->kleft.second = 0;
                        std::cout << word << " deleted" << endl;
                        reorderTree(root);
                        return true;
    
                    }
                    // if only right subtree
                    // if(tmp->kleft.first > target->kright.first)
                    else{
                        target->kleft.first = target->kright.first;
                        target->kleft.second = target->kright.second;
                        target->kright.first = tmp->kleft.first;
                        target->kright.second = tmp->kleft.second;
                        tmp->kleft.first = "";
                        tmp->kleft.second = 0;
                        std::cout << word << " deleted" << endl;
                        reorderTree(root);
                        return true;
                    }
                }
                
            }
        }
        else if(word == target->kright.first){
            // decrement count if > 1
            if(target->kright.second > 1){
                target->kright.second--;
                std::cout << word << " deleted, new count = " << target->kright.second << endl;
                return true;
            }
            else if(target->kright.second == 1){
                // no children
                if(!target->left && !target->mid && !target->right){
                    // root case
                    if(root == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            root = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kright to be deleted with kleft present
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                    // left child
                    else if(target->parent->left == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            target->parent->left = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kright to be deleted with kleft present
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                    // mid child
                    else if(target->parent->mid == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            target->parent->mid = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kright to be deleted with kleft present
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                    // right child
                    else if(target->parent->right == target){
                        // either kleft or kright has nothing
                        if(target->kleft.second == 0 || target->kright.second == 0){
                            target->parent->right = nullptr;
                            delete target;
                            std::cout << word << " deleted" << endl;
                            return true;
                        }
                        // kright to be deleted with kleft present
                        target->kright.first = "";
                        target->kright.second = 0;
                        std::cout << word << " deleted" << endl;
                        return true;
                    }
                }
                // if children present
                else{
                    // get next smallest word
                    Node* tmp = getSuccessorNode(word);
                    // right subtree
                    if(tmp->kleft.first > target->kright.first){
                        target->kright.first = tmp->kleft.first;
                        target->kright.second = tmp->kleft.second;
                        tmp->kleft.first = "";
                        tmp->kleft.second = 0;
                        std::cout << word << " deleted" << endl;
                        reorderTree(root);
                        return true;
                    }
                    // two part
                    else if(tmp->kright.second > 0){
                        // mid subtree
                        if(tmp->kright.first < target->kright.first && tmp->kright.first > target->kleft.first){
                            target->kright.first = tmp->kright.first;
                            target->kright.second = tmp->kright.second;
                            tmp->kright.first = "";
                            tmp->kright.second = 0;
                            std::cout << word << " deleted" << endl;
                            reorderTree(root);
                            return true;
                        }
                        // left subtree
                        else if(tmp->kright.first < target->kleft.first){
                            target->kright.first = target->kleft.first;
                            target->kright.second = target->kleft.second;
                            target->kleft.first = tmp->kright.first;
                            target->kleft.second = tmp->kright.second;
                            tmp->kright.first = "";
                            tmp->kright.second = 0;
                            std::cout << word << " deleted" << endl;
                            reorderTree(root);
                            return true;
                        }
                    }
                    // two part
                    else if(tmp->kright.second < 1){
                        // mid subtree
                        if(tmp->kleft.first < target->kright.first && tmp->kleft.first > target->kleft.first){
                            target->kright.first = tmp->kleft.first;
                            target->kright.second = tmp->kleft.second;
                            tmp->kleft.first = "";
                            tmp->kleft.second = 0;
                            std::cout << word << " deleted" << endl;
                            reorderTree(root);
                            return true;
                        }
                        else if(tmp->kleft.first < target->kleft.first){
                            target->kright.first = target->kleft.first;
                            target->kright.second = target->kleft.second;
                            target->kleft.first = tmp->kleft.first;
                            target->kleft.second = tmp->kleft.second;
                            tmp->kleft.first = "";
                            tmp->kleft.second = 0;
                            std::cout << word << " deleted" << endl;
                            reorderTree(root);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
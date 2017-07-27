//
//  main.cpp
//  4.6
//
//  Created by Drew Alam on 2017-07-27.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

class Node{
public:
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int nodeHeight = -1;
    bool isBalancedNode = false;
    
    Node(int key, Node *parent): key{key}, parent{parent}{}
    
    ~Node(){
        delete left;
        delete right;
    }
    
    void printInorder(){
        if (left){
            left->printInorder();
        }
        cout << key << endl;
        if (right){
            right->printInorder();
        }
    }
};
struct Tree{
    Node *rootNode = nullptr;
    int a = 0;
    int b = 1;
    
    Node *findNode(Node *node, int key){
        if (not node){
            return nullptr;
        }
        if (node->key < key){
            return findNode(node->right, key);
        } else if (node->key > key) {
            return findNode(node->left, key);
        }
        return node;
    }
    
    Node *find(int key){
        return findNode(rootNode, key);
    }
    
    Node *insertNode(Node *root, int key, Node *parent){
        if (not root){
            return new Node(key,parent);
        }
        
        if (root->key < key){
            root->right = insertNode(root->right, key, root);
        } else if (root->key > key) {
            root->left = insertNode(root->left, key , root);
        }
        return root;
    }
    
    Node *insertNodeRandom(Node *root, int key, Node *parent){
        if (not root){
            return new Node(key, parent);
        }
        
        if (root->key > key){
            if (a % 2 == 0){
                root->right = insertNode(root->right, key, root);
            } else {
                root->right = insertNode(root->left, key, root);
            }
            ++a;
        } else if (root->key < key) {
            if (b % 2 == 0){
                root->left = insertNode(root->left, key, root);
            } else {
                root->left = insertNode(root->right, key, root);
            }
            ++b;
        }
        return root;
    }
    
    void insert(int key){
        if (not rootNode){
            rootNode = new Node(key, nullptr);
        } else {
            insertNode(rootNode, key, rootNode);
        }
    }
    
    void insertRandom(int key){
        if (not rootNode){
            rootNode = new Node(key , nullptr);
        } else {
            insertNodeRandom(rootNode, key, rootNode);
        }
    }
    
    void inorderTraversal(){
        if (rootNode){
            rootNode->printInorder();
        }
    }
};

void binaryInsert(vector<int> &sortedArray, Tree *tree, int start, int end){
    if (start == end){
        tree->insert(sortedArray[start]);
        return;
    } else if (end < start){
        return;
    }
    
    int middle = (start + end) / 2;
    tree->insert(sortedArray[middle]);
    //recurse on left subarray
    binaryInsert(sortedArray, tree, start, middle  - 1);
    //recure on right subArray
    binaryInsert(sortedArray, tree, middle + 1, end);
    
}

void binaryInsertRandom(vector<int> &sortedArray, Tree *tree, int start, int end){
    if (start == end){
        tree->insert(sortedArray[start]);
        return;
    } else if (end < start){
        return;
    }
    
    int middle = (start + end) / 2;
    tree->insertRandom(sortedArray[middle]);
    //recurse on left subarray
    binaryInsertRandom(sortedArray, tree, start, middle  - 1);
    //recure on right subArray
    binaryInsertRandom(sortedArray, tree, middle + 1, end);
    
}

Node *findSuccessor(Node *node){
    if (node->right){
        Node *temp = node->right;
        while(temp){
            temp = temp->left;
        }
        return temp;
    }
    if (node->parent->left == node){
        return node->parent;
    } else { //it is on right side of parent
        //keep going up the parent list un
        Node *parent = node->parent;
        Node *current = node;
        while (parent->right == current){
            current = parent;
            parent = parent->parent;
        }
        return parent;
        
    }
}



int main(int argc, const char * argv[]) {
    cout << "How many numbers in increasing order would you like to enter" << endl;
    int numberOfNums;
    cin >> numberOfNums;
    
    vector<int> sortedNumbers;
    int temp = 0;
    cout << "Enter sorted nubmers one by one" << endl;
    for (int i = 0; i < numberOfNums; ++i){
        cin >> temp;
        sortedNumbers.push_back(temp);
    }
    Tree *tree = new Tree();
    binaryInsert(sortedNumbers, tree, 0, static_cast<int>(sortedNumbers.size()) -1);
    
    cout << "What number would you like to find? " << endl;
    int numToFind;
    cin >> numToFind;
    
    Node * tempNode = tree->find(numToFind);
    cout << "The parent's value is: " << findSuccessor(tempNode)->key << endl;
}

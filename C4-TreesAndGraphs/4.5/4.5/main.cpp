//
//  main.cpp
//  4.5
//
//  Created by Drew Alam on 2017-07-26.
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
    int nodeHeight = -1;
    bool isBalancedNode = false;
    
    Node(int key): key{key}{}
    
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
    
    Node *insertNode(Node *root, int key){
        if (not root){
            return new Node(key);
        }
        
        if (root->key < key){
            root->right = insertNode(root->right, key);
        } else if (root->key > key) {
            root->left = insertNode(root->left, key);
        }
        return root;
    }
    
    Node *insertNodeRandom(Node *root, int key){
        if (not root){
            return new Node(key);
        }
        
        if (root->key > key){
            if (a % 2 == 0){
                root->right = insertNode(root->right, key);
            } else {
                root->right = insertNode(root->left, key);
            }
            ++a;
        } else if (root->key < key) {
            if (b % 2 == 0){
                root->left = insertNode(root->left, key);
            } else {
                root->left = insertNode(root->right, key);
            }
            ++b;
        }
        return root;
    }
    
    void insert(int key){
        if (not rootNode){
            rootNode = new Node(key);
        } else {
            insertNode(rootNode, key);
        }
    }
    
    void insertRandom(int key){
        if (not rootNode){
            rootNode = new Node(key);
        } else {
            insertNodeRandom(rootNode, key);
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

bool checkNodeIsInRange(Node * node, int min, int max){
    if (not node){
        return true;
    }
    
    if ((node->key < max || max == -1) && node->key >= min){
        return checkNodeIsInRange(node->left, min, node->key) && checkNodeIsInRange(node->right, node->key, max);
    }
    return false;
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
    binaryInsertRandom(sortedNumbers, tree, 0, static_cast<int>(sortedNumbers.size()) -1);
    cout << checkNodeIsInRange(tree->rootNode, -1, -1) << endl;
    cout << "Hello" << endl;
}

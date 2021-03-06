//
//  main.cpp
//  4.3
//
//  Created by Drew Alam on 2017-07-25.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Node{
public:
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    
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
    
    void insert(int key){
        if (not rootNode){
            rootNode = new Node(key);
        } else {
            insertNode(rootNode, key);
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
void binaryDepth(Node *node, vector<deque<Node *>*> &depthNodes, int depth){
    if (not node){
        return;
    }
    if (depthNodes.size() < (depth + 1)){
        deque<Node *> *newDepth = new deque<Node *>;
        depthNodes.push_back(newDepth);
    }
    depthNodes[depth]->push_back(node);
    binaryDepth(node->left, depthNodes, depth+1);
    binaryDepth(node->right, depthNodes, depth+1);
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
    
    vector<deque<Node*> *> depthNodes;
    binaryDepth(tree->rootNode, depthNodes, 0);
    int i = 0;
    for (auto iterator = depthNodes.begin(); iterator != depthNodes.end(); ++iterator){
        cout << "Depth " << i << ": " ;
        for (auto it = (*iterator)->begin(); it != (*iterator)->end(); ++it){
            cout << (*it)->key << " ";
        }
        cout << endl;
        ++i;
    }
    
    delete tree;
}

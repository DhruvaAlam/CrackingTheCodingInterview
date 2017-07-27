//
//  main.cpp
//  4.4
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
int height(Node *node){
    if (node->nodeHeight != -1){
        return node->nodeHeight;
    }
    if (not node->left && not node->right){
        node->nodeHeight = 1;
    } else if (not node->left){
        node->nodeHeight = 1 + height(node->right);
    } else if (not node->right){
        node->nodeHeight = 1 + height(node->left);
    } else {
        node->nodeHeight = 1 + max(height(node->left), height(node->right));
    }
    return node->nodeHeight;
}

bool isBalanced(Node *node){
    int leftHeight = 0;
    int rightHeight = 0;
    bool isLeftBalanced = false;
    bool isRightBalanced = false;
    if (node->left){
        leftHeight = height(node->left);
        isLeftBalanced = isBalanced(node->left);
    }
    if (node->right){
        rightHeight = height(node->right);
        isRightBalanced = isBalanced(node->right);
    }
    int diff = abs(leftHeight - rightHeight);
    if (diff > 1){
        node->isBalancedNode = false;
        return false;
    } else if ((isLeftBalanced && isRightBalanced) || (not node->left && not node->right)){
        node->isBalancedNode = true;
        return true;
    }
    node->isBalancedNode = false;
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
    binaryInsert(sortedNumbers, tree, 0, static_cast<int>(sortedNumbers.size()) -1);
    height(tree->rootNode);
    cout << isBalanced(tree->rootNode) << endl;;
    
    
}

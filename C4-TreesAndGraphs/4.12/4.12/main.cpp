//
//  main.cpp
//  4.12
//
//  Created by Drew Alam on 2017-08-07.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <vector>

#include <deque>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
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
    unordered_map<int, Node *> nodeTable;
    
    Node *insertNode(Node *root, int key){
        if (not root){
            nodeTable[key] = new Node(key);
            return nodeTable[key];
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
            nodeTable[key] = rootNode;
        } else {
            insertNode(rootNode, key);
        }
    }
    
    void inorderTraversal(){
        if (rootNode){
            rootNode->printInorder();
        }
    }
    
    void prettyPrint(Node* p, int indent)
    {
        if(p != NULL) {
            if(p->right) {
                prettyPrint(p->right, indent+4);
            }
            if (indent) {
                cout << setw(indent) << ' ';
            }
            if (p->right) cout<<" /\n" << std::setw(indent) << ' ';
            cout<< p->key << "\n ";
            if(p->left) {
                cout << setw(indent) << ' ' <<" \\\n";
                prettyPrint(p->left, indent+4);
            }
        }
    }
    
    void prettyPrinter(){
        prettyPrint(rootNode, 2);
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
void recursivePathWithSum(Node *node, int sum, int &count, int sumSoFar){
    if (not node){
        return;
    }
    int newSumSoFar = sumSoFar + node->key;
    if (newSumSoFar == sum){
        ++count;
    }
    recursivePathWithSum(node->left, sum, count, newSumSoFar); //continue path left
    recursivePathWithSum(node->right, sum, count, newSumSoFar); //continue right
    recursivePathWithSum(node, sum, count, 0); //restart at this node
    
}

int pathsWithSum(Node *rootNode, int sum){
    int count = 0;
    recursivePathWithSum(rootNode, sum, count, 0);
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
    
    tree->prettyPrinter();
}

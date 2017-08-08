//
//  main.cpp
//  4.8
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

int recurseThroughTree(Node *a, Node *b, Node *currentNode, Node *&answer){
    if (not currentNode){
        return 0;
    }
    if (currentNode->key == a->key || currentNode->key == b->key){
        return 1;
    }
    int left = 0;
    int right = 0;
    left = recurseThroughTree(a, b, currentNode->left, answer);
    right = recurseThroughTree(a, b, currentNode->right, answer);
    if (left == 3 || right == 3){
        //3 indicates we already found it, break early.
        return 3;
    }
    
    if (left == 1 && right == 1){
        cout << currentNode->key << endl;
        answer = currentNode;
        return 3;
    }
    if (left == 1 || right == 1){
        return 1;
    }
    return 0;
}

Node *getCommonAncestor(Node *a, Node *b, Node *treeRootNode){
    Node * answer = nullptr;
    recurseThroughTree(a, b, treeRootNode, answer);
    return answer;
    
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
    
    cout << "Enter the two numbers who you would like to find the first common ancestor of: " << endl;
    int a;
    int b;
    cin >> a;
    cin >> b;
    Node *aNode = tree->nodeTable[a];
    Node *bNode = tree->nodeTable[b];
    
    Node *ancestor = getCommonAncestor(aNode, bNode, tree->rootNode);
    cout << "Ancestor " << ancestor->key << endl;
    
}

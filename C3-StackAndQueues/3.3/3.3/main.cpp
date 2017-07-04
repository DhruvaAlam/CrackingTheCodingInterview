//
//  main.cpp
//  3.3
//
//  Created by Drew Alam on 2017-07-03.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <deque>
#include <string>
using namespace std;

class Node{
public:
    int value;
    Node *lowestNodeInStackBelow;
    
    Node (int value, Node *lowest): value{value}, lowestNodeInStackBelow{lowest}{}
    
    void print(){
        cout << value << " ";
    }
    
    void pop(){
        cout << "Popping off the the node with value:" ;
        print();
        cout << endl;
    }
};

void printStack (deque <Node *> &stack){
    for (deque<Node *>::iterator it = stack.begin(); it != stack.end(); ++it){
        (*it)->print();
    }
    cout << endl;
    /*
     for (auto node:stack){
     (*node).print();
     }
     cout << endl;
     for (const auto &node:stack){
     node->print();
     }
     */
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

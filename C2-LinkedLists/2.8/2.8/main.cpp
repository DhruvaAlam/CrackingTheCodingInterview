//
//  main.cpp
//  2.8
//
//  Created by Drew Alam on 2017-06-18.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <unordered_set>
using namespace std;

class Node{
public:
    int value;
    Node *next;
    Node (int value): value{value}, next{nullptr}{
        
    }
    ~Node(){
        delete next;
    }
    void print(){
        cout << value << " ";
        if (next){
            next->print();
        } else{
            cout << endl;
        }
    }
};

void print(Node *linkedList){
    cout << "Printing number" << endl;
    if (linkedList){
        linkedList->print();
    } else {
        cout << "list is empty" << endl;
    }
}


int main(int argc, const char * argv[]) {
    Node *node1 = new Node(1);
    Node *node2 = new Node(2);
    Node *node3 = new Node(3);
    Node *node4 = new Node(4);
    Node *node5 = new Node(5);
    
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node3;
    
    
    
    Node* list = node1;
    unordered_set<Node *> nodes;
    //iterate through linked list and store addressed of each node in the unordered set
    while (list){
        if (nodes.find(list) == nodes.end()){
            //store address in hash table
            nodes.emplace(list);
        } else {
            cout << list->value << " is the node that starts the loop" << endl;
            break; 
        }
        list = list->next;
    }
    
}

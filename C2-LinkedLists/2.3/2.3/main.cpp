//
//  main.cpp
//  2.3
//
//  Created by Drew Alam on 2017-06-17.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
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
};
int main(int argc, const char * argv[]) {
    int num;
    Node *front = nullptr;
    cout << "Enter in values one at a time" << endl;
    while (cin >> num){
        Node * temp = new Node(num);
        if (front){
            temp->next = front;
            front = temp;
        } else {
            front = temp;
        }
    }
    cin.clear();
    cin.ignore();
    
    cout << "Printing linked list" << endl;
    Node *current = front;
    while (current){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
    
    cout << "Enter the key of the node you wish to delete" << endl;
    int key;
    cin  >> key;
    
    current = front;
    while (current && current->value != key){
        current = current->next;
    }
    
    if (not current){
        cout << "No node with that value existed" << endl;
    } else {
        if (current->next){
            Node *next = current->next;
            current->value = next->value;
            current->next = next->next;
            next->next = nullptr;
            delete next;
        } else {
            delete current;
        }
    }
    
    cout << "Printing out new linked list" << endl;
    current = front;
    while (current){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
    delete front;
}

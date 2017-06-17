//
//  main.cpp
//  2.1
//
//  Created by Drew Alam on 2017-06-17.
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
    
    cout << "Printing linked list" << endl;
    Node *current = front;
    while (current){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
    
    
    unordered_set<int>keys;
    //remove duplicates
    current = front;
    Node *previous = nullptr;
    while (current){
        if (keys.find(current->value) == keys.end()){
            keys.emplace(current->value);
            previous = current;
            current = current->next;
        } else {
            previous->next = current->next; //set previous element in linked list correctly
            //delete only this node
            current->next = nullptr;
            delete current;
            //fix loop invariant
            current = previous->next;
        }
    }
    
    cout << "After removing duplicate elements, we get" << endl;
    current = front;
    while (current){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
    
    
    
    delete front;
    
    return 0;
}

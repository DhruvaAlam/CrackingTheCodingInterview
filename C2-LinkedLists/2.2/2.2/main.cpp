//
//  main.cpp
//  2.2
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
    
    int k;
    cout << "Enter the value for k" << endl;
    cin >> k;
    
    
    Node *a = front;
    Node *b  = front;
    if (!a){
        
    } else {
    
        for (int i = 0; i < k; ++i){
            if (not b->next){
                cout << "Not enough elements in our list" << endl;
                break;
            }
            b = b->next;
        }
    }
    while (b && b->next){
        b = b->next;
        a = a->next;
    }
    
    cout << "The Kth Last Element is " << a->value << endl;
    return 0;
}

//
//  main.cpp
//  2.4
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
    
    int x;
    cout << "Enter the value for x" << endl;
    cin >> x;
    
    Node *less = nullptr;
    Node *lessFront = nullptr;
    Node *greater = nullptr;
    Node *greaterFront = nullptr;
    
    
    current = front;
    while (current){
        Node *temp = current;
        current = current->next;
        temp->next = nullptr;
        
        if (temp->value < x){
            //move current to the before list
            if (less){
                less->next = temp;
                less = temp;
            } else {
                less = temp;
                lessFront = less;
            }
        } else {
            //add it to the greater list
            if (greater){
                //connect prvious node with our node
                greater->next = temp;
                //update the last element of the greater list to be temp
                greater = temp;
            } else{
                //first element greater than or equal to x, all elements will be appended after
                greater = temp;
                //set the first element of this list
                greaterFront = greater;
                
            }
        }
    }
    //combine lists
    Node *newList = nullptr;
    if (less){
        less -> next = greaterFront;
        newList = lessFront;
    } else {
        newList = greaterFront;
    }
    
    cout << "Printing updated linked list" << endl;
    current = newList;
    while (current){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
    
    delete newList;
    
}

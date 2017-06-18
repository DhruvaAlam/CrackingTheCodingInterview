//
//  main.cpp
//  2.7
//
//  Created by Drew Alam on 2017-06-18.
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

Node *readInLinkedList(int count){
    //get first num;
    int num;
    Node *num1 = nullptr;
    cout << "Enter in values one at a time for" << count << " number. Enter any non integer to stop reading in." << endl;
    while (cin >> num){
        Node * temp = new Node(num);
        if (num1){
            temp->next = num1;
            num1 = temp;
        } else {
            num1 = temp;
        }
    }
    cin.clear();
    cin.ignore();
    return num1;
    
}

int main(int argc, const char * argv[]) {
    
    Node *intersection  =readInLinkedList(1);
    Node *first = intersection;
    {
        Node *temp = new Node(4);
        temp->next  = first;
        first = temp;
        
        temp = new Node(5);
        temp->next  = first;
        first = temp;

    }
    Node *second  = intersection;
    {
        Node *temp = new Node(1);
        temp->next  = second;
        second = temp;
        
        temp = new Node(2);
        temp->next  = second;
        second = temp;
        
        temp = new Node(3);
        temp->next  = second;
        second = temp;
    }
    //determine if they end at same point, this must be true if they intersect
    int sizeFirst = 0;
    int sizeSecond = 0;
    
    Node *lastOfFirst = first;
    while (lastOfFirst){
        ++sizeFirst;
        lastOfFirst = lastOfFirst->next;
    }
    
    Node* lastOfSecond = second;
    while(lastOfSecond){
        ++sizeSecond;
        lastOfSecond= lastOfSecond->next;
    }
    
    if (lastOfSecond != lastOfFirst){
        cout << "Do not intersect" << endl;
        return 0;
    }
    int min = sizeFirst < sizeSecond ? sizeFirst : sizeSecond;
    
    for (int i = 0; i < (sizeFirst - min) ; ++ i){
        first = first->next;
    }
    for (int i = 0; i < (sizeSecond - min) ; ++ i){
        second = second->next;
    }
    bool hasMatched = false;
    while (first){
        if (hasMatched){
            if (first == second){
                first = first->next;
                second = second->next;
            } else {
                cout << "Do not intersect properly" << endl;
                return 0;
            }
        } else {
            if (first == second){
                hasMatched = true;
            }
            first = first->next;
            second = second->next;
        }
    }
    cout << "They intersect" << endl;
}

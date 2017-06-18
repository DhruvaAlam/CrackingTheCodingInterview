//
//  main.cpp
//  2.6
//
//  Created by Drew Alam on 2017-06-18.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <deque>
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
    //get first number
    Node * num1 = readInLinkedList(1);
    print(num1);
    
    //use runner technique to get to middle element
    Node *tortise = num1;
    Node *hare = num1;
    deque<Node*> firstHalf;
    while (hare){
        if (hare->next != nullptr){ //go twice, even sized list
            hare= hare->next;
            if (hare -> next == nullptr){
                break;
            } else {
                hare= hare->next;
            }
        } else { //just go once, odd size list
            break;
        }
        firstHalf.push_back(tortise);
        tortise = tortise->next;
    }
    firstHalf.push_back(tortise);
    if (firstHalf.size() % 2 == 0){ //odd sized stack, pop off one element
        firstHalf.pop_back();
    }
    tortise = tortise -> next;
    while (firstHalf.size() != 0){
        Node *top = firstHalf.back();
        cout << "Stack Top: " << top->value << endl;
        cout << "Tortise: " << tortise->value << endl;
        if (top->value == tortise->value){
            firstHalf.pop_back();
            tortise = tortise->next;
        } else {
            cout << "Not palindrom" << endl;
            return 0;
        }
    }
    cout << "Palindrome" << endl;
}

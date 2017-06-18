//
//  main.cpp
//  2.5
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

Node *sumLists(Node *first, Node *second, int carry){
    int sum = 0;
    if (first){
        sum += first->value;
    }
    if (second){
        sum += second->value;
    }
    sum += carry;

    
    int num = sum % 10;
    Node *temp = new Node(num);
    if (not first && not second){
        if (sum == 0){
            return nullptr;
        }
    } else if(not second){
        temp->next = sumLists(first->next, nullptr, sum / 10);
    } else if(not first){
        temp->next = sumLists(nullptr, second->next, sum / 10);
    } else {
        temp->next = sumLists(first->next, second->next, sum / 10);
    }
    return temp;
    
}
Node *padWithZeroes(Node *linkedList, int numZeroes){
    for (int i = 0; i < numZeroes; ++i){
        Node *temp  = new Node(0);
        temp->next = linkedList;
        linkedList = temp;
    }
    return linkedList;
}
Node *sumLists2(Node *first, Node* second, int *carry){
    int sum = 0;
    if (first){
        sum += first->value;
    }
    if (second){
        sum += second->value;
    }
    if (not first->next && not second->next){
        *carry = sum / 10;
        {
            Node *temp = new Node(sum %10);
            temp->next = nullptr;
            return temp;
        }
    }
    
    Node *next = sumLists2(first->next, second->next, carry);
    sum += *carry;
    *carry = sum / 10;
    Node *temp = new Node(sum % 10);
    temp->next = next;
    return temp;
}

Node *forwardSum(Node *first, Node* second){
    int lengthFirst = 0;
    int lengthSecond = 0;
    {
        Node *current = first;
        while (current){
            ++lengthFirst;
            current = current->next;
        }
    }
    {
        Node *current = second;
        while (current){
            ++lengthSecond;
            current = current->next;
        }
    }
    int max = (lengthFirst < lengthSecond) ? lengthSecond : lengthFirst;
    first = padWithZeroes(first, max - lengthFirst);
    second = padWithZeroes(second, max - lengthSecond);
    int carry = 0;
    Node * listNew = sumLists2(first,second, &carry);
    if (carry != 0){
        Node *temp  = new Node(carry);
        temp->next = listNew;
        return temp;
    }
    return listNew;
}

int main(int argc, const char * argv[]) {
    //get first num;
    int num;
    Node *num1 = nullptr;
    cout << "Enter in values one at a time for first number" << endl;
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
    
    print(num1);
    
    //get second num;
    Node *num2 = nullptr;
    cout << "Enter in values one at a time for second number" << endl;
    while (cin >> num){
        Node * temp = new Node(num);
        if (num1){
            temp->next = num2;
            num2 = temp;
        } else {
            num2 = temp;
        }
    }
    cin.clear();
    cin.ignore();
    
    print(num2);
    
    cout << "Would you like to forward add or backwards add? Enter \"f\" for forwards or any other char for backwards " << endl;
    char character;
    cin >> character;
    Node *current = nullptr;
    cout << "Num1 + Num2 = " << endl;
    if (character == 'f'){
        current = forwardSum(num1, num2);
    } else {
        current = sumLists(num1, num2, 0);
    }
    
    print(current);
    
    
    
    delete num1;
    delete num2;
    delete current;
}

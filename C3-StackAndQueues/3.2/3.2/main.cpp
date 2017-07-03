//
//  main.cpp
//  3.2
//
//  Created by Drew Alam on 2017-07-02.
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
    
    Node (int value, Node *lowest): value{value}, lowestNodeInStackBelow{lowest}{
        
    }
    
    void print(){
        cout << value << " ";
    }
    
    void pop(){
        cout << "Popping off the the node with value:" ;
        print();
        cout << endl;
    }
    void lowPrint(){
        cout << "The node with the lowest value is: ";
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
    deque<Node *> stack;
    Node * lowest = nullptr;
    string input;
    int num;
    cout << "Enter numbers one at a time to push elements onto the stack. Enter \"pop\" to pop the top element of the stack. Enter \"min\" to get the lowest elemnt of the list. Enter anything else to exit and print the stack." << endl;
    while (cin >> input){
        if (input == "pop"){
            //get top element and print it off
            Node * temp = stack.front();
            temp->pop();
            
            //if it is the lowest element, then update lowest
            if (temp == lowest){
                lowest = temp->lowestNodeInStackBelow;
            }
            //pop it off the stack
            stack.pop_front();
            //free the memory
            delete temp;
            continue;
        } else if (input == "min"){
            if (lowest){
                lowest->lowPrint();
            } else {
                cout << "There are no element in the stack." << endl;
            }
            continue;
        }
        
        try {
            num  = stoi(input);
        } catch (invalid_argument) {
            cout << "Could not parse input as valid input. Exiting." << endl;
            break;
        }
        Node * temp = new Node(num, lowest ? lowest : nullptr);
        stack.push_front(temp);
        if (not lowest){
            lowest = temp;
        } else {
            if (temp->value < lowest->value){
                lowest = temp;
            }
        }
        printStack(stack);
    }
    printStack(stack);
    //delete elements of the stack
    while (not stack.empty()){
        Node *top = stack.front();
        stack.pop_front();
        delete top;
    }
    
}

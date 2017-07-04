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
#include <vector>
using namespace std;

class Node{
public:
    int value;
    Node (int value): value{value}{
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

class Stack{
    vector<deque<int>> stackList;
    int maxPerStack;
    
public:
    Stack(int maxSize): maxPerStack{maxSize}{
    }
    void print(){
        int i = 0;
        for (auto &subStack: stackList){
            cout << "Elements in substack: " << i << endl;
            for (int num: subStack){
                cout << num << " ";
            }
            cout  << endl;
            ++i;
        }
    }
    void push_front(int num){
    //get the last stack
        if (stackList.empty() || (stackList.at(stackList.size() - 1).size() == maxPerStack)){
            //create new substack
            stackList.emplace_back(deque<int>());
        }
        //insert into last stack
        stackList.at(stackList.size() -1).push_front(num);
    }
    int front(){
        if (stackList.empty()){
            return -1;
        }
        return stackList.at(stackList.size() -1 ).front();
    }
    
    int pop_front(){
        if (stackList.empty()){
            cout << "Nothing else to pop off, stack is empty." << endl;
            return -1;
        }
        int top =front();
        //pop it off
        stackList.at(stackList.size() - 1).pop_front();
        return top;
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
    cout << "How many plates per stack would you like?" << endl;
    int num = 10;
    cin >> num;
    Stack stack (num);
    string input;
    cout << "Enter numbers one at a time to push elements onto the stack. Enter \"pop\" to pop the top element of the stack. Enter \"top\" to view the top element of the stack. Enter anything else to exit and print the stack." << endl;
    while (cin >> input){
        if (input == "pop"){
            stack.pop_front();
            continue;
        } else if (input == "top"){
            cout << stack.front() << endl;
            continue;
        }
        
        try {
            num  = stoi(input);
        } catch (invalid_argument) {
            cout << "Could not parse input as valid input. Exiting." << endl;
            break;
        }
        stack.push_front(num);
    }
    stack.print();
    
}

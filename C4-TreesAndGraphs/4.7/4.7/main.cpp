//
//  main.cpp
//  4.7
//
//  Created by Drew Alam on 2017-07-28.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>
#include <deque>
using namespace std;

class Node{
public:
    string key;
    vector<Node *> neighbours;
    bool visited = false;
    Node(string key): key{key}{}
    
    void addNeighbour(Node *node){
        neighbours.push_back(node);
    }
    
    void print(){
        cout << "Key: " << key << " Neighbours: ";
        for (auto &node: neighbours){
            cout << node->key << " ";
        }
        cout << endl;
    }
    void reset(){
        visited = false;
    }
    void visit(){
        visited = true;
    }
};

class Graph{
public:
    int numDependencies = 0;
    unordered_map<string, Node *> graphTable;
    vector<string> projects;
    unordered_set<string> hasNoParent;
    unordered_set<string> hasParent;
    int numProjects = 0;
    
    void constructGraph(){
        cout << "How many projects are there?" << endl;
        cin >> numProjects;
        cout << "Enter names of the projects seperated by a space" << endl;
        string name;
        for (int i = 0; i < numProjects; ++i){
            cin >> name;
            projects.push_back(name);
            graphTable[name] = new Node{name};
        }
        cout << "Enter the number of dependencies you would like to enter" << endl;
        cin >> numDependencies;
        cout << "Enter dependecies like this: a d" << endl;
        cout << "This means that d depends on a" << endl;
        cin.ignore();
        string child;
        for (int i = 0; i < numDependencies; ++i){
            cin >> name;
            cin >> child;
            
            Node *temp  =  graphTable[name];
            temp->addNeighbour(graphTable[child]);
            
            if (hasParent.find(name) == hasNoParent.end()){
                // If it's not  in the hash table, it means it has no parent
                hasNoParent.emplace(name);
            }
            hasParent.emplace(child);
        }
        printParentLessNodes();
    }
    
    ~Graph(){
        for (auto it = graphTable.begin(); it != graphTable.end(); ++it) {
            delete it->second;
        }
    }
    
    void printGraph(){
        for (auto it = graphTable.begin(); it != graphTable.end(); ++it) {
            it->second->print();
        }
        
        
    }
    
    void printParentLessNodes(){
     cout << "has no parents: ";
        for (auto &str:hasNoParent){
            cout << str << " ";
        }
        cout << endl;
    }
    
    
    void resetVisitation(){
        for (auto it = graphTable.begin(); it != graphTable.end(); ++it){
            it->second->reset();
        }
    }
    
    void buildBFS(Node *node){
        deque<Node*> queue;
        queue.push_back(node);
        while (not queue.empty()) {
            Node * temp = queue.front();
            queue.pop_front();
            
            if (not temp->visited){
                cout << temp->key << endl;
            }
            temp->visit();
            for (auto &child:temp->neighbours){
                queue.push_back(child);
            }
        }
    }
    
    void buildDependencies(){
        unordered_set<string> possibleParentLess;
        while(not hasNoParent.empty()){
            for (auto it = hasNoParent.begin(); it != hasNoParent.end(); ++it){
                cout << "Building: " << graphTable[*it]->key << endl;
                // add all the neighbours of this node
                for (auto &node:(graphTable[*it]->neighbours)){
                    possibleParentLess.emplace(node->key);
                }
            }
            //remove the ones that cannot be compiled yet
            for (auto it = possibleParentLess.begin(); it !=possibleParentLess.end(); ++it){
                for (auto &child:(graphTable[*it]->neighbours)){
                    possibleParentLess.erase(child->key);
                }
            }
        
            possibleParentLess.swap(hasNoParent);
            possibleParentLess.clear();
            printParentLessNodes();
        }
        
        
    }
};

int main(int argc, const char * argv[]) {
    Graph graph;
    graph.constructGraph();
    //graph.printParentLessNodes();
    graph.buildDependencies();
}

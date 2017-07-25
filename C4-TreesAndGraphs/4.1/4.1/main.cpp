//
//  main.cpp
//  4.1
//
//  Created by Drew Alam on 2017-07-23.
//  Copyright © 2017 Drew Alam. All rights reserved.
//

#include <iostream>
#include <unordered_map>
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
    int numNodes = 0;
    unordered_map<string, Node *> graphTable;
    Node *rootNode;
    
    void constructGraph(){
        cout << "Enter the number of nodes you would like to enter" << endl;
        cin >> numNodes;
        cout << "Enter nodes like this: 5 4 3 1" << endl;
        cout << "This creates a node 5 with neighbours 4, 3, and 1" << endl;
        cin.ignore();
        for (int i = 0; i < numNodes; ++i){
            cout << i << endl;
            string input;
            getline(cin, input);
            stringstream line {input};
            
            string nodeKey;
            line >> nodeKey;
            
            Node *temp;
            if (graphTable.find(nodeKey) != graphTable.end()){
                temp = graphTable[nodeKey];
            } else {
                temp = new Node{nodeKey};
                graphTable[nodeKey] = temp;
            }
            
            while (line >> nodeKey) {
                // If the node is in the map, then just add that node to the list of neighbours of our temp node;
                if (graphTable.find(nodeKey) != graphTable.end()){
                    temp->addNeighbour(graphTable[nodeKey]);
                } else {
                    // Construct the node and add it to the table
                    Node *tempNeighbour = new Node{nodeKey};
                    graphTable[nodeKey] = tempNeighbour;
                    temp->addNeighbour(tempNeighbour);
                }
            }
        }
        
        cout << "Enter the key of the root node of the graph" << endl;
        string rootNodeKey = "";
        cin >> rootNodeKey;
        rootNode = graphTable[rootNodeKey];
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
    
    void resetVisitation(){
        for (auto it = graphTable.begin(); it != graphTable.end(); ++it){
            it->second->reset();
        }
    }
};

Node *depthFirstSearch(Node *root, string key){
    if (not root){
        return nullptr;
    }
    cout << root->key << endl;
    if (root->key == key){
        return root;
    }
    for (auto &child: root->neighbours){
        Node *target = depthFirstSearch(child, key);
        if (target){
            return target;
        }
    }
    return nullptr;
}

bool depthFirstSearchFunction(Node *root, string startNodeKey, string endNodeKey){
    //starting from the root, search for the startNodeKey using dfs
    Node *startNode = depthFirstSearch(root, startNodeKey);
    Node *end = depthFirstSearch(startNode, endNodeKey);
    
    if (end){
        return true;
    }
    return false;
}

Node *breadthFirstSearch(Node * root, string key){
    if (not root){
        return nullptr;
    }
    deque<Node *> queue;
    queue.push_back(root);
    
    while (not queue.empty()) {
        Node *popped = queue.front();
        cout << popped->key << endl;
        queue.pop_front();
        if (popped->key == key){
            return popped;
        }
        for (auto &child : popped->neighbours){
                queue.push_back(child);
        }
    }
    return nullptr;
}
bool breadthFirstSearchFunction(Node *root, string startNodeKey, string endNodeKey){
    //starting from the root, search for the startNodeKey using bfs
    Node *startNode = breadthFirstSearch(root, startNodeKey);
    Node *end = breadthFirstSearch(startNode, endNodeKey);
    
    if (end){
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    Graph graph;
    graph.constructGraph();
    graph.printGraph();
    
    string startNodeKey;
    string endNodeKey;
    cout << "Enter the key of the start Node" << endl;
    cin >> startNodeKey;
    cout << "Enter the key of the end Node" << endl;
    cin >> endNodeKey;
    
    bool dfsResult = depthFirstSearchFunction(graph.rootNode, startNodeKey, endNodeKey);
    graph.resetVisitation();
    bool bfsResult = breadthFirstSearchFunction(graph.rootNode, startNodeKey, endNodeKey);
    
    cout << "DFS Result: " << dfsResult << endl;
    cout << "BFS Result: " << bfsResult << endl;
}

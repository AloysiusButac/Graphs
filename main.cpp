#include <iostream>
#include <vector>

#include "SDL2/SDL.h"

// TODO: Make GUI

class Node {
public:
    Node() {
        this->rect.x = 0;
        this->rect.y = 0;
        this->rect.w = 0;
        this->rect.h = 0;
    }
    ~Node() {

    }

    void addConnection(Node* n) {
        this->connections.push_back(n);
    }

    void removeConnection() {
        this->connections.pop_back();
    }
    
    void setValue(void* _val) {
        this->value = _val;
    }

    void* getValue() {return this->value; }

private:
    void* value;
    int x, y;
    int radius;
    SDL_Rect rect;
    std::vector<Node*> connections;
};

static void addTwoWayConnection(Node* _n1, Node* _n2) {
    _n1->addConnection(_n2);
    _n2->addConnection(_n1);
}

int main(int argc, char* argv[]) {
    
    Node* n1 = new Node();
    Node* n2 = new Node();
    Node* n3 = new Node();
    Node* n4 = new Node();
    printf("nodes created.\n");

    n1->addConnection(n2);
    n2->addConnection(n4);
    n1->addConnection(n3);
    printf("connections added.\n");

    delete n1; 
    delete n2;
    delete n3;
    delete n4;
    printf("Program exit.\n");

    return 0;
} 
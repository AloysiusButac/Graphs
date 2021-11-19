
#pragma once

#include <vector>
#include "SDL2/SDL.h"

// TODO: Make GUI

class Node {
public:
    Node();
    Node(int x, int y);
    ~Node();

    void addConnection(Node* n);

    void addTwoWayConnection(Node* n);

    void removeConnection();
    
    void setValue(void* _val);

    void* getValue();

    void setPosition(int _x, int _y);

    void getPosition(int *_x, int *_y);
private:
    void* value;
    int x, y;
    int radius;
    std::vector<Node*> connections;
};

#pragma once

#include <vector>
#include <array>
#include "SDL2/SDL.h"

// TODO: Make GUI

class Node {
public:
    Node();
    Node(int x, int y);
    ~Node();

    void addConnection(Node* n);

    void addTwoWayConnection(Node* n);

    std::vector<Node*> getConnections();

    void removeConnection();

    void removeConnection(Node* n);
    
    void setValue(void* _val);

    void* getValue();

    void setPosition(int _x, int _y);

    void getPosition(int *_x, int *_y);
private:
    void* value = 0;
    int x = 0, y = 0;
    std::vector<Node*> connections;
};

#pragma once
#include <vector>
#include "SDL2/SDL.h"
#include "Node.hpp"

class Graph {
public:
    Graph();
    ~Graph();

    void Render(SDL_Renderer *ren);

    void addElement();

    void addElement(Node* n);

    void removeElement(int index);

    void removeElement(Node* n);

    int getElementCount();
    
    void clearShapes();

    void clearElements();
    
private:
    std::vector<Node*> elements;
    std::vector<SDL_Rect*> shapes;
};
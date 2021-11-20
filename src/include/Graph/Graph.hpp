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

    void selectElement(int _x, int _y);

    void unselectElement();

    void moveElement(int _x, int _y);

    bool isThereElementSelected();
    
private:
    Node *selectedElement = NULL;
    int selectedShapeIndex = 0;
    std::vector<Node*> elements;
    std::vector<SDL_Rect*> shapes;
};
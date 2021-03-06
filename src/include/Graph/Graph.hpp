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

    Node* getSelectedElement();

    void unselectElement();

    void moveElement(int _x, int _y);

    bool isThereElementSelected();

    void addNodeConnection(Node *n1, Node *n2);

    void addTwoWayNodeConnections(Node *n1, Node *n2);

    void scanConnections();

    bool isThereElementHere(int x, int y);

    Node* getElement(int x, int y);
private:
    Node *selectedElement = NULL;
    unsigned int selectedShapeIndex = 0;
    std::vector<Node*> elements;
    std::vector<SDL_Rect*> shapes;
    std::vector<std::vector<Node*>> nodeConnections;
};
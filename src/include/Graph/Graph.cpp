#include "Graph.hpp"

Graph::Graph() {}

Graph::~Graph() {
    clearShapes();
    clearElements();
}

void Graph::Render(SDL_Renderer *ren) {

    int x=0, y=0;
    int x2=0, y2=0;

    // Rendering node connections

    for(int i = 0; i < nodeConnections.size(); i++) {
        elements[i]->getPosition(&x, &y);
        for(auto&& c : nodeConnections[i]) {
            c->getPosition(&x2, &y2);
            SDL_RenderDrawLine(ren, x+10, y+10, x2+10, y2+10);
        }
    }

    // Rendering nodes

    for(int i = 0 ; i < this->shapes.size(); i++) {
        if(this->selectedElement && i == this->selectedShapeIndex) {
            SDL_SetRenderDrawColor(ren, 255, 50, 50, 255);
            SDL_RenderFillRect(ren, this->shapes[i]);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        } else {
            SDL_RenderFillRect(ren, this->shapes[i]);
        }
    }

}

void Graph::addElement() {
    // Placing elements next to each other with margin of 5px
    this->elements.push_back(new Node());
    this->elements[this->elements.size()-1]->setPosition(20 * this->elements.size(), 5);

    this->shapes.push_back(new SDL_Rect());
    this->shapes[this->elements.size()-1]->x = 20 * this->elements.size();
    this->shapes[this->elements.size()-1]->y = 5;
    this->shapes[this->elements.size()-1]->w = 20;
    this->shapes[this->elements.size()-1]->h = 20;

    // SDL_Log("element size: %d", this->elements.size());
}

void Graph::addElement(Node* n) {
    // Placing elements next to each other with margin of 5px
    this->elements.push_back(n);

    int x = 20 * this->elements.size() + 5 * this->elements.size();
    int y = 5;

    this->elements[this->elements.size()-1]->getPosition(&x, &y);

    this->shapes.push_back(new SDL_Rect());
    this->shapes[this->elements.size()-1]->x = x;
    this->shapes[this->elements.size()-1]->y = y;
    this->shapes[this->elements.size()-1]->w = 20;
    this->shapes[this->elements.size()-1]->h = 20;

    // SDL_Log("element size: %d", this->elements.size());
}

void Graph::removeElement(int index) {
    if(index < (int)this->elements.size()) {
        for(auto&& c : this->elements[index]->getConnections()) {
            c->removeConnection(this->elements[index]);
        }

        delete this->elements[index];
        delete this->shapes[index];

        this->elements.erase(this->elements.begin() + index);
        this->shapes.erase(this->shapes.begin() + index);
    }
}

void Graph::removeElement(Node* n) {
    for(int i = 0; i < this->elements.size(); i++) {
        if(n == this->elements[i]) {
            for(auto&& c : n->getConnections()) {
                c->removeConnection(n);
            }

            delete this->elements[i];
            delete this->shapes[i];

            this->elements.erase(this->elements.begin() + i);
            this->shapes.erase(this->shapes.begin() + i);

            return;
        }
    }
}

int Graph::getElementCount() {
    return this->elements.size();
}

void Graph::clearShapes() {
    if(this->shapes.size() > 0)
        for(auto&& s : shapes) 
            delete s;
    
    shapes.clear();
}

void Graph::clearElements() {
    if(this->elements.size() > 0)
        for(auto&& s : elements) 
            delete s;
    
    elements.clear();
}

void Graph::selectElement(int _x, int _y) {
    int xpos = 0, ypos = 0;
    for(unsigned int i = 0; i < this->elements.size(); i++) {
        this->elements[i]->getPosition(&xpos, &ypos);
        if(_x > xpos && _x < xpos + 20 && _y > ypos && _y < ypos + 20){
            this->selectedElement = this->elements[i];
            this->selectedShapeIndex = i;
            return;
        }   
    }
}

Node* Graph::getSelectedElement() {
    return this->selectedElement;
}

void Graph::unselectElement() {
    this->selectedElement = NULL;
}

void Graph::moveElement(int _x, int _y) {
    this->selectedElement->setPosition(_x, _y);
    this->shapes[selectedShapeIndex]->x = _x;
    this->shapes[selectedShapeIndex]->y = _y;
}

bool Graph::isThereElementSelected() {
    return this->selectedElement ? true : false;
}

void Graph::addNodeConnection(Node *n1, Node *n2) {
    n1->addConnection(n2);
}

void Graph::addTwoWayNodeConnections(Node *n1, Node *n2) {
   n1->addTwoWayConnection(n2);
}

void Graph::scanConnections() {
    this->nodeConnections.clear();
    for(auto&& e : this->elements) {
        this->nodeConnections.push_back(e->getConnections());
    }
}

bool Graph::isThereElementHere(int x, int y) {
    int e_x, e_y;
    for(auto&& e : this->elements) {
        e->getPosition(&e_x, &e_y);
        if(x > e_x && y > e_y && x < e_x+20 && y < e_y+20) {
            return true;
        }
    }
    return false;
}

Node* Graph::getElement(int x, int y) {
    int e_x, e_y;
    for(auto&& e : elements) {
        e->getPosition(&e_x, &e_y);
        if(x > e_x && y > e_y && x < e_x+20 && y < e_y+20) {
            return e;
        }
    }

    return NULL;
}
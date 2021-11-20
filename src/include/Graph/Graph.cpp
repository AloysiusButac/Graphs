#include "Graph.hpp"

Graph::Graph() {}

Graph::~Graph() {
    clearShapes();
    clearElements();
}

void Graph::Render(SDL_Renderer *ren) {
    for(auto&& s : shapes) {
        SDL_RenderFillRect(ren, s);
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

    SDL_Log("element size: %d", this->elements.size());
}

void Graph::addElement(Node* n) {
    this->elements.push_back(n);
    this->shapes.push_back(new SDL_Rect());
}

void Graph::removeElement(int index) {
    if(index < (int)this->elements.size()) {
        delete this->elements[index];
        this->elements.shrink_to_fit();
        this->shapes.pop_back();
    }
}

void Graph::removeElement(Node* n) {
    for(auto&& o : this->elements) {
        if(&o == &n) {
           delete o;
           this->elements.shrink_to_fit();
           this->shapes.pop_back();
           break; 
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
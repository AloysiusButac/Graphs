#include "Graph.hpp"

Graph::Graph() {}
Graph::~Graph() {}

void Graph::Render(SDL_Renderer *ren) {
    if(this->shapes.size() > 0)
        SDL_RenderFillRects(ren, shapes[0], shapes.size());
}

void Graph::addElement() {
    this->elements.push_back(new Node());
    this->shapes.push_back(new SDL_Rect());
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
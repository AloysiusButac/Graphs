#include "Node.hpp"

Node::Node(){
    this->setPosition(0, 0);
}
Node::Node(int x, int y) {
    this->setPosition(x, y);
}
Node::~Node() {}

void Node::addConnection(Node* n) {
    this->connections.push_back(n);
}

void Node::addTwoWayConnection(Node* n) {
    this->addConnection(n);
    n->addConnection(this);
}

std::vector<Node*> Node::getConnections() {
    return this->connections;
}

void Node::removeConnection() {
    this->connections.pop_back();
}

void Node::removeConnection(Node* n) {
    for(unsigned int i = 0; i < this->connections.size(); i++) {
        if(this->connections[i] == n) {
            this->connections.erase(this->connections.begin() + i);
        }
    }
}

void Node::setValue(void* _val) {
    this->value = _val;
}

void* Node::getValue() { return this->value; }

void Node::setPosition(int _x, int _y) {
    this->x = _x;
    this->y = _y;
}

void Node::getPosition(int *_x, int *_y) {
    *_x = this->x;
    *_y = this->y;
}
#include "Node.h"


Node::Node(){
    this->parent = nullptr;
    this->link = nullptr;
}

Node::Node(Node * u){
    this->parent = u->parent;
    this->link = u->link;
}

Node::Node(Node* p, QStringList* l){
    this->parent = p;
    this->link = l;
}

Node* Node::getParent(){
    return this->parent;
}

QStringList* Node::getData(){
    return this->link;
}

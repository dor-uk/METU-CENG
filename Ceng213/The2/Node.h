#ifndef NODE_H
#define NODE_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

template<class T>
class Node {
public:
    Node() {
        this->left = NULL;
        this->right = NULL;
    }

    Node(const T &element, Node<T> *left, Node<T> *right) {
        this->element = element;
        this->left = left;
        this->right = right;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "Node(" << node.element << ")";
        return os;
    }

    T element;
    Node<T> *left;
    Node<T> *right;
};

#endif //NODE_H

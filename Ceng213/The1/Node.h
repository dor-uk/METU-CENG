#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T>
class Node
{
public:
    T data;
    Node<T> *prev, *next;

    Node(T dataT) : data(dataT)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }

    Node(T dataT, Node<T> *prev, Node<T> *next) : data(dataT)
    {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &obj) {
        os << obj.data;
        return os;
    }
};

#endif //NODE_H

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "licore_global.h"

template <typename T>
class LICORE_EXPORT DoublyLinkedList
{
public:
    struct Node
    {
        T item;
        Node *previous;
        Node *next;

        Node() : previous(nullptr), next(nullptr) {}
        Node(const T &i, Node *p, Node *n)
        {
            item = i;
            previous = p;
            next = n;
        }
    };

    Node *head;
    Node *tail;
    int _length;

    DoublyLinkedList()
        : head(nullptr)
        , tail(nullptr)
        , _length(0)
    {
    }

    ~DoublyLinkedList()
    {
        Node *p;
        Node *n = head;
        while (n) {
            p = n;
            n = n->next;
            delete p;
        }
    }

    int length() const { return _length; }

    Node *add(const T &item)
    {
        Node *node = new Node(item, tail, nullptr);
        if (tail)
        {
            tail->next = node;
            tail = node;
        }
        else
        {
            head = node;
            tail = node;
        }

        ++_length;

        return node;
    }

    void remove(Node *node)
    {
        if (!node)
            return;

        if (node->previous && node->next) {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        } else if (node->previous) {
            // Remove last node
            node->previous->next = nullptr;
            tail = node->previous;
        } else if (node->next) {
            // Remove first node
            node->next->previous = nullptr;
            head = node->next;
        } else {
            // Remove last node in the linked list
            head = nullptr;
            tail = nullptr;
        }

        node->next = nullptr;
        node->previous = nullptr;

        --_length;
    }

    void splice(Node *node, Node *nextNode)
    {
        if (node == nextNode) {
            return;
        }

        // Remove nextNode, then insert after node
        remove(nextNode);

        Node *oldNodeNext = node->next;
        node->next = nextNode;

        // nextNode is the new tail
        if (tail == node) {
            tail = nextNode;
        } else {
            oldNodeNext->previous = nextNode;
        }

        nextNode->next = oldNodeNext;
        nextNode->previous = node;

        ++_length;
    }
};

#endif // DOUBLYLINKEDLIST_H

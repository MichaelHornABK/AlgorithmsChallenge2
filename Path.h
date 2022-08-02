#pragma once
#include "Node.h"

class Path {
protected:
    Node* m_start;
    Node* m_destination;
    int m_weight;
public:
    Path(Node* start, Node* destination, int weight);
    
    ~Path();

    Node* GetStart() { return m_start; }

    Node* GetDestination() { return m_destination; }

    int GetWeight() { return m_weight; }
};
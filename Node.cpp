#include "Node.h"

Node::Node(char letter, int heuristic, int currPathWeight, Node* previousNode)
    :m_letter(letter)
    , m_heuristic(heuristic)
    , m_currPathWeight(currPathWeight)
    , m_previousNode(previousNode)
{

}

Node::~Node()
{
    delete m_previousNode;
    m_previousNode = nullptr;
}

#include "Path.h"
Path::Path(Node* start, Node* destination, int weight)
    :m_start(start)
    , m_destination(destination)
    , m_weight(weight)
{

}

Path::~Path()
{
    delete m_start;
    m_start = nullptr;
    delete m_destination;
    m_destination = nullptr;
}
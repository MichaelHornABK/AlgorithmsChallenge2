#pragma once
class Node {
protected:
    char m_letter;
    int m_heuristic;
    int m_currPathWeight;
    Node* m_previousNode;
public:
    Node(char letter, int heuristic, int currPathWeight, Node* previousNode);

    ~Node();

    char GetLetter() { return m_letter; }

    int GetHeuristic() { return m_heuristic; }

    int GetPathWeight() { return m_currPathWeight; }

    void SetPathWeight(int weight) { m_currPathWeight = weight; }

    void SetPreviousNode(Node* previousNode) { m_previousNode = previousNode; }

    Node* GetPreviousNode(){ return m_previousNode; }
};
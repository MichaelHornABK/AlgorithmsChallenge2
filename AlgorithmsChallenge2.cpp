#include <iostream>
#include <stack>
#include <queue>

class Node {
protected:
    char m_letter;
    int m_heuristic;
    int m_currPathWeight;
    Node* m_previousNode;
public:
    Node(char letter, int heuristic, int currPathWeight, Node* previousNode)
        :m_letter(letter)
        ,m_heuristic(heuristic)
        ,m_currPathWeight(currPathWeight)
        ,m_previousNode(previousNode)
    {

    }

    ~Node()
    {

    }

    char GetLetter()
    {
        return m_letter;
    }

    int GetHeuristic()
    {
        return m_heuristic;
    }
    
    int GetPathWeight()
    {
        return m_currPathWeight;
    }

    void SetPathWeight(int weight)
    {
        m_currPathWeight = weight;
    }

    void SetPreviousNode(Node* previousNode)
    {
        m_previousNode = previousNode;
    }

    Node* GetPreviousNode()
    {
        return m_previousNode;
    }
};

class Path {
protected:
    Node* m_start;
    Node* m_destination;
    int m_weight;
public:
    Path(Node* start, Node* destination, int weight)
        :m_start(start)
        , m_destination(destination)
        , m_weight(weight)
    {

    }

    ~Path()
    {
        delete m_start;
        m_start = nullptr;
        delete m_destination;
        m_destination = nullptr;
    }

    Node* GetStart()
    {
        return m_start;
    }

    Node* GetDestination()
    {
        return m_destination;
    }

    int GetWeight()
    {
        return m_weight;
    }
};

int CheckTraversal(Node* start, Node* destination, std::vector<Path*> paths);
void BubbleSortArray(std::vector<Node*>* arr);


int main()
{
    Node* nodeA = new Node('A', 0, 0, nullptr);
    Node* nodeB = new Node('B', 0, -1, nullptr);
    Node* nodeC = new Node('C', 0, -1, nullptr);
    Node* nodeD = new Node('D', 0, -1, nullptr);
    Node* nodeY = new Node('Y', 0, -1, nullptr);
    Node* nodeZ = new Node('Z', 0, -1, nullptr);

    Path* pathAB = new Path(nodeA, nodeB, 5);
    Path* pathBC = new Path(nodeB, nodeC, 1);
    Path* pathAD = new Path(nodeA, nodeD, 10);
    Path* pathCD = new Path(nodeC, nodeD, 1);
    Path* pathYZ = new Path(nodeY, nodeZ, 10);

    std::vector<Path*> paths;

    paths.push_back(pathAB);
    paths.push_back(pathBC);
    paths.push_back(pathAD);
    paths.push_back(pathCD);
    paths.push_back(pathYZ);

    int isTraversalPossible = CheckTraversal(nodeA, nodeD, paths);

    if (isTraversalPossible != -1)
    {
        Node* currNode = nodeD;
        std::cout << "The shortest path to D from A is has the weight of: " << nodeD->GetPathWeight() << " and the path goes from ";
        while (currNode->GetPreviousNode() != nullptr)
        {
            if (currNode->GetPreviousNode()->GetPreviousNode() != nullptr)
            {
                std::cout << currNode->GetLetter() << "<-----";
            }
            else
            {
                std::cout << currNode->GetLetter() << "<-----" << currNode->GetPreviousNode()->GetLetter();
            }
            currNode = currNode->GetPreviousNode();
        }
    }
}

int CheckTraversal(Node* start, Node* destination, std::vector<Path*> paths)
{
    std::queue<Node*> travelQueue;
    Node* currNode = start;
    std::vector<Path*> currStack;
    std::vector<Node*>* needToSortArr = new std::vector<Node*>;

    travelQueue.push(currNode);

    while (travelQueue.size() > 0)
    {
        if (currNode == destination)
        {
            return currNode->GetPathWeight();
        }

        //For loop to get all of the paths connected to the current node 
        for (int i = 0; i < paths.size() - 1; i++)
        {
            if (paths[i]->GetStart() == currNode)
            {
                currStack.push_back(paths[i]);
            }
        }

        //For loop to go through the connected nodes
        //Assign weight to the destination nodes
        //Put the nodes in the queue if not already in the queue
        for (int i = 0; i < currStack.size(); i++)
        {
            Node* destinationNode = currStack[i]->GetDestination();
            Node* startNode = currStack[i]->GetStart();
            travelQueue.push(destinationNode);

            //If the current destination does not have a weight
            if (destinationNode->GetPathWeight() == -1)
            {
                destinationNode->SetPathWeight(currStack[i]->GetWeight() + destinationNode->GetHeuristic() + startNode->GetPathWeight());
                destinationNode->SetPreviousNode(currNode);
            }
            //else if the current weight + heuristic is less than the already assigned weight
            else if (destinationNode->GetPathWeight() > currStack[i]->GetWeight() + destinationNode->GetHeuristic())
            {
                destinationNode->SetPathWeight(currStack[i]->GetWeight() + destinationNode->GetHeuristic() + startNode->GetPathWeight());
                destinationNode->SetPreviousNode(currNode);
            }
            
            //curr node is the top of the queue
        }

        //remove the current node from the travel queue because it is done
        travelQueue.pop();

        //Sort the queue
        if (travelQueue.size() > 0)
        {
            for (int i = 0; i <= travelQueue.size(); i++)
            {
                needToSortArr->push_back(travelQueue.front());
                travelQueue.pop();
            }
            BubbleSortArray(needToSortArr);

            for (int i = 0; i < needToSortArr->size(); i++)
            {
                travelQueue.push(needToSortArr->at(i));
            }
            currNode = travelQueue.front();
        }
        needToSortArr->clear();
        currStack.clear();
    }
    std::cout << "There is no path from " << start->GetLetter() << " to " << destination->GetLetter();
    return -1;
    
}

void BubbleSortArray(std::vector<Node*>* arrayToSort)
{
    for (int pass = 0; pass < arrayToSort->size(); pass++)
    {
        for (int i = 0; i < arrayToSort->size() - 1; i++)
        {
            if (arrayToSort->at(i)->GetPathWeight() > arrayToSort->at(i + 1)->GetPathWeight())
            {
                Node* temp = arrayToSort->at(i);

                arrayToSort->at(i) = arrayToSort->at(i+1);

                arrayToSort->at(i+1) = temp;
            }
        }
    }
}
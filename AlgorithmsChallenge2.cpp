#include <iostream>
#include <stack>
#include <queue>
#include "Node.h"
#include "Path.h"

bool CheckTraversal(Node* start, Node* destination, std::vector<Path*> paths);
void BubbleSortArray(std::vector<Node*>* arr);
void DisplayResults(Node* startingNode, Node* destinationNode);
void RemoveDuplicates(std::vector<Node*>* arr);

int main()
{
    Node* nodeA = new Node('A', 5, 0, nullptr);
    Node* nodeB = new Node('B', 4, -1, nullptr);
    Node* nodeC = new Node('C', 2, -1, nullptr);
    Node* nodeD = new Node('D', 0, -1, nullptr);
    Node* nodeY = new Node('Y', 0, -1, nullptr);
    Node* nodeZ = new Node('Z', 0, -1, nullptr);

    Path* pathAB = new Path(nodeA, nodeB, 5);
    Path* pathBC = new Path(nodeB, nodeC, 1);
    Path* pathAD = new Path(nodeA, nodeD, 7);
    Path* pathCD = new Path(nodeC, nodeD, 1);
    Path* pathYZ = new Path(nodeY, nodeZ, 10);

    std::vector<Path*> paths;

    paths.push_back(pathAB);
    paths.push_back(pathBC);
    paths.push_back(pathAD);
    paths.push_back(pathCD);
    paths.push_back(pathYZ);

    Node* startingNode = nodeA;
    Node* destinationNode = nodeD;

    bool isTraversalPossible = CheckTraversal(startingNode, nodeD, paths);

    if (isTraversalPossible)
    {
        DisplayResults(startingNode, destinationNode);
    }
}

bool CheckTraversal(Node* start, Node* destination, std::vector<Path*> paths)
{
    Node* currNode = start;
    std::queue<Node*> travelQueue;
    std::vector<Path*> currStack;
    std::vector<Node*>* needToSortArr = new std::vector<Node*>;

    travelQueue.push(currNode);

    while (travelQueue.size() > 0)
    {
        if (currNode == destination)
        {
            return true;
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
            RemoveDuplicates(needToSortArr);
            BubbleSortArray(needToSortArr);

            //put the sorted array back into the travel queue
            for (int i = 0; i < needToSortArr->size(); i++)
            {
                travelQueue.push(needToSortArr->at(i));
            }
            //the front of the queue will now be the currentnode for the next iteration of the while loop
            currNode = travelQueue.front();
        }

        needToSortArr->clear();
        currStack.clear();
    }
    std::cout << "There is no path from " << start->GetLetter() << " to " << destination->GetLetter();
    return false;
    
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

void RemoveDuplicates(std::vector<Node*>* arrayToRemoveDupes)
{
    for (int i = 0; i < arrayToRemoveDupes->size() - 1; i++)
    {
        for (int y = i + 1; y < arrayToRemoveDupes->size(); y++)
        {
            if (arrayToRemoveDupes->at(i)->GetLetter() == arrayToRemoveDupes->at(y)->GetLetter())
            {
                if (arrayToRemoveDupes->at(i)->GetPathWeight() >= arrayToRemoveDupes->at(y)->GetPathWeight())
                {
                    arrayToRemoveDupes->erase(std::next(arrayToRemoveDupes->begin(), i));
                }
                else
                {
                    arrayToRemoveDupes->erase(std::next(arrayToRemoveDupes->begin(), y));
                }
            }
        }
    }
}

void DisplayResults(Node* startingNode, Node* destinationNode)
{
    //Go through nodes via a Nodes PreviousNode to create the path
    Node* currNode = destinationNode;
    std::cout << "The shortest path to " << destinationNode->GetLetter() << " from " << startingNode->GetLetter() << " has the weight of : " << destinationNode->GetPathWeight() << " and the path goes from ";
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
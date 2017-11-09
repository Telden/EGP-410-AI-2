#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include "GameApp.h"
#include <list>
#include <vector>
#include <algorithm>
#include "Vector2D.h"
#include "Grid.h"

using namespace std;

AStar::AStar(Graph* pGraph, GameApp* applet) : GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
	mpGrid = applet->getGrid();
}

AStar::~AStar()
{

}

const Path& AStar::findPath(Node* pFrom, Node* pTo)
{
#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif
	mPath.clear();

	NodeRecord* startRecord;
	NodeRecord* currentNode;
	NodeRecord* endNodeRecord;
	NodeRecord*endNode;
	int endNodeCost;
	vector <Connection*> connectionList;

	int nodeID;
	/* Initialize the Record */
	startRecord = new NodeRecord();
	startRecord->mpNode = pFrom;
	startRecord->mpConnection = NULL;
	startRecord->mCostSoFar = 0;

	/* Initialize the open and closed lists */
	vector<NodeRecord*>openNodeList;
	openNodeList.push_back(startRecord);

	std::vector<Node*> pClosedList;

	/* Iterate through processing each node */
	while (openNodeList.size() > 0)
	{
		/* Find the smallest element in the open list */ //Cost + distance to end
		currentNode = findSmallestElement(openNodeList, pTo);
		nodeID = getNodeID(openNodeList, currentNode->mpNode);

		/* if it is the goal node, then terminate */
		if (currentNode->mpNode == pTo)
		{
			cout << "Found it\n";
			break;
		}


		/* Get the node's outgoing connections */
		connectionList = mpGraph->getConnections(currentNode->mpNode->getId());

		/* Loop through each connection in turn */
		for (int i = 0; i < connectionList.size(); i++)
		{
			/* Get the cost estimate for the  end node */
			endNode = new NodeRecord();
			endNode->mpNode = connectionList[i]->getToNode();
			endNodeCost = currentNode->mCostSoFar + connectionList[i]->getCost();

			/* Skip if the node is closed */
			if (checkClosedList(pClosedList, endNode->mpNode))
			{
				continue;
			}

			/* or if the node is open and we've found a worse route */
			else if (checkOpenQueue(openNodeList, endNode->mpNode))
			{
				endNodeRecord = findOpenNode(openNodeList, endNode->mpNode);

				if (endNodeRecord->mCostSoFar <= endNodeCost)
					continue;
			}
			/* Otherwise we know we've got an unvisited node, so  make a record for it*/
			else
			{
				//endNodeRecord = new NodeRecord();
				endNodeRecord = endNode;
			}
			endNodeRecord->mpConnection = currentNode;

			/* add it to the open lisit  */
			if (!checkOpenQueue(openNodeList, endNode->mpNode))
				openNodeList.push_back(endNodeRecord);

			/* add the curent node to the closed list */



			cout << openNodeList.size() << "\t" << pClosedList.size() << "\n";

		}

		pClosedList.push_back(currentNode->mpNode);
		openNodeList.erase(openNodeList.begin() + nodeID);


	}

	/* Either we found our goal or ran out of nodes to search. Find  out which */
	if (currentNode->mpNode != pTo)
	{
		/*  We ran out of nodes with no goal found, so there is no solution */
		//return mPath;
	}
	while (currentNode->mpNode != pFrom)
	{


		mPath.addNode(currentNode->mpNode);
#ifdef VISUALIZE_PATH
		mVisitedNodes.push_back(currentNode->mpNode);
#endif
		currentNode = currentNode->mpConnection;

	}
	/* return it */
	return mPath;

}

//Checks to see if the node is in the open queue
bool AStar::checkOpenQueue(vector<NodeRecord*> openList, Node* pSearch)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->mpNode == pSearch)
			return true;
	}

	return false;
}

//checks to see if the node is in the closed list
bool AStar::checkClosedList(std::vector<Node*> closedList, Node* endNode)
{
	for (int j = 0; j < closedList.size(); j++)
	{
		if (closedList[j] == endNode)
			return true;

	}
	return false;
}
//finds the node in the open list
NodeRecord* AStar::findOpenNode(vector<NodeRecord*> openList, Node* search)
{
	for (int j = 0; j < openList.size(); j++)
	{
		if (openList[j]->mpNode == search)
			return openList[j];

	}
	return NULL;
}
//Finds the closest element to the target
NodeRecord* AStar::findSmallestElement(std::vector<NodeRecord*> openList, Node* pTo)
{
	Vector2D unitPos;
	Vector2D endPointPos;
	NodeRecord* lowestCost;
	float distance = 99999;
	float test;

	endPointPos = mpGrid->getULCornerOfSquare(pTo->getId());

	for (int i = 0; i < openList.size(); i++)
	{
		unitPos = mpGrid->getULCornerOfSquare(openList[i]->mpNode->getId());
		test = getDistance(unitPos, endPointPos);
		

		if (test < distance)
		{
			distance = test;
			lowestCost = openList[i];
		}
			
	}

	return lowestCost;
}
//Gets the index of the node
int AStar::getNodeID(std::vector<NodeRecord*> openList, Node* search)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->mpNode == search)
			return i;
	}
	return NULL;
}
//gets the distance between two nodes
float AStar::getDistance(Vector2D lhs, Vector2D rhs)
{
	float distance = sqrt(pow(rhs.getX() - lhs.getX(), 2.0f)
		+ pow(rhs.getY() - lhs.getY(), 2.0f));

	return distance;
}


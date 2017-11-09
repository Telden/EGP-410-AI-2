#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

Dijkstra::Dijkstra(Graph* pGraph) : GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{

}

Dijkstra::~Dijkstra()
{

}

const Path& Dijkstra::findPath(Node* pFrom, Node* pTo)
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
		/* Find the smallest element in the open list */
		currentNode = findSmallestElement( openNodeList);
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
				if(!checkOpenQueue(openNodeList, endNode->mpNode))
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
	cout << "Going into While Loop\n";
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


bool Dijkstra::checkOpenQueue(vector<NodeRecord*> openList, Node* pSearch)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->mpNode == pSearch)
			return true;
	}

	return false;
}


bool Dijkstra::checkClosedList(std::vector<Node*> closedList, Node* endNode)
{
	for (int j = 0; j < closedList.size(); j++)
	{
		if (closedList[j] == endNode)
			return true;

	}
	return false;
}

NodeRecord* Dijkstra::findOpenNode(vector<NodeRecord*> openList, Node* search)
{
	for (int j = 0; j < openList.size(); j++)
	{
		if (openList[j]->mpNode == search)
			return openList[j];

	}
	return NULL;
}

NodeRecord* Dijkstra::findSmallestElement(std::vector<NodeRecord*> openList)
{
	NodeRecord* lowestCost;
	lowestCost = openList.front();
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->mCostSoFar < lowestCost->mCostSoFar)
			lowestCost = openList[i];
	}

	return lowestCost;
}

int Dijkstra::getNodeID(std::vector<NodeRecord*> openList, Node* search)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->mpNode == search)
			return i;
	}
	return NULL;
}




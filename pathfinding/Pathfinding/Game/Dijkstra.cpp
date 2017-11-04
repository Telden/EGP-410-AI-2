#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <queue>
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


	



	NodeRecord* startRecord;
	NodeRecord* current;
	Node*endNode;
	int endNodeCost;
	vector <Connection*> connectionList;

	/* Initialize the Record */
	startRecord = new NodeRecord();
	startRecord->mpNode = pFrom;
	startRecord->mpConnection = NULL;
	startRecord->mCostSoFar = 0;
	
	std::priority_queue<NodeRecord*> openNodeQueue;
	openNodeQueue.push( startRecord);

	std::vector<Node*> pClosedList;
	

	while (openNodeQueue.size() > 0)
	{
		current = openNodeQueue.top();
		openNodeQueue.pop();

		if (current->mpNode == pTo)
			break;
		
		connectionList = mpGraph->getConnections(current->mpNode->getId());

		for (int i = 0; i < connectionList.size() - 1; i++)
		{
			endNode = connectionList[i]->getToNode();
			endNodeCost = current->mCostSoFar + connectionList[i]->getCost();

			for (int j = 0; j < pClosedList.size() - 1; j++)
			{
				if (pClosedList[j] == endNode)
					continue;
				
			}
			for (int k = 0; k < openNodeQueue.size() - 1; k++)
			{
				
			}
		}
	}
}
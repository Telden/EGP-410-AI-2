#pragma once

#include "GridPathfinder.h"
#include "Trackable.h"
#include "GridPathfinder.h"
#include "NodeRecord.h"
#include <vector>
#include <queue>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class Dijkstra : public GridPathfinder
{
private:
	

public:
	Dijkstra(Graph* pGraph);
	~Dijkstra();
	const Path& findPath(Node* pFrom, Node* pTo);
	bool checkOpenQueue(std::vector<NodeRecord*> openList, Node* search);
	NodeRecord* findSmallestElement(std::vector<NodeRecord*> openList);
	NodeRecord* findOpenNode(std::vector<NodeRecord*> openList, Node* search);
	bool checkClosedList(std::vector<Node*> closedList, Node* endNode);
	int getNodeID(std::vector<NodeRecord*> openList, Node* endNode);


};

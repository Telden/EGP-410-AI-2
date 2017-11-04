#pragma once

#include "GridPathfinder.h"
#include "Trackable.h"
#include <vector>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class Dijkstra : public GridPathfinder
{
public:
	Dijkstra(Graph* pGraph);
	~Dijkstra();
	const Path& findPath(Node* pFrom, Node* pTo);


private:
	struct NodeRecord 
	{
		Node* mpNode;
		Connection* mpConnection;
		float mCostSoFar;
	};


};

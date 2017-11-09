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
class GameApp;
class Grid;
class Vector2D;

class AStar : public GridPathfinder
{
private:
	Grid* mpGrid;

public:
	AStar(Graph* pGraph, GameApp* applet);
	~AStar();
	const Path& findPath(Node* pFrom, Node* pTo);
	bool checkOpenQueue(std::vector<NodeRecord*> openList, Node* search);
	NodeRecord* findSmallestElement(std::vector<NodeRecord*> openList, Node* pTo);
	NodeRecord* findOpenNode(std::vector<NodeRecord*> openList, Node* search);
	bool checkClosedList(std::vector<Node*> closedList, Node* endNode);
	int getNodeID(std::vector<NodeRecord*> openList, Node* endNode);
	float getDistance(Vector2D lhs, Vector2D rhs);

};

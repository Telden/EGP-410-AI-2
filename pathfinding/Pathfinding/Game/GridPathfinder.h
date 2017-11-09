#pragma once

#include "Pathfinder.h"
#include <allegro5/allegro.h>

class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;


class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual const Path& findPath( Node* pFrom, Node* pTo ) = 0;
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
	void switchColor(char input);
protected:
	std::vector<Node*> mVisitedNodes;
	GridVisualizer* mpVisualizer;
#endif
	ALLEGRO_COLOR currentPathColor = al_map_rgb(255, 64, 64);
	double mTimeElapsed;
};
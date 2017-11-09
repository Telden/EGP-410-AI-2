#pragma once

class Node;
class Connection;

struct NodeRecord
{
	Node* mpNode;
	NodeRecord* mpConnection;
	float mCostSoFar;
};
#include "AI.h"

using namespace AI;

Node::Node(Vec2 pos, bool isCollidable)
	: pos(pos), collidable(isCollidable)
{
	indexPos = pos / 32.0f;
}

Astar::~Astar()
{
	openList.clear();
	closedList.clear();
}

std::vector<std::vector<Node*>> AI::Astar::nodes;

void Astar::initNodes(std::vector<std::vector<Node*>> nodes)
{
	Astar::nodes = nodes;
}

void Astar::deleteNodes()
{
	for (unsigned int x = 0; x < nodes.size(); x++)
	{
		for (unsigned int y = 0; y < nodes[x].size(); y++)
		{
			delete nodes[x][y];
		}
	}
	nodes.clear();
}

void Astar::searchAStar(Tile* start, Tile* target)
{
	//Vec2 startIndex = start->getPos() / 32.0f;
	//Add the first tile straight to the closed list
	currentNode = getNodeByPos(start->getPos());
	closedList.push_back(currentNode);

	targetReached = false;

	while (!targetReached)
	{
		findNextNode();
	}
	

}

void Astar::findNextNode()
{

}

std::vector<Node> Astar::getAdjacentNodes()
{
	std::vector<Node> result(4);

	Vec2 index = currentNode.getIndex();
	
}
Node Astar::getNodeByPos(Vec2 pos)
{
	pos /= 32.0f;
	return *nodes[pos.x][pos.y];
}
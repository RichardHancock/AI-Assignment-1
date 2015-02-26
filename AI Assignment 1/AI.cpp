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
	std::vector<Node> adjacent = getSafeAdjacentNodes();
	
	for (auto node : adjacent)
	{
		node.setParent(currentNode.getIndex());
		node.g(currentNode.g() + 1); 
		node.h((float)manhattanHeuristic(node.getIndex()));
		node.calculateF();
	}

}

std::vector<Node> Astar::getSafeAdjacentNodes()
{
	std::vector<Node> result;
	
	Vec2 index = currentNode.getIndex();
	
	//Top
	Vec2 top = index;
	top.y -= 1;
	if (checkIndexSafe(top))
	{	if(!nodes[(unsigned int)top.x][(unsigned int)top.y]->isCollidable())
	result.push_back(*nodes[(unsigned int)top.x][(unsigned int)top.y]);
	}
	//Right
	Vec2 right = index;
	right.x += 1;
	if (checkIndexSafe(right))
	{
		if (!nodes[(unsigned int)right.x][(unsigned int)right.y]->isCollidable())
			result.push_back(*nodes[(unsigned int)right.x][(unsigned int)right.y]);
	}
	//Bottom
	Vec2 bottom = index;
	bottom.y += 1;
	if (checkIndexSafe(bottom))
	{
		if (!nodes[(unsigned int)bottom.x][(unsigned int)bottom.y]->isCollidable())
			result.push_back(*nodes[(unsigned int)bottom.x][(unsigned int)bottom.y]);
	}
	//Left
	Vec2 left = index;
	left.x -= 1;
	if (checkIndexSafe(left))
	{
		if (!nodes[(unsigned int)left.x][(unsigned int)left.y]->isCollidable())
			result.push_back(*nodes[(unsigned int)left.x][(unsigned int)left.y]);
	}
	
	return result;
}

bool Astar::checkIndexSafe(Vec2 index)
{
	int sizeX = nodes.size();
	int sizeY = nodes[0].size();

	if (index.x < 0 || index.y < 0 || index.x > sizeX || index.y > sizeY)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Node Astar::getNodeByPos(Vec2 pos)
{
	pos /= 32.0f;
	return *nodes[(unsigned int)pos.x][(unsigned int)pos.y];
}

unsigned int Astar::manhattanHeuristic(Vec2 index)
{
	Vec2 temp;
	temp.x = abs(index.x - target.getIndex().x);
	temp.y = abs(index.y - target.getIndex().y);
	return (unsigned int)(temp.x + temp.y);

}
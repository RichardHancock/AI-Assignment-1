#include "AI.h"

using namespace AI;

Node::Node()
{

}

Node::Node(Vec2 pos, bool isCollidable)
	: pos(pos), collidable(isCollidable)
{
	indexPos = pos / 32.0f;
}

Astar::Astar()
{

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

void Astar::devRender(SDL_Renderer* renderer)
{
	for(auto node : closedList)
	{
		SDL_Rect rect;
		rect.x = node.getPos().x;
		rect.y = node.getPos().y;
		rect.h = 32;
		rect.w = 32;
		SDL_RenderDrawRect(renderer, &rect);
	}
}

std::vector<Vec2> Astar::searchAStar(Vec2 startTile, Vec2 targetTile)
{
	//Find the targetTiles node
	target = getNodeByPos(targetTile);

	//Add the first tile straight to the closed list
	start = getNodeByPos(startTile);
	currentNode = start;
	closedList.push_back(currentNode);

	currentNode.g(0);

	targetReached = false;

	int executionCap = 1000; //Stops the A* going out of control

	while (!targetReached)
	{
		exploreAdjacent();
		findNextNode();

		if(currentNode.getIndex() == target.getIndex())
		{
			targetReached = true;
		}
		
		//Protect the program from infinate loop if the A* goes out of control
		executionCap--;
		if (executionCap == 0)
		{
			Utility::log(Utility::W, "A* loop exceeded its execution cap");
			std::vector<Vec2> failed;
			return failed;
		}
	}
	
	//Target found
	return retraceSteps();
}

void Astar::exploreAdjacent()
{
	std::vector<Node> adjacent = getSafeAdjacentNodes();
	
	for (auto node : adjacent)
	{
		node.setParent(currentNode.getIndex());
		node.g(currentNode.g() + 1); 
		node.h((float)manhattanHeuristic(node.getIndex()));
		node.calculateF();

		openList.push_back(node);
	}
		
	
}

void Astar::findNextNode()
{
	//This finds the smallest f score and if there are multiple it takes the most recent

	//Pre set to a very high number
	unsigned int smallestFScore = 100000;
	unsigned int smallestFNodeIndex;

	for (unsigned int i = 0; i < openList.size(); i++)
	{
		Node cur = openList[i];
		if (cur.f() <= smallestFScore)
		{
			smallestFScore = cur.f();
			smallestFNodeIndex = i;
		}
	}
#ifdef _DEBUG
	if (smallestFScore >= 100000)
	{
		Utility::log(Utility::W, "Either an F score just got more than 100000 or there is a bug in findNextNode()");
	}
#endif

	//Save a copy of the next node
	Node nextNode = openList[smallestFNodeIndex];
	//Delete it from the open list
	openList.erase(openList.begin() + smallestFNodeIndex);
	//Push to the closed list
	closedList.push_back(nextNode);

	//Switch the current node to the next node
	currentNode = nextNode;
}

std::vector<Vec2> Astar::retraceSteps()
{
	std::vector<Vec2> result;
	bool backHome = false;

	//Set the parent to equal the last element of the vector so that it will work the first time
	Vec2 parent = closedList.back().getIndex();

	while (!backHome)
	{
		Node node = closedList.back();
		closedList.pop_back();

		if (node.getIndex() == parent)
		{
			result.push_back(node.getPos());
			
			if (node.getIndex() == start.getIndex())
			{
				backHome = true;
			}
			else
			{
				parent = node.getParent();
			}
		}
		
		
	}

	//Might need this to flip the vector: http://www.cplusplus.com/reference/algorithm/reverse/

	return result;
}

std::vector<Node> Astar::getSafeAdjacentNodes()
{
	std::vector<Node> result;
	
	Vec2 index = currentNode.getIndex();
	
	//Top
	Vec2 top = index;
	top.y -= 1;
	if (checkIndexSafe(top))
	{
		Node cur = *nodes[(unsigned int)top.x][(unsigned int)top.y];
		if (!cur.isCollidable() && !alreadyFound(cur))
			result.push_back(cur);
	}
	//Right
	Vec2 right = index;
	right.x += 1;
	if (checkIndexSafe(right))
	{
		Node cur = *nodes[(unsigned int)right.x][(unsigned int)right.y];
		if (!cur.isCollidable() && !alreadyFound(cur))
			result.push_back(cur);
	}
	//Bottom
	Vec2 bottom = index;
	bottom.y += 1;
	if (checkIndexSafe(bottom))
	{
		Node cur = *nodes[(unsigned int)bottom.x][(unsigned int)bottom.y];
		if (!cur.isCollidable() && !alreadyFound(cur))
			result.push_back(cur);
	}
	//Left
	Vec2 left = index;
	left.x -= 1;
	if (checkIndexSafe(left))
	{
		Node cur = *nodes[(unsigned int)left.x][(unsigned int)left.y];
		if (!cur.isCollidable() && !alreadyFound(cur))
			result.push_back(cur);
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

bool Astar::alreadyFound(Node n)
{
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		if (n.getIndex() == openList[i].getIndex())
		{
			return true;
		}
	}

	for (unsigned int i = 0; i < closedList.size(); i++)
	{
		if (n.getIndex() == closedList[i].getIndex())
		{
			return true;
		}
	}

	return false;
}
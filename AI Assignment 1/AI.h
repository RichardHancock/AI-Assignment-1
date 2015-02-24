#pragma once

#include <vector>

#include "levelManagement/Tile.h"
#include "Vec2.h"

namespace AI
{
	class Node
	{
	public:
		Node(Vec2 pos, bool isCollidable);

		bool isCollidable() { return collidable; }

		//Getters and Setters
		float f() { return fVar; }
		float calculateF() { fVar = gVar + hVar; }
		float g() { return gVar; }
		float g(float newg) { gVar = newg; }
		float h() { return hVar; }
		float h(float newh) { hVar = newh; }

		Vec2 getParent() { return parent; }

		void setParent(Vec2 parentIndex)
		{
			parent = parentIndex;
		}

		Vec2 getIndex() { return indexPos; }

	private:
		Vec2 pos;

		Vec2 indexPos;

		bool collidable;

		Vec2 parent;

		float fVar;
		float gVar;
		float hVar;
	};

	/**
	@class Astar
	@brief A basic Astar pathfinding search (No Diagonals)
	*/
	class Astar
	{
	public:
		~Astar();

		void searchAStar(Tile* start, Tile* target);
		static void initNodes(std::vector<std::vector<Node*>> nodes);
		static void deleteNodes();
	private:
		static std::vector<std::vector<Node*>> nodes;

		std::vector<Node> openList;
		std::vector<Node> closedList;

		Node currentNode;

		Node target;

		bool targetReached;

		Node getNodeByPos(Vec2 pos);

		void findNextNode();

		std::vector<Node> getAdjacentNodes();
	};
	
}
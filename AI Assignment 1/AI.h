#pragma once

#include <vector>

#include "levelManagement/Tile.h"
#include "Vec2.h"

namespace AI
{
	class Node
	{
	public:
		Node();

		Node(Vec2 pos, bool isCollidable);

		bool isCollidable() { return collidable; }

		//Getters and Setters
		float f() { return fVar; }
		void calculateF() { fVar = gVar + hVar; }
		float g() { return gVar; }
		void g(float newg) { gVar = newg; }
		float h() { return hVar; }
		void h(float newh) { hVar = newh; }

		Vec2 getParent() { return parent; }

		void setParent(Vec2 parentIndex)
		{
			parent = parentIndex;
		}

		Vec2 getIndex() { return indexPos; }

		Vec2 getPos() { return pos; }
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
		Astar();
		~Astar();

		std::vector<Vec2> searchAStar(Vec2 start, Vec2 target);
		static void initNodes(std::vector<std::vector<Node*>> nodes);
		static void deleteNodes();

		void devRender(SDL_Renderer* renderer);
	private:
		static std::vector<std::vector<Node*>> nodes;

		std::vector<Node> openList;
		std::vector<Node> closedList;

		Node currentNode;

		Node start;

		Node target;

		bool targetReached;

		

		/**
		@brief Checks if an index is safe (Not out of bounds)
		@param Vec2 - The x and y index of the node
		@return bool - True if safe
		*/
		bool checkIndexSafe(Vec2 index);

		Node getNodeByPos(Vec2 pos);

		void exploreAdjacent();

		void findNextNode();

		std::vector<Vec2> retraceSteps();

		///@todo Refactor get rid of all the excesive casting
		std::vector<Node> getSafeAdjacentNodes();

		unsigned int manhattanHeuristic(Vec2 index);

		bool alreadyFound(Node n);
	};
	
}
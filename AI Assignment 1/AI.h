#pragma once

#include <vector>
#include <stack>

#include "levelManagement/Tile.h"
#include "Vec2.h"

/**
@brief Contains functions and classes related to Artificial intelligence
*/
namespace AI
{
	/**
	@class Node
	@brief A Node for use in AI pathfinding (Mainly A*)
	*/
	class Node
	{
	public:
		///Create Blank Node
		Node();

		/**
		@brief Create a Node
		@param Vec2 - Nodes position
		@param bool - If the node can be traversed (Collidable)
		*/
		Node(Vec2 pos, bool isCollidable);

		/**
		@brief Is this node traversable
		@return bool - Traversable
		*/
		bool isCollidable() { return collidable; }

		//Getters and Setters
		/**
		@brief Get F Score
		@return float - F Score
		*/
		float f() { return fVar; }

		/**
		@brief Calculate the F Score using G and H
		*/
		void calculateF() { fVar = gVar + hVar; }


		/**
		@brief Get G Score
		@return float - G Score
		*/
		float g() { return gVar; }

		/**
		@brief Set G Score
		@param float - New G Score
		*/
		void g(float newg) { gVar = newg; }


		/**
		@brief Get H Score
		@return float - H Score
		*/
		float h() { return hVar; }

		/**
		@brief Set H Score
		@param float - New H Score
		*/
		void h(float newh) { hVar = newh; }


		/**
		@brief Get Node's parent's index
		@return Vec2 - Parent's index
		*/
		Vec2 getParent() { return parent; }

		/**
		@brief Set Node's parent's index
		@param Vec2 - Parent's index
		*/
		void setParent(Vec2 parentIndex)
		{
			parent = parentIndex;
		}

		/**
		@brief Get Node's index
		@return Vec2 - Node's index
		*/
		Vec2 getIndex() { return indexPos; }

		/**
		@brief Get Node's world space position
		@return Vec2 - Node's position
		*/
		Vec2 getPos() { return pos; }
	private:
		///Node's World Space Position
		Vec2 pos;

		///Node's Index Position in the array (Could also be its grid pos (X,Y))
		Vec2 indexPos;

		///Is the Node traversable (Collidable)
		bool collidable;

		///Node's Parent's Index Position in the array (Could also be its grid pos (X,Y))
		Vec2 parent;

		///F Score (G + H)
		float fVar;

		///G Score (Cost of moving to this Node)
		float gVar;

		///H Score (Distance to the goal from this target)
		float hVar;
	};

	/**
	@class Astar
	@brief A basic Astar pathfinding search (No Diagonals)
	*/
	class Astar
	{
	public:
		///Init Astar instance
		Astar();
		///Delete Astar instance
		~Astar();

		/**
		@brief Search for a path using the A* Algorithm
		@param Vec2 - Starting world space position (Must be == to a Node Pos)
		@param Vec2 - Target world space position (Must be == to a Node Pos)
		
		@return std::stack<Vec2> - The generated path
		@todo Make this accept indexes rather than world space positions
		*/
		std::stack<Vec2> searchAStar(Vec2 start, Vec2 target);

		/**
		@brief Static method to initialize the static multi-dimensional vector of nodes
		@param std::vector<std::vector<Node*>> - The vector of all the nodes for the current level
		*/
		static void initNodes(std::vector<std::vector<Node*>> nodes);
		
		/**
		@brief Erase the vector of nodes
		*/
		static void deleteNodes();

		/**
		@brief Draws all the Nodes in the Closed list (Only need for debugging)
		@param SDL_Renderer* - Pointer to the Renderer
		*/
		void devRender(SDL_Renderer* renderer);
	private:
		///Multi-Dimensional Vector containing all the nodes for the current level (these should never be altered, only copied)
		static std::vector<std::vector<Node*>> nodes;

		///The List of all Nodes that are being considered by the A* algorithm
		std::vector<Node> openList;

		///The List of all Nodes that have been visited by the A* algorithm
		std::vector<Node> closedList;

		///The current node the A* algorithm is processing
		Node currentNode;

		///The Node where the search was started from
		Node start;

		///The Node the search is trying to get to
		Node target;

		///Has the target been reached by the algorithm
		bool targetReached;

		

		/**
		@brief Checks if an index is safe (Not out of bounds)
		@param Vec2 - The x and y index of the node
		@return bool - True if safe
		*/
		bool checkIndexSafe(Vec2 index);

		/**
		@brief Gets a node by a World Space Position
		@param Vec2 - World Space Position
		@return Node - Node at that position
		*/
		Node getNodeByPos(Vec2 pos);

		/**
		@brief Explore all the nodes around the current node and populate their internal values. (4 Directions only)
		*/
		void exploreAdjacent();

		/**
		@brief Find the Node with the lowest F score and make it the current Node

		If their are multiple Nodes with the lowest F, the most recent is picked
		*/
		void findNextNode();

		/**
		@brief Follows the closed list of Nodes following the Node's parent indexes until start node is reached
		@return std::stack<Vec2> - The Final Path
		*/
		std::stack<Vec2> retraceSteps();

		/**
		@brief Fetches all the safe (non collidable) nodes adjacent to a node
		@return std::vector<Node> - All the safe adjacent nodes
		*/
		std::vector<Node> getSafeAdjacentNodes();

		/**
		@brief The Manhattan Heuristic used to calculate the H scores
		@param Vec2 - The Node's index we want to get the H score for
		@return unsigned int - H score
		*/
		unsigned int manhattanHeuristic(Vec2 index);

		/**
		@brief Checks if a Node is already in the open or closed lists
		@param Node - Node to check
		@return bool - Already found
		*/
		bool alreadyFound(Node n);
	};
	
}
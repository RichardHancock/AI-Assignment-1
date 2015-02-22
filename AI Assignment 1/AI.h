#include <vector>

#include "Vec2.h"

namespace AI
{
	class Node
	{
	public:
		Node(Vec2 pos, bool isCollidable);

	private:
		Vec2 pos;
		std::vector<Node*> connections;

		bool isCollidable;
	};
}
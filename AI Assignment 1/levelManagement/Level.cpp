#include "Level.h"
#include "../AI.h"

Level::Level(std::vector<std::vector<Tile*>> &tiles, int tileCountW, int tileCountH)
	: tiles(tiles), tileCountW(tileCountW), tileCountH(tileCountH), levelWidth(tileCountW * (int)tileDimensions.x)
	, levelHeight(tileCountH * (int)tileDimensions.y)
{
	setupAI();
}


void Level::render()
{

	//Render Tiles
	for (unsigned int x = 0; x < tiles.size(); x++)
	{
		for (unsigned int y = 0; y < tiles[x].size(); y++)
		{
			if (tiles[x][y] != NULL)
			{
				tiles[x][y]->render();
			}
		}
	}
}

void Level::update(float dt)
{

	//Update Tiles
	for (unsigned int x = 0; x < tiles.size(); x++)
	{
		for (unsigned int y = 0; y < tiles[x].size(); y++)
		{
			if (tiles[x][y] != NULL)
			{
				tiles[x][y]->update(dt);
			}
		}
	}
}

std::vector<Tile*> Level::checkTiles(SDL_Rect selection)
{
	//I could write a more complex search with filtering here to reduce the amount but this should be fine.

	int offset = 0; //just to make sure we get them all
	//Start the 
	Vec2 start;
	Vec2 end;
	start.x = (selection.x / tileDimensions.x) - offset;
	end.x = ((selection.x + selection.w) / tileDimensions.x) + offset;
	start.y = (selection.y / tileDimensions.y) - offset;
	end.y = ((selection.y + selection.h) / tileDimensions.y) + offset;

	std::vector<Tile*> results;

	if (start.x < 0) { start.x = 0; }
	if (end.x > tileCountW) { end.x = (float)tileCountW; }
	if (start.y < 0) { start.y = 0; }
	if (end.y > tileCountH) { end.y = (float)tileCountH; }

	for (int x = (int)start.x; x < end.x; x++)
	{
		for (int y = (int)start.y; y < end.y; y++)
		{
			if (tiles[x][y] != NULL)
			{
				if (tiles[x][y]->isCollidable())
				{
					results.push_back(tiles[x][y]);
				}				
			}
			
		}
	}

	return results;
}

void Level::setupAI()
{
	std::vector<std::vector<AI::Node*>> nodes;
	//Set the vector to the correct size
	nodes.resize(tileCountW);
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		nodes[i].resize(tileCountH);
	}

	//Loop over all the tiles and create a Node for it
	for (int x = 0; x < tileCountW; x++)
	{
		for (int y = 0; y < tileCountH; y++)
		{
			Tile* curTile = tiles[x][y];
			
			AI::Node* node;

			if (curTile == nullptr)
			{
				Vec2 pos(x * tileDimensions.x, y * tileDimensions.y);
				node = new AI::Node(pos, false);
			}
			else
			{
				node = new AI::Node(curTile->getPos(), curTile->isCollidable());
			}
			
			nodes[x][y] = node;
			
		}
	}

	AI::Astar::initNodes(nodes);

}

Tile* Level::getTileByIndex(Vec2 index)
{
	return tiles[(int)index.x][(int)index.y];
}
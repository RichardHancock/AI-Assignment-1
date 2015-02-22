#include "Tile.h"

Tile::Tile(Texture* texture, Vec2 pos, bool collidable, bool obscuresVision, Utility::TileType type)
	: Entity(texture, pos), collidable(collidable), obscuresVision(obscuresVision), type(type)
{

}

void Tile::update(float dt)
{
	//No Function but required since the base class has it.
}

bool Tile::isCollidable()
{
	return collidable;
}

bool Tile::blocksVision()
{
	return obscuresVision;
}

Utility::TileType Tile::getType()
{
	return type;
}
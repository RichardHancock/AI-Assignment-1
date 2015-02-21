#pragma once

#include "../Entity.h"

/**
@class Tile
@brief A tile used in the construction of a level
*/
class Tile : public Entity
{
public:

	/**
	@brief Creates a Tile
	@param Texture* - The Tiles Sprite
	@param Vec2 - Position
	@param bool - Is the tile collidable
	@param bool - Does the tile obscure Entity's line of sight
	@param 
	*/
	Tile(Texture*, Vec2, bool, bool, Utility::TileType);
	
	/**
	@brief Updates the Internal values of Tile
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Is this tile collidable
	@return bool - True if collidable, false if not
	*/
	bool isCollidable();

	/**
	@brief Render Tile relative to passed in camera
	@param SDL_Rect* - The current camera
	*/
	void render(SDL_Rect* camera);

	/**
	@brief Get what tile type this tile is
	@return Utility::TileType - The Tile Type
	*/
	Utility::TileType getType();
private:
	/// Is this tile collidable
	bool collidable;

	/// Does this tile obscure an Entity's vision (Line of Sight)
	bool obscuresVision;

	/// This tiles TileType
	Utility::TileType type;
};
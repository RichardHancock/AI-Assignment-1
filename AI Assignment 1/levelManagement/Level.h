#pragma once

#include <vector>

#include "Tile.h"

/**
@class Level
@brief Class containing all the Tiles for a level
*/
class Level
{
public:
	/**
	@brief Contains a Level and pointers to its data, also holds method to access this data
	in a meaningful way.
	
	@param std::vector<std::vector<Tile*>>& - Reference to all the tiles.
	@param int - Amount of tiles in the X axis (Width).
	@param int - Amount of tiles in the Y axis (Height).
	*/
	Level(std::vector<std::vector<Tile*>>&, int, int);
	
	/**
	@brief Render Tiles 
	*/
	void render();

	/**
	@brief Updates the internal values of all Tiles
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Get all tiles inside the passed in rectangle
	@param SDL_Rect - The box stating what area, the tiles should be from 
	@return std::vector<Tile*> - Vector of all tiles inside the catchment box
	*/
	std::vector<Tile*> checkTiles(SDL_Rect);

	Tile* getTileByIndex(Vec2 index);

	///The Dimension of all tiles
	const Vec2 tileDimensions = { 32, 32 };

	///Tile count in the x axis (Width)
	const int tileCountW;

	///Tile count in the y axis (Height)
	const int tileCountH;

	///Level's width in pixels
	const int levelWidth;

	///Level's height in pixels
	const int levelHeight;

private:

	/// Setups the Nodes for this level so that the AI can function
	void setupAI();

	///Vector of all tiles in the level
	std::vector<std::vector<Tile*>> tiles;

	
};

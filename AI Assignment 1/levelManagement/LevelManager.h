#pragma once

#include <map>
#include <vector>

#include "Tile.h"
#include "Level.h"

/**
@class LevelManager
@brief Loads level data and relevant images 
*/
class LevelManager
{
private:
	//The properties of a tile
	struct TileProperties
	{
		Texture* texture; //< Can be null for no texture
		bool hasCollision; //< Does the tile have collision
		bool obscuresVision; //< Does the tile block vision (For line of sight tests)
	};

public:
	/**
	@brief Create the Level Manager
	@param std::string - The level file
	@param SDL_Renderer - Renderer
	*/
	LevelManager(std::string filename, SDL_Renderer* renderer);

	/**
	@brief Load the level from a the lvl file
	@param string - The level file
	@param SDL_Renderer* - Renderer
	@return bool - Success
	*/
	bool loadFile(std::string filename, SDL_Renderer* renderer);

	/**
	@brief Get the specified level by its name name
	@param std::string - Name of level
	@return Level* - Pointer to the Level data
	*/
	Level* getLevel(std::string name);

private:
	///The Dimensions of all Tiles
	const Vec2 TILE_DIMENSIONS = { 32, 32 };

	///All the stored Levels
	std::map<std::string, Level*> levels;

	/**
	@brief Resizes a multi-dimensional vector to the size of the level dimensions
	@param std::vector<std::vector<Tile*>> - The vector to make correct size
	@param int - The level height in tiles (not pixels)
	@param int - The level width in tiles (not pixels)
	*/
	void createTileVector(std::vector<std::vector<Tile*>> &tiles, int levelHeight, int levelWidth);

	/**
	@brief Create a tile with all of the required data
	@param std::map<Utility::TileType, TileProperties> - The array of Tile Properties containing textures and other properties
	@param std::ifstream - stream containing the level file at the current tile position
	@param Vec2 - Its position in the tile grid
	@return Tile* - The newly created Tile
	*/
	Tile* createTile(std::map<Utility::TileType, TileProperties> &textures, std::ifstream &file, Vec2 gridPos);

	/**
	@brief 
	@param SDL_Renderer* - Renderer
	@param std::ifstream - stream containing the level file at the tile properties section
	@return std::map<Utility::TileType, TileProperties> - The map of textures and properties
	*/
	std::map<Utility::TileType, TileProperties> loadTileTextures(SDL_Renderer* renderer, std::ifstream &file);

};
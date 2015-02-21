#include <SDL_ttf.h>

#include "State.h"
#include "StateManager.h"

#include "../Utility.h"
#include "../Texture.h"
#include "../levelManagement/LevelManager.h"
#include "../Player.h"

#pragma once

/**
@class PlayState
@brief The state which contains the game and all gameplay elements
*/
class PlayState :public State
{
public:
	/**
	@brief Create the State
	@param StateManager* - Pointer to the current state manager
	@param SDL_Renderer* - Renderer
	@param unsigned int - Starting level
	*/
	PlayState(StateManager* manager, SDL_Renderer* renderer, unsigned int level);

	~PlayState();

	/**
	@brief Handles any events such as keyboard/mouse input
	*/
	bool eventHandler();

	/**
	@brief Update any internal values
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	void render();

private:
	/*
	/**
	@brief Check for collisions between the player and the world
	@param float - delta time
	@param LevelManager - Level manager containing the level data
	@param Player - The player object
	
	void worldCollisions(float dt, LevelManager &levels, Player &player);

	/**
	@brief Check for collisions between the player and the enemies
	@param EnemyManager - Enemy manager containing the enemies
	@param Player - The player object
	
	void enemyCollisions(EnemyManager &enemies, Player &player);

	/**
	@brief Checks if a game over has occurred (Reach end of level
	@todo Add a game over screen, currently only prints to console.
	
	void checkGameOver();
	*/

	/**
	@brief Load most of the resources require for gameplay (Mostly done to clean up the constructor)
	*/
	void loadResources();

	///The level manager which contains all of the levels data.
	LevelManager* levels;

	///The Player
	Player* player;

	///Font
	TTF_Font* font;

};
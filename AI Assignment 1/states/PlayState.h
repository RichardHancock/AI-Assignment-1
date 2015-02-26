#include <SDL_ttf.h>

#include "State.h"
#include "StateManager.h"

#include "../Utility.h"
#include "../Texture.h"
#include "../levelManagement/LevelManager.h"
#include "../Player.h"
#include "../Bot.h"
#include "../AI.h"

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
	*/
	PlayState(StateManager* manager, SDL_Renderer* renderer);

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
	
	/**
	@brief Check if the player is going to collide with the scenery next frame
	@param float - DeltaTime
	*/
	void collision(float);

	/**
	@brief Checks for line of sight between two entity's
	@param Level& - The level
	@param Player& - The player
	@param Bot& - The bot
	@return bool - Has line of sight
	*/
	bool lineOfSight(Level& level, Player& player, Bot& bot);

	/**
	@brief Load most of the resources require for gameplay (Mostly done to clean up the constructor)
	*/
	void loadResources();

	///The level manager which contains all of the levels data.
	LevelManager* levels;

	//Sprites
	///Player Sprite
	Texture* playerSprite;

	///Bot A Sprite
	Texture* botASprite;

	///Bot B Sprite
	Texture* botBSprite;

	//Objects
	///The Player
	Player* player;

	///Bot A
	Bot* botA;

	///Bot B
	Bot* botB;

	///Font
	TTF_Font* font;

	///@todo just for testing remove
	AI::Astar* astar;

	std::vector<Vec2> pathTest;
};
#pragma once

#include "EntityWithNavigation.h"
#include "levelManagement/LevelManager.h"
#include "Player.h"

/**
@class Bot
@brief An AI that follows a state machine and has pathfinding
*/
class Bot : public EntityWithNavigation
{
public:

	///Enum of the behaviours the Bot can use
	enum Behaviour
	{
		Stopped,
		PlaningToFlee,
		Fleeing,
		Following
	};

	/**
	@brief Create the Bot
	@param Texture* - Bot's sprite
	@param Vec2 - Initial Position
	@param bool - Whether the Bot should use the "Bot B" Behaviour set
	@param LevelManager* - The level Manager
	*/
	Bot(Texture* sprite, Vec2 initPos, bool behaviourSetB, LevelManager* levels);

	///Delete Bot
	~Bot();

	/// Update the Bot's internal values
	virtual void update(float dt);

	/**
	@brief Update the Bot's knowledge of the player and bot positions
	@param
	*/
	void updateOtherAABBs(SDL_Rect player, SDL_Rect bot, Vec2 botLastWP);

private:
	
	/// Bot's current behaviour
	Behaviour curBehaviour;

	///If true use behaviour set B else use A
	bool useBehavioursB;

	//Bot A Behaviours (Doesn't have the "Following" behaviour)
	void behavioursA();

	//Bot B Behaviours
	void behavioursB();

	///Does the player currently have line of sight with the bot
	bool seenByPlayer;

	///Does the bot have line of sight with the other bot
	bool spottedOtherBot;

	///Needed for line of sight (Must be a better way of doing this)
	LevelManager* levels;

	///The player's current position and AABB
	SDL_Rect curPlayerAABB;

	///The other bot's current actual position and AABB
	SDL_Rect otherBotAABB;

	/// The other bots last known waypoint (used for following)
	SDL_Rect otherBotLastWPAABB;

	/**
	@brief Checks for line of sight between two entity's
	@param Level& - The level
	@param SDL_Rect& - other
	@return bool - Has line of sight
	*/
	bool lineOfSight(Level& level, SDL_Rect& other);

	/**
	@brief Checks for line of sight between two entity's
	@param Level& - The level
	@param SDL_Rect& - A
	@param SDL_Rect& - B
	@return bool - Has line of sight
	*/
	bool lineOfSight(Level& level, SDL_Rect& a, SDL_Rect& b);

	/**
	@brief Finds a random hidden tile out of sight from the player.
	@return Vec2 - Index to the random tile
	*/
	Vec2 findHiddenTile();
};
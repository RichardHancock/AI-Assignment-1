#pragma once

#include "EntityWithNavigation.h"
#include "levelManagement/LevelManager.h"
#include "Player.h"

class Bot : public EntityWithNavigation
{
public:

	enum Behaviour
	{
		Stopped,
		PlaningToFlee,
		Fleeing,
		Following
	};

	Bot(Texture* sprite, Vec2 initPos, bool behaviourSetB, LevelManager* levels);

	~Bot();

	
	virtual void update(float dt);

	void updateOtherAABBs(SDL_Rect player, SDL_Rect bot);

private:
	
	/// Bot's current behaviour
	Behaviour curBehaviour;

	///If true use behaviour set B else use A
	bool useBehavioursB;

	//Bot A Behaviours (Doesn't have the "Following" behaviour)
	void behavioursA();

	//Bot B Behaviours
	void behavioursB();

	bool seenByPlayer;

	bool spottedOtherBot;

	///Needed for line of sight (Must be a better way of doing this)
	LevelManager* levels;

	SDL_Rect curPlayerAABB;

	SDL_Rect otherBotAABB;

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


	Vec2 findHiddenTile();
};
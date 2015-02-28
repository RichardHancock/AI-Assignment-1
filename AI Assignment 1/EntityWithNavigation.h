#pragma once

#include "EntityWithMotion.h"

#include <stack>

#include "AI.h"

class EntityWithNavigation : public EntityWithMotion
{
public:
	/**
	@brief Create an EntityWithNavigation (Abstract Base Class)
	@param Texture* - Entity's sprite
	@param Vec2 - Starting position
	*/
	EntityWithNavigation(Texture*, Vec2);

	~EntityWithNavigation();

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	virtual void update(float) = 0;

	void generatePath(Vec2 target);

	void updateNav(float dt);

	void showPath(bool);

	void render();
protected:
	std::stack<Vec2> waypoints;

	AI::Astar* pathfinding;

	bool finishedNavigation;

	float distanceToWP;

	bool displayPath;

	void nextWaypoint();

	void startMoving();
};
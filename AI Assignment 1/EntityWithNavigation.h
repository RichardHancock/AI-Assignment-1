#pragma once

#include "EntityWithMotion.h"

#include <stack>

#include "AI.h"

/**
@class EntityWithNavigation
@brief An entity that has pathfinding to move along waypoints
*/
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

	/**
	@brief Generates a path to a target
	@param Vec2 - Target
	*/
	void generatePath(Vec2 target);

	/**
	@brief Updates all the internal values needed for navigation
	@param float - Deltatime
	*/
	void updateNav(float dt);

	/**
	@brief Toggle whether the path the Entity is following is displayed
	@param bool - Show Path
	*/
	void showPath(bool);

	/**
	@brief Render the bot and the path (if enabled)
	*/
	void render();

	/**
	@brief Get the previous waypoint the bot last visited
	@return Vec2 - Previous waypoint position
	*/
	Vec2 getPreviousWP();
protected:
	///Stack containing the Position of all the waypoints 
	std::stack<Vec2> waypoints;

	///The A* algorithm local instance
	AI::Astar* pathfinding;

	/// Has the entity finished navigating (Not Moving)
	bool finishedNavigation;

	/// Distance to Waypoint
	float distanceToWP;

	/// Whether the path should be displayed
	bool displayPath;

	/// A flag telling the entity to stop at the next waypoint
	bool stop;

	/// The previous waypoint visited by the Entity
	Vec2 lastNavigationWP;

	/**
	@brief Switches to the next waypoint in the stack
	*/
	void nextWaypoint();

	/**
	@brief Sets the initial velocity for the Entity to start moving
	*/
	void startMoving();

	/**
	@brief Sets the stop flag
	*/
	void stopAtNextWaypoint();
};
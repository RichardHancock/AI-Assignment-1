#include "Entity.h"

#pragma once

/**
@class EntityWithMotion
@brief Abstract base class that contains all the data needed by something that appears on screen and moves (Velocity
*/
class EntityWithMotion : public Entity
{
public:
	/**
	@brief Create an EntityWithMotion (#Abstract Base Class)
	@param Texture* - Entity's sprite
	@param Vec2 - Starting position
	*/
	EntityWithMotion(Texture*, Vec2);

	/**
	@brief Create an EntityWithMotion (#Abstract Base Class)
	@param Texture* - Entity's sprite
	@param Vec2 - Starting position
	@param float - Maximum Rotation Speed
	*/
	EntityWithMotion(Texture*, Vec2, float);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	virtual void update(float) = 0;

	/**
	@brief Get the Entity's current velocity	
	@return Vec2 - Velocity
	*/
	Vec2 getVelocity();

	/**
	@brief Set the Entity's current velocity
	@param Vec2 - New Velocity
	*/
	void setVelocity(Vec2 velocity);
	
	/**
	@brief Get the Entity's current rotation speed
	@return float - Rotation Speed
	*/
	float getRotationSpeed();

	/**
	@brief Set the Entity's current rotation speed
	@param float - New Rotation Speed
	*/
	void setRotationSpeed(float rotationSpeed);
protected:
	/// Entity's Current velocity
	Vec2 velocity;

	/// Entity's Current rotation Speed
	float rotationSpeed;

	/// The Maximum rotation speed
	float maxRotationSpeed;
};
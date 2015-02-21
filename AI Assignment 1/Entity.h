#include "Texture.h"
#include "Vec2.h"

#pragma once

/**
@class Entity
@brief Abstract base class that contains all the data needed by something that appears on screen
*/
class Entity
{
public:
	/**
	@brief Create an Entity (Abstract Base Class)
	@param Texture* - Entity's sprite
	@param Vec2 - Starting position
	*/
	Entity(Texture* sprite, Vec2 pos);
	
	~Entity();

	/**
	@brief Render the Entity's sprite at its position
	*/
	void Entity::render();

	/**
	@brief Moves the Entity by the passed in amount
	@param Vec2 - Position to add to the Entity's current position
	*/
	void Entity::move(Vec2);

	/**
	@brief Gets the Entity's position
	@return Vec2 - Current Position
	*/
	Vec2 Entity::getPos();

	/**
	@brief Sets the Entity's position
	@param Vec2 - Position to move to 
	*/
	void Entity::setPos(Vec2);

	/**
	@brief Gets the Dimensions of the Entity's stored texture

	Not necessarily the dimension of the Entity in the world
	@return Vec2 - Dimensions of Sprite
	*/
	Vec2 Entity::getDimensions();

	/**
	@brief Gets the Entity's rotation
	@return float - Rotation in degrees
	*/
	float getRotation();

	/**
	@brief Sets the Entity's rotation
	@param float - Rotation in degrees
	*/
	void setRotation(float);
	
	/**
	@brief Gets the Entity's Axis Aligned Bounding Box

	Not necessarily the dimensions of the image.
	@return SDL_Rect - Rectangular box
	*/
	SDL_Rect getAABB();

	/**
	@brief Reduces the AABB to the width and height passed in
	@param Vec2 - New width and height for the AABB
	*/
	void setReducedAABB(Vec2);

	/**
	@brief Reduces the AABB to the percent passed in 
	@param unsigned int - Percent between 0 - 100
	*/
	void setReducedAABB(unsigned int);

	/**
	@brief Updates the Internal values of Entity
	@param float - delta time
	*/
	virtual void update(float) = 0;
protected:
	///Entity's Sprite
	Texture* sprite;

	///Current Position
	Vec2 pos;

	/**
	@brief Checks if the Texture is NULL and then assigns it to the Entity
	@param Texture* - sprite
	@return bool - Was the sprite valid and assigned successfully
	*/
	bool Entity::assignTexture(Texture*);

	///Current Rotation in Degrees
	float rotation;

	/**
	@brief Updates the X,Y Pos of the AABB with the Entity's current position
	*/
	void updateAABB();

	/// Entity's Axis-Aligned Bounding Box
	SDL_Rect AABB;
};
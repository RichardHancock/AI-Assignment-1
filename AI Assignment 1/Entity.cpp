#include <iostream>

#include "Entity.h"

Entity::Entity(Texture* inputTexture, Vec2 inputPos)
{
	pos = inputPos;
	assignTexture(inputTexture);

	//Create the Collision box (AABB - Axis-Aligned Bounding Box)
	SDL_Rect tempAABB;
	tempAABB.h = (int)getDimensions().y;
	tempAABB.w = (int)getDimensions().x;
	tempAABB.x = (int)pos.x;
	tempAABB.y = (int)pos.y;

	AABB = tempAABB;
}

Entity::~Entity()
{
	
}

bool Entity::assignTexture(Texture *texture)
{
	if (!texture)
	{
		std::cout << "Texture supplied to Entity incorrect" << std::endl;
		return false;
	}
	else
	{
		sprite = texture;
		return true;
	}

}

Vec2 Entity::getDimensions()
{	
	return sprite->getDimensions();
}

void Entity::render()
{
	(*sprite).draw(pos, rotation);
}

void Entity::move(Vec2 adjustBy)
{
	/*
	if (pos.x > 640 - getDimensions().x)
	{
		pos.x = 640 - getDimensions().x;
	} 
	else if (pos.x < 0)
	{
		pos.x = 0;
	}
	else
	{
	*/
		pos.x += adjustBy.x;
		pos.y += adjustBy.y;
	
}

Vec2 Entity::getPos()
{
	return pos;
}

void Entity::setPos(Vec2 setTo)
{
	pos = setTo;
}

float Entity::getRotation()
{
	return rotation;
}

void Entity::setRotation(float newRotation)
{
	rotation = newRotation;
}

void Entity::updateAABB()
{
	AABB.x = (int)pos.x;
	AABB.y = (int)pos.y;
}

SDL_Rect Entity::getAABB()
{
	updateAABB();
	return this->AABB;
}

void Entity::setReducedAABB(Vec2 dimensions)
{
	AABB.w = (int)dimensions.x;
	AABB.h = (int)dimensions.y;
}

void Entity::setReducedAABB(unsigned int percent)
{
	if (percent > 100)
	{
		Utility::log(Utility::E, "setReducedAABB was given a percentage higher than 100: " + std::to_string(percent));
		return;
	}
	//Casts put everywhere for paranoia that it will throw out the decimals too early 
	AABB.w = (int)(((float)percent / 100.0f) * (float)AABB.w);
}
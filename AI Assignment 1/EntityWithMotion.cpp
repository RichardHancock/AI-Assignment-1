#include "EntityWithMotion.h"

EntityWithMotion::EntityWithMotion(Texture* texture, Vec2 pos, float maxRotationSpeed)
	: Entity(texture, pos), maxRotationSpeed(maxRotationSpeed)
{
	rotationSpeed = 0;
	velocity = { 0, 0 };
}

EntityWithMotion::EntityWithMotion(Texture* texture, Vec2 pos)
	: Entity(texture, pos), maxRotationSpeed(0)
{
	rotationSpeed = 0;
	velocity = { 0, 0 };
}

Vec2 EntityWithMotion::getVelocity() { return velocity; }

void EntityWithMotion::setVelocity(Vec2 velocity)
{
	this->velocity = velocity;
}

float EntityWithMotion::getRotationSpeed() { return rotationSpeed; }

void EntityWithMotion::setRotationSpeed(float rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}
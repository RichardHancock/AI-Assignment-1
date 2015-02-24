#pragma once

#include "EntityWithMotion.h"

class Bot : public EntityWithMotion
{
public:

	Bot(Texture* sprite, Vec2 initPos);

	~Bot();

	void update(float dt);
private:
	bool pathFound;
};
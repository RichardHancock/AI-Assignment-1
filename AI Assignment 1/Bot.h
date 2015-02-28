#pragma once

#include "EntityWithNavigation.h"

class Bot : public EntityWithNavigation
{
public:

	Bot(Texture* sprite, Vec2 initPos);

	~Bot();

	void update(float dt);
private:
	
};
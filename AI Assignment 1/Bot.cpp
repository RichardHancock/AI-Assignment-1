#include "Bot.h"

Bot::Bot(Texture* sprite, Vec2 initPos)
	: EntityWithNavigation(sprite, initPos)
{

}

Bot::~Bot()
{

}

void Bot::update(float dt)
{
	updateNav(dt);
}
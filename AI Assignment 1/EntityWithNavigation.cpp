#include "EntityWithNavigation.h"

EntityWithNavigation::EntityWithNavigation(Texture* sprite, Vec2 pos)
	: EntityWithMotion(sprite, pos), finishedNavigation(true), distanceToWP(0), displayPath(true)
{

}

EntityWithNavigation::~EntityWithNavigation()
{
	delete pathfinding;

	//Apparently stacks don't have a clear function
	while (!waypoints.empty())
	{
		waypoints.pop();
	}
}

void EntityWithNavigation::showPath(bool show)
{
	displayPath = show;
}

void EntityWithNavigation::generatePath(Vec2 target)
{
	finishedNavigation = false; 

	delete pathfinding;
	pathfinding = new AI::Astar();

	waypoints = pathfinding->searchAStar(pos, target);
	
	waypoints.pop();
	Vec2 curWP = waypoints.top();
	Vec2 temp;

	temp.x = abs(pos.x - curWP.x);
	temp.y = abs(pos.y - curWP.y);

	distanceToWP = temp.x + temp.y;

	startMoving();
}

void EntityWithNavigation::nextWaypoint()
{
	waypoints.pop();

	if (waypoints.size() != 0)
	{
		Vec2 curWP = waypoints.top();
		Vec2 temp;

		temp.x = abs(pos.x - curWP.x);
		temp.y = abs(pos.y - curWP.y);

		distanceToWP = temp.x + temp.y;

		startMoving();
	} 
	else
	{
		finishedNavigation = true;
	}
}

void EntityWithNavigation::startMoving()
{
	velocity = 0;

	Vec2 curWP = waypoints.top();

	float speed = 50.0f;

	if (pos.x > curWP.x)
	{
		velocity.x = -speed;
		Utility::log(Utility::I, "Going left");
	}
	else if (pos.x < curWP.x)
	{
		velocity.x = speed;
		Utility::log(Utility::I, "Going right");
	}
	
	if (pos.y > curWP.y)
	{
		velocity.y = -speed;
		Utility::log(Utility::I, "Going up");
	}
	else if (pos.y < curWP.y)
	{
		velocity.y = speed;
		Utility::log(Utility::I, "Going down");
	}
}

void EntityWithNavigation::updateNav(float dt)
{
	if (!finishedNavigation)
	{
		Vec2 velDT = velocity * dt;
		float totalVel = abs(velDT.x + velDT.y);
		if (totalVel > distanceToWP)
		{
			pos = waypoints.top();
			/*
			if (abs(velDT.x) > 0.00f)
			{
				velocity.x = distanceToWP;
			}
			if (abs(velDT.y) > 0.00f)
			{
				velocity.y = distanceToWP;
			}

			pos += velocity;
			*/
		}
		else
		{
			pos += velocity * dt;
		}

		distanceToWP -= totalVel;

		

		if (distanceToWP <= 0.00f)
		{
			nextWaypoint();
		}
	}
}

void EntityWithNavigation::render()
{
	(*sprite).draw(pos, rotation);

	//Terrible way of doing this (regret using stack already)
	if (displayPath)
	{
		SDL_SetRenderDrawColor(sprite->getRenderer(), 0, 0, 255, 0);
		std::stack<Vec2> toDisplay = waypoints;
		while (!toDisplay.empty())
		{
			Vec2 curWP = toDisplay.top();
			SDL_Rect rect;
			rect.x = (int)curWP.x;
			rect.y = (int)curWP.y;
			rect.h = 32;
			rect.w = 32;
			SDL_RenderDrawRect(sprite->getRenderer(), &rect);
			toDisplay.pop();
		}
		SDL_SetRenderDrawColor(sprite->getRenderer(), 0, 0, 0, 0);
	}
}
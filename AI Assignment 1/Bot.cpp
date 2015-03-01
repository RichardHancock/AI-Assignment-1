#include "Bot.h"

Bot::Bot(Texture* sprite, Vec2 initPos, bool behaviourSetB, LevelManager* levels)
	: EntityWithNavigation(sprite, initPos), curBehaviour(Stopped), levels(levels),
	seenByPlayer(false), spottedOtherBot(false), useBehavioursB(behaviourSetB)
{

}

Bot::~Bot()
{

}

void Bot::update(float dt)
{
	seenByPlayer = lineOfSight(*levels->getLevel("Level 1"), curPlayerAABB);


	updateNav(dt);

	useBehavioursB ? behavioursB() : behavioursA();
}

void Bot::behavioursA()
{
	switch (curBehaviour)
	{
	case Stopped:
		
		if (seenByPlayer)
		{
			curBehaviour = PlaningToFlee;
		}

		break;

	case PlaningToFlee:

		generatePath(findHiddenTile());
		curBehaviour = Fleeing;

		break;

	case Fleeing:
		
		if (finishedNavigation)
		{
			curBehaviour = Stopped;
		}

		break;

	default:
		Utility::log(Utility::E, "Switched to an Unhandled Behaviour in behavioursA()");
	}
}

void Bot::behavioursB()
{
	switch (curBehaviour)
	{
	case Stopped:
		if (seenByPlayer)
		{
			Utility::log(Utility::I, "Bot B: switched to the \"PlanningToFlee\" behaviour");
			curBehaviour = PlaningToFlee;
		}
		else if (lineOfSight(*levels->getLevel("Level 1"), otherBotAABB)
			&& pos != Vec2(otherBotLastWPAABB.x, otherBotLastWPAABB.y))
		{
			generatePath(Vec2(otherBotLastWPAABB.x, otherBotLastWPAABB.y));
			Utility::log(Utility::I, "Bot B: switched to the \"Following\" behaviour");
			curBehaviour = Following;
		}
		break;
	case PlaningToFlee:

		generatePath(findHiddenTile());
		Utility::log(Utility::I, "Bot B: switched to the \"Fleeing\" behaviour");
		curBehaviour = Fleeing;

		break;

	case Fleeing:
		
		if (finishedNavigation)
		{
			Utility::log(Utility::I, "Bot B: switched to the \"Stopped\" behaviour");
			curBehaviour = Stopped;
		}

		break;

	case Following:
		if (seenByPlayer && !stop)
		{
			stop = true;
		}
		
		if (finishedNavigation)
		{
			Utility::log(Utility::I, "Bot B: switched to the \"Stopped\" behaviour");
			curBehaviour = Stopped;
		}

		break;

	default:
		Utility::log(Utility::E, "Switched to an Unhandled Behaviour in behavioursB()");
	}
}

bool Bot::lineOfSight(Level& level, SDL_Rect& other)
{
	Vec2 lineP1 = Utility::getRectCenter(getAABB());
	Vec2 lineP2 = Utility::getRectCenter(other);

	SDL_Rect areaToTest;
	SDL_UnionRect(&getAABB(), &other, &areaToTest);

	std::vector<Tile*> tilesToProcess = level.checkTiles(areaToTest);

	for (auto tile : tilesToProcess)
	{
		if (tile->blocksVision())
		{
			if (Utility::lineRectIntersection(lineP1, lineP2, tile->getAABB()))
			{
				return false;
			}
		}

	}
	return true;
}

bool Bot::lineOfSight(Level& level, SDL_Rect& a, SDL_Rect& b)
{
	Vec2 lineP1 = Utility::getRectCenter(a);
	Vec2 lineP2 = Utility::getRectCenter(b);

	SDL_Rect areaToTest;
	SDL_UnionRect(&a, &b, &areaToTest);

	std::vector<Tile*> tilesToProcess = level.checkTiles(areaToTest);

	for (auto tile : tilesToProcess)
	{
		if (tile->blocksVision())
		{
			if (Utility::lineRectIntersection(lineP1, lineP2, tile->getAABB()))
			{
				return false;
			}
		}

	}
	return true;
}


void Bot::updateOtherAABBs(SDL_Rect player, SDL_Rect bot, Vec2 botLastWP)
{
	curPlayerAABB = player;
	otherBotAABB = bot;
	otherBotLastWPAABB.x = botLastWP.x;
	otherBotLastWPAABB.y = botLastWP.y;
	otherBotLastWPAABB.h = otherBotLastWPAABB.w = 32;
}

Vec2 Bot::findHiddenTile()
{
	Vec2 result;

	bool hidden = false;
	Vec2 levelMax(levels->getLevel("Level 1")->tileCountW, levels->getLevel("Level 1")->tileCountH);

	while (!hidden)
	{
		//Utility::log(Utility::I, "Finding");
		Vec2 index;
		index.x = Utility::randomInt(0, levelMax.x - 1);
		index.y = Utility::randomInt(0, levelMax.y - 1);
		Tile* randomTile = levels->getLevel("Level 1")->getTileByIndex(index);

		if (randomTile == nullptr)
		{
			Vec2 tilePosition = index * 32.0f;
			SDL_Rect rect;
			rect.x = (int)tilePosition.x;
			rect.y = (int)tilePosition.y;
			rect.h = 32;
			rect.w = 32;
			if (!lineOfSight(*levels->getLevel("Level 1"), curPlayerAABB, rect))
			{
				result = tilePosition;
				hidden = true;
			}
		}
		else if (!randomTile->isCollidable())
		{
			if (!lineOfSight(*levels->getLevel("Level 1"), curPlayerAABB, randomTile->getAABB()))
			{
				result = index * 32.0f;
				hidden = true;
			}
		}
	}

	return result;
}
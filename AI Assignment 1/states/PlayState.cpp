#include "PlayState.h"
#include "HelpState.h"

PlayState::PlayState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Play State";
	///@todo Change Level manager to use the uint level parameter
	
	loadResources();

	//Load Level
	levels = new LevelManager("res/levels/Level 1.lvl", renderer);
	//player->setPos(levels->getLevel("Level 1")->getStartPos());

}

PlayState::~PlayState()
{
	delete player;
	delete botA;
	delete botB;

	delete playerSprite;
	delete botASprite;
	delete botBSprite;

	TTF_CloseFont(font);
	font = nullptr;
}

bool PlayState::eventHandler()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			player->eventKeyboard(e);
			break;
		case SDL_KEYUP:
			player->eventKeyboard(e);

			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				//Quit
				return false;
			}
			break;
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

void PlayState::update(float dt)
{
	Utility::Timer::update(dt);

	levels->getLevel("Level 1")->update(dt);
	
	player->updateVelocities(dt);

	collision(dt);
	if (lineOfSight(*levels->getLevel("Level 1"), *player, *botA))
	{
		Utility::log(Utility::I, "Seen");
	}

	player->update(dt);

	botA->update(dt);
	botB->update(dt);
}

void PlayState::render()
{
	levels->getLevel("Level 1")->render();
	
	player->render();

	botA->render();
	botB->render();

	//Show the line of sight
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	Vec2 playerPos(Utility::getRectCenter(player->getAABB()));
	Vec2 botAPos(Utility::getRectCenter(botA->getAABB()));
	SDL_RenderDrawLine(renderer, playerPos.x, playerPos.y, botAPos.x, botAPos.y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void PlayState::loadResources()
{
	std::string dir = "res/images/";
	playerSprite = new Texture(dir + "player.png", renderer);
	botASprite = new Texture(dir + "botA.png", renderer);
	botBSprite = new Texture(dir + "botB.png", renderer);

	player = new Player(playerSprite, Vec2(32, 32));
	botA = new Bot(botASprite, Vec2(576, 416));
	botB = new Bot(botBSprite, Vec2(32, 416));

	font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 32);
}

void PlayState::collision(float dt)
{
	Vec2 playerNewPos = player->getPos() + (player->getVelocity() * dt);

	SDL_Rect playerOld = player->getAABB();
	SDL_Rect playerNew = playerOld;

	playerNew.x = (int)playerNewPos.x;
	playerNew.y = (int)playerNewPos.y;

	SDL_Rect movementArea;
	SDL_UnionRect(&playerOld, &playerNew, &movementArea);

	std::vector<Tile*> tilesToProcess = levels->getLevel("Level 1")->checkTiles(movementArea);

	for (unsigned int i = 0; i < (int)tilesToProcess.size(); i++)
	{
		SDL_Rect tileAABB = tilesToProcess[i]->getAABB();
		if (SDL_HasIntersection(&tileAABB, &playerNew))
		{
			player->setVelocity(Vec2(0));
		}
	}
}

bool PlayState::lineOfSight(Level& level, Player& player, Bot& bot)
{
	Vec2 lineP1 = Utility::getRectCenter(player.getAABB());
	Vec2 lineP2 = Utility::getRectCenter(bot.getAABB());

	SDL_Rect areaToTest;
	SDL_UnionRect(&player.getAABB(), &bot.getAABB(), &areaToTest);

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
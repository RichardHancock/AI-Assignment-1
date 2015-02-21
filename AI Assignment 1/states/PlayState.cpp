#include "PlayState.h"
#include "GameOverState.h"

PlayState::PlayState(StateManager* manager, SDL_Renderer* renderer,
	unsigned int level)
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
	//worldCollisions(dt, *levels, *player);
	//enemyCollisions(*enemyManager, *player);

	player->update(dt);

}

void PlayState::render()
{
	levels->getLevel("Level 1")->render();
	
	player->render();
}

void PlayState::loadResources()
{
	std::string dir = "res/images/";
	
	//player = new Player(playerSprite, Vec2(360, 200), bulletSprite);

	font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 32);
}

/*
//I have no idea how this works anymore, it has quite irritating bugs that I cannot fix without scraping it entirely
void PlayState::worldCollisions(float dt, LevelManager &levels, Player &player)
{
	//Calculate the area that collisions will need to be calculated in.
	Vec2 playerNewPos = player.getPos() + (player.getVelocity() * dt);
	SDL_Rect playerOld = player.getAABB();
	SDL_Rect playerNew = playerOld;
	playerNew.x = (int)playerNewPos.x;
	playerNew.y = (int)playerNewPos.y;
	Vec2 playerNewCenter = Utility::getRectCenter(playerNew);
	SDL_Rect result;
	SDL_UnionRect(&playerOld, &playerNew, &result);

	std::vector<Tile*> tilesToProcess = levels.getLevel("Level 1")->checkTiles(result);

	bool stillLanded = false;

	for (int i = 0; i < (int)tilesToProcess.size(); i++)
	{
		SDL_Rect tileAABB = tilesToProcess[i]->getAABB();
		if (SDL_HasIntersection(&tileAABB, &playerNew))
		{
			//test x
			bool movingLeft = false;
			bool movingRight = false;
			bool movingUp = false;
			bool movingDown = false;

			if (player.getVelocity().x < 0.0f)
			{
				movingLeft = true;
				//player.setVelocity(Vec2(0, player.getVelocity().y));
			}
			else if (player.getVelocity().x > 0.0f)
			{
				movingRight = true;
			}

			bool hitLeft = false;
			bool hitRight = false;

			if (movingLeft)
			{
				if (tilesToProcess[i]->getPos().x + tileAABB.w >= playerNewPos.x)
				{
					player.setVelocity(Vec2(0, player.getVelocity().y));
					hitLeft = true;
				}
			}
			else if (movingRight)
			{
				if (tilesToProcess[i]->getPos().x <= playerNewPos.x + playerNew.w)
				{
					hitRight = true;
					player.setVelocity(Vec2(0, player.getVelocity().y));
				}
			}


			//test y
			if (player.getVelocity().y < 0.0f)
			{
				movingUp = true;
			}
			else if (player.getVelocity().y > 0.0f)
			{
				movingDown = true;
			}

			
			if (movingUp)
			{
				if (tilesToProcess[i]->getPos().y + tileAABB.h >= playerNewPos.y)
				{
					player.setVelocity(Vec2(player.getVelocity().x, 0));
				}
			}
			if (movingDown && !hitLeft && !hitRight)
			{
				if (tilesToProcess[i]->getPos().y <= playerNewPos.y + playerNew.h )
				{
					stillLanded = true;
					//if (!player.landed)
					//{
						player.setVelocity(Vec2(player.getVelocity().x, 0));
						float newYPos = (tilesToProcess[i]->getPos().y) - player.getDimensions().y;
						player.setPos(Vec2(player.getPos().x, newYPos));
						player.landed = true;
					//}
					
				}
			}
		}
	}

	player.landed = stillLanded;
}

void PlayState::enemyCollisions(EnemyManager &enemies, Player &player)
{
	//Checks for any collisions with enemies and then applies any damage to the player
	player.hit(enemies.playerCollision(&player.getAABB()));
}
*/
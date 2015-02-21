#include "Player.h"

Player::Player(Texture* texture, Vec2 pos)
	:EntityWithMotion(texture, pos, 0)
{
	movingLeft = false;
	movingRight = false;
}

Player::~Player()
{

}

void Player::eventKeyboard(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			movingLeft = true;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			movingRight = true;
			break;
		case SDLK_UP:
		case SDLK_w:
			movingUp = true;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			movingDown = true;
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			movingLeft = false;
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			movingRight = false;
			break;

		case SDLK_UP:
		case SDLK_w:
			movingUp = false;
			break;

		case SDLK_DOWN:
		case SDLK_s:
			movingDown = false;
			break;
		}
	}
}

void Player::update(float dt)
{
	velocity.x = 0;

	if (movingLeft &!movingRight)
	{
		// We are told to move left
		velocity.x = -150.0f;
	}
	if (movingRight &!movingLeft)
	{
		// We are told to move right
		velocity.x = 150.0f;
	}
	
	if (movingUp & !movingDown)
	{
		velocity.y = -150.0f;
	}
	if (movingDown & !movingUp)
	{
		velocity.y = 150.0f;
	}


	move(velocity * dt);
}
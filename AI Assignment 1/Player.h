#pragma once

#include "EntityWithMotion.h"

/**
@class Player
@brief The Player, his physics and input handling
*/
class Player : public EntityWithMotion
{
public:

	/**
	@brief Creates the Player
	@param Texture* - Players's sprite
	@param Vec2 - Starting position
	*/
	Player::Player(Texture* sprite, Vec2 initPos);

	~Player();

	/**
	@brief Updates the velocities of the player.

	This is so that collision detection knows where the player will be next and prevent collision.
	@param float - delta time
	*/
	void updateVelocities(float dt);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	void update(float);

	/**
	@brief Processes any Keyboard input relevant to the Player (Moving Left/right/spacebar)
	@param SDL_Event - The Event Data
	*/
	void eventKeyboard(SDL_Event&);

private:

	/// Is the player moving left
	bool movingLeft;

	/// Is the player moving right
	bool movingRight;

	/// Is the player moving up
	bool movingUp;

	/// Is the player moving down
	bool movingDown;
};
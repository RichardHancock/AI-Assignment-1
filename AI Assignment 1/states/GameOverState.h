#include <unordered_map>

#include "State.h"
#include "StateManager.h"
#include "../Vec2.h"
#include "../entities/Button.h"
#include "../Music.h"

#pragma once

/**
@class GameOverState
@brief A state shown when the game is over Win or Lose
*/
class GameOverState : public State
{
private:
	/// All the possible buttons on this menu
	enum MenuButton
	{
		Retry,
		MainMenu
	};
public:
	/**
	@brief Create the State
	@param StateManager* - Pointer to the current state manager
	@param SDL_Renderer* - Renderer
	@param bool - Was the game won
	@param int - Player's health remaining (irrelevant if game lost)
	*/
	GameOverState(StateManager* manager, SDL_Renderer* renderer, bool gameWon, int healthRemaining);

	~GameOverState();

	/**
	@brief Handles any events such as keyboard/mouse input
	*/
	bool eventHandler();

	/**
	@brief Update any internal values
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	void render();

private:
	///Was the game Won or Lost
	bool gameWon;

	///Text Message Congratulating or 'Shunning' the player
	Texture* message;

	//Message position
	Vec2 messagePos;

	/// Buttons background texture
	Texture* buttonTexture;

	/// The mouse's current position
	Vec2 mouse;

	/**
	@brief When the mouse is clicked this function checks which/if a button was pressed
	@return bool - If the game should continue, False to exit
	*/
	bool click();

	/// Array of all of the buttons in the menu
	std::unordered_map<MenuButton, Button*> buttons;

};
#include "State.h"
#include "StateManager.h"
#include "../Vec2.h"

#pragma once

/**
@class HelpState
@brief A Help screen displaying controls and other tips
*/
class HelpState : public State
{
public:
	/**
	@brief Create the State
	@param StateManager* - Pointer to the current state manager
	@param SDL_Renderer* - Renderer
	*/
	HelpState(StateManager* manager, SDL_Renderer* renderer);

	~HelpState();

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
	
};
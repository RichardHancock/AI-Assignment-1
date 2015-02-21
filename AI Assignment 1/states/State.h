#include <SDL.h>
#include <string>

#pragma once
class StateManager;

//Reference: Pete Allen's Game State Example

/**
@class State
@brief A game state that contains one screen of the game such as a Menu or the game itself
*/
class State
{
public:
	/**
	@brief Create the State
	@param StateManager* - Pointer to the current state manager
	@param SDL_Renderer* - Renderer
	*/
	State(StateManager* manager, SDL_Renderer* renderer);

	virtual ~State() {}

	/**
	@brief Handles any events such as keyboard/mouse input
	*/
	virtual bool eventHandler() = 0;

	/**
	@brief Update any internal values
	@param float - delta time
	*/
	virtual void update(float dt) = 0;

	/**
	@brief Render any sprites relevant to the state
	*/
	virtual void render() = 0;

	/**
	@brief Get this states name
	@return std::string - Name
	*/
	std::string getStateName() { return stateName; }
protected:
	///Pointer to state manager
	StateManager* stateManager;

	/// Renderer
	SDL_Renderer* renderer;

	///This states name
	std::string stateName;
};
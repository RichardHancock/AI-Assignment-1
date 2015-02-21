#include "HelpState.h"
#include "PlayState.h"

HelpState::HelpState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Help State";

	TTF_Font* font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 32);
	if (!font)
	{
		Utility::log(Utility::E, "TTF_OpenFont in GameOverState: " + std::string(TTF_GetError()));
	}

	SDL_Colour colour = { 255, 255, 255 };

	
	
	//message = new Texture(TTF_RenderText_Blended(font, textMessage.c_str(), colour),renderer);

	TTF_CloseFont(font);
	font = nullptr;
}

HelpState::~HelpState()
{
	
}

bool HelpState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				stateManager->prepareToChangeState();
				stateManager->popLastState();
			}
			break;
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

void HelpState::update(float dt)
{

}

void HelpState::render()
{
	
}

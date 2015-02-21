#include "GameOverState.h"
#include "MenuState.h"
#include "PlayState.h"

GameOverState::GameOverState(StateManager* manager, SDL_Renderer* renderer, bool gameWon, int healthRemaining)
	:State(manager, renderer), gameWon(gameWon)
{
	stateName = "Game Over State";
	mouse = { 0, 0 };

	TTF_Font* font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 32);
	if (!font)
	{
		Utility::log(Utility::E, "TTF_OpenFont in GameOverState: " + std::string(TTF_GetError()));
	}

	SDL_Colour colour = { 255, 255, 255 };

	std::string textMessage;
	textMessage = (gameWon ? 
		"You Win! With " + std::to_string(healthRemaining) + " Health Remaining!"
		: "You Lose!");
	
	message = new Texture(TTF_RenderText_Blended(font, textMessage.c_str(), colour),renderer);

	messagePos.x = (stateManager->WINDOW_WIDTH - message->getDimensions().x) / 2;
	messagePos.y = 200.0f;

	//Buttons
	buttonTexture = new Texture("res/images/button.png", renderer);
	
	float padding = 25.0f;
	Vec2 buttonPos = { (stateManager->WINDOW_WIDTH / 2) - padding - buttonTexture->getDimensions().x,
		stateManager->WINDOW_HEIGHT - buttonTexture->getDimensions().y - 50 };

	buttons[MainMenu] = new Button(buttonPos, buttonTexture, "Quit", font, colour, renderer);

	if (gameWon)
	{
		buttonPos.x += (padding * 2) + buttonTexture->getDimensions().x;
		buttons[Retry] = new Button(buttonPos, buttonTexture, "Retry", font, colour, renderer);
	}
	

	TTF_CloseFont(font);
	font = nullptr;
}

GameOverState::~GameOverState()
{
	delete buttonTexture;

	for (auto b : buttons)
	{
		delete b.second;
	}

	buttons.clear();

	delete message;
}

bool GameOverState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			mouse.x = (float)e.motion.x;
			mouse.y = (float)e.motion.y;
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) {
				return click();
			}
			break;

		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				stateManager->prepareToChangeState();
				stateManager->changeState(new MenuState(stateManager, renderer));
			}
			break;
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

void GameOverState::update(float dt)
{

}

void GameOverState::render()
{
	message->draw(messagePos);
	
	for (auto b : buttons)
	{
		b.second->render();
	}
}

bool GameOverState::click()
{
	for (auto b : buttons)
	{
		if (b.second->isClicked(mouse))
		{
			switch (b.first)
			{
			case Retry:
				stateManager->prepareToChangeState();
				stateManager->changeState(new PlayState(stateManager, renderer, 2));
				break;
			case MainMenu:
				stateManager->prepareToChangeState();
				stateManager->changeState(new MenuState(stateManager, renderer));
				break;
			default:
				Utility::log(Utility::W, "Unhandled menu button pressed");
				break;
			}

			//A button has been pressed, its pointless and dangerous to continue looping.
			break;
		}
	}

	return true;
}
#include "MenuState.h"
#include "StateStack.h"

MenuState::MenuState(const StateID InputStateId, StateStack& stateStack, bool isPauseMenu) :
State(InputStateId),
pauseMenu(isPauseMenu)
{
	float width = stateStack.windowWidth;
	float height = stateStack.windowHeight;
	float heightWithMargins = (height / 6) * 4;
}

MenuState::~MenuState()
{

}


int MenuState::update(const float deltaTime, sf::RenderWindow& window, sf::Event& event)
{
	int returnMessage = 0;
	unpauseTimerElapsed += deltaTime;
	buttonPressedTimerElapsed += deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (cursorPos > 0) cursorPos--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (cursorPos < 1) cursorPos++;
	}
	
	if (unpauseTimer < unpauseTimerElapsed)
	{
		if (pauseMenu && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			unpauseTimerElapsed = 0.f;
			returnMessage = (int)stateEvent::Unpause;
		}
	}

	if (buttonPressedTimerElapsed > buttonPressedTimer)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
		{
			buttonPressedTimerElapsed = 0.f;
			if (pauseMenu)
			{
				switch (cursorPos)
				{
				case (int)PauseMenuItems::Resume:
					returnMessage = (int)stateEvent::Unpause;
					break;

				case (int)PauseMenuItems::ReturnToMainMenu:
					returnMessage = (int)stateEvent::ReturnToMainMenu;
					break;
				}
			}
			else
			{
				switch (cursorPos)
				{
				case (int)MainMenuItems::Play:
					returnMessage = (int)stateEvent::GameState;
					break;

				case (int)MainMenuItems::QuitGame:
					returnMessage = (int)stateEvent::ExitGame;
					break;
				}
			}
		}
	}
	
	return returnMessage;
}

void MenuState::render(sf::RenderWindow& window)
{

}
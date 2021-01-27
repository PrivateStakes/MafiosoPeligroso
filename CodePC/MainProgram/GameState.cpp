#include "GameState.h"
#include "StateStack.h"
#include <iostream>

GameState::GameState(const StateID InputStateId, StateStack& stateStack) :
State(InputStateId)
{
	width = stateStack.windowWidth;
	height = stateStack.windowHeight;

}

GameState::~GameState()
{

}

int GameState::update(const float deltaTime)
{
	int returnMessage = 0;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;

	
	/*if (unpauseTimer < unpauseTimerElapsed)
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			unpauseTimerElapsed = 0.f;
			returnMessage = (int)stateEvent::PauseState;
		}
	}*/

	return returnMessage;
}

void GameState::render(sf::RenderWindow& window)
{

}
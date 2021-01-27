#include "EditorState.h"
#include "StateStack.h"
#include <iostream>

EditorState::EditorState(const StateID InputStateId, StateStack& stateStack) :
	State(InputStateId)
{
	width = stateStack.windowWidth;
	height = stateStack.windowHeight;

}

EditorState::~EditorState()
{

}

int EditorState::update(const float deltaTime)
{
	int returnMessage = 0;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;


	return returnMessage;
}

void EditorState::render(sf::RenderWindow& window)
{

}
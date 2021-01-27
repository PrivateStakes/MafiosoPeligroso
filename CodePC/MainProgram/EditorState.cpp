#include "EditorState.h"
#include "StateStack.h"
#include "Tile.h"
#include <iostream>

EditorState::EditorState(const StateID InputStateId, StateStack& stateStack) :
	State(InputStateId)
{
	width = stateStack.windowWidth;
	height = stateStack.windowHeight;

	for (int i = 0; i < tileSizeY; i++)
	{
		for (int j = 0; j < tileSizeX; j++)
		{
			tiles.push_back(new Tile("basic_tile.png"));
			tiles.back()->setPosition({ 
				(tiles.back()->getSprite().getGlobalBounds().width / 2) + ((j * tiles.back()->getSprite().getGlobalBounds().width)),
				(tiles.back()->getSprite().getGlobalBounds().height / 2) + ((i * tiles.back()->getSprite().getGlobalBounds().height)) });
		}
	}

	int temp = 0;
}

EditorState::~EditorState()
{

}

int EditorState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;

	//sf::Vector2f(mouse.getPosition(window));

	return returnMessage;
}

void EditorState::render(sf::RenderWindow& window)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->draw(window);
		//window.draw(tiles[i].get()->getSprite());
	}

	int temp = 0;
}
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
			tiles.push_back(make_unique<Tile>(Tile("basic_tile.png")));
			tiles.back().get()->setPosition({ 
				(tiles.back().get()->getSprite().getLocalBounds().height / 2) + ((i * 2 * tiles.back().get()->getSprite().getLocalBounds().height)),
				(tiles.back().get()->getSprite().getLocalBounds().height / 2) + ((j * 2 * tiles.back().get()->getSprite().getLocalBounds().width)) });
		}
	}

	int temp = 0;
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

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].get()->draw(window);
	}

	int temp = 0;
}
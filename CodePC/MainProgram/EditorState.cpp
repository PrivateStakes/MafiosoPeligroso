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
			grid.push_back(new Tile("basic_tile.png"));
			grid.back()->setPosition({ 
				(grid.back()->getSprite().getGlobalBounds().width / 2) + ((j * grid.back()->getSprite().getGlobalBounds().width)),
				(grid.back()->getSprite().getGlobalBounds().height / 2) + ((i * grid.back()->getSprite().getGlobalBounds().height)) });
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (size_t i = 0; i < grid.size(); i++)
		{
			if (grid[i]->getPosition().x - grid[i]->getSprite().getLocalBounds().width / 2 < mouse.getPosition(window).x &&
				grid[i]->getPosition().x + grid[i]->getSprite().getLocalBounds().width / 2 > mouse.getPosition(window).x)
			{
				if (grid[i]->getPosition().y - grid[i]->getSprite().getLocalBounds().height / 2 < mouse.getPosition(window).y &&
					grid[i]->getPosition().y + grid[i]->getSprite().getLocalBounds().height / 2 > mouse.getPosition(window).y)
				{
					//give console prompt on pos..
					bool hasSelectedOption = false;
					std::cout <<	"select an option:" << std::endl << 
									"[0] do nothing" << std::endl <<
									"[1] place wall" << std::endl <<
									"[2] place Enemy NPC spawnpoint" << std::endl <<
									"[3] place player spawnpoint" << std::endl <<
									"[--] ***" << std::endl;

					int input = 0;
					const int control_number_high = 3; //highest option

					//recieves input from editor (into var input) and validates it
					//comment this section and set input != 0 to paint
					while (!hasSelectedOption)
					{
						cin >> input;


						if (cin.fail() != true)
						{
							if (input >= 0 && input <= control_number_high) hasSelectedOption = true;
							else cout << "Pick a number FROM 0 to " << control_number_high << std::endl;
						}
						else cout << "Pick a NUMBER from 0 to " << control_number_high << std::endl;

						cin.clear();
						cin.ignore();
					}
					
					//add blue tile
					if (input != 0)
					{
						tiles.push_back(new Tile("basic_tile2.png"));
						tiles.back()->setPosition(grid[i]->getPosition());
					}
				}
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			if (tiles[i]->getPosition().x - tiles[i]->getSprite().getLocalBounds().width / 2 < mouse.getPosition(window).x &&
				tiles[i]->getPosition().x + tiles[i]->getSprite().getLocalBounds().width / 2 > mouse.getPosition(window).x)
			{
				if (tiles[i]->getPosition().y - tiles[i]->getSprite().getLocalBounds().height / 2 < mouse.getPosition(window).y &&
					tiles[i]->getPosition().y + tiles[i]->getSprite().getLocalBounds().height / 2 > mouse.getPosition(window).y)
				{
					//erase tile on
					tiles[i] = tiles.back();
					tiles.back() = nullptr;
					tiles.pop_back();
				}
			}
		}
	}
	

	return returnMessage;
}

void EditorState::render(sf::RenderWindow& window)
{
	for (int i = 0; i < grid.size(); i++)
	{
		grid[i]->draw(window);
		//window.draw(tiles[i].get()->getSprite());
	}
	
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->draw(window);
		//window.draw(tiles[i].get()->getSprite());
	}

	int temp = 0;
}
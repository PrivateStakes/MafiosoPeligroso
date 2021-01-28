#include "EditorState.h"
#include "StateStack.h"
#include "Tile.h"
#include <iostream>


EditorState::EditorState(const StateID InputStateId, StateStack& stateStack) :
	State(InputStateId),
	width(stateStack.windowWidth),
	height(stateStack.windowHeight)
{
	

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

	tileCache[TileSorts::wall] = std::make_unique<Tile>("basic_tile2.png");
	tileCache[TileSorts::breakable] = std::make_unique<Tile>("basic_tile2.png");
	tileCache[TileSorts::enemySpawnPoint] = std::make_unique<Tile>("basic_tile3.png");
	tileCache[TileSorts::friendlySpawnPoint] = std::make_unique<Tile>("basic_tile4.png");
	
	currentBrush = nullptr;
	currentBrush = tileCache.at(TileSorts::wall).get();

	std::cout << "Level editor loaded! Open palette by pressing 'G'" << std::endl;
}

EditorState::~EditorState()
{
	for (int i = 0; i < grid.size(); i++)
	{
		delete grid[i];
		grid[i] = nullptr;
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		delete tiles[i];
		tiles[i] = nullptr;
	}

	delete currentBrush;
	currentBrush = nullptr;
}

int EditorState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		grid[i]->update(deltaTime);
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->update(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		//give console prompt on pos..
		bool hasSelectedOption = false;
		std::cout <<	"select an option:" << std::endl << 
						"[0] do nothing" << std::endl <<
						"[1] wall" << std::endl <<
						"[2] Enemy NPC spawnpoint" << std::endl <<
						"[3] Friendly NPC spawnpoint" << std::endl <<
						"[--] ***" << std::endl;
		int input = 0;
		const int control_number_high = 3; //highest option

		//recieves input from editor (into var input) and validates it
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
		
		if (input != 0) currentBrush = tileCache.at((TileSorts)input).get();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i input = mouse.getPosition(window);
		bool otherTileOnPosition = false;
		for (int j = 0; j < tiles.size(); j++)
		{
			otherTileOnPosition = hasClickedOnTile(j, tiles, input);
		}

		if (!otherTileOnPosition)
		{
			for (size_t i = 0; i < grid.size(); i++)
			{
				if (hasClickedOnTile(i, grid, input))
				{
					tiles.push_back(new Tile(*currentBrush));
					tiles.back()->setPosition(grid[i]->getPosition());

					std::cout << tiles.size() << std::endl;
				}
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			if (hasClickedOnTile(i, tiles, mouse.getPosition(window)))
			{
				tiles[i] = tiles.back();
				tiles.back() = nullptr;
				tiles.pop_back();
			}
		}
	}

	return returnMessage;
}

bool EditorState::hasClickedOnTile(int i, std::vector<Tile*> inputTiles, sf::Vector2i mousePos)
{
	bool hasBeenClickedOn = false;

	if (inputTiles[i]->getPosition().x - (inputTiles[i]->getSprite().getLocalBounds().width * inputTiles[i]->getSprite().getScale().x) / 2 < mousePos.x &&
		inputTiles[i]->getPosition().x + (inputTiles[i]->getSprite().getLocalBounds().width * inputTiles[i]->getSprite().getScale().x) / 2 > mousePos.x)
	{
		if (inputTiles[i]->getPosition().y - (inputTiles[i]->getSprite().getLocalBounds().height * inputTiles[i]->getSprite().getScale().y) / 2 < mousePos.y &&
			inputTiles[i]->getPosition().y + (inputTiles[i]->getSprite().getLocalBounds().height * inputTiles[i]->getSprite().getScale().y) / 2 > mousePos.y)
		{
			hasBeenClickedOn = true;
		}
	}
	return hasBeenClickedOn;
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
}
#include "EditorState.h"
#include "StateStack.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>

EditorState::EditorState(const StateID InputStateId, StateStack& stateStack, Levels level) :
	State(InputStateId),
	width(stateStack.windowWidth),
	height(stateStack.windowHeight)
{
	bool loadEmptyLevel = true;
	currentFileName = levelDirectories[(int)level];

	std::ifstream loadStream;
	loadStream.open("../Saves/" + currentFileName);
	/*if (loadStream && loadStream.is_open())
	{
		std::string saveFileSize;
		loadStream >> saveFileSize;
		if (saveFileSize.size() > 0) loadEmptyLevel = false;
	}*/
	
	//Loads level data
	for (int i = 0; i < tileSizeY; i++)
	{
		std::vector<Tile*> tempGrid;
		std::vector<Tile*> emptyTiles;

		std::string tileRow;
		std::getline(loadStream, tileRow);

		for (int j = 0; j < tileSizeX; j++)
		{
			tempGrid.push_back(new Tile("basic_tile.png"));
			tempGrid.back()->setPosition({
				(tempGrid.back()->getSprite().getGlobalBounds().width / 2) + ((j * tempGrid.back()->getSprite().getGlobalBounds().width)),
				(tempGrid.back()->getSprite().getGlobalBounds().height / 2) + ((i * tempGrid.back()->getSprite().getGlobalBounds().height)) });
			
			emptyTiles.push_back(nullptr);
			if (!loadEmptyLevel) 
			{
				//NOTE: MUST READ FROM NEW LINE AFTER i = 0
				//int whichTile;
				//loadStream >> whichTile;

				if (!std::isblank(tileRow[j]) && tileRow[j] != ' ')
				{
					if (loadTile((TileSorts)(int)tileRow[j]) != nullptr)
					{
						emptyTiles[j] = new Tile(*loadTile((TileSorts)(int)tileRow[j]));
						emptyTiles[j]->setTileType((int)tileRow[j]);
					}
				}
			}
		}
		grid.push_back(tempGrid);
		tiles.push_back(emptyTiles);
	}
	loadStream.close();

	//Create palette chache
	{
		tileCache[TileSorts::wall] = std::make_unique<Tile>("basic_tile2.png");
		tileCache[TileSorts::wall].get()->setTileType((int)TileSorts::wall);

		tileCache[TileSorts::breakable] = std::make_unique<Tile>("basic_tile2.png");
		tileCache[TileSorts::breakable].get()->setTileType((int)TileSorts::breakable);

		tileCache[TileSorts::enemySpawnPoint] = std::make_unique<Tile>("basic_tile3.png");
		tileCache[TileSorts::enemySpawnPoint].get()->setTileType((int)TileSorts::enemySpawnPoint);

		tileCache[TileSorts::friendlySpawnPoint] = std::make_unique<Tile>("basic_tile4.png");
		tileCache[TileSorts::friendlySpawnPoint].get()->setTileType((int)TileSorts::friendlySpawnPoint);

		currentBrush = nullptr;
		currentBrush = tileCache.at(TileSorts::wall).get();
	}

	std::cout << "Level editor loaded! Open palette by pressing 'G'" << std::endl;
}

EditorState::~EditorState()
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			delete grid[i][j];
			grid[i][j] = nullptr;
		}
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			delete tiles[i][j];
			tiles[i][j] = nullptr;
		}
	}

	delete currentBrush;
	currentBrush = nullptr;
}

int EditorState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;

	//Update all tiles
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				grid[i][j]->update(deltaTime);
			}
		}

		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				if (tiles[i][j] != nullptr) tiles[i][j]->update(deltaTime);
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) returnMessage = (int)stateEvent::ExitGame;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		int input = consoleMenu(true, 3);
		if (input != 0) currentBrush = tileCache.at((TileSorts)input).get();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		int input = consoleMenu(false, 3);
		if (input != 0)
		{
			switch (input)
			{
			case 1:
				writeLevel();
				break;

			case 2:
				std::cout << "Write new level name:" << std::endl;
				cin >> currentFileName;
				std::cout << std::endl;
				writeLevel();
				break;
				
			case 3:
				//send new level name enum name
				returnMessage = (int)stateEvent::LaunchEditor;
				break;
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Used to check tile count
		/*int tileQuantity = 0;

		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				if (tiles[i][j] != nullptr)
				{
					tileQuantity++;
				}
			}
		}
		std::cout << tileQuantity << std::endl;
		*/

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (tiles[i][j] == nullptr && hasClickedOnTile(i, j, grid, mouse.getPosition(window)))
				{
					tiles[i][j] = new Tile(*currentBrush);
					tiles[i][j]->setPosition(grid[i][j]->getPosition());
				}
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				if (tiles[i][j] != nullptr)
				{
					if (hasClickedOnTile(i, j, tiles, mouse.getPosition(window)))
					{
						tiles[i][j] = tiles[i].back();
						tiles[i].back() = nullptr;
						//tiles[i].pop_back();
					}
				}
			}
		}
	}

	return returnMessage;
}

bool EditorState::hasClickedOnTile(int i, int j, std::vector <std::vector<Tile*>> inputTiles, sf::Vector2i mousePos)
{
	bool hasBeenClickedOn = false;

	if (inputTiles[i][j]->getPosition().x - (inputTiles[i][j]->getSprite().getLocalBounds().width * inputTiles[i][j]->getSprite().getScale().x) / 2 < mousePos.x &&
		inputTiles[i][j]->getPosition().x + (inputTiles[i][j]->getSprite().getLocalBounds().width * inputTiles[i][j]->getSprite().getScale().x) / 2 > mousePos.x)
	{
		if (inputTiles[i][j]->getPosition().y - (inputTiles[i][j]->getSprite().getLocalBounds().height * inputTiles[i][j]->getSprite().getScale().y) / 2 < mousePos.y &&
			inputTiles[i][j]->getPosition().y + (inputTiles[i][j]->getSprite().getLocalBounds().height * inputTiles[i][j]->getSprite().getScale().y) / 2 > mousePos.y)
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
		for (int j = 0; j < grid[i].size(); j++)
		{
			grid[i][j]->draw(window);
		}
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] != nullptr) tiles[i][j]->draw(window);
		}
	}
}

Tile* EditorState::loadTile(TileSorts whichTile)
{
	Tile* returnTile = nullptr;

	switch (whichTile)
	{
	case TileSorts::wall:
		returnTile = tileCache[TileSorts::wall].get();
		break;

	case TileSorts::breakable:
		returnTile = tileCache[TileSorts::breakable].get();
		break;

	case TileSorts::enemySpawnPoint:
		returnTile = tileCache[TileSorts::enemySpawnPoint].get();
		break;

	case TileSorts::friendlySpawnPoint:
		returnTile = tileCache[TileSorts::friendlySpawnPoint].get();
		break;

	default:
		returnTile = nullptr;
		break;
	}

	return returnTile;
}

int EditorState::consoleMenu(bool pallete, int highestNumber)
{
	bool hasSelectedOption = false;
	int input = 0;

	if (pallete)
	{
		std::cout << "select an option:" << std::endl <<
			"[0] do nothing" << std::endl <<
			"[1] wall" << std::endl <<
			"[2] Enemy NPC spawnpoint" << std::endl <<
			"[3] Friendly NPC spawnpoint" << std::endl <<
			"[--] ***" << std::endl;
	}
	else
	{
		std::cout << "select an option:" << std::endl <<
			"[0] do nothing" << std::endl <<
			"[1] save to current level" << std::endl <<
			"[2] save as new level" << std::endl <<
			"[3] load new level" << std::endl <<
			"[--] ***" << std::endl;
	}

	//recieves input from editor (into var input) and validates it
	while (!hasSelectedOption)
	{
		cin >> input;
		cout << std::endl;
		if (cin.fail() != true)
		{
			if (input >= 0 && input <= highestNumber) hasSelectedOption = true;
			else cout << "Pick a number FROM 0 to " << highestNumber << std::endl;
		}
		else cout << "Pick a NUMBER from 0 to " << highestNumber << std::endl;
		cin.clear();
		cin.ignore();
	}

	return input;
}

bool EditorState::writeLevel()
{
	bool saveSuccessful = true;

	std::ofstream saveStream;
	saveStream.open("../Saves/" + currentFileName, std::ofstream::out | std::ofstream::trunc);
	if (saveStream && saveStream.is_open())
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j <= tiles.size(); j++)
			{
				if (j == tiles.size()) saveStream << std::endl;
				else if(tiles[i][j] != nullptr) saveStream << tiles[i][j]->getTileType();
			}
		}
	}
	else saveSuccessful = false;

	saveStream.close();

	return saveSuccessful;
}
#include "EditorState.h"
#include "StateStack.h"
#include "Tile.h"
#include "Bullet.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

int inputChecker(int high);
char intToLetter(int input);

//CONTROLS:
/*
- H: Start Editor
- J: Save menu
- L: Exit
- G: Palette
*/

EditorState::EditorState(const StateID InputStateId, StateStack& stateStack, std::string* level) :
	State(InputStateId),
	width(stateStack.windowWidth),
	height(stateStack.windowHeight),
	currentFileName(level)
{
	camera.setCenter(0, 0);
	camera.setSize(width, height);

	bool loadEmptyLevel = true;

	//Create palette chache
	for (int i = 1; i < (int)TileSorts::COUNT; i++)
	{
		tileCache[(TileSorts)i] = std::make_unique<Tile>(tileTextures[i - 1]);
		tileCache[(TileSorts)i].get()->setTileType(intToLetter(i));
	}
	currentBrush = nullptr;
	currentBrush = tileCache.at(TileSorts::wall).get();

	std::ifstream loadStream;
	loadStream.open("../Saves/saveFiles.txt");
	if (loadStream && loadStream.is_open())
	{
		int i = 0;
		while (1)
		{
			std::string tileRow = "";
			getline(loadStream, tileRow);
			if (tileRow.size() > 0)
			{
				levels.push_back(tileRow);
				std::cout << levels[i] << std::endl;
			}
			else break;
			i++;
		}
	}
	loadStream.close();

	//Loads level data
	for (int i = 0; i < tileSizeY; i++)
	{
		std::vector<Tile*> tempGrid;
		std::vector<Tile*> tempTiles;

		std::string tileRow = "";
		loadStream >> tileRow;
		if (tileRow.size() > 0) loadEmptyLevel = false;
		loadStream.ignore();

		for (int j = 0; j < tileSizeX; j++)
		{
			tempGrid.push_back(new Tile("basic_tile.png"));
			tempGrid.back()->setPosition({
				(tempGrid.back()->getSprite().getGlobalBounds().width / 2) + ((j * tempGrid.back()->getSprite().getGlobalBounds().width)),
				(tempGrid.back()->getSprite().getGlobalBounds().height / 2) + ((i * tempGrid.back()->getSprite().getGlobalBounds().height)) });
			
			tempTiles.push_back(nullptr);
			if (!loadEmptyLevel) 
			{
				std::locale loc;
				if (!std::isblank(tileRow[j], loc))
				{
					char saveFileInformation = (char)tileRow[j] - 48;

					if (saveFileInformation != -99 && saveFileInformation != '\0' && loadTile((TileSorts)(saveFileInformation - 48)) != nullptr)
					{
						tempTiles[j] = new Tile(*loadTile((TileSorts)(saveFileInformation - 48)));
						tempTiles[j]->setPosition(tempGrid[j]->getPosition());
					}
				}
			}
		}
		grid.push_back(tempGrid);
		tiles.push_back(tempTiles);
	}
	loadStream.close();

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

	currentFileName = nullptr;
}

int EditorState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;

	//---[Player]---
	player.rotateSprite((sf::Vector2f)mouse.getPosition());
	player.move();
	camera.move(player.getInputDirection());
	//--------------

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
				std::cin >> *currentFileName;
				std::cout << std::endl;
				writeLevel();
				break;
				
			case 3:
				std::cout << "Which level would you like to edit?" << std::endl;
				/*for (int i = 0; i < (int)Levels::COUNT; i++)
				{
					std::cout << levelDirectories[i] << std::endl;
				}

				//send new level name enum name
				stateStackCurrentLevel = new Levels((Levels)inputChecker((int)Levels::COUNT));*/
				returnMessage = (int)stateEvent::LaunchEditor;
				break;
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (tiles[i][j] == nullptr && hasClickedOnTile(i, j, grid, mouse.getPosition(window), window))
				{
					tiles[i][j] = new Tile(*currentBrush);
					tiles[i][j]->setPosition(grid[i][j]->getPosition());
				}
				else if (
				(currentBrush->getTileType() == intToLetter((int)TileSorts::enemySpawnPoint) || currentBrush->getTileType() == intToLetter((int)TileSorts::friendlySpawnPoint)) &&
				hasClickedOnTile(i, j, grid, mouse.getPosition(window), window))
				{
					bool do_not_place = false;

					if (tiles[i][j] != nullptr)
					{
						if (tiles[i][j]->getTileType() == intToLetter((int)TileSorts::enemySpawnPoint) || tiles[i][j]->getTileType() == intToLetter((int)TileSorts::friendlySpawnPoint))
						{
							do_not_place = true;
						}
					}
					
					if (!do_not_place)
					{
						tiles[i][j] = new Tile(*currentBrush);
						tiles[i][j]->setPosition(grid[i][j]->getPosition());
					}
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
					if (hasClickedOnTile(i, j, tiles, mouse.getPosition(window), window))
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

bool EditorState::hasClickedOnTile(int i, int j, std::vector <std::vector<Tile*>> inputTiles, sf::Vector2i mousePos, sf::RenderWindow& window)
{
	bool hasBeenClickedOn = false;
	sf::Vector2i tilePos_high = window.mapCoordsToPixel(sf::Vector2f(
		(inputTiles[i][j]->getPosition().x - (inputTiles[i][j]->getSprite().getLocalBounds().width * inputTiles[i][j]->getSprite().getScale().x) / 2),
		(inputTiles[i][j]->getPosition().y - (inputTiles[i][j]->getSprite().getLocalBounds().height * inputTiles[i][j]->getSprite().getScale().y) / 2)));

	sf::Vector2i tilePos_low = window.mapCoordsToPixel(sf::Vector2f(
		(inputTiles[i][j]->getPosition().x + (inputTiles[i][j]->getSprite().getLocalBounds().width * inputTiles[i][j]->getSprite().getScale().x) / 2),
		(inputTiles[i][j]->getPosition().y + (inputTiles[i][j]->getSprite().getLocalBounds().height * inputTiles[i][j]->getSprite().getScale().y) / 2)));


	if (tilePos_high.x < mousePos.x && tilePos_low.x > mousePos.x)
	{
		if (tilePos_high.y < mousePos.y && tilePos_low.y > mousePos.y)
		{
			hasBeenClickedOn = true;
		}
	}

	return hasBeenClickedOn;
}

void EditorState::render(sf::RenderWindow& window)
{
	if (!do_once)
	{
		window.setMouseCursorVisible(true);
		do_once = true;
	}

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

	window.draw(player);
	window.setView(camera);
}

Tile* EditorState::loadTile(TileSorts whichTile)
{
	Tile* returnTile = nullptr;

	switch (whichTile)
	{
	case TileSorts::wall:
		returnTile = new Tile(*tileCache[TileSorts::wall].get());
		break;

	case TileSorts::breakable:
		returnTile = new Tile(*tileCache[TileSorts::breakable].get());
		break;

	case TileSorts::enemySpawnPoint:
		returnTile = new Tile(*tileCache[TileSorts::enemySpawnPoint].get());
		break;

	case TileSorts::friendlySpawnPoint:
		returnTile = new Tile(*tileCache[TileSorts::friendlySpawnPoint].get());
		break;
	}

	if (returnTile != nullptr)
	{

	}
	returnTile->setTileType(intToLetter((int)whichTile));
	return returnTile;
}

char intToLetter(int input)
{
	char returnValue;
	switch (input)
	{
	case (int)TileSorts::wall:
		returnValue = 'a';
		break;

	case (int)TileSorts::breakable:
		returnValue = 'b';
		break;

	case (int)TileSorts::enemySpawnPoint:
		returnValue = 'c';
		break;

	case (int)TileSorts::friendlySpawnPoint:
		returnValue = 'd';
		break;

	default:
		returnValue = '0';
	}

	return returnValue;
}

int EditorState::consoleMenu(bool pallete, int highestNumber)
{
	int input = 0;

	if (pallete)
	{
		std::cout << "select an option:" << std::endl <<
					 "[0] do nothing" << std::endl;

		for (int i = 0; i < ((int)TileSorts::COUNT - 1); i++)
		{
			std::cout << "[" << (i + 1) << "] " << tileTextures[i] << std::endl;
		}
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

	input = inputChecker(highestNumber);
	return input;
}

int inputChecker(int highestNumber)
{
	//recieves input from editor (into var input) and validates it
	int input;
	bool hasSelectedOption = false;
	while (!hasSelectedOption)
	{
		std::cin >> input;
		std::cout << std::endl;
		if (std::cin.fail() != true)
		{
			if (input >= 0 && input <= highestNumber) hasSelectedOption = true;
			else std::cout << "Pick a number FROM 0 to " << highestNumber << std::endl;
		}
		else std::cout << "Pick a NUMBER from 0 to " << highestNumber << std::endl;
		std::cin.clear();
		std::cin.ignore();
	}

	return input;
}

bool EditorState::writeLevel()
{
	bool saveSuccessful = true;

	std::ofstream saveStream;
	saveStream.open(currentDirectory + *currentFileName + ".txt", std::ofstream::out | std::ofstream::trunc);
	if (saveStream && saveStream.is_open())
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j <= tiles[i].size(); j++)
			{
				if (j == tiles[i].size()) saveStream << std::endl;
				else if (tiles[i][j] != nullptr)
				{
					if (tiles[i][j]->getTileType() != '\0') saveStream << tiles[i][j]->getTileType();
				}
				else saveStream << '0';
			}
		}
	}
	else saveSuccessful = false;
	saveStream.close();

	saveStream.open("../Saves/save.txt", std::ofstream::out | std::ofstream::trunc);
	if (saveStream && saveStream.is_open())
	{
		bool change_saveFiles = false;
		for (int i = 0; i < levels.size(); i++)
		{
			if ((*currentFileName + ".txt") == levels[i])
			{
				change_saveFiles = true;
			}
			
			saveStream << levels[i];
		}

		if (!change_saveFiles)
		{
			levels.push_back((*currentFileName + ".txt"));
			saveStream << (*currentFileName + ".txt");
		}
	}
	saveStream.close();

	return saveSuccessful;
}
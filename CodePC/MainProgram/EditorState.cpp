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

- Saving/Loading:
	Write 'full name of file'.txt
- Adding more tiles:
	* Add tile to Enum 'TileSorts'							(make sure COUNT is last!)
	* Add texture of tile to 'tileTextures'					(make sure you increase the array size)
	* Assign tile a char in function/method 'intToLetter	(*see local method format and repeat*)
- Manually adding levels:
	* Add level to Bin/Saves
	* Add level name to saveFiles.txt						(in Bin/Saves)
*/

EditorState::EditorState(const StateID InputStateId, StateStack& stateStack, std::string* level) :
	State(InputStateId),
	width(stateStack.windowWidth),
	height(stateStack.windowHeight),
	currentFileName(level)
{
	camera.setCenter(0, 0);
	camera.setSize(width, height);

	//Create palette chache
	for (int i = 1; i < (int)TileSorts::COUNT; i++)
	{
		tileCache[(TileSorts)i] = std::make_unique<Tile>(tileTextures[i - 1]);
		tileCache[(TileSorts)i].get()->setTileType(intToLetter(i));
	}
	currentBrush = nullptr;
	currentBrush = tileCache.at(TileSorts::wall).get();

	std::ifstream loadStream;
	loadStream.open(currentDirectory + "saveFiles.txt");
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
				//printf("%s\n", levels[i]);
			}
			else break;
			i++;
		}
	}
	loadStream.close();

	bool loadEmptyLevel = true;
	loadStream.open(currentDirectory + *currentFileName);
	if (loadStream && loadStream.is_open()) loadEmptyLevel = false;

	//Loads level data
	for (int i = 0; i < tileSizeY; i++)
	{
		std::vector<Tile*>* tempGrid = new std::vector<Tile*>;
		std::vector<Tile*>* tempTiles = new std::vector<Tile*>;

		std::string tileRow = "";
		loadStream >> tileRow;
		if (tileRow.size() > 0) loadEmptyLevel = false;
		loadStream.ignore();

		for (int j = 0; j < tileSizeX; j++)
		{
			tempGrid->push_back(new Tile("basic_tile.png"));
			tempGrid->back()->setPosition({
				(tempGrid->back()->getSprite().getGlobalBounds().width / 2) + ((j * tempGrid->back()->getSprite().getGlobalBounds().width)),
				(tempGrid->back()->getSprite().getGlobalBounds().height / 2) + ((i * tempGrid->back()->getSprite().getGlobalBounds().height)) });
			
			tempTiles->push_back(nullptr);
			if (!loadEmptyLevel) 
			{
				std::locale loc;
				if (!std::isblank(tileRow[j], loc))
				{
					char saveFileInformation = (char)tileRow[j] - 48;

					if (saveFileInformation != -99 && saveFileInformation != '\0' && loadTile((TileSorts)(saveFileInformation - 48)) != nullptr)
					{
						tempTiles->at(j) = new Tile(*loadTile((TileSorts)(saveFileInformation - 48)));
						tempTiles->at(j)->setPosition(tempGrid->at(j)->getPosition());
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
		for (int j = 0; j < grid[i]->size(); j++)
		{
			if (grid[i]->at(j) != nullptr)
			{
				delete grid[i]->at(j);
				grid[i]->at(j) = nullptr;
			}
			
		}
		grid[i]->clear();
	}
	grid.clear();

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr)
			{
				delete tiles[i]->at(j);
				tiles[i]->at(j) = nullptr;
			}
		}
		tiles[i]->clear();
	}
	tiles.clear();

	currentBrush = nullptr;
	tileCache.clear();

	currentFileName = nullptr;
}

int EditorState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;

	//---[Player]---
	player.rotateSprite((sf::Vector2f)mouse.getPosition());
	player.move();
	camera.move(player.getInputDirection());
	camera.setCenter(player.getPosition());
	//--------------

	//Update all tiles
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i]->size(); j++)
		{
			grid[i]->at(j)->update(deltaTime);
		}
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr) tiles[i]->at(j)->update(deltaTime);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) returnMessage = (int)stateEvent::ExitGame;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		int input = consoleMenu(true, (int)TileSorts::COUNT -1);
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
				for (int i = 0; i < levels.size(); i++)
				{
					std::cout << levels[i] << std::endl;
				}

				std::cin >> *currentFileName;
				returnMessage = (int)stateEvent::LaunchEditor;
				break;
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i]->size(); j++)
			{
				if (tiles[i] != nullptr)
				{
					if (tiles[i]->at(j) == nullptr && hasClickedOnTile(i, j, grid, mouse.getPosition(window), window))
					{
						tiles[i]->at(j) = new Tile(*currentBrush);
						tiles[i]->at(j)->setPosition(grid[i]->at(j)->getPosition());
					}
					else if (
						(currentBrush->getTileType() == intToLetter((int)TileSorts::enemySpawnPoint) || currentBrush->getTileType() == intToLetter((int)TileSorts::friendlySpawnPoint)) &&
						hasClickedOnTile(i, j, grid, mouse.getPosition(window), window))
					{
						bool do_not_place = false;

						if (tiles[i]->at(j) != nullptr)
						{
							if (tiles[i]->at(j)->getTileType() == intToLetter((int)TileSorts::enemySpawnPoint) || tiles[i]->at(j)->getTileType() == intToLetter((int)TileSorts::friendlySpawnPoint))
							{
								do_not_place = true;
							}
						}

						if (!do_not_place)
						{
							tiles[i]->at(j) = new Tile(*currentBrush);
							tiles[i]->at(j)->setPosition(grid[i]->at(j)->getPosition());
						}
					}
				}
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i]->size(); j++)
			{
				if (tiles[i]->at(j) != nullptr)
				{
					if (hasClickedOnTile(i, j, tiles, mouse.getPosition(window), window))
					{
						tiles[i]->at(j) = tiles[i]->back();
						tiles[i]->back() = nullptr;
					}
				}
			}
		}
	}

	return returnMessage;
}

bool EditorState::hasClickedOnTile(int i, int j, std::vector <std::vector<Tile*>*> inputTiles, sf::Vector2i mousePos, sf::RenderWindow& window)
{
	bool hasBeenClickedOn = false;
	sf::Vector2i tilePos_high = window.mapCoordsToPixel(sf::Vector2f(
		(inputTiles[i]->at(j)->getPosition().x  - (inputTiles[i]->at(j)->getSprite().getLocalBounds().width  * inputTiles[i]->at(j)->getSprite().getScale().x) / 2),
		(inputTiles[i]->at(j)->getPosition().y - (inputTiles[i]->at(j)->getSprite().getLocalBounds().height * inputTiles[i]->at(j)->getSprite().getScale().y) / 2)));

	sf::Vector2i tilePos_low = window.mapCoordsToPixel(sf::Vector2f(
		(inputTiles[i]->at(j)->getPosition().x + (inputTiles[i]->at(j)->getSprite().getLocalBounds().width  * inputTiles[i]->at(j)->getSprite().getScale().x) / 2),
		(inputTiles[i]->at(j)->getPosition().y + (inputTiles[i]->at(j)->getSprite().getLocalBounds().height * inputTiles[i]->at(j)->getSprite().getScale().y) / 2)));


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
		for (int j = 0; j < grid[i]->size(); j++)
		{
			grid[i]->at(j)->draw(window);
		}
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr) tiles[i]->at(j)->draw(window);
		}
	}

	window.draw(player);
	window.setView(camera);
}

Tile* EditorState::loadTile(TileSorts whichTile)
{
	Tile* returnTile = nullptr;

	returnTile = new Tile(*tileCache[whichTile].get());
	if (returnTile == nullptr) returnTile = new Tile(*tileCache[TileSorts::wall].get());

	returnTile->setTileType(intToLetter((int)whichTile));
	return returnTile;
}

/*std::string* EditorState::getTileTexturePaths()
{
	return tileTextures;
}

int EditorState::getTileTextureQuantity()
{
	return textureQuantity;
}*/

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

	case (int)TileSorts::floor:
		returnValue = 'e';
		break;

	case (int)TileSorts::brakeableWall:
		returnValue = 'f';
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
	saveStream.open(currentDirectory + *currentFileName, std::ofstream::out | std::ofstream::trunc);
	if (saveStream && saveStream.is_open())
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j <= tiles[i]->size(); j++)
			{
				if (j == tiles[i]->size()) saveStream << std::endl;
				else if (tiles[i]->at(j) != nullptr)
				{
					if (tiles[i]->at(j)->getTileType() != '\0') saveStream << tiles[i]->at(j)->getTileType();
				}
				else saveStream << '0';
			}
		}
	}
	else saveSuccessful = false;
	saveStream.close();

	saveStream.open("../Saves/saveFiles.txt", std::ofstream::out | std::ofstream::trunc);
	if (saveStream && saveStream.is_open())
	{
		bool change_saveFiles = false;
		for (int i = 0; i < levels.size(); i++)
		{
			if ((*currentFileName) == levels[i])
			{
				change_saveFiles = true;
			}
			
			saveStream << levels[i] << std::endl;;
		}

		if (!change_saveFiles)
		{
			levels.push_back((*currentFileName));
			saveStream << (*currentFileName);
		}
	}
	saveStream.close();

	return saveSuccessful;
}
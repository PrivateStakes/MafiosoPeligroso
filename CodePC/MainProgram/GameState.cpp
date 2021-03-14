#include "GameState.h"
#include "StateStack.h"
#include "CollissionMan.h"
#include "Tile.h"
#include "EditorState.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

GameState::GameState(const StateID InputStateId, StateStack& stateStack, std::string* level, std::vector<Soldier*>& soliderHierarchy) :
State(InputStateId),
width(stateStack.windowWidth),
height(stateStack.windowHeight),
currentFileName(level)
{
	camera.setCenter(0, 0);
	//camera.setSize(1280, 720);
	camera.setSize(width, height);

	for (int i = 0; i < soliderHierarchy.size(); i++)
	{
		soldiers.push_back(soliderHierarchy[i]);
	}
	
	player = soldiers[0];
	float temp = 0.f;
	texture.loadFromFile("../Images/cursor.png");
	cursor.setTexture(texture);
	cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
	cursor.setScale(2, 2);

	amountOfBullets = 0;
	amountOfEnemySpawnPoints = 0;
	cap = 32;
	enemySpawnPointArray = new sf::Vector2f*[cap];

	std::ifstream loadStream;
	loadStream.open(currentDirectory + *currentFileName);
	if (!loadStream && loadStream.is_open()) assert(true == true && "No level present on location!");

	EditorState tempEditor(InputStateId, stateStack, level);

	for (int i = 0; i < soldiers.size(); i++)
	{
		soldiers[i]->setWeapon(weaponFactory.buildWeapon(GunType::pistol));
	}

	//Loads level data
	for (int i = 0; i < tileSizeY; i++)
	{
		std::vector<Tile*> tempGrid;
		std::vector<Tile*>* tempTiles = new std::vector<Tile*>;
		std::vector<Tile*>* tempFloor = new std::vector<Tile*>;

		std::string tileRow = "";
		loadStream >> tileRow;
		loadStream.ignore();

		for (int j = 0; j < tileSizeX; j++)
		{
			tempGrid.push_back(new Tile("basic_tile.png"));
			tempGrid.back()->setPosition({
				(tempGrid.back()->getSprite().getGlobalBounds().width / 2) + ((j * tempGrid.back()->getSprite().getGlobalBounds().width)),
				(tempGrid.back()->getSprite().getGlobalBounds().height / 2) + ((i * tempGrid.back()->getSprite().getGlobalBounds().height)) });

			tempTiles->push_back(nullptr);
			tempFloor->push_back(nullptr);
			std::locale loc;
			if (!std::isblank(tileRow[j], loc))
			{
				char saveFileInformation = (char)tileRow[j] - 48;

				if (saveFileInformation != -99 && saveFileInformation != '\0' && tempEditor.loadTile((TileSorts)(saveFileInformation - 48)) != nullptr)
				{
					bool addTile = true;
					Tile tempTile = *tempEditor.loadTile((TileSorts)(saveFileInformation - 48));

					if (tempTile.getTileType() == 'c')
					{
						enemySpawnPointArray[amountOfEnemySpawnPoints++] = new sf::Vector2f(tempGrid[j]->getPosition());	//if the game crashes because of this, change to std::vector
						if (amountOfEnemySpawnPoints == cap)
						{
							addTile = false;

							cap += 3;
							sf::Vector2f** temp = new sf::Vector2f * [cap];
							for (int i = 0; i < amountOfEnemySpawnPoints; i++)
							{
								temp[i] = enemySpawnPointArray[i];
							}

							delete[] enemySpawnPointArray;
							enemySpawnPointArray = temp;
							temp = nullptr;
						}
					}
					else if (tempTile.getTileType() == 'e')
					{
						addTile = false;

						tempFloor->at(j) = new Tile(tempTile.getTexturePath());
						tempFloor->at(j)->setTileType(tempTile.getTileType());
						tempFloor->at(j)->setPosition(tempGrid[j]->getPosition());
					}

					if (addTile)
					{
						tempTiles->at(j) = new Tile(tempTile.getTexturePath());
						tempTiles->at(j)->setTileType(tempTile.getTileType());
						tempTiles->at(j)->setPosition(tempGrid[j]->getPosition());
					}
				}
			}
		}
		tiles.push_back(tempTiles);
		floor.push_back(tempFloor);

		for (int k = 0; k < tempGrid.size(); k++)
		{
			delete tempGrid[k];
			tempGrid[k] = nullptr;
		}
	}
	loadStream.close();
	enemies = new Soldier[amountOfEnemySpawnPoints];

	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		enemies[i].setPosition(*enemySpawnPointArray[i]);
		stateStack.setID(stateStack.getID() + 1);
		enemies[i].setID(stateStack.getID());
		enemies[i].setWeapon(weaponFactory.buildWeapon(GunType::pistol));
	}
}

GameState::~GameState()
{
	currentFileName = nullptr;
	delete[] enemies;
	
	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		delete enemySpawnPointArray[i];
		enemySpawnPointArray[i] = nullptr;
	}
	delete[] enemySpawnPointArray;

	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
		bullets[i] = nullptr;
	}
	bullets.clear();

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

	for (int i = 0; i < floor.size(); i++)
	{
		for (int j = 0; j < floor[i]->size(); j++)
		{
			if (floor[i]->at(j) != nullptr && floor[i]->at(j)->getTileType() == 'e')
			{
				delete floor[i]->at(j);
				floor[i]->at(j) = nullptr;
			}
		}
		floor[i]->clear();
	}
	floor.clear();

	while (soldiers.size() > 0)
	{
		delete soldiers[soldiers.size() - 1];
		soldiers[soldiers.size() - 1] = nullptr;
		soldiers.pop_back();
	}
	soldiers.clear();
	player = nullptr;
}

int GameState::backendUpdate()
{
	for (int k = 0; k < amountOfEnemySpawnPoints; k++)
	{
		int x;
		int y;

		int xOrigin;
		int yOrigin;

		for (int i = 0; i < floor.size(); i++)
		{
			for (int j = 0; j < floor[i]->size(); j++)
			{
				if (CollissionMan().intersectRectPoint(*floor[i]->at(j), enemies[amountOfEnemySpawnPoints].getPosition()))
				{
					x = i;
					y = j;
				}
			}
		}

		xOrigin = x;
		yOrigin = y;
		
		while (1)
		{
			int tempX;
			int tempY;
			unsigned int shortestDistance = 0 - 1;

			//each connection
			if (!floor[x + 1]->at(y + 1)->getVisitedByAlgorithm() | floor[x + 1]->at(y + 1)->getTravelDistance() <= shortestDistance)
			{
				floor[x + 1]->at(y + 1)->setTravelDistance(floor[x]->at(y)->getTravelDistance() + 1);
				floor[x + 1]->at(y + 1)->setVisitedByAlgorithm(true);

				shortestDistance = floor[x + 1]->at(y + 1)->getTravelDistance();
				tempX = x + 1;
				tempY = y + 1;
			}

			if (!floor[x + 1]->at(y - 1)->getVisitedByAlgorithm() | floor[x + 1]->at(y - 1)->getTravelDistance() <= shortestDistance)
			{
				floor[x + 1]->at(y - 1)->setTravelDistance(floor[x]->at(y)->getTravelDistance() + 1);
				floor[x + 1]->at(y - 1)->setVisitedByAlgorithm(true);

				shortestDistance = floor[x + 1]->at(y - 1)->getTravelDistance();
				tempX = x + 1;
				tempY = y - 1;
			}

			if (!floor[x - 1]->at(y - 1)->getVisitedByAlgorithm() | floor[x - 1]->at(y - 1)->getTravelDistance() <= shortestDistance)
			{
				floor[x - 1]->at(y - 1)->setTravelDistance(floor[x]->at(y)->getTravelDistance() + 1);
				floor[x - 1]->at(y - 1)->setVisitedByAlgorithm(true);

				shortestDistance = floor[x - 1]->at(y - 1)->getTravelDistance();
				tempX = x - 1;
				tempY = y - 1;
			}

			if (!floor[x - 1]->at(y + 1)->getVisitedByAlgorithm() | floor[x - 1]->at(y + 1)->getTravelDistance() <= shortestDistance)
			{
				floor[x - 1]->at(y + 1)->setTravelDistance(floor[x]->at(y)->getTravelDistance() + 1);
				floor[x - 1]->at(y + 1)->setVisitedByAlgorithm(true);

				shortestDistance = floor[x - 1]->at(y + 1)->getTravelDistance();
				tempX = x - 1;
				tempY = y + 1;
			}

			x = tempX;
			y = tempY;
		}
	}

	return 0;
}

int GameState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) returnMessage = (int)stateEvent::LaunchEditor;

	//Update all tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr) tiles[i]->at(j)->update(deltaTime);
		}
	}

	if (mouseVisability)
	{
		window.setMouseCursorVisible(false);
		mouseVisability = false;
	}

	for (int i = 1; i < soldiers.size(); i++)
	{
		soldiers[i]->move();
	}

	player->rotateSprite(cursor.getPosition());

	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		//enemies[i].move();
		enemies[i].rotateSprite(player->getPosition());
		/*if (enemies[i].isAbleToShoot())
		{
			bullets[amountOfBullets++] = new Bullet(enemies[i].shoot((player->getPosition() - enemies[i].getPosition())));
		}*/
	}

	collideCheck = false;

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr)
			{
				if (CollissionMan().intersectCircRect(*player, *tiles[i]->at(j), 'a'))
				{
					collideCheck = true;
				}
				for (int k = 0; k < bullets.size(); k++)
				{
					if (CollissionMan().intersectCircRect(*bullets[k], *tiles[i]->at(j), 'a'))
					{
						/*delete bullets[k];
						bullets[k] = nullptr;
						bullets[k] = new Bullet(*bullets.back());
						if (bullets.back() != nullptr)
						{
							delete bullets.back();
							bullets.back() = nullptr;
						}
						bullets.pop_back();*/
					}
					
				}
			}
		}
	}

	if (collideCheck == false)
	{
		player->move();
		cursor.move(sf::Vector2f(mouse.getPosition(window)) - (player->getPosition() - 2.f * player->getInputDirection()));
	}

	//camera.move(player.getInputDirection());
	camera.setCenter(player->getPosition());
	

	mouse.setPosition(sf::Vector2i(player->getPosition()), window);
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i] != nullptr) bullets[i]->update(deltaTime);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->isAbleToShoot())
	{
		bullets.push_back(new Bullet(player->shoot((cursor.getPosition() - player->getPosition()))));
		/*if (bullets.size() > 100)
		{
			delete bullets.back();
			bullets.back() = nullptr;
			bullets.pop_back();
		}*/
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bool deleteBullet = false;
		for (int j = 0; j < amountOfEnemySpawnPoints; j++)
		{
			if (bullets.size() > 0 && i < bullets.size())
			{
				if (enemies[j].gotHit(*bullets[i]))
				{
					enemies[j].loseHealth(1);
					deleteBullet = true;
					if (enemies[j].getHealth() <= 0) enemies[j].setPosition(sf::Vector2f(-100, -100));
				}
			}
			
		}

		if (!CollissionMan().intersectCircCirc(*player, *bullets[i]) && bullets[i]->getID() != player->getID())
		{
			player->loseHealth(1);
			deleteBullet = true;

			if (player->getHealth() <= 0)
			{
				if (soldiers.size() > 1)
				{
					Soldier* temp = new Soldier(*soldiers[1]);
					soldiers[0]->setIsPlayer(false);
					delete soldiers[0];
					soldiers[0] = nullptr;

					delete soldiers[1];
					soldiers[1] = nullptr;
					soldiers[1] = soldiers.back();
					soldiers.pop_back();

					soldiers[0] = new Soldier(*temp);
					soldiers[0]->setIsPlayer(true);
					player = soldiers[0];
					player->setPosition(sf::Vector2f(100, 100));

					delete temp;
					temp = nullptr;
				}
				else
				{
					returnMessage = (int)stateEvent::ExitGame;
				}
			}
		}

		if (deleteBullet)
		{
			delete bullets[i];
			bullets[i] = nullptr;
			bullets[i] = new Bullet(*bullets.back());
			if (bullets.back() != nullptr)
			{
				delete bullets.back();
				bullets.back() = nullptr;
			}
			bullets.pop_back();
		}
	}
	return returnMessage;
}

void GameState::render(sf::RenderWindow& window)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr) tiles[i]->at(j)->draw(window);
		}
	}

	for (int i = 0; i < floor.size(); i++)
	{
		for (int j = 0; j < floor[i]->size(); j++)
		{
			if (floor[i]->at(j) != nullptr && floor[i]->at(j)->getTileType() == 'e') floor[i]->at(j)->draw(window);
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i] != nullptr) window.draw(*bullets[i]);
	}

	for (int i = 0; i < soldiers.size(); i++)
	{
		window.draw(*soldiers[i]);
	}

	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		window.draw(enemies[i]);
	}

	window.draw(cursor);
	window.setView(camera);
}
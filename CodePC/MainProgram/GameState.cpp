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

GameState::GameState(const StateID InputStateId, StateStack& stateStack, std::string* level) :
State(InputStateId),
width(stateStack.windowWidth),
height(stateStack.windowHeight),
currentFileName(level)
{
	camera.setCenter(0, 0);
	camera.setSize(1280, 720);
	float temp = 0.f;
	texture.loadFromFile("../Images/cursor.png");
	cursor.setTexture(texture);
	cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
	cursor.setScale(2, 2);
	soldiers[0].setPosition(sf::Vector2f(200,200));
	soldiers[0].setIsPlayer(true);
	player = &soldiers[0];
	soldiers[1].setPosition(sf::Vector2f(200, 200));
	amountOfBullets = 0;
	amountOfEnemySpawnPoints = 0;
	cap = 3;
	enemySpawnPointArray = new sf::Vector2f*[cap];

	

	std::ifstream loadStream;
	loadStream.open(currentDirectory + *currentFileName);
	if (!loadStream && loadStream.is_open()) assert(true == true && "No level present on location!");

	EditorState tempEditor(InputStateId, stateStack, level);

	//Loads level data
	for (int i = 0; i < tileSizeY; i++)
	{
		std::vector<Tile*> tempGrid;
		std::vector<Tile*> tempTiles;

		std::string tileRow = "";
		loadStream >> tileRow;
		loadStream.ignore();

		for (int j = 0; j < tileSizeX; j++)
		{
			tempGrid.push_back(new Tile("basic_tile.png"));
			tempGrid.back()->setPosition({
				(tempGrid.back()->getSprite().getGlobalBounds().width / 2) + ((j * tempGrid.back()->getSprite().getGlobalBounds().width)),
				(tempGrid.back()->getSprite().getGlobalBounds().height / 2) + ((i * tempGrid.back()->getSprite().getGlobalBounds().height)) });

			tempTiles.push_back(nullptr);
			std::locale loc;
			if (!std::isblank(tileRow[j], loc))
			{
				char saveFileInformation = (char)tileRow[j] - 48;

				if (saveFileInformation != -99 && saveFileInformation != '\0' && tempEditor.loadTile((TileSorts)(saveFileInformation - 48)) != nullptr)
				{
					Tile tempTile = *tempEditor.loadTile((TileSorts)(saveFileInformation - 48));
					tempTiles[j] = new Tile(tempTile.getTexturePath());
					tempTiles[j]->setTileType(tempTile.getTileType());
					tempTiles[j]->setPosition(tempGrid[j]->getPosition());
					if (tempEditor.loadTile((TileSorts)(saveFileInformation - 48))->getTileType() == 'c')
					{
						enemySpawnPointArray[amountOfEnemySpawnPoints++] = new sf::Vector2f(tempTiles[j]->getPosition());
						if (amountOfEnemySpawnPoints == cap)
						{
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
				}
			}
		}
		tiles.push_back(tempTiles);

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
	}
}

GameState::~GameState()
{
	currentFileName = nullptr;
	
	for (int i = 0; i < amountOfBullets; i++)
	{
		delete bullets[i];
	}

	for (int k = 0; k < tiles.size(); k++)
	{
		for (int i = 0; i < tiles[k].size(); i++)
		{
			delete tiles[k][i];
			tiles[k][i] = nullptr;
		}
	}
}

int GameState::backendUpdate()
{
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
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] != nullptr) tiles[i][j]->update(deltaTime);
		}
	}

	if (mouseVisability)
	{
		window.setMouseCursorVisible(false);
		mouseVisability = false;
	}

	for (int i = 1; i < 2; i++)
	{
		soldiers[i].move();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		Soldier temp = soldiers[1];
		soldiers[0].setIsPlayer(false);
		soldiers[1] = soldiers[0];
		soldiers[0] = temp;
		soldiers[0].setIsPlayer(true);
		player = &soldiers[0];
		std::cout << "Switched\n";
	}
	
	/*if (unpauseTimer < unpauseTimerElapsed)
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			unpauseTimerElapsed = 0.f;
			returnMessage = (int)stateEvent::PauseState;
		}
	}*/

	player->rotateSprite(cursor.getPosition());
	//soldiers[0].rotateSprite(cursor.getPosition());

	if (!CollissionMan().intersectCircCirc(*player, npc))
	{
		
	}

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
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] != nullptr)
			{
				if (CollissionMan().intersectCircRect(*player, *tiles[i][j]))
				{
					collideCheck = true;
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
	for (int i = 0; i < amountOfBullets; i++)
	{
		bullets[i]->update(deltaTime);
	}
	/*
	if (!stateStack.get()->update(timePerFrame.asSeconds()))
	{
		window.close();
		gameOn = false;
	}*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->isAbleToShoot())
	{
		bullets[amountOfBullets++] = new Bullet(player->shoot((cursor.getPosition() - player->getPosition())));
		if (amountOfBullets > 50)
		{
			for (int i = 0; i < amountOfBullets; i++)
			{
				delete bullets[i];
			}
		}
	}
	for (int i = 0; i < amountOfBullets; i++)
	{
		for (int j = 0; j < amountOfEnemySpawnPoints; j++)
		{
			if (enemies[j].gotHit(*bullets[i]))
			{
				enemies[j].loseHealth(1);
				delete bullets[i];
				if (i != (amountOfBullets - 1) && amountOfBullets > 1)
				{
					bullets[i] = bullets[amountOfBullets - 1];
				}
				amountOfBullets--;
				if (enemies[j].getHealth() <= 0)
				{
					enemies[j].setPosition(sf::Vector2f(-100, -100));
				}
			}
		}
		if (player->gotHit(*bullets[i]))
		{
			player->loseHealth(1);
			delete bullets[i];
			if (i != (amountOfBullets - 1) && amountOfBullets > 1)
			{
				bullets[i] = bullets[amountOfBullets - 1];
			}
			amountOfBullets--;
			if (player->getHealth() <= 0)
			{
				player->setPosition(sf::Vector2f(100, 100));
			}
		}
		if (npc.gotHit(*bullets[i]))
		{
			npc.loseHealth(player->getDmg());
			delete bullets[i];
			if (i != (amountOfBullets - 1) && amountOfBullets > 1)
			{
				bullets[i] = bullets[amountOfBullets - 1];
			}
			amountOfBullets--;
			if (npc.getHealth() <= 0)
			{
				npc.setPosition(sf::Vector2f(-100, -100));
			}
		}
	}
		
	

	return returnMessage;
}

void GameState::render(sf::RenderWindow& window)
{
	for (int i = 0; i < amountOfBullets; i++)
	{
		window.draw(*bullets[i]);
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] != nullptr)
				tiles[i][j]->draw(window);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		window.draw(soldiers[i]);
	}

	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		window.draw(enemies[i]);
	}

	window.draw(npc);
	//window.draw(*player);
	window.draw(cursor);
	window.setView(camera);
}
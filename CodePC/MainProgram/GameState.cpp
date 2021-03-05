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
}

GameState::~GameState()
{
	currentFileName = nullptr;
	
	delete bullets;
	bullets = nullptr;

	for (int k = 0; k < tiles.size(); k++)
	{
		for (int i = 0; i < tiles[k].size(); i++)
		{
			delete tiles[k][i];
			tiles[k][i] = nullptr;
		}
	}
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
	
	/*if (unpauseTimer < unpauseTimerElapsed)
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			unpauseTimerElapsed = 0.f;
			returnMessage = (int)stateEvent::PauseState;
		}
	}*/

	player.rotateSprite(cursor.getPosition());

	if (!CollissionMan().intersectCircCirc(player, npc))
	{
		
	}

	collideCheck = false;

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] != nullptr)
			{
				if (CollissionMan().intersectCircRect(player, *tiles[i][j]))
				{
					collideCheck = true;
				}
			}
			
		}
	}

	if (collideCheck == false)
	{
		player.move();
		cursor.move(sf::Vector2f(mouse.getPosition(window)) - (player.getPosition() - 2.f * player.getInputDirection()));
	}
	

	//camera.move(player.getInputDirection());
	camera.setCenter(player.getPosition());
	

	mouse.setPosition(sf::Vector2i(player.getPosition()), window);
	if (bullets != nullptr)
	{
		bullets->update(deltaTime);
	}
	/*
	if (!stateStack.get()->update(timePerFrame.asSeconds()))
	{
		window.close();
		gameOn = false;
	}*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.ableToShoot())
	{
		bullets = new Bullet(player.shoot((cursor.getPosition() - player.getPosition())));
	}
	if (bullets != nullptr)
	{
		if (npc.gotHit(*bullets))
		{
			npc.loseHealth(player.getDmg());
			delete bullets;
			bullets = nullptr;
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
	if (bullets != nullptr)
	{
		window.draw(*bullets);
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] != nullptr)
				tiles[i][j]->draw(window);
		}
	}

	window.draw(npc);
	window.draw(player);
	window.draw(cursor);
	window.setView(camera);
}
#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateStack.h"
#include "Player.h"
#include "NPC.h"

class StateStack;
class Player;
class GameEntity;
class Tile;
class CollissionMan;

enum class GameEntityCollision
{
	player,
	other
};

class GameState : public State
{
private:
	const float width;
	const float height;
	bool collideCheck;

	sf::Font font;

	//Level loading
	std::string* currentFileName;
	std::string currentDirectory = "../Saves/";
	const int tileSizeX = 30;	//DO NOT CHANGE WÍTHOUT CHANGING IN EditorState.h AND REMOVING ALL SAVED LEVEL DATA!!
	const int tileSizeY = 20;	// /\.. /\.. /\..
	std::vector <std::vector<Tile*>> tiles;
	std::vector <std::vector<Tile*>> floor;


	//Cursor + camera
	sf::Sprite cursor;
	sf::View camera;
	sf::Mouse mouse;
	sf::Texture texture;

	//Player + NPC
	Soldier* player;
	std::vector<Soldier*> soldiers;

	sf::Vector2f* *enemySpawnPointArray;
	int amountOfEnemySpawnPoints;
	int cap;
	Soldier* enemies;
	
	///Bullet* bullets1 = nullptr; //<-- only 1 bulet? if so: make vector or something containing bullets, else: keep track of bullet quantity
	std::vector<Bullet*> bullets;
	int amountOfBullets;

	bool mouseVisability = true;

public:
	GameState(const StateID InputStateId, StateStack& stateStack, std::string* level, std::vector<Soldier*>& soliderHierarchy);
	~GameState() override;

	int backendUpdate();
	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


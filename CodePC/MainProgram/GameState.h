#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateStack.h"
#include "Player.h"
#include "NPC.h"
#include "WeaponFactory.h"
#include "WeaponType.h"
#include <SFML/Audio.hpp>

class BulletType;
class StateStack;
class Player;
class GameEntity;
class Tile;
class CollissionMan;
class EditorState;

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
	int tileSizeX;
	int tileSizeY;
	std::vector <std::vector<Tile*>*> tiles;
	std::vector <std::vector<Tile*>*> floor;
	std::vector<Tile*>* tempTiles;
	std::vector<Tile*>* tempFloor;
	std::vector<Tile*>* holder[60];
	std::vector<Tile*>* holder2[60];
	std::vector<sf::Text> nameDisplayer;
	
	//Pathfinding


	//Cursor + camera
	sf::Sprite cursor;
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
	sf::View camera;
	sf::Mouse mouse;
	sf::Texture texture;
	sf::Music themeSong;
	sf::Sound pow;
	sf::SoundBuffer powBuffer;
	sf::SoundBuffer kapowBuffer;
	sf::SoundBuffer deathsoundBuffer;
	sf::SoundBuffer crackBuffer;
	sf::SoundBuffer hitBuffer;
	sf::Sound kapow;
	sf::Sound deathsound;
	sf::Sound hit;
	sf::Sound crack;

	sf::Text healthText;
	sf::Text weaponText;
	sf::Font gameFont;

	//Player + NPC
	Soldier* player;
	std::vector<Soldier*>* soldiers;

	sf::Vector2f** enemySpawnPointArray;
	int amountOfEnemySpawnPoints;
	int enemyAmount;
	int cap;
	int* soldierRecieved;
	Soldier* *enemies;
	WeaponFactory weaponFactory;
	EditorState* tempEditor;
	sf::Vector2f lastMousePos;
	sf::Vector2f currentMousePos;
	
	std::vector<BulletType*>* bullets;
	int amountOfBullets;
	int playerWeapon;
	int counter;
	int updateTimer;

	bool mouseVisability = true;

public:
	GameState(const StateID InputStateId, StateStack& stateStack, std::string* level, std::vector<Soldier*> *soldierHierarchy, int* solderSent);
	~GameState() override;

	int backendUpdate();	//non-deltaTime reliant code
	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


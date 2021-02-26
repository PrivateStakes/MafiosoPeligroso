#pragma once
#include "State.h"
#include "Player.h"
#include <unordered_map>
#include <memory>

class StateStack;
class Player;
class GameEntity;
class Tile;
class Bullet;

//cannot exceed 9 tile sorts -- change to letters if you need more
enum class TileSorts 
{
	wall = 1,
	breakable,
	enemySpawnPoint,
	friendlySpawnPoint,
	COUNT
};

enum class Levels
{
	level1,
	level2,
	COUNT //dictates size of levels -- always last
};

class EditorState : public State
{
private:
	bool do_once = false;

	//std::string** levelDirectories; //fetches from StateStack
	std::string levelDirectories[3]
	{
		"level1.txt",
		"level2.txt",
		"urmumga.txt"
	};

	std::string tileTextures[4]
	{
		"wall1.png",
		"basic_tile2.png",
		"basic_tile3.png",
		"basic_tile4.png"
	};

	Levels* stateStackCurrentLevel;
	const float width;
	const float height;
	const int tileSizeX = 30;
	const int tileSizeY = 20;

	std::string currentFileName;
	std::string currentDirectory = "../Saves/";
	
	std::vector <std::vector<Tile*>> grid;
	std::vector <std::vector<Tile*>> tiles;

	Tile* currentBrush;
	std::unordered_map<TileSorts, std::unique_ptr<Tile>> tileCache;

	//---
	sf::View camera;
	sf::Mouse mouse;
	sf::Texture texture_player;
	Player player;
	bool mouseVisability = true;
	//---

public:
	EditorState(const StateID InputStateId, StateStack& stateStack, Levels* level);
	~EditorState() override;

	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	
	int consoleMenu(bool pallete, int highestNumber);
	bool hasClickedOnTile(int index_i, int index_j, std::vector <std::vector<Tile*>> inputTiles, sf::Vector2i mousePos, sf::RenderWindow& window);
	bool writeLevel();
	Tile* loadTile(TileSorts whichTile);

};
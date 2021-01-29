#pragma once
#include "State.h"
#include <unordered_map>
#include <memory>

class StateStack;
class Player;
class GameEntity;
class Tile;

//cannot exceed 9 tile sorts -- change to letters if you need more
enum class TileSorts 
{
	wall = 1,
	breakable,
	enemySpawnPoint,
	friendlySpawnPoint
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
	std::string levelDirectories[2]
	{
		"level1.txt",
		"level2.txt"
	};

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

public:
	EditorState(const StateID InputStateId, StateStack& stateStack, Levels level);
	~EditorState() override;

	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	
	int consoleMenu(bool pallete, int highestNumber);
	bool hasClickedOnTile(int index_i, int index_j, std::vector <std::vector<Tile*>> inputTiles, sf::Vector2i mousePos);
	bool writeLevel();
	Tile* loadTile(TileSorts whichTile);

};
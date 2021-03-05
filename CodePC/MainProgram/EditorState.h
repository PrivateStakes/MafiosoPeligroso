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

class EditorState : public State
{
private:
	bool do_once = false;

	//const int textureQuantity = 4;
	std::string tileTextures[4]
	{
		"wall1.png",
		"basic_tile2.png",
		"basic_tile3.png",
		"basic_tile4.png"
	};

	std::vector<std::string> levels;
	std::string* currentFileName;
	std::string currentDirectory = "../Saves/";

	const float width;
	const float height;
	const int tileSizeX = 30;
	const int tileSizeY = 20;
	
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
	EditorState(const StateID InputStateId, StateStack& stateStack, std::string* level);
	~EditorState() override;

	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	
	int consoleMenu(bool pallete, int highestNumber);
	bool hasClickedOnTile(int index_i, int index_j, std::vector <std::vector<Tile*>> inputTiles, sf::Vector2i mousePos, sf::RenderWindow& window);
	bool writeLevel();
	Tile* loadTile(TileSorts whichTile);

	//std::string* getTileTexturePaths();
	//int getTileTextureQuantity();
};
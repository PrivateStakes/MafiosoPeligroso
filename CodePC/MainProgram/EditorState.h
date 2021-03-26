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
	wallH = 1,			//a
	breakable,			//b
	enemySpawnPoint,	//c
	friendlySpawnPoint,	//d
	floor,				//e
	brakeableWall,		//f
	wallV,				//g
	wallU,				//h
	wallR,				//i
	wallD,				//j
	wallL,				//k
	wallC,				//l
	wallDL,				//m
	wallTL,				//n
	wallTR,				//o
	wallMiddleT,		//p
	wallMiddleL,		//q
	wallMiddleD,		//r
	wallMiddleR,		//s
	wallDR,				//t
	COUNT
};

class EditorState: public State
{
private:
	bool do_once = false;

	std::string tileTextures[20]
	{
		"Wall_Horizontal.png",
		"basic_tile2.png",
		"basic_tile3.png",
		"basic_tile4.png",
		"floor.png",
		"brakeableWall.png",
		"Wall_Vertical.png",
		"Wall_U_End.png",
		"Wall_R_End.png",
		"Wall_D_End.png",
		"Wall_L_End.png",
		"Wall_Corner.png",
		"Wall_D_L_End.png",
		"Wall_T_L_End.png",
		"Wall_T_R_End.png",
		"Wall_Middle_T.png",
		"Wall_Middle_L.png",
		"Wall_Middle_D.png",
		"Wall_Middle_R.png",
		"Wall_D_R_End.png"
	};

	std::vector<std::string> levels;
	std::string* currentFileName;
	std::string currentDirectory = "../Saves/";

	const float width;
	const float height;
	const int tileSizeX = 60;
	const int tileSizeY = 60;
	
	std::vector <std::vector<Tile*>*> grid;
	std::vector <std::vector<Tile*>*> tiles;

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
	EditorState(const EditorState& editorState) = default;
	~EditorState() override;

	int update(const float deltaTime, sf::RenderWindow& window, sf::Event& event) override;
	void render(sf::RenderWindow& window) override;
	
	int consoleMenu(bool pallete, int highestNumber);
	bool hasClickedOnTile(int index_i, int index_j, std::vector <std::vector<Tile*>*> inputTiles, sf::Vector2i mousePos, sf::RenderWindow& window);
	bool writeLevel();
	Tile loadTile(TileSorts whichTile);

	std::vector<Tile*>* tempGrid;
	std::vector<Tile*>* tempTiles;
	std::vector<Tile*>* holder[60];
	std::vector<Tile*>* holder2[60];

	int getGridSizeX();
	int getGridSizeY();

	//std::string* getTileTexturePaths();
	//int getTileTextureQuantity();
};
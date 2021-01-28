#pragma once
#include "State.h"
#include <unordered_map>
#include <memory>

class StateStack;
class Player;
class GameEntity;
class Tile;

enum class TileSorts 
{
	wall = 1,
	breakable,
	enemySpawnPoint,
	friendlySpawnPoint
};

class EditorState : public State
{
private:
	float width;
	float height;

	sf::Font font;

	const int tileSizeX = 30;
	const int tileSizeY = 20;

	
	std::vector<Tile*> grid;

	std::vector<Tile*> tiles;

	Tile* currentBrush;
	std::unordered_map<TileSorts, std::unique_ptr<Tile>> tileCache;

public:
	EditorState(const StateID InputStateId, StateStack& stateStack);
	~EditorState() override;

	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	bool hasClickedOnTile(int index, std::vector<Tile*> inputTiles, sf::Vector2i mousePos);
};
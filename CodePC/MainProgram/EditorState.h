#pragma once
#include "State.h"

class StateStack;
class Player;
class GameEntity;
class Tile;

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

public:
	EditorState(const StateID InputStateId, StateStack& stateStack);
	~EditorState() override;

	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};
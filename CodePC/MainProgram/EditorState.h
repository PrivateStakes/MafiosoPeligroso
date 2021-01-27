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

	const int tileSizeX = 20;
	const int tileSizeY = 20;
	std::vector<std::unique_ptr<Tile>> tiles;

public:
	EditorState(const StateID InputStateId, StateStack& stateStack);
	~EditorState() override;

	int update(const float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};
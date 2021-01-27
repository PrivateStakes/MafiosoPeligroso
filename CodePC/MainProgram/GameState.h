#pragma once
#include "State.h"

class StateStack;
class Player;
class GameEntity;

enum class GameEntityCollision
{
	player,
	other
};

class GameState : public State
{
private:
	float width;
	float height;

	sf::Font font;
	//sf::Mouse mouse;

public:
	GameState(const StateID InputStateId, StateStack& stateStack);
	~GameState() override;

	int update(const float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};


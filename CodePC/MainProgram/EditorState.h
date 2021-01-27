#pragma once
#include "State.h"

class StateStack;
class Player;
class GameEntity;

class EditorState : State
{
private:
	float width;
	float height;

	sf::Font font;

public:
	EditorState(const StateID InputStateId, StateStack& stateStack);
	~EditorState() override;

	int update(const float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};
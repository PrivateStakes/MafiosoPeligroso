#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateStack.h"
#include "Player.h"
#include "NPC.h"

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

	//Cursor + camera
	sf::Sprite cursor;
	sf::View camera;
	sf::Mouse mouse;
	sf::Texture texture;

	//Player + NPC
	Player player;
	NPC npc;
	Bullet* bullets = nullptr;

	bool mouseVisability = true;

public:
	GameState(const StateID InputStateId, StateStack& stateStack);
	~GameState() override;

	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


#pragma once
#include "State.h"

class StateStack;

class CityMap : public State
{
private:
	sf::Texture cityTexture;
	sf::Sprite citySprite;

	sf::Texture squareTexture;
	sf::Sprite squareSprite;

	int returnMessage;

public:
	CityMap(const StateID InputStateId, StateStack& stateStack);
	~CityMap() override;

	// Inherited via State
	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};
#pragma once
#include "State.h"
#include "Communication.h"
#include "Recruitment.h"
#include <ctime>

class StateStack;
class Soldier;

class CityMap : public State, public Communication, public Recruitment
{
private:
	sf::Texture cityTexture;
	sf::Sprite citySprite;

	sf::Texture squareTexture;
	sf::Sprite squareSprite;

	sf::Texture blueSquareTexture;
	sf::Sprite blueSquareSprite;
	sf::Mouse kms;

	Communication communicator;
	Recruitment recruiter;

	std::vector<Soldier*> soldiers;

public:
	CityMap(const StateID InputStateId, StateStack& stateStack, std::vector<Soldier*>& soliderHierarchy);
	~CityMap() override;

	// Inherited via State
	int update(const float deltaTime, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};
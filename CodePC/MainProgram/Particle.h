#pragma once
#include "GameEntity.h"

class Particle : GameEntity
{
private:
	float decaySpeed;
	float decay = 1;

	float speed;
	sf::Vector2f direction;

public:
	Particle(std::string filename, float decaySpeed);
	~Particle();

	void update(const float deltaTime) override;

	float getDecay();

	void setSpeed(float inputSpeed);
	float getSpeed();

	void setDirecttion(sf::Vector2f inputDirection); //sets any given direction (but normalised)
	sf::Vector2f getDirecttion();
};


#include "Particle.h"

Particle::Particle(std::string filename, float decaySpeed) : 
	GameEntity(filename),
	decaySpeed(decaySpeed)
{

}

Particle::~Particle()
{

}

void Particle::update(const float deltaTime)
{
	if (decay > 0.f) decay -= deltaTime * decaySpeed;
	else decay = 0.f;
	
	sprite.setScale({ decay, decay });	//good enough for now, make a transparncy shader later 
										//and make decay optional for e.g: bullets.
	sprite.move(direction*deltaTime);	//Think this is right, will test later
}

float Particle::getDecay()
{
	return decay;
}

void Particle::setSpeed(float inputSpeed)
{
	speed = inputSpeed;
}

float Particle::getSpeed()
{
	return speed;
}

void Particle::setDirecttion(sf::Vector2f inputDirection)
{
	direction = inputDirection;

	//Normalises direction
	float squaredLength = direction.x * direction.x + direction.y * direction.y;
	if (squaredLength > 0)
	{
		direction.x /= sqrt(squaredLength);
		direction.y /= sqrt(squaredLength);
	}
}

sf::Vector2f Particle::getDirecttion()
{
	return direction;
}

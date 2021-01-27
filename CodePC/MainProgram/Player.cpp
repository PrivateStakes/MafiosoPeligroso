#include "Player.h"
#include <cmath>
#include <iostream>

int Player::biggerOrNot(int firstValue, int secondValue)
{
	int value = 0;

	if (firstValue < secondValue)
	{
		value = -1;
	}

	else if (firstValue > secondValue)
	{
		value = 1;
	}

	return value;
}

Player::Player(string name, int health, float speed)
	:Soldier("character.png", name, health)
{
}

Player::~Player()
{
}

void Player::rotateSprite(sf::Vector2f pos)
{
	float hypotenuse = sqrt((pos.x - this->sprite.getPosition().x) * (pos.x - this->sprite.getPosition().x) + (pos.y - this->sprite.getPosition().y) * (pos.y - this->sprite.getPosition().y));
	if (biggerOrNot(this->sprite.getPosition().x, pos.x) == -1)
	{
		this->sprite.setRotation(((asin((pos.y - this->sprite.getPosition().y) / hypotenuse)) / 3.141592) * 180);
	}
	else if (biggerOrNot(this->sprite.getPosition().x, pos.x) == 1)
	{
		this->sprite.setRotation(180 - ((asin((pos.y - this->sprite.getPosition().y) / hypotenuse)) / 3.141592) * 180);
	}
	
	//std::cout << biggerOrNot(this->sprite.getPosition().y, (pos.y)) * ((atan(pos.x - this->sprite.getPosition().x) / ((pos.y - this->sprite.getPosition().y)) / 3.141592) * 180) << std::endl;
}

void Player::update(const float deltaTime)
{
	this->move();
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->sprite.move(-this->speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->sprite.move(this->speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->sprite.move(0, -this->speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->sprite.move(0, this->speed);
	}
}

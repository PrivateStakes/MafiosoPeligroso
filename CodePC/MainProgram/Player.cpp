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
	:Soldier("character.png", name, health), counter(0), reloading(false)
{
	this->currentWeapon = new Weapon(GunType::sniper);
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
	
}

Bullet Player::shoot(sf::Vector2f direction)
{
	//float offset1 = (abs(this->sprite.getPosition().x - direction.x) + abs(this->sprite.getPosition().y - direction.y))/2;
	sf::Vector2f offset = (direction/100.f);
	float rotation = 0;
	direction.x += (int(offset.x) * (rand() % 3 - 1) * (rand() % 10)) * this->currentWeapon->getSpreadMultiplier();
	direction.y += (int(offset.y) * (rand() % 3 - 1) * (rand() % 10)) * this->currentWeapon->getSpreadMultiplier();

	float squaredLength = direction.x * direction.x + direction.y * direction.y;

	if (biggerOrNot(direction.x, 0) == 1)
	{
		rotation = (asin((direction.y) / sqrt(squaredLength)) / 3.141592) * 180;
	}

	else if (biggerOrNot(direction.x, 0) == -1)
	{
		rotation = 180 - (asin((direction.y) / sqrt(squaredLength)) / 3.141592) * 180;
	}

	//Normalises direction
	
	if (squaredLength > 0)
	{
		direction.x /= sqrt(squaredLength);
		direction.y /= sqrt(squaredLength);
	}

	this->reloading = true;

	return Bullet(rotation, direction, this->sprite.getPosition(), this->currentWeapon->getDmg(), this->currentWeapon->getSpeed());
}

bool Player::ableToShoot() const
{
	return !this->reloading;
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

	if (this->reloading)
	{
		this->counter = (this->counter + 1) % this->currentWeapon->getReloadTime();
		if (counter == 0)
		{
			this->reloading = false;
		}
	}
}

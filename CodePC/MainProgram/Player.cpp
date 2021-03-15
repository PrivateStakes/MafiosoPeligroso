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

Player::Player(std::string name, int health, float speed)
	:Soldier("character_1.png", name, health), counter(0), reloading(false)
{
	//this->currentWeapon = new Weapon(GunType::pistol);
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

sf::Vector2f Player::getInputDirection() const
{
	return this->inputDirection;
}

bool Player::ableToShoot() const
{
	return !this->reloading;
}

float Player::getRotation() const
{
	return this->sprite.getRotation();
}

void Player::update(const float deltaTime)
{
	this->move();
}

void Player::move()
{
	this->inputDirection = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->inputDirection.x = -this->speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->inputDirection.x = this->speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->inputDirection.y = -this->speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->inputDirection.y = this->speed;
	}


	this->sprite.move(this->inputDirection);

	/*if (this->sprite.getGlobalBounds().left < 0 && this->sprite.getGlobalBounds().left > -100)
		{
			this->setPosition(sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top));
		}
		else if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width > 1680)
		{
			this->setPosition(sf::Vector2f(1680 - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top));
		}
		if (this->sprite.getGlobalBounds().top < 0)
		{
			this->setPosition(sf::Vector2f(this->sprite.getGlobalBounds().left, this->sprite.getGlobalBounds().width));
		}
		else if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height > 1050)
		{
			this->setPosition(sf::Vector2f(this->sprite.getGlobalBounds().left, 1050 - this->sprite.getGlobalBounds().height));
		}*/
}

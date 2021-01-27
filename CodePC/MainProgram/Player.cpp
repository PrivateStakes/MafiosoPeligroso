#include "Player.h"
#include <cmath>

Player::Player(string name, int health, float speed)
	:Soldier("platform.png", name, health)
{
}

Player::~Player()
{
}

void Player::rotateSprite(sf::Vector2f pos)
{
	this->sprite.setRotation((atan(pos.x - this->sprite.getPosition().x/(pos.y - this->sprite.getPosition().y)/3.141592)*180));
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

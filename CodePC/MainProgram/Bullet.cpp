#include "Bullet.h"

void Bullet::move()
{
	this->sprite.move(this->speed*this->xDir, this->speed*this->yDir);
}

Bullet::Bullet(sf::Vector2f direction, sf::Vector2f position, int dmg, float speed)
	:GameEntity("Bullet.png"), xDir(xDir), yDir(yDir), dmg(dmg), speed(speed)
{
}

void Bullet::update(const float deltaTime)
{
	this->move();
}

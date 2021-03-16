#include "Bullet.h"

void Bullet::move()
{
	this->sprite.move(this->speed*this->xDir, this->speed*this->yDir);
}

Bullet::Bullet(float rotation, sf::Vector2f direction, sf::Vector2f position, int dmg, float speed, int ID)
	:GameEntity("Bullet2.png"), xDir(direction.x), yDir(direction.y), dmg(dmg), speed(speed), ID(ID), rotation(rotation)
{
	this->sprite.setPosition(position);
	//this->sprite.setRotation(rotation);
}

Bullet::~Bullet()
{
}

int Bullet::getID() const
{
	return this->ID;
}

int Bullet::getDamage() const
{
	return this->dmg;
}

float Bullet::getRotation() const
{
	return this->rotation;
}

sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bullet::update(const float deltaTime)
{
	this->move();
}

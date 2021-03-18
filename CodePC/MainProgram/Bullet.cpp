#include "Bullet.h"

Bullet::Bullet(float rotation, sf::Vector2f direction, sf::Vector2f position, int dmg, float speed, int ID)
	:GameEntity("Bullet2.png"), xDir(direction.x), yDir(direction.y), dmg(dmg), speed(speed*60), ID(ID), rotation(rotation)
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
	this->sprite.move(this->speed * this->xDir * deltaTime, this->speed * this->yDir * deltaTime);
}

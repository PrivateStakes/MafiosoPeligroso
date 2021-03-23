#include "BulletType.h"
#include "Bullet.h"

BulletType::BulletType(const Bullet* source, sf::Vector2f direction, sf::Vector2f position, float rotation, int ID)
	:GameEntity("Bullet2.png"), copiedBullet(source)
{
	this->xDir = direction.x;
	this->yDir = direction.y;
	this->sprite.setPosition(position);
	this->sprite.setRotation(rotation);
	this->ID = ID;
}

BulletType::~BulletType()
{
	copiedBullet = nullptr;
}

int BulletType::getID() const
{
	return this->ID;
}

float BulletType::getRotation() const
{
	return this->sprite.getRotation();
}

int BulletType::getDmg() const
{
	return this->copiedBullet->getDamage();
}

void BulletType::update(const float deltaTime)
{
	this->sprite.move(xDir * deltaTime * copiedBullet->getSpeed(), yDir * deltaTime * copiedBullet->getSpeed());
}

bool BulletType::getHasBeenUpdated()
{
	return hasBeenUpdated;
}

void BulletType::setHasBeenUpdated(bool input)
{
	hasBeenUpdated = input;
}
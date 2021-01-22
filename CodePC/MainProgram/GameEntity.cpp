#include "GameEntity.h"

GameEntity::GameEntity(string fileName)
{
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
}

GameEntity::~GameEntity()
{

}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}

void GameEntity::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

sf::Vector2f GameEntity::getPosition()
{
	return sprite.getPosition();
}
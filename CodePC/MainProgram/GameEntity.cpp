#include "GameEntity.h"

GameEntity::GameEntity(string fileName)
{
	texture.loadFromFile("../Images/"+fileName);
	sprite.setTexture(texture);

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(5.f, 5.f);
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

sf::Sprite GameEntity::getSprite()
{
	return sprite;
}
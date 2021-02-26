#include "GameEntity.h"
#include "Bullet.h"

GameEntity::GameEntity(std::string fileName)
{
	texture.loadFromFile("../Images/"+fileName);
	sprite.setTexture(texture);

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(2.f, 2.f);
}

GameEntity::~GameEntity()
{

}

bool GameEntity::gotHit(const Bullet& bullet) const
{
	return this->sprite.getGlobalBounds().intersects(bullet.getBounds());
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

sf::FloatRect GameEntity::getBounds()
{
	return this->sprite.getGlobalBounds();
}

#include "GameEntity.h"
#include "Bullet.h"

GameEntity::GameEntity(std::string fileName)
{
	if (fileName != "Bullet2.png")
	{
		texture.loadFromFile("../Images/" + fileName);
		sprite.setTexture(texture);
	}
	

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(2.f, 2.f);
	hasCustomCollider = false;
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

void GameEntity::setColour(sf::Color input)
{
	sprite.setColor(input);
}

sf::Sprite GameEntity::getSprite()
{
	return sprite;
}

void GameEntity::setCustomCollider(sf::FloatRect input)
{
	customCollider = input;
	hasCustomCollider = true;
}

sf::FloatRect GameEntity::getBounds()
{
	if (!hasCustomCollider)
	{
		return this->sprite.getGlobalBounds();
	}
	else
	{
		sf::FloatRect returnRect;
		returnRect = customCollider;
		returnRect.height = customCollider.height;
		returnRect.left = customCollider.left + sprite.getPosition().x;
		returnRect.top = customCollider.top + sprite.getPosition().y;
		returnRect.width = customCollider.width; 
		return returnRect;
	}
}

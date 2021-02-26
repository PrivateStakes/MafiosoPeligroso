#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>

class Bullet;

class GameEntity : public sf::Drawable
{
protected:
	sf::Sprite sprite;

private:
	sf::Texture texture;

public:
	GameEntity(std::string fileName);
	~GameEntity();
	bool gotHit(const Bullet &bullet)const;

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	sf::Sprite getSprite();

	sf::FloatRect getBounds();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

};


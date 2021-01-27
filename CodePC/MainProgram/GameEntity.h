#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>

using namespace std;
class GameEntity : public sf::Drawable
{
protected:
	sf::Sprite sprite;

private:
	sf::Texture texture;

public:
	GameEntity(string fileName);
	~GameEntity();

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	sf::Sprite getSprite();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
};


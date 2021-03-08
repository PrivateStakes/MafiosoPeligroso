#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>

class Communication : public sf::Drawable
{
protected:
	sf::Sprite commSprite;
	sf::Texture commTexture;
	sf::Text commText;
private:

public:
	Communication();
	~Communication();

	void openMenu();
	void closeMenu();
	sf::Sprite getSprite();

};

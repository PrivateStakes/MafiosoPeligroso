#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>

class Communication
{
protected:
	sf::Texture commTexture;
	sf::Sprite commSprite;
	sf::Text commText1;
	sf::Text commText2;
	sf::Font commFont;
	int choice;
	bool isOpen;
private:

public:
	Communication();
	~Communication();

	void openMenu();
	void closeMenu();
	bool yesOpen();
	std::string textBit(int id);
};

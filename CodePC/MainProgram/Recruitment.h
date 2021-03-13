#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>
#include <ctime>
#include <iostream>

class Recruitment
{
protected:
	sf::Texture bodyTexture;
	sf::Texture mouthTexture;
	sf::Texture faceTexture;
	sf::Texture hatTexture;
	sf::Sprite bodySprite;
	sf::Sprite mouthSprite;
	sf::Sprite faceSprite;
	sf::Sprite hatSprite;

	bool isOpen;
private:

public:
	Recruitment();
	~Recruitment();

	void openMenu();
	void closeMenu();
	bool yesOpen();
	void randomCharacter();
};

#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>
#include <ctime>
#include <iostream>
#include "Soldier.h"

class Recruitment
{
protected:
	sf::Texture backgroundTexture;
	sf::Texture bodyTexture;
	sf::Texture mouthTexture;
	sf::Texture faceTexture;
	sf::Texture hatTexture;

	sf::Sprite backgroundSprite;
	sf::Sprite bodySprite;
	sf::Sprite mouthSprite;
	sf::Sprite faceSprite;
	sf::Sprite hatSprite;

	sf::Text recText1;
	sf::Text recText2;
	sf::Text recText3;
	sf::Text recText4;
	sf::Font recFont;

	bool isOpen;
	int deleteSoon;
private:
	std::string name;
	int age;
	std::string occupation;
	std::string backstory;
	int temp;
	

public:
	Recruitment();
	~Recruitment();

	void openMenu();
	void closeMenu();
	bool yesOpen();
	void randomCharacter();
	void updateText();
	std::string recruit(int &counter);
};

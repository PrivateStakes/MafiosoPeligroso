#include "Recruitment.h"

Recruitment::Recruitment()
{
	isOpen = false;
	deleteSoon = 1;

	randomCharacter();

	backgroundTexture.loadFromFile("../Images/Background.png");
	backgroundSprite.setTexture(backgroundTexture);
	bodySprite.setPosition(0, 0);

	bodyTexture.loadFromFile("../Images/Body.png");
	bodySprite.setTexture(bodyTexture);
	bodySprite.setPosition(0, 270);

	mouthTexture.loadFromFile("../Images/M" + std::to_string(rand() % 4) + ".png");
	mouthSprite.setTexture(mouthTexture);
	mouthSprite.setPosition(0, 270);

	faceTexture.loadFromFile("../Images/F" + std::to_string(rand() % 6) + ".png");
	faceSprite.setTexture(faceTexture);
	faceSprite.setPosition(0, 270);

	hatTexture.loadFromFile("../Images/H" + std::to_string(rand() % 4) + ".png");
	hatSprite.setTexture(hatTexture);
	hatSprite.setPosition(0, 270);

	recText1.setPosition(60, 100);
	recText2.setPosition(1100, 60);
	recText3.setPosition(1100, 300);
	recText4.setPosition(1100, 975);

	recFont.loadFromFile("../Fonts/PressStart2P-Regular.ttf");
	recText1.setFont(recFont);
	recText1.setString("RECRUITMENT:");
	recText1.setCharacterSize(80);
	recText1.setFillColor(sf::Color::Black);

	recText2.setFont(recFont);
	recText2.setString("INSTRUCTIONS:\n\nP: Open Menu\n\nO: Close Menu\n\nI: Generate New Soldier");
	recText2.setCharacterSize(20);
	recText2.setFillColor(sf::Color::Black);

	recText3.setFont(recFont);
	recText3.setString("NAME: " + name + "\n\n\n\n\n\nAGE: " + std::to_string(age) + "\n\n\n\n\n\nOCCUPATION: " + occupation + "\n\n\n\n\n\nBACKSTORY: " + backstory);
	recText3.setCharacterSize(20);
	recText3.setFillColor(sf::Color::Black);

	recText4.setFont(recFont);
	recText4.setString("TO RECRUIT HIT 'ENTER'\n(Current Soldiers: " + std::to_string(deleteSoon) + ")");
	recText4.setCharacterSize(20);
	recText4.setFillColor(sf::Color::Black);
}

Recruitment::~Recruitment()
{
}

void Recruitment::openMenu()
{
	this->isOpen = true;
}

void Recruitment::closeMenu()
{
	this->isOpen = false;
}

bool Recruitment::yesOpen()
{
	return this->isOpen;
}

void Recruitment::randomCharacter()
{
	this->mouthTexture.loadFromFile("../Images/M" + std::to_string(rand()%4) + ".png");
	this->mouthSprite.setTexture(mouthTexture);
	this->faceTexture.loadFromFile("../Images/F" + std::to_string(rand()%6) + ".png");
	this->faceSprite.setTexture(faceTexture);
	this->hatTexture.loadFromFile("../Images/H" + std::to_string(rand()%4) + ".png");
	this->hatSprite.setTexture(hatTexture);

	temp = rand() % 4;
	if (temp == 0)
	{
		name = "Jörgen";
	}
	else if (temp == 1)
	{
		name = "Morgan";
	}
	else if (temp == 2)
	{
		name = "Josef";
	}
	else if (temp == 3)
	{
		name = "Sten";
	}

	age = rand()%60 + 14;

	temp = rand() % 4;
	if (temp == 0)
	{
		occupation = "Blacksmith";
	}
	else if (temp == 1)
	{
		occupation = "Doctor";
	}
	else if (temp == 2)
	{
		occupation = "Author";
	}
	else if (temp == 3)
	{
		occupation = "Teacher";
	}

	temp = rand() % 4;
	if (temp == 0)
	{
		backstory = "His wife left \nhim for some other guy. \n\nSo he left his old life \nto hunt her down";
	}
	else if (temp == 1)
	{
		backstory = "His wife left \nhim for some other guy. \n\nSo he left his old life \nto hunt her down";
	}
	else if (temp == 2)
	{
		backstory = "His wife left \nhim for some other guy. \n\nSo he left his old life \nto hunt her down";
	}
	else if (temp == 3)
	{
		backstory = "His wife left \nhim for some other guy. \n\nSo he left his old life \nto hunt her down";
	}

	temp = rand() % 3;

	updateText();
}

void Recruitment::updateText()
{
	recText3.setString("NAME: " + name + "\n\n\n\n\n\nAGE: " + std::to_string(age) + "\n\n\n\n\n\nOCCUPATION: " + occupation + "\n\n\n\n\n\nBACKSTORY: " + backstory);
	recText4.setString("TO RECRUIT HIT 'ENTER'\n(Current Soldiers: " + std::to_string(deleteSoon) + ")");
}

std::string Recruitment::recruit(int& counter)
{
	counter++;
	randomCharacter();
	updateText();
	return name;
}

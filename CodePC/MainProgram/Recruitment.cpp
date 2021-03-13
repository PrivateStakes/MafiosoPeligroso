#include "Recruitment.h"

Recruitment::Recruitment()
{
	isOpen = false;
	bodyTexture.loadFromFile("../Images/Body.png");
	bodySprite.setTexture(bodyTexture);
	bodySprite.setPosition(0, 265);

	mouthTexture.loadFromFile("../Images/M" + std::to_string(rand() % 4) + ".png");
	mouthSprite.setTexture(mouthTexture);
	mouthSprite.setPosition(0, 265);

	faceTexture.loadFromFile("../Images/F" + std::to_string(rand() % 6) + ".png");
	faceSprite.setTexture(faceTexture);
	faceSprite.setPosition(0, 265);

	hatTexture.loadFromFile("../Images/H" + std::to_string(rand() % 4) + ".png");
	hatSprite.setTexture(hatTexture);
	hatSprite.setPosition(0, 265);

	srand(time(0));
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
}

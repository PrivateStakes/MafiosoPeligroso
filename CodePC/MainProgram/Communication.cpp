#include "Communication.h"

Communication::Communication()
{
	choice = 1;
	isOpen = false;
	commTexture.loadFromFile("../Images/AttaBoy.png");
	commSprite.setTexture(commTexture);
	commSprite.setPosition(0, 265);

	commText1.setPosition(590, 850);
	commText2.setPosition(1080, 860);

	commFont.loadFromFile("../Fonts/PressStart2P-Regular.ttf");
	commText1.setFont(commFont);
	commText1.setString(textBit(-1));
	commText1.setCharacterSize(10);
	commText1.setFillColor(sf::Color::Black);

	commText2.setFont(commFont);
	commText2.setCharacterSize(20);
	commText2.setFillColor(sf::Color::Black);
}

Communication::~Communication()
{
}

void Communication::openMenu()
{
	this->isOpen = true;
}

void Communication::closeMenu()
{
	this->isOpen = false;
}

bool Communication::yesOpen()
{
	return this->isOpen;
}

std::string Communication::textBit(int id)
{
	if (id == -1) return "I welcome you to my humble abode";
	if (id == 0)
	{
		return "Lose away off why half led have near bed.\n\n\n\nAt engage simple father of period others except.\n\n\n\nMy giving do summer of though narrow marked at.\n\n\n\nSpring formal no county ye waited.";
	}
	else if (id == 1)
	{
		return "My whether cheered at regular it of promise \n\nblushes perhaps.\n\n\n\nUncommonly simplicity interested mr is be \n\ncompliment projecting my inhabiting.\n\n\n\nGentleman he september in oh excellent.";
	}
	else if (id == 2)
	{
		return "Yourself off its pleasant ecstatic now law.\n\n\n\nYe their mirth seems of songs.\n\n\n\nProspect out bed contempt separate.\n\n\n\nHer inquietude our shy yet sentiments \n\ncollecting.";
	}
	else if (id == 3)
	{
		return "Cottage fat beloved himself arrived old.\n\n\n\nGrave widow hours among him ﻿no you led.\n\n\n\nPower had these met least nor young.\n\n\n\nYet match drift wrong his our. ";
	}
	else if (id == 4)
	{
		return "Extremity direction existence as dashwoods do \n\nup.\n\n\n\nSecuring marianne led welcomed offended but \n\noffering six raptures.\n\n\n\nConveying concluded newspaper rapturous oh at.";
	}
}




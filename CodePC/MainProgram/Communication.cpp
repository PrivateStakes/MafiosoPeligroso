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
	if (id == -1) return "Got something to say cat?";
	if (id == 0)
	{
		return "Don't think just 'cause you bumped off the boss \n\nthat you got it all figured out big six. \n\n\n\nEvery rube in the city wants yer seat, the real \n\ntest is keeping it.";
	}
	else if (id == 1)
	{
		return "You gotta take someone for a ride? \n\n\n\nDrop the evidence off at the Milson brother's \n\n\nplace. \n\n\n\nTheir pigs will eat anything.";
	}
	else if (id == 2)
	{
		return "The fuzz ain't no thing in this city, our \n\nerstwhile boss had that covered, now it's you \n\nwho covers that expense *hur-hur-hur*.";
	}
	else if (id == 3)
	{
		return "Don't hire a man who can't look 'em in the eye \n\nwhen they pop 'em, can't trust a fink.";
	}
	else if (id == 4)
	{
		return "Used to be easy riding the Muddy Miss to the \n\nCajun fer business. \n\n\n\nBut their hooch turned to panther sweat, then \n\nto coffin varnish, now the fuzz won't let up.";
	}
}




#include "Recruitment.h"

Recruitment::Recruitment()
{
	isOpen = false;

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
	recText4.setString("TO RECRUIT HIT 'ENTER'\n(Current Soldiers: " + std::to_string(counter) + ")");
	recText4.setCharacterSize(20);
	recText4.setFillColor(sf::Color::Black);

	updateText();
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

	temp = rand() % 13;
	if (temp == 0)
	{
		name = "Charlie";
	}
	else if (temp == 1)
	{
		name = "Edmund";
	}
	else if (temp == 2)
	{
		name = "Viktor";
	}
	else if (temp == 3)
	{
		name = "Nicholas";
	}
	else if (temp == 4)
	{
		name = "Dominic";
	}
	else if (temp == 5)
	{
		name = "Dorian";
	}
	else if (temp == 6)
	{
		name = "Alfred";
	}
	else if (temp == 7)
	{
		name = "Mordecai";
	}
	else if (temp == 8)
	{
		name = "Virgil";
	}
	else if (temp == 9)
	{
		name = "Horatio";
	}
	else if (temp == 10)
	{
		name = "Andrik";
	}
	else if (temp == 11)
	{
		name = "Bobby";
	}
	else if (temp == 11)
	{
		name = "Clyde";
	}
	else if (temp == 12)
	{
		name = "Harrier";
	}

	age = rand()%60 + 14;

	temp = rand() % 13;
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
	else if (temp == 4)
	{
		occupation = "Pediatrician";
	}
	else if (temp == 5)
	{
		occupation = "Fisherman";
	}
	else if (temp == 6)
	{
		occupation = "Austronaut";
	}
	else if (temp == 7)
	{
		occupation = "Mucisian";
	}
	else if (temp == 8)
	{
		occupation = "News anchor";
	}
	else if (temp == 9)
	{
		occupation = "Chef";
	}
	else if (temp == 10)
	{
		occupation = "Cashier";
	}
	else if (temp == 11)
	{
		occupation = "Police";
	}
	else if (temp == 12)
	{
		occupation = "Beatboxer";
	}

	temp = rand() % 13;
	if (temp == 0)
	{
		backstory = "Couldn't settle \ninto civillian life after \nhis service in France. \n\nHis hands shake \nuncontrollably unless he's \nholding a gun.";
	}
	else if (temp == 1)
	{
		backstory = "Lost his medical license \nafter being caught mixing \nhis own laudanum. \n\nIf he offers you a drink, \ndon't accept it.";
	}
	else if (temp == 2)
	{
		backstory = "A behemoth of a \nman and expatriate of the \nonce Austro-Hungarian \nempire. \n\nDon't call him vinegar, \nonly his wife calls \nhim vinegar.";
	}
	else if (temp == 3)
	{
		backstory = "Used to be a \nboxer before he got \n'too competitive' for the \nring. \n\nRaised in the swamp, don't \nmind his accent.";
	}
	else if (temp == 4)
	{
		backstory = "Would have \ninherited his father's \nranch in Texas if he didn't \nburn it down. \n\nLoves a good chase.";
	}
	else if (temp == 5)
	{
		backstory = "Used to play \nsaxophone for a cabaret \nbefore being caught in the \nladies dress room. \n\nLanguid as a cloud of \ntobacco smoke.";
	}
	else if (temp == 6)
	{
		backstory = "Survived the \nwhole campaign at the \nSomme, moved to America for 'peace and quiet'. \n\nPlays the piano like a \nchampion.";
	}
	else if (temp == 7)
	{
		backstory = "Made a bitter \ndeparture from home after \nsettling a grudge with his \nabusive father. \n\nHas a stare like a pair \nof icepicks.";
	}
	else if (temp == 8)
	{
		backstory = "Flunked police \nacademy because he gets too \n'intense' at the shooting \nrange. \n\nWhere did he get a tommy \ngun ? [NAME HERE] STOP!";
	}
	else if (temp == 9)
	{
		backstory = "Worked as a \nwaiter at a high-class \nrestaurant before the \ndepression hit. \n\nCouldn't sound threatening \nto save his life.";
	}
	else if (temp == 10)
	{
		backstory = "Moved to America \nfrom some slavic country he \nrefuses to talk about. \n\nDon't ask him about his \nfamily.";
	}
	else if (temp == 11)
	{
		backstory = "A British \nveteran of the war, fell in \nlove with an American nurse. \n\nOptimistic to a fault.";
	}
	else if (temp == 12)
	{
		backstory = "Used to crew a \nfishing vessel before \ngetting pegged for the liquor \nin the hold. \n\nNot a lot of personality, \nbut he could strangle a \nhorse.";
	}

	temp = rand() % 4;

	updateText();
}

void Recruitment::updateText()
{
	recText3.setString("NAME: " + name + "\n\n\n\n\n\nAGE: " + std::to_string(age) + "\n\n\n\n\n\nOCCUPATION: " + occupation + "\n\n\n\n\n\nBACKSTORY: " + backstory);
	recText4.setString("TO RECRUIT HIT 'ENTER'\n(Current Soldiers: " + std::to_string(counter) + ")");
}

std::string Recruitment::recruit(int& counter)
{
	//counter++;
	randomCharacter();
	return name;
}

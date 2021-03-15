#include "CityMap.h"
#include "StateStack.h"
#include <iostream>
#include "Soldier.h"

CityMap::CityMap(StateID InputStateId, StateStack& stateStack, std::vector<Soldier*>* soliderHierarchy):
    State(InputStateId),
    soldiers(soliderHierarchy)
{
   cityTexture.loadFromFile("../Images/citymap.png");
   citySprite.setTexture(cityTexture);
   citySprite.setScale(stateStack.windowWidth / citySprite.getGlobalBounds().width, stateStack.windowHeight / citySprite.getGlobalBounds().height);
   squareTexture.loadFromFile("../Images/RedRectangle.png");
   squareSprite.setTexture(squareTexture); 
   squareSprite.setPosition(30, 425);
   squareSprite.setScale(0.3, 0.5);
   blueSquareTexture.loadFromFile("../Images/BlueSquare.png");
   blueSquareSprite.setTexture(blueSquareTexture);
   blueSquareSprite.setPosition(239, 425);
   blueSquareSprite.setScale(0.3, 0.5);

   srand(time(NULL));
}

CityMap::~CityMap()
{
}

int CityMap::update(const float deltaTime, sf::RenderWindow& window)
{
    int returnMessage = 0;
    if (choice == 1)
    {
        commText2.setString("SELECT:\n\nTALK<-\n\nATTACK\n\nCLOSE");
    }
    else if (choice == 2)
    {
        commText2.setString("SELECT:\n\nTALK\n\nATTACK<-\n\nCLOSE");
    }
    else if (choice == 3)
    {
        commText2.setString("SELECT:\n\nTALK\n\nATTACK\n\nCLOSE<-");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && kms.getPosition().x > 365 && kms.getPosition().x < 575 
        && kms.getPosition().y > 470 && kms.getPosition().y < 750)
    {
        communicator.openMenu();
        commText1.setString(textBit(-1));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) recruiter.closeMenu();

    if (communicator.yesOpen())
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && choice > 1) choice--;
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && choice < 3) choice++;

        if (kms.getPosition().x > 1200 && kms.getPosition().x < 1320
            && kms.getPosition().y > 950 && kms.getPosition().y < 970) choice = 1;
        else if (kms.getPosition().x > 1200 && kms.getPosition().x < 1320
            && kms.getPosition().y > 990 && kms.getPosition().y < 1010) choice = 2;
        else if (kms.getPosition().x > 1200 && kms.getPosition().x < 1320
            && kms.getPosition().y > 1030 && kms.getPosition().y < 1050) choice = 3;
    }

    if (communicator.yesOpen() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        if (choice == 1)
        {
            commText1.setString(textBit(rand()%5));
        }
        else if (choice == 2)
        {
            std::cout << "How many soldiers do you want to send into combat? (You have " << soldiers->size() << " soldiers)\n";
            std::cin >> temp;
            if (temp <= soldiers->size() && temp > 0)
            {
                returnMessage = (int)stateEvent::GameState;
            }
            else
            {
                std::cout << "Not within area of selection Please insert something between 1 and " << soldiers->size() << std::endl;
            }
            
        }
        else if (choice == 3)
        {
            communicator.closeMenu();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
        recruiter.openMenu();
    }

    if (recruiter.yesOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
        {
            randomCharacter();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) recruiter.closeMenu();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            soldiers->push_back(new Soldier("character_" + std::to_string(temp+1) + ".png", recruit(deleteSoon), 3));
    
        }
    }

    return returnMessage;
}

void CityMap::render(sf::RenderWindow& window)
{
    window.draw(citySprite);
    window.draw(squareSprite);
    window.draw(blueSquareSprite);
    if (communicator.yesOpen())
    {
        window.draw(commSprite);
        window.draw(commText1);
        window.draw(commText2);
    }
    if (recruiter.yesOpen())
    {
        window.draw(backgroundSprite);
        window.draw(bodySprite);
        window.draw(mouthSprite);
        window.draw(faceSprite);
        window.draw(hatSprite);
        window.draw(recText1);
        window.draw(recText2);
        window.draw(recText3);
        window.draw(recText4);
    }
}

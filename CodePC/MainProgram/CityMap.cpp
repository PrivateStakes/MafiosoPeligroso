#include "CityMap.h"
#include "StateStack.h"
#include <iostream>

CityMap::CityMap(StateID InputStateId, StateStack& stateStack)
    :State(InputStateId)
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
    returnMessage = 0;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) communicator.closeMenu();
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
        std::cout << kms.getPosition().x << " " << kms.getPosition().y << std::endl;
    }
    if (communicator.yesOpen() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        if (choice == 1)
        {
            commText1.setString(textBit(rand()%5));
        }
        else if (choice == 2)
        {
            returnMessage = (int)stateEvent::GameState;
        }
        else if (choice == 3)
        {
            communicator.closeMenu();
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
}

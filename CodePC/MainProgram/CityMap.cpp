#include "CityMap.h"
#include "StateStack.h"

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
   
}

CityMap::~CityMap()
{
}

int CityMap::update(const float deltaTime, sf::RenderWindow& window)
{
    returnMessage = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) returnMessage = (int)stateEvent::GameState;

    return returnMessage;
}

void CityMap::render(sf::RenderWindow& window)
{
    window.draw(citySprite);
    window.draw(squareSprite);
}

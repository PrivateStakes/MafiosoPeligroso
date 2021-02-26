#include "CityMap.h"
#include "StateStack.h"

CityMap::CityMap(StateID InputStateId, StateStack& stateStack)
    :State(InputStateId)
{
    this->cityTexture.loadFromFile("../Images/CityMap.png");
    this->citySprite.setTexture(this->cityTexture);
    this->citySprite.setScale(stateStack.windowWidth / this->citySprite.getGlobalBounds().width, stateStack.windowHeight / this->citySprite.getGlobalBounds().height);
}

CityMap::~CityMap()
{
}

int CityMap::update(const float deltaTime, sf::RenderWindow& window)
{
    this->returnMessage = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) returnMessage = (int)stateEvent::GameState;

    return this->returnMessage;
}

void CityMap::render(sf::RenderWindow& window)
{
    window.draw(this->citySprite);
}

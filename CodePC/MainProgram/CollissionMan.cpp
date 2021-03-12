#include "CollissionMan.h"

CollissionMan::CollissionMan()
{
}

CollissionMan::~CollissionMan()
{
}

bool CollissionMan::intersectCircRect(GameEntity& circle, Tile& rect, char tileType)
{
    bool hasCollided = false;
    circleDistanceX = abs(circle.getBounds().left - rect.getBounds().left);
    circleDistanceY = abs(circle.getBounds().top - rect.getBounds().top);

    if (circleDistanceX > (rect.getBounds().width/2 + circle.getBounds().width/2)) 
    { 
        return hasCollided;
    }
    if (circleDistanceY > (rect.getBounds().height/2 + circle.getBounds().width/2)) 
    { 
        return hasCollided;
    }

    if (circleDistanceX <= (rect.getBounds().height / 2) && rect.getTileType() == tileType);
    { 
        
        if (((circle.getBounds().top + circle.getBounds().height) - rect.getBounds().top) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y - 0.2));
            //std::cout << "UP\n";
        }
        else if ((circle.getBounds().top - (rect.getBounds().top + rect.getBounds().height)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y + 0.2));
            //std::cout << "DOWN\n";
        }
        
        hasCollided = true;
    }
    if (circleDistanceY <= (rect.getBounds().width / 2) && rect.getTileType() == tileType);
    { 
        if ((circle.getBounds().left - (rect.getBounds().left + rect.getBounds().width)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x + 0.2), circle.getPosition().y));
            //std::cout << "RIGHT\n";
        }
        else if (((circle.getBounds().left + circle.getBounds().width) - rect.getBounds().left) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x - 0.2), circle.getPosition().y));
            //std::cout << "LEFT\n";
        }
        hasCollided = true;
    }

    cornerDistanceSQ = (float)pow((circleDistanceX - rect.getBounds().width / 2),2) +
        pow((circleDistanceY - rect.getBounds().height / 2),2);

    if (cornerDistanceSQ <= (pow((circle.getBounds().width / 2), 2)) && rect.getTileType() == tileType);
    {
        if ((circle.getBounds().left - (rect.getBounds().left + rect.getBounds().width)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x + 0.2), circle.getPosition().y));
            //std::cout << "RIGHT\n";
        }
        else if (((circle.getBounds().left + circle.getBounds().width) - rect.getBounds().left) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x - 0.2), circle.getPosition().y));
            //std::cout << "LEFT\n";
        }
        else if (((circle.getBounds().top + circle.getBounds().height) - rect.getBounds().top) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y - 0.2));
            //std::cout << "UP\n";
        }
        else if ((circle.getBounds().top - (rect.getBounds().top + rect.getBounds().height)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y + 0.2));
            //std::cout << "DOWN\n";
        }
        hasCollided = true;
    }
    return hasCollided;
}

bool CollissionMan::intersectCircCirc(GameEntity& circle1, GameEntity& circle2)
{
    return (pow(((circle2.getBounds().left + (circle2.getBounds().width / 2)) - (circle1.getBounds().left + (circle1.getBounds().width) / 2)), 2) +
        pow(((circle1.getBounds().top + (circle1.getBounds().height / 2)) - (circle2.getBounds().top + (circle2.getBounds().height) / 2)), 2) <=
        pow((circle1.getBounds().height / 2) + (circle2.getBounds().height / 2), 2));
}

bool CollissionMan::intersectRectPoint(Tile& rect, sf::Vector2f point)
{
    sf::Vector2i tilePos_high(
        (rect.getPosition().x - (rect.getSprite().getLocalBounds().width * rect.getSprite().getScale().x) / 2),
        (rect.getPosition().y - (rect.getSprite().getLocalBounds().height * rect.getSprite().getScale().y) / 2));

    sf::Vector2i tilePos_low(
        (rect.getPosition().x + (rect.getSprite().getLocalBounds().width * rect.getSprite().getScale().x) / 2),
        (rect.getPosition().y + (rect.getSprite().getLocalBounds().height * rect.getSprite().getScale().y) / 2));


    return ((tilePos_high.x < point.x&& tilePos_low.x > point.x) && (tilePos_high.y < point.y&& tilePos_low.y > point.y));
}



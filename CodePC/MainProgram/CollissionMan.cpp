#include "CollissionMan.h"

CollissionMan::CollissionMan()
{
}

CollissionMan::~CollissionMan()
{
}

bool CollissionMan::intersectCircRect(GameEntity& circle, Tile& rect)
{
    circleDistanceX = abs(circle.getBounds().left - rect.getBounds().left);
    circleDistanceY = abs(circle.getBounds().top - rect.getBounds().top);

    if (circleDistanceX > (rect.getBounds().width/2 + circle.getBounds().width/2)) 
    { 
        return false; 
    }
    if (circleDistanceY > (rect.getBounds().height/2 + circle.getBounds().width/2)) 
    { 
        return false; 
    }

    if (circleDistanceX <= (rect.getBounds().width / 2)/* && (rect.getTileType() == 0 || rect.getTileType() == 0)*/)
    { 
        
        if (((circle.getBounds().top + circle.getBounds().height) - rect.getBounds().top) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y - 1));
            std::cout << "UP\n";
        }
        else if ((circle.getBounds().top - (rect.getBounds().top + rect.getBounds().height)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y + 1));
            std::cout << "DOWN\n";
        }
        
        return true; 
    }
    if (circleDistanceY <= (rect.getBounds().height / 2)/* && (rect.getTileType() == 0 || rect.getTileType() == 0)*/)
    { 
        if ((circle.getBounds().left - (rect.getBounds().left + rect.getBounds().width)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x + 1), circle.getPosition().y));
            std::cout << "RIGHT\n";
        }
        else if (((circle.getBounds().left + circle.getBounds().width) - rect.getBounds().left) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x - 1), circle.getPosition().y));
            std::cout << "LEFT\n";
        }
        return true; 
    }

    cornerDistanceSQ = pow((circleDistanceX - rect.getBounds().width / 2),2) +
        pow((circleDistanceY - rect.getBounds().height / 2),2);

    if (cornerDistanceSQ <= (pow((circle.getBounds().width / 2), 2))/* && (rect.getTileType() == 0 || rect.getTileType() == 0)*/)
    {
        if ((circle.getBounds().left - (rect.getBounds().left + rect.getBounds().width)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x + 1), circle.getPosition().y));
            std::cout << "RIGHT\n";
        }
        else if (((circle.getBounds().left + circle.getBounds().width) - rect.getBounds().left) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x - 1), circle.getPosition().y));
            std::cout << "LEFT\n";
        }
        else if (((circle.getBounds().top + circle.getBounds().height) - rect.getBounds().top) < 25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y - 1));
            std::cout << "UP\n";
        }
        else if ((circle.getBounds().top - (rect.getBounds().top + rect.getBounds().height)) > -25)
        {
            circle.setPosition(sf::Vector2f((circle.getPosition().x), circle.getPosition().y + 1));
            std::cout << "DOWN\n";
        }
        return true;
    }
    return false;
}

bool CollissionMan::intersectCircCirc(GameEntity& circle1, GameEntity& circle2)
{
    return (pow(((circle2.getBounds().left + (circle2.getBounds().width / 2)) - (circle1.getBounds().left + (circle1.getBounds().width) / 2)), 2) +
        pow(((circle1.getBounds().top + (circle1.getBounds().height / 2)) - (circle2.getBounds().top + (circle2.getBounds().height) / 2)), 2) <=
        pow((circle1.getBounds().height / 2) + (circle2.getBounds().height / 2), 2));
}



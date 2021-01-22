#pragma once
#include "GameEntity.h"
class Soldier : public GameEntity
{
private:
    sf::IntRect intRect;
    string name;
    int health;
    float speed;

public:
    Soldier(string fileName, string name, int health = 3);
    ~Soldier();

    virtual void move() = 0;
};
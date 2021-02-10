#pragma once
#include "GameEntity.h"
class Soldier : public GameEntity
{
private:
    sf::IntRect intRect;
    std::string name;

protected:
    int health;
    float speed;

    int updateTimer;
    int counter;

public:
    Soldier(std::string fileName, std::string name, int health = 3);
    ~Soldier();
    void loseHealth(int dmg = 1);
    int getHealth()const;

    virtual void move() = 0;
};
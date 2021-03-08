#pragma once
#include "GameEntity.h"
#include "Weapon.h"
#include "Bullet.h"

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

    bool isPlayer;
    bool reloading;
    sf::Vector2f inputDirection;
    Weapon* currentWeapon;

public:
    Soldier(std::string fileName = "character.png", std::string name = "joe", int health = 3);
    ~Soldier();
    void loseHealth(int dmg = 1);
    void setIsPlayer(bool state);
    bool getIsPlayer()const;
    bool isAbleToShoot()const;
    int getHealth()const;
    int getDmg()const;
    sf::Vector2f getInputDirection()const;
    void rotateSprite(sf::Vector2f pos);

    void move();
    Bullet shoot(sf::Vector2f direction);

    // Inherited via GameEntity
    virtual void update(const float deltaTime) override;
};
#pragma once
#include "GameEntity.h"
#include "Bullet.h"

class WeaponType;
class Tile;

class Soldier : public GameEntity
{
private:
    sf::IntRect intRect;
    std::string name;

protected:
    int health;
    float speed;
    int ID;
    bool collided;

    int updateTimer;
    int counter;

    bool isPlayer;
    bool reloading;
    sf::Vector2f inputDirection;
    WeaponType* currentWeapon;

    std::vector<Tile*> nodes;

public:
    Soldier(std::string fileName = "character_1.png", std::string name = "joe", int health = 3);
    ~Soldier();
    void loseHealth(int dmg = 1);
    void setIsPlayer(bool state);
    void setID(int ID);
    void setWeapon(WeaponType *sourceWeapon);
    bool getIsPlayer()const;
    bool isAbleToShoot()const;
    bool getColl()const;
    void setColl(bool thing);
    int getHealth()const;
    int getDmg()const;
    int getID()const;

    sf::Vector2f getInputDirection()const;
    void rotateSprite(sf::Vector2f pos);

    void move();
    Bullet shoot(sf::Vector2f direction);

    // Inherited via GameEntity
    virtual void update(const float deltaTime) override;

    std::vector<Tile*>& getNodes();
    void addNode(Tile*);
    void setNodes(std::vector<Tile*>& inputNodes);
    void emplaceNode(int previousNode, Tile*); //place node after given position
};
#include "Soldier.h"
#include "WeaponType.h"
#include "Tile.h"

Soldier::Soldier(std::string fileName, std::string name, int health) :
	GameEntity(fileName),
	health(health),
	speed(300),
	isPlayer(false),
	reloading(false),
	currentWeapon(nullptr),
	counter(0),
	collided(false),
	walkCounter(0),
	walkTimer(0),
	xDir(0),
	yDir(0)
{	

}

Soldier::~Soldier()
{
	if (currentWeapon != nullptr)
	{
		delete currentWeapon;
		currentWeapon = nullptr;
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}
}

void Soldier::loseHealth(int dmg)
{
	this->health -= dmg;
}

void Soldier::setIsPlayer(bool state)
{
	this->isPlayer = state;
}

void Soldier::setID(int ID)
{
	this->ID = ID;
}

void Soldier::setWeapon(WeaponType *sourceWeapon)
{
	currentWeapon = sourceWeapon;
}

bool Soldier::getIsPlayer() const
{
	return this->isPlayer;
}

bool Soldier::isAbleToShoot() const
{
	return !this->reloading;
}

bool Soldier::getColl() const
{
	return collided;
}

void Soldier::setColl(bool thing)
{
	collided = thing;
}

int Soldier::getHealth() const
{
	return this->health;
}

int Soldier::getDmg() const
{
	return this->currentWeapon->getDmg();
}

int Soldier::getID() const
{
	return this->ID;
}

sf::Vector2f Soldier::getInputDirection(float deltaTime) const
{
	return this->inputDirection*deltaTime;
}

void Soldier::rotateSprite(sf::Vector2f pos)
{
	float hypotenuse = sqrt((pos.x - this->sprite.getPosition().x) * (pos.x - this->sprite.getPosition().x) + (pos.y - this->sprite.getPosition().y) * (pos.y - this->sprite.getPosition().y));
	if (this->sprite.getPosition().x < pos.x)
	{
		this->sprite.setRotation(((asin((pos.y - this->sprite.getPosition().y) / hypotenuse)) / 3.141592) * 180);
	}
	else if (this->sprite.getPosition().x > pos.x)
	{
		this->sprite.setRotation(180 - ((asin((pos.y - this->sprite.getPosition().y) / hypotenuse)) / 3.141592) * 180);
	}

}

Bullet Soldier::shoot(sf::Vector2f direction)
{
	if (currentWeapon != nullptr)
	{
		sf::Vector2f offset = (direction / 100.f);
		float rotation = 0;
		direction.x += (int(offset.x) * (rand() % 3 - 1) * (rand() % 10)) * this->currentWeapon->getSpreadMultiplier();
		direction.y += (int(offset.y) * (rand() % 3 - 1) * (rand() % 10)) * this->currentWeapon->getSpreadMultiplier();

		float squaredLength = direction.x * direction.x + direction.y * direction.y;

		if (direction.x > 0)
		{
			rotation = (asin((direction.y) / sqrt(squaredLength)) / 3.141592) * 180;
		}

		else if (direction.x < 0)
		{
			rotation = 180 - (asin((direction.y) / sqrt(squaredLength)) / 3.141592) * 180;
		}

		//Normalises direction

		if (squaredLength > 0)
		{
			direction.x /= sqrt(squaredLength);
			direction.y /= sqrt(squaredLength);
		}

		this->reloading = true;

		return Bullet(rotation, direction, this->getPosition(), this->currentWeapon->getDmg(), this->currentWeapon->getSpeed(), this->ID);
	}
}

void Soldier::update(const float deltaTime)
{
	if (this->isPlayer)
	{
		this->inputDirection = sf::Vector2f(0, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->inputDirection.x = -this->speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->inputDirection.x = this->speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->inputDirection.y = -this->speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->inputDirection.y = this->speed;
		}

		this->sprite.move(this->inputDirection*deltaTime);
	}
	else
	{
		//AI movement
		if (walkCounter == 0)
		{
			xDir = rand() % 3 - 1;
			yDir = rand() % 3 - 1;
			walkTimer = rand() % 11 + 10;
		}
		walkCounter = (walkCounter + 1) % walkTimer;
		this->sprite.move(this->speed/2*deltaTime*xDir, this->speed/2 * deltaTime * yDir);
	}

	if (this->reloading)
	{
		this->counter = (this->counter + 1) % this->currentWeapon->getReloadTime();
		if (counter == 0)
		{
			this->reloading = false;
		}
	}
}

std::vector<Tile*> &Soldier::getNodes()
{
	return nodes;
}

void Soldier::addNode(Tile* inputNode)
{
	nodes.push_back(inputNode);
}

void Soldier::emplaceNode(int previousNode, Tile* inputNode)
{

	for (int i = previousNode; i < nodes.size(); i++)
	{
		if (previousNode != 0)
		{
			Tile tempTile = *nodes[i];
			delete nodes[i];
			nodes[i] = nullptr;
			nodes.pop_back();

			nodes.push_back(new Tile(tempTile));
		}
		
		if (i == previousNode) nodes.push_back(inputNode);
	}
}

void Soldier::setNodes(std::vector<Tile*> &inputNodes)
{
	nodes = inputNodes;
}

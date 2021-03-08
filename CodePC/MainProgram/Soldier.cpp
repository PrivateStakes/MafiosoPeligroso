#include "Soldier.h"

Soldier::Soldier(std::string fileName, std::string name, int health):
	GameEntity(fileName),
	health(health),
	speed(5),
	isPlayer(false),
	reloading(false)
{	
	this->currentWeapon = new Weapon(GunType::pistol);
}

Soldier::~Soldier()
{
	//delete this->currentWeapon;
}

void Soldier::loseHealth(int dmg)
{
	this->health -= dmg;
}

void Soldier::setIsPlayer(bool state)
{
	this->isPlayer = state;
}

bool Soldier::getIsPlayer() const
{
	return this->isPlayer;
}

bool Soldier::isAbleToShoot() const
{
	return !this->reloading;
}

int Soldier::getHealth() const
{
	return this->health;
}

int Soldier::getDmg() const
{
	return this->currentWeapon->getDmg();
}

sf::Vector2f Soldier::getInputDirection() const
{
	return this->inputDirection;
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

void Soldier::move()
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

		this->sprite.move(this->inputDirection);
	}
	else
	{
		//AI movement
		this->sprite.move((rand() % 3 - 1) * 5, (rand() % 3 - 1) * 5);
		this->sprite.setRotation(((rand() % 360) / 180.f) * 3.141592);
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

Bullet Soldier::shoot(sf::Vector2f direction)
{
	//float offset1 = (abs(this->sprite.getPosition().x - direction.x) + abs(this->sprite.getPosition().y - direction.y))/2;
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

	return Bullet(rotation, direction, this->sprite.getPosition(), this->currentWeapon->getDmg(), this->currentWeapon->getSpeed());
}

void Soldier::update(const float deltaTime)
{
}



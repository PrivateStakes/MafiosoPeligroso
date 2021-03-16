#include "Tile.h"

Tile::Tile(std::string filename) :
	GameEntity(filename),
	texturePath(filename),
	hp(5)
{
	tileType = 0;
	travelDistance = 999999999;
	visitedByAlgorithm = false;
}

Tile::~Tile()
{

}

void Tile::update(const float deltaTime)
{
	sprite.setPosition((sf::Vector2f)((sf::Vector2i)sprite.getPosition()));
}

std::string Tile::getTexturePath()
{
	return texturePath;
}

char Tile::getTileType()
{
	return tileType;
}

void Tile::setTileType(char input)
{
	tileType = input;
}

bool Tile::getVisitedByAlgorithm()
{
	return visitedByAlgorithm;
}

void Tile::setVisitedByAlgorithm(bool input)
{
	visitedByAlgorithm = input;
}

int Tile::getTravelDistance()
{
	return travelDistance;
}

void Tile::setTravelDistance(int input)
{
	travelDistance = input;
}

int Tile::getHP()
{
	return hp;
}

void Tile::setHP(int dmg)
{
	hp -= dmg;
}

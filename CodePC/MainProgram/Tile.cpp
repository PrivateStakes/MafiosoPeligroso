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
	previousNode = nullptr;
	nextNode = nullptr;
}
 
void Tile::update(const float deltaTime)
{
	sprite.setPosition((sf::Vector2f)((sf::Vector2i)sprite.getPosition()));
}

void Tile::resetPathfindingValues()
{
	visitedByAlgorithm = false;
	travelDistance = 999999999;
	weightDistance = 999999999;
	hueristicDistance = 999999999;

	previousNode = nullptr;
	nextNode = nullptr;
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

float  Tile::getWeightDistance()
{
	return weightDistance;
}

void  Tile::setWeightDistance(float input)
{
	weightDistance = input;
}

float Tile::getHueristicDistance()
{
	return hueristicDistance;
}

void Tile::setHueristicDistance(sf::Vector2i start, sf::Vector2i end)
{
	float tempX = std::abs(start.x - end.x);
	float tempY = std::abs(start.y - end.y);

	//hueristicDistance = sqrt((tempX * tempX) + (tempY * tempY));
	hueristicDistance = tempX + tempY;
}

Tile* Tile::getPreviousNode()
{
	return previousNode;
}

void Tile::setPreviousNode(Tile* inputTile)
{
	if (this != nullptr)//(getTileType() == 'e' || getTileType() == 'c' || getTileType() == 'd')
	{
		previousNode = nullptr;
		previousNode = inputTile;
	}
}

Tile* Tile::getNextNode()
{
	return nextNode;
}

void Tile::setNextNode(Tile* inputTile)
{
	if (this != nullptr)//(getTileType() == 'e' || getTileType() == 'c' || getTileType() == 'd')
	{
		nextNode = nullptr;
		nextNode = inputTile;
	}
}
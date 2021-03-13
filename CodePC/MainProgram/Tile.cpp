#include "Tile.h"

Tile::Tile(std::string filename) :
	GameEntity(filename),
	texturePath(filename)
{
	tileType = 0;
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

Tile* Tile::getPreviousNode()
{
	return previousNode;
}

void Tile::setPreviousNode(Tile* inputTile)
{
	previousNode = inputTile;
}

Tile* Tile::getNextNode()
{
	return nextNode;
}

void Tile::setNextNode(Tile* inputTile)
{
	nextNode = inputTile;
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
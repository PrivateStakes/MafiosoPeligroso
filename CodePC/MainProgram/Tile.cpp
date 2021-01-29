#include "Tile.h"

Tile::Tile(std::string filename) :
	GameEntity(filename)
{

}

Tile::~Tile()
{

}

void Tile::update(const float deltaTime)
{
	sprite.setPosition((sf::Vector2f)((sf::Vector2i)sprite.getPosition()));
}

int Tile::getTileType()
{
	return tileType;
}

void Tile::setTileType(int input)
{
	tileType = input;
}
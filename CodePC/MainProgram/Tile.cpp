#include "Tile.h"

Tile::Tile(std::string filename) :
	GameEntity(filename)
{
	tileType = 0;
}

Tile::~Tile()
{

}

void Tile::update(const float deltaTime)
{
	sprite.setPosition((sf::Vector2f)((sf::Vector2i)sprite.getPosition()));
}

char Tile::getTileType()
{
	return tileType;
}

void Tile::setTileType(char input)
{
	tileType = input;
}
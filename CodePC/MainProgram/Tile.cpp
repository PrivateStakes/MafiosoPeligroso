#include "Tile.h"

Tile::Tile(std::string filename) :
	GameEntity(filename),
	texturePath(filename)
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
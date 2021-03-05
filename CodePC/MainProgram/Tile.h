#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:
	char tileType;
	std::string texturePath;

public:
	Tile(std::string filename);
	~Tile();

	std::string getTexturePath();
	char getTileType();
	void setTileType(char input);
	virtual void update(const float deltaTime) override;
};


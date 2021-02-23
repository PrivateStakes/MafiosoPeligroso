#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:
	char tileType;

public:
	Tile(std::string filename);
	~Tile();

	char getTileType();
	void setTileType(char input);
	virtual void update(const float deltaTime) override;
};


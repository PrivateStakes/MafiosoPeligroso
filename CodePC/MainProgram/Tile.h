#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:
	int tileType = 0;

public:
	Tile(std::string filename);
	~Tile();

	int getTileType();
	void setTileType(int input);
	virtual void update(const float deltaTime) override;
};


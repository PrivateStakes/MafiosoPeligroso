#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:


public:
	Tile(std::string filename);
	~Tile();

	virtual void update(const float deltaTime) override;
};


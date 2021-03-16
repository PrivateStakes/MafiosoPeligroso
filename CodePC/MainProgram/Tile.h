#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:
	char tileType;
	std::string texturePath;

	//Djikstra stuff
	bool visitedByAlgorithm;
	int travelDistance;
	int hp;

public:
	Tile(std::string filename);
	~Tile();

	std::string getTexturePath();
	char getTileType();
	void setTileType(char input);
	virtual void update(const float deltaTime) override;


	bool getVisitedByAlgorithm();
	void setVisitedByAlgorithm(bool);

	int getTravelDistance();
	void setTravelDistance(int);

	int getHP();
	void setHP(int);
};


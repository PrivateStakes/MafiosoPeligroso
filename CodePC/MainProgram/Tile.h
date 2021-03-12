#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:
	char tileType;
	std::string texturePath;

	//Djikstra stuff
	Tile* previousNode;
	Tile* nextNode;
	bool visitedByAlgorithm;
	int travelDistance;

public:
	Tile(std::string filename);
	~Tile();

	std::string getTexturePath();
	char getTileType();
	void setTileType(char input);
	virtual void update(const float deltaTime) override;


	Tile* getPreviousNode();
	void setPreviousNode(Tile*);

	Tile* getNextNode();
	void setNextNode(Tile*);

	bool getVisitedByAlgorithm();
	void setVisitedByAlgorithm(bool);

	int getTravelDistance();
	void setTravelDistance(int);
};


#pragma once
#include "GameEntity.h"

class Tile : public GameEntity
{
private:
	char tileType;
	std::string texturePath;

	Tile* previousNode;
	Tile* nextNode;

	//Djikstra stuff
	bool visitedByAlgorithm;
	int travelDistance;
	float weightDistance;	 //represents our current best guess as to how short a path from start to finish can be if it goes through n (edge-wise)
	float hueristicDistance; //exact distance to end point (Euclidean)

	int hp;	//Not Djikstra stuff, Morgan >:(

public: 
	Tile(std::string filename);
	~Tile();

	std::string getTexturePath();
	char getTileType();
	void setTileType(char input);
	virtual void update(const float deltaTime) override;
	void resetPathfindingValues();

	bool getVisitedByAlgorithm();
	void setVisitedByAlgorithm(bool);

	int getTravelDistance();
	void setTravelDistance(int);

	Tile* getPreviousNode();
	void setPreviousNode(Tile*);

	Tile* getNextNode();
	void setNextNode(Tile*);

	int getHP();
	void setHP(int);

	float getWeightDistance();
	void setWeightDistance(float);

	float getHueristicDistance();
	void setHueristicDistance(sf::Vector2i start, sf::Vector2i end);
};
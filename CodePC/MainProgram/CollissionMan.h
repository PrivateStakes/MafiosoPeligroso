#pragma once
#include <cmath>
#include "GameEntity.h"

class CollissionMan
{
protected:

private:
	float circleDistanceX;
	float circleDistanceY;
	float cornerDistanceSQ;

public:
	CollissionMan();
	~CollissionMan();

	virtual bool intersects(GameEntity circle, GameEntity rect);


};
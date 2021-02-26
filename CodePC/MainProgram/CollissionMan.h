#pragma once
#include <cmath>
#include <math.h>
#include "GameEntity.h"
#include <iostream>

class CollissionMan
{
protected:

private:
	float circleDistanceX = 0;
	float circleDistanceY = 0;
	float cornerDistanceSQ = 0;

public:
	CollissionMan();
	~CollissionMan();

	virtual bool intersectCircRect(GameEntity& circle, GameEntity& rect);

	virtual bool intersectCircCirc(GameEntity& circle1, GameEntity& circle2);


};
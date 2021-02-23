#include "CollissionMan.h"

bool CollissionMan::intersects(GameEntity circle, GameEntity rect)
{
    circleDistanceX = abs(circle.getBounds().x - rect.getBounds().x);
    circleDistanceY = abs(circle.getBounds().y - rect.getBounds().y);

    if (circleDistanceX > (rect.getBounds().width / 2 + circle.getBounds().width/2)) { return false; }
    if (circleDistanceY > (rect.getBounds().height / 2 + circle.getBounds().width/2)) { return false; }

    if (circleDistanceX <= (rect.getBounds().width / 2)) { return true; }
    if (circleDistanceY <= (rect.getBounds().height / 2)) { return true; }

    cornerDistanceSQ = (circleDistanceX - rect.getBounds().width / 2) ^ 2 +
        (circleDistanceY - rect.getBounds().height / 2) ^ 2;

    return (cornerDistanceSQ <= ((circle.getBounds().width/2) ^ 2));
}

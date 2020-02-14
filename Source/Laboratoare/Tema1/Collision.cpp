#include <vector>
#include <iostream>
#include <algorithm>    // std::min
#include <math.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Collision.h"

using namespace std;

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckCollision(float birdCentreX, float birdCentreY, float positionX, float positionY, float length, float width) {
	// handling circle - rectangle collisions
	float squareRadius = pow(radius, 2);

	distX = birdCentreX - max(positionX, min(birdCentreX, positionX + width));
	distY = birdCentreY - max(positionY, min(birdCentreY, positionY + length));

	finalDistX = pow(distX, 2);
    finalDistY = pow(distY, 2);

	return (finalDistX + finalDistY) < squareRadius;
}

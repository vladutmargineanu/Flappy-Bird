#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <math.h> 
#include <Core/Engine.h>

class Collision
{
public:
	Collision();
	~Collision();

	bool CheckCollision(float birdCentreX, float birdCentreY, float positionX, float positionY, float length, float width);

protected:
	float radius = 20; // circle radius that aproximate the bird
	float distX;
	float distY;
	float finalDistX;
	float finalDistY;
};
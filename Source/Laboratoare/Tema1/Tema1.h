#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <math.h> 
#include <Core/Engine.h>
#include "Collision.h"

#define NUMBER_RECTANGLES 4

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix0;
	glm::mat3 modelMatrix1;
	glm::mat3 modelMatrix2;
	glm::mat3 modelMatrix3;
	glm::mat3 modelMatrix4;
	glm::mat3 modelMatrix5;
	glm::mat3 modelMatrix6;
	glm::mat3 modelMatrix7;
	glm::mat3 modelMatrix8;
	glm::mat3 modelMatrix9;
	glm::mat3 modelMatrix10;
	glm::vec3 birdCorner = glm::vec3(600, 360, 0);
	glm::vec3 treeCorner = glm::vec3(400, 0, 0);
	int dificultyLevel = -pow(NUMBER_RECTANGLES, NUMBER_RECTANGLES);
	int nextLevel = 0;
	int maxLevel = pow(NUMBER_RECTANGLES, NUMBER_RECTANGLES);
	float birdWidth = 50;
	float birdLength = 50;
	float birdRadius = 20;
	float birdCentreX = 670;
	float birdCentreY = 385;
	int i;
	float stepScaleUp;
	float score;
	float translateX[NUMBER_RECTANGLES];
	float translateBirdY;
	float scaleX[NUMBER_RECTANGLES];
	float translateDownY;
	float translateUpY;
	float angularStep = 0;
	float angularWingStep = 0;
	float cx, cy;
	bool isScaleValid;
	bool direction = false;
	float rotation = 0;
	glm::vec3 corner = glm::vec3(0, 0, 0);
	float rectangleSideWidth = 100;
	float rectangleSideLength = 350;
	float distRctangles = 250;
	float initialPos = 0;
	bool collisionDown;
	bool collisionUp;
	float increaseMoveRectangle;
	int numberOfCollision;
	float birdCentreBigX;
	Collision newCollision;
};
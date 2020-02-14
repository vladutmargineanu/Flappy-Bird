#include "Tema1.h"

#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Collision.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// initialize tx and ty (the translation steps)
	translateX[0] = initialPos;
	translateDownY = 0;
	translateUpY = 490;
	translateBirdY = 0;
	numberOfCollision = 0;
	score = 0;
	increaseMoveRectangle = 0;
	stepScaleUp = 500;
	// Circle centre that aproximate the bird
	birdCentreBigX = 650;
	collisionUp = false;
	collisionDown = false;
	// initialize tx (the translate factor)
	for (i = 1; i < NUMBER_RECTANGLES; ++i) {
		translateX[i] = translateX[i-1] + distRctangles + rectangleSideWidth;
	}

	// initialize sx (the scale factor)
	/* initialize random seed: */
	srand(time(NULL));

	/* generate number between 0 and 1 */
	for (i = 0; i < NUMBER_RECTANGLES; ++i) {
		scaleX[i] = ((float)rand() / (RAND_MAX));
	}

	// Create rectangle for the scene
	Mesh* rectangle = Object2D::CreateRectangle("rectangle", corner, rectangleSideWidth,
		rectangleSideLength, glm::vec3(0, 0, 0), true);
	AddMeshToList(rectangle);

	// initialize angularStep
	angularStep = 0;

	// Initialize the corner and dimension for triangle and trianlge (bird creation)
	glm::vec3 corner_rectangle = birdCorner; 
	glm::vec3 corner_triangle = corner_rectangle + glm::vec3(90, 10, 0);
	glm::vec3 corner_wing = corner_rectangle + glm::vec3(20, 10, 0);

	float rectangleBirdWidth = birdWidth;
	float rectangleBirdLength = birdLength;
	float triangleBirdWidth = birdWidth / 2;;
	float triangleBirdLength = birdLength / 2;
	increaseMoveRectangle = 50;

	// Create the bird: one rectangle, one trianlge and one circle
	Mesh* rectangleBird = Object2D::CreateRectangle("rectangle bird", corner_rectangle, rectangleBirdWidth,
		rectangleBirdLength, glm::vec3(0.9, 1, 0.1), true);
	AddMeshToList(rectangleBird);

	Mesh* triangleBird = Object2D::CreateTriangle("triangle bird", corner_triangle, triangleBirdWidth,
		triangleBirdLength, glm::vec3(1, 0.5, 0), true);
	AddMeshToList(triangleBird);

	Mesh* triangleWingBird = Object2D::CreateTriangle("wing bird", corner_wing, 1.5f * triangleBirdWidth,
		1.5f * triangleBirdLength, glm::vec3(1, 0, 0), true);
	AddMeshToList(triangleWingBird);

	Mesh* circleBird = Object2D::CreateCircle("circle bird", birdRadius,
		birdCentreX, birdCentreY, glm::vec3(0.9, 1, 0.1), true);
	AddMeshToList(circleBird);

	Mesh* circleBirdEye = Object2D::CreateCircle("eye bird", birdRadius / 4.0f,
		birdCentreX + 10.0f, birdCentreY + 10.0f, glm::vec3(0, 0, 0), true);
	AddMeshToList(circleBirdEye);

	Mesh* rectangle_grass = Object2D::CreateRectangle("rectangle_grass", corner, 1280,
		100, glm::vec3(0, 0.9, 0), true);
	AddMeshToList(rectangle_grass);

	Mesh* circleTree = Object2D::CreateCircle("circle tree", 4 * birdRadius,
		birdCentreX - 250, birdCentreY - 50, glm::vec3(0.6,0.5,0.1), true);
	AddMeshToList(circleTree);

	Mesh* rectangleTree = Object2D::CreateRectangle("rectangle tree", treeCorner, rectangleSideWidth / 2,
		rectangleSideLength, glm::vec3(0.6, 0.2, 0), true);
	AddMeshToList(rectangleTree);

	Mesh* circleSun = Object2D::CreateCircle("sun", 3 * birdRadius,
		40, 690, glm::vec3(0.9, 1, 0.1), true);
	AddMeshToList(circleSun);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {

	// For scale the rectangle up
	angularStep = deltaTimeSeconds;
	modelMatrix0 = glm::mat3(1);
	modelMatrix3 = glm::mat3(1);
	modelMatrix4 = glm::mat3(1);
	modelMatrix5 = glm::mat3(1);
	modelMatrix6 = glm::mat3(1);
	modelMatrix7 = glm::mat3(1);
	modelMatrix8 = glm::mat3(1);
	modelMatrix9 = glm::mat3(1);
	modelMatrix10 = glm::mat3(1);

	// Modify the angle for the wing
	if (direction == true) {

		if (angularWingStep >= -M_PI / 6) {
			angularWingStep -= deltaTimeSeconds * 10;
		}
		else if (angularWingStep <= M_PI / 7) {
			angularWingStep += deltaTimeSeconds * 10;
		}
	}
	// When the space button is off
	else {
		angularWingStep = 0;
	}
	// Modify the angle for rotation for the bird, up or down (Oy axes)
	if (direction == true) {
		// The bird go up
		angularStep += deltaTimeSeconds * 0.5;
	}
	else {
		// The bird go down
		angularStep = (-3) * angularStep;
	}

	// Translate the bird when she fly up or down
	modelMatrix6 *= Transform2D::Translate(0, translateBirdY);
	// Rotate the bird when she fly up or down
	modelMatrix6 *= Transform2D::Translate(birdCentreX, birdCentreY);
	modelMatrix6 *= Transform2D::Rotate(4 * angularStep);
	modelMatrix6 *= Transform2D::Translate(-birdCentreX, -birdCentreY);
	RenderMesh2D(meshes["eye bird"], shaders["VertexColor"], modelMatrix6);

	modelMatrix7 *= Transform2D::Translate(0, translateBirdY);

	modelMatrix7 *= Transform2D::Translate(birdCentreX, birdCentreY);
	modelMatrix7 *= Transform2D::Rotate(angularWingStep);
	modelMatrix7 *= Transform2D::Translate(-birdCentreX, -birdCentreY);
	RenderMesh2D(meshes["wing bird"], shaders["VertexColor"], modelMatrix7);

	modelMatrix3 *= Transform2D::Translate(0, translateBirdY);

	modelMatrix3 *= Transform2D::Translate(birdCentreX, birdCentreY);
	modelMatrix3 *= Transform2D::Rotate(4 * angularStep);
	modelMatrix3 *= Transform2D::Translate(-birdCentreX, -birdCentreY);
	RenderMesh2D(meshes["rectangle bird"], shaders["VertexColor"], modelMatrix3);

	modelMatrix4 *= Transform2D::Translate(0, translateBirdY);

	modelMatrix4 *= Transform2D::Translate(birdCentreX, birdCentreY);
	modelMatrix4 *= Transform2D::Rotate(4 * angularStep);
	modelMatrix4 *= Transform2D::Translate(-birdCentreX, -birdCentreY);
	RenderMesh2D(meshes["circle bird"], shaders["VertexColor"], modelMatrix4);

	modelMatrix5 *= Transform2D::Translate(0, translateBirdY);

	modelMatrix5 *= Transform2D::Translate(birdCentreX, birdCentreY);
	modelMatrix5 *= Transform2D::Rotate(4 * angularStep);
	modelMatrix5 *= Transform2D::Translate(-birdCentreX, -birdCentreY);
	RenderMesh2D(meshes["triangle bird"], shaders["VertexColor"], modelMatrix5);

	// Modify the y coordinate for the bird
	if (translateBirdY > -360) {
		translateBirdY -= deltaTimeSeconds * 150;

		if (translateBirdY < -360) {
			translateBirdY = -360;
		}
	}

	for (i = 0; i < NUMBER_RECTANGLES; ++i) {
		// Model matrix for the two rectangle up and down for scene
		modelMatrix1 = glm::mat3(1);
		modelMatrix2 = glm::mat3(1);
		// Calculate the variables for translation
		translateX[i] -= deltaTimeSeconds;
		
		if (translateX[i] <= -150) {
			translateX[i] = 1280;
			// The score got the number of frames 
			score += 1; 
		}

		if (scaleX[i] >= 1) {
			isScaleValid = false;
		}

		if (scaleX[i] < 0.2) {
			isScaleValid = true;
		}
		// Calculate the variables for scale, dificullty change (3 states)
		if (nextLevel < maxLevel) {

			if (isScaleValid) {
				scaleX[i] += deltaTimeSeconds / (rand() % 10 + 5);
			}
			else {
				scaleX[i] -= deltaTimeSeconds / (rand() % 10 + 5);
			}
			// Increase the movement, modify the translate coordinates
			translateX[i] -= deltaTimeSeconds * increaseMoveRectangle;

		}
		else if (nextLevel > maxLevel && dificultyLevel < maxLevel * NUMBER_RECTANGLES) {

			if (isScaleValid) {
				scaleX[i] += deltaTimeSeconds;
			}
			else {
				scaleX[i] -= deltaTimeSeconds;
			}
			// Increase the movement, modify the translate coordinates
			translateX[i] -= deltaTimeSeconds * 1.5 * increaseMoveRectangle;
		}
		else {

			if (isScaleValid) {
				scaleX[i] += deltaTimeSeconds / (i + 1);
			}
			else {
				scaleX[i] -= deltaTimeSeconds / (i + 1);
			}
			// Increase the movement, modify the translate coordinates
			translateX[i] -= deltaTimeSeconds * 2 * increaseMoveRectangle;
		}

		// Translate down
		modelMatrix1 *= Transform2D::Translate(translateX[i], translateDownY);

		// Scale down
		modelMatrix1 *= Transform2D::Scale(1, scaleX[i]);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix1);

		// Translate up
		modelMatrix2 *= Transform2D::Translate(translateX[i], translateUpY);

		//Scale up
		modelMatrix2 *= Transform2D::Translate(translateX[i], stepScaleUp / 2);
		modelMatrix2 *= Transform2D::Scale(1, scaleX[i]);
		modelMatrix2 *= Transform2D::Translate(-translateX[i], -(stepScaleUp / 2));
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix2);

	}
	// Check collision for the all rectangles in the scene
	for (i = 0; i < NUMBER_RECTANGLES; ++i) {

		collisionUp = newCollision.CheckCollision(birdCentreBigX, translateBirdY + 360, translateX[i], translateDownY,
			rectangleSideLength * scaleX[i], rectangleSideWidth);
		collisionDown = newCollision.CheckCollision(birdCentreBigX, translateBirdY + 360, translateX[i], translateUpY,
			rectangleSideLength * scaleX[i], rectangleSideWidth);

		if (collisionUp || collisionDown) {
			numberOfCollision += 1;
			cout << "Collision! Watch out!\n";
			cout << "The number of collisions in this moment is = " << numberOfCollision << endl;
			cout << "The score in this moment is:" << score << endl;
			cout << "The maximum collisions are 500!" << endl;
			cout << endl;
			if (numberOfCollision >= 500) {
				cout << "The final score is:" << score << endl;
				cout << "The TOTAL NUMBER of collisions = " << numberOfCollision << endl;
				cout << "Game Over" << endl;
				Engine::Exit();
				exit(0);
			}
		}
	}
		// Increase the speed for the rectangles
		increaseMoveRectangle += 0.2f;
		// Change de level in time
		dificultyLevel++;

		if (nextLevel <= maxLevel && dificultyLevel >= nextLevel) {
			nextLevel += NUMBER_RECTANGLES;
		}
		// Repeat all three scene with speed changed
		if (dificultyLevel > maxLevel* pow(NUMBER_RECTANGLES, 2)) {
			dificultyLevel = -pow(NUMBER_RECTANGLES, NUMBER_RECTANGLES);
			nextLevel = 0;
			increaseMoveRectangle = 0;
			cout << endl;
			cout << "You got the maximum LEVEL! The score is: " << score << endl;
			cout << "Congratulations!!\n";
			cout << endl; 
			numberOfCollision = 0;
			cout << "Next GAME LEVEL!!\n";
		}
		RenderMesh2D(meshes["rectangle_grass"], shaders["VertexColor"], modelMatrix0);
		RenderMesh2D(meshes["circle tree"], shaders["VertexColor"], modelMatrix9);
		RenderMesh2D(meshes["rectangle tree"], shaders["VertexColor"], modelMatrix8);
		RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix10);
	
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		translateBirdY += deltaTime * 500;
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		direction = true;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_SPACE) {
		direction = false;
	}
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
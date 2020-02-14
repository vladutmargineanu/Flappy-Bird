#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	// Create rectangle with given bottom left corner, length and color
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, 
		 float width, float length, glm::vec3 color, bool fill = false);

	// Create circle with given bottom left corner, length and color
	Mesh* CreateCircle(std::string name, float radius,
		float centreX, float centreY, glm::vec3 color, bool fill);

	// Create triangle with given bottom left corner, length and color
	Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner, 
		float width, float length, glm::vec3 color, bool fill = false);
}


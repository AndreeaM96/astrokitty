#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateAstronaut(std::string name, float length, glm::vec3 color, bool fill)
{
	//glm::vec3 corner = leftBottomCorner;
	float height = sqrt(3.0f) * length / 2.0f; //inaltimea triungiului. Astronautul este un triunghi echilateral

	std::vector<VertexFormat> vertices = 
	{
		
		VertexFormat(glm::vec3(length / 2.0f, -height / 3.0f, 1), color),
		VertexFormat(glm::vec3(1, 2.0f * height / 3.0f, 1), color),
		VertexFormat(glm::vec3(-length / 2.0f, -height / 3.0f, 1), color)
		
	};
	
	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 cent, float radius, glm::vec3 color, bool fill)
{
	glm::vec3 center = cent;


	std::vector<VertexFormat> vertices = 
	{
		VertexFormat(center - glm::vec3(radius / 2, radius, 0), color),
		VertexFormat(center - glm::vec3((-1) * radius / 2, radius, 0), color),
		VertexFormat(center + glm::vec3(radius, (-1) * radius / 2, 0), color),
		VertexFormat(center + glm::vec3(radius, radius / 2, 0), color),
		VertexFormat(center + glm::vec3(radius / 2, radius, 0), color),
		VertexFormat(center + glm::vec3((-1) * radius / 2, radius, 0), color),
		VertexFormat(center - glm::vec3(radius, (-1) * radius / 2, 0), color),
		VertexFormat(center - glm::vec3(radius, radius / 2, 0), color)
	};


	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7 };

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// adaug punctul central si adaug indicii pentru triunghiuri
		vertices.push_back(VertexFormat(center, color)); // index centru = 8
		indices.clear();
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(8);

		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(8);

		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(8);

		indices.push_back(3);
		indices.push_back(4);
		indices.push_back(8);

		indices.push_back(4);
		indices.push_back(5);
		indices.push_back(8);

		indices.push_back(5);
		indices.push_back(6);
		indices.push_back(8);

		indices.push_back(6);
		indices.push_back(7);
		indices.push_back(8);

		indices.push_back(7);
		indices.push_back(0);
		indices.push_back(8);
	}


	circle->InitFromData(vertices, indices);
	return circle;
}
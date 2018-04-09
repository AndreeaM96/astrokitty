#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

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

	translateX = 0;
	translateY = 0;
	scaleX = 1;
	scaleY = 1;
	asteroidAngle = 0;


	Mesh* astronaut = Object2D::CreateAstronaut("astronaut", astronautSize, glm::vec3(0, 0.5f, 0.2f), true);
	AddMeshToList(astronaut);

	Mesh* final_platform = Object2D::CreateRectangle("final_platform", final_platform_lcorner, final_platform_width, final_platform_height, glm::vec3(0, 0.8f, 0), true);
	AddMeshToList(final_platform);

	Mesh* stat_platform = Object2D::CreateRectangle("stat_platform", stat_platform_lcorner, stat_platform_width, stat_platform_height, glm::vec3(1, 0, 0), true);
	AddMeshToList(stat_platform);

	Mesh* refl_platform = Object2D::CreateRectangle("refl_platform", refl_platform_lcorner, refl_platform_width, refl_platform_height, glm::vec3(0, 0.5f, 0.5f), true);
	AddMeshToList(refl_platform);

	Mesh* asteroid1 = Object2D::CreateCircle("asteroid1", asteroid1_center, asteroid1_radius, glm::vec3(0.7f, 0.7f, 0), true);
	AddMeshToList(asteroid1);

	Mesh* asteroid2 = Object2D::CreateCircle("asteroid2", asteroid2_center, asteroid2_radius, glm::vec3(0.3, 0, 0.3f), true);
	AddMeshToList(asteroid2);

	Mesh* asteroid3 = Object2D::CreateCircle("asteroid3", asteroid3_center, asteroid3_radius, glm::vec3(0.7f, 0, 0.7f), true);
	AddMeshToList(asteroid3);

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["final_platform"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["stat_platform"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["refl_platform"], shaders["VertexColor"], modelMatrix);

	if (ast1_isBroken == false) { //daca asteroidul 1 nu a fost spart, se roteste
		modelMatrix = glm::mat3(1);
		asteroidAngle = asteroidAngle + deltaTimeSeconds * 3;

		modelMatrix *= Transform2D::Translate(asteroid1_center.x, asteroid1_center.y);
		modelMatrix *= Transform2D::Rotate(asteroidAngle);
		modelMatrix *= Transform2D::Translate(-asteroid1_center.x, -asteroid1_center.y);
		RenderMesh2D(meshes["asteroid1"], shaders["VertexColor"], modelMatrix);
	}

	if (ast2_isBroken == false) { //daca asteroidul 2 nu a fost spart, translateaza
		modelMatrix = glm::mat3(1);

		if (sens_translate == 1) {
			translateY = translateY + deltaTimeSeconds * 100;
			asteroid2_center.y = asteroid2_center.y + deltaTimeSeconds * 100;
			if (translateY >= 200)
				sens_translate = 0;
		}
		else {
			translateY = translateY - deltaTimeSeconds * 100;
			asteroid2_center.y = asteroid2_center.y - deltaTimeSeconds * 100;
			if (translateY <= deltaTimeSeconds)
				sens_translate = 1;
		}

		modelMatrix *= Transform2D::Translate(translateX, translateY);
		RenderMesh2D(meshes["asteroid2"], shaders["VertexColor"], modelMatrix);
	}

	if (ast3_isBroken == false) { //daca asteroidul 1 nu a fost spart, se scaleaza
		modelMatrix = glm::mat3(1);

		if (sens_scale == 1) {
			scaleX = scaleX + deltaTimeSeconds;
			scaleY = scaleY + deltaTimeSeconds;
			asteroid3_radius = asteroid3_radius + deltaTimeSeconds;
			if (scaleX >= 1.5f)
				sens_scale = 0;
		}
		else {
			scaleX = scaleX - deltaTimeSeconds;
			scaleY = scaleY - deltaTimeSeconds;
			asteroid3_radius = asteroid3_radius - deltaTimeSeconds;
			if (scaleX < 0.75f) {
				sens_scale = 1;
			}
		}

		modelMatrix *= Transform2D::Translate(asteroid3_center.x, asteroid3_center.y);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY);
		modelMatrix *= Transform2D::Translate(-asteroid3_center.x, -asteroid3_center.y);

		RenderMesh2D(meshes["asteroid3"], shaders["VertexColor"], modelMatrix);
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(astronautSize / 2, astronautHeight / 3);

	if (isMoving == true) { //daca astronautul se afla in miscare, se verifica coliziunile
		astronautPos.x += pas.x;
		astronautPos.y += pas.y;

		if (astronautPos.x + 2 * astronautHeight / 3 > resolution.x){ //daca m-am ciocnit cu marginea din dreapta a ferestrei
			astronautPos.x = resolution.x - 9 * astronautHeight / 10;
			rot_angle = 90 * 3.14 / 180;

			isMoving = false;
		}
		if (astronautPos.y + 2 * astronautHeight / 3 > resolution.y) { //daca m-am ciocnit cu marginea de sus a ferestrei
			astronautPos.y = resolution.y - 2 * astronautHeight / 3;
			rot_angle = 180 * 3.14 / 180;
			isMoving = false;
		}
		if (astronautPos.x + 2 * astronautHeight / 3 < 0) { //daca m-am ciocnit cu marginea din stanga a ferestrei
			astronautPos.x = -astronautHeight / 4;
			rot_angle = 270 * 3.14 / 180;
			isMoving = false;
		}
		if (astronautPos.y + 2 * astronautHeight / 3 < 0) { //daca m-am ciocnit cu marginea de jos a ferestrei
			astronautPos.y = 0;
			rot_angle = 0;
			isMoving = false;
		}
		if (astronautPos.y + 2 * astronautHeight / 3 >= stat_platform_lcorner.y && 
			astronautPos.x + 2 * astronautHeight / 3 <= stat_platform_lcorner.x + stat_platform_width - 5) { // daca m-am ciocnit cu platforma de stationare
			astronautPos.y = stat_platform_lcorner.y - 2 * astronautHeight / 3;
			rot_angle = 180 * 3.14 / 180;
			isMoving = false;
		}

		// conditiile pentru reflexie
		if (astronautPos.y <= refl_platform_lcorner.y + refl_platform_height &&
			astronautPos.y > refl_platform_lcorner.y + refl_platform_height / 2 &&
			astronautPos.x + 2 * astronautHeight / 3 >= refl_platform_lcorner.x &&
			astronautPos.x < refl_platform_lcorner.x + refl_platform_width &&
			pas.y < 0) {
			pas.y = -pas.y;
		}
		else {
			if (astronautPos.y + 2 * astronautHeight / 3 >= refl_platform_lcorner.y &&
				astronautPos.y + 2 * astronautHeight / 3 < refl_platform_lcorner.y + refl_platform_height / 2 &&
				astronautPos.x + 2 * astronautHeight / 3 >= refl_platform_lcorner.x &&
				astronautPos.x <= refl_platform_lcorner.x + refl_platform_width &&
				pas.y > 0) {
				pas.y = -pas.y;
			}

			else {
				if (astronautPos.y + 2 * astronautHeight / 3 <= final_platform_lcorner.y + final_platform_height &&
					astronautPos.y + 2 * astronautHeight / 3 >= final_platform_lcorner.y &&
					astronautPos.x + 2 * astronautHeight / 3 >= final_platform_lcorner.x) {
					astronautPos.x = final_platform_lcorner.x - 9 * astronautHeight / 10;
					rot_angle = 90 * 3.14 / 180;
					isMoving = false;
					isGameOver = true;
				}
				else {
					if (astronautPos.y >= refl_platform_lcorner.y &&
						astronautPos.y <= refl_platform_lcorner.y + refl_platform_height &&
						astronautPos.x + 2 * astronautHeight / 3 >= refl_platform_lcorner.x &&
						astronautPos.x + 2 * astronautHeight / 3 < refl_platform_lcorner.x + refl_platform_width / 2)
						pas.x = -pas.x;
					else {
						if (astronautPos.y >= refl_platform_lcorner.y &&
							astronautPos.y <= refl_platform_lcorner.y + refl_platform_height &&
							astronautPos.x + 2 * astronautHeight / 3 <= refl_platform_lcorner.x + refl_platform_width &&
							astronautPos.x + 2 * astronautHeight / 3 > refl_platform_lcorner.x + refl_platform_width / 2
							)
							pas.x = -pas.x;
					}
				}
			}
		}

		if (ast1_isBroken == false) { //daca asteroidul 1 inca nu a fost spart, se verifica coliziunea
			float distX = asteroid1_center.x - astronautPos.x;
			float distY = asteroid1_center.y - astronautPos.y;
			float distance = sqrt(distX * distX + distY * distY);
			if (distance < 2 * astronautHeight / 3 + asteroid1_radius) {
				pas.y = -pas.y;
				ast1_isBroken = true;
			}
		}

		if (ast2_isBroken == false) { //daca asteroidul 2 inca nu a fost spart, se verifica coliziunea
			float distX = asteroid2_center.x - astronautPos.x;
			float distY = asteroid2_center.y - astronautPos.y;
			float distance = sqrt(distX * distX + distY * distY);
			if (distance < 2 * astronautHeight / 3 + asteroid2_radius) {
				pas.x = -pas.x;
				ast2_isBroken = true;
			}
		}

		if (ast3_isBroken == false) { //daca asteroidul 3 inca nu a fost spart, se verifica coliziunea
			float distX = asteroid3_center.x - astronautPos.x;
			float distY = asteroid3_center.y - astronautPos.y;
			float distance = sqrt(distX * distX + distY * distY);
			if (distance < 2 * astronautHeight / 3 + asteroid3_radius) {
				pas.x = -pas.x;
				ast3_isBroken = true;
			}
		}
	}

	modelMatrix *= Transform2D::Translate(astronautPos.x, astronautPos.y);
	modelMatrix *= Transform2D::Rotate(rot_angle);
	RenderMesh2D(meshes["astronaut"], shaders["VertexColor"], modelMatrix);

}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (isMoving == false && isGameOver == false) { //daca astronautul nu se misca deja, si daca jocul nu s-a terminat
		cursorPos = glm::vec3(mouseX, resolution.y - mouseY, 1); //salvez pozitia unde s-a dat click
		isMoving = true; //setez faptul ca astronautul se misca

		glm::vec3 dif = glm::vec3(cursorPos.x - astronautPos.x, cursorPos.y - astronautPos.y, 1); //calculez diferentele intre coordonate
		radian = atan2(dif.y, dif.x); //calcul intermediar pentru a afla pasul de miscare al astronautului
		pas.x = cos(radian) * speed; //pasul astronautului pe axa ox la fiecare refresh
		pas.y = sin(radian) * speed; //pasul astronautului pe axa oy la fiecare refresh

		rot_angle = atan((astronautPos.y - cursorPos.y) / (astronautPos.x - cursorPos.x)); //unghiul de rotatie al astronautului
		if (astronautPos.x - cursorPos.x > 0) {
			rot_angle = rot_angle + 3.1415f;
		}
	}
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

#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

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
	glm::mat3 modelMatrix;
	float translateX, translateY; //translatiile asteroidului 2
	float scaleX, scaleY; //scalarile asteroidului 3
	float asteroidAngle; // unghiul de rotatie al asteroidului 1

	glm::ivec2 resolution = window->GetResolution();
	glm::vec3 corner = glm::vec3(0, 0, 1);
	
	float astronautSize = 50; //marimea astronautului. Lungimea oricarei laturi (astronaut = triunghi echilateral)
	glm::vec3 astronautPos = { 0, 0, 1 }; //coordonatele centrului astronautului
	float astronautHeight = sqrt(3.0f) * astronautSize / 2.0f; //inaltimea astronautului

	glm::vec3 final_platform_lcorner = glm::vec3(resolution.x - 40, resolution.y / 5, 1); //coltul stanga jos al platformei finale
	float final_platform_width = 40; //grosimea platformei finale
	float final_platform_height = resolution.y / 2; //inaltimea platformei finale

	glm::vec3 stat_platform_lcorner = glm::vec3(0, resolution.y - 40, 1); //coltul stanga jos al platformei de stationare
	float stat_platform_width = 600; //grosimea platformei de stationare
	float stat_platform_height = 40; //inaltimea platformei de stationare

	glm::vec3 refl_platform_lcorner = glm::vec3(resolution.x / 3, resolution.y / 2, 1); //coltul stanga jos al platformei de reflexie
	float refl_platform_width = 250; //grosimea platformei de reflexie
	float refl_platform_height = 40; //inaltimea platformei de reflexie

	glm::vec3 asteroid1_center = glm::vec3(250, 500, 1); //coordonatele centrului asteroidului 1
	float asteroid1_radius = 80; //raza asteroidului 1

	glm::vec3 asteroid2_center = glm::vec3(resolution.x - 200, resolution.y / 3, 1); //coordonatele centrului asteroidului 2
	float asteroid2_radius = 60; //raza asteroidului 2

	glm::vec3 asteroid3_center = glm::vec3(resolution.x / 2, resolution.y / 5, 1); //coordonatele centrului asteroidului 3
	float asteroid3_radius = 80; //raza asteroidului 3

	glm::vec3 cursorPos = { 0, 0, 1 }; //pozitia cursorului
	float speed = 5; //viteza astronautului
	bool isMoving = false; //variabila in care retin starea de miscare sau nu a astronautului

	float rot_angle = 0; //unghiul de rotatie al astronautului
	float radian = 0; //folosit pentru calculul pasului
	glm::vec3 pas = { 0, 0, 1 }; //pasul cu care se muta astronautul la fiecare refresh

	bool ast1_isBroken = false; //retin daca asteroidul 1 e distrus sau nu
	bool ast2_isBroken = false; //retin daca asteroidul 2 e distrus sau nu
	bool ast3_isBroken = false; //retin daca asteroidul 3 e distrus sau nu
	bool isGameOver = false; //retin daca jocul s-a terminat sau nu

	int sens_translate = 1; //sensul in care translateaza asteroidul 2 (are valoarea 1 sau 0)
	int sens_scale = 1; //sensul in care se scaleaza asteroidul 3 (are valoarea 1 sau 0)

};
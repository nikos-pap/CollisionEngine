#pragma once
#include "CameraController.h"
#include "DynamicShapeArray.h"

extern bool tex;

class InputController {
private:
	CameraController* camera;
	DynamicShapeArray* shapeArray;
	//speeds
	float cameraSpeed = 1000.0f / GLOBAL_SPEED;
	float yawSpeed = 100.0f / GLOBAL_SPEED;

	//flags
	bool joystick_space = false;
	bool joystick_tex = false;
	bool joystick_mute = false;

	bool spaceChecker = true;
	bool texChecker = true;
	bool muteChecker = true;

public:
	InputController(CameraController* camera, DynamicShapeArray* shapeArray);
	//~InputController();
	int parseInputs(GLFWwindow* window, float deltaTime);
};
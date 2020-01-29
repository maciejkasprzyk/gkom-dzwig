#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using namespace glm;


class Camera {
	GLFWwindow* window;
	glm::vec3 position;
	float horizontalAngle;
	float verticalAngle;
	float initialFoV;
	float speed;
	float mouseSpeed;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
public:
	Camera::Camera(
		GLFWwindow* windoww,
		glm::vec3 pos,
		float hAngle,
		float vAngle,
		float initFoV,
		float speedOfCamera,
		float speedOfMouse) {
		window = windoww;
		position = pos;
		horizontalAngle = hAngle;
		verticalAngle = vAngle;
		initialFoV = initFoV;
		speed = speedOfCamera;
		mouseSpeed = speedOfMouse;
	};



	glm::mat4 getViewMatrix() {
		return ViewMatrix;
	}
	glm::mat4 getProjectionMatrix() {
		return ProjectionMatrix;
	}
	float getFoV() {
		return initialFoV;
	}
	void computeMatricesFromInputs();
};

#endif
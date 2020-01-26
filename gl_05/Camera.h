#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <vector>
#include <glm/glm.hpp>
using namespace glm;


class Camera {
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
		glm::vec3 pos,
		float hAngle,
		float vAngle,
		float initFoV,
		float speedOfCamera,
		float speedOfMouse) {
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
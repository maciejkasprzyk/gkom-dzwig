#pragma once
#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Object.h"
#include "Cube.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>
#include "CraneTop.h"
#include "CraneBottom.h"

class Crane : public Compound {
public:

	Crane() {

		auto top = std::unique_ptr<CraneTop>(new CraneTop());
		addObject(std::move(top));
		auto bottom = std::unique_ptr<CraneBottom>(new CraneBottom());
		addObject(std::move(bottom));

	}
	void rotateTop(bool dir,float deltaTime) {
		if (dir) {
			objects[0]->rotate2(glm::vec3(0.0f, 0.5f, 0.0f) * deltaTime);
		}
		else {
			objects[0]->rotate2(glm::vec3(0.0f, -0.5f, 0.0f) * deltaTime);
		}
	}
	void forward(float deltaTime) {
		dynamic_cast<CraneTop&>(*objects[0]).forward(deltaTime);
	}
	void backwards(float deltaTime) {
		dynamic_cast<CraneTop&>(*objects[0]).backwards(deltaTime);
	}
	void up(float deltaTime) {
		dynamic_cast<CraneTop&>(*objects[0]).up(deltaTime);
	}
	void down(float deltaTime) {
		dynamic_cast<CraneTop&>(*objects[0]).down(deltaTime);
	}

};

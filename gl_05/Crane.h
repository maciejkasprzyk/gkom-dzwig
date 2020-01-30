#pragma once
#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Object.h"
#include "Cube.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>



class Crane : public Compound {
public:

	Crane() {

		std::unique_ptr<Cube> base[3];
		std::generate(
			begin(base),
			end(base),
			[]() { return std::make_unique<Cube>(YELLOW); }
		);

		for (auto& x : base) {

			x->scale(glm::vec3(0.05f, 2.0f, 0.05f));
			x->move(glm::vec3(0.0f, 0.5f, 0.0f));
		}

		addObject(std::move(base[0]));
		

	}

};

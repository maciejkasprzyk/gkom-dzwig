#pragma once
#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Object.h"
#include "Cube.h"
#include "Compound.h"

class Crane : public Compound {
public:

	Crane() {

		std::unique_ptr<Cube> p1(new Cube(YELLOW));
		
		addObject(std::move(p1));
	}

};

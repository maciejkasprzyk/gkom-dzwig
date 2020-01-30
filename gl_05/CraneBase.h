#pragma once

#include "Cube.h"
#include <vector>

class CraneBase : public Compound{

public:
	CraneBase()
	{
		auto base1 = std::unique_ptr<Cube>(new Cube(YELLOW));
		auto base2 = std::unique_ptr<Cube>(new Cube(YELLOW));
		
		
		
		base1->move(glm::vec3(0.0f, 0.05f, 0.0f));
		base1->scale(glm::vec3(0.3f, 0.1f, 2.0f));
		base1->rotate(glm::vec3(0.0f, 45.0f, 0.0f));

		base2->move(glm::vec3(0.0f, 0.05f, 0.0f));
		base2->scale(glm::vec3(0.3f, 0.1f, 2.0f));
		base2->rotate(glm::vec3(0.0f, -45.0f, 0.0f));

		addObject(std::move(base1));
		addObject(std::move(base2));

	}



};